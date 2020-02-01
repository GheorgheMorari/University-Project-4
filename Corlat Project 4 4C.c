#include <stdio.h>
#include <stdlib.h>

struct node {
	int data, child;
	struct node* left;
	struct node* right;
};

struct node* newNode(int i) {
	/* Allocate memory for new node. */
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->data = i;
	node->child = 0;
	node->left = NULL;
	node->right = NULL;
	return(node);
}

	/* The findLeft function finds the leftmost node at the desired level. */
int findLeft(struct node* rootNode, int curLevel, int desiredLevel)
{
	int temp;
	if (curLevel != desiredLevel) {
		if (rootNode->left != NULL) { //Check for left node first.
			temp = findLeft(rootNode->left, curLevel + 1, desiredLevel);
			if (temp != -1) {
				return temp;
			}
		}
		if (rootNode->right != NULL) {
			temp = findLeft(rootNode->right, curLevel + 1, desiredLevel);
			if (temp != -1) {
				return temp;
			}
		}
		return -1; //Return -1 if there are no more children
	}
	return rootNode->data;
}

	/* Copy of findLeft() but with check right first. */
int findRight(struct node* rootNode, int curLevel, int desiredLevel)
{ 
	int temp;
	if (curLevel != desiredLevel) {
		if (rootNode->right != NULL) {
			temp = findRight(rootNode->right, curLevel + 1, desiredLevel);
			if (temp != -1) {
				return temp;
			}
		}
		if (rootNode->left != NULL) {
			temp = findRight(rootNode->left, curLevel + 1, desiredLevel);
			if (temp != -1) {
				return temp;
			}
		}
		return -1;  
	}
	return rootNode->data;
}


int main()
{
	int i;
	int n;	//The Number of nodes in the tree from 1 to n.
	int k;	//The desired level to look the leftmost and rightmost.
	int rootIndex; //The Index of the Root node.

	scanf_s("%d %d", &n, &k);
	n++; //increment n for this type of input

	struct node** arrOfNodes = (struct node**)malloc(sizeof(struct node*) * n);

	for (i = 0; i < n; i++) {
		arrOfNodes[i] = newNode(i); //Initialize each node with its index.
	}

	for (i = 0; i < n-2; i++) {
		int j, t;
		char dir;
		scanf_s("%d %d %c", &j, &t, &dir);

		/*Set the left or right childs.*/
		if (dir == 'D') {	
			arrOfNodes[j]->right = arrOfNodes[t]; 
		}
		else {
			arrOfNodes[j]->left = arrOfNodes[t];
		}
		arrOfNodes[t]->child = 1;            
	}

	/*Find the root of the tree.*/
	for (i = 1; i < n - 1; i++) {
		if ((arrOfNodes[i]->child) == 0) {  
			rootIndex = i;
			break;
		}
	}

	printf("%d %d",
			 findLeft(arrOfNodes[rootIndex], 0, k),
			findRight(arrOfNodes[rootIndex], 0, k)); 

	free(arrOfNodes);
	return 0;
}

