#pragma once

//ЗАПОЛНЕНИЕ ПОЛЯ ПРОБЕЛАМИ
void FillFieldToSpaces(char playField[Rows][Columns])
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			playField[i][j] = ' ';
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ В УГЛУ 
bool IsPossibleToPlaceHorizontalShipInCorner(char playField[Rows][Columns], const int shipSize, int horizontalStartPoint, int verticalStartPoint, const char shipSymbol)
{
	if (horizontalStartPoint == 0 && verticalStartPoint == 0)
		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
		{
			if (playField[verticalStartPoint][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint + 1][i] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint + shipSize == Columns && verticalStartPoint == 0)
		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
		{
			if (playField[verticalStartPoint][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint + 1][i] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint == 0 && verticalStartPoint == Rows - 1)
		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
		{
			if (playField[verticalStartPoint - 1][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint][i] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint + shipSize == Columns && verticalStartPoint == Rows - 1)
		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
		{
			if (playField[verticalStartPoint - 1][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint][i] == shipSymbol)
				return true;
		}

	return false;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ НА КРАЮ
bool IsPossibleToPlaceHorizontalShipOnEdge(char playField[Rows][Columns], const int shipSize, int horizontalStartPoint, int verticalStartPoint, const char shipSymbol)
{
	if (horizontalStartPoint == 0 && verticalStartPoint != 0 && verticalStartPoint != Rows - 1)
		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
		{
			if (playField[verticalStartPoint - 1][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint + 1][i] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint + shipSize == Columns && verticalStartPoint != 0 && verticalStartPoint != Rows - 1)
		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
		{
			if (playField[verticalStartPoint - 1][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint + 1][i] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint != 0 && horizontalStartPoint + shipSize != Columns && verticalStartPoint == 0)
		for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
		{
			if (playField[verticalStartPoint][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint + 1][i] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint != 0 && horizontalStartPoint + shipSize != Columns && verticalStartPoint == Rows - 1)
		for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
		{
			if (playField[verticalStartPoint][i] == shipSymbol)
				return true;
			if (playField[verticalStartPoint - 1][i] == shipSymbol)
				return true;
		}

	return false;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ В ЦЕНТРЕ
bool IsPossibleToPlaceHorizontalShipInCenter(char playField[Rows][Columns], const int shipSize, int horizontalStartPoint, int verticalStartPoint, const char shipSymbol)
{
	for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
	{
		if (playField[verticalStartPoint - 1][i] == shipSymbol)
			return true;
		if (playField[verticalStartPoint][i] == shipSymbol)
			return true;
		if (playField[verticalStartPoint + 1][i] == shipSymbol)
			return true;
	}

	return false;
}

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ ДЛЯ КОМПА
void RandomStartPointsForHorizontalShip(char playField[Rows][Columns], const int shipSize, int& horizontalStartPoint, int& verticalStartPoint, const char shipSymbol)
{
	const int BeginRange = 0;
	const int EndRange = 9;

	bool isSetNotPossible = true;

	do
	{
		verticalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;
		horizontalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (horizontalStartPoint + shipSize > Columns)
			continue;

		isSetNotPossible = false;

		isSetNotPossible = IsPossibleToPlaceHorizontalShipInCorner(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorizontalShipOnEdge(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorizontalShipInCenter(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);

	} while (isSetNotPossible);
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ В УГЛУ 
bool IsPossibleToPlaceVerticalShipInCorner(char playField[Rows][Columns], const int shipSize, int horizontalStartPoint, int verticalStartPoint, const char shipSymbol)
{
	if (horizontalStartPoint == 0 && verticalStartPoint == 0)
		for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
		{
			if (playField[i][horizontalStartPoint] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint == Columns - 1 && verticalStartPoint == 0)
		for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
		{
			if (playField[i][horizontalStartPoint] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint == 0 && verticalStartPoint + shipSize == Rows)
		for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
		{
			if (playField[i][horizontalStartPoint] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint == Columns - 1 && verticalStartPoint + shipSize == Rows)
		for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
		{
			if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint] == shipSymbol)
				return true;
		}

	return false;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ НА КРАЮ
bool IsPossibleToPlaceVerticalShipOnEdge(char playField[Rows][Columns], const int shipSize, int horizontalStartPoint, int verticalStartPoint, const char shipSymbol)
{
	if (horizontalStartPoint == 0 && verticalStartPoint != 0 && verticalStartPoint + shipSize != Rows)
		for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
		{
			if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint == Columns - 1 && verticalStartPoint != 0 && verticalStartPoint + shipSize != Rows)
		for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
		{
			if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint != 0 && horizontalStartPoint != Columns - 1 && verticalStartPoint == 0)
		for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
		{
			if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				return true;
		}

	else if (horizontalStartPoint != 0 && horizontalStartPoint != Columns - 1 && verticalStartPoint + shipSize == Rows)
		for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
		{
			if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint] == shipSymbol)
				return true;
			if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				return true;
		}

	return false;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ В ЦЕНТРЕ
bool IsPossibleToPlaceVerticalShipInCenter(char playField[Rows][Columns], const int shipSize, int horizontalStartPoint, int verticalStartPoint, const char shipSymbol)
{
	for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
	{
		if (playField[i][horizontalStartPoint - 1] == shipSymbol)
			return true;
		if (playField[i][horizontalStartPoint] == shipSymbol)
			return true;
		if (playField[i][horizontalStartPoint + 1] == shipSymbol)
			return true;
	}

	return false;
}

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ ДЛЯ КОМПА
void RandomStartPointsForVerticalShip(char playField[Rows][Columns], const int shipSize, int& horizontalStartPoint, int& verticalStartPoint, const char shipSymbol)
{
	const int BeginRange = 0;
	const int EndRange = 9;

	bool isSetNotPossible = true;

	do
	{
		verticalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;
		horizontalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (verticalStartPoint + shipSize > Rows)
			continue;

		isSetNotPossible = false;

		isSetNotPossible = IsPossibleToPlaceVerticalShipInCorner(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceVerticalShipOnEdge(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceVerticalShipInCenter(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
		
	} while (isSetNotPossible);
}

//ГОРИЗАНТАЛЬНОЕ РАЗМЕЩЕНИЕ КОРАБЛЯ ДЛЯ КОМПА
void SetHorizontalShip(char playField[Rows][Columns], const int shipSize, const int horizontalStartPoint, const int verticalStartPoint, const char shipSymbol)
{
	for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
		playField[verticalStartPoint][i] = shipSymbol;
}

//ВЕРТИКАЛЬНОЕ РАЗМЕЩЕНИЕ КОРАБЛЯ ДЛЯ КОМПА
void SetVerticalShip(char playField[Rows][Columns], const int shipSize, const int horizontalStartPoint, const int verticalStartPoint, const char shipSymbol)
{
	for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
		playField[i][horizontalStartPoint] = shipSymbol;
}

//РАЗМЕЩЕНИЕ КОРАБЛЕЙ С ЗАДАННЫМ РАЗМЕРОМ
void SetShips(char playField[Rows][Columns], const int shipSize, const int shipsNumber, const char shipSymbol)
{
	const int BeginRange = 1;
	const int EndRange = 2;
	const int HorizontalShipDirection = 1;
	const int VerticalShipDirection = 2;

	for (int i = 1; i <= shipsNumber; i++)
	{

		int shipDirection = rand() % (EndRange - BeginRange + 1) + BeginRange;

		int horizontalStartPoint;
		int verticalStartPoint;

		if (shipDirection == HorizontalShipDirection)
		{
			RandomStartPointsForHorizontalShip(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
			SetHorizontalShip(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
		}

		else if (shipDirection == VerticalShipDirection)
		{
			RandomStartPointsForVerticalShip(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
			SetVerticalShip(playField, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
		}
	}
}

//РАЗМЕЩЕНИЕ КОРАБЛЕЙ ДЛЯ КОМПА
void FillPlayField(char playField[Rows][Columns])
{
	const char ShipSymbol = 'O';

	const int OneDeckSize = 1;
	const int TwoDeckSize = 2;
	const int ThreeDeckSize = 3;
	const int FourDeckSize = 4;

	const int OneDeckNumber = 4;
	const int TwoDeckNumber = 3;
	const int ThreeDeckNumber = 2;
	const int FourDeckNumber = 1;

	FillFieldToSpaces(playField);

	SetShips(playField, FourDeckSize, FourDeckNumber, ShipSymbol);
	SetShips(playField, ThreeDeckSize, ThreeDeckNumber, ShipSymbol);
	SetShips(playField, TwoDeckSize, TwoDeckNumber, ShipSymbol);
	SetShips(playField, OneDeckSize, OneDeckNumber, ShipSymbol);
	
}