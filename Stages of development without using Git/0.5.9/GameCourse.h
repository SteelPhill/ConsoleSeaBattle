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
	ModeMenuItems gameMode,
	DifficultyMenuItems difficulty,
	char targedField[Rows][Columns],
	char shooterField[Rows][Columns],
	Cell& targedShot,
	Cell& shooterShot,
	PlayerData& targedData,
	PlayerData& shooterData)
{
	bool isOpenPauseMenu;
	bool isContinueGame;

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

		if (shooterData.isPlayer)
			PrintBattlefield(targedField, shooterField, shooterShot, shooterData.name, targedData, shooterData);
		else if (targedData.isPlayer)
			PrintBattlefield(shooterField, targedField, shooterShot, shooterData.name, shooterData, targedData);
		else if (shooterData.isFirstAI)
			PrintBattlefield(shooterField, targedField, shooterShot, shooterData.name, shooterData, targedData);
		else if (targedData.isFirstAI)
			PrintBattlefield(targedField, shooterField, shooterShot, shooterData.name, targedData, shooterData);

		if (IsGameOver(targedField))
		{
			system("pause");
			system("cls");
			PrintTheWinner(shooterData.name);
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
						system("cls");
						if (targedData.isPlayer || shooterData.isFirstAI)
						{
							SaveGame(gameMode, difficulty, shooterField, targedField, shooterShot, targedShot, shooterData, targedData);
						}
						else if (targedData.isFirstAI || shooterData.isPlayer)
						{
							SaveGame(gameMode, difficulty, targedField, shooterField, targedShot, shooterShot, targedData, shooterData);
						}
						continue;
					}
					case PauseMenuItems::GoToMainMenu:
					{
						system("cls");
						return false;
					}
					}
				} while (!isContinueGame);

				system("cls");

				if (shooterData.isPlayer)
					PrintBattlefield(targedField, shooterField, shooterShot, shooterData.name, targedData, shooterData);
				else if (targedData.isPlayer)
					PrintBattlefield(shooterField, targedField, shooterShot, shooterData.name, shooterData, targedData);
				else if (shooterData.isFirstAI)
					PrintBattlefield(shooterField, targedField, shooterShot, shooterData.name, shooterData, targedData);
				else if (targedData.isFirstAI)
					PrintBattlefield(targedField, shooterField, shooterShot, shooterData.name, targedData, shooterData);
			}

		} while (isOpenPauseMenu);

	} while (shooterShot.result.isHit);

	return true;
}

//ВЫБРАННЫЙ РЕЖИМ ИГРЫ
void SelectedMode(
	const bool isNewGame,
	ModeMenuItems gameMode,
	DifficultyMenuItems difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	Cell& firstPlayerShot,
	Cell& secondPlayerShot,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	string NoOneShot = "";

	if (isNewGame)
	{
		bool isGoToMainMenu;

		if (firstPlayerData.isPlayer || secondPlayerData.isPlayer)
		{
			if (firstPlayerData.isPlayer)
			{
				isGoToMainMenu = !TryChooseShipsPlacementOption(firstPlayerField);
				if (isGoToMainMenu)
					return;
				AutoFillField(secondPlayerField);

				secondPlayerShot.result.isKilled = true;

				cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
				PrintBattlefield(secondPlayerField, firstPlayerField, firstPlayerShot, NoOneShot, secondPlayerData, firstPlayerData);
				system("pause");
				system("cls");
			}
			else if (secondPlayerData.isPlayer)
			{
				firstPlayerData.name.swap(secondPlayerData.name);

				isGoToMainMenu = !TryChooseShipsPlacementOption(secondPlayerField);
				if (isGoToMainMenu)
					return;
				AutoFillField(firstPlayerField);

				firstPlayerShot.result.isKilled = true;

				cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
				PrintBattlefield(firstPlayerField, secondPlayerField, firstPlayerShot, NoOneShot, firstPlayerData, secondPlayerData);
				system("pause");
				system("cls");
			}
		}
		else
		{
			AutoFillField(firstPlayerField);
			AutoFillField(secondPlayerField);

			firstPlayerShot.result.isKilled = true;
			secondPlayerShot.result.isKilled = true;

			cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
			PrintBattlefield(firstPlayerField, secondPlayerField, firstPlayerShot, NoOneShot, firstPlayerData, secondPlayerData);
			system("pause");
			system("cls");
		}
	}
	else
	{
		cout << "\t\t\t      " << "Загруженное поле" << endl << endl;
		PrintBattlefield(firstPlayerField, secondPlayerField, firstPlayerShot, NoOneShot, firstPlayerData, secondPlayerData);
		system("pause");
		system("cls");
	}

	bool isGameOver;

	do
	{
		isGameOver = !TryMove(gameMode, difficulty, secondPlayerField, firstPlayerField, secondPlayerShot, firstPlayerShot, secondPlayerData, firstPlayerData);
		if (isGameOver)
			return;
		
		isGameOver = !TryMove(gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerShot, secondPlayerShot, firstPlayerData, secondPlayerData);
		if (isGameOver)
			return;

	} while (true);
}