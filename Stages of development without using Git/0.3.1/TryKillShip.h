#pragma once

//УНИЧТОЖЕНИЕ ОДНОПАЛУБНИКА
inline void OneDeckKilled(char field[Rows][Columns], const ShootResult& hit)
{
	field[hit.y][hit.x] = Killed;
	field[hit.y][hit.x - 1] = Miss;
	field[hit.y][hit.x + 1] = Miss;

	for (int i = hit.x - 1; i <= hit.x + 1; i++)
		field[hit.y - 1][i] = Miss;

	for (int i = hit.x - 1; i <= hit.x + 1; i++)
		field[hit.y + 1][i] = Miss;
}

//ВЕРНУТЬ ИНДЕКС КЛЕТКИ ПЕРЕД НАЧАЛОМ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
inline int GetIndexBeforeFrontHorizontalShip(char field[Rows][Columns], const ShootResult& hit)
{
	int index = hit.x - 1;

	while (field[hit.y][index] != Empty && field[hit.y][index] != Miss)
		index--;

	return index;
}

//УНИЧТОЖЕНИЕ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
inline void KillHorizontalShip(char field[Rows][Columns], const ShootResult& hit)
{
	int horizontalIndex = GetIndexBeforeFrontHorizontalShip(field, hit);

	for (int j = hit.y - 1; j <= hit.y + 1; j++)
		field[j][horizontalIndex] = Miss;

	horizontalIndex++;

	for (; field[hit.y][horizontalIndex] == Hit; horizontalIndex++)
	{
		field[hit.y][horizontalIndex] = Killed;
		field[hit.y - 1][horizontalIndex] = Miss;
		field[hit.y + 1][horizontalIndex] = Miss;
	}

	for (int j = hit.y - 1; j <= hit.y + 1; j++)
		field[j][horizontalIndex] = Miss;
}

//ВЕРНУТЬ ИНДЕКС КЛЕТКИ ПЕРЕД НАЧАЛОМ ВЕРТИКАЛЬНОГО КОРАБЛЯ
inline int GetIndexBeforeFrontVerticalShip(char field[Rows][Columns], const ShootResult& hit)
{
	int index = hit.y - 1;

	while (field[index][hit.x] != Empty && field[index][hit.x] != Miss)
		index--;

	return index;
}

//УНИЧТОЖЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
inline void KillVerticalShip(char field[Rows][Columns], const ShootResult& hit)
{
	int verticalIndex = GetIndexBeforeFrontVerticalShip(field, hit);

	for (int j = hit.x - 1; j <= hit.x + 1; j++)
		field[verticalIndex][j] = Miss;

	verticalIndex++;

	for (; field[verticalIndex][hit.x] == Hit; verticalIndex++)
	{
		field[verticalIndex][hit.x] = Killed;
		field[verticalIndex][hit.x - 1] = Miss;
		field[verticalIndex][hit.x + 1] = Miss;
	}

	for (int j = hit.x - 1; j <= hit.x + 1; j++)
		field[verticalIndex][j] = Miss;
}

//ПОПЫТКА УНИЧТОЖЕНИЯ КОРАБЛЯ
inline bool IsShipKilled(char field[Rows][Columns], const ShootResult& hit)
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