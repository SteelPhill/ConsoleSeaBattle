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

struct shotResult
{
	bool isHit;
	bool isKilled;
	int howManyShipsLeft = TotalShipsNumber;
};

struct Cell
{
	Coordinates coordinates;
	shotResult result;
};

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include "TryKillShip.h"
#include "TryReadValue.h"
#include "OutputDataToConsole.h"
#include "InputDataFromConsole.h"
#include "Shooting.h"
#include "BeginFillField.h"
#include "GameModeOptions.h"
#include <Windows.h>
using namespace std;


//MAIN()
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	MainMenuItems gameMode;
	DifficultySelectionMenuItems difficulty;
	ShipPlacementVariantsMenuItems shipsPlacementVariants;

	do
	{
		gameMode = MainMenu();

		switch (gameMode)
		{

		case MainMenuItems::PlayerVsComputer:
		{
			difficulty = DifficultySelectionMenu();

			switch (difficulty)
			{
			case DifficultySelectionMenuItems::Easy:
			{
				shipsPlacementVariants = ShipPlacementVariantsMenu();
				if (shipsPlacementVariants == ShipPlacementVariantsMenuItems::GoToMainMenu)
					continue;
				PlayerVsEasyAI(shipsPlacementVariants);
				break;
			}

			case DifficultySelectionMenuItems::Hard:
			{
				shipsPlacementVariants = ShipPlacementVariantsMenu();
				if (shipsPlacementVariants == ShipPlacementVariantsMenuItems::GoToMainMenu)
					continue;
				PlayerVsHardAI(shipsPlacementVariants);
				break;
			}

			case DifficultySelectionMenuItems::GoToMainMenu:
			{
				continue;
			}

			default:
				break;
			}

			break;
		}

		case MainMenuItems::ComputerVsComputer:
		{
			difficulty = DifficultySelectionMenu();

			switch (difficulty)
			{
			case DifficultySelectionMenuItems::Easy:
				EasyAIVsEasyAI();
				break;

			case DifficultySelectionMenuItems::Hard:
				HardAIVsHardAI();
				break;

			case DifficultySelectionMenuItems::GoToMainMenu:
				continue;

			default:
				break;
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
			cout << "Завершение работы . . ." << endl << endl;
			system("pause");
			return;
		}

		default:
			break;
		}

	} while (true);
}