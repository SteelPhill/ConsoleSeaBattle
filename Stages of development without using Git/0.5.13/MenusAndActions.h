#pragma once

#define GameLogo "===\\\\\\МОРСКОЙ БОЙ///==="

#include <iostream>
#include "TryReadValue.h"
#include "PrintPlayField.h"
#include "SaveAndLoad.h"
using namespace std;


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
	cout << "3.Строки обозначены цифрами от 0 до 9." << endl;
	cout << "4.Столбцы обозначены буквами латинского алфавита от A до J." << endl;
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

		cout << " => ";

		getline(cin, firstPlayerData.name);

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

		getline(cin, secondPlayerData.name);

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
	cout << "Esc - Выйти в главное меню" << endl << endl;

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
	cout << "Esc - Выйти в главное меню" << endl << endl;

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
	cout << "Esc - Выйти в главное меню" << endl << endl;

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
	cout << "Esc - Выйти в главное меню" << endl << endl;

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
	cout << "Esc - Выйти в главное меню" << endl;

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
		cout << "Esc - Выйти в главное меню" << endl << endl;

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
inline bool IsEnterNotCoordinateLetter(const char letter)
{
	return !(letter >= 'A' && letter <= 'J') && !(letter >= 'a' && letter <= 'j');
}

//ПЕРЕВОД КООРДИНАТНОЙ БУКВЫ В ЦИФРУ
int ConvertCoordinateLetterToNumber(char letter)
{
	const int differenceBetweenIndexAndCoordinate = 1;

	letter = toupper(letter);

	char searchedLetterInStringForm[2] = { letter };

	char coordinateLettersArray[11] = { "ABCDEFGHIJ" };

	char* pointerToSearchLetter = strstr(coordinateLettersArray, searchedLetterInStringForm);

	return strlen(coordinateLettersArray) - strlen(pointerToSearchLetter) + differenceBetweenIndexAndCoordinate;
}

//ВВОД КООРДИНАТ 
void InputCoordinates(char field[Rows][Columns], Cell& cell, const int shipSize)
{
	const int zeroCode = 48;
	const int differenceBetweenIndexAndCoordinate = 1;

	if (shipSize == NULL)
		cout << "    " << "Ввод координатов выстрела:" << endl;
	else
		cout << "    " << "Ввод начальных координат корабля:" << endl;

	char letter;

	do
	{
		cout << "Введите букву => ";

		letter = _getch();

		cout << letter << endl;

		if (IsEnterNotCoordinateLetter(letter))
			cout << "Ошибка ввода!" << endl;

	} while (IsEnterNotCoordinateLetter(letter));

	cell.coordinates.abscissa = ConvertCoordinateLetterToNumber(letter);

	cout << endl;

	char digit;

	do
	{
		cout << "Введите цифру => ";

		digit = _getch();

		cout << digit << endl;

		if (digit < '0' || digit > '9')
			cout << "Ошибка ввода!" << endl;

	} while (digit < '0' || digit > '9');

	cell.coordinates.ordinate = digit - zeroCode + differenceBetweenIndexAndCoordinate;
}