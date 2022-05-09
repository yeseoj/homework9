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

	printf("[----- 2021041018  �忹�� -----]\n");

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

	/* ù ��°�� ���ԵǴ� ���, head�� left �ʵ忡 ��� ���� */
	if (findNode == NULL)
		head->left = node;
	/* Leaf Node�� ���ԵǴ� ��� */
	else {
		while (findNode != NULL) {
			parentNode = findNode;
			/** ��� �� �ʵ�� ������ ���� ����
			 * ���ԵǴ� ����� key�� �� �۴ٸ� ��������, �� ũ�ٸ� ���������� ����
			*/
			if (findNode->key > key)
				findNode = findNode->left;
			else if (findNode->key < key)
				findNode = findNode->right;
			/* �̹� Ʈ���� ���� key�� �����ϴ� ��� ���� */
			else {
				printf("Already same key exists.\n");
				return 1;
			}
		}
		/* ���ԵǴ� ����� key�� �� ������ left, �� ũ�� right �ʵ忡 ���� */
		if (parentNode->key > key)
			parentNode->left = node;
		else
			parentNode->right = node;
	}

	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	/* Ʈ���� ���ǵ��� �ʾҰų� ��� �־ �������� ���ϴ� ��� */
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
			/* Leaf Node���� Ȯ�� */
			if (findNode->left == NULL && findNode->right == NULL) {
				/* �ش� ����� Parent Node�� ����/������ �ʵ� �� ��� NULL�� ������ Ȯ�� */
				if (parentNode->key > key)
					parentNode->left = NULL;
				else if (parentNode->key < key)
					parentNode->right = NULL;
				/* Leaf Node ���� */
				free(findNode);
				break;
			}
			/* Leaf Node�� �ƴ� ��� */
			printf("the node [%d] is not a leaf\n", key);
			break;
		}
		parentNode = findNode;
		/* ��� �������� ������ Ȯ�� */
		if (findNode->key > key)
			findNode = findNode->left;
		else if (findNode->key < key)
			findNode = findNode->right;

	}
	/* �ش��ϴ� ��带 ã�� ���� ��� */
	if (findNode == NULL)
		printf("Cannot find the node [%d]\n", key);

	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	/* ã�� ���� ��� */
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
	
	/* ã�� ���� ��� */
	return NULL;
}


int freeBST(Node* head)
{
	Node* ptr = head->left;
	Node* parentNode = head;
	while (ptr != NULL) {
		parentNode = ptr;
		ptr = ptr->left;	/* �ش��ϴ� ��带 ã�� ���� ��� */

		free(parentNode);
	}
}





