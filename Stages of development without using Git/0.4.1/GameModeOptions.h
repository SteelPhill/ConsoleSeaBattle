#pragma once

#include <iostream>
#include "InputDataFromConsole.h"
#include "BeginFillField.h"
#include "OutputDataToConsole.h"
#include "Shooting.h"
using namespace std;


//ПРОВЕРКА НА ПОБЕДУ
bool isGameOver(char field[Rows][Columns])
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			if (field[i][j] == Ship)
				return false;

	return true;
}

//РЕЖИМ: ИГРОК ПРОТИВ ПРОСТОГО КОМПЬЮТЕРА
void PlayerVsEasyAI(ShipPlacementVariantsMenuItems placingShipsChosenMethod)
{
	const string playerName = "Игрок";
	const string AIName = "Компьютер";

	char playerField[Rows][Columns];

	switch (placingShipsChosenMethod)
	{
	case ShipPlacementVariantsMenuItems::AutoPlacement:
	{
		AutoFillBattleField(playerField);
		break;
	}
	case ShipPlacementVariantsMenuItems::ManuallyPlacement:
	{
		bool isShipsPlacement;
		isShipsPlacement = TryManuallyFillBattleField(playerField);
		if (!isShipsPlacement)
			return;
		break;
	}
	default:
		break;
	}

	char AIField[Rows][Columns];
	AutoFillBattleField(AIField);

	Cell  playerShot;
	Cell  AIShot;
	AIShot.result.isKilled = true;

	do
	{
		do
		{
			playerShot.result.isKilled = true;
			playerShot = PlayerShooting(AIField, playerShot);

			PrintWhoseMove(playerName);
			PrintPlayerVsAiBattlefield(AIField, playerField, AIName, playerName, playerShot);
			PrintHowManyShipsLeft(playerShot);

			if (isGameOver(AIField))
			{
				PrintTheWinner(playerName);
				return;
			}
		} while (playerShot.result.isHit);

		do
		{
			AIShot.result.isKilled = true;
			AIShot = AIShooting(playerField, AIShot);

			PrintWhoseMove(AIName);
			PrintPlayerVsAiBattlefield(AIField, playerField, AIName, playerName, AIShot);
			PrintHowManyShipsLeft(AIShot);

			if (isGameOver(playerField))
			{
				PrintTheWinner(AIName);
				return;
			}
		} while (AIShot.result.isHit);

	} while (true);
}

//РЕЖИМ: ИГРОК ПРОТИВ СЛОЖНОГО КОМПЬЮТЕРА
void PlayerVsHardAI(ShipPlacementVariantsMenuItems placingShipsChosenMethod)
{
	const string playerName = "Игрок";
	const string aiName = "Компьютер";

	char playerField[Rows][Columns];

	switch (placingShipsChosenMethod)
	{
	case ShipPlacementVariantsMenuItems::AutoPlacement:
	{
		AutoFillBattleField(playerField);
		break;
	}
	case ShipPlacementVariantsMenuItems::ManuallyPlacement:
	{
		bool isShipsPlacement;
		isShipsPlacement = TryManuallyFillBattleField(playerField);
		if (!isShipsPlacement)
			return;
		break;
	}
	default:
		break;
	}

	char AIField[Rows][Columns];
	AutoFillBattleField(AIField);

	Cell  playerShot;
	Cell  AIShot;

	do
	{
		do
		{
			playerShot.result.isKilled = true;
			playerShot = PlayerShooting(AIField, playerShot);

			PrintWhoseMove(playerName);
			PrintPlayerVsAiBattlefield(AIField, playerField, aiName, playerName, playerShot);

			if (isGameOver(AIField))
			{
				PrintTheWinner(playerName);
				return;
			}
		} while (playerShot.result.isHit);

		do
		{
			AIShot = AIShooting(playerField, AIShot);

			PrintWhoseMove(aiName);
			PrintPlayerVsAiBattlefield(AIField, playerField, aiName, playerName, AIShot);

			if (isGameOver(playerField))
			{
				PrintTheWinner(aiName);
				return;
			}
		} while (AIShot.result.isHit);

	} while (true);
}

//РЕЖИМ: ПРОСТОЙ КОМПЬЮТЕР ПРОТИВ ПРОСТОГО КОМПЬЮТЕРА
void EasyAIVsEasyAI()
{
	const string firstAIName = "Компьютер 1";
	const string secondAIName = "Компьютер 2";

	char firstAIField[Rows][Columns];
	AutoFillBattleField(firstAIField);

	char secondAIField[Rows][Columns];
	AutoFillBattleField(secondAIField);

	Cell  firstAIShot;
	Cell  secondAIShot;

	do
	{
		do
		{
			firstAIShot.result.isKilled = true;
			firstAIShot = AIShooting(secondAIField, firstAIShot);

			PrintWhoseMove(firstAIName);
			PrintAiVsAiBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, firstAIShot);

			if (isGameOver(secondAIField))
			{
				PrintTheWinner(firstAIName);
				return;
			}
		} while (firstAIShot.result.isHit);

		do
		{
			secondAIShot.result.isKilled = true;
			secondAIShot = AIShooting(firstAIField, secondAIShot);

			PrintWhoseMove(secondAIName);
			PrintAiVsAiBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, secondAIShot);

			if (isGameOver(firstAIField))
			{
				PrintTheWinner(secondAIName);
				return;
			}
		} while (secondAIShot.result.isHit);

	} while (true);
}

//РЕЖИМ: СЛОЖНЫЙ КОМПЬЮТЕР ПРОТИВ СЛОЖНОГО КОМПЬЮТЕРА
void HardAIVsHardAI()
{
	const string firstAIName = "Компьютер 1";
	const string secondAIName = "Компьютер 2";

	char firstAIField[Rows][Columns];
	AutoFillBattleField(firstAIField);

	char secondAIField[Rows][Columns];
	AutoFillBattleField(secondAIField);

	Cell  firstAIShot;
	firstAIShot.result.isKilled = true;

	Cell  secondAIShot;
	secondAIShot.result.isKilled = true;

	do
	{
		do
		{
			firstAIShot = AIShooting(secondAIField, firstAIShot);

			PrintWhoseMove(firstAIName);
			PrintAiVsAiBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, firstAIShot);

			if (isGameOver(secondAIField))
			{
				PrintTheWinner(firstAIName);
				return;
			}
		} while (firstAIShot.result.isHit);

		do
		{
			secondAIShot = AIShooting(firstAIField, secondAIShot);

			PrintWhoseMove(secondAIName);
			PrintAiVsAiBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, secondAIShot);

			if (isGameOver(firstAIField))
			{
				PrintTheWinner(secondAIName);
				return;
			}
		} while (secondAIShot.result.isHit);

	} while (true);
}