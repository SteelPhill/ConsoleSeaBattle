#pragma once

//НАЧАЛЬНОЕ ЗАПОЛНЕНИЕ ПОЛЯ ПРОБЕЛАМИ
void FillFieldToSpaces(char playField[Rows][Columns])
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			playField[i][j] = EmptyCell;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ
bool IsPossibleToPlaceHorizontalShip(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
{
	for (int i = startCoordinates.x - 1; i <= startCoordinates.x + shipSize; i++)
	{
		if (playField[startCoordinates.y - 1][i] == ShipPart)
			return true;
		if (playField[startCoordinates.y][i] == ShipPart)
			return true;
		if (playField[startCoordinates.y + 1][i] == ShipPart)
			return true;
	}

	return false;
}

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ
void RandomStartPointsForHorizontalShip(char playField[Rows][Columns], const int shipSize, CellCoordinates& startCoordinates)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	bool isSetNotPossible = true;

	do
	{
		startCoordinates.y = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCoordinates.x = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCoordinates.x + shipSize >= Columns)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorizontalShip(playField, shipSize, startCoordinates);

	} while (isSetNotPossible);
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ
bool IsPossibleToPlaceVerticalShip(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
{
	for (int i = startCoordinates.y - 1; i <= startCoordinates.y + shipSize; i++)
	{
		if (playField[i][startCoordinates.x - 1] == ShipPart)
			return true;
		if (playField[i][startCoordinates.x] == ShipPart)
			return true;
		if (playField[i][startCoordinates.x + 1] == ShipPart)
			return true;
	}

	return false;
}

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ 
void RandomStartPointsForVerticalShip(char playField[Rows][Columns], const int shipSize, CellCoordinates& startCoordinates)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	bool isSetNotPossible = true;

	do
	{
		startCoordinates.y = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCoordinates.x = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCoordinates.y + shipSize >= Rows)
			continue;

		isSetNotPossible = IsPossibleToPlaceVerticalShip(playField, shipSize, startCoordinates);

	} while (isSetNotPossible);
}

//РАЗМЕЩЕНИЕ ГОРИЗАНТАЛЬНЫХ КОРАБЛЕЙ 
void SetHorizontalShip(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
{
	for (int i = startCoordinates.x; i < startCoordinates.x + shipSize; i++)
		playField[startCoordinates.y][i] = ShipPart;
}

//РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ 
void SetVerticalShip(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
{
	for (int i = startCoordinates.y; i < startCoordinates.y + shipSize; i++)
		playField[i][startCoordinates.x] = ShipPart;
}

//РАЗМЕЩЕНИЕ КОРАБЛЕЙ С ЗАДАННЫМ РАЗМЕРОМ
void SetShips(char playField[Rows][Columns], const int shipSize, const int shipsNumber)
{
	const int BeginRange = 1;
	const int EndRange = 2;
	const int HorizontalShipDirection = 1;
	const int VerticalShipDirection = 2;

	for (int i = 1; i <= shipsNumber; i++)
	{

		int shipDirection = rand() % (EndRange - BeginRange + 1) + BeginRange;

		CellCoordinates startCoordinates;

		if (shipDirection == HorizontalShipDirection)
		{
			RandomStartPointsForHorizontalShip(playField, shipSize, startCoordinates);
			SetHorizontalShip(playField, shipSize, startCoordinates);
		}

		else if (shipDirection == VerticalShipDirection)
		{
			RandomStartPointsForVerticalShip(playField, shipSize, startCoordinates);
			SetVerticalShip(playField, shipSize, startCoordinates);
		}
	}
}

//ЗАПОЛНЕНИЕ ПОЛЯ КОРАБЛЯМИ
void FillPlayField(char playField[Rows][Columns])
{
	const int OneDeckSize = 1;
	const int TwoDeckSize = 2;
	const int ThreeDeckSize = 3;
	const int FourDeckSize = 4;

	const int OneDeckNumber = 4;
	const int TwoDeckNumber = 3;
	const int ThreeDeckNumber = 2;
	const int FourDeckNumber = 1;

	FillFieldToSpaces(playField);

	SetShips(playField, FourDeckSize, FourDeckNumber);
	SetShips(playField, ThreeDeckSize, ThreeDeckNumber);
	SetShips(playField, TwoDeckSize, TwoDeckNumber);
	SetShips(playField, OneDeckSize, OneDeckNumber);
}