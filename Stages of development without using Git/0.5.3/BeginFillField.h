#pragma once

#include <iostream>
#include "MenusAndActions.h"
#include "PrintPlayField.h"
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

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ОДНОПАЛУБНИКА
bool IsPossibleToPlaceOneDeck(char field[Rows][Columns], const Cell& startCell)
{
	for (int i = startCell.coordinates.ordinate - 1; i <= startCell.coordinates.ordinate + 1; i++)
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

//АВТОМАТИЧЕСКАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ОДНОПАЛУБНИКА
void AutoGetStartPointsForOneDeck(char field[Rows][Columns], Cell& startCell)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	do
	{
		startCell.coordinates.ordinate = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCell.coordinates.abscissa = rand() % (EndRange - BeginRange + 1) + BeginRange;

	} while (IsPossibleToPlaceOneDeck(field, startCell));
}

//АВТОМАТИЧЕСКОЕ РАЗМЕЩЕНИЕ КОРАБЛЕЙ С ЗАДАННЫМ РАЗМЕРОМ И КОЛИЧЕСТВОМ
void AutoShipsPlacement(char field[Rows][Columns], const int shipSize, const int shipsNumber)
{
	const int BeginRange = 1;
	const int EndRange = 2;
	const int HorizontalDirection = 1;
	const int VerticalDirection = 2;
	const int ItOneDeck = 0;

	int shipDirection;
	Cell startCoordinate;

	for (int i = 1; i <= shipsNumber; i++)
	{
		if (shipSize != ItOneDeck)
			shipDirection = rand() % (EndRange - BeginRange + 1) + BeginRange;
		else
			shipDirection = NULL;

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

		else if (shipDirection == NULL)
		{
			AutoGetStartPointsForOneDeck(field, startCoordinate);
			field[startCoordinate.coordinates.ordinate][startCoordinate.coordinates.abscissa] = Ship;
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

//ПРОВЕРКА НА ВОЗМОЖНОСТЬ РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ 
inline bool TryManuallyGetStartPointsForHorizontalShip(char field[Rows][Columns], Cell& startCell, const int shipSize)
{
	return startCell.coordinates.abscissa + shipSize >= Columns || IsPossibleToPlaceHorizontalShip(field, shipSize, startCell);
}

//ПРОВЕРКА НА ВОЗМОЖНОСТЬ РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
inline bool TryManuallyGetStartPointsForVerticalShip(char field[Rows][Columns], Cell& startCell, const int shipSize)
{
	return startCell.coordinates.ordinate + shipSize >= Rows || IsPossibleToPlaceVerticalShip(field, shipSize, startCell);
}

//РУЧНОЕ РАЗМЕЩЕНИЕ КОРАБЛЕЙ С ЗАДАННЫМ РАЗМЕРОМ И КОЛИЧЕСТВОМ
bool TryManuallyShipsPlacement(char field[Rows][Columns], const int shipSize, const int shipsNumber)
{
	const int BeginRange = 0;
	const int EndRange = 2;
	const int OneDeckSize = 1;

	bool isShipNotSet = true;

	Cell startCell;

	do
	{
		for (int i = 1; i <= shipsNumber; i++)
		{
			PrintOnlyOneField(field, shipSize);

			ShipsDirectionListItems shipDirection;

			if (shipSize != OneDeckSize)
				shipDirection = ShipsDirectionList();
			else
				shipDirection = ShipsDirectionListItems::ItOnedeck;

			switch (shipDirection)
			{
			case ShipsDirectionListItems::Horizontal:
			{
				InputCoordinates(field, startCell, shipSize);
				isShipNotSet = TryManuallyGetStartPointsForHorizontalShip(field, startCell, shipSize);
				break;
			}

			case ShipsDirectionListItems::Vertical:
			{
				InputCoordinates(field, startCell, shipSize);
				isShipNotSet = TryManuallyGetStartPointsForVerticalShip(field, startCell, shipSize);
				break;
			}

			case ShipsDirectionListItems::ItOnedeck:
			{
				InputCoordinates(field, startCell, shipSize);
				isShipNotSet = TryManuallyGetStartPointsForVerticalShip(field, startCell, shipSize);
				break;
			}

			case ShipsDirectionListItems::GoToMainMenu:
			{
				return false;
			}

			default:
				break;
			}

			if (isShipNotSet)
			{
				cout << "Установка корабля по заданным координатам невозможна! Попробуйте ещё раз!" << endl << endl;
				system("pause");
				system("cls");
				break;
			}

			switch (shipDirection)
			{
			case ShipsDirectionListItems::Horizontal:
			case ShipsDirectionListItems::ItOnedeck:
			{
				PlacementHorizontalShip(field, shipSize, startCell);
				break;
			}

			case ShipsDirectionListItems::Vertical:
			{
				PlacementVerticalShip(field, shipSize, startCell);
				break;
			}

			default:
				break;
			}

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