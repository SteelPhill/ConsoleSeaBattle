#pragma once

#include <iostream>
#include "TryReadValue.h"
#include "PrintPlayField.h"
using namespace std;

#define CleaningInputStream cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

//ГЛАВНОЕ МЕНЮ 
MainMenuItems MainMenu()
{
	const int BeginRange = 0;
	const int EndRange = 3;

	MainMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Главное меню:" << endl << endl;
	cout << "1.Новая игра" << endl;
	cout << "2.Загрузить игру" << endl;
	cout << "3.Правила" << endl << endl;
	cout << "0.Выход из игры" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	choice = (MainMenuItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	system("cls");

	return choice;
}

//МЕНЮ ВЫБОРА РЕЖИМОВ ИГРЫ 
ModeMenuItems ModeMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	ModeMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Режимы игры:" << endl << endl;
	cout << "1.Игрок против компьютера" << endl;
	cout << "2.Компьютер против компьютера" << endl << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	choice = (ModeMenuItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	system("cls");

	return choice;
}

//МЕНЮ ВЫБОРА СЛОЖНОСТИ ИГРЫ
DifficultySelectionMenuItems DifficultySelectionMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	DifficultySelectionMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Уровень сложности:" << endl << endl;
	cout << "1.Низкий" << endl;
	cout << "2.Высокий" << endl << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
	choice = (DifficultySelectionMenuItems)CinValueInRange(BeginRange, EndRange);

	CleaningInputStream;

	system("cls");

	return choice;
}

//МЕНЮ ВАРИАНТОВ РАЗМЕЩЕНИЯ КОРАБЛЕЙ 
ShipPlacementVariantsMenuItems ShipPlacementVariantsMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	ShipPlacementVariantsMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Варианты размещения кораблей:" << endl << endl;
	cout << "1.Автоматическое размещение" << endl;
	cout << "2.Ручное размещение" << endl << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
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

	cout << "Варианты размещения кораблей:" << endl;
	cout << "1.Горизонтальное размещение корабля" << endl;
	cout << "2.Вертикальное размещение корабля" << endl;
	cout << "0.Выйти в главное меню" << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
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

	cout << "\t" << "ПАУЗА" << endl << endl;
	cout << "1.Продолжить игру" << endl;
	cout << "2.Сохранить игру" << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта и нажмите Enter" << endl;
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

	cout << endl;
	cout << "Следующий выстрел: нажмите Enter" << endl;
	cout << "Пауза: введите 0 затем нажмите Enter" << endl;

	do
	{
		cout << " => ";
		choice = cin.get();

		if (choice != ContinueGame)
			CleaningInputStream;

		if (choice != OpenPauseMenu && choice != ContinueGame)
			cout << "Ошибка!" << endl;

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
inline bool IsPossibleShootByCell(char field[Rows][Columns], Cell& shot)
{
	return field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit || field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss || field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Killed;
}

//ВВОД КООРДИНАТ 
void InputCoordinates(char field[Rows][Columns], Cell& shot, const int shipSize)
{
	const int beginRange = 1;
	const int endRange = 10;

	do
	{
		if (shipSize == NULL)
		{
			cout << "\t " << "Фаза стрельбы" << endl << endl;
			PrintFieldForShot(field);
			cout << "Введите координаты выстрела:" << endl;
		}
		else
			cout << "Введите начальные координаты корабля:" << endl;

		cout << "Буква:" << endl;
		unsigned char letter;

		do
		{
			letter = CinValue<unsigned char>();

			CleaningInputStream;

			if (IsEnterNotCoordinateLetter(letter))
				cout << "Ошибка!" << endl;

		} while (IsEnterNotCoordinateLetter(letter));

		switch (letter)
		{
		case (unsigned char)'А':
		case (unsigned char)'а':
			shot.coordinates.abscissa = 1;
			break;

		case (unsigned char)'Б':
		case (unsigned char)'б':
			shot.coordinates.abscissa = 2;
			break;

		case (unsigned char)'В':
		case (unsigned char)'в':
			shot.coordinates.abscissa = 3;
			break;

		case (unsigned char)'Г':
		case (unsigned char)'г':
			shot.coordinates.abscissa = 4;
			break;

		case (unsigned char)'Д':
		case (unsigned char)'д':
			shot.coordinates.abscissa = 5;
			break;

		case (unsigned char)'Е':
		case (unsigned char)'е':
			shot.coordinates.abscissa = 6;
			break;

		case (unsigned char)'Ж':
		case (unsigned char)'ж':
			shot.coordinates.abscissa = 7;
			break;

		case (unsigned char)'З':
		case (unsigned char)'з':
			shot.coordinates.abscissa = 8;
			break;

		case (unsigned char)'И':
		case (unsigned char)'и':
			shot.coordinates.abscissa = 9;
			break;

		case (unsigned char)'К':
		case (unsigned char)'к':
			shot.coordinates.abscissa = 10;
			break;

		default:
			break;
		}

		cout << "Число:" << endl;
		shot.coordinates.ordinate = CinValueInRange(beginRange, endRange);

		CleaningInputStream;

		if (IsPossibleShootByCell(field, shot))
		{
			cout << "Выстрел по введенным координатам невозможен! Попробуйте ещё раз!" << endl;
			system("pause");
			system("cls");
		}

	} while (IsPossibleShootByCell(field, shot));
}

//ВВОД ИМЕНИ ИГРОКА
void InputPlayerNames(string& playerName, string& computerName)
{
	const int maxNameSize = 10;

	do
	{
		cout << "Введите имя игрока" << endl << endl;

		playerName = CinValue<string>();

		CleaningInputStream;

		cout << endl;

		if (playerName.size() > maxNameSize)
			cout << "Ошибка! Имя не может содержать более 10 символов" << endl << endl;

		system("pause");
		system("cls");

	} while (playerName.size() > maxNameSize);

	do
	{
		cout << "Введите имя противника" << endl << endl;

		computerName = CinValue<string>();

		CleaningInputStream;

		cout << endl;

		if (computerName.size() > maxNameSize)
			cout << "Ошибка! Имя не может содержать более 10 символов" << endl << endl;

		system("pause");
		system("cls");

	} while (computerName.size() > maxNameSize);
}