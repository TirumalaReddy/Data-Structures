// Example input
// 7
// 9
// 0 1 3
// 0 2 8
// 1 3 7
// 2 4 2
// 2 3 1
// 3 4 4
// 3 5 2
// 4 6 4
// 5 6 1
// 0
#include <stdio.h>
#include <stdlib.h>
struct vertex {
	int data;
	int capacity;
	struct vertex* next;
};
struct shortDist {
	int data;
	int capacity;
};
void push(int *Queue, int value, int* front) {
	Queue[(*front)++] = value;
}
int pop(int *Queue, int* rear, int* front) {
	if (*rear == *front) return -1;
	else {
		return Queue[(*rear)++];
	}
}
void DFS(struct vertex** ref, int vertex, int* visited) {
	visited[vertex] = 1;
	printf("%d ", vertex);
	struct vertex* vert = ref[vertex];
	while (vert != NULL) {
		if(visited[vert->data] == 0) DFS(ref, vert->data, visited);
		vert = vert->next;
	}
}
void DFSUtil(struct vertex** ref, int size) {
	int i, visited[size];
	for(i=0;i<size;i++) visited[i]=0;
	for(i=0;i<size;i++) {
		if (visited[i] == 0) {
			DFS(ref, i, visited);
		}
	}
}
void BFS(struct vertex** ref, int size) {
	int i=0;
	int visited[size], Queue[size], front=0, rear=0;
	for (i=0;i<size;i++)visited[i]=0;
	for (i=0;i<size; i++) {
		if(visited[i] == 0) push(Queue, i, &front);
		int vertex = pop(Queue, &rear, &front);
		while (vertex != -1 && visited[vertex] == 0) {
			printf("%d ", vertex);
			visited[vertex] = 1;
			struct vertex* ver = ref[vertex];
			while (ver != NULL) {
				push(Queue, ver->data, &front);
				ver = ver->next;
			}
			vertex = pop(Queue, &rear, &front);
		}
	}
}
struct shortDist* minimum(struct shortDist** minHeap, int i,int heapsize, int* position) {
	// Check for boundary conditions
	if (2*i+1 >= heapsize) {
		return NULL;
	}
	if (2*i+2 >= heapsize) {
		*position = 2*i+1;
		return minHeap[2*i+1];
	}
	if (minHeap[2*i+1]->capacity < minHeap[2*i+2]->capacity) 
		{
			*position = 2*i+1;
			return minHeap[2*i+1];
		}
	else {
		*position = 2*i+2;
		return minHeap[2*i+2];
	}
}
void minHeapify(struct shortDist** minHeap, int heapsize) {
	int position, parentPosition = 0;
	struct shortDist* parent = minHeap[0];
	struct shortDist* minLR = minimum(minHeap, parentPosition, heapsize, &position);
	while (minLR != NULL) {
		if(minLR->capacity < parent->capacity) {
			minHeap[position] = parent;
			minHeap[parentPosition] = minLR;
			parentPosition = position;
			parent = minHeap[position];
		}
		minLR = minimum(minHeap, position, heapsize, &position);
	}
}
struct shortDist* extractMin(struct shortDist** minHeap, int *heapsize) {
	if (*heapsize == 0) {
		return NULL;
	}
	int i = *heapsize -1;
	struct shortDist* mini = minHeap[0];
	struct shortDist* last = minHeap[i];
	(*heapsize)--;
	minHeap[0] = last;
	minHeapify(minHeap, *heapsize);
	return mini;
}
void insertHeap(struct shortDist** minHeap, struct shortDist* node, int *heapsize) {
	int i = *heapsize;
	minHeap[(*heapsize)++] = node;
	struct shortDist* parent = minHeap[(i-1)/2];
	if(parent->capacity > node->capacity) {
		minHeap[i] = parent;
		minHeap[(i-1)/2] = node;
	}
}
struct vertex* newNode(int data, int capacity) {
	struct vertex* v1 = (struct vertex*) malloc(sizeof(struct vertex));
	v1->data=data;
	v1->capacity=capacity;
	v1->next = NULL;
	return v1;
}
struct shortDist* newSD(int data, int capacity) {
	struct shortDist* v1 = (struct shortDist*) malloc(sizeof(struct shortDist));
	v1->data=data;
	v1->capacity=capacity;
	return v1;
}
void printHeap(struct shortDist** minheap,int heapsize) {
	int i;
	printf("\n");
	for (i=0;i<heapsize;i++) {
		printf(" %d %d, ", minheap[i]->data, minheap[i]->capacity);
	}
}
void dijkstra(struct vertex** ref, int size, int edges, int source) {
	struct shortDist** minHeap;
	int i, heapsize = 0, current;
	int visited[size];
	struct shortDist** sd =(struct shortDist**) malloc(sizeof(struct shortDist*) * size);
	for (i=0;i<size;i++) visited[i]=0;
	minHeap = (struct shortDist **) malloc(sizeof(struct shortDist*) * edges);
	for(i=0;i<size;i++) {
		sd[i] = newSD(i, 10000);
	}
	sd[source]->capacity = 0;
	struct shortDist* min = sd[source];
	visited[source] = 1;
	while(min != NULL) {
		struct vertex* next = ref[min->data];
		while(next != NULL) {
			if(visited[next->data] == 0) {
				insertHeap(minHeap, sd[next->data], &heapsize);
				visited[next->data] = 1;
			}
			if (min->capacity + next->capacity < sd[next->data]->capacity) {
				sd[next->data]->capacity = min->capacity + next->capacity;
			}
			next = next->next;
		}
		//printHeap(minHeap, heapsize);
		min = extractMin(minHeap, &heapsize);
	}
	printf("Shortest distances from source %d \n", source);
	for (i=0;i<size;i++) {
		printf("%d distance %d\n", i, sd[i]->capacity);
	}
}

void PrimsMST(struct vertex** ref, int size, int edges, int source) {
	int i, visited[size], heapsize=0, parent[size];
	struct shortDist** minHeap;
	struct shortDist* min;
	struct shortDist** sd =(struct shortDist**) malloc(sizeof(struct shortDist*) * size);
	minHeap = (struct shortDist **) malloc(sizeof(struct shortDist*) * size);
	for (i=0;i<size;i++) {
		visited[i] = 0;
		sd[i] = newSD(i, 10000);
		parent[i] = source;
	}
	sd[source]->capacity = 0;
	min = sd[source];
	visited[source] = 1;
	printf("Minimum Spanning Tree \n");
	while(min != NULL) {
		printf("%d --> %d : %d\n",parent[min->data], min->data, min->capacity);
		struct vertex* next = ref[min->data];
		while(next != NULL) {
			if (next->capacity < sd[next->data]->capacity) {
				sd[next->data]->capacity = next->capacity;
				parent[next->data] = min->data;
			}
			if (visited[next->data] == 0) {
				insertHeap(minHeap, sd[next->data], &heapsize);
				visited[next->data] = 1;
			}
			next = next->next;
		}
		min = extractMin(minHeap, &heapsize);
	}
	printf("\n");
}

void addEdge(struct vertex** ref, int v1, int v2, int capacity) {
	struct vertex* vertex = newNode(v2, capacity);
	struct vertex* exist = ref[v1];
	if (exist == NULL) {
		ref[v1] = vertex;
	} else {
		while (exist->next != NULL) {
			exist = exist->next;
		}
		exist->next = vertex;
	}
}
void printAdj(struct vertex ** ref, int size) {
	int i;
	for (i=0; i<size; i++) {
		struct vertex* temp = ref[i];
		while (temp != NULL) {
			printf("%d ", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}
int main(void) {
	struct vertex** ref;
	int i,size, edges, v1, v2, capacity, *capacities;
	int source=0;
	scanf("%d", &size);
	scanf("%d", &edges);
	capacities = (int *) malloc(sizeof(int) * size);
	ref =(struct vertex**) malloc(sizeof(struct vertex*) * size);
	for (i=0;i<size;i++) ref[i] = NULL;
	i = edges;
	// undirected
	while (i--) {
		scanf("%d %d %d", &v1, &v2, &capacity);
		addEdge(ref, v1, v2, capacity);
		addEdge(ref, v2, v1, capacity);
	}
	scanf("%d", &source);
	dijkstra(ref, size, edges, source);
	PrimsMST(ref, size, edges, source);
	//printAdj(ref, size);
	printf("BFS \n");
	BFS(ref, size);
	printf("\nDFS\n");
	DFSUtil(ref, size);
	return 0;
}
