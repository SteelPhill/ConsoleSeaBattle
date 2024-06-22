#pragma once

#include <iostream>
#include "InputDataFromConsole.h"
#include "OutputDataToConsole.h"
using namespace std;


//НАЧАЛЬНОЕ ЗАПОЛНЕНИЕ ПОЛЯ
void FieldInitialFill(char playField[Rows][Columns])
{
	const int firstRowIndex = 0;
	const int lastRowIndex = 11;
	const int firstColumnsIndex = 0;
	const int lastColumnsIndex = 11;

	for (int j = 0; j < Columns; j++)
		playField[firstRowIndex][j] = Miss;

	for (int i = 1; i < Rows - 1; i++)
		for (int j = 1; j < Columns - 1; j++)
		{
			playField[i][firstColumnsIndex] = Miss;
			playField[i][j] = Empty;
			playField[i][lastColumnsIndex] = Miss;
		}

	for (int j = 0; j < Columns; j++)
		playField[lastRowIndex][j] = Miss;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
bool IsPossibleToPlaceHorizontalShip(char field[Rows][Columns], const int shipSize, const Cell& startCell)
{
	for (int i = startCell.coordinates.abscissa - 1; i <= startCell.coordinates.abscissa + shipSize; i++)
	{
		if (field[startCell.coordinates.ordinate - 1][i] == Ship)
			return true;
		if (field[startCell.coordinates.ordinate][i] == Ship)
			return true;
		if (field[startCell.coordinates.ordinate + 1][i] == Ship)
			return true;
	}

	return false;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
bool IsPossibleToPlaceVerticalShip(char field[Rows][Columns], const int shipSize, const Cell& startCell)
{
	for (int i = startCell.coordinates.ordinate - 1; i <= startCell.coordinates.ordinate + shipSize; i++)
	{
		if (field[i][startCell.coordinates.abscissa - 1] == Ship)
			return true;
		if (field[i][startCell.coordinates.abscissa] == Ship)
			return true;
		if (field[i][startCell.coordinates.abscissa + 1] == Ship)
			return true;
	}

	return false;
}

//РАЗМЕЩЕНИЕ ГОРИЗАНТАЛЬНОГО КОРАБЛЯ 
void PlacementHorizontalShip(char field[Rows][Columns], const int shipSize, const Cell& startCell)
{
	for (int i = startCell.coordinates.abscissa; i < startCell.coordinates.abscissa + shipSize; i++)
		field[startCell.coordinates.ordinate][i] = Ship;
}

//РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
void PlacementVerticalShip(char playField[Rows][Columns], const int shipSize, const Cell& startCell)
{
	for (int i = startCell.coordinates.ordinate; i < startCell.coordinates.ordinate + shipSize; i++)
		playField[i][startCell.coordinates.abscissa] = Ship;
}

//АВТОМАТИЧЕСКАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
void AutoGetStartPointsForHorizontalShip(char field[Rows][Columns], const int shipSize, Cell& startCell)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	bool isSetNotPossible = true;

	do
	{
		startCell.coordinates.ordinate = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCell.coordinates.abscissa = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCell.coordinates.abscissa + shipSize >= Columns)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorizontalShip(field, shipSize, startCell);

	} while (isSetNotPossible);
}

//АВТОМАТИЧЕСКАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
void AutoGetStartPointsForVerticalShip(char field[Rows][Columns], const int shipSize, Cell& startCell)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	bool isSetNotPossible = true;

	do
	{
		startCell.coordinates.ordinate = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCell.coordinates.abscissa = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCell.coordinates.ordinate + shipSize >= Rows)
			continue;

		isSetNotPossible = IsPossibleToPlaceVerticalShip(field, shipSize, startCell);

	} while (isSetNotPossible);
}

//АВТОМАТИЧЕСКОЕ РАЗМЕЩЕНИЕ КОРАБЛЕЙ ЗАДАННЫМ РАЗМЕРОМ И КОЛИЧЕСТВОМ
void AutoShipsPlacement(char field[Rows][Columns], const int shipSize, const int shipsNumber)
{
	const int BeginRange = 1;
	const int EndRange = 2;
	const int HorizontalDirection = 1;
	const int VerticalDirection = 2;

	for (int i = 1; i <= shipsNumber; i++)
	{

		int shipDirection = rand() % (EndRange - BeginRange + 1) + BeginRange;

		Cell startCoordinate;

		if (shipDirection == HorizontalDirection)
		{
			AutoGetStartPointsForHorizontalShip(field, shipSize, startCoordinate);
			PlacementHorizontalShip(field, shipSize, startCoordinate);
		}

		else if (shipDirection == VerticalDirection)
		{
			AutoGetStartPointsForVerticalShip(field, shipSize, startCoordinate);
			PlacementVerticalShip(field, shipSize, startCoordinate);
		}
	}
}

//АВТОМАТИЧЕСКОЕ ЗАПОЛНЕНИЕ ПОЛЯ КОРАБЛЯМИ
void AutoFillBattleField(char field[Rows][Columns])
{
	const int OneDeckSize = 1;
	const int TwoDeckSize = 2;
	const int ThreeDeckSize = 3;
	const int FourDeckSize = 4;

	const int OneDeckNumber = 4;
	const int TwoDeckNumber = 3;
	const int ThreeDeckNumber = 2;
	const int FourDeckNumber = 1;

	FieldInitialFill(field);

	AutoShipsPlacement(field, FourDeckSize, FourDeckNumber);
	AutoShipsPlacement(field, ThreeDeckSize, ThreeDeckNumber);
	AutoShipsPlacement(field, TwoDeckSize, TwoDeckNumber);
	AutoShipsPlacement(field, OneDeckSize, OneDeckNumber);
}

//РУЧНАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ 
bool TryManuallyGetStartPointsForHorizontalShip(char field[Rows][Columns], Cell& startCell, const int shipSize)
{
	InputCoordinates(field, startCell, shipSize);

	if (startCell.coordinates.abscissa + shipSize >= Columns || IsPossibleToPlaceHorizontalShip(field, shipSize, startCell))
	{
		cout << "Установка корабля по заданным координатам невозможна! Повторите ввод!" << endl << endl;
		return true;
	}

	return false;
}

//РУЧНАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
bool TryManuallyGetStartPointsForVerticalShip(char field[Rows][Columns], Cell& startCell, const int shipSize)
{
	InputCoordinates(field, startCell, shipSize);

	if (startCell.coordinates.ordinate + shipSize >= Rows || IsPossibleToPlaceVerticalShip(field, shipSize, startCell))
	{
		cout << "Установка корабля по заданным координатам невозможна! Повторите ввод!" << endl << endl;
		return true;
	}

	return false;
}

//РУЧНОЕ РАЗМЕЩЕНИЕ КОРАБЛЕЙ ЗАДАННЫМ РАЗМЕРОМ И КОЛИЧЕСТВОМ
bool TryManuallyShipsPlacement(char field[Rows][Columns], const int shipSize, const int shipsNumber)
{
	const int BeginRange = 0;
	const int EndRange = 2;
	const int OneDeckSize = 1;

	bool isShipNotSet = true;

	int i = 1;

	do
	{
		for (; i <= shipsNumber; i++)
		{
			cout << "     " << "Фаза размещения кораблей" << endl << endl << endl;
			cout << "      " << "Размещение " << shipSize << "-палубника" << endl << endl;

			PrintFieldForPlacement(field);

			ShipsDirectionMenuItems shipDirection;

			if (shipSize != OneDeckSize)
				shipDirection = ShipsDirectionMenu();
			else
				shipDirection = ShipsDirectionMenuItems::ItOnedeck;

			Cell startCell;

			switch (shipDirection)
			{
			case ShipsDirectionMenuItems::Horizontal:
			case ShipsDirectionMenuItems::ItOnedeck:
			{
				isShipNotSet = TryManuallyGetStartPointsForHorizontalShip(field, startCell, shipSize);
				break;
			}

			case ShipsDirectionMenuItems::Vertical:
			{
				isShipNotSet = TryManuallyGetStartPointsForVerticalShip(field, startCell, shipSize);
				break;
			}

			case ShipsDirectionMenuItems::GoToMainMenu:
			{
				return false;
			}

			default:
				break;
			}

			if (isShipNotSet)
			{
				system("pause");
				system("cls");
				break;
			}

			switch (shipDirection)
			{
			case ShipsDirectionMenuItems::Horizontal:
			case ShipsDirectionMenuItems::ItOnedeck:
			{
				PlacementHorizontalShip(field, shipSize, startCell);
				break;
			}

			case ShipsDirectionMenuItems::Vertical:
			{
				PlacementVerticalShip(field, shipSize, startCell);
				break;
			}

			default:
				break;
			}

			system("pause");
			system("cls");
		}

	} while (isShipNotSet);

	return true;
}

//РУЧНОЕ ЗАПОЛНЕНИЕ ПОЛЯ КОРАБЛЯМИ
bool TryManuallyFillBattleField(char field[Rows][Columns])
{
	const int OneDeckSize = 1;
	const int TwoDeckSize = 2;
	const int ThreeDeckSize = 3;
	const int FourDeckSize = 4;

	const int OneDeckNumber = 4;
	const int TwoDeckNumber = 3;
	const int ThreeDeckNumber = 2;
	const int FourDeckNumber = 1;

	FieldInitialFill(field);

	bool isShipPlacement;

	isShipPlacement = TryManuallyShipsPlacement(field, FourDeckSize, FourDeckNumber);
	if (!isShipPlacement)
		return false;

	isShipPlacement = TryManuallyShipsPlacement(field, ThreeDeckSize, ThreeDeckNumber);
	if (!isShipPlacement)
		return false;

	isShipPlacement = TryManuallyShipsPlacement(field, TwoDeckSize, TwoDeckNumber);
	if (!isShipPlacement)
		return false;

	isShipPlacement = TryManuallyShipsPlacement(field, OneDeckSize, OneDeckNumber);
	if (!isShipPlacement)
		return false;

	return true;
}