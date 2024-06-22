#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define Rows 12
#define Columns 12
#define Ship 'S'
#define Empty ' '
#define Miss '.'
#define Hit '+'
#define Killed 'X'

struct ShootResult
{
	int x;
	int y;
	bool isHit;
	bool isKilled;
};

#include "ShowPlayField.h"
#include "TryReadValue.h"
#include "Menu.h"
#include "BeginFillFieldForComputer.h"
#include "HitAndKillAndWinChecks.h"
#include "TryKillShip.h"
#include "ComputerShooting.h"


//РЕЖИМ: ПРОСТОЙ КОМПЬЮТЕР ПРОТИВ ПРОСТОГО КОМПЬЮТЕРА
void EasyComputerVsEasyComputer()
{
	const string nameComputer1 = "Компьютер 1";
	const string nameComputer2 = "Компьютер 2";

	char fieldComputer1[Rows][Columns];
	FillBattleField(fieldComputer1);

	char fieldComputer2[Rows][Columns];
	FillBattleField(fieldComputer2);

	ShootResult  shootComputer1;
	ShootResult  shootComputer2;

	for (int i = 1; ; i++)
	{

		do
		{
			PrintRoundNumberAndWhoseMove(i, nameComputer1);

			shootComputer1.isKilled = true;
			shootComputer1 = ComputerShooting(fieldComputer2, shootComputer1);

			PrintBothBattlefields(fieldComputer1, fieldComputer2, nameComputer1, nameComputer2);

			if (isGameOver(fieldComputer2))
			{
				cout << "Победа: " << nameComputer1 << endl;
				cout << "Игра окончена!" << endl << endl;
				return;
			}
		} while (shootComputer1.isHit);

		do
		{
			PrintRoundNumberAndWhoseMove(i, nameComputer2);

			shootComputer2.isKilled = true;
			shootComputer2 = ComputerShooting(fieldComputer1, shootComputer2);

			PrintBothBattlefields(fieldComputer1, fieldComputer2, nameComputer1, nameComputer2);

			if (isGameOver(fieldComputer1))
			{
				cout << "Победа: " << nameComputer2 << endl;
				cout << "Игра окончена!" << endl << endl;
				return;
			}
		} while (shootComputer2.isHit);
	}
}

//РЕЖИМ: СЛОЖНЫЙ КОМПЬЮТЕР ПРОТИВ СЛОЖНОГО КОМПЬЮТЕРА
void HardComputerVsHardComputer()
{
	const string nameComputer1 = "Компьютер 1";
	const string nameComputer2 = "Компьютер 2";

	char fieldComputer1[Rows][Columns];
	FillBattleField(fieldComputer1);

	char fieldComputer2[Rows][Columns];
	FillBattleField(fieldComputer2);

	ShootResult  shootComputer1;
	shootComputer1.isKilled = true;

	ShootResult  shootComputer2;
	shootComputer2.isKilled = true;

	for (int i = 1; ; i++)
	{
		shootComputer1.isHit = false;

		do
		{
			PrintRoundNumberAndWhoseMove(i, nameComputer1);

			shootComputer1 = ComputerShooting(fieldComputer2, shootComputer1);

			PrintBothBattlefields(fieldComputer1, fieldComputer2, nameComputer1, nameComputer2);

			if (isGameOver(fieldComputer2))
			{
				cout << "Победа: " << nameComputer1 << endl;
				cout << "Игра окончена!" << endl << endl;
				return;
			}
		} while (shootComputer1.isHit);

		do
		{
			PrintRoundNumberAndWhoseMove(i, nameComputer2);

			shootComputer2 = ComputerShooting(fieldComputer1, shootComputer2);

			PrintBothBattlefields(fieldComputer1, fieldComputer2, nameComputer1, nameComputer2);

			if (isGameOver(fieldComputer1))
			{
				cout << "Победа: " << nameComputer2 << endl;
				cout << "Игра окончена!" << endl << endl;
				return;
			}
		} while (shootComputer2.isHit);
	}
}

//MAIN()
void main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	MainMenuItems gameMode = MainMenu();
	DifficultySelectionMenuItems difficulty = DifficultySelectionMenu();

	switch (gameMode)
	{
	case MainMenuItems::PlayerVsComputer:
	{
		switch (difficulty)
		{
		case DifficultySelectionMenuItems::Easy:

			break;

		case DifficultySelectionMenuItems::Hard:

			break;

		default:
			break;
		}
		break;
	}

	case MainMenuItems::ComputerVsComputer:
	{
		switch (difficulty)
		{
		case DifficultySelectionMenuItems::Easy:
			EasyComputerVsEasyComputer();
			break;

		case DifficultySelectionMenuItems::Hard:
			HardComputerVsHardComputer();
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