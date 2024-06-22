#pragma once

#define GameLogo "===\\\\\\МОРСКОЙ БОЙ///==="
#define CleaningInputStream cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

#include <iostream>
#include "TryReadValue.h"
#include "PrintPlayField.h"
#include "SaveAndLoad.h"
using namespace std;

#define NOMINMAX

enum class MainMenuItems
{
	NewGame = '1',
	LoadGame = '2',
	Rules = '3',
	ExitProgram = EscCode
};

enum class MovesOrderMenuItems
{
	PlayerMoveFirst = '1',
	AIMoveFirst = '2',
	GoToMainMenu = EscCode
};

enum class ShipPlacementVariantsMenuItems
{
	AutoPlacement = '1',
	ManuallyPlacement = '2',
	GoToMainMenu = EscCode
};

enum class ShipsDirectionListItems
{
	Horizontal = '1',
	Vertical = '2',
	ItOnedeck = '3',
	GoToMainMenu = EscCode
};

enum class PauseMenuItems
{
	Continue = '1',
	Save = '2',
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
void InputPlayersName(PlayerData& firstPlayerData, PlayerData& secondPlayerData)
{
	const int maxNameSize = 14;

	do
	{
		cout << "Введите имя игрока и нажмите Enter:" << endl << endl;

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
	cout << GameLogo << endl << endl;
	cout << "   " << "Очередность хода:" << endl << endl;
	cout << "  1 - Игрок ходит первым" << endl;
	cout << "  2 - Компьютер ходит первым" << endl << endl;
	cout << "ESC - Выйти в главное меню" << endl << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != '1' && choice != '2' && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != '1' && choice != '2' && choice != EscCode);

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
	const ModeMenuItems& gameMode,
	DifficultyMenuItems& difficulty,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	cout << GameLogo << endl << endl;
	cout << "  " << "Уровень сложности:" << endl << endl;
	cout << "  1 - Низкий" << endl;
	cout << "  2 - Высокий" << endl << endl;
	cout << "ESC - Выйти в главное меню" << endl << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != '1' && choice != '2' && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != '1' && choice != '2' && choice != EscCode);

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
	cout << GameLogo << endl << endl;
	cout << "     " << "Режимы игры:" << endl << endl;
	cout << "  1 - Игрок против компьютера" << endl;
	cout << "  2 - Компьютер против компьютера" << endl << endl;
	cout << "ESC - Выйти в главное меню" << endl << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != '1' && choice != '2' && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != '1' && choice != '2' && choice != EscCode);

	system("cls");

	gameMode = (ModeMenuItems)choice;

	bool isProgramContinue = true;

	switch (gameMode)
	{
	case ModeMenuItems::PlayerVsAI:
	{
		InputPlayersName(firstPlayerData, secondPlayerData);

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
		cout << GameLogo << endl << endl;
		cout << "     " << "Главное меню:" << endl << endl;
		cout << "  1 - Новая игра" << endl;
		cout << "  2 - Загрузить игру" << endl;
		cout << "  3 - Справка" << endl << endl;
		cout << "Esc - Выход из игры" << endl << endl;

		int choice;

		do
		{
			choice = _getch();

			if (choice != '1' && choice != '2' && choice != '3' && choice != EscCode)
				cout << "Ошибка ввода!" << endl;

		} while (choice != '1' && choice != '2' && choice != '3' && choice != EscCode);

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
	cout << GameLogo << endl << endl;
	cout << "Варианты размещения кораблей:" << endl << endl;
	cout << "  1 - Автоматическое размещение" << endl;
	cout << "  2 - Ручное размещение" << endl << endl;
	cout << "ESC - Выйти в главное меню" << endl << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != '1' && choice != '2' && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != '1' && choice != '2' && choice != EscCode);

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

		if (choice != '1' && choice != '2' && choice != EscCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != '1' && choice != '2' && choice != EscCode);

	cout << endl;

	return (ShipsDirectionListItems)choice;
}

//ОТКРЫТЬ МЕНЮ ПАУЗЫ?
bool IsOpenPauseMenu()
{
	cout << "Следующий выстрел: нажмите Enter" << endl;
	cout << "Пауза:             нажмите Esc" << endl;

	int choice;

	do
	{
		choice = _getch();

		if (choice != EscCode && choice != EnterCode)
			cout << "Ошибка ввода!" << endl;

	} while (choice != EscCode && choice != EnterCode);

	system("cls");

	if (choice == EscCode)
		return true;

	return false;
}

//МЕНЮ ПАУЗЫ
bool TryChoicePauseMenuOptions(
	const ModeMenuItems gameMode,
	const DifficultyMenuItems difficulty,
	char targedField[Rows][Columns],
	char shooterField[Rows][Columns],
	const Cell& targedShot,
	Cell& shooterShot,
	PlayerData& targedData,
	PlayerData& shooterData)
{
	bool isContinueGame = false;

	do
	{
		cout << "    " << "ПАУЗА" << endl << endl;
		cout << "  1 - Продолжить игру" << endl;
		cout << "  2 - Сохранить игру" << endl << endl;
		cout << "ESC - Выйти в главное меню" << endl << endl;

		int choice;

		do
		{
			choice = _getch();

			if (choice != '1' && choice != '2' && choice != EscCode)
				cout << "Ошибка ввода!" << endl;

		} while (choice != '1' && choice != '2' && choice != EscCode);

		switch ((PauseMenuItems)choice)
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

	if (shooterData.isPlayer || targedData.isFirstAI)
		PrintBattlefield(targedField, shooterField, shooterShot, shooterData.name, targedData, shooterData);
	else if (targedData.isPlayer || shooterData.isFirstAI)
		PrintBattlefield(shooterField, targedField, shooterShot, shooterData.name, shooterData, targedData);

	return true;
}

//ПРОВЕРКА ВВЕДЕННОЙ БУКВЫ
inline bool IsEnterNotCoordinateLetter(const unsigned char letter)
{
	return !(letter >= (unsigned char)'А' && letter <= (unsigned char)'К') && !(letter >= (unsigned char)'а' && letter <= (unsigned char)'к') || letter == (unsigned char)'Й' || letter == (unsigned char)'й';
}

//ПРОВЕРКА НА ВОЗМОЖНОСТЬ ВЫСТРЕЛА
inline bool IsShootByCellNotPossible(char field[Rows][Columns], const Cell& shot)
{
	return field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit || field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss || field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Killed;
}

//ВВОД КООРДИНАТ 
void InputCoordinates(char field[Rows][Columns], Cell& cell, const int shipSize)
{
	const int beginCoordinateRange = 1;
	const int endCoordinateRange = 10;

	unsigned char letter;

	if (shipSize == NULL)
		cout << "    " << "Ввод координатов выстрела:" << endl << endl;
	else
		cout << "    " << "Ввод начальных координат корабля:" << endl << endl;

	cout << "Введите букву и нажмите Enter" << endl;

	do
	{
		letter = CinValue<unsigned char>();

		if (IsEnterNotCoordinateLetter(letter))
			cout << "Ошибка ввода!" << endl;

		CleaningInputStream;

	} while (IsEnterNotCoordinateLetter(letter));

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
	}

	cout << endl;

	cout << "Введите число и нажмите Enter" << endl;

	cell.coordinates.ordinate = CinValueInRange(beginCoordinateRange, endCoordinateRange);

	CleaningInputStream;
}