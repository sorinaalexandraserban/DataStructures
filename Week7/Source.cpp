#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIZE_BUFFER 100
#define _CRT_SECURE_NO_WARNINGS

struct Student
{
	char* name;
};

struct Node
{
	Node* prev;
	Student* stud;
	Node* next;
};

struct Queue
{
	Node* head = NULL;
	Node* tail = NULL;

};

Student* createStudent(char* name)
{
	Student* value = NULL;
	value = (Student*)malloc(sizeof(Student));
	value->name = (char*)malloc(strlen(name) + 1);
	strcpy(value->name, name);
	return value;
}

Node* createNode(Student* stud)
{
	Node* value = NULL;
	value = (Node*)malloc(sizeof(Node));
	value->stud = stud;
	value->next = value->prev = NULL;
	return value;
}

void push(Node** stack, Student* stud)
{
	Node* node = createNode(stud);
	//1. legati structura de node
	//2. conectati nodul de structura
	if (*stack != NULL)
	{
		(*stack)->prev = node;
	}
	node->next = (*stack);
	(*stack) = node;
}

Student* peek(Node* stack)
{
	Student* value = NULL;
	if (stack != NULL)
		value = stack->stud;
	return value;
}

Student* pop(Node** stack)
{
	Student* value = NULL;
	if (*stack != NULL)
	{
		value = (*stack)->stud;
		Node* tmp = *stack;
		(*stack) = tmp->next;
		if (*stack != NULL)
			(*stack)->prev = NULL;
		free(tmp);
	}
	return value;
}

void displayStack(Node*& stack)
{
	if (stack != NULL)
	{
		printf("Student: %s \n", peek(stack)->name);
		Student* stud = pop(&stack);
		displayStack(stack);
		push(&stack, stud);
	}
}

void main()
{
	Queue queue;
	FILE* pFile = fopen("S07Data.txt", "r");
	char* buffer = (char*)malloc(SIZE_BUFFER);
	Node* list = NULL;
	Node* stack = NULL;
	if (pFile)
	{
		char* token, separators[] = ",\n";
		while (fgets(buffer, SIZE_BUFFER, pFile))
		{
			token = strtok(buffer, separators);
			Student* stud = createStudent(token);
			Node* node = createNode(stud);
			//insertNodeTail(&list, node);
			//insertNodeHead(list, node);
			//enqueue(queue, stud);
			push(&stack, stud);
		}
		displayStack(stack);
		fclose(pFile);
	}
}
