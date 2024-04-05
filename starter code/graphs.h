/**
 * FILE: GRAPHS.H
 *
 * Contains definitions of data structures and error codes required for the
 * Graph implementations. It also provides declarations of the functions 
 * that have to be implemented too.
 *
 * NOTE: YOU DO NOT NEED TO MODIFY THIS FILE. IT CAN BE USED AS-IS.
 * THE CODE THAT YOU IMPLEMENT WILL BE IN THE GRAPHS.C FILE.
 */

#ifndef __GRAPHS_HEADER__ // this is a 'guard' on the header file, to prevent it's contents from
#define __GRAPHS_HEADER__ // being redefined more than once during the build process

/** 
 * ### INCLUDES
 */
#include <stdbool.h> // required, defines the 'bool' data type in C

/**
 * ### ERROR codes / SUCCESS codes ###
 * 
 * PLEASE USE THESE AS THE RETURN VALUES FOR YOUR FUNCTIONS. 
 *
 * Example:
 * return INVALID_INPUT_PARAMETER;
 *
 */
#define SUCCESS                	100   	// Value to be returned if a function is completed successfully
#define INVALID_INPUT_PARAMETER	101     // Value to be returned if you detect that one of the input parameters 
                                      	// into your function is invalid, e.g. it is NULL or an unexpected value
#define PARTIAL_SUCCESS         102     // Value to return if there has been only partial success in adding a collection
                                        // of edges to a graph, i.e., some were added, some were not.
#define MEMORY_ALLOCATION_ERROR 103     // Value to be returned if your function detects an operation that is being
                                        // attempted on your list data structure isn't valid or your list
                                        // isn't in a ready state to receive. For example, an attempt is made to remove
                                        // an item from an empty list
#define NOT_IMPLEMENTED          104    // Value to be returned if you haven't implemented this function yet
#define FILE_IO_ERROR            105    // May be required for some File IO tasks. E.g. failure to open a file.

/** OTHER CONSTANTS **/
#define NUMBER_OF_VERTICES 		10 		// the number of vertices on the graphs you will be working with
#define VERY_LARGE_NUMBER		9999999	// a large number, guaranteed to be larger than any path distance
										// found on a graph


/** ### DATA STRUCTURES ### */

/* typedef for an Adjacency Matrix. Contains a 2-D array
 * as one of its fields, which represents the matrix itself 
 */
/* DO NOT MODIFY */
typedef struct adjacency_matrix {
	int matrix[NUMBER_OF_VERTICES][NUMBER_OF_VERTICES];
} AdjacencyMatrix;

/* typedef for an Edge, to record details of an Edge on
 * a graph, e.g., start node (src), destination node (dest)
 * and the weight on the edge
 */
/* DO NOT MODIFY */
typedef struct edge {
	int src;
	int dest;
	int weight;
} Edge;

/* typedef for one of the rows / entries in a Dijkstra Table.
 * For a corresponding node in a graph, will record whether that
 * node has been visited, the shortest cumulative distance found
 * to that node so far from a starting point, and any predecessor
 * found, along that shortest distance
 */
/* DO NOT MODIFY */
typedef struct dijkstra_table_entry {
    bool visited;
    int distance;
    int predecessor;
} DijkstraTableEntry; 

/* typedef the actual Dijkstra Table itself
 * It contains an array of Dijkstra Table entries as one of its fields,
 * an entry for each corresponding node on the graph
 */
/* DO NOT MODIFY */
typedef struct dijkstra_table {
    DijkstraTableEntry table[NUMBER_OF_VERTICES];
} DijkstraTable;

/* typedef for a list node in an Adjacency List.
 * For node X on a graph, it records details of any directly
 * adjacent destination on the graph from node X, as well as 
 * the weight of the edge connecting them.
 * Each list node may refer / point to another list node after it.
 * This represents the case, for example, where node X has several
 * directly adjacency destinations emanating from it, and these have
 * to be listed, one after another in a connected fashion. 
 */
/* DO NOT MODIFY */
typedef struct listnode {
	int destNode;
	int weight;
	struct listnode *next;
} ListNode;

/* typedef for the Adjacency List itself
 * It contains an array of pointers to list nodes. Effectively, a series
 * of mini-linked lists, each one corresponding to a node on the graph,
 * and each one recording any of the adjacent destinations from each
 * node on the graph
 */
/* DO NOT MODIFY */
typedef struct adjacency_list {
	ListNode* adjacencyList[NUMBER_OF_VERTICES];
} AdjacencyList;

/** ### FUNCTION DECLARATIONS ### */
/*  DO NOT MODIFY FUNCTION NAMES, RETURN TYPES, OR INPUT PARAMETERS.
 *  YOU WILL IMPLEMENT THESE FUNCTIONS IN THE SEPARATE GRAPHS.C FILE.
 */

/**
 * Create a new, empty Adjacency Matrix, returning a pointer to the newly 
 * allocated matrix OR a value of NULL in the event of error. Ensure that 
 * the matrix is initialised to the defaultEdgeValue provided.
 * 
 * Remember to use myMalloc() to allocate memory instead of malloc(). 
 *
 */
AdjacencyMatrix* createAdjacencyMatrix(int defaultEdgeValue);

/**
 * Add a new edge into the Adjacency Matrix provided, for the
 * relevant source node (src), destination node (dest), and weight
 * of the edge.
 * 
 * The function should return SUCCESS or a relevant error code.
 */
int addEdge(AdjacencyMatrix *pMatrix, int src, int dest, int weight);

/**
 * This function should add a collection of new edges into the 
 * AdjacencyMatrix provided, using the input values given. 
 * The function should return SUCCESS, PARTIAL_SUCCESS, or 
 * INVALID_INPUT_PARAMETER. 
 * 
 * Consider: could you keep a count of how many edges were added 
 * successfully as you go along, and compare that to the number of 
 * edges provided?  
 * 
 */
int addEdges(AdjacencyMatrix *pMatrix, Edge edges[], int edgeNum);

/**
 * This function should conduct a depth-first traversal of a graph and record the traversal 
 * sequence into the array provided (traversalOutput). The function expects to receive the 
 * following inputs:
 * - A pointer to an Adjacency Matrix representing the graph to be traversed.
 * - The index of the starting node in the graph where the traversal should commence.
 * - An array which will be used to store the output of the traversal, i.e., the order in 
 *   which the traversal visited the nodes in the graph. The array will store the index of the 
 *   graph nodes which are visited and in the order in which they are visited. The first item of 
 *   the array will show the starting node of the traversal. The last item of the array will be 
 *   the final node that was visited. 
 * 
 * The function should return SUCCESS or a relevant error code.
 *
 */
int doDepthFirstTraversal(AdjacencyMatrix *pMatrix, int startingNode, int traversalOutput[]);


/**
 * This function will receive the name of a file on disk which contains the 
 * data for a graph which has been stored in the form of an adjacency matrix. 
 * The function should read the content from the file and use it to populate 
 * the AdjacencyMatrix provided. The file will be formatted thus:
 * 
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 
 * I.e., assuming a graph with 10 vertices, this will require a 10 x 10 matrix.
 * 
 * Each line in the file represents the next row in matrix, indexed from 0 to 9.
 * 
 * Each line will record the weight of the relevant edge in the graph. This will
 * be a value of zero (no edge) or a value of greater than zero (signifying that
 * an edge does exist, and the weight of that edge).
 * 
 * You can assume that the file content will be valid and in the correct format 
 * too, so you do not need to check for this when reading in from the file. 
 * Other validations may be required in the function however.
 * 
 * The function should return SUCCESS or a relevant error code.
 * 
 */
int loadMatrixFromFile(AdjacencyMatrix *pMatrix, char filename[]);

/**
 * This function should perform the Dijkstra algorithm. It expects to receive a 
 * ready-made graph to work with, in the form of an AdjacencyMatrix. It 
 * also expects to receive an empty DijkstraTable, ready to be initialised and 
 * used. It also expects to receive the starting node on the graph to commence 
 * the algorithm from. 
 * 
 * This function should implement the algorithm, running it on the graph 
 * provided and updating the DijkstraTable with the outcome. After the function 
 * is called, the DijkstraTable will be inspected to determine whether the 
 * algorithm has been completed successfully. 
 * 
 * The function should return SUCCESS or a relevant error code.
 */
int doDijsktraAlgorithm(AdjacencyMatrix *pMatrix, DijkstraTable *pTable, int startNode);


/**
 * This function should determine the shortest path that exists on a graph 
 * from a given starting node (nodeFrom) to a given end node (nodeTo). 
 * The function expects to receive a pre-populated DijkstraTable which already 
 * contains the outcome of running the Dijkstra algorithm on a graph. It will 
 * also be provided with an array (pathFound) into which the shortest path should 
 * be recorded. The path should be recorded in reverse order; showing, from the 
 * end node, the predecessors that lead us there from the start node. 
 * For example, if the shortest path on graph from node 2 to node 8 was found 
 * to be 2 -> 4 -> 5 -> 8. The content that would be recorded in the ‘pathFound’ 
 * variable would be as follows: [8][5][4][2]. I.e., it shows the relevant nodes 
 * in the path, in reverse order. This includes the start and end node too. 
 * 
 * The function should return SUCCESS or a relevant error code.
 */
int findShortestPathTo(DijkstraTable *pTable, int nodeFrom, int nodeTo, int pathFound[]);


/**
 * This function should add a new edge into the AdjacencyList provided, based on 
 * a starting vertex (src), destination vertex (dest), and weight of the edge. 
 * 
 * The function should return SUCCESS or an error code. 
 * 
 * Remember to use myMalloc() to allocate memory instead of malloc(). 
 */
int addEdgeToAdjacencyList(AdjacencyList *pList, int src, int dest, int weight);


/**
 * This function should populate the AdjacencyList provided. The list can be 
 * populated by examining the content of a corresponding adjacency matrix which
 * is also provided. By examining the adjacency matrix, the necessary edges on 
 * the graph can be ascertained and then added into the adjacency list at the 
 * appropriate locations. 
 * 
 * NOTE: when you are traversing the adjacency matrix, you must do it in the order
 * intimated below:
 * 
 * for i is 0 to number of rows in matrix
 *    for j is 0 to number of cols in matrix
 *        next element to process is at [i][j]
 * 
 * If you do not process the matrix in this order, your adjacency list will not
 * be populated in the correct order and will fail tests that run on it. 
 * 
 * The function should return SUCCESS or an error code. 
 * 
 * Remember to use myMalloc() to allocate memory instead of malloc(). 
 * 
 */
int populateAdjacencyList(AdjacencyList *pList, AdjacencyMatrix *pMatrix);

/**
 * In the lectures, we looked at how to use an AdjacencyMatrix representation
 * of a graph as a basis for completing Dijkstra's algorithm. For this function, 
 * see if you can implement the algorithm using an AdjacencyList representation
 * of a graph instead. The AdjacencyList has the exact same content as the 
 * AdjacencyMatrix: it represents all of the nodes on a graph and the edges between 
 * them. It just represents these in a different way. 
 * 
 * To implement this function, you just need to review how you were using the 
 * AdjacencyMatrix during specific stages of the Dijkstra algorithm, and think about
 * how you could swap the AdjacencyList into these stages instead. The main difference
 * is likely to be related to how the edges that are emanating from the 'current'
 * node in the traversal are discovered. With the AdjacencyMatrix, we simply went
 * through the relevant row in the matrix, examining each column one at a time.
 * A similar approach can be taken for the AdjacencyList, but requiring a
 * different form of traversal for the relevant 'row' in the list.
 * 
 * The function expects to receive a ready-made graph to work with, in the form of 
 * an AdjacencyList. It also exepcts to receive an empty DijkstraTable, ready to be 
 * populated. It will also receive the starting node on the graph to 
 * commence the algorithm from. This function should implement the algorithm, 
 * running it on the graph provided and updating the DijkstraTable with the 
 * outcome. After the function is called, the DijkstraTable will be inspected to 
 * determine whether the algorithm has been completed successfully. 
 * 
 * The function should return SUCCESS or an error code.
 */
int doDijsktraAlgorithmOnAdjacencyList(AdjacencyList *pList, DijkstraTable *pTable, int startNode);


/**
 * myMalloc(): a function to allocate memory.
 *
 * DO NOT REMOVE OR MODIFY THIS - PLEASE LEAVE AS IS
 * 
 * YOU DO NOT NEED TO IMPLEMENT THIS FUNCTION YOURSELF, IT WILL BE DONE FOR YOU
 *
 * You will use myMalloc() to allocate memory in your own code. 
 * The implementation of this function is provided to you and
 * has already been placed in the accompanying 'tester' files 
 * where it is ready to use. You simply need to call the
 * function in your code where required. When you compile your
 * own code with any of the tester files, everything will be linked 
 * together. 
 *
 * myMalloc works exactly the same way as malloc. For example, if 
 * you were using malloc to allocate an array of 10 integers, it
 * would be as follows:
 *
 * int *array = (int*)malloc(sizeof(int) * 10);
 * 
 * Using myMalloc will be exactly the same:
 *
 * int *array = (int*)myMalloc(sizeof(int) * 10);
 * 
 */
void *myMalloc(size_t size);



#endif
