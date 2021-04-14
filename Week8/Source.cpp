#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIZE_BUFFER 100
#define SIZE_HT 26

struct Student
{
	char* name;
	int groupId;
};

struct Node
{
	Student* stud;
	Node* pNext;
	Node* pPrev;
};

struct HashTable
{
	Node** slots;
	int size;
	static void initHashTable(HashTable*, int);
	void addStudent(Student*);
	int getHash(const char*);
	Student* getStudent(const char*);
};

Student* createStudent(char* name, int group)
{
	Student* retValue = NULL;
	retValue = (Student*)malloc(sizeof(Student));
	retValue->name = (char*)malloc(strlen(name) + 1);
	strcpy(retValue->name, name);
	retValue->groupId = group;
	return retValue;
}

Node* createNode(Student * stud)
{
	Node* retValue = NULL;
	retValue = (Node*)malloc(sizeof(Node));
	retValue->stud = stud;
	retValue->pNext = NULL;
	retValue->pPrev = NULL;
	return retValue;
}

void HashTable::initHashTable(HashTable* ht, int size)
{
	ht->slots = (Node**)malloc(sizeof(Node*) * size);
	ht->size = size;
	memset(ht->slots, NULL, sizeof(Node*) * size);
	/*for (int i = 0; i < size; i++)
		ht->slots[i] = NULL;*/
}

int HashTable::getHash(const char* key)
{
	return key[0] % SIZE_HT;
}

void insertList(Node*& head, Student* stud)
{
	Node* node = createNode(stud);
	if (head == NULL)
		head->pPrev = head->pNext = head = node;
	else
	{
		node->pNext = head;
		node->pPrev = head->pPrev;
		/*head->pPrev->pNext = node;
		head->pPrev = node; */
		head->pPrev = node;
		node->pPrev->pNext = node;
		head = node;
	}
}

void HashTable::addStudent(Student* stud)
{
	int index = getHash(stud->name);
	Node* list = slots[index];
	insertList(list, stud);
	slots[index] = list;
}

Student* searchList(Node* head, const char* key)
{
	Student* stud = NULL;
	Node* iterator = head;
	do
	{
		if (strcmp(iterator->stud->name, key) == 0)
			stud = iterator->stud;
		iterator = iterator->pNext;
	} while (iterator != head && stud == NULL);
	return stud;
}

Student* HashTable::getStudent(const char* key)
{
	Student* stud = NULL;
	int index = getHash(key);
	Node* list = slots[index];
	stud = searchList(list, key);
	return stud;
}

void main()
{
	FILE* pFile = fopen("S08Data.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);
	HashTable hashTable;
	HashTable::initHashTable(&hashTable, SIZE_HT);
	if (pFile)
	{
		char* token, separators[] = ",\n", name[30];
		int group;
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			token = strtok(buffer, separators);
			strcpy(name, token);
			token = strtok(NULL, separators);
			group = atoi(token);
			Student* stud = createStudent(name, group);
			hashTable.addStudent(stud);
		}
		fclose(pFile);
		Student* stud = hashTable.getStudent("Sandulescu Liviu");
		if (stud != NULL)
			printf("Student: %s - Group: %d\n", stud->name, stud->groupId);
		else
			printf("Student not found!\n");
		stud = hashTable.removeStudent("Sandulescu Liviu");
		if (stud != NULL)
			printf("Student: %s - Group: %d\n", stud->name, stud->groupId);
		else
			printf("Student not found!\n");
	}
}
