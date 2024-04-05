/**
 * FILE: BASIC_TESTER.C
 *
 * Can be used to run some tests for the GRAPHS program.
 * This file can be compiled alongside your own file (graphs.c)
 * and it will automatically call and make use of the functions that 
 * you have implemented and which are contained within your
 * graphs.c file.
 *
 * YOU CAN MODIFY THIS FILE IF YOU WISH, E.G. CHANGE OUTPUT MESSAGES
 * OR TO ADD NEW TESTS, ETC. 
 *
 * YOU WON'T BE SUBMITTING THIS FILE TO MY DUNDEE.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

/**
 * A helper function, to display the contents of an adjacency matrix
 * for debugging purposes. The implementation for this is further 
 * below, under main()
 */
void displayMatrix(AdjacencyMatrix *pMatrix);

/**
 * A helper function, to fill up the contents of an adjacency matrix to 0
 */
void fillUpMatrixWithEmptyValues(AdjacencyMatrix *pMatrix);

/**
 * A helper function, to fill up the contents of an adjacency matrix 
 * with specific edges in it, to correspond to a sample graph to 
 * work with for the Dijkstra algorithm
 */
void fillUpMatrixWithDijkstraExampleGraph1(AdjacencyMatrix *pMatrix);

/**
 * A helper function, to display the contents of a dijkstra table
 * for debugging purposes. The implementation for this is further 
 * below, under main()
 */
void displayDijkstraTable(DijkstraTable *pTable);

/**
 * A helper function, to fill up the contents of an adjacency matrix 
 * with specific edges in it, to correspond to a sample graph to 
 * work with for the Dijkstra algorithm
 */
void fillUpMatrixWithDijkstraExampleGraph2(AdjacencyMatrix *pMatrix);

/**
 * A helper function, to display the contents of a path
 * found from a starting node (nodeFrom) to an ending 
 * node (nodeTo) in a graph
 */
void displayPathFound(int nodeFrom, int nodeTo, int pathFound[]);

/**
 * Helper function. Initialise the content of given AdjacencyList
 * to be empty.
 */
void initialiseAdjListToEmpty(AdjacencyList *pList);

/**
 * A helper function, to display the contents of an adjacency list
 * for debugging purposes.
 */
void displayAdjacencyList(AdjacencyList *pList);

/**
 * Helper function to free the content of an Adjacency List
 */
void freeAdjacencyList(AdjacencyList *pList);

/**
 * Implementation of the 'myMalloc' function. Required so that any
 * references to myMalloc within *YOUR* code will be resolved. 
 * Please leave this function here. You don't need to copy or 
 * place it anywhere else.
 */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

/**
 * The main function. Run some basic tests on the playlist.
 */
int main()
{
	printf("## BASIC TESTER FOR GRAPHS PROGRAM\n\n");

	// some test variables that may be useful later
	AdjacencyMatrix adjacencyMatrix;

	// ## Test creating an adjacency matrix with a default edge value of 0, and displaying its content
	printf("TEST: Creating an AdjacencyMatrix:\n");
	AdjacencyMatrix *pMatrix = createAdjacencyMatrix(0);
	if (pMatrix != NULL)
	{
		// display the matrix
		displayMatrix(pMatrix);

		// free the memory allocated, unless it is needed for anything else first
		free(pMatrix);
	}

	// ## Test adding some edges to an existing adjacency matrix
	printf("TEST: Adding edges to an AdjacencyMatrix with addEdge():\n"); 
    fillUpMatrixWithEmptyValues(&adjacencyMatrix);
    addEdge(&adjacencyMatrix, 0, 2, 8);
    addEdge(&adjacencyMatrix, 3, 5, 2);
    addEdge(&adjacencyMatrix, 7, 5, 1);
    addEdge(&adjacencyMatrix, 7, 6, 7);
    displayMatrix(&adjacencyMatrix);

    // ## Test adding some edges to an existing adjacency matrix - version 2
	printf("TEST: Adding an array of edges to an AdjacencyMatrix with addEdges():\n");
    fillUpMatrixWithEmptyValues(&adjacencyMatrix);
    Edge edges[5] = { {0, 1, 2}, {1, 2, 3}, {2, 3, 4}, {3, 4, 5}, {4, 5, 6} };
    addEdges(&adjacencyMatrix, edges, 5);
    displayMatrix(&adjacencyMatrix);

    // ## Test reading an adjacency matrix from a file
    // See FileExample1 for what graph and matrix look like
	printf("TEST: Reading the content of an adjacency matrix in from a file:\n");
    fillUpMatrixWithEmptyValues(&adjacencyMatrix);
    loadMatrixFromFile(&adjacencyMatrix, "adjacency_matrix.txt");
    displayMatrix(&adjacencyMatrix);

    // ## Test running Dijsktra's algorithm
    DijkstraTable dijkstraTable;
	printf("TEST: Running Dijkstra's Algorithm on Example Graph 1:\n");
    fillUpMatrixWithDijkstraExampleGraph1(&adjacencyMatrix);
    doDijsktraAlgorithm(&adjacencyMatrix, &dijkstraTable, 3);
    displayDijkstraTable(&dijkstraTable);

    // find shortest path in graph
	printf("TEST: Displaying a shortest path from the Dijkstra result above:\n");
    int pathFound[NUMBER_OF_VERTICES];
    for (int i=0; i<NUMBER_OF_VERTICES; i++)
    	pathFound[i] = -1;
    int nodeFrom= 3;
    int nodeTo = 1;
    findShortestPathTo(&dijkstraTable, nodeFrom, nodeTo, pathFound);
    displayPathFound(nodeFrom, nodeTo, pathFound);

    // ## Test running Dijsktra's algorithm again
	printf("TEST: Running Dijkstra's Algorithm on Example Graph 2:\n");
    fillUpMatrixWithDijkstraExampleGraph2(&adjacencyMatrix);
    doDijsktraAlgorithm(&adjacencyMatrix, &dijkstraTable, 0);
    displayDijkstraTable(&dijkstraTable);

    // find shortest path in graph
	printf("TEST: Displaying a shortest path from the Dijkstra result above:\n");
    for (int i=0; i<NUMBER_OF_VERTICES; i++)
    	pathFound[i] = -1;
    nodeFrom= 0;
    nodeTo = 4;
    findShortestPathTo(&dijkstraTable, nodeFrom, nodeTo, pathFound);
    displayPathFound(nodeFrom, nodeTo, pathFound);

    // ## Test adding edges to an AdjacencyList
	printf("TEST: Adding edges to an AdjacencyList using 'addEdgeToAdjacencyList()' :\n");
    AdjacencyList adjList;
    initialiseAdjListToEmpty(&adjList);
    addEdgeToAdjacencyList(&adjList, 2, 3, 8);
    addEdgeToAdjacencyList(&adjList, 5, 1, 3);
    addEdgeToAdjacencyList(&adjList, 2, 6, 5);
    addEdgeToAdjacencyList(&adjList, 0, 2, 6);
    displayAdjacencyList(&adjList);
    freeAdjacencyList(&adjList);

    // ## Test populating an adjacency list from the content
    // of a corresponding adjacency matrix - example 1
	printf("TEST: Populating an AdjacencyList from an AdjacencyMatrix - Example 1:\n");
    AdjacencyList adjList2;
    initialiseAdjListToEmpty(&adjList2);    
    fillUpMatrixWithDijkstraExampleGraph1(&adjacencyMatrix);
    populateAdjacencyList(&adjList2, &adjacencyMatrix);
    displayAdjacencyList(&adjList2);
    freeAdjacencyList(&adjList2);

    // ## Test populating an adjacency list from the content
    // of a corresponding adjacency matrix - example 2
	printf("TEST: Populating an AdjacencyList from an AdjacencyMatrix - Example 2:\n");
    AdjacencyList adjList3;
    initialiseAdjListToEmpty(&adjList3);    
    fillUpMatrixWithDijkstraExampleGraph2(&adjacencyMatrix);
    populateAdjacencyList(&adjList3, &adjacencyMatrix);
    displayAdjacencyList(&adjList3);
    freeAdjacencyList(&adjList3);

    // ## Test running Dijsktra's algorithm but using the
    // adjacency list to work with instead of the adjacency
    // matrix
	printf("TEST: Running Dijkstra's Algorithm using an AdjacencyList - Example Graph 2:\n");
    AdjacencyList adjList4;
    initialiseAdjListToEmpty(&adjList4);    
    fillUpMatrixWithDijkstraExampleGraph2(&adjacencyMatrix);
    populateAdjacencyList(&adjList4, &adjacencyMatrix);
    doDijsktraAlgorithmOnAdjacencyList(&adjList4, &dijkstraTable, 0);
    displayDijkstraTable(&dijkstraTable);
    freeAdjacencyList(&adjList4);

    // find shortest path in graph
	printf("TEST: Displaying a shortest path from the Dijkstra result above:\n");
    for (int i=0; i<NUMBER_OF_VERTICES; i++)
    	pathFound[i] = -1;
    nodeFrom= 0;
    nodeTo = 4;
    findShortestPathTo(&dijkstraTable, nodeFrom, nodeTo, pathFound);
    displayPathFound(nodeFrom, nodeTo, pathFound);
}

/**
 * A helper function, to display the contents of an adjacency matrix
 * for debugging purposes.
 */
void displayMatrix(AdjacencyMatrix *pMatrix)
{
	printf("DISPLAYING ADJACENCY MATRIX:\n");
    for (int i=0; i<NUMBER_OF_VERTICES; i++)
    {
    	for (int j=0; j<NUMBER_OF_VERTICES; j++)
    	{
    		printf("[%d] ", pMatrix->matrix[i][j]);
    	}
    	printf("\n");
    }
    printf("\n");
}

/**
 * A helper function, to fill up the contents of an adjacency matrix to 0
 */
void fillUpMatrixWithEmptyValues(AdjacencyMatrix *pMatrix)
{
	for (int i=0; i<NUMBER_OF_VERTICES; i++)
    {
    	for (int j=0; j<NUMBER_OF_VERTICES; j++)
    	{
    		pMatrix->matrix[i][j] = 0;
    	}
    }
}

/**
* A helper function, to fill up the contents of an adjacency matrix 
 * with specific edges in it, to correspond to a sample graph to 
 * work with for the Dijkstra algorithm
 */
void fillUpMatrixWithDijkstraExampleGraph1(AdjacencyMatrix *pMatrix)
{
	// initialise matrix to zero first
	fillUpMatrixWithEmptyValues(pMatrix);

	// now, create a graph
	// see 'dijkstra graph example 1' for a
	// a visual presentation of the graph
	// that this matrix will correspond to,
	// and the resultant dijkstra table
	// that would be expected from it too
	pMatrix->matrix[0][1] = 7;
	pMatrix->matrix[0][3] = 2;
	pMatrix->matrix[1][0] = 7;
	pMatrix->matrix[1][2] = 4;
	pMatrix->matrix[1][3] = 8;
	pMatrix->matrix[2][1] = 4;
	pMatrix->matrix[2][3] = 1;
	pMatrix->matrix[3][0] = 2;
	pMatrix->matrix[3][1] = 8;
	pMatrix->matrix[3][2] = 1;
}

/**
* A helper function, to fill up the contents of an adjacency matrix 
 * with specific edges in it, to correspond to a sample graph to 
 * work with for the Dijkstra algorithm
 */
void fillUpMatrixWithDijkstraExampleGraph2(AdjacencyMatrix *pMatrix)
{
	// initialise matrix to zero first
	fillUpMatrixWithEmptyValues(pMatrix);

	// now, create a graph
	// see 'dijkstra graph example 2' for a
	// a visual presentation of the graph
	// that this matrix will correspond to,
	// and the resultant dijkstra table
	// that would be expected from it too
	pMatrix->matrix[0][1] = 10;
	pMatrix->matrix[0][2] = 15;
	pMatrix->matrix[1][3] = 12;
	pMatrix->matrix[1][5] = 15;
	pMatrix->matrix[2][4] = 10;
	pMatrix->matrix[3][5] = 1;
	pMatrix->matrix[3][4] = 2;
	pMatrix->matrix[5][4] = 5;
}

/**
 * A helper function, to display the contents of a dijkstra table
 * for debugging purposes. 
 */
void displayDijkstraTable(DijkstraTable *pTable)
{
	printf("DISPLAYING DIJKSTRA TABLE:\n");
	printf("Node\tDist\tPred\n");
    for (int i=0; i<NUMBER_OF_VERTICES; i++)
    {
    	printf("%d\t%d\t%d\n", i, pTable->table[i].distance, pTable->table[i].predecessor);
    }
    printf("\n");
}

/**
 * A helper function, to display the contents of a path
 * found from a starting node (nodeFrom) to an ending 
 * node (nodeTo) in a graph
 */
void displayPathFound(int nodeFrom, int nodeTo, int pathFound[])
{
	printf("DISPLAYING SHORTEST PATH FROM NODE %d to NODE %d:\n", nodeFrom, nodeTo);
	for (int i=NUMBER_OF_VERTICES-1; i>=0; i--)
	{
		if (pathFound[i] != -1)
		{
			printf("%d", pathFound[i]);
			if (i > 0)
				printf(" -> ");
		}
	}
    printf("\n");
    printf("\n");
}


/**
 * Helper function. Initialise the content of given AdjacencyList
 * to be empty.
 */
void initialiseAdjListToEmpty(AdjacencyList *pList)
{
	for (int i=0; i<NUMBER_OF_VERTICES; i++)
		pList->adjacencyList[i] = NULL;
}

/**
 * A helper function, to display the contents of an adjacency list
 * for debugging purposes.
 */
void displayAdjacencyList(AdjacencyList *pList)
{
	printf("DISPLAYING ADJACENCY LIST [node(weight)]:\n");
	ListNode *pNextNode;
	for (int i=0; i<NUMBER_OF_VERTICES; i++)
	{
		printf("[%d]", i);
		pNextNode = pList->adjacencyList[i];
		while (pNextNode != NULL)
		{
			printf(" -> [%d(%d)]", pNextNode->destNode, pNextNode->weight);
			pNextNode = pNextNode->next;
		}
    	printf("\n");
    }
    printf("\n");
}


/**
 * Helper function to free the content of an Adjacency List
 */
void freeAdjacencyList(AdjacencyList *pList)
{
	ListNode *pNextNode;
	for (int i=0; i<NUMBER_OF_VERTICES; i++)
	{
		pNextNode = pList->adjacencyList[i];
		while (pNextNode != NULL)
		{
			ListNode *nodeToDelete = pNextNode;
			pNextNode = pNextNode->next;
			free(nodeToDelete);
		}
    }	
}
