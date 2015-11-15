/********************************************************
# Copyright (C) 2012, 2013 __MIS 111408062__
# The Application __ FARE ESTIMATOR__.
#
# __TRANSPORTATION FARE CALCULATOR__ is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# __TRANSPORTATION FARE CALCULATOR__ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
********************************************************/

/********************************************************
		MINI PROJECT
	       FARE CALCULATOR
	    (USING GRAPH THEORY)

********************************************************/


/*******************************************************
INCLUDED HEADER FILES
*******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define true 1
#define false 0 
char s[28];  /*character array to store the starting point*/
char d[28];  /*character array to store the destination point*/
int cityno1;
int cityno2;  
int cost_unit;	
/*******************************************************
STRUCTURE NAME: AdjListNode
DETAIL: A structure to represent a node in adjacency list

*******************************************************/

struct AdjListNode {
	int dest;
	int weight;
	struct AdjListNode* next;

};
 
/*******************************************************
STRUCTURE NAME: AdjListNode
DETAIL: A structure to represent an adjacency liat

*******************************************************/

struct AdjList {
	struct AdjListNode *head;  /* pointer to head node of list */

};

/*******************************************************
STRUCTURE NAME: Graph
DETAIL: A structure to represent a graph.A graph is an array of adjacency list.
        Size of array will be V (number of vertices in graph) 

*******************************************************/

struct Graph {	
	int V;
	struct AdjList* array;

};
 
/*******************************************************
FUNCTION NAME: newAdjListNode()
DETAIL: A utility function to create a new adjacency list node

*******************************************************/

struct AdjListNode* newAdjListNode(int dest, int weight) {    
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;

}

/*******************************************************
FUNCTION NAME: newAdjListNode()
DETAIL:  A utility function that creates a graph of V vertices

*******************************************************/

struct Graph* createGraph(int V) {
	int i;
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
	graph->V = V;
 
/* Create an array of adjacency lists.Size of array will be V*/
	graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
/* Initializing each adjacency list as empty by making head as NULL*/
	for (i = 0; i < V; ++i)
        	graph->array[i].head = NULL;
	return graph;

}

/*******************************************************
FUNCTION NAME: addEdge()
DETAIL:  A utility functon that adds an edge to an undirected graph

******************************************************/

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
/* Adding an edge from src to dest.  A new node is added to the adjacency
 list of src.  The node is added at the begining */
	struct AdjListNode* newNode = newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
 
/* Since graph is undirected, add an edge from dest to src also*/
	newNode = newAdjListNode(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

/***************************************************
SRUCTURE NAME: MinHeapNode
DETAIL:  Structure to represent a min heap node

****************************************************/

struct MinHeapNode {
	int  v;
	int dist;

};

/************************************************
STRUCTURE NAME: MinHeap
DETAIL: Structure to represent a minHeap

************************************************/ 

struct MinHeap {
	int size;         /* Number of heap nodes present currently*/
	int capacity;     /* Capacity of min heap*/
	int *pos;         /* This is needed for decreaseKey()*/
	struct MinHeapNode **array;
};

/************************************************
FUNCTION NAME: newMeanHeapNode()
DETAIL: A utility function to create a new Min Heap Node

************************************************/

struct MinHeapNode* newMinHeapNode(int v, int dist) {
	struct MinHeapNode* minHeapNode = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;

}

/*************************************************
FUNCTION NAME: createMeanHeap()
DETAIL: A utility function to create a new Min Heap 

*************************************************/

struct MinHeap* createMinHeap(int capacity) {
	struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
	minHeap->pos = (int *)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;    
	minHeap->array =(struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
	return minHeap;

}

/*************************************************
FUNCTION NAME: swapMeanHeapNode()
DETAIL: A utility function to swap two nodes of min heap.
        Needed for min heapify 

*************************************************/
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

/***********************************************************
FUNCTION NAME: minHeapify()
DETAIL:  A stadard function to heapify at given idx
         This function also updates position of nodes when they are swapped.
         Position is needed for decreaseKey()

************************************************************/

void minHeapify(struct MinHeap* minHeap, int idx) {
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;
 	if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist )
		smallest = left;
	if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist )
		smallest = right;
	if (smallest != idx) {
        /* The nodes to be swapped in min heap*/
        	struct MinHeapNode *smallestNode = minHeap->array[smallest];
        	struct MinHeapNode *idxNode = minHeap->array[idx];
		/* Swaping positions*/
        	minHeap->pos[smallestNode->v] = idx;
        	minHeap->pos[idxNode->v] = smallest;
		/* Swap nodes*/
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}

}
 
/***********************************************************
FUNCTION NAME: isEmpty()
DETAIL:  A utility function to check if the given minHeap is ampty or not

************************************************************/

int isEmpty(struct MinHeap* minHeap) {
	return minHeap->size == 0;

}
 
/***********************************************************
FUNCTION NAME: MinHeapNode()
DETAIL:  Standard function to extract minimum node from heap

************************************************************/

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
	if (isEmpty(minHeap))
		return NULL;
	/* Storeing the root node*/
	struct MinHeapNode* root = minHeap->array[0];
	/* Replace root node with last node*/
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;
	/* Updating position of last node*/
	minHeap->pos[root->v] = minHeap->size-1;
	minHeap->pos[lastNode->v] = 0; 
	/* Reduce heap size and heapify root*/
	--minHeap->size;
	minHeapify(minHeap, 0);
	return root;

}
/***********************************************************
FUNCTION NAME: decreaseKey()
DETAIL:  Function to decreasy dist value of a given vertex v. This function
         uses pos[] of min heap to get the current index of node in min heap

************************************************************/ 

void decreaseKey(struct MinHeap* minHeap, int v, int dist) {
	/* Get the index of v in  heap array*/
	int i = minHeap->pos[v];
 	/* Get the node and update its dist value*/
	minHeap->array[i]->dist = dist;
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
		swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
		i = (i - 1) / 2;
	}

}
 
/***********************************************************
FUNCTION NAME:isminHeap()
DETAILS: A utility function to check if a given vertex
        'v' is in min heap or not

**********************************************************/

int isInMinHeap(struct MinHeap *minHeap, int v) {
	if (minHeap->pos[v] < minHeap->size)
		return true;
	return false;

}
/**********************************************************
FUNCTION NAME:printaArr()
DETAILS: A utility function used to print the solution

**********************************************************/
 
void printArr(int dist[], int n) {
	int i = 1;
	while(1) {
		if(i == n) {
			if(dist[i] == 0) {
				printf("OopS..!\n");
				printf("TRAVEL TO THE DESTINATION BY THIS MODE IS ");
				printf("NOT AVAILABLE.\n");
				printf("YOU MIGHT WANT TO TRY OTHER MODES OF TRANSPORT");
				cost_unit = 0;
			}else {	        	
				printf("________________________________________________\n");
				printf("THE SHORTEST DISTANCE TO BE TRAVELLED\n");
				printf("FROM : %s", s);
				printf("\nTO : %s", d);
				printf(" \tis\t%d km\n", dist[i]);
				cost_unit = dist[i];
				break;
			}
		}
		i++;
	}

}

/**********************************************************
FUNCTION NAME : dijkstra()
DETAIL: The main function that calulates distances of shortest paths from src to all vertices.
        It is a O(ELogV) function

********************************************************/

void dijkstra(struct Graph* graph, int src,int des)
{
	int v;
	int V = graph->V; 
	int dist[V];      
	struct MinHeap* minHeap = createMinHeap(V);
	/* Initialize min heap with all vertices. dist value of all vertices*/
	for (v = 0; v < V; ++v) {
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, dist[v]);
		minHeap->pos[v] = v;
	}
 
	/* Makeing dist value of src vertex as 0 so that it is extracted first*/
	minHeap->array[src] = newMinHeapNode(src, dist[src]);
	minHeap->pos[src]   = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);
	minHeap->size = V;
	while (!isEmpty(minHeap)) {
		/* Extract the vertex with minimum distance value*/
		struct MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v; 
 		/* Traverse through all adjacent vertices of u (the extracted vertex) and update their distance values*/
		struct AdjListNode* pCrawl = graph->array[u].head;
		while (pCrawl != NULL) {
			int v = pCrawl->dest;
			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v]) {
				dist[v] = dist[u] + pCrawl->weight;
 				/* update distance value in min heap also*/
				decreaseKey(minHeap, v, dist[v]);
			}
		pCrawl = pCrawl->next;
		}
	}
	printArr(dist, des);

}

/*******************************************************
FUNCTION NAME: printgraph()
DETAIL: A utility function to print the adjacency list or say graph

*******************************************************/ 

void printGraph(struct Graph* graph) {
	int v;
	for (v=0;v<graph->V;++v) {
		struct AdjListNode* pCrawl=graph->array[v].head;
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl) {
			printf("-> %d[%d]",pCrawl->dest, pCrawl->weight);
			pCrawl=pCrawl->next;
		}
		printf("\n");
	}
}

/*******************************************************
FUNCTION NAME: city_no_from_file()
DETAIL: A utility function to give the corrosponding integer of a city from a file.

*******************************************************/ 

int city_no_from_file(char *s) {   
	char c[28];
	int counter =0;
	FILE *fptr;
   	if ((fptr=fopen("cities.txt","r"))==NULL) {
		printf("Error! opening file");
		exit(1);         
	}
	while(1) {
		fscanf(fptr,"%s",c);counter++;
		if(strcmp(c,s) == 0)
			return counter;
		else if(feof(fptr)) {
			return 0;
		}
	}
   	fclose(fptr);

}
/*******************************************************
FUNCTION NAME: totalROADcost()
DETAIL: The function to calculate the Expenses by Road travel

*******************************************************/ 

int totalROADcost(int unit) {
	float cost, avg;
	printf("Enter the average km/lt of the vehicle\n");
	scanf("%f",&avg);
	cost = (unit/avg)*76.6;
	/* a formula to calculate cost of the travel*/
	printf("THE APPROXIMATE AMOUNT IS: %f", cost);
	return ;

}
/*******************************************************
FUNCTION NAME: totalRAILcost()
DETAIL: The function to calculate the expenses, when travelling through Railways

*******************************************************/ 

int totalRAILcost(int unit) {
	float cost;
	//printf("Enter the average km/lt of the vehicle\n");
	//scanf("%f",&avg);
	cost = (unit/8)*12.5;
	/* a formula to calculate cost of the travel*/
	printf("THE APPROXIMATE AMOUNT IS: %f", cost);
	return;

}
/*******************************************************
FUNCTION NAME: totalAIRcost()
DETAIL: The function which calculates the expenses by air travel.

*******************************************************/ 

int totalAIRcost(int unit) {
	float cost;
	//printf("Enter the average km/lt of the vehicle\n");
	//canf("%f",&avg);
	cost = (unit*20);
	/* a formula to calculate cost of the travel*/
	printf("THE APPROXIMATE AMOUNT IS: %f", cost);
	return;

}
/*******************************************************
FUNCTION NAME: totalWATERcost()
DETAIL: The function which calculates the expenses by water travel.

*******************************************************/ 

int totalWATERcost(int unit) {
	float cost;
	//printf("Enter the average km/lt of the vehicle\n");
	//canf("%f",&avg);
	cost = (unit*15);
	/* a formula to calculate cost of the travel*/
	printf("THE APPROXIMATE AMOUNT IS: %f", cost);
	return;

}
int check_if_air_exist(int node) {
	FILE *fair;
	int start,end,wt;
	fair = fopen("airroute.c","r");
	if(fair== NULL) {
		printf("unable to open the file");

	}else {
		while(1){
			fscanf(fair,"%d\t%d\t%d", &start, &end, &wt);
			if(start == node) 
				return 1;
			else if(feof(fair)) { 
				printf("OopS..!\n");
				printf("TRAVEL TO THE DESTINATION BY THIS MODE IS ");
				printf("NOT AVAILABLE.\n");
				printf("YOU MIGHT WANT TO TRY OTHER MODES OF TRANSPORT");
				cost_unit = 0;
				return 0;
			}
		}

	}
	fclose(fair);
}
int check_if_rail_exist(int node) {
	FILE *frail;
	int start,end,wt;
	frail = fopen("railroute.c","r");
	if(frail == NULL) {
		printf("unable to open the file");

	}else {
		while(1){
			fscanf(frail,"%d\t%d\t%d", &start, &end, &wt);
			if(start == node) 
				return 1;
			else if(feof(frail)) { 
				printf("OopS..!\n");
				printf("TRAVEL TO THE DESTINATION BY THIS MODE IS ");
				printf("NOT AVAILABLE.\n");
				printf("YOU MIGHT WANT TO TRY OTHER MODES OF TRANSPORT");
				cost_unit = 0;
				return 0;
			}
		}

	}
	fclose(frail);
}

int check_if_road_exist(int node) {
	FILE *froad;
	int start,end,wt;
	froad= fopen("roadroute.c","r");
	if(froad == NULL) {
		printf("unable to open the file");

	}else {
		while(1){
			fscanf(froad,"%d\t%d\t%d", &start, &end, &wt);
			if(start == node) 
				return 1;
			else if(feof(froad)) { 
				printf("OopS..!\n");
				printf("TRAVEL TO THE DESTINATION BY THIS MODE IS ");
				printf("NOT AVAILABLE.\n");
				printf("YOU MIGHT WANT TO TRY OTHER MODES OF TRANSPORT");
				cost_unit = 0;
				return 0;
			}
		}

	}
	fclose(froad);
}

int check_if_water_exist(int node) {
	FILE *fwater;
	int start,end,wt;
	fwater= fopen("waterroute.c","r");
	if(fwater== NULL) {
		printf("unable to open the file");

	}else {
		while(1){
			fscanf(fwater,"%d\t%d\t%d", &start, &end, &wt);
			if(start == node) 
				return 1;
			else if(feof(fwater)) { 
				printf("OopS..!\n");
				printf("TRAVEL TO THE DESTINATION BY THIS MODE IS ");
				printf("NOT AVAILABLE.\n");
				printf("YOU MIGHT WANT TO TRY OTHER MODES OF TRANSPORT");
				cost_unit = 0;
				return 0;
			}		
		}

	}
	fclose(fwater);
}
/*******************************************************
FUNCTION NAME: main()
DETAIL: The most important function which gives a call to other function when required

*******************************************************/ 

int main() {
	/*declaration of the variable*/
	int choice, cityno1, cityno2;
	int V, start, end, wt;

	/*Forming 1st graph*/
	V = 231;
	struct Graph* graph1 = createGraph(V);
	FILE *fair;
	fair = fopen("airroute.c","r");
	if(fair == NULL) {
		printf("unable to open the file");
	}else {
		while(1){
			fscanf(fair,"%d\t%d\t%d", &start, &end, &wt);
			if(feof(fair)) 
				break;
			//printf("%d\t%d\t%d\n", start, end, wt);
			addEdge(graph1, start, end, wt);
			}
	
		}
		fclose(fair);

	/*making another graph for rail routes*/
	V = 197;
	struct Graph* graph2 = createGraph(V);
	FILE *frail;
	frail = fopen("railroute.c","r");
	if(frail == NULL) {
		printf("unable to open the file");

	}else {
		while(1){
			fscanf(frail,"%d\t%d\t%d", &start, &end, &wt);
			if(feof(frail)) 
				break;
			addEdge(graph2, start, end, wt);
		}

	}
	fclose(frail);

	/*Making of the 3rd graph for road routes*/
	V = 260;
	struct Graph* graph3 = createGraph(V);
	FILE *froad;
	froad = fopen("roadroute.c","r");
	if(froad == NULL) {
		printf("unable to open the file");

	}else {
	
		while(1){
			fscanf(froad,"%d\t%d\t%d", &start, &end, &wt);
			if(feof(froad)) 
				break;
			addEdge(graph3, start, end, wt);
		}

	}
	fclose(froad);
	/*Making of the 4Tth graph for road routes*/
	V = 21;
	struct Graph* graph4 = createGraph(V);
	FILE *fwater;
	fwater = fopen("waterroute.c","r");
	if(fwater == NULL) {
		printf("unable to open the file");

	}else {
	
		while(1){
			fscanf(fwater,"%d\t%d\t%d", &start, &end, &wt);
			if(feof(fwater)) 
				break;
			addEdge(graph4, start, end, wt);
		}

	}
	fclose(fwater);
	/*welcome screen*/
	printf("__________________________WELCOME_____________________________\n");
	printf("\t\t\tLET US MAKE UR TRAVEL EASY\n\n");
	printf("SELECT THE MODE OF TRANSPORTATION\n");
	printf("1)BY AIR\n2)BY RAIL\n3)BY ROADWAY\n4)WATERWAY\n");
	scanf("%d",&choice);	
	switch(choice) {
			case 1:
				printf("_________FLIGHT DETAILS__________\n");
				printf("PLZ ENTER THE NAME OF THE CITY ,WHERE YOUR JOURNEY BEGINS :");
				scanf("%s",s);
				printf("PLZ ENTER THE NAME OF THE CITY ,WHERE YOUR JOURNEY ENDS :");
				scanf("%s",d);
				cityno1 = city_no_from_file(s);
				cityno2 = city_no_from_file(d);
				if(cityno1 == 0 ) {
					printf("OopS..!!\n");
					printf("%s CITY IS NOT IN RECORDS\n",s);
					printf("RUN THE APLLICATION AGAIN AND ENTER ANOTHER NEAREST STATION\n");
					break;
				}else if (cityno2 ==0) {
					printf("OopS..!!\n");
					printf("%s CITY IS NOT IN RECORDS\n",d);
					printf("RUN THE APLLICATION AGAIN AND ENTER ANOTHER NEAREST STATION\n");
					break;
				}else
				dijkstra(graph1, cityno1, cityno2);
				break;
			case 2:
				printf("__________RAILWAY DETAILS__________\n");
				printf("PLZ ENTER THE NAME OF THE CITY ,WHERE YOUR JOURNEY BEGINS :");
				scanf("%s",s);
				printf("PLZ ENTER THE NAME OF THE CITY ,WHERE YOUR JOURNEY ENDS :");
				scanf("%s",d);
				cityno1 = city_no_from_file(s);
				cityno2 = city_no_from_file(d);
				if(cityno1 == 0 ) {
					printf("OopS..!!\n");
					printf("%s CITY IS NOT IN RECORDS\n",s);
					printf("RUN THE APLLICATION AGAIN AND ENTER ANOTHER NEAREST STATION\n");
					break;
				}else if (cityno2 ==0) {
					printf("OopS..!!\n");
					printf("%s CITY IS NOT IN RECORDS\n",d);
					printf("RUN THE APLLICATION AGAIN AND ENTER ANOTHER NEAREST STATION\n");
					break;
				}else if (check_if_rail_exist(cityno1)); {
				dijkstra(graph2, cityno1,cityno2);
				}
				break;
			case 3:
				printf("__________ROADWAY DETAILS__________\n");
				printf("PLZ ENTER THE NAME OF THE CITY ,WHERE YOUR JOURNEY BEGINS :");
				scanf("%s",s);
				printf("PLZ ENTER THE NAME OF THE CITY ,WHERE YOUR JOURNEY ENDS :");
				scanf("%s",d);
				cityno1 = city_no_from_file(s);
				cityno2 = city_no_from_file(d);
				if(cityno1 == 0 ) {
					printf("OopS..!!\n");
					printf("%s CITY IS NOT IN RECORDS\n",s);
					printf("RUN THE APLLICATION AGAIN AND ENTER ANOTHER NEAREST STATION\n");
					break;
				}else if (cityno2 ==0) {
					printf("OopS..!!\n");
					printf("%s CITY IS NOT IN RECORDS\n",d);
					printf("RUN THE APLLICATION AGAIN AND ENTER ANOTHER NEAREST STATION\n");
					break;
				}else if (check_if_rail_exist(cityno1)); {
				dijkstra(graph3, cityno1,cityno2);
				}
				break;
			case 4:
				printf("__________WATERWAY DETAILS__________\n");
				printf(" ENTER THE NAME OF THE HARBOUR CITY ,WHERE YOUR JOURNEY BEGINS :");
				scanf("%s",s);
				printf(" ENTER THE NAME OF THE HARBOUR CITY ,WHERE YOUR JOURNEY ENDS :");
				scanf("%s",d);
				cityno1 = city_no_from_file(s);
				cityno2 = city_no_from_file(d);
				if(cityno1 == 0 ) {
					printf("OopS..!!\n");
					printf("%s CITY IS NOT IN RECORDS\n",s);
					printf("RUN THE APLLICATION AGAIN AND ENTER ANOTHER NEAREST STATION\n");
					break;
				}else if (cityno2 ==0) {
					printf("OopS..!!\n");
					printf("%s CITY IS NOT IN RECORDS\n",d);
					printf("RUN THE APLLICATION AGAIN AND ENTER ANOTHER NEAREST STATION\n");
					break;
				}else if (check_if_water_exist(cityno1))
					dijkstra(graph4, cityno1,cityno2);
				break;
			default: 
				printf("WRONG CHOICE");
				printf("PLEASE RUN THE PROGRAM AGAIN AND ENTER CORRECTLY");
	
		}
	printf("____________________________________________________");
	while(1) {
		if(choice == 1) { 
			if(cityno1 == 0) 
				break;
			else if( cityno2 == 0)
				break;
			else {
				printf("\nLETS SEE THE EXPENSES :\n");
				printf("YOU CHOOSE TO TRAVEL BY PLANE\n");
				printf("THE EXPENCES WILL BE AS FOLLOWS:\n");
				totalAIRcost(cost_unit);
				break;
			}
		}		
		else if( choice == 2) {
			if(cityno1 == 0) 
				break;
			else if( cityno2 == 0)	
				break;
			else {
				printf("\nLETS SEE THE EXPENSES :\n");		
				printf("YOU CHOOSE TO TRAVEL BY TRAIN\n");
				printf("THE EXPENCES WILL BE AS FOLLOWS:\n");
				totalRAILcost(cost_unit);
				break;
			}
		}
		else if (choice == 3) {
			if(cityno1 == 0) 
				break;
			else if( cityno2 == 0)
				break;
			else {
				printf("\nLETS SEE THE EXPENSES :\n");
				printf("YOU CHOOSE TO TRAVEL BY ROAD\n");
				printf("THE EXPENCES WILL BE AS FOLLOWS:\n");
				totalROADcost(cost_unit);
				break;
			}
	 	}
		else {
			if(cityno1 == 0) 
				break;
			else if( cityno2 == 0)
				break;
			else {

				printf("\nLETS SEE THE EXPENSES :\n");
				printf("YOU CHOOSE TO TRAVEL BY WATERWAY\n");
				printf("THE EXPENCES WILL BE AS FOLLOWS:\n");
				totalWATERcost(cost_unit);
				break;
			}
		}
	}	
	printf("____________________________________________________\n");
	printf("....Wishing you Happy Journey...");
	return 0 ;
}

