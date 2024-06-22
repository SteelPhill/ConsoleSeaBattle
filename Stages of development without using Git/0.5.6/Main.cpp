#define Rows 12
#define Columns 12
#define TotalShipsNumber 10
#define Ship 'O'
#define Empty ' '
#define Miss '*'
#define Hit '+'
#define Killed 'X'

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

enum class MainMenuItems
{
	NewGame = 1,
	LoadGame = 2,
	Rules = 3,
	ExitProgram = 0
};

enum class ModeMenuItems
{
	PlayerVsAI = 1,
	AIVsAI = 2,
	GoToMainMenu = 0
};

enum class DifficultySelectionMenuItems
{
	Easy = 1,
	Hard = 2,
	GoToMainMenu = 0
};

enum class MenuForChoosingMovesOrderItems
{
	PlayerMoveFirst = 1,
	AIMoveFirst = 2,
	GoToMainMenu = 0
};

enum class ShipPlacementVariantsMenuItems
{
	AutoPlacement = 1,
	ManuallyPlacement = 2,
	GoToMainMenu = 0
};

enum class ShipsDirectionListItems
{
	Horizontal = 1,
	Vertical = 2,
	ItOnedeck = 3,
	GoToMainMenu = 0
};

enum class PauseMenuItems
{
	Continue = 1,
	Save = 2,
	GoToMainMenu = 0
};

struct PlayerData
{
	string name;
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


#include "TryKillShip.h"
#include "TryReadValue.h"
#include "PrintPlayField.h"
#include "MenusAndActions.h"
#include "Shooting.h"
#include "BeginFillField.h"
#include "GameModes.h"
#include "SaveAndLoad.h"
#include <Windows.h>


//MAIN()
void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));

	char firstPlayerField[Rows][Columns];
	char secondPlayerField[Rows][Columns];

	PlayerData firstPlayerData;
	PlayerData secondPlayerData;

	ModeMenuItems gameMode;
	DifficultySelectionMenuItems difficulty;

	bool isNewGame;
	bool isProgramContinue;

	do
	{
		Cell firstPlayerLastShot;
		Cell secondPlayerLastShot;

		isProgramContinue = TryChoiceMainMenuItem(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerData, secondPlayerData);
		if (!isProgramContinue)
			return;

		SelectedMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerData, secondPlayerData);

	} while (true);
}