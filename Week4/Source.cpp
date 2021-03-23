#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 100

void convert(char*);

struct Letter //18
{
	int : 5;
	int bit : 1;
	int : 2;
};

//matrice de siruri de caractere

void main() 
{
	//int** mat; //matrice de intregi
	//char** mat; // matrice de caractere
	//char* nume; //sir de caractere
	//char* mat[10][10]; //alocata static

	char*** matrix = NULL; //matrice de siruri de caractere alocata dinamic
	FILE* pFile = fopen("S04Data.txt", "r");
	char* buffer = (char*)malloc(BUFFER_SIZE);
	if (pFile)
	{
		int matSize = 0;
		//fscanf(pFile, "%i", &matSize);
		fgets(buffer, BUFFER_SIZE, pFile);
		matSize = atoi(buffer);
		// 1. 
		matrix = (char***)malloc(matSize * sizeof(char**));
		// 2.
		for(int i = 0; i< matSize; i++)
		{
			matrix[i] = (char**)malloc(matSize * sizeof(char*));
			for (int j = 0; j < matSize; j++)
				matrix[i][j] = NULL;
		}
		int i = 0, j = 0, index = 0;
		while (!feof(pFile))
		{
			i = index / matSize;
			j = index % matSize;
			fgets(buffer, BUFFER_SIZE, pFile);
			matrix[i][j] = (char*)malloc(strlen(buffer) + 1);
			strcpy(matrix[i][j], buffer);
			index++;
		}
		fclose(pFile);

		for (int i = 0; i < matSize; i++)
		{
			for (j = 0; j < matSize; j++)
			{
				fputs(matrix[i][j], stdout);
			}
		}

		for (int i = 0; i < matSize; i++)
		{
			for (j = 0; j < matSize; j++)
			{
				convert(matrix[i][j]);
			}
		}

		for (int i = 0; i < matSize; i++)
		{
			for (j = 0; j < matSize; j++)
			{
				fputs(matrix[i][j], stdout);
			}
		}
	}

}

void convert(char* name)
{
	Letter* letter;
	for (int i = 0; i < strlen(name); i++)
		if (name[i] >= 'á' && name[i] <= 'z')
		{
			//name[i] = name[i] & 223;
			letter = (Letter*)&name[i];
			letter->bit = ~letter->bit;
		}
		
}

//de luat matricea si sa o transf intr un vector de siruri de caractere
