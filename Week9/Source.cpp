#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIZE_BUFFER 100
#define SIZE_PQ 100

struct Student
{
	int key; 
	char* name;
	int groupNo;
};

struct Heap
{
	Student** items;
	int size;
	int noElements;
};

Student* createStudent(int key, char* name, int group)
{
	Student* retValue = NULL;
	retValue = (Student*)malloc(sizeof(Student));
	retValue->name = (char*)malloc(strlen(name) + 1);
	strcpy(retValue->name, name);
	retValue->groupNo = group;
	retValue->key = key;
	return retValue;
}

void printStudent(Student stud)
{
	printf("%d - %s - %d \n", stud.key, stud.name, stud.groupNo);
}

void initHeap(Heap *heap)
{
	heap->items = (Student**)malloc(SIZE_PQ * sizeof(Student*));
	heap->size = SIZE_PQ;
	heap->noElements = 0;
	/*for (int i = 0; i < SIZE_PQ; i++)
	{
		heap->items[i] = NULL;
	}	*/
	memset(heap->items, NULL, sizeof(Student*) * SIZE_PQ);
}

void ReHeapUp(Heap heap, int child)
{
	if (child > 0)
	{
		int parent = (child - 1) / 2;
		if (heap.items[child]->key > heap.items[parent]->key)
		{
			Student* aux = heap.items[child];
			heap.items[child] = heap.items[parent];
			heap.items[parent] = aux;
			ReHeapUp(heap, parent);
		}
	}
}

Heap addStudent(Heap heap, Student* stud)
{
	if (heap.noElements < heap.size)
	{
		heap.items[heap.noElements] = stud;
		ReHeapUp(heap, heap.noElements);
		heap.noElements++;
	}
	else
	{
		Student** aux = heap.items;
		heap.items = (Student**)malloc(heap.size * 2 * sizeof(Student*));
		for (int i = 0; i < heap.noElements; i++)
		{
			heap.items[i] = aux[i];
			heap.items[heap.noElements + 1 + i] = NULL;
		}
		heap.size = 2 * heap.size;
		free(aux);
		heap = addStudent(heap, stud);
	}
	return heap;
}

void main()
{
	Heap heap;
	initHeap(&heap);
	FILE* pFile = fopen("S09Data.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);

	if (pFile)
	{
		char* token, separators[] = ",\n", name[30];
		int group;
		int key;
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			token = strtok(buffer, separators);
			key = atoi(token);
			token = strtok(NULL, separators);
			strcpy(name, token);
			token = strtok(NULL, separators);
			group = atoi(token);
			Student* stud = createStudent(key, name, group);
			printStudent(*stud);
			heap = addStudent(heap, stud);
		}
		for (int i = 0; i < heap.noElements; i++)
			printf("Key: %d - Name: %s - Group: %d \n", 
			      heap.items[i]->key, 
			      heap.items[i]->name, 
			      heap.items[i]->groupNo);
		fclose(pFile);
	}
}
