#include<stdio.h>
#include<stdlib.h>
//A Structure to represent an adjacency List Node 
struct AdjListNode {
	int dest;int wt;
	struct AdjListNode* next;
};
//A Structure to represent an adjacency List 
struct AdjList {
	struct AdjListNode *head;  //head pointer to the nodes.
};
//A stucture to represent a Graph, where a graph is an array of adjacency lists.
//The Size of the array is equal to the no. of lists or the no of nodes.
struct Graph {
	int V;int wt;
	struct AdjList* array;
};
struct AdjListNode* newAdjListNode(int dest,int wt) {
	struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->wt = wt;
	newNode->next = NULL;
	
return newNode;
}
struct Graph* createGraph(int V) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;
	// Create an array of adjacency lists.  Size of array will be V
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
	// Initialize each adjacency list as empty by making head as NULL
	int i;
	for (i = 0; i < V; ++i)
	graph->array[i].head = NULL;
	return graph;
}
void addEdge(struct Graph* graph, int src, int dest,int wt)
{
// Add an edge from src to dest.  A new node is added to the adjacency
// list of src.  The node is added at the begining
	struct AdjListNode* newNode = newAdjListNode(dest, wt);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
// Since graph is undirected, add an edge from dest to src also
	newNode = newAdjListNode(src, wt);	
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
	graph->wt = wt;
	//printf(" %d\n",graph->wt);
}
// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph) {
	int v;
	for (v=0;v<graph->V;++v) {
		struct AdjListNode* pCrawl=graph->array[v].head;
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl) {
			printf("-> %d[%d]",pCrawl->dest, pCrawl->wt);
			pCrawl=pCrawl->next;
		}
		printf("\n");
	}
}
int main() {
	int V;

	/*char boardingpt[18], destination[18];
	char choice;
	int option;
	printf("Enter the boarding point\n");
	scanf("%c",boardingpt); 
	printf("Enter the Destination\n");
	//flushall();
	scanf("%c",destination); 
	printf("Choose The Mode of Trasportation\n");
	printf("1) By Railway\n2)BY Airways\n");
	scanf("%c",&choice);
	switch(choice) {
 		case 1 : 
			printf("You choose to travel by Railway\n");
			printf("choose your option of optimization\n 1)cost\t 2)time");
			scanf("%d",&option);
			switch(option) {
				//case 1 :
				//	break;
				//case 2:
					break;
		case 2:
			printf("You choose to travel by Airways\n");
			printf("choose your option of optimization\n 1)cost\t 2)time");
			scanf("%d",&option);
			switch(option) {
				//case 1 :
				//	break;
				//case 2:
					break;

 	}*/
	//building of graph-IMPORTANT PART
	V = 10;
	struct Graph* graph1 = createGraph(V);
	FILE *fair;
	int start, end, wt;
	fair = fopen("airroute.c","r");
	if(fair == NULL) {
		printf("unable to open the file");

	}else {
	
		while(1){

			//printf("%s\t%f\n", start, fare);
			fscanf(fair,"%d\t%d\t%d", &start, &end, &wt);
			if(feof(fair)) 
				break;
			printf("%d\t%d\t%d\n", start, end, wt);
			addEdge(graph1, start, end, wt);
		}

	}
	fclose(fair);
	printGraph(graph1);
//making another graph for rail routes
	printf("___________________________________________________\n");
	V = 6;
	struct Graph* graph2 = createGraph(V);
	FILE *frail;
	frail = fopen("railroute.c","r");
	if(frail == NULL) {
		printf("unable to open the file");

	}else {
	
		while(1){

			//printf("%s\t%f\n", start, fare);
			fscanf(frail,"%d\t%d\t%d", &start, &end, &wt);
			if(feof(frail)) 
				break;
			printf("%d\t%d\t%d\n", start, end, wt);
			addEdge(graph2, start, end, wt);
		}

	}
	fclose(frail);
	printGraph(graph2);
	//ShortestPath(AdjacencyList, 10, 1, 7);
	return 0;
}

// finding the shortest path algorithm

/*
typedef struct linktype {
	int link;
	int weight;
}Link;
typedef struct nodetype {
	int data;
	Link links[10];
}Node;
#define MAXVERTICES     10    
#define MAXLINKS        45 
#define Minimum(X,Y)    ((X) < (Y)) ? (X) : (Y)
enum StatusType {intree, fringe, unseen} StatusType;

// See the Code Vault for a full implementation of this algorithm

//-------------------------------------------
// ShortestPath()
//
// Find shortest path from node v to
//   node w using Dijkstra's shortest
//   path algorithm.
// Returns total number of units in shortest
//   path
//-------------------------------------------
int ShortestPath(Node AdjacencyList[], int n, int v, int w)
{
	// AdjacencyList -- adjacency list of nodes in graph
	// n -- number of nodes in the graph (6)
	// v -- number of the starting vertex (1..6)
	// w -- number of the destination vertex (1..6)
	int		MinDistance;
	int		ShortestDist[MAXVERTICES];
	int		W[MAXVERTICES];
	int		nextWIdx = 0;
	int		i;
	int		wNode;		// Index of node being considered
	int		tempIdx;	// Temporary use index
	StatusType	status[MAXVERTICES];

	// -------------------- INITIALIZATION SECTION -------------------- 
	for(i = 0; i < MAXVERTICES; i++)
	{
		W[i] = -1;                   // Init W to empty
		ShortestDist[i] = MAXINT;    // Init shortest dists to infinity
		status[i] = unseen;          // Init all nodes to unseen
	}
	// ------------------------ SETUP SECTION -------------------------
	W[nextWIdx] = v;         // Add first node to W 
	nextWIdx++;              // Increment index into W
	ShortestDist[v-1] = 0;   // Set shortest dist from v to v
	status[v-1] = intree;    // Set status of v in W

	for(i = 0; i < MAXLINKS; i++)
	{
		ShortestDist[AdjacencyList[v-1].links[i].link - 1] =
			AdjacencyList[v-1].links[i].weight;
		status[AdjacencyList[v-1].links[i].link - 1] = fringe;
	// enlarge W until it includes all vertices in the graph (multiple times)
	while(nextWIdx < MAXVERTICES)
	{
		// Find the vertex n in V - W at the minimum distance from v
		MinDistance = MAXINT;
		for(i = 0; i < MAXVERTICES; i++)
		{
			if(status[i] == fringe)
			{
				if(ShortestDist[i] < MinDistance)
				{
					MinDistance = ShortestDist[i];
					wNode = i + 1;	// Convert index to node number
				}
			}
		}

		// Add w to W
		W[nextWIdx] = wNode;
		status[wNode - 1] = intree;
		nextWIdx++;

		// Update the shortest distances to vertices in V - W
		for(i = 0; i < MAXLINKS; i++)
		{
			tempIdx = AdjacencyList[wNode -1].links[i].link - 1;
			ShortestDist[tempIdx] = Minimum(ShortestDist[tempIdx],
				ShortestDist[wNode - 1] + AdjacencyList[wNode - 1].links[i].weight);
			status[tempIdx] = fringe;
		}
	} // End while
	return(ShortestDist[w - 1]);
}
*/
