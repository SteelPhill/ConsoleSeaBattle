#include <iostream>
#include <ctime>
#include "shipPlacementForComputers.h"
using namespace std;


//ЗАПОЛНЕНИЕ ПОЛЯ ПРОБЕЛАМИ
void FillFieldToSpaces(char playField[10][10], const int rows, const int columns)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			playField[i][j] = ' ';
}



//ПЕЧАТЬ БУКВ ДЛЯ ОБОЗНАЧЕНИЯ СТОЛБЦОВ
void PrintLetter()
{
	cout << "  ";
	for (unsigned char c = 224; c <= 234; c++)
		if (c != 233)
			cout << " " << c << " ";
	cout << endl;
}

//ПЕЧАТЬ ПОЛЯ - В РАЗРАБОТКЕ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void PrintField(char field[10][10], const int rows, const int columns)
{
	PrintLetter();

	for (int i = 0; i < rows; i++)
	{
		if (i == 9)
			cout << i + 1;
		else
			cout << " " << i + 1;

		for (int j = 0; j < columns; j++)
			cout << "[" << field[i][j] << "]";
		cout << endl;
	}

	cout << endl;
}

//MAIN()
void main()
{
	const int Rows = 10;
	const int Columns = 10;
	const int OneDeckSize = 1;
	const int TwoDeckSize = 2;
	const int ThreeDeckSize = 3;
	const int FourDeckSize = 4;

	setlocale(LC_ALL, "ru");
	srand(time(0));

	char playField[Rows][Columns];

	FillFieldToSpaces(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, FourDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, ThreeDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, ThreeDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, TwoDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, TwoDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, TwoDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, OneDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, OneDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, OneDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, OneDeckSize);
	//PrintField(playField, Rows, Columns);

	PrintField(playField, Rows, Columns);

	system("pause");
}