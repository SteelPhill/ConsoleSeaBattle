#pragma once

//ЗАПОЛНЕНИЕ ПОЛЯ ПРОБЕЛАМИ
void FillFieldToSpaces(char playField[Rows][Columns])
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			playField[i][j] = EmptyCell;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ В УГЛУ 
bool IsPossibleToPlaceHorizontalShipInCorner(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
{
	if (startCoordinates.x == 0 && startCoordinates.y == 0)
		for (int i = startCoordinates.x; i <= startCoordinates.x + shipSize; i++)
		{
			if (playField[startCoordinates.y][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y + 1][i] == ShipPart)
				return true;
		}

	else if (startCoordinates.x + shipSize == Columns && startCoordinates.y == 0)
		for (int i = startCoordinates.x - 1; i < startCoordinates.x + shipSize; i++)
		{
			if (playField[startCoordinates.y][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y + 1][i] == ShipPart)
				return true;
		}

	else if (startCoordinates.x == 0 && startCoordinates.y == Rows - 1)
		for (int i = startCoordinates.x; i <= startCoordinates.x + shipSize; i++)
		{
			if (playField[startCoordinates.y - 1][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y][i] == ShipPart)
				return true;
		}

	else if (startCoordinates.x + shipSize == Columns && startCoordinates.y == Rows - 1)
		for (int i = startCoordinates.x - 1; i < startCoordinates.x + shipSize; i++)
		{
			if (playField[startCoordinates.y - 1][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y][i] == ShipPart)
				return true;
		}

	return false;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ НА КРАЮ
bool IsPossibleToPlaceHorizontalShipOnEdge(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
{
	if (startCoordinates.x == 0 && startCoordinates.y != 0 && startCoordinates.y != Rows - 1)
		for (int i = startCoordinates.x; i <= startCoordinates.x + shipSize; i++)
		{
			if (playField[startCoordinates.y - 1][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y + 1][i] == ShipPart)
				return true;
		}

	else if (startCoordinates.x + shipSize == Columns && startCoordinates.y != 0 && startCoordinates.y != Rows - 1)
		for (int i = startCoordinates.x - 1; i < startCoordinates.x + shipSize; i++)
		{
			if (playField[startCoordinates.y - 1][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y + 1][i] == ShipPart)
				return true;
		}

	else if (startCoordinates.x != 0 && startCoordinates.x + shipSize != Columns && startCoordinates.y == 0)
		for (int i = startCoordinates.x - 1; i <= startCoordinates.x + shipSize; i++)
		{
			if (playField[startCoordinates.y][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y + 1][i] == ShipPart)
				return true;
		}

	else if (startCoordinates.x != 0 && startCoordinates.x + shipSize != Columns && startCoordinates.y == Rows - 1)
		for (int i = startCoordinates.x - 1; i <= startCoordinates.x + shipSize; i++)
		{
			if (playField[startCoordinates.y][i] == ShipPart)
				return true;
			if (playField[startCoordinates.y - 1][i] == ShipPart)
				return true;
		}

	return false;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ В ЦЕНТРЕ
bool IsPossibleToPlaceHorizontalShipInCenter(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
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

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ ДЛЯ КОМПА
void RandomStartPointsForHorizontalShip(char playField[Rows][Columns], const int shipSize, CellCoordinates& startCoordinates)
{
	const int BeginRange = 0;
	const int EndRange = 9;

	bool isSetNotPossible = true;

	do
	{
		startCoordinates.y = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCoordinates.x = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCoordinates.x + shipSize > Columns)
			continue;

		isSetNotPossible = false;

		isSetNotPossible = IsPossibleToPlaceHorizontalShipInCorner(playField, shipSize, startCoordinates);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorizontalShipOnEdge(playField, shipSize, startCoordinates);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorizontalShipInCenter(playField, shipSize, startCoordinates);

	} while (isSetNotPossible);
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ В УГЛУ 
bool IsPossibleToPlaceVerticalShipInCorner(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
{
	if (startCoordinates.x == 0 && startCoordinates.y == 0)
		for (int i = startCoordinates.y; i <= startCoordinates.y + shipSize; i++)
		{
			if (playField[i][startCoordinates.x] == ShipPart)
				return true;
			if (playField[i][startCoordinates.x + 1] == ShipPart)
				return true;
		}

	else if (startCoordinates.x == Columns - 1 && startCoordinates.y == 0)
		for (int i = startCoordinates.y; i <= startCoordinates.y + shipSize; i++)
		{
			if (playField[i][startCoordinates.x] == ShipPart)
				return true;
			if (playField[i][startCoordinates.x - 1] == ShipPart)
				return true;
		}

	else if (startCoordinates.x == 0 && startCoordinates.y + shipSize == Rows)
		for (int i = startCoordinates.y - 1; i < startCoordinates.y + shipSize; i++)
		{
			if (playField[i][startCoordinates.x] == ShipPart)
				return true;
			if (playField[i][startCoordinates.x + 1] == ShipPart)
				return true;
		}

	else if (startCoordinates.x == Columns - 1 && startCoordinates.y + shipSize == Rows)
		for (int i = startCoordinates.y - 1; i < startCoordinates.y + shipSize; i++)
		{
			if (playField[i][startCoordinates.x - 1] == ShipPart)
				return true;
			if (playField[i][startCoordinates.x] == ShipPart)
				return true;
		}

	return false;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ НА КРАЮ
bool IsPossibleToPlaceVerticalShipOnEdge(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
{
	if (startCoordinates.x == 0 && startCoordinates.y != 0 && startCoordinates.y + shipSize != Rows)
		for (int i = startCoordinates.y - 1; i <= startCoordinates.y + shipSize; i++)
		{
			if (playField[i][startCoordinates.x + 1] == ShipPart)
				return true;
			if (playField[i][startCoordinates.x] == ShipPart)
				return true;
		}

	else if (startCoordinates.x == Columns - 1 && startCoordinates.y != 0 && startCoordinates.y + shipSize != Rows)
		for (int i = startCoordinates.y - 1; i <= startCoordinates.y + shipSize; i++)
		{
			if (playField[i][startCoordinates.x - 1] == ShipPart)
				return true;
			if (playField[i][startCoordinates.x] == ShipPart)
				return true;
		}

	else if (startCoordinates.x != 0 && startCoordinates.x != Columns - 1 && startCoordinates.y == 0)
		for (int i = startCoordinates.y; i <= startCoordinates.y + shipSize; i++)
		{
			if (playField[i][startCoordinates.x - 1] == ShipPart)
				return true;
			if (playField[i][startCoordinates.x] == ShipPart)
				return true;
			if (playField[i][startCoordinates.x + 1] == ShipPart)
				return true;
		}

	else if (startCoordinates.x != 0 && startCoordinates.x != Columns - 1 && startCoordinates.y + shipSize == Rows)
		for (int i = startCoordinates.y - 1; i < startCoordinates.y + shipSize; i++)
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

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ В ЦЕНТРЕ
bool IsPossibleToPlaceVerticalShipInCenter(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
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

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ ДЛЯ КОМПА
void RandomStartPointsForVerticalShip(char playField[Rows][Columns], const int shipSize, CellCoordinates& startCoordinates)
{
	const int BeginRange = 0;
	const int EndRange = 9;

	bool isSetNotPossible = true;

	do
	{
		startCoordinates.y = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCoordinates.x = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCoordinates.y + shipSize > Rows)
			continue;

		isSetNotPossible = false;

		isSetNotPossible = IsPossibleToPlaceVerticalShipInCorner(playField, shipSize, startCoordinates);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceVerticalShipOnEdge(playField, shipSize, startCoordinates);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceVerticalShipInCenter(playField, shipSize, startCoordinates);

	} while (isSetNotPossible);
}

//ГОРИЗАНТАЛЬНОЕ РАЗМЕЩЕНИЕ КОРАБЛЯ ДЛЯ КОМПА
void SetHorizontalShip(char playField[Rows][Columns], const int shipSize, const CellCoordinates& startCoordinates)
{
	for (int i = startCoordinates.x; i < startCoordinates.x + shipSize; i++)
		playField[startCoordinates.y][i] = ShipPart;
}

//ВЕРТИКАЛЬНОЕ РАЗМЕЩЕНИЕ КОРАБЛЯ ДЛЯ КОМПА
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

//РАЗМЕЩЕНИЕ КОРАБЛЕЙ ДЛЯ КОМПА
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