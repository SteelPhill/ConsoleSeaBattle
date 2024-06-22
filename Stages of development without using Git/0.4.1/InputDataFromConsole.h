#pragma once

#include <iostream>
#include "TryReadValue.h"
#include "OutputDataToConsole.h"
using namespace std;


enum class MainMenuItems
{
	PlayerVsComputer = 1,
	ComputerVsComputer = 2,
	Rules = 3,
	ExitProgram = 0
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

enum class ShipsDirectionMenuItems
{
	Horizontal = 1,
	Vertical = 2,
	ItOnedeck = 3,
	GoToMainMenu = 0
};

MainMenuItems MainMenu()
{
	const int BeginRange = 0;
	const int EndRange = 3;

	MainMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Главное меню:" << endl << endl;
	cout << "1.Игрок против компьютера" << endl;
	cout << "2.Компьютер против компьютера" << endl;
	cout << "3.Правила игры" << endl;
	cout << "0.Выйти из игры" << endl << endl;

	cout << "Выберите номер пункта";
	choice = (MainMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;
	system("pause");
	system("cls");

	return choice;
}

DifficultySelectionMenuItems DifficultySelectionMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	DifficultySelectionMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Уровень сложности:" << endl << endl;
	cout << "1.Низкий" << endl;
	cout << "2.Высокий" << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта";
	choice = (DifficultySelectionMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;
	system("pause");
	system("cls");

	return choice;
}

ShipPlacementVariantsMenuItems ShipPlacementVariantsMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	ShipPlacementVariantsMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Варианты размещения кораблей:" << endl << endl;
	cout << "1.Автоматическое размещение" << endl;
	cout << "2.Ручное размещение" << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта";
	choice = (ShipPlacementVariantsMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;
	system("pause");
	system("cls");

	return choice;
}

ShipsDirectionMenuItems ShipsDirectionMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	ShipsDirectionMenuItems choice;

	cout << "Варианты размещения кораблей:" << endl;
	cout << "1.Горизонтальное размещение корабля" << endl;
	cout << "2.Вертикальное размещение корабля" << endl;
	cout << "0.Выйти в главное меню" << endl;

	cout << "Выберите номер пункта";
	choice = (ShipsDirectionMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;

	return choice;
}

//ПРОВЕРКА ВВЕДЕННОЙ БУКВЫ
inline bool IsEnterNotCoordinateLetter(const unsigned char letter)
{
	return !(letter >= (unsigned char)'А' && letter <= (unsigned char)'К') && !(letter >= (unsigned char)'а' && letter <= (unsigned char)'к') || letter == (unsigned char)'Й' || letter == (unsigned char)'й';
}

//ПРОВЕРКА НА ВОЗМОЖНОСТЬ ВЫСТРЕЛА
inline bool IsPossibleShootInCell(char field[Rows][Columns], Cell& shot)
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
		if (!shipSize)
		{
			cout << "\t " << "Фаза стрельбы" << endl << endl << endl;
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

		cin.clear();
		cin.get();

		cout << "Число:" << endl;
		shot.coordinates.ordinate = CinValueInRange(beginRange, endRange);
		cout << endl;

		cin.clear();
		cin.get();

		if (IsPossibleShootInCell(field, shot))
		{
			cout << "Выстрел по введенным координатам невозможен! Повторите ввод!" << endl << endl;
			system("pause");
			system("cls");
		}

	} while (IsPossibleShootInCell(field, shot));
}