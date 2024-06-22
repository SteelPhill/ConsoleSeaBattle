#pragma once

#include <iostream>
#include "MenusAndActions.h"
#include "BeginFillField.h"
#include "PrintPlayField.h"
#include "Shooting.h"
#include "SaveAndLoad.h"
using namespace std;


struct PlayerData
{
	bool isPlayer;
	bool isFirstAI;
};


//ПРОВЕРКА НА ПОБЕДУ
bool IsGameOver(char field[Rows][Columns])
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			if (field[i][j] == Ship)
				return false;

	return true;
}

//ПРОВЕРКА, ЗАПОЛНЕНО ЛИ ПОЛЕ ИГРОКА
bool IsPlacementPlayerField(char playerField[Rows][Columns])
{
	switch (ShipPlacementVariantsMenu())
	{
	case ShipPlacementVariantsMenuItems::AutoPlacement:
	{
		AutoFillField(playerField);
		break;
	}
	case ShipPlacementVariantsMenuItems::ManuallyPlacement:
	{
		bool isShipsPlacement;
		isShipsPlacement = TryManuallyFillField(playerField);
		if (!isShipsPlacement)
		{
			system("cls");
			return false;
		}
		break;
	}
	case ShipPlacementVariantsMenuItems::GoToMainMenu:
	{
		return false;
	}
	}

	return true;
}

//СТРЕЛЬБА
bool IsShot(
	ModeMenuItems gameMode,
	DifficultySelectionMenuItems difficulty,
	char targedField[Rows][Columns],
	char shooterField[Rows][Columns],
	Cell& targedShot,
	Cell& shooterShot,
	string& targedName,
	string& shooterName,
	PlayerData& targed,
	PlayerData& shooter,
	const bool isEasyAIOrPlayer)
{
	bool isOpenPauseMenu;
	bool isContinueGame;

	do
	{
		if (isEasyAIOrPlayer)
			shooterShot.result.isKilled = true;

		if(shooter.isPlayer)
			PlayerShooting(targedField, shooterShot);
		else
			AIShooting(targedField, shooterShot);

		if (shooter.isPlayer)
			PrintPlayerVsAIBattlefield(targedField, shooterField, targedName, shooterName, shooterShot, shooterName);
		else if (targed.isPlayer)
			PrintPlayerVsAIBattlefield(shooterField, targedField, shooterName, targedName, shooterShot, shooterName);
		else if (shooter.isFirstAI)
			PrintAIVsAIBattlefield(shooterField, targedField, shooterName, targedName, shooterShot, shooterName);
		else if (targed.isFirstAI)
			PrintAIVsAIBattlefield(targedField, shooterField, targedName, shooterName, shooterShot, shooterName);

		if (IsGameOver(targedField))
		{
			system("pause");
			system("cls");
			PrintTheWinner(shooterName);
			return false;
		}

		do
		{
			isOpenPauseMenu = IsOpenPauseMenu();

			isContinueGame = false;

			if (isOpenPauseMenu)
			{
				do
				{
					switch (PauseMenu())
					{
					case PauseMenuItems::Continue:
					{
						isContinueGame = true;
						break;
					}
					case PauseMenuItems::Save:
					{
						if (targed.isPlayer || shooter.isFirstAI)
							SaveGame(gameMode, difficulty, shooterField, targedField, shooterShot, targedShot, shooterName, targedName);
						else if(targed.isFirstAI || shooter.isPlayer)
							SaveGame(gameMode, difficulty, targedField, shooterField, targedShot, shooterShot, targedName, shooterName);
						continue;
					}
					case PauseMenuItems::GoToMainMenu:
					{
						return false;
					}
					}
				} while (!isContinueGame);

				system("cls");

				if (shooter.isPlayer)
					PrintPlayerVsAIBattlefield(targedField, shooterField, targedName, shooterName, shooterShot, shooterName);
				else if (targed.isPlayer)
					PrintPlayerVsAIBattlefield(shooterField, targedField, shooterName, targedName, shooterShot, shooterName);
				else if (shooter.isFirstAI)
					PrintAIVsAIBattlefield(shooterField, targedField, shooterName, targedName, shooterShot, shooterName);
				else if (targed.isFirstAI)
					PrintAIVsAIBattlefield(targedField, shooterField, targedName, shooterName, shooterShot, shooterName);
			}

		} while (isOpenPauseMenu);

	} while (shooterShot.result.isHit);

	return true;
}

//РЕЖИМ: ИГРОК ПРОТИВ КОМПЬЮТЕРА
void PlayerVsAIMode(
	const bool isNewGame,
	ModeMenuItems gameMode,
	DifficultySelectionMenuItems difficulty,
	char playerField[Rows][Columns],
	char AIField[Rows][Columns],
	Cell& playerShot,
	Cell& AIShot,
	string& playerName,
	string& AIName)
{
	const bool isPlayer = true;

	bool isEasyAI = true;

	if (difficulty == DifficultySelectionMenuItems::Hard)
		isEasyAI = false;

	PlayerData playerData;
	playerData.isPlayer = true;

	PlayerData AIData;
	AIData.isPlayer = false;
	AIData.isFirstAI = false;

	string NoOneShot = "";

	if (isNewGame)
	{
		bool isGoToMainMenu;

		isGoToMainMenu = !IsPlacementPlayerField(playerField);

		if (isGoToMainMenu)
			return;

		AutoFillField(AIField);

		cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
	}
	else
		cout << "\t\t\t      " << "Загруженное поле" << endl << endl;

	PrintPlayerVsAIBattlefield(AIField, playerField, AIName, playerName, playerShot, NoOneShot);
	system("pause");
	system("cls");

	bool isGameOver;

	AIShot.result.isKilled = true;

	do
	{
		isGameOver = !IsShot(gameMode, difficulty, AIField, playerField, AIShot, playerShot, AIName, playerName, AIData, playerData, isPlayer);
		if (isGameOver)
			return;

		isGameOver = !IsShot(gameMode, difficulty, playerField, AIField, playerShot, AIShot, playerName, AIName, playerData, AIData, isEasyAI);
		if (isGameOver)
			return;

	} while (true);
}

//РЕЖИМ: КОМПЬЮТЕР ПРОТИВ КОМПЬЮТЕРА
void AIVsAIMode(
	const bool isNewGame,
	ModeMenuItems gameMode,
	DifficultySelectionMenuItems difficulty,
	char firstAIField[Rows][Columns],
	char secondAIField[Rows][Columns],
	Cell& firstAIShot,
	Cell& secondAIShot,
	string& firstAIName,
	string& secondAIName)
{
	bool isEasyAIs = true;

	if (difficulty == DifficultySelectionMenuItems::Hard)
		isEasyAIs = false;

	PlayerData firstAIData;
	firstAIData.isPlayer = false;
	firstAIData.isFirstAI = true;

	PlayerData secondAIData;
	secondAIData.isPlayer = false;
	secondAIData.isFirstAI = false;

	string NoOneShot = "";

	if (isNewGame)
	{
		AutoFillField(firstAIField);
		AutoFillField(secondAIField);

		cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
	}
	else
		cout << "\t\t\t      " << "Загруженное поле" << endl << endl;

	PrintAIVsAIBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, firstAIShot, NoOneShot);
	system("pause");
	system("cls");

	bool isGameOver;

	firstAIShot.result.isKilled = true;
	secondAIShot.result.isKilled = true;

	do
	{
		isGameOver = !IsShot(gameMode, difficulty, secondAIField, firstAIField, secondAIShot, firstAIShot, secondAIName, firstAIName, secondAIData, firstAIData, isEasyAIs);
		if (isGameOver)
			return;

		isGameOver = !IsShot(gameMode, difficulty, firstAIField, secondAIField, firstAIShot, secondAIShot, firstAIName, secondAIName, firstAIData, secondAIData, isEasyAIs);
		if (isGameOver)
			return;

	} while (true);
}