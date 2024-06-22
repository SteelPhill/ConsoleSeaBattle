#pragma once

//ПРОВЕРКА, ЧТО КОРАБЛЬ ТОЧНО НЕ УНИЧТОЖЕН
inline bool IsShipDefinitelyNotKilled(char field[Rows][Columns], const CellCoordinates& hit)
{
	if (field[hit.y][hit.x - 1] == ShipPart)
		return true;
	else if (field[hit.y][hit.x + 1] == ShipPart)
		return true;
	else if (field[hit.y - 1][hit.x] == ShipPart)
		return true;
	else if (field[hit.y + 1][hit.x] == ShipPart)
		return true;

	return false;
}

//ПРОВЕРКА НА ПОПАДАНИЕ В ОДНОПАЛУБНИК
inline bool IsHitOneDeck(char field[Rows][Columns], const CellCoordinates& hit)
{
	if (field[hit.y][hit.x - 1] == Hit)
		return false;
	else if (field[hit.y][hit.x + 1] == Hit)
		return false;
	else if (field[hit.y - 1][hit.x] == Hit)
		return false;
	else if (field[hit.y + 1][hit.x] == Hit)
		return false;

	return true;
}

//ПРОВЕРКА НА ПОПАДАНИЕ В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
inline bool IsHitHorizontalShip(char field[Rows][Columns], const CellCoordinates& hit)
{
	return field[hit.y][hit.x - 1] == Hit || field[hit.y][hit.x + 1] == Hit;
}

//ПРОВЕРКА НА ПОПАДАНИЕ В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
inline bool IsHitVerticalShip(char field[Rows][Columns], const CellCoordinates& hit)
{
	return field[hit.y - 1][hit.x] == Hit || field[hit.y + 1][hit.x] == Hit;
}

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
inline bool IsHorizontalShipKilled(char field[Rows][Columns], const CellCoordinates& hit)
{
	for (int i = hit.x - 1; field[hit.y][i] != EmptyCell && field[hit.y][i] != Miss; i--)
		if (field[hit.y][i] == ShipPart)
			return false;

	for (int i = hit.x + 1; field[hit.y][i] != EmptyCell && field[hit.y][i] != Miss; i++)
		if (field[hit.y][i] == ShipPart)
			return false;

	return true;
}

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
inline bool IsVerticalShipKilled(char field[Rows][Columns], const CellCoordinates& hit)
{
	for (int i = hit.y - 1; field[i][hit.x] != EmptyCell && field[i][hit.x] != Miss; i--)
		if (field[i][hit.x] == ShipPart)
			return false;

	for (int i = hit.y + 1; field[i][hit.x] != EmptyCell && field[i][hit.x] != Miss; i++)
		if (field[i][hit.x] == ShipPart)
			return false;

	return true;
}

//УНИЧТОЖЕНИЕ ОДНОПАЛУБНИКА
inline void OneDeckKilled(char field[Rows][Columns], const CellCoordinates& hit)
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
inline int GetIndexBeforeFrontHorizontalShip(char field[Rows][Columns], const CellCoordinates& hit)
{
	int index = hit.x - 1;

	while (field[hit.y][index] != EmptyCell && field[hit.y][index] != Miss)
		index--;

	return index;
}

//УНИЧТОЖЕНИЕ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
inline void KillHorizontalShip(char field[Rows][Columns], const CellCoordinates& hit)
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
inline int GetIndexBeforeFrontVerticalShip(char field[Rows][Columns], const CellCoordinates& hit)
{
	int index = hit.y - 1;

	while (field[index][hit.x] != EmptyCell && field[index][hit.x] != Miss)
		index--;

	return index;
}

//УНИЧТОЖЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
inline void KillVerticalShip(char field[Rows][Columns], const CellCoordinates& hit)
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
inline bool IsShipKilled(char field[Rows][Columns], const CellCoordinates& hit)
{
	if (IsHitOneDeck(field, hit)) //ПОПАДАНИЕ В ОДНОПАЛУБНИК
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

//ВЫБОР КОРРЕКТНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
inline CellCoordinates SetCorrectCoordinatesForShoot(char field[Rows][Columns])
{
	const int BeginRange = 1;
	const int EndRange = 10;

	CellCoordinates shoot;

	do
	{
		shoot.x = rand() % (EndRange - BeginRange + 1) + BeginRange;
		shoot.y = rand() % (EndRange - BeginRange + 1) + BeginRange;

	} while (field[shoot.y][shoot.x] == Hit || field[shoot.y][shoot.x] == Miss || field[shoot.y][shoot.x] == Killed);

	return shoot;
}

//СТРЕЛЬБА ПРОСТОГО КОМПЬЮТЕРА
inline bool IsShootHit(char field[Rows][Columns])
{
	CellCoordinates shoot = SetCorrectCoordinatesForShoot(field);

	PrintShootCoordinates(shoot);

	if (field[shoot.y][shoot.x] == ShipPart)
	{
		field[shoot.y][shoot.x] = Hit;

		if (!(IsShipDefinitelyNotKilled(field, shoot)))
			if(IsShipKilled(field, shoot))
				cout << "Результат: корабль уничтожен!" << endl << endl;
			else
				cout << "Результат: попадание!" << endl << endl;
		else
			cout << "Результат: попадание!" << endl << endl;

		return true;
	}

	else if (field[shoot.y][shoot.x] == EmptyCell)
	{
		field[shoot.y][shoot.x] = Miss;
		cout << "Результат: промах." << endl << endl;

		return false;
	}
}