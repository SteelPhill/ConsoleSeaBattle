#pragma once

#include <iostream>
#include "MenusAndActions.h"
#include "BeginFillField.h"
#include "PrintPlayField.h"
#include "Shooting.h"
#include "SaveAndLoad.h"
using namespace std;


//ПРОВЕРКА НА ПОБЕДУ
bool IsGameOver(char field[Rows][Columns])
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			if (field[i][j] == Ship)
				return false;

	return true;
}

//ВЫБОР СПОСОБА РАССТАНОВКИ КОРАБЛЕЙ
bool TryChooseShipsPlacementOption(char playerField[Rows][Columns])
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

//ХОД ИГРОКА ИЛИ КОМПЬЮТЕРА
bool TryMove(
	const ModeMenuItems gameMode,
	const DifficultyMenuItems difficulty,
	char targedField[Rows][Columns],
	char shooterField[Rows][Columns],
	const Cell& targedShot,
	Cell& shooterShot,
	PlayerData& targedData,
	PlayerData& shooterData)
{
	shooterData.isMove = true;
	targedData.isMove = false;

	do
	{
		if (shooterData.isPlayer || shooterData.isEasyAI)
			shooterShot.result.isKilled = true;

		if (shooterData.isPlayer)
			PlayerShooting(targedField, shooterShot);
		else
			AIShooting(targedField, shooterShot);

		if (shooterData.isPlayer || targedData.isFirstAI)
			PrintBattlefield(targedField, shooterField, shooterShot, shooterData.name, targedData, shooterData);
		else if (targedData.isPlayer || shooterData.isFirstAI)
			PrintBattlefield(shooterField, targedField, shooterShot, shooterData.name, shooterData, targedData);

		if (IsGameOver(targedField))
		{
			system("pause");
			system("cls");
			PrintTheWinner(shooterData.name);
			return false;
		}

		bool isOpenPauseMenu = false;
		bool isContinueGame = false;

		do
		{
			isOpenPauseMenu = IsOpenPauseMenu();

			if (isOpenPauseMenu)
			{
				isContinueGame = TryChoicePauseMenuOptions(gameMode, difficulty, targedField, shooterField, targedShot, shooterShot, targedData, shooterData);

				if (!isContinueGame)
					return false;
			}

		} while (isOpenPauseMenu);

	} while (shooterShot.result.isHit);

	return true;
}

//ВЫБРАННЫЙ РЕЖИМ ИГРЫ
void SelectedMode(
	const bool isNewGame,
	const ModeMenuItems gameMode,
	const DifficultyMenuItems difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	Cell& firstPlayerShot,
	Cell& secondPlayerShot,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	const string noOneShot = "";

	bool isGameContinue;

	if (isNewGame)
	{
		if (firstPlayerData.isPlayer)
		{
			isGameContinue = TryChooseShipsPlacementOption(firstPlayerField);
			if (!isGameContinue)
				return;

			AutoFillField(secondPlayerField);

			secondPlayerShot.result.isKilled = true;

			cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
			PrintBattlefield(secondPlayerField, firstPlayerField, firstPlayerShot, noOneShot, secondPlayerData, firstPlayerData);
		}
		else if (secondPlayerData.isPlayer)
		{
			firstPlayerData.name.swap(secondPlayerData.name);

			isGameContinue = TryChooseShipsPlacementOption(secondPlayerField);
			if (!isGameContinue)
				return;

			AutoFillField(firstPlayerField);

			firstPlayerShot.result.isKilled = true;

			cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
			PrintBattlefield(firstPlayerField, secondPlayerField, firstPlayerShot, noOneShot, firstPlayerData, secondPlayerData);
		}
		else
		{
			AutoFillField(firstPlayerField);
			AutoFillField(secondPlayerField);

			firstPlayerShot.result.isKilled = true;
			secondPlayerShot.result.isKilled = true;

			cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
			PrintBattlefield(firstPlayerField, secondPlayerField, firstPlayerShot, noOneShot, firstPlayerData, secondPlayerData);
		}
	}
	else
	{
		cout << "\t\t\t      " << "Загруженное поле" << endl << endl;
		PrintBattlefield(firstPlayerField, secondPlayerField, firstPlayerShot, noOneShot, firstPlayerData, secondPlayerData);
	}

	system("pause");
	system("cls");

	do
	{
		isGameContinue = TryMove(gameMode, difficulty, secondPlayerField, firstPlayerField, secondPlayerShot, firstPlayerShot, secondPlayerData, firstPlayerData);
		if (!isGameContinue)
			return;

		isGameContinue = TryMove(gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerShot, secondPlayerShot, firstPlayerData, secondPlayerData);
		if (!isGameContinue)
			return;

	} while (true);
}