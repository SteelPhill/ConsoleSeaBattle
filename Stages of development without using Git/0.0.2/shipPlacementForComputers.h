#pragma once


//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ В УГЛУ 
bool IsPossibleToPlaceHorShipInCorner(char playField[10][10], const int rows, const int columns, const int shipSize, int horizontalStartPoint, int verticalStartPoint, const char shipSymbol)
{
	bool isSetNotPossible = false;

	if (horizontalStartPoint == 0 && verticalStartPoint == 0)
		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			if (playField[verticalStartPoint][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint + 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}

	else if (horizontalStartPoint + shipSize == columns && verticalStartPoint == 0)
		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			if (playField[verticalStartPoint][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint + 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}

	else if (horizontalStartPoint == 0 && verticalStartPoint == rows - 1)
		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			if (playField[verticalStartPoint - 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}

	else if (horizontalStartPoint + shipSize == columns && verticalStartPoint == rows - 1)
		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			if (playField[verticalStartPoint - 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}

	return isSetNotPossible;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ НА КРАЮ
bool IsPossibleToPlaceHorShipOnEdge(char playField[10][10], const int rows, const int columns, const int shipSize, int horizontalStartPoint, int verticalStartPoint, const char shipSymbol)
{
	bool isSetNotPossible = false;

	if (horizontalStartPoint == 0 && verticalStartPoint != 0 && verticalStartPoint != rows - 1)
		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			if (playField[verticalStartPoint - 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint + 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}

	else if (horizontalStartPoint + shipSize == columns && verticalStartPoint != 0 && verticalStartPoint != rows - 1)
		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			if (playField[verticalStartPoint - 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint + 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}

	else if (horizontalStartPoint != 0 && horizontalStartPoint + shipSize != columns && verticalStartPoint == 0)
		for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
			if (playField[verticalStartPoint][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint + 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}

	else if (horizontalStartPoint != 0 && horizontalStartPoint + shipSize != columns && verticalStartPoint == rows - 1)
		for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
			if (playField[verticalStartPoint][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}
			else if (playField[verticalStartPoint - 1][i] == shipSymbol)
			{
				isSetNotPossible = true;
				break;
			}

	return isSetNotPossible;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ В ЦЕНТРЕ
bool IsPossibleToPlaceHorShipInCenter(char playField[10][10], const int rows, const int columns, const int shipSize, int horizontalStartPoint, int verticalStartPoint, const char shipSymbol)
{
	bool isSetNotPossible = false;

	for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
		if (playField[verticalStartPoint - 1][i] == shipSymbol)
		{
			isSetNotPossible = true;
			break;
		}
		else if (playField[verticalStartPoint][i] == shipSymbol)
		{
			isSetNotPossible = true;
			break;
		}
		else if (playField[verticalStartPoint + 1][i] == shipSymbol)
		{
			isSetNotPossible = true;
			break;
		}

	return isSetNotPossible;
}

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ ДЛЯ КОМПА
void RandomStartPointsForHorizontalShip(char playField[10][10], const int rows, const int columns, const int shipSize, int& horizontalStartPoint, int& verticalStartPoint, const char shipSymbol)
{
	const int BeginRange = 0;
	const int EndRange = 9;

	bool isSetNotPossible = true;

	do
	{
		verticalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;
		horizontalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;

		isSetNotPossible = false;

		if (horizontalStartPoint + shipSize > columns)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorShipInCorner(playField, rows, columns, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorShipOnEdge(playField, rows, columns, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);
		if (isSetNotPossible)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorShipInCenter(playField, rows, columns, shipSize, horizontalStartPoint, verticalStartPoint, shipSymbol);

	} while (isSetNotPossible);
}

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ ДЛЯ КОМПА
void RandomStartPointsForVerticalShip(char playField[10][10], const int rows, const int columns, const int shipSize, int& horizontalStartPoint, int& verticalStartPoint, const char shipSymbol)
{
	const int BeginRange = 0;
	const int EndRange = 9;

	bool isSetNotPossible = true;

	do
	{
		verticalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;
		horizontalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (verticalStartPoint + shipSize > rows)
			continue;

		isSetNotPossible = false;

		if (horizontalStartPoint == 0 && verticalStartPoint == 0)
		{
			for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == columns - 1 && verticalStartPoint == 0)
		{
			for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == 0 && verticalStartPoint + shipSize == rows)
		{
			for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == columns - 1 && verticalStartPoint + shipSize == rows)
		{
			for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == 0 && verticalStartPoint != 0 && verticalStartPoint + shipSize != rows)
		{
			for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == columns - 1 && verticalStartPoint != 0 && verticalStartPoint + shipSize != rows)
		{
			for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint != 0 && horizontalStartPoint != columns - 1 && verticalStartPoint == 0)
		{
			for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint != 0 && horizontalStartPoint != columns - 1 && verticalStartPoint + shipSize == rows)
		{
			for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else
		{
			for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

	} while (isSetNotPossible);
}

//ГОРИЗАНТАЛЬНОЕ РАЗМЕЩЕНИЕ КОРАБЛЯ ДЛЯ КОМПА
void SetHorizontalShip(char playField[10][10], const int shipSize, const int horizontalStartPoint, const int verticalStartPoint, const char shipSymbol)
{
	for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
		playField[verticalStartPoint][i] = shipSymbol;
}

//ВЕРТИКАЛЬНОЕ РАЗМЕЩЕНИЕ КОРАБЛЯ ДЛЯ КОМПА
void SetVerticalShip(char playField[10][10], const int shipSize, const int horizontalStartPoint, const int verticalStartPoint, const char shipSymbol)
{
	for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
		playField[i][horizontalStartPoint] = shipSymbol;
}

//РАЗМЕЩЕНИЕ КОРАБЛЕЙ ДЛЯ КОМПА
void SetShip(char playField[10][10], const int rows, const int columns, const int shipSize)
{
	const char ShipSymbol = 'O';
	const int BeginRange = 1;
	const int EndRange = 2;
	const int HorizontalShipDirection = 1;
	const int VerticalShipDirection = 2;

	int shipDirection = rand() % (EndRange - BeginRange + 1) + BeginRange;

	int horizontalStartPoint;
	int verticalStartPoint;

	if (shipDirection == HorizontalShipDirection)
	{
		RandomStartPointsForHorizontalShip(playField, rows, columns, shipSize, horizontalStartPoint, verticalStartPoint, ShipSymbol);
		SetHorizontalShip(playField, shipSize, horizontalStartPoint, verticalStartPoint, ShipSymbol);
	}

	else if (shipDirection == VerticalShipDirection)
	{
		RandomStartPointsForVerticalShip(playField, rows, columns, shipSize, horizontalStartPoint, verticalStartPoint, ShipSymbol);
		SetVerticalShip(playField, shipSize, horizontalStartPoint, verticalStartPoint, ShipSymbol);
	}
}