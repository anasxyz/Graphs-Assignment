/*
    Name: Anas Saad
    Matric number: 2510059
    Module code: AC21008
*/

/**
 * FILE: GRAPHS.C
 * 
 * THIS FILE  CONTAINS EMPTY / DO-NOTHING IMPLEMENTATIONS
 * FOR THE FUNCTIONS REQUIRED FOR THE GRAPHS ASSIGNMENT. 
 *
 * DO NOT RENAME THESE FUNCTIONS OR CHANGE THEIR RETURN
 * TYPES OR INPUT PARAMETERS.
 *
 * YOU NEED TO COMPLETE THE IMPLEMENTATION OF THESE
 * FUNCTIONS BY REPLACING THE CURRENT IMPLEMENTATIONS
 * WITH IMPLEMENTATIONS OF YOUR OWN. 
 *
 * THESE FUNCTIONS RECEIVE INPUT PARAMETERS THAT WILL
 * PROVIDE THEM WITH THE INFORMATION THAT THEY REQUIRE. YOU
 * DO NOT NEED TO USE USER INPUT FUNCTIONS SUCH AS SCANF
 * ETC, TO READ IN VALUES. THE GRAPH FUNCTIONS ARE CALLED
 * FROM A SEPARATE FILE (SEE THE TESTER PROGRAM) AND THE
 * INPUTS TO THE FUNCTIONS ARE PROVIDED THERE. 
 *
 * THE FUNCTIONS RETURN VALUES TO REPRESENT SUCCESS, ERROR,
 * OR, IN SOME CASES, DATA THAT HAS TO BE RETURNED. THE CALLER 
 * OF THESE FUNCTIONS WILL EXPECT TO RECEIVE THESE RETURN VALUES 
 * IN ORDER TO VERIFY THE OUTCOME OF THE FUNCTION CALL. 
 *
 * IF THERE AREANY FUNCTIONS THAT YOU DON'T HAVE TIME TO 
 * IMPLEMENT, PLEASE LEAVE THE EMPTY / DO-NOTHING IMPLEMENTATION
 * FOR THEM IN THIS FILE, OTHERWISE YOUR PROGRAM WON'T COMPILE
 * WHEN IT IS FED INTO OUR TESTER PROGRAM.
 * 
 */

/** 
 * ### INCLUDES
 */
#include <stdio.h>  // required for access to file input-output functions in C
#include <stdlib.h> // may be required for access to memory allocation functions
#include "graphs.h" // required, to include the Graph data structures and function declarations

/** #### FUNCTION IMPLEMENTATIONS ## */


/**
 * Create a new, empty Adjacency Matrix, returning a pointer to the newly 
 * allocated matrix OR a value of NULL in the event of error. Ensure that 
 * the matrix is initialised to the defaultEdgeValue provided.
 * 
 * Remember to use myMalloc() to allocate memory instead of malloc(). 
 *
 */
AdjacencyMatrix* createAdjacencyMatrix(int defaultEdgeValue)
{
    // Allocate some memory for the adjacency matrix using myMalloc
    AdjacencyMatrix* adjMatrix = (AdjacencyMatrix*)myMalloc(sizeof(AdjacencyMatrix));
    
    // Check if myMalloc worked
    if (adjMatrix == NULL) {
        return NULL;
    }
    
    // Fill matrix with defaultEdgeValue
    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        for (int j = 0; j < NUMBER_OF_VERTICES; j++) {
            adjMatrix->matrix[i][j] = defaultEdgeValue;
        }
    }
    
    return adjMatrix;
}

/**
 * Add a new edge into the Adjacency Matrix provided, for the
 * relevant source node (src), destination node (dest), and weight
 * of the edge.
 * 
 * The function should return SUCCESS or a relevant error code.
 */
int addEdge(AdjacencyMatrix *pMatrix, int src, int dest, int weight)
{
    // input validation for source and target nodes
    if (pMatrix == NULL || src < 0 || src >= NUMBER_OF_VERTICES || dest < 0 || dest >= NUMBER_OF_VERTICES) {
        return INVALID_INPUT_PARAMETER;
    }

    // Update the row and column of the matrix with the weight
    pMatrix->matrix[src][dest] = weight;

    return SUCCESS;
}

/**
 * This function should add a collection of new edges into the 
 * AdjacencyMatrix provided, using the input values given. 
 * The function should return SUCCESS, PARTIAL_SUCCESS, or 
 * INVALID_INPUT_PARAMETER. 
 * 
 */
int addEdges(AdjacencyMatrix *pMatrix, Edge edges[], int edgeNum)
{ 
    // Input validation
    if (pMatrix == NULL || edgeNum < 0) {
        return INVALID_INPUT_PARAMETER;
    }

    // Variable storing successful edges implemented
    int edgeSuccess = 0;

    // Go through edges
    for (int i = 0; i < edgeNum; i++) {
        int loopSrc = edges[i].src;
        int loopDest = edges[i].dest;
        int loopWeight = edges[i].weight;

        // Again, the source node and target node both have to be in range
        // so must have validation for their values
        if (loopSrc < 0 || loopSrc >= NUMBER_OF_VERTICES || loopDest < 0 || loopDest >= NUMBER_OF_VERTICES) {
            return INVALID_INPUT_PARAMETER;
        } 

        pMatrix->matrix[loopSrc][loopDest] = loopWeight;
        edgeSuccess++;
    }

    // If number of edges implemented is same as number of edges overall then return SUCCESS
    if (edgeSuccess == edgeNum) {
        return SUCCESS;
    } 
    else {
        return PARTIAL_SUCCESS;
    }
}

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
int doDepthFirstTraversal(AdjacencyMatrix *pMatrix, int startingNode, int traversalOutput[])
{
    // Parameter validation
    if (pMatrix == NULL || startingNode < 0 || startingNode >= NUMBER_OF_VERTICES || traversalOutput == NULL) {
        return INVALID_INPUT_PARAMETER;
    }

    // Variable storing visited nodes
    int visited[NUMBER_OF_VERTICES];

    // Set all nodes to unvisited
    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        visited[i] = 0;
    }

    // Variable storing the traversal output's index
    int tIndex = 0;

    // Create a stack with top variable storing top element's index
    int stack[NUMBER_OF_VERTICES];
    int top = 0;

    // Push the starting node onto the stack
    stack[top] = startingNode;
    top++;

    // Loop until stack is empty
    while (top > 0) {
        // Pop top element from the stack
        top--;
        int currentNode = stack[top];

        // If the node hasn't been visited yet
        if (visited[currentNode] == 0) {
            traversalOutput[tIndex++] = currentNode;
            visited[currentNode] = 1;
        }

        // Look for next unvisited nodes in reverse order
        // because I was having problems with the ordering of the stack and the traversalOutput
        // array, so decided to do it backwards
        for (int i = NUMBER_OF_VERTICES - 1; i >= 0; i--) {
            if (pMatrix->matrix[currentNode][i]) {
                if (visited[i] == 0) {
                    // Push the next unvisited node to the stack 
                    stack[top] = i;
                    top++;
                }
            }
        }
    }

    return SUCCESS;
}

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
 * The function should return SUCCESS or a relevant error code.
 * 
 */
int loadMatrixFromFile(AdjacencyMatrix *pMatrix, char filename[])
{
    // Input validation
    if (pMatrix == NULL || filename == NULL) {
        return INVALID_INPUT_PARAMETER;
    }

    // Create pointer to file
    FILE *matrixFile;
    // Open file to read
    matrixFile = fopen(filename, "r");

    // Go through and read edges from rows and columns
    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        for (int j = 0; j < NUMBER_OF_VERTICES; j++) {
            // Check if current index is an integer
            // If false then proceed
            if (!fscanf(matrixFile, "%d", &pMatrix->matrix[i][j])) {
                // If current index is a non-integer then close file
                fclose(matrixFile);
                // Return a file handling error
                return FILE_IO_ERROR;
            }
        }
    }

    // Close file
    fclose(matrixFile);

    return SUCCESS;
}

/**
 * This function should perform the Dijkstra algorithm. It will receive a 
 * ready-made graph to work with, in the form of an AdjacencyMatrix. It 
 * will also receive an empty DijkstraTable, ready to be initialised and 
 * used. It will also receive the starting node on the graph to commence 
 * the algorithm from. 
 * 
 * This function should implement the algorithm, running it on the graph 
 * provided and updating the DijkstraTable with the outcome. After the function 
 * is called, the DijkstraTable will be inspected to determine whether the 
 * algorithm has been completed successfully. 
 * 
 * The function should return SUCCESS or a relevant error code.
 */
int doDijsktraAlgorithm(AdjacencyMatrix *pMatrix, DijkstraTable *pTable, int startNode)
{
    // Input validation, as always
    if (pMatrix == NULL || pTable == NULL || startNode < 0 || startNode > NUMBER_OF_VERTICES) {
        return INVALID_INPUT_PARAMETER;
    }

    // Set up Dijkstra's table
    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        // Set all nodes to not visited
        pTable->table[i].visited = false; 
        // Set all nodes distances to a vary large number
        pTable->table[i].distance = VERY_LARGE_NUMBER;
        // Set all nodes predecessors to -1
        pTable->table[i].predecessor = -1;
    }

    // Set distance of starting node to 0
    pTable->table[startNode].distance = 0;

    // Loop to find shortest path for all nodes
    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        int minDistance = VERY_LARGE_NUMBER;
        int minDistNode = -1;

        // Loop through all nodes
        for (int j = 0; j < NUMBER_OF_VERTICES; j++) {
            // Check if node is not visited
            if (pTable->table[j].visited == false) {
                // Check if node has a smaller distance
                if (pTable->table[j].distance < minDistance) {
                    // Set minimum distance and the corresponding node
                    minDistance = pTable->table[j].distance;
                    minDistNode = j;
                }
                
            }
        }

        // Set node with minimum distance to visited
        pTable->table[minDistNode].visited = true;

        // Set distance values for nodes
        for (int x = 0; x < NUMBER_OF_VERTICES; x++) {
            // Check if node is not visited
            if (!pTable->table[x].visited) { 
                // Check if there is an edge between node with minimum distance and x
                if (pMatrix->matrix[minDistNode][x] != 0) {
                    // Calculate new distance through node with minimum distance
                    int newDistance = pTable->table[minDistNode].distance + pMatrix->matrix[minDistNode][x];
                
                    // Update dist and pred if shorter distance is found
                    if (newDistance < pTable->table[x].distance) {
                        pTable->table[x].distance = newDistance;
                        pTable->table[x].predecessor = minDistNode;
                    }
                }
            }
        }
    }

    return SUCCESS;
}


/**
 * This function should determine the shortest path that exists on a graph 
 * from a given starting node (nodeFrom) to a given end node (nodeTo). 
 * The function will be provided with a pre-populated DijkstraTable which already 
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
int findShortestPathTo(DijkstraTable *pTable, int nodeFrom, int nodeTo, int pathFound[])
{
    // Parameter validation of course
    if (pTable == NULL || pathFound == NULL || nodeFrom < 0 || nodeFrom >= NUMBER_OF_VERTICES || nodeTo < 0 || nodeTo >= NUMBER_OF_VERTICES) {
        return INVALID_INPUT_PARAMETER;
    }

    // Make sure the target node is able to be reached by the algorithm 
    // or else it's invalid
    if (pTable->table[nodeTo].predecessor == -1 || pTable->table[nodeTo].distance == VERY_LARGE_NUMBER) {
        return INVALID_INPUT_PARAMETER;
    }

    // Set length of path to 0
    int pathLength = 0;
    // Set current node to the target node
    // to start from the target node
    int currentNode = nodeTo;

    // Go from target node back to the starting node
    // so looping until the current node = the starting node
    while (currentNode != nodeFrom) {
        // Add current node to path array
        pathFound[pathLength] = currentNode;
        pathLength++;
        // Set current node to predecessor node to go back
        currentNode = pTable->table[currentNode].predecessor;
    }

    // Almost forgot this, but must add the starting node to the path array
    pathFound[pathLength] = nodeFrom;
    pathLength++;

    return SUCCESS;
}


/**
 * This function should add a new edge into the AdjacencyList provided, based on 
 * a starting vertex (src), destination vertex (dest), and weight of the edge. 
 * 
 * The function should return SUCCESS or an error code. 
 * 
 * Remember to use myMalloc() to allocate memory instead of malloc(). 
 */
int addEdgeToAdjacencyList(AdjacencyList *pList, int src, int dest, int weight)
{
    // Input validation
    if (pList == NULL || src < 0 || src >= NUMBER_OF_VERTICES || dest < 0 || dest >= NUMBER_OF_VERTICES) {
        return INVALID_INPUT_PARAMETER;
    }

    // Create new list node
    ListNode* node;
    // Allocate memory for node
    node = (ListNode*)myMalloc(sizeof(ListNode));

    // Check if myMalloc worked
    if (node == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    // Set new node's destination node inputted target
    node->destNode = dest;
    // Set new node's weight to inputted weight
    node->weight = weight;
    // Set link to next node
    node->next = pList->adjacencyList[src];

    // Add the new node to the adjacency list
    pList->adjacencyList[src] = node;

    return SUCCESS;
}


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
 */
int populateAdjacencyList(AdjacencyList *pList, AdjacencyMatrix *pMatrix)
{
    // Input validation
    if (pMatrix == NULL || pList == NULL ) {
        return INVALID_INPUT_PARAMETER;
    }

    /*
        Same iteration through adjacency matrix as implemented in previous functions.

        Loop through rows and columns of the matrix, and for each column in a row
        check if there's an edge between loop index node and current node, if there is,
        create and allocate memory for a new list node, check if myMalloc worked, then
        just fill out the adjacency list with the new node details. 
    */

    for (int i = 0; i < NUMBER_OF_VERTICES; i++) {
        for (int j = 0; j < NUMBER_OF_VERTICES; j++) {
            if (pMatrix->matrix[i][j] != 0) {
                ListNode* node = (ListNode*)myMalloc(sizeof(ListNode));

                // If myMalloc doesn't work return memory allocation error
                if (node == NULL) {
                    return MEMORY_ALLOCATION_ERROR;
                }

                node->destNode = j;
                node->weight = pMatrix->matrix[i][j];
                node->next = pList->adjacencyList[i];

                pList->adjacencyList[i] = node;
            }
        }
    }

    return SUCCESS;
}

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
 * The function will receive a ready-made graph to work with, in the form of 
 * an AdjacencyList. It will also receive an empty DijkstraTable, ready to be 
 * populated. It will also receive the starting node on the graph to 
 * commence the algorithm from. This function should implement the algorithm, 
 * running it on the graph provided and updating the DijkstraTable with the 
 * outcome. After the function is called, the DijkstraTable will be inspected to 
 * determine whether the algorithm has been completed successfully. 
 * 
 * The function should return SUCCESS or an error code.
 */
int doDijsktraAlgorithmOnAdjacencyList(AdjacencyList *pList, DijkstraTable *pTable, int startNode)
{
    // void casts to prevent 'unused variable warning'
    // remove the following lines of code when you have 
    // implemented the function yourself
    (void)pList;
    (void)pTable;
    (void)startNode;

    // returning NOT_IMPLEMENTED until your own implementation provided
    return NOT_IMPLEMENTED;
}