#pragma once

//НАЧАЛЬНОЕ ЗАПОЛНЕНИЕ ПОЛЯ
inline void FieldInitialFill(char playField[Rows][Columns])
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
inline bool IsPossibleToPlaceHorizontalShip(char field[Rows][Columns], const int shipSize, const ShotResult& startCoordinate)
{
	for (int i = startCoordinate.x - 1; i <= startCoordinate.x + shipSize; i++)
	{
		if (field[startCoordinate.y - 1][i] == Ship)
			return true;
		if (field[startCoordinate.y][i] == Ship)
			return true;
		if (field[startCoordinate.y + 1][i] == Ship)
			return true;
	}

	return false;
}

//УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
inline void GetStartPointsForHorizontalShip(char field[Rows][Columns], const int shipSize, ShotResult& startCoordinate)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	bool isSetNotPossible = true;

	do
	{
		startCoordinate.y = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCoordinate.x = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCoordinate.x + shipSize >= Columns)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorizontalShip(field, shipSize, startCoordinate);

	} while (isSetNotPossible);
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
inline bool IsPossibleToPlaceVerticalShip(char field[Rows][Columns], const int shipSize, const ShotResult& startCoordinate)
{
	for (int i = startCoordinate.y - 1; i <= startCoordinate.y + shipSize; i++)
	{
		if (field[i][startCoordinate.x - 1] == Ship)
			return true;
		if (field[i][startCoordinate.x] == Ship)
			return true;
		if (field[i][startCoordinate.x + 1] == Ship)
			return true;
	}

	return false;
}

//УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
inline void GetStartPointsForVerticalShip(char field[Rows][Columns], const int shipSize, ShotResult& startCoordinate)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	bool isSetNotPossible = true;

	do
	{
		startCoordinate.y = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCoordinate.x = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCoordinate.y + shipSize >= Rows)
			continue;

		isSetNotPossible = IsPossibleToPlaceVerticalShip(field, shipSize, startCoordinate);

	} while (isSetNotPossible);
}

//РАЗМЕЩЕНИЕ ГОРИЗАНТАЛЬНОГО КОРАБЛЯ 
inline void PlacementHorizontalShip(char field[Rows][Columns], const int shipSize, const ShotResult& startCoordinate)
{
	for (int i = startCoordinate.x; i < startCoordinate.x + shipSize; i++)
		field[startCoordinate.y][i] = Ship;
}

//РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
inline void PlacementVerticalShip(char playField[Rows][Columns], const int shipSize, const ShotResult& startCoordinate)
{
	for (int i = startCoordinate.y; i < startCoordinate.y + shipSize; i++)
		playField[i][startCoordinate.x] = Ship;
}

//РАЗМЕЩЕНИЕ КОРАБЛЕЙ ЗАДАННЫМ РАЗМЕРОМ И КОЛИЧЕСТВОМ
inline void ShipsPlacement(char field[Rows][Columns], const int shipSize, const int shipsNumber)
{
	const int BeginRange = 1;
	const int EndRange = 2;
	const int HorizontalDirection = 1;
	const int VerticalDirection = 2;

	for (int i = 1; i <= shipsNumber; i++)
	{

		int shipDirection = rand() % (EndRange - BeginRange + 1) + BeginRange;

		ShotResult startCoordinate;

		if (shipDirection == HorizontalDirection)
		{
			GetStartPointsForHorizontalShip(field, shipSize, startCoordinate);
			PlacementHorizontalShip(field, shipSize, startCoordinate);
		}

		else if (shipDirection == VerticalDirection)
		{
			GetStartPointsForVerticalShip(field, shipSize, startCoordinate);
			PlacementVerticalShip(field, shipSize, startCoordinate);
		}
	}
}

//ЗАПОЛНЕНИЕ ПОЛЯ КОРАБЛЯМИ
inline void FillBattleField(char field[Rows][Columns])
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

	ShipsPlacement(field, FourDeckSize, FourDeckNumber);
	ShipsPlacement(field, ThreeDeckSize, ThreeDeckNumber);
	ShipsPlacement(field, TwoDeckSize, TwoDeckNumber);
	ShipsPlacement(field, OneDeckSize, OneDeckNumber);
}