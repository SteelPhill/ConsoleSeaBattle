#define Rows 10
#define Columns 10
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include "PlacingShipsOnField.h"
#include "TryReadValue.h"
#include "Menu.h"
using namespace std;


//ПЕЧАТЬ ПОЛЯ - В РАЗРАБОТКЕ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void PrintField(char field[Rows][Columns])
{
	cout << "  ";
	for (unsigned char c = 224; c <= 234; c++)
		if (c != 233)
			cout << " " << c << " ";
	cout << endl;

	for (int i = 0; i < Rows; i++)
	{
		if (i == 9)
			cout << i + 1;
		else
			cout << " " << i + 1;

		for (int j = 0; j < Columns; j++)
			cout << "[" << field[i][j] << "]";
		cout << endl;
	}

	cout << endl;
}


//РЕЖИМ: ЛЕГКИЙ КОМПЬЮТЕР ПРОТИВ ЛЕГКОГО КОМПЬЮТЕРА
void EasyComputerVsEasyComputer()
{
	char firstAi[Rows][Columns];
	FillPlayField(firstAi);

	char secondAi[Rows][Columns];
	FillPlayField(secondAi);

	PrintField(firstAi);
	cout << endl;
	PrintField(secondAi);

}


//MAIN()
void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	MainMenuItems gameMode = MainMenu();
	SecondMenuItems difficulty = SecondMenu();

	switch (gameMode)
	{
	case MainMenuItems::PlayerVsAi:
	{
		switch (difficulty)
		{
		case SecondMenuItems::Easy:

			break;
		case SecondMenuItems::Hard:

			break;
		default:
			break;
		}
		break;
	}
	case MainMenuItems::AiVsAi:
	{
		switch (difficulty)
		{
		case SecondMenuItems::Easy:
			EasyComputerVsEasyComputer();
			break;
		case SecondMenuItems::Hard:

			break;
		default:
			break;
		}
		break;
	}
	case MainMenuItems::Rules:

		break;
	default:
		break;
	}

	system("pause");
}