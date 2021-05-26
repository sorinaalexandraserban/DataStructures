#define _CRT_SECURE_NO_WARNINGS
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#define SIZE_BUFFER 100
#define SEPARATOR "\n---------------\n"

// arbore echilibrat 

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
	short bFactor;
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
	nou->bFactor = 0;
	return nou;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

short getHeight(Node* root)
{
	if (root != NULL) 
		return 1 + max(getHeight(root->left), getHeight(root->right));
	else
		return 0;
}

void updateBFactor(Node** pivot)
{
	(*pivot)->bFactor = getHeight((*pivot)->right) - getHeight((*pivot)->left);
}

Node* rightRotation(Node* pivot) 
{
	Node* desc = pivot->left;
	pivot->left = desc->right;
	desc-> right = pivot;
	updateBFactor(&pivot);
	updateBFactor(&desc);
	return desc;
}

Node* leftRotation(Node* pivot)
{
	Node* desc = pivot->right;
	pivot->right = desc->left;
	desc->left = pivot;
	updateBFactor(&pivot);
	updateBFactor(&desc);
	return desc;
}

//echilibrare arbore
void balanceTree(Node** pivot)
{
	updateBFactor(&*pivot);
	Node* desc = NULL;
	if ((*pivot)->bFactor == -2)
	{
		desc = (*pivot)->left;
		if (desc->bFactor == -1) {
			//rightRotation in pivot;
			*pivot = rightRotation(*pivot);
		}
		else
		{
			//leftRotation in desc
			desc = leftRotation(desc);
			//rightRotation in pivot
			*pivot = rightRotation(*pivot);
		}
	}
	else if ((*pivot)->bFactor == 2)
	{
		desc = (*pivot)->right;
		if (desc->bFactor == -1) {
			//rightRotation in desc
			desc = rightRotation(desc);
		    //leftRotation in pivot
			*pivot = leftRotation(*pivot);
		}
		else {
			//leftRotation in pivot
			*pivot = leftRotation(*pivot);
		}
	}
}

void insertNode(Node** root, Student* student) {
	if (*root == NULL)//insert
	{
		*root = createNode(student);
	}
	else //search
	{
		if (student->key < (*root)->student->key)
		{
			insertNode(&(*root)->left, student);
		}
		else if (student->key > (*root)->student->key)
		{
			insertNode(&(*root)->right, student);
		}
		else //insertion not possible
			printf("No duplicate's allowed");
	}
	balanceTree(root);
}

//function for tree traversal LD->Root->RD
void printInorder(Node* root)
{
	if (root)
	{
		printInorder(root->left);
		printf("BF: %d - %d - %s\n", root->bFactor, root->student->key, root->student->name);
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

//function that tests if a node has two descendants
bool hasTwoDescendants(Node* root) {
	if (root->left != NULL && root->right != NULL)
		return true;
	else
		return false;
}

void logicalExtraction(Node*& root, Node*& desc) {
	if (desc->right) {
		logicalExtraction(root, desc->right);
	}
	else {
		Node* aux = desc->left;
		Node* left = root->left;
		Node* right = root->right;
		root = desc;
		root->right = right;
		if (root != left)
			root->left = left;
		else
			root->left = left->left;
		desc = aux;
	}
}
Node* extractNode(Node*& root, int key) {
	Node* cautat = NULL;
	if (root != NULL) {
		if (key < root->student->key)
			cautat = extractNode(root->left, key);
		else if (key > root->student->key)
			cautat = extractNode(root->right, key);
		else
		{
			cautat = root;
			if (!hasTwoDescendants(root))
				root = root->left ? root->left : root->right;
			else
				logicalExtraction(root, root->left);
		}
	}
	return cautat;
}
Node* extractNode(Node** root, int key) {
	Node* value = NULL;
	if (*root != NULL) {
		if ((*root)->student->key < key)
			value = extractNode(&(*root)->right, key);
		else if ((*root)->student->key > key)
			value = extractNode(&(*root)->left, key);
		else
		{
			value = *root;
			if (!hasTwoDescendants(*root))
			{
				Node* aux = (*root)->left ? (*root)->left : (*root)->right;
				*root = aux;
			}
			else
			{
				Node* parentLeft = NULL;
				Node* leftSubTree = parentLeft = (*root)->left;
				while (leftSubTree->right)
				{
					parentLeft = leftSubTree;
					leftSubTree = leftSubTree->right;
				}
				Node* leftChild = (*root)->left;
				Node* rightChild = (*root)->right;
				leftSubTree->right = rightChild;

				if (parentLeft != leftSubTree)
					parentLeft->right = leftSubTree->left;
				if (leftSubTree != leftChild)
					leftSubTree->left = leftChild;
				else
					leftSubTree->left = leftChild->left;
				*root = leftSubTree;
			}
		}
	}
	return value;
}

Student* searchStudent(Node* root, int key)
{
	Student* value = NULL;
	if (root != NULL) {
		if (key < root->student->key)
			value = searchStudent(root->left, key);
		else if (key > root->student->key)
			value = searchStudent(root->right, key);
		else
			value = root->student;
	}
	return value;
}

void logicalDeletion(Node*& root, Node*& desc)
{
	if (desc->left != NULL)
		logicalDeletion(root, desc->left);
	else
	{
		Student* tmp = root->student;
		root->student = desc->student;
		Node* aux = desc;
		desc = desc->right;
		free(tmp->name);
		free(tmp);
		free(aux);
	}
}
void deleteNode(Node*& root, int key) {
	if (root != NULL)
	{
		if (key == root->student->key)
		{
			if (!hasTwoDescendants(root))
			{
				Node* tmp = root;
				root = root->left ? root->left : root->right;
				// stergere nod frunza
				free(tmp->student->name);
				free(tmp->student);
				free(tmp);
			}
			else
				logicalDeletion(root, root->right);
		}
		else {
			if (key < root->student->key)
				deleteNode(root->left, key);
			else
				deleteNode(root->right, key);
		}
		//balanceTreeDelete(root);
	}
}

void main()
{
	Node* tree = NULL;
	Node* invTree = NULL;
	FILE* pFile = fopen("S13Data.txt", "r");
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
		printf(SEPARATOR);
		printOneDescendent(tree);
		printf(SEPARATOR);
		invertTree(tree);
		printf(SEPARATOR);
		printInorder(tree);
		printf(SEPARATOR);
		createInvertedTree(invTree, tree);
		printf(SEPARATOR);
		printInorder(invTree);
		printf(SEPARATOR);

		Student** paths = (Student**)malloc(sizeof(Student*) * 6);
		pathsToLeaves(tree, paths, 0);

		Student* stud = searchStudent(tree, 3);
		if (stud)
			printf("%d - %s\n", stud->key, stud->name);
		else
			printf("Key not found %s", SEPARATOR);
		//deleteNode(tree, 3);
		Node* extracted = extractNode(&tree, 3);
		if (extracted)
			printf("%d - %s %s", extracted->student->key, extracted->student->name, SEPARATOR);
		else
			printf("Key not found %s", SEPARATOR);
		printf(SEPARATOR);
		printInorder(tree);
		printf(SEPARATOR);
	}
}
