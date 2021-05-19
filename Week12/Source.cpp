#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#define SIZE_BUFFER 100

struct Student
{
	int key;
	char* name;
	int group;
};

struct Node
{
	Node* left;
	Student* student;
	Node* right;
};

Student* createStudent(char* name, int group, int key)
{
	Student* retValue = NULL;
	retValue = (Student*)malloc(sizeof(Student));
	retValue->name = (char*)malloc(strlen(name) + 1);
	strcpy(retValue->name, name);
	retValue->key = key;
	retValue->group = group;
	return retValue;
}

Node* createNode(Student* student) {
	Node* nou = (Node*)malloc(sizeof(Node));
	nou->student = student;
	nou->left = nou->right = NULL;
	return nou;
}

void insertNode(Node** root, Student* student) {
	if (*root == NULL)//insert
	{
		*root = createNode(student);
	}
	else //search
	{
		if ((*root)->student->key < student->key)
		{
			insertNode(&(*root)->left, student);
		}
		else if ((*root)->student->key > student->key)
		{
			insertNode(&(*root)->right, student);
		}
		else //insertion not possible
			printf("No duplicate's allowed");
	}
}

//LD->Root->RD
void printInorder(Node* root)
{
	if (root)
	{
		printInorder(root->left);
		printf("%d - %s\n", root->student->key, root->student->name);
		printInorder(root->right);
	}
}

void createInvertedTree(Node*& invRoot, Node* orgRoot)
{
	if (orgRoot)
	{
		insertNode(&invRoot, orgRoot->student);
		createInvertedTree(invRoot->right, orgRoot->left);
		createInvertedTree(invRoot->left, orgRoot->right);
	}
}

void printOneDescendent(Node* root)
{
	if (root)
	{
		printOneDescendent(root->left);
		if ((root->right != NULL && root->left != NULL))
			printf("%d - %s\n", root->student->key, root->student->name);
		printOneDescendent(root->right);
	}
}

void invertTree(Node* root)
{
	if (root)
	{
		invertTree(root->left);
		invertTree(root->right);
		Node* aux = root->left;
		root->left = root->right;
		root->right = aux;
	}
}

void pathsToLeaves(Node* root, Student** vector, int index) {
	if (root)
	{
		vector[index] = root->student;
		if (root->left == NULL && root->right == NULL) {
			for (int i = 0; i <= index; i++)
				printf("%d:", vector[i]->key);
			printf("\n");
		}
		else {
			pathsToLeaves(root->left, vector, index + 1);
			pathsToLeaves(root->right, vector, index + 1);
		}
	}
}

bool isLeaf(Node* root)
{
	if (root->left == NULL && root->right == NULL)
	{
		return true;
	}
	else
		return false;
}

bool hasOneDescendant(Node* root)
{
	if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void searchKey(Node* root, int key, Student** student) {
	if (root) {
		if (key < root->student->key) {
			searchKey(root->left, key, student);
		}
		else if (key > root->student->key) {
			searchKey(root->right, key, student);
		}
		else {
			*student = root->student;
		}
	}
}

void logicalDeletion(Node** root, Node** leftDesc) {
	if ((*leftDesc)->right)
		logicalDeletion(root, &(*leftDesc)->right);
	else
	{
		free((*root)->student->name);
		free((*root)->student);
		(*root)->student = (*leftDesc)->student;
		Node* aux = (*leftDesc)->left;
		free(aux);
	}
}

void deleteNode(Node** root, int key) {
	if (*root) {
		if ((*root)->student->key < key) {
			deleteNode(&(*root)->right, key);
		}
		else if ((*root)->student->key > key) {
			deleteNode(&(*root)->left, key);
		}
		else {
			if (isLeaf(*root)) {
				free((*root)->student->name);
				free((*root)->student);
				free((*root));
				*root = NULL;
			}
			else if (hasOneDescendant(*root)) {
				Node* child = (*root)->right ? (*root)->right : (*root)->left;
				free((*root)->student->name);
				free((*root)->student);
				free((*root));
				*root = child;
			}
			else {
				logicalDeletion(root, &(*root)->left);
			}
		}
	}
}

void main()
{
	Node* tree = NULL;
	Node* invTree = NULL;
	FILE* pFile = fopen("S12_Data.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);
	if (pFile)
	{
		char* token, separators[] = ",\n", name[30];
		int group, key;
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			token = strtok(buffer, separators);
			key = atoi(token);
			token = strtok(NULL, separators);
			strcpy(name, token);
			token = strtok(NULL, separators);
			group = atoi(token);
			Student* stud = createStudent(name, group, key);
			insertNode(&tree, stud);
		}
		fclose(pFile);
		printInorder(tree);
		printf("\n----------------\n");
		printOneDescendent(tree);
		printf("\n----------------\n");
		invertTree(tree);
		printf("\n----------------\n");
		printInorder(tree);
		printf("\n----------------\n");
		createInvertedTree(invTree, tree);
		printf("\n----------------\n");
		printInorder(invTree);
		printf("\n----------------\n");
		//TBI: implement the following function with array reallocation
		Student** paths = (Student**)malloc(sizeof(Student*) * 6);
		pathsToLeaves(tree, paths, 0);

		
		Student* student = NULL;
		searchKey(tree, 5, &student);  //12 - Not found!
		if (student != NULL) {
			printf("\n %s --- %d", student->name, student->key);
		}
		else {
			printf("\nNot found!");
		}
		printf("\n----------------\n");
		printInorder(tree);
		printf("\n----------------\n");
		deleteNode(&tree, 7);
		printf("\n----------------\n");
		printInorder(tree);
		printf("\n----------------\n");
	}
}
