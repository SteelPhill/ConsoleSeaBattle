#pragma once

using namespace std;


//УНИЧТОЖЕНИЕ ОДНОПАЛУБНИКА
void OneDeckKilled(char field[Rows][Columns], const Cell& hit)
{
	field[hit.coordinates.ordinate][hit.coordinates.abscissa] = Killed;
	field[hit.coordinates.ordinate][hit.coordinates.abscissa - 1] = Miss;
	field[hit.coordinates.ordinate][hit.coordinates.abscissa + 1] = Miss;

	for (int i = hit.coordinates.abscissa - 1; i <= hit.coordinates.abscissa + 1; i++)
		field[hit.coordinates.ordinate - 1][i] = Miss;

	for (int i = hit.coordinates.abscissa - 1; i <= hit.coordinates.abscissa + 1; i++)
		field[hit.coordinates.ordinate + 1][i] = Miss;
}

//ВЕРНУТЬ ИНДЕКС КЛЕТКИ ПЕРЕД НАЧАЛОМ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
int GetIndexBeforeFrontHorizontalShip(char field[Rows][Columns], const Cell& hit)
{
	int index = hit.coordinates.abscissa - 1;

	while (field[hit.coordinates.ordinate][index] != Empty && field[hit.coordinates.ordinate][index] != Miss)
		index--;

	return index;
}

//ВЕРНУТЬ ИНДЕКС КЛЕТКИ ПЕРЕД НАЧАЛОМ ВЕРТИКАЛЬНОГО КОРАБЛЯ
int GetIndexBeforeFrontVerticalShip(char field[Rows][Columns], const Cell& hit)
{
	int index = hit.coordinates.ordinate - 1;

	while (field[index][hit.coordinates.abscissa] != Empty && field[index][hit.coordinates.abscissa] != Miss)
		index--;

	return index;
}

//УНИЧТОЖЕНИЕ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
void KillHorizontalShip(char field[Rows][Columns], const Cell& hit)
{
	int horizontalIndex = GetIndexBeforeFrontHorizontalShip(field, hit);

	for (int j = hit.coordinates.ordinate - 1; j <= hit.coordinates.ordinate + 1; j++)
		field[j][horizontalIndex] = Miss;

	horizontalIndex++;

	for (; field[hit.coordinates.ordinate][horizontalIndex] == Hit; horizontalIndex++)
	{
		field[hit.coordinates.ordinate][horizontalIndex] = Killed;
		field[hit.coordinates.ordinate - 1][horizontalIndex] = Miss;
		field[hit.coordinates.ordinate + 1][horizontalIndex] = Miss;
	}

	for (int j = hit.coordinates.ordinate - 1; j <= hit.coordinates.ordinate + 1; j++)
		field[j][horizontalIndex] = Miss;
}

//УНИЧТОЖЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
void KillVerticalShip(char field[Rows][Columns], const Cell& hit)
{
	int verticalIndex = GetIndexBeforeFrontVerticalShip(field, hit);

	for (int j = hit.coordinates.abscissa - 1; j <= hit.coordinates.abscissa + 1; j++)
		field[verticalIndex][j] = Miss;

	verticalIndex++;

	for (; field[verticalIndex][hit.coordinates.abscissa] == Hit; verticalIndex++)
	{
		field[verticalIndex][hit.coordinates.abscissa] = Killed;
		field[verticalIndex][hit.coordinates.abscissa - 1] = Miss;
		field[verticalIndex][hit.coordinates.abscissa + 1] = Miss;
	}

	for (int j = hit.coordinates.abscissa - 1; j <= hit.coordinates.abscissa + 1; j++)
		field[verticalIndex][j] = Miss;
}

//ПРОВЕРКА, ЧТО КОРАБЛЬ ТОЧНО НЕ УНИЧТОЖЕН
bool IsShipDefinitelyNotKilled(char field[Rows][Columns], const Cell& hit)
{
	if (field[hit.coordinates.ordinate][hit.coordinates.abscissa - 1] == Ship)
		return true;
	else if (field[hit.coordinates.ordinate][hit.coordinates.abscissa + 1] == Ship)
		return true;
	else if (field[hit.coordinates.ordinate - 1][hit.coordinates.abscissa] == Ship)
		return true;
	else if (field[hit.coordinates.ordinate + 1][hit.coordinates.abscissa] == Ship)
		return true;

	return false;
}

//ПРОВЕРКА ЕСТЬ ЛИ ЕЩЁ ПОПАДАНИЯ ВОКРУГ
bool IsNoMoreHitsAround(char field[Rows][Columns], const Cell& hit)
{
	if (field[hit.coordinates.ordinate][hit.coordinates.abscissa - 1] == Hit)
		return false;
	else if (field[hit.coordinates.ordinate][hit.coordinates.abscissa + 1] == Hit)
		return false;
	else if (field[hit.coordinates.ordinate - 1][hit.coordinates.abscissa] == Hit)
		return false;
	else if (field[hit.coordinates.ordinate + 1][hit.coordinates.abscissa] == Hit)
		return false;

	return true;
}

//ПРОВЕРКА НА ПОПАДАНИЕ В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
inline bool IsHitHorizontalShip(char field[Rows][Columns], const Cell& hit)
{
	return field[hit.coordinates.ordinate][hit.coordinates.abscissa - 1] == Hit || field[hit.coordinates.ordinate][hit.coordinates.abscissa + 1] == Hit;
}

//ПРОВЕРКА НА ПОПАДАНИЕ В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
inline bool IsHitVerticalShip(char field[Rows][Columns], const Cell& hit)
{
	return field[hit.coordinates.ordinate - 1][hit.coordinates.abscissa] == Hit || field[hit.coordinates.ordinate + 1][hit.coordinates.abscissa] == Hit;
}

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
bool IsHorizontalShipKilled(char field[Rows][Columns], const Cell& hit)
{
	for (int i = hit.coordinates.abscissa - 1; field[hit.coordinates.ordinate][i] != Empty && field[hit.coordinates.ordinate][i] != Miss; i--)
		if (field[hit.coordinates.ordinate][i] == Ship)
			return false;

	for (int i = hit.coordinates.abscissa + 1; field[hit.coordinates.ordinate][i] != Empty && field[hit.coordinates.ordinate][i] != Miss; i++)
		if (field[hit.coordinates.ordinate][i] == Ship)
			return false;

	return true;
}

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
bool IsVerticalShipKilled(char field[Rows][Columns], const Cell& hit)
{
	for (int i = hit.coordinates.ordinate - 1; field[i][hit.coordinates.abscissa] != Empty && field[i][hit.coordinates.abscissa] != Miss; i--)
		if (field[i][hit.coordinates.abscissa] == Ship)
			return false;

	for (int i = hit.coordinates.ordinate + 1; field[i][hit.coordinates.abscissa] != Empty && field[i][hit.coordinates.abscissa] != Miss; i++)
		if (field[i][hit.coordinates.abscissa] == Ship)
			return false;

	return true;
}

//ПОПЫТКА УНИЧТОЖЕНИЯ КОРАБЛЯ
bool IsShipKilled(char field[Rows][Columns], const Cell& hit)
{
	if (IsNoMoreHitsAround(field, hit)) //ПОПАДАНИЕ В ОДНОПАЛУБНИК
	{
		OneDeckKilled(field, hit);
		return true;
	}

	else if (IsHitHorizontalShip(field, hit)) //ПОПАДАНИЕ В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
	{
		if (IsHorizontalShipKilled(field, hit))
		{
			KillHorizontalShip(field, hit);
			return true;
		}
		else
			return false;
	}

	else if (IsHitVerticalShip(field, hit)) //ПОПАДАНИЕ В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
	{
		if (IsVerticalShipKilled(field, hit))
		{
			KillVerticalShip(field, hit);
			return true;
		}
		else
			return false;
	}
}