#pragma once

//ПРОВЕРКА НА ПОБЕДУ
bool isGameOver(char field[Rows][Columns])
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			if (field[i][j] == ShipPart)
				return false;

	return true;
}

//ПРОВЕРКА, ЧТО КОРАБЛЬ ТОЧНО НЕ УНИЧТОЖЕН
bool IsShipDefinitelyNotDestroyed(char field[Rows][Columns], const CellCoordinates& hit)
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

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ ОДНОПАЛУБНИКА
bool IsDestroyedOneDeckShip(char field[Rows][Columns], const CellCoordinates& hit)
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

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
int IsHorizontalShipDestroyed(char field[Rows][Columns], const CellCoordinates& hit)
{
	if (field[hit.y][hit.x - 1] == Hit || field[hit.y][hit.x + 1] == Hit)
	{
		for (int i = hit.x - 1; field[hit.y][i] != EmptyCell && field[hit.y][i] != Miss; i--)
			if (field[hit.y][i] == ShipPart)
				return -1;

		int i = hit.x + 1;

		for (; field[hit.y][i] != EmptyCell && field[hit.y][i] != Miss; i++)
			if (field[hit.y][i] == ShipPart)
				return -1;

		return i;
	}
}

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
int IsVerticalShipDestroyed(char field[Rows][Columns], const CellCoordinates& hit)
{
	if (field[hit.y - 1][hit.x] == Hit || field[hit.y + 1][hit.x] == Hit)
	{
		for (int i = hit.y; field[i][hit.x] != EmptyCell && field[i][hit.x] != Miss; i--)
			if (field[i][hit.x] == ShipPart)
				return -1;

		int i = hit.y;

		for (; field[i][hit.x] != EmptyCell && field[i][hit.x] != Miss; i++)
			if (field[i][hit.x] == ShipPart)
				return -1;

		return i;
	}
}

//УНИЧТОЖЕНИЕ КОРАБЛЯ
void ShipDestruction(char field[Rows][Columns], const CellCoordinates& hit)
{
	if (IsDestroyedOneDeckShip(field, hit)) //ПОПАДАНИЕ В ОДНОПАЛУБНИК
	{
		field[hit.y][hit.x] = Destroied;
		field[hit.y][hit.x - 1] = Miss;
		field[hit.y][hit.x + 1] = Miss;

		for (int i = hit.x - 1; i <= hit.x + 1; i++)
			field[hit.y - 1][i] = Miss;

		for (int i = hit.x - 1; i <= hit.x + 1; i++)
			field[hit.y + 1][i] = Miss;

		return;
	}

	int indexShipPart = IsHorizontalShipDestroyed(field, hit);

	if (indexShipPart != -1) //ПОПАДАНИЕ В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
	{
		for (int j = hit.y - 1; j <= hit.y + 1; j++)
			field[j][indexShipPart] = Miss;

		indexShipPart--;

		for (; field[hit.y][indexShipPart] == Hit; indexShipPart--)
		{
			field[hit.y][indexShipPart] = Destroied;
			field[hit.y - 1][indexShipPart] = Miss;
			field[hit.y + 1][indexShipPart] = Miss;
		}

		for (int j = hit.y - 1; j <= hit.y + 1; j++)
			field[j][indexShipPart] = Miss;

		return;
	}

	indexShipPart = IsVerticalShipDestroyed(field, hit);

	if (indexShipPart != -1) //ПОПАДАНИЕ В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
	{
		for (int j = hit.x - 1; j <= hit.x + 1; j++)
			field[indexShipPart][j] = Miss;

		indexShipPart--;

		for (; field[indexShipPart][hit.x] == Hit; indexShipPart--)
		{
			field[indexShipPart][hit.x] = Destroied;
			field[indexShipPart][hit.x - 1] = Miss;
			field[indexShipPart][hit.x + 1] = Miss;
		}

		for (int j = hit.x - 1; j <= hit.x + 1; j++)
			field[indexShipPart][j] = Miss;
	}
}

//СТРЕЛЬБА ЛЕГКОГО КОМПЬЮТЕРА
bool IsShootHit(char field[Rows][Columns])
{
	const int BeginRange = 1;
	const int EndRange = 10;

	CellCoordinates shoot;

	do
	{
		shoot.x = rand() % (EndRange - BeginRange + 1) + BeginRange;
		shoot.y = rand() % (EndRange - BeginRange + 1) + BeginRange;

	} while (field[shoot.y][shoot.x] == Hit || field[shoot.y][shoot.x] == Miss || field[shoot.y][shoot.x] == Destroied);

	cout << "Координаты:" << endl;

	cout << "Буквы: " << shoot.x << endl;
	cout << "Цифры: " << shoot.y << endl;

	if (field[shoot.y][shoot.x] == ShipPart)
	{
		field[shoot.y][shoot.x] = Hit;

		if (!(IsShipDefinitelyNotDestroyed(field, shoot)))
			ShipDestruction(field, shoot);

		return true;
	}

	else if (field[shoot.y][shoot.x] == EmptyCell)
	{
		field[shoot.y][shoot.x] = Miss;
		return false;
	}
}