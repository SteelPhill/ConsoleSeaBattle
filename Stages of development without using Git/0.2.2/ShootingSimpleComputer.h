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

//УНИЧТОЖЕНИЕ КОРАБЛЯ
void ShipDestruction(char field[Rows][Columns], const CellCoordinates& hit)
{
	if (field[hit.y][hit.x - 1] == ShipPart)
		return;
	else if (field[hit.y][hit.x + 1] == ShipPart)
		return;
	else if (field[hit.y - 1][hit.x] == ShipPart)
		return;
	else if (field[hit.y + 1][hit.x] == ShipPart)
		return;

	if (field[hit.y][hit.x - 1] == Hit) //ПОПАДАНИЕ В ЦЕНТР ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
	{

		for (int i = hit.x - 1; field[hit.y][i] != EmptyCell && field[hit.y][i] != Miss; i--)
			if (field[hit.y][i] == ShipPart)
				return;

		int i = hit.x + 1;

		for (; field[hit.y][i] != EmptyCell && field[hit.y][i] != Miss; i++)
			if (field[hit.y][i] == ShipPart)
				return;

		for (int j = hit.y - 1; j <= hit.y + 1; j++)
			field[j][i] = Miss;

		i--;

		for (; field[hit.y][i] == Hit; i--)
		{
			field[hit.y][i] = Destroied;
			field[hit.y - 1][i] = Miss;
			field[hit.y + 1][i] = Miss;
		}

		for (int j = hit.y - 1; j <= hit.y + 1; j++)
			field[j][i] = Miss;
	}

	else if (field[hit.y - 1][hit.x] == Hit) //ПОПАДАНИЕ В ЦЕНТР ВЕРТИКАЛЬНОГО КОРАБЛЯ
	{

		for (int i = hit.y - 1; field[i][hit.x] != EmptyCell && field[i][hit.x] != Miss; i--)
			if (field[i][hit.x] == ShipPart)
				return;

		int i = hit.y + 1;

		for (; field[i][hit.x] != EmptyCell && field[i][hit.x] != Miss; i++)
			if (field[i][hit.x] == ShipPart)
				return;

		for (int j = hit.x - 1; j <= hit.x + 1; j++)
			field[i][j] = Miss;

		i--;

		for (; field[i][hit.x] == Hit; i--)
		{
			field[i][hit.x] = Destroied;
			field[i][hit.x - 1] = Miss;
			field[i][hit.x + 1] = Miss;
		}

		for (int j = hit.x - 1; j <= hit.x + 1; j++)
			field[i][j] = Miss;
	}

	else if (field[hit.y][hit.x - 1] != Hit && field[hit.y][hit.x + 1] == Hit) //ПОПАДАНИЕ В НАЧАЛО ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
	{
		int i = hit.x;

		for (; field[hit.y][i] != EmptyCell && field[hit.y][i] != Miss; i++)
			if (field[hit.y][i] == ShipPart)
				return;

		for (int j = hit.y - 1; j <= hit.y + 1; j++)
			field[j][i] = Miss;

		i--;

		for (; field[hit.y][i] == Hit; i--)
		{
			field[hit.y][i] = Destroied;
			field[hit.y - 1][i] = Miss;
			field[hit.y + 1][i] = Miss;
		}

		for (int j = hit.y - 1; j <= hit.y + 1; j++)
			field[j][i] = Miss;
	}

	else if (field[hit.y - 1][hit.x] != Hit && field[hit.y + 1][hit.x] == Hit) //ПОПАДАНИЕ В НАЧАЛО ВЕРТИКАЛЬНОГО КОРАБЛЯ
	{
		int i = hit.y;

		for (; field[i][hit.x] != EmptyCell && field[i][hit.x] != Miss; i++)
			if (field[i][hit.x] == ShipPart)
				return;

		for (int j = hit.x - 1; j <= hit.x + 1; j++)
			field[i][j] = Miss;

		i--;

		for (; field[i][hit.x] == Hit; i--)
		{
			field[i][hit.x] = Destroied;
			field[i][hit.x - 1] = Miss;
			field[i][hit.x + 1] = Miss;
		}

		for (int j = hit.x - 1; j <= hit.x + 1; j++)
			field[i][j] = Miss;
	}

	else //ПОПАДАНИЕ В ОДНОПАЛУБНИК
	{
		field[hit.y][hit.x] = Destroied;
		field[hit.y][hit.x - 1] = Miss;
		field[hit.y][hit.x + 1] = Miss;

		for (int i = hit.x - 1; i <= hit.x + 1; i++)
			field[hit.y - 1][i] = Miss;

		for (int i = hit.x - 1; i <= hit.x + 1; i++)
			field[hit.y + 1][i] = Miss;
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
		ShipDestruction(field, shoot);
		return true;
	}

	else if (field[shoot.y][shoot.x] == EmptyCell)
	{
		field[shoot.y][shoot.x] = Miss;
		return false;
	}
}