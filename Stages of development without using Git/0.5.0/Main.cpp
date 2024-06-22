#define Rows 12
#define Columns 12
#define TotalShipsNumber 10
#define Ship 'O'
#define Empty ' '
#define Miss '*'
#define Hit '+'
#define Killed 'X'

struct PlayerData
{
	bool isPlayer;
	bool isFirstAI;
	bool isEasyAI;
};

struct Coordinates
{
	int abscissa;
	int ordinate;
};

struct ShotResult
{
	bool isHit;
	bool isKilled;
	int howManyShipsLeft = TotalShipsNumber;
};

struct Cell
{
	Coordinates coordinates;
	ShotResult result;
};

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "TryKillShip.h"
#include "TryReadValue.h"
#include "PrintPlayField.h"
#include "MenusAndActions.h"
#include "Shooting.h"
#include "BeginFillField.h"
#include "GameModes.h"
#include "SaveAndLoad.h"
#include <Windows.h>
using namespace std;


//MAIN()
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	char firstPlayerField[Rows][Columns];
	char secondPlayerField[Rows][Columns];

	string firstPlayerName;
	string secondPlayerName;

	Cell firstPlayerLastShot;
	Cell secondPlayerLastShot;

	PlayerData firstPlayerData;
	PlayerData secondPlayerData;

	MainMenuItems selectInMainMenu;
	ModeMenuItems gameMode;
	DifficultySelectionMenuItems difficulty;
	MenuForChoosingMovesOrderItems choosingMovesOrder;
	ShipPlacementVariantsMenuItems shipsPlacementVariants;

	bool isNewGame;

	do
	{
		selectInMainMenu = MainMenu();

		switch (selectInMainMenu)
		{
		case MainMenuItems::NewGame:
		{
			isNewGame = true;

			gameMode = ModeMenu();

			switch (gameMode)
			{
			case ModeMenuItems::PlayerVsAI:
			{
				InputPlayerNames(firstPlayerName, secondPlayerName);

				difficulty = DifficultySelectionMenu();

				choosingMovesOrder = MenuForChoosingMovesOrder();

				switch (difficulty)
				{
				case DifficultySelectionMenuItems::Easy:
				{
					switch (choosingMovesOrder)
					{
					case MenuForChoosingMovesOrderItems::PlayerMoveFirst:
					{
						firstPlayerData.isPlayer = true;
						firstPlayerData.isFirstAI = false;
						firstPlayerData.isEasyAI = false;
						secondPlayerData.isPlayer = false;
						secondPlayerData.isFirstAI = false;
						secondPlayerData.isEasyAI = true;
						SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
						break;
					}
					case MenuForChoosingMovesOrderItems::AIMoveFirst:
					{
						firstPlayerData.isPlayer = false;
						firstPlayerData.isFirstAI = true;
						firstPlayerData.isEasyAI = true;
						secondPlayerData.isPlayer = true;
						secondPlayerData.isFirstAI = false;
						secondPlayerData.isEasyAI = false;
						SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
						break;
					}
					}
					break;
				}
				case DifficultySelectionMenuItems::Hard:
				{
					switch (choosingMovesOrder)
					{
					case MenuForChoosingMovesOrderItems::PlayerMoveFirst:
					{
						firstPlayerData.isPlayer = true;
						firstPlayerData.isFirstAI = false;
						firstPlayerData.isEasyAI = false;
						secondPlayerData.isPlayer = false;
						secondPlayerData.isFirstAI = false;
						secondPlayerData.isEasyAI = false;
						SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
						break;
					}
					case MenuForChoosingMovesOrderItems::AIMoveFirst:
					{
						firstPlayerData.isPlayer = false;
						firstPlayerData.isFirstAI = true;
						firstPlayerData.isEasyAI = false;
						secondPlayerData.isPlayer = true;
						secondPlayerData.isFirstAI = false;
						secondPlayerData.isEasyAI = false;
						SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
						break;
					}
					}
					break;
				}
				case DifficultySelectionMenuItems::GoToMainMenu:
				{
					continue;
				}
				}

				break;
			}
			case ModeMenuItems::AIVsAI:
			{
				firstPlayerName = "Компьютер 1";
				secondPlayerName = "Компьютер 2";

				firstPlayerData.isPlayer = false;
				firstPlayerData.isFirstAI = true;
				secondPlayerData.isPlayer = false;
				secondPlayerData.isFirstAI = false;

				difficulty = DifficultySelectionMenu();

				switch (difficulty)
				{
				case DifficultySelectionMenuItems::Easy:
				{
					firstPlayerData.isEasyAI = true;
					secondPlayerData.isEasyAI = true;
					SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
					break;
				}
				case DifficultySelectionMenuItems::Hard:
				{
					firstPlayerData.isEasyAI = false;
					secondPlayerData.isEasyAI = false;
					SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
					break;
				}
				case DifficultySelectionMenuItems::GoToMainMenu:
				{
					continue;
				}
				}

				break;
			}
			case ModeMenuItems::GoToMainMenu:
			{
				continue;
			}
			}

			break;
		}
		case MainMenuItems::LoadGame:
		{
			isNewGame = false;

			LoadGame(gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName);

			switch (gameMode)
			{
			case ModeMenuItems::PlayerVsAI:
			{
				switch (difficulty)
				{
				case DifficultySelectionMenuItems::Easy:
				{
					SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
					break;
				}
				case DifficultySelectionMenuItems::Hard:
				{
					SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
					break;
				}
				}

				break;
			}
			case ModeMenuItems::AIVsAI:
			{
				switch (difficulty)
				{
				case DifficultySelectionMenuItems::Easy:
				{
					SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
					break;
				}
				case DifficultySelectionMenuItems::Hard:
				{
					SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName, firstPlayerData, secondPlayerData);
					break;
				}
				}

				break;
			}
			}

			break;
		}
		case MainMenuItems::Rules:
		{
			PrintRules();
			continue;
		}
		case MainMenuItems::ExitProgram:
		{
			return;
		}
		}

	} while (true);
}