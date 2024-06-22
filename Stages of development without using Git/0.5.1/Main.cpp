#define Rows 12
#define Columns 12
#define TotalShipsNumber 10
#define Ship 'O'
#define Empty ' '
#define Miss '*'
#define Hit '+'
#define Killed 'X'

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


void IfNewGame()
{

}

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

	MainMenuItems selectInMainMenu;
	ModeMenuItems gameMode;
	DifficultySelectionMenuItems difficulty;
	ShipPlacementVariantsMenuItems shipsPlacementVariants;

	bool isNewGame;

	do
	{
		Cell firstPlayerLastShot;
		Cell secondPlayerLastShot;

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

				switch (difficulty)
				{
				case DifficultySelectionMenuItems::Easy:
				{
					PlayerVsEasyAI(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName);
					break;
				}
				case DifficultySelectionMenuItems::Hard:
				{
					PlayerVsHardAI(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName);
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
				firstPlayerName = "Компьютер1";
				secondPlayerName = "Компьютер2";

				difficulty = DifficultySelectionMenu();

				switch (difficulty)
				{
				case DifficultySelectionMenuItems::Easy:
					EasyAIVsEasyAI(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName);
					break;

				case DifficultySelectionMenuItems::Hard:
					HardAIVsHardAI(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName);
					break;

				case DifficultySelectionMenuItems::GoToMainMenu:
					continue;

				default:
					break;
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
					PlayerVsEasyAI(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName);
					break;
				}
				case DifficultySelectionMenuItems::Hard:
				{
					PlayerVsHardAI(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName);
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
					EasyAIVsEasyAI(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName);
					break;
				}
				case DifficultySelectionMenuItems::Hard:
				{
					HardAIVsHardAI(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerName, secondPlayerName);
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

			system("pause");
			system("cls");
			continue;
		}

		case MainMenuItems::ExitProgram:
		{
			return;
		}
		}

	} while (true);
}