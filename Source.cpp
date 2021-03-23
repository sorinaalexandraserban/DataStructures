#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define _CRT_SECURE_NO_WARNINGS

enum VehicleType { CAR = 10, AIRPLANE = 20 };

union VehicleUsage  
{
	int noMiles;
	double flightHours;
};

struct Vehicle
{
	char* name;
	VehicleType type;
	VehicleUsage operation;
};

Vehicle* buildVehicle(char* _name, int _type, double _operation)
{
	Vehicle* retValue = NULL;
	retValue = (Vehicle*)malloc(sizeof(Vehicle));
	retValue->name = (char*)malloc(strlen(_name) + 1);
	strcpy(retValue->name, _name);
	switch (_type)
	{
	 case VehicleType::CAR:
		retValue->type = VehicleType::CAR;
		retValue->operation.noMiles = _operation;
		break;
	 case VehicleType::AIRPLANE:
		 retValue->type = VehicleType::AIRPLANE;
		 retValue->operation.flightHours = _operation;
		 break;
	 default:
		 break;
	}
	return retValue;
}

void main()
{
	/*VehicleUsage vu;
	vu.noMiles = 5;
	vu.flightHours = 200.5;
	printf("Integer: %i \n", vu.noMiles);
	printf("Double: %Lf \n", vu.flightHours);*/
	
	//vector de pointeri de tip vehicul
	//1. matrice cu elemente de tip vehicul //2 dimensiuni
	//2. vector de pointeri de tip vehicul //1 dimensiune
	//3. pointer la un alt pointer de tip vehicul //scalar
	
	//vector alocat static [] --> Vehicle* vehicles[4];

	Vehicle** vehicles = NULL;
	FILE* pFile = NULL;
	pFile = fopen("S03Data.txt", "r");
	int noEl = 0;
	int index = 0;
	if (pFile)
	{
		//citire vehicule din fisier 
		fscanf(pFile, "%i", &noEl);
		vehicles = (Vehicle**)malloc(noEl * sizeof(Vehicle*));
		char buffer[50];
		int type = 0;
		double operation = 0;
		while (!feof(pFile))
		{
			fscanf(pFile, "%s", buffer);
			fscanf(pFile, "%i", &type);
			fscanf(pFile, "%Lf", &operation);
			Vehicle* vehicle = buildVehicle(buffer, type, operation);
			vehicles[index++] = vehicle;
		}
		fclose(pFile);

		for (int i = 0; i < noEl; i++)
		{
			printf("Vehicle name: %s \n", vehicles[i]->name);
			switch (vehicles[i]->type)
			{
			case VehicleType::CAR:
				printf("Vehicle usage: %i \n", vehicles[i]->operation.noMiles);
				break;
			case VehicleType::AIRPLANE:
				printf("Vehicle usage: %i \n", vehicles[i]->operation.flightHours);
				break;
			default:
				break;
			}
		}
	}
	
}