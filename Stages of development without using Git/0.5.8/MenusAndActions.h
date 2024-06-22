#pragma once

#define CleaningInputStream cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

#include <iostream>
#include "TryReadValue.h"
#include "PrintPlayField.h"
#include "SaveAndLoad.h"
using namespace std;

enum class MainMenuItems
{
	NewGame = OneCode,
	LoadGame = TwoCode,
	Rules = ThreeCode,
	ExitProgram = EscCode
};

enum class MovesOrderMenuItems
{
	PlayerMoveFirst = OneCode,
	AIMoveFirst = TwoCode,
	GoToMainMenu = EscCode
};

enum class ShipPlacementVariantsMenuItems
{
	AutoPlacement = OneCode,
	ManuallyPlacement = TwoCode,
	GoToMainMenu = EscCode
};

enum class ShipsDirectionListItems
{
	Horizontal = OneCode,
	Vertical = TwoCode,
	ItOnedeck = ThreeCode,
	GoToMainMenu = EscCode
};

enum class PauseMenuItems
{
	Continue = OneCode,
	Save = TwoCode,
	GoToMainMenu = EscCode
};


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
	cout << "7.Координаты назначаются следующим образом: первой вводится буква, затем число. Пример: А1." << endl;
	cout << "8.При расстановке кораблей в ручном режиме, вводятся координаты только стартовой клетки (самой левой или самой верхней)." << endl << endl;
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

//ВВОД ИМЕНИ ИГРОКА
void InputPlayerNames(PlayerData& firstPlayerData, PlayerData& secondPlayerData)
{
	const int maxNameSize = 14;

	do
	{
		cout << "Введите имя игрока и нажмите Enter:" << endl << endl;
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
		cout << "Введите имя противника и нажмите Enter:" << endl << endl;
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

//МЕНЮ ВЫБОРА ОЧЕРЕДНОСТИ ХОДА 
bool TryContinueSelectedInMovesOrderMenu(PlayerData& firstPlayerData, PlayerData& secondPlayerData)
{
	cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "   " << "Очередность хода:" << endl << endl;
	cout << "  1 - Игрок ходит первым" << endl;
	cout << "  2 - Компьютер ходит первым" << endl << endl;
	cout << "ESC - Выйти в главное меню" << endl << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != OneCode && choice != TwoCode && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != OneCode && choice != TwoCode && choice != EscCode);

	system("cls");

	switch ((MovesOrderMenuItems)choice)
	{
	case MovesOrderMenuItems::PlayerMoveFirst:
	{
		firstPlayerData.isMove = true;
		secondPlayerData.isMove = false;
		firstPlayerData.isEasyAI = false;
		firstPlayerData.isPlayer = true;
		firstPlayerData.isFirstAI = false;
		secondPlayerData.isPlayer = false;
		secondPlayerData.isFirstAI = false;

		break;
	}
	case MovesOrderMenuItems::AIMoveFirst:
	{
		firstPlayerData.isMove = false;
		secondPlayerData.isMove = true;
		secondPlayerData.isEasyAI = false;
		firstPlayerData.isPlayer = false;
		firstPlayerData.isFirstAI = true;
		secondPlayerData.isPlayer = true;
		secondPlayerData.isFirstAI = false;

		break;
	}
	case MovesOrderMenuItems::GoToMainMenu:
	{
		return false;
	}
	}

	return true;
}

//МЕНЮ ВЫБОРА СЛОЖНОСТИ ИГРЫ
bool TryContinueSelectedInDifficultyMenu(
	ModeMenuItems& gameMode,
	DifficultyMenuItems& difficulty,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "  " << "Уровень сложности:" << endl << endl;
	cout << "  1 - Низкий" << endl;
	cout << "  2 - Высокий" << endl << endl;
	cout << "ESC - Выйти в главное меню" << endl << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != OneCode && choice != TwoCode && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != OneCode && choice != TwoCode && choice != EscCode);

	system("cls");

	difficulty = (DifficultyMenuItems)choice;

	bool isProgramContinue = true;

	switch (difficulty)
	{
	case DifficultyMenuItems::Easy:
	{
		firstPlayerData.isMove = true;
		secondPlayerData.isMove = false;
		firstPlayerData.isEasyAI = true;
		secondPlayerData.isEasyAI = true;

		if (gameMode == ModeMenuItems::PlayerVsAI)
			isProgramContinue = TryContinueSelectedInMovesOrderMenu(firstPlayerData, secondPlayerData);

		break;
	}
	case DifficultyMenuItems::Hard:
	{
		firstPlayerData.isMove = true;
		secondPlayerData.isMove = false;
		firstPlayerData.isEasyAI = false;
		secondPlayerData.isEasyAI = false;

		if (gameMode == ModeMenuItems::PlayerVsAI)
			isProgramContinue = TryContinueSelectedInMovesOrderMenu(firstPlayerData, secondPlayerData);

		break;
	}
	case DifficultyMenuItems::GoToMainMenu:
	{
		return false;
	}
	}

	return isProgramContinue;
}

//МЕНЮ ВЫБОРА РЕЖИМОВ ИГРЫ 
bool TryContinueSelectedInModesMenu(
	ModeMenuItems& gameMode,
	DifficultyMenuItems& difficulty,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "     " << "Режимы игры:" << endl << endl;
	cout << "  1 - Игрок против компьютера" << endl;
	cout << "  2 - Компьютер против компьютера" << endl << endl;
	cout << "ESC - Выйти в главное меню" << endl << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != OneCode && choice != TwoCode && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != OneCode && choice != TwoCode && choice != EscCode);

	system("cls");

	gameMode = (ModeMenuItems)choice;

	bool isProgramContinue = true;

	switch (gameMode)
	{
	case ModeMenuItems::PlayerVsAI:
	{
		InputPlayerNames(firstPlayerData, secondPlayerData);

		isProgramContinue = TryContinueSelectedInDifficultyMenu(gameMode, difficulty, firstPlayerData, secondPlayerData);

		break;
	}
	case ModeMenuItems::AIVsAI:
	{
		firstPlayerData.name = "Компьютер 1";
		secondPlayerData.name = "Компьютер 2";

		firstPlayerData.isPlayer = false;
		firstPlayerData.isFirstAI = true;
		secondPlayerData.isPlayer = false;
		secondPlayerData.isFirstAI = false;

		isProgramContinue = TryContinueSelectedInDifficultyMenu(gameMode, difficulty, firstPlayerData, secondPlayerData);

		break;
	}
	case ModeMenuItems::GoToMainMenu:
	{
		return false;
	}
	}

	return isProgramContinue;
}

//ГЛАВНОЕ МЕНЮ 
bool TryContinueSelectedInMainMenu(
	bool& isNewGame,
	ModeMenuItems& gameMode,
	DifficultyMenuItems& difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	Cell& firstPlayerLastShot,
	Cell& secondPlayerLastShot,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	bool isProgramContinue = true;

	do
	{
		cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
		cout << "     " << "Главное меню:" << endl << endl;
		cout << "  1 - Новая игра" << endl;
		cout << "  2 - Загрузить игру" << endl;
		cout << "  3 - Справка" << endl << endl;
		cout << "Esc - Выход из игры" << endl << endl;

		int choice;

		do
		{
			choice = _getch();

			if (choice != OneCode && choice != TwoCode && choice != ThreeCode && choice != EscCode)
				cout << "Ошибка ввода!" << endl;

		} while (choice != OneCode && choice != TwoCode && choice != ThreeCode && choice != EscCode);

		system("cls");

		switch ((MainMenuItems)choice)
		{
		case MainMenuItems::NewGame:
		{
			isProgramContinue = TryContinueSelectedInModesMenu(gameMode, difficulty, firstPlayerData, secondPlayerData);

			if (isProgramContinue)
			{
				isNewGame = true;
				return true;
			}

			continue;
		}
		case MainMenuItems::LoadGame:
		{
			LoadGame(gameMode, difficulty, firstPlayerField, secondPlayerField, firstPlayerLastShot, secondPlayerLastShot, firstPlayerData, secondPlayerData);

			isNewGame = false;

			return true;
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
	} while (true);

}


//МЕНЮ ВАРИАНТОВ РАЗМЕЩЕНИЯ КОРАБЛЕЙ 
ShipPlacementVariantsMenuItems ShipPlacementVariantsMenu()
{
	cout << "===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Варианты размещения кораблей:" << endl << endl;
	cout << "  1 - Автоматическое размещение" << endl;
	cout << "  2 - Ручное размещение" << endl << endl;
	cout << "ESC - Выйти в главное меню" << endl << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != OneCode && choice != TwoCode && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != OneCode && choice != TwoCode && choice != EscCode);

	system("cls");

	return (ShipPlacementVariantsMenuItems)choice;
}

//СПИСОК ДЛЯ ВЫБОРА НАПРАВЛЕНИЯ РАЗМЕЩЕНИЯ КОРАБЛЯ
ShipsDirectionListItems ShipsDirectionList()
{
	cout << "    " << "Варианты размещения кораблей:" << endl;
	cout << "  1 - Горизонтальное размещение корабля" << endl;
	cout << "  2 - Вертикальное размещение корабля" << endl;
	cout << "ESC - Выйти в главное меню" << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != OneCode && choice != TwoCode && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != OneCode && choice != TwoCode && choice != EscCode);

	cout << endl;

	return (ShipsDirectionListItems)choice;
}

//МЕНЮ ПАУЗЫ
PauseMenuItems PauseMenu()
{
	cout << "    " << "ПАУЗА" << endl << endl;
	cout << "  1 - Продолжить игру" << endl;
	cout << "  2 - Сохранить игру" << endl << endl;
	cout << "ESC - Выйти в главное меню" << endl << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != OneCode && choice != TwoCode && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != OneCode && choice != TwoCode && choice != EscCode);

	return (PauseMenuItems)choice;
}

//ОТКРЫТЬ МЕНЮ ПАУЗЫ?
bool IsOpenPauseMenu()
{
	char choice;

	cout << "Следующий выстрел: нажмите Enter" << endl;
	cout << "Пауза:             нажмите Esc" << endl;

	do
	{
		choice = _getch();

		if (choice != EscCode && choice != EnterCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != EscCode && choice != EnterCode);

	system("cls");

	if (choice == EscCode)
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
			cout << "Введите начальные координаты (первую клетку) корабля:" << endl;

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