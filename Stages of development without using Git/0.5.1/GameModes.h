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
bool isGameOver(char field[Rows][Columns])
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			if (field[i][j] == Ship)
				return false;

	return true;
}

//ХОД ИГРОКА ИЛИ КОМПЬЮТЕРА
void PlayerOrAITurn(
	char targedPlayerField[Rows][Columns],
	char shooterPlayerField[Rows][Columns], 
	const string& targedPlayerName,
	const string& shooterPlayerName,
	Cell& shot, 
	PlayerData& targed, 
	PlayerData& shooter)
{
	if (shooter.isPlayer)
	{
		PlayerShooting(targedPlayerField, shot);
		PrintPlayerVsAIBattlefield(targedPlayerField, shooterPlayerField, targedPlayerName, shooterPlayerName, shot, shooterPlayerName);
	}

	else if (targed.isPlayer)
	{
		AIShooting(targedPlayerField, shot);
		PrintPlayerVsAIBattlefield(shooterPlayerField, targedPlayerField, shooterPlayerName, targedPlayerName, shot, shooterPlayerName);
	}

	else if (shooter.isFirstAI)
	{
		AIShooting(targedPlayerField, shot);
		PrintAIVsAIBattlefield(shooterPlayerField, targedPlayerField, shooterPlayerName, targedPlayerName, shot, shooterPlayerName);
	}

	else
	{
		AIShooting(targedPlayerField, shot);
		PrintAIVsAIBattlefield(targedPlayerField, shooterPlayerField, targedPlayerName, shooterPlayerName, shot, shooterPlayerName);
	}
}

//РЕЖИМ: ИГРОК ПРОТИВ ПРОСТОГО КОМПЬЮТЕРА
void PlayerVsEasyAI(
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
	PlayerData playerData;
	playerData.isPlayer = true;

	PlayerData AIData;
	AIData.isPlayer = false;
	AIData.isFirstAI = false;

	if (isNewGame)
	{
		switch (ShipPlacementVariantsMenu())
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
			{
				system("cls");
				return;
			}
			break;
		}
		case ShipPlacementVariantsMenuItems::GoToMainMenu:
		{
			return;
		}
		}

		AutoFillBattleField(AIField);

		const string NoOneShot = "";

		cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
		PrintPlayerVsAIBattlefield(AIField, playerField, AIName, playerName, playerShot, NoOneShot);
		system("pause");
		system("cls");
	}

	bool isOpenPauseMenu;
	bool isContinueGame;

	do
	{
		do
		{
			playerShot.result.isKilled = true;

			PlayerOrAITurn(AIField, playerField, AIName, playerName, playerShot, AIData, playerData);

			if (isGameOver(AIField))
			{
				system("pause");
				system("cls");
				PrintTheWinner(playerName);
				return;
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
							isContinueGame = true;
							break;
						case PauseMenuItems::Save:
							SaveGame(gameMode, difficulty, playerField, AIField, playerShot, AIShot, playerName, AIName);
							continue;
						case PauseMenuItems::GoToMainMenu:
							return;
						}
					} while (!isContinueGame);

					system("cls");

					PrintPlayerVsAIBattlefield(AIField, playerField, AIName, playerName, playerShot, playerName);
				}

			} while (isOpenPauseMenu);

		} while (playerShot.result.isHit);

		do
		{
			AIShot.result.isKilled = true;

			PlayerOrAITurn(playerField, AIField, playerName, AIName, AIShot, playerData, AIData);

			if (isGameOver(playerField))
			{
				system("pause");
				system("cls");
				PrintTheWinner(AIName);
				return;
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
							isContinueGame = true;
							break;
						case PauseMenuItems::Save:
							SaveGame(gameMode, difficulty, playerField, AIField, playerShot, AIShot, playerName, AIName);
							continue;
						case PauseMenuItems::GoToMainMenu:
							return;
						}
					} while (!isContinueGame);

					system("cls");

					PrintPlayerVsAIBattlefield(AIField, playerField, AIName, playerName, AIShot, AIName);
				}

			} while (isOpenPauseMenu);

		} while (AIShot.result.isHit);

	} while (true);
}

//РЕЖИМ: ИГРОК ПРОТИВ СЛОЖНОГО КОМПЬЮТЕРА
void PlayerVsHardAI(
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
	PlayerData playerData;
	playerData.isPlayer = true;

	PlayerData AIData;
	AIData.isPlayer = false;
	AIData.isFirstAI = false;

	if (isNewGame)
	{
		switch (ShipPlacementVariantsMenu())
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
			{
				system("cls");
				return;
			}
			break;
		}
		case ShipPlacementVariantsMenuItems::GoToMainMenu:
		{
			return;
		}
		}

		AutoFillBattleField(AIField);

		const string NoOneShot = "";

		cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
		PrintPlayerVsAIBattlefield(AIField, playerField, AIName, playerName, playerShot, NoOneShot);
		system("pause");
		system("cls");
	}

	AIShot.result.isKilled = true;

	bool isOpenPauseMenu;
	bool isContinueGame;

	do
	{
		do
		{
			playerShot.result.isKilled = true;

			PlayerOrAITurn(AIField, playerField, AIName, playerName, playerShot, AIData, playerData);

			if (isGameOver(AIField))
			{
				system("pause");
				system("cls");
				PrintTheWinner(playerName);
				return;
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
							isContinueGame = true;
							break;
						case PauseMenuItems::Save:
							SaveGame(gameMode, difficulty, playerField, AIField, playerShot, AIShot, playerName, AIName);
							continue;
						case PauseMenuItems::GoToMainMenu:
							return;
						}
					} while (!isContinueGame);

					system("cls");

					PrintPlayerVsAIBattlefield(AIField, playerField, AIName, playerName, playerShot, playerName);
				}

			} while (isOpenPauseMenu);

		} while (playerShot.result.isHit);

		do
		{
			PlayerOrAITurn(playerField, AIField, playerName, AIName, AIShot, playerData, AIData);

			if (isGameOver(playerField))
			{
				system("pause");
				system("cls");
				PrintTheWinner(AIName);
				return;
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
							isContinueGame = true;
							break;
						case PauseMenuItems::Save:
							SaveGame(gameMode, difficulty, playerField, AIField, playerShot, AIShot, playerName, AIName);
							continue;
						case PauseMenuItems::GoToMainMenu:
							return;
						}
					} while (!isContinueGame);

					system("cls");

					PrintPlayerVsAIBattlefield(AIField, playerField, AIName, playerName, AIShot, AIName);
				}

			} while (isOpenPauseMenu);

		} while (AIShot.result.isHit);

	} while (true);
}

//РЕЖИМ: ПРОСТОЙ КОМПЬЮТЕР ПРОТИВ ПРОСТОГО КОМПЬЮТЕРА
void EasyAIVsEasyAI(const bool isNewGame,
	ModeMenuItems gameMode,
	DifficultySelectionMenuItems difficulty,
	char firstAIField[Rows][Columns],
	char secondAIField[Rows][Columns],
	Cell& firstAIShot,
	Cell& secondAIShot,
	string& firstAIName,
	string& secondAIName)
{
	PlayerData firstAIData;
	firstAIData.isPlayer = false;
	firstAIData.isFirstAI = true;

	PlayerData secondAIData;
	secondAIData.isPlayer = false;
	secondAIData.isFirstAI = false;

	if (isNewGame)
	{
		AutoFillBattleField(firstAIField);
		AutoFillBattleField(secondAIField);

		const string NoOneShot = "";

		cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
		PrintAIVsAIBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, firstAIShot, NoOneShot);
		system("pause");
		system("cls");
	}

	bool isOpenPauseMenu;
	bool isContinueGame;

	do
	{
		do
		{
			firstAIShot.result.isKilled = true;

			PlayerOrAITurn(secondAIField, firstAIField, secondAIName, firstAIName, firstAIShot, secondAIData, firstAIData);

			if (isGameOver(secondAIField))
			{
				system("pause");
				system("cls");
				PrintTheWinner(firstAIName);
				return;
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
							isContinueGame = true;
							break;
						case PauseMenuItems::Save:
							SaveGame(gameMode, difficulty, firstAIField, secondAIField, firstAIShot, secondAIShot, firstAIName, secondAIName);
							continue;
						case PauseMenuItems::GoToMainMenu:
							return;
						}
					} while (!isContinueGame);

					system("cls");

					PrintAIVsAIBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, firstAIShot, firstAIName);
				}

			} while (isOpenPauseMenu);

		} while (firstAIShot.result.isHit);

		do
		{
			secondAIShot.result.isKilled = true;

			PlayerOrAITurn(firstAIField, secondAIField, firstAIName, secondAIName, secondAIShot, firstAIData, secondAIData);

			if (isGameOver(firstAIField))
			{
				system("pause");
				system("cls");
				PrintTheWinner(secondAIName);
				return;
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
							isContinueGame = true;
							break;
						case PauseMenuItems::Save:
							SaveGame(gameMode, difficulty, firstAIField, secondAIField, firstAIShot, secondAIShot, firstAIName, secondAIName);
							continue;
						case PauseMenuItems::GoToMainMenu:
							return;
						}
					} while (!isContinueGame);

					system("cls");

					PrintAIVsAIBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, secondAIShot, secondAIName);
				}

			} while (isOpenPauseMenu);

		} while (secondAIShot.result.isHit);

	} while (true);
}

//РЕЖИМ: СЛОЖНЫЙ КОМПЬЮТЕР ПРОТИВ СЛОЖНОГО КОМПЬЮТЕРА
void HardAIVsHardAI(const bool isNewGame,
	ModeMenuItems gameMode,
	DifficultySelectionMenuItems difficulty,
	char firstAIField[Rows][Columns],
	char secondAIField[Rows][Columns],
	Cell& firstAIShot,
	Cell& secondAIShot,
	string& firstAIName,
	string& secondAIName)
{
	PlayerData firstAIData;
	firstAIData.isPlayer = false;
	firstAIData.isFirstAI = true;

	PlayerData secondAIData;
	secondAIData.isPlayer = false;
	secondAIData.isFirstAI = false;

	if (isNewGame)
	{
		AutoFillBattleField(firstAIField);
		AutoFillBattleField(secondAIField);

		const string NoOneShot = "";

		cout << "\t\t\t      " << "Стартовое поле" << endl << endl;
		PrintAIVsAIBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, firstAIShot, NoOneShot);
		system("pause");
		system("cls");
	}

	firstAIShot.result.isKilled = true;
	secondAIShot.result.isKilled = true;

	bool isOpenPauseMenu;
	bool isContinueGame;

	do
	{
		do
		{
			PlayerOrAITurn(secondAIField, firstAIField, secondAIName, firstAIName, firstAIShot, secondAIData, firstAIData);

			if (isGameOver(secondAIField))
			{
				system("pause");
				system("cls");
				PrintTheWinner(firstAIName);
				return;
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
							isContinueGame = true;
							break;
						case PauseMenuItems::Save:
							SaveGame(gameMode, difficulty, firstAIField, secondAIField, firstAIShot, secondAIShot, firstAIName, secondAIName);
							continue;
						case PauseMenuItems::GoToMainMenu:
							return;
						}
					} while (!isContinueGame);

					system("cls");

					PrintAIVsAIBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, firstAIShot, firstAIName);
				}

			} while (isOpenPauseMenu);

		} while (firstAIShot.result.isHit);

		do
		{
			PlayerOrAITurn(firstAIField, secondAIField, firstAIName, secondAIName, secondAIShot, firstAIData, secondAIData);

			if (isGameOver(firstAIField))
			{
				system("pause");
				system("cls");
				PrintTheWinner(secondAIName);
				return;
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
							isContinueGame = true;
							break;
						case PauseMenuItems::Save:
							SaveGame(gameMode, difficulty, firstAIField, secondAIField, firstAIShot, secondAIShot, firstAIName, secondAIName);
							continue;
						case PauseMenuItems::GoToMainMenu:
							return;
						}
					} while (!isContinueGame);

					system("cls");

					PrintAIVsAIBattlefield(firstAIField, secondAIField, firstAIName, secondAIName, secondAIShot, secondAIName);
				}

			} while (isOpenPauseMenu);

		} while (secondAIShot.result.isHit);

	} while (true);
}