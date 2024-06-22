#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define Rows 10
#define Columns 10
#define ShipPart 'S'
#define EmptyCell ' '
#define Miss '-'
#define Hit 'X'

enum class MainMenuItems
{
	PlayerVsAi = 1,
	AiVsAi = 2,
	Rules = 3
};

enum class SecondMenuItems
{
	Easy = 1,
	Hard = 2
};

struct CellCoordinates
{
	int x;
	int y;
};

#include "BeginFillFieldForComputer.h"
#include "TryReadValue.h"
#include "Menu.h"
#include "ShootCheck.h"
#include "ShowPlayField.h"


//РЕЖИМ: ЛЕГКИЙ КОМПЬЮТЕР ПРОТИВ ЛЕГКОГО КОМПЬЮТЕРА
void EasyComputerVsEasyComputer()
{
	const string firstAiName = "Компьютер 1";
	const string secondAiName = "Компьютер 2";

	char firstAiField[Rows][Columns];
	FillPlayField(firstAiField);

	char secondAiField[Rows][Columns];
	FillPlayField(secondAiField);

	int round = 1;

	while (true)
	{
		bool isHit = false;

		do
		{
			isHit = IsShootHit(secondAiField);
			cout << "Ход: " << firstAiName << endl;
			PrintOpenField(firstAiField, secondAiField, firstAiName, secondAiName, round);

			if (isHit)
				cout << firstAiName << ": попадание!" << endl << endl;
			else
				cout << firstAiName << ": промах." << endl << endl;

			system("pause");
			system("cls");

			if (isGameOver(secondAiField))
			{
				cout << "Победа: " << firstAiName << endl;
				cout << "Игра окончена!" << endl << endl;
				return;
			}
		} while (isHit);

		do
		{
			isHit = IsShootHit(firstAiField);
			cout << "Ход: " << secondAiName << endl;
			PrintOpenField(firstAiField, secondAiField, firstAiName, secondAiName, round);
			
			if (isHit)
				cout << secondAiName << ": попадание!" << endl << endl;
			else
				cout << secondAiName << ": промах." << endl << endl;

			system("pause");
			system("cls");

			if (isGameOver(firstAiField))
			{
				cout << "Победа: " << secondAiName << endl;
				cout << "Игра окончена!" << endl << endl;
				return;
			}
		} while (isHit);

		round++;
	}
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