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

struct BSTNode {
	Student* info = NULL;
	BSTNode* left = NULL;
	BSTNode* right = NULL;
};

BSTNode* createNode(Student* info) {
	BSTNode* res = NULL;
	res = (BSTNode*)malloc(sizeof(BSTNode));
	res->info = info;
	res->left = NULL;
	res->right = NULL;
	return res;
}

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

void insertNode(BSTNode*& root, Student* stud) {
	if (root == NULL) {
		root = createNode(stud);
	}
	else {
		if (stud->key < root->info->key) {
			insertNode(root->left, stud);
		}
		else if (stud->key > root->info->key) {
			insertNode(root->right, stud);
		}
		else {
			printf("Duplicates!");
		}
	}
}

//LD -> Root -> RD //crescator
void printInOrder(BSTNode* root) {
	if (root)
	{
		printInOrder(root->left);
		printf("Key: %d - Name: %s\n",
			root->info->key,
			root->info->name);
		printInOrder(root->right);
	}
}

void main()
{
	BSTNode* tree = NULL;
	FILE* pFile = fopen("S11_Data.txt", "r");
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
			insertNode(tree, stud);

		}
		printInOrder(tree);
		fclose(pFile);
	}
}
