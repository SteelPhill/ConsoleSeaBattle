#pragma once

#define CleaningInputStream cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

#include <iostream>
#include "TryReadValue.h"
#include "PrintPlayField.h"
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

//МЕНЮ ВЫБОРА ОЧЕРЕДНОСТИ ХОДА 
bool TryChoiceMovesOrder(PlayerData& firstPlayerData, PlayerData& secondPlayerData)
{
	const int BeginRange = 0;
	const int EndRange = 2;

	cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "   " << "Очередность хода:" << endl << endl;
	cout << "1.Игрок ходит первым" << endl;
	cout << "2.Компьютер ходит первым" << endl << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	cout << " => ";
	MenuForChoosingMovesOrderItems choice = (MenuForChoosingMovesOrderItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	system("cls");

	switch (choice)
	{
	case MenuForChoosingMovesOrderItems::PlayerMoveFirst:
	{
		firstPlayerData.isEasyAI = false;
		firstPlayerData.isPlayer = true;
		firstPlayerData.isFirstAI = false;
		secondPlayerData.isPlayer = false;
		secondPlayerData.isFirstAI = false;
		break;
	}
	case MenuForChoosingMovesOrderItems::AIMoveFirst:
	{
		secondPlayerData.isEasyAI = false;
		firstPlayerData.isPlayer = false;
		firstPlayerData.isFirstAI = true;
		secondPlayerData.isPlayer = true;
		secondPlayerData.isFirstAI = false;
		break;
	}
	case MenuForChoosingMovesOrderItems::GoToMainMenu:
	{
		return false;
	}
	}

	return true;
}

//МЕНЮ ВЫБОРА СЛОЖНОСТИ ИГРЫ
bool TryChoiceDifficulty(
	bool& isNewGame,
	ModeMenuItems& gameMode,
	DifficultySelectionMenuItems& difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	Cell& firstPlayerLastShot,
	Cell& secondPlayerLastShot,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	const int BeginRange = 0;
	const int EndRange = 2;

	cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "  " << "Уровень сложности:" << endl << endl;
	cout << "1.Низкий" << endl;
	cout << "2.Высокий" << endl << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	cout << " => ";
	difficulty = (DifficultySelectionMenuItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	system("cls");

	switch (difficulty)
	{
	case DifficultySelectionMenuItems::Easy:
	{
		firstPlayerData.isEasyAI = true;
		secondPlayerData.isEasyAI = true;
		TryChoiceMovesOrder(firstPlayerData, secondPlayerData);
		break;
	}
	case DifficultySelectionMenuItems::Hard:
	{
		firstPlayerData.isEasyAI = false;
		secondPlayerData.isEasyAI = false;
		TryChoiceMovesOrder(firstPlayerData, secondPlayerData);
		break;
	}
	case DifficultySelectionMenuItems::GoToMainMenu:
	{
		return false;
	}
	}

	return true;
}

//ВВОД ИМЕНИ ИГРОКА
void InputPlayerNames(PlayerData& firstPlayerData, PlayerData& secondPlayerData)
{
	const int maxNameSize = 14;

	do
	{
		cout << "Введите имя игрока:" << endl << endl;
		cout << " => ";

		firstPlayerData.name = CinValue<string>();

		CleaningInputStream;

		cout << endl;

		if (firstPlayerData.name.size() > maxNameSize)
		{
			cout << "Ошибка! Имя не может содержать более 14 символов!" << endl << endl;
			system("pause");
		}

		system("cls");

	} while (firstPlayerData.name.size() > maxNameSize);

	do
	{
		cout << "Введите имя противника:" << endl << endl;
		cout << " => ";

		secondPlayerData.name = CinValue<string>();

		CleaningInputStream;

		cout << endl;

		if (secondPlayerData.name.size() > maxNameSize)
		{
			cout << "Ошибка! Имя не может содержать более 14 символов!" << endl << endl;
			system("pause");
		}

		system("cls");

	} while (secondPlayerData.name.size() > maxNameSize);
}

//МЕНЮ ВЫБОРА РЕЖИМОВ ИГРЫ 
bool TryChoiceMode(
	bool& isNewGame,
	ModeMenuItems& gameMode,
	DifficultySelectionMenuItems& difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	Cell& firstPlayerLastShot,
	Cell& secondPlayerLastShot,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	const int BeginRange = 0;
	const int EndRange = 2;

	cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "     " << "Режимы игры:" << endl << endl;
	cout << "1.Игрок против компьютера" << endl;
	cout << "2.Компьютер против компьютера" << endl << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	cout << " => ";
	gameMode = (ModeMenuItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	system("cls");

	switch (gameMode)
	{
	case ModeMenuItems::PlayerVsAI:
	{

		InputPlayerNames(firstPlayerData, secondPlayerData);
		break;
	}
	case ModeMenuItems::AIVsAI:
	{
		firstPlayerData.name = "Компьютер 1";
		secondPlayerData.name = "Компьютер 2";
		break;
	}
	case ModeMenuItems::GoToMainMenu:
	{
		return false;
	}
	}

	return true;
}

//ГЛАВНОЕ МЕНЮ 
bool TryChoiceMainMenuItem(
	bool& isNewGame,
	ModeMenuItems& gameMode,
	DifficultySelectionMenuItems& difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	Cell& firstPlayerLastShot,
	Cell& secondPlayerLastShot,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	const int BeginRange = 0;
	const int EndRange = 3;

	cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "     " << "Главное меню:" << endl << endl;
	cout << "1.Новая игра" << endl;
	cout << "2.Загрузить игру" << endl;
	cout << "3.Правила" << endl << endl;
	cout << "0.Выход из игры" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	cout << " => ";
	MainMenuItems choice = (MainMenuItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	system("cls");

	bool isProgramContinue = true;

	switch (choice)
	{
	case MainMenuItems::NewGame:
	{
		isProgramContinue = TryChoiceMode(isNewGame, gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerData, secondPlayerData);
		break;
	}
	case MainMenuItems::LoadGame:
	{

		break;
	}
	case MainMenuItems::Rules:
	{
		PrintRules();
		break;
	}
	case MainMenuItems::ExitProgram:
	{
		return false;
	}
	}
	
	return isProgramContinue;
}


//МЕНЮ ВАРИАНТОВ РАЗМЕЩЕНИЯ КОРАБЛЕЙ 
ShipPlacementVariantsMenuItems ShipPlacementVariantsMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	ShipPlacementVariantsMenuItems choice;

	cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Варианты размещения кораблей:" << endl << endl;
	cout << "1.Автоматическое размещение" << endl;
	cout << "2.Ручное размещение" << endl << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	cout << " => ";
	choice = (ShipPlacementVariantsMenuItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	system("cls");

	return choice;
}

//СПИСОК ДЛЯ ВЫБОРА НАПРАВЛЕНИЯ РАЗМЕЩЕНИЯ КОРАБЛЯ
ShipsDirectionListItems ShipsDirectionList()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	ShipsDirectionListItems choice;

	cout << "    " << "Варианты размещения кораблей:" << endl;
	cout << "1.Горизонтальное размещение корабля" << endl;
	cout << "2.Вертикальное размещение корабля" << endl;
	cout << "0.Выйти в главное меню" << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	cout << " => ";
	choice = (ShipsDirectionListItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	cout << endl;

	return choice;
}

//МЕНЮ ПАУЗЫ
PauseMenuItems PauseMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	PauseMenuItems choice;

	cout << "    " << "ПАУЗА" << endl << endl;
	cout << "1.Продолжить игру" << endl;
	cout << "2.Сохранить игру" << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	cout << " => ";
	choice = (PauseMenuItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	system("cls");

	return choice;
}

//ОТКРЫТЬ МЕНЮ ПАУЗЫ?
bool IsOpenPauseMenu()
{
	const char OpenPauseMenu = '0';
	const char ContinueGame = '\n';

	char choice;

	cout << "Следующий выстрел: нажмите Enter" << endl;
	cout << "Пауза: введите 0 затем нажмите Enter" << endl;

	do
	{
		cout << " => ";
		choice = cin.get();

		if (choice != ContinueGame)
			CleaningInputStream;

		if (choice != OpenPauseMenu && choice != ContinueGame)
			cout << "Ошибка ввода!" << endl;

	} while (choice != OpenPauseMenu && choice != ContinueGame);

	system("cls");

	if (choice == OpenPauseMenu)
		return true;

	else
		return false;
}

//ПРОВЕРКА ВВЕДЕННОЙ БУКВЫ
inline bool IsEnterNotCoordinateLetter(const unsigned char letter)
{
	return !(letter >= (unsigned char)'А' && letter <= (unsigned char)'К') && !(letter >= (unsigned char)'а' && letter <= (unsigned char)'к') || letter == (unsigned char)'Й' || letter == (unsigned char)'й';
}

//ПРОВЕРКА НА ВОЗМОЖНОСТЬ ВЫСТРЕЛА
inline bool IsShootByCellNotPossible(char field[Rows][Columns], Cell& shot)
{
	return field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit || field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss || field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Killed;
}

//ВВОД КООРДИНАТ 
void InputCoordinates(char field[Rows][Columns], Cell& cell, const int shipSize)
{
	const int beginRange = 1;
	const int endRange = 10;

	unsigned char letter;

	do
	{
		if (shipSize == NULL)
			cout << "Введите координаты выстрела:" << endl;
		else
			cout << "Введите начальные координаты корабля:" << endl;

		cout << " => ";

		letter = CinValue<unsigned char>();

		if (IsEnterNotCoordinateLetter(letter))
		{
			cout << "Ошибка ввода!" << endl << endl;
			CleaningInputStream;
			continue;
		}

		switch (letter)
		{
		case (unsigned char)'А':
		case (unsigned char)'а':
			cell.coordinates.abscissa = 1;
			break;

		case (unsigned char)'Б':
		case (unsigned char)'б':
			cell.coordinates.abscissa = 2;
			break;

		case (unsigned char)'В':
		case (unsigned char)'в':
			cell.coordinates.abscissa = 3;
			break;

		case (unsigned char)'Г':
		case (unsigned char)'г':
			cell.coordinates.abscissa = 4;
			break;

		case (unsigned char)'Д':
		case (unsigned char)'д':
			cell.coordinates.abscissa = 5;
			break;

		case (unsigned char)'Е':
		case (unsigned char)'е':
			cell.coordinates.abscissa = 6;
			break;

		case (unsigned char)'Ж':
		case (unsigned char)'ж':
			cell.coordinates.abscissa = 7;
			break;

		case (unsigned char)'З':
		case (unsigned char)'з':
			cell.coordinates.abscissa = 8;
			break;

		case (unsigned char)'И':
		case (unsigned char)'и':
			cell.coordinates.abscissa = 9;
			break;

		case (unsigned char)'К':
		case (unsigned char)'к':
			cell.coordinates.abscissa = 10;
			break;

		default:
			break;
		}

		cout << " => ";

		cell.coordinates.ordinate = CinValueInRange(beginRange, endRange);

		CleaningInputStream;

	} while (IsEnterNotCoordinateLetter(letter));
}

//ПЕЧАТАТЬ ПРАВИЛА ИГРЫ
void PrintRules()
{
	cout << "\t\t\t" << "Правила игры" << endl << endl;
	cout << "1.Цель игры - \"потопить\" все корабли, находящиеся на игровом поле противника." << endl;
	cout << "2.Игровое поле представляет собой квадрат, состоящий из 10 строк и 10 столбцов." << endl;
	cout << "3.Строки обозначены числами от 1 до 10." << endl;
	cout << "4.Столбцы обозначены буквами русского алфавита от А до К (буквы Ё и Й - пропущены)." << endl;
	cout << "5.На игровом поле расположены: 4 однопалубника, 3 двухпалубника, 2 трёхпалубника, 1 четырёхпалубник." << endl;
	cout << "6.Соприкосновение соседних кораблей не допускается!" << endl;
	cout << "7.Координаты назначаются следующим образом: первой вводится буква, затем число. Пример: А1." << endl << endl;
	cout << "Обозначения, присутствующие на игровом поле:" << endl;
	cout << " ---> - показывает направление атаки;" << endl;
	cout << " [ ] - пустая клетка или клетка, по которой не стреляли;" << endl;
	cout << " [O] - клетка с кораблём;" << endl;
	cout << " [*] - промах;" << endl;
	cout << " [+] - подбитый корабль;" << endl;
	cout << " [X] - уничтоженный корабль." << endl << endl;
	system("pause");
	system("cls");
}