/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("[----- 2021041018  장예서 -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f \n");
		printf(" Postorder Traversal  = t      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if (ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if (ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if (ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->key = key;
	node->left = node->right = NULL;
	Node* findNode = head->left;
	Node* parentNode = head;

	/* 첫 번째로 삽입되는 경우, head의 left 필드에 노드 삽입 */
	if (findNode == NULL)
		head->left = node;
	/* Leaf Node로 삽입되는 경우 */
	else {
		while (findNode != NULL) {
			parentNode = findNode;
			/** 어느 쪽 필드로 향할지 방향 선택
			 * 삽입되는 노드의 key가 더 작다면 왼쪽으로, 더 크다면 오른쪽으로 향함
			*/
			if (findNode->key > key)
				findNode = findNode->left;
			else if (findNode->key < key)
				findNode = findNode->right;
			/* 이미 트리에 같은 key가 존재하는 경우 리턴 */
			else {
				printf("Already same key exists.\n");
				return 1;
			}
		}
		/* 삽입되는 노드의 key가 더 작으면 left, 더 크면 right 필드에 삽입 */
		if (parentNode->key > key)
			parentNode->left = node;
		else
			parentNode->right = node;
	}

	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	/* 트리가 정의되지 않았거나 비어 있어서 삭제하지 못하는 경우 */
	if (head == NULL) {
		printf("Please initialize first.\n");
		return 1;
	}
	else if (head->left == NULL) {
		printf("Nothing to delete.\n");
		return 1;
	}

	Node* findNode = head->left;
	Node* parentNode = head;

	while (findNode != NULL) {
		if (findNode->key == key) {
			/* Leaf Node인지 확인 */
			if (findNode->left == NULL && findNode->right == NULL) {
				/* 해당 노드의 Parent Node의 왼쪽/오른쪽 필드 중 어디를 NULL로 만들지 확인 */
				if (parentNode->key > key)
					parentNode->left = NULL;
				else if (parentNode->key < key)
					parentNode->right = NULL;
				/* Leaf Node 삭제 */
				free(findNode);
				break;
			}
			/* Leaf Node가 아닌 경우 */
			printf("the node [%d] is not a leaf\n", key);
			break;
		}
		parentNode = findNode;
		/* 어느 방향으로 향할지 확인 */
		if (findNode->key > key)
			findNode = findNode->left;
		else if (findNode->key < key)
			findNode = findNode->right;

	}
	/* 해당하는 노드를 찾지 못한 경우 */
	if (findNode == NULL)
		printf("Cannot find the node [%d]\n", key);

	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	/* 찾지 못한 경우 */
	if (!ptr) return NULL;
	if (key == ptr->key) return ptr;
	if (key < ptr->key)
		return searchRecursive(ptr->left, key);
	return searchRecursive(ptr->right, key);
}

Node* searchIterative(Node* head, int key)
{
	Node* temp = head->left;
	while (temp) {
		if (key == temp->key) return temp;
		if (key < temp->key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	
	/* 찾지 못한 경우 */
	return NULL;
}


int freeBST(Node* head)
{
	Node* ptr = head->left;
	Node* parentNode = head;
	while (ptr != NULL) {
		parentNode = ptr;
		ptr = ptr->left;	/* 해당하는 노드를 찾지 못한 경우 */

		free(parentNode);
	}
}





