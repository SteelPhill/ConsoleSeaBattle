#pragma once

#define BeginCoordinateRange 1
#define EndCoordinateRange 10
#define OneDeckSize 1
#define TwoDeckSize 2
#define ThreeDeckSize 3
#define FourDeckSize 4
#define OneDeckNumber 4
#define TwoDeckNumber 3
#define ThreeDeckNumber 2
#define FourDeckNumber 1

#include <iostream>
#include "MenusAndActions.h"
#include "PrintPlayField.h"
using namespace std;


//НАЧАЛЬНОЕ ЗАПОЛНЕНИЕ ПОЛЯ
void FieldInitialFill(char playField[Rows][Columns])
{
	const int firstRowIndex = 0;
	const int lastRowIndex = 11;
	const int firstColumnIndex = 0;
	const int lastColumnIndex = 11;

	for (int j = 0; j < Columns; j++)
		playField[firstRowIndex][j] = Miss;

	for (int i = 1; i < Rows - 1; i++)
	{
		playField[i][firstColumnIndex] = Miss;

		for (int j = 1; j < Columns - 1; j++)
			playField[i][j] = Empty;
			
		playField[i][lastColumnIndex] = Miss;
	}

	for (int j = 0; j < Columns; j++)
		playField[lastRowIndex][j] = Miss;
}

//ПРОВЕРКА, ЕСТЬ ЛИ РЯДОМ С ГОРИЗОНТАЛЬНЫМ КОРАБЛЕМ ДРУГИЕ КОРАБЛИ
bool IsAnyShipsNearHorizontalShip(char field[Rows][Columns], const int shipSize, const Cell& startCell)
{
	for (int i = startCell.coordinates.abscissa - 1; i <= startCell.coordinates.abscissa + shipSize; i++)
	{
		if (field[startCell.coordinates.ordinate - 1][i] == Ship)
			return true;
		else if (field[startCell.coordinates.ordinate][i] == Ship)
			return true;
		else if (field[startCell.coordinates.ordinate + 1][i] == Ship)
			return true;
	}

	return false;
}

//ПРОВЕРКА, ЕСТЬ ЛИ РЯДОМ С ВЕРТИКАЛЬНЫМ КОРАБЛЕМ ДРУГИЕ КОРАБЛИ
bool IsAnyShipsNearVerticalShip(char field[Rows][Columns], const int shipSize, const Cell& startCell)
{
	for (int i = startCell.coordinates.ordinate - 1; i <= startCell.coordinates.ordinate + shipSize; i++)
	{
		if (field[i][startCell.coordinates.abscissa - 1] == Ship)
			return true;
		else if (field[i][startCell.coordinates.abscissa] == Ship)
			return true;
		else if (field[i][startCell.coordinates.abscissa + 1] == Ship)
			return true;
	}

	return false;
}

//ПРОВЕРКА, ЕСТЬ ЛИ РЯДОМ С ОДНОПАЛУБНИКОМ КОРАБЛИ
bool IsAnyShipsNearOneDeck(char field[Rows][Columns], const Cell& cell)
{
	for (int i = cell.coordinates.ordinate - 1; i <= cell.coordinates.ordinate + 1; i++)
	{
		if (field[i][cell.coordinates.abscissa - 1] == Ship)
			return true;
		else if (field[i][cell.coordinates.abscissa] == Ship)
			return true;
		else if (field[i][cell.coordinates.abscissa + 1] == Ship)
			return true;
	}

	return false;
}

//ПРОВЕРКА НА ВОЗМОЖНОСТЬ РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ 
bool IsPossiblePlacementHorizontalShip(char field[Rows][Columns], Cell& startCell, const int shipSize)
{
	return startCell.coordinates.abscissa + shipSize >= Columns || IsAnyShipsNearHorizontalShip(field, shipSize, startCell);
}

//ПРОВЕРКА НА ВОЗМОЖНОСТЬ РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
bool IsPossiblePlacementVerticalShip(char field[Rows][Columns], Cell& startCell, const int shipSize)
{
	return startCell.coordinates.ordinate + shipSize >= Rows || IsAnyShipsNearVerticalShip(field, shipSize, startCell);
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
	do
	{
		startCell.coordinates.ordinate = rand() % (EndCoordinateRange - BeginCoordinateRange + 1) + BeginCoordinateRange;
		startCell.coordinates.abscissa = rand() % (EndCoordinateRange - BeginCoordinateRange + 1) + BeginCoordinateRange;

	} while (IsPossiblePlacementHorizontalShip(field, startCell, shipSize));
}

//АВТОМАТИЧЕСКАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
void AutoGetStartPointsForVerticalShip(char field[Rows][Columns], const int shipSize, Cell& startCell)
{
	do
	{
		startCell.coordinates.ordinate = rand() % (EndCoordinateRange - BeginCoordinateRange + 1) + BeginCoordinateRange;
		startCell.coordinates.abscissa = rand() % (EndCoordinateRange - BeginCoordinateRange + 1) + BeginCoordinateRange;

	} while (IsPossiblePlacementVerticalShip(field, startCell, shipSize));
}

//АВТОМАТИЧЕСКАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ОДНОПАЛУБНИКА
void AutoGetStartPointsForOneDeck(char field[Rows][Columns], Cell& cell)
{
	do
	{
		cell.coordinates.ordinate = rand() % (EndCoordinateRange - BeginCoordinateRange + 1) + BeginCoordinateRange;
		cell.coordinates.abscissa = rand() % (EndCoordinateRange - BeginCoordinateRange + 1) + BeginCoordinateRange;

	} while (IsAnyShipsNearOneDeck(field, cell));
}

//АВТОМАТИЧЕСКОЕ РАЗМЕЩЕНИЕ КОРАБЛЕЙ С ЗАДАННЫМ РАЗМЕРОМ И КОЛИЧЕСТВОМ
void AutoShipsPlacement(char field[Rows][Columns], const int shipSize, const int shipsNumber)
{
	const int beginDirectionRange = 1;
	const int endDirectionRange = 2;
	const int horizontalDirection = 1;
	const int verticalDirection = 2;

	int shipDirection;
	Cell startCoordinate;

	for (int i = 1; i <= shipsNumber; i++)
	{
		if (shipSize != OneDeckSize)
			shipDirection = rand() % (endDirectionRange - beginDirectionRange + 1) + beginDirectionRange;
		else
			shipDirection = 0;

		if (shipDirection == horizontalDirection)
		{
			AutoGetStartPointsForHorizontalShip(field, shipSize, startCoordinate);
			PlacementHorizontalShip(field, shipSize, startCoordinate);
		}
		else if (shipDirection == verticalDirection)
		{
			AutoGetStartPointsForVerticalShip(field, shipSize, startCoordinate);
			PlacementVerticalShip(field, shipSize, startCoordinate);
		}
		else if (shipDirection == 0)
		{
			AutoGetStartPointsForOneDeck(field, startCoordinate);
			field[startCoordinate.coordinates.ordinate][startCoordinate.coordinates.abscissa] = Ship;
		}
	}
}

//АВТОМАТИЧЕСКОЕ ЗАПОЛНЕНИЕ ПОЛЯ КОРАБЛЯМИ
void AutoFillField(char field[Rows][Columns])
{
	FieldInitialFill(field);

	AutoShipsPlacement(field, FourDeckSize, FourDeckNumber);
	AutoShipsPlacement(field, ThreeDeckSize, ThreeDeckNumber);
	AutoShipsPlacement(field, TwoDeckSize, TwoDeckNumber);
	AutoShipsPlacement(field, OneDeckSize, OneDeckNumber);
}

//РУЧНОЕ РАЗМЕЩЕНИЕ КОРАБЛЕЙ С ЗАДАННЫМ РАЗМЕРОМ И КОЛИЧЕСТВОМ
bool TryManuallyShipsPlacement(char field[Rows][Columns], const int shipSize, const int shipsNumber)
{
	ShipsDirectionListItems shipDirection;
	Cell startCell;

	bool isShipNotSet = true;

	int i = 1;

	do
	{
		for (; i <= shipsNumber; i++)
		{
			PrintOnlyOneField(field, shipSize);

			if (shipSize != OneDeckSize)
				shipDirection = ShipsDirectionList();
			else
				shipDirection = ShipsDirectionListItems::ItOnedeck;

			switch (shipDirection)
			{
			case ShipsDirectionListItems::Horizontal:
			{
				InputCoordinates(field, startCell, shipSize);
				isShipNotSet = IsPossiblePlacementHorizontalShip(field, startCell, shipSize);
				if (!isShipNotSet)
					PlacementHorizontalShip(field, shipSize, startCell);
				break;
			}

			case ShipsDirectionListItems::Vertical:
			{
				InputCoordinates(field, startCell, shipSize);
				isShipNotSet = IsPossiblePlacementVerticalShip(field, startCell, shipSize);
				if (!isShipNotSet)
					PlacementVerticalShip(field, shipSize, startCell);
				break;
			}

			case ShipsDirectionListItems::ItOnedeck:
			{
				InputCoordinates(field, startCell, shipSize);
				isShipNotSet = IsAnyShipsNearOneDeck(field, startCell);
				if (!isShipNotSet)
					field[startCell.coordinates.ordinate][startCell.coordinates.abscissa] = Ship;
				break;
			}

			case ShipsDirectionListItems::GoToMainMenu:
			{
				return true;
			}
			}

			if (isShipNotSet)
			{
				cout << endl;
				cout << "Установка корабля по заданным координатам невозможна! Попробуйте ещё раз!" << endl << endl;
				system("pause");
				system("cls");
				break;
			}

			system("cls");
		}

	} while (isShipNotSet);

	return false;
}

//РУЧНОЕ ЗАПОЛНЕНИЕ ПОЛЯ КОРАБЛЯМИ
bool TryManuallyFillField(char field[Rows][Columns])
{
	FieldInitialFill(field);

	bool isReturnToMainMenu;

	isReturnToMainMenu = TryManuallyShipsPlacement(field, FourDeckSize, FourDeckNumber);
	if (isReturnToMainMenu)
		return false;

	isReturnToMainMenu = TryManuallyShipsPlacement(field, ThreeDeckSize, ThreeDeckNumber);
	if (isReturnToMainMenu)
		return false;

	isReturnToMainMenu = TryManuallyShipsPlacement(field, TwoDeckSize, TwoDeckNumber);
	if (isReturnToMainMenu)
		return false;

	isReturnToMainMenu = TryManuallyShipsPlacement(field, OneDeckSize, OneDeckNumber);
	if (isReturnToMainMenu)
		return false;

	return true;
}