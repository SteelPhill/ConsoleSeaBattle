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
void Desroied(char field[Rows][Columns], CellCoordinates& hit)
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
		int i = hit.x - 1;
		while (field[hit.y][i] == Hit)
			i--;
		i++;

		while (field[hit.y][i] != EmptyCell && field[hit.y][i] != Miss)
		{
			if (field[hit.y][i] == ShipPart)
				return;
			i++;
		}

		field[hit.y][i] = Miss;
		field[hit.y - 1][i] = Miss;
		field[hit.y + 1][i] = Miss;

		i--;
		while (field[hit.y][i] == Hit)
		{
			field[hit.y][i] = Destroied;
			field[hit.y - 1][i] = Miss;
			field[hit.y + 1][i] = Miss;
			i--;
		}

		field[hit.y][i] = Miss;
		field[hit.y - 1][i] = Miss;
		field[hit.y + 1][i] = Miss;
	}

	else if (field[hit.y - 1][hit.x] == Hit) //ПОПАДАНИЕ В ЦЕНТР ВЕРТИКАЛЬНОГО КОРАБЛЯ
	{
		int i = hit.y - 1;
		while (field[i][hit.x] == Hit)
			i--;
		i++;

		while (field[i][hit.x] != EmptyCell && field[i][hit.x] != Miss)
		{
			if (field[i][hit.x] == ShipPart)
				return;
			i++;
		}

		field[i][hit.x] = Miss;
		field[i][hit.x - 1] = Miss;
		field[i][hit.x + 1] = Miss;

		i--;
		while (field[i][hit.x] == Hit)
		{
			field[i][hit.x] = Destroied;
			field[i][hit.x - 1] = Miss;
			field[i][hit.x + 1] = Miss;
			i--;
		}

		field[i][hit.x] = Miss;
		field[i][hit.x - 1] = Miss;
		field[i][hit.x + 1] = Miss;
	}

	else if (field[hit.y][hit.x - 1] != Hit && field[hit.y][hit.x + 1] == Hit) //ПОПАДАНИЕ В НАЧАЛО ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
	{
		int i = hit.x;

		while (field[hit.y][i] != EmptyCell && field[hit.y][i] != Miss)
		{
			if (field[hit.y][i] == ShipPart)
				return;
			i++;
		}

		field[hit.y][i] = Miss;
		field[hit.y - 1][i] = Miss;
		field[hit.y + 1][i] = Miss;

		i--;
		while (field[hit.y][i] == Hit)
		{
			field[hit.y][i] = Destroied;
			field[hit.y - 1][i] = Miss;
			field[hit.y + 1][i] = Miss;
			i--;
		}

		field[hit.y][i] = Miss;
		field[hit.y - 1][i] = Miss;
		field[hit.y + 1][i] = Miss;
	}

	else if (field[hit.y - 1][hit.x] != Hit && field[hit.y + 1][hit.x] == Hit) //ПОПАДАНИЕ В НАЧАЛО ВЕРТИКАЛЬНОГО КОРАБЛЯ
	{
		int i = hit.y;

		while (field[i][hit.x] != EmptyCell && field[i][hit.x] != Miss)
		{
			if (field[i][hit.x] == ShipPart)
				return;
			i++;
		}

		field[i][hit.x] = Miss;
		field[i][hit.x - 1] = Miss;
		field[i][hit.x + 1] = Miss;

		i--;
		while (field[i][hit.x] == Hit)
		{
			field[i][hit.x] = Destroied;
			field[i][hit.x - 1] = Miss;
			field[i][hit.x + 1] = Miss;
			i--;
		}

		field[i][hit.x] = Miss;
		field[i][hit.x - 1] = Miss;
		field[i][hit.x + 1] = Miss;
	}
	else //ПОПАДАНИЕ В ОДНОПАЛУБНИК
	{
		field[hit.y][hit.x] = Destroied;
		field[hit.y][hit.x - 1] = Miss;
		field[hit.y][hit.x + 1] = Miss;

		field[hit.y - 1][hit.x - 1] = Miss;
		field[hit.y - 1][hit.x + 1] = Miss;

		field[hit.y - 1][hit.x] = Miss;
		field[hit.y + 1][hit.x] = Miss;

		field[hit.y + 1][hit.x - 1] = Miss;
		field[hit.y + 1][hit.x + 1] = Miss;
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
		Desroied(field, shoot);
		return true;
	}

	else if (field[shoot.y][shoot.x] == EmptyCell)
	{
		field[shoot.y][shoot.x] = Miss;
		return false;
	}
}