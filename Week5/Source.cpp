#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define _CRT_SECURE_NO_WARNINGS

//liste simplu inlantuite
struct Student
{
	char* nume;

};

struct Node
{
	Student* student;
	Node* pNext;
};

#define SIZEOF_BUFFER 100

Student* createStudent(char* nume)
{
	Student* retValue = NULL;
	//1. alocare spatiu pentru elemente
	retValue = (Student*)malloc(sizeof(Student));
	//2. initializare atributele elem
	retValue->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(retValue->nume, nume);
	return retValue;
}

Node* createNode(Student* stud) {
	Node* node = NULL;
	node = (Node*)malloc(sizeof(Node));
	node->student = stud;
	node->pNext = NULL;
	return node;
}

//1. param pass by value -- daca au acelasi tip---> ex. Node* lista
//2. param pass by adress -- daca sunt diferite
		//2.1. by reference -- Node*& lista
		//2.2. by pointer -- Node** lista
void insertListHead(Node** lista, Node* node)
{
	if (*lista == NULL)
	{
		*lista = node;
	}
	else 
	{
		//inserare lista la inceput
		node->pNext = *lista;
		*lista = node;
	}
}

void insertListTail(Node** lista, Node* node)
{
	if (*lista == NULL)
	{
		*lista = node;
	}
	else
	{
		//inserare lista la sfarsit
		Node* tmp = *lista;
		while (tmp->pNext)
			tmp = tmp->pNext;
		tmp->pNext = node;
	}
}

void printList(Node* lista)
{
	while (lista)
	{
		fputs(lista->student->nume, stdout);
		lista = lista->pNext;
	}
}

void main() 
{
	Node* lista = NULL; //lista vida
	FILE* pFile = fopen("S05Data.txt", "r");
	char* buffer = (char*)malloc(SIZEOF_BUFFER);
	if (pFile)
	{
		while (!feof(pFile))
		{
			fgets(buffer, SIZEOF_BUFFER, pFile);
			Student* stud = createStudent(buffer);
			Node* node = createNode(stud);
			insertListHead(&lista, node);
		}
		fclose(pFile);
		printList(lista);
	}
	
}
