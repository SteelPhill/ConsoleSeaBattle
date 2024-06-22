#define Rows 12
#define Columns 12
#define Ship '#'
#define Empty ' '
#define Miss '*'
#define Hit '+'
#define Killed 'X'

struct ShotResult
{
	int x;
	int y;
	bool isHit;
	bool isKilled;
};

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include "ShowPlayField.h"
#include "TryReadValue.h"
#include "Menu.h"
#include "BeginFillField.h"
#include "Hit-Kill-WinChecks.h"
#include "TryKillShip.h"
#include "ComputerShooting.h"
#include "PlayerShooting.h"
#include <Windows.h>


//РЕЖИМ: ИГРОК ПРОТИВ ПРОСТОГО КОМПЬЮТЕРА
inline void PlayerVsEasyComputer()
{
	const string playerName = "Игрок";
	const string computerName = "Компьютер";

	char playerField[Rows][Columns];
	FillBattleField(playerField);

	char computerField[Rows][Columns];
	FillBattleField(computerField);

	ShotResult  shotPlayer;
	ShotResult  shotComputer;
	shotComputer.isKilled = true;

	do
	{
		do
		{
			shotPlayer.isKilled = true;
			shotPlayer = PlayerShooting(computerField, shotPlayer);

			PrintWhoseMove(playerName);
			PrintPlayerVsComputerBattlefield(computerField, playerField, computerName, playerName, shotPlayer);

			if (isGameOver(computerField))
			{
				PrintTheWinner(playerName);
				return;
			}
		} while (shotPlayer.isHit);

		do
		{
			shotComputer.isKilled = true;
			shotComputer = ComputerShooting(playerField, shotComputer);

			PrintWhoseMove(computerName);
			PrintPlayerVsComputerBattlefield(computerField, playerField, computerName, playerName, shotComputer);

			if (isGameOver(playerField))
			{
				PrintTheWinner(computerName);
				return;
			}
		} while (shotComputer.isHit);

	} while (true);
}

//РЕЖИМ: ИГРОК ПРОТИВ СЛОЖНОГО КОМПЬЮТЕРА
inline void PlayerVsHardComputer()
{
	const string playerName = "Игрок";
	const string computerName = "Компьютер";

	char playerField[Rows][Columns];
	FillBattleField(playerField);

	char computerField[Rows][Columns];
	FillBattleField(computerField);

	ShotResult  shotPlayer;
	ShotResult  shotComputer;

	do
	{
		do
		{
			shotPlayer.isKilled = true;
			shotPlayer = PlayerShooting(computerField, shotPlayer);

			PrintWhoseMove(playerName);
			PrintPlayerVsComputerBattlefield(computerField, playerField, computerName, playerName, shotPlayer);

			if (isGameOver(computerField))
			{
				PrintTheWinner(playerName);
				return;
			}
		} while (shotPlayer.isHit);

		do
		{
			shotComputer = ComputerShooting(playerField, shotComputer);

			PrintWhoseMove(computerName);
			PrintPlayerVsComputerBattlefield(computerField, playerField, computerName, playerName, shotComputer);

			if (isGameOver(playerField))
			{
				PrintTheWinner(computerName);
				return;
			}
		} while (shotComputer.isHit);

	} while (true);
}

//РЕЖИМ: ПРОСТОЙ КОМПЬЮТЕР ПРОТИВ ПРОСТОГО КОМПЬЮТЕРА
inline void EasyComputerVsEasyComputer()
{
	const string firstComputerName = "Компьютер 1";
	const string secondComputerName = "Компьютер 2";

	char firstComputerField[Rows][Columns];
	FillBattleField(firstComputerField);

	char secondComputerField[Rows][Columns];
	FillBattleField(secondComputerField);

	ShotResult  shotFirstComputer;
	ShotResult  shotSecondComputer;

	do
	{
		do
		{
			shotFirstComputer.isKilled = true;
			shotFirstComputer = ComputerShooting(secondComputerField, shotFirstComputer);

			PrintWhoseMove(firstComputerName);
			PrintComputerVsComputerBattlefield(firstComputerField, secondComputerField, firstComputerName, secondComputerName, shotFirstComputer);

			if (isGameOver(secondComputerField))
			{
				PrintTheWinner(firstComputerName);
				return;
			}
		} while (shotFirstComputer.isHit);

		do
		{
			shotSecondComputer.isKilled = true;
			shotSecondComputer = ComputerShooting(firstComputerField, shotSecondComputer);

			PrintWhoseMove(secondComputerName);
			PrintComputerVsComputerBattlefield(firstComputerField, secondComputerField, firstComputerName, secondComputerName, shotSecondComputer);

			if (isGameOver(firstComputerField))
			{
				PrintTheWinner(secondComputerName);
				return;
			}
		} while (shotSecondComputer.isHit);

	} while (true);
}

//РЕЖИМ: СЛОЖНЫЙ КОМПЬЮТЕР ПРОТИВ СЛОЖНОГО КОМПЬЮТЕРА
inline void HardComputerVsHardComputer()
{
	const string firstComputerName = "Компьютер 1";
	const string secondComputerName = "Компьютер 2";

	char firstComputerField[Rows][Columns];
	FillBattleField(firstComputerField);

	char secondComputerField[Rows][Columns];
	FillBattleField(secondComputerField);

	ShotResult  shotFirstComputer;
	shotFirstComputer.isKilled = true;

	ShotResult  shotSecondComputer;
	shotSecondComputer.isKilled = true;

	do
	{
		do
		{
			shotFirstComputer = ComputerShooting(secondComputerField, shotFirstComputer);

			PrintWhoseMove(firstComputerName);
			PrintComputerVsComputerBattlefield(firstComputerField, secondComputerField, firstComputerName, secondComputerName, shotFirstComputer);

			if (isGameOver(secondComputerField))
			{
				PrintTheWinner(firstComputerName);
				return;
			}
		} while (shotFirstComputer.isHit);

		do
		{
			shotSecondComputer = ComputerShooting(firstComputerField, shotSecondComputer);

			PrintWhoseMove(secondComputerName);
			PrintComputerVsComputerBattlefield(firstComputerField, secondComputerField, firstComputerName, secondComputerName, shotSecondComputer);

			if (isGameOver(firstComputerField))
			{
				PrintTheWinner(secondComputerName);
				return;
			}
		} while (shotSecondComputer.isHit);

	} while (true);
}

//MAIN()
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
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
			PlayerVsEasyComputer();
			break;

		case DifficultySelectionMenuItems::Hard:
			PlayerVsHardComputer();
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