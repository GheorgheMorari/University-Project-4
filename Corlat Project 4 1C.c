#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	long int val, index;
	struct node* prev;
} node_t;

node_t * newNode(long int val,long int index, node_t* prev) {
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->index = index;
	temp->val = val;
	temp->prev = prev;
	return temp;
}

void undoMove(long int n, node_t* currentNode) {
	long int ballsRemoved = 0;
	while (currentNode->val > 0) { 
		ballsRemoved ++;
		currentNode->val --;
		currentNode = currentNode->prev;
	}
	currentNode->val = ballsRemoved;
}

int main() {
	int i;

	int n; //The number of boxes
	int m; //The number of moves

	scanf_s("%d %d", &n, &m);

	node_t** nodes = (node_t**)malloc(sizeof(node_t*) * n);

	for (i = 0; i < n; i++) {
		long int temp;
		scanf_s("%d", &temp);
		if (i == 0) 
			nodes[i] = newNode(temp,i, NULL);
		else
			nodes[i] = newNode(temp,i, nodes[i - 1]);  
	}

	nodes[0]->prev = nodes[n - 1];  //Complete the cycle

	for (i = 0; i < m; i++) {
		long int temp;
		scanf_s("%d", &temp);
		/*Use temp-1 because input is from 1 to n not 0 to n-1*/
		undoMove(temp,nodes[temp-1]);   
	}

	printf("\n");

	for (i = 0; i < n; i++) {
		printf("%d \n",nodes[i]->val);
		free(nodes[i]);
	}
	free(nodes);
	return 0;
}
