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

//ПОПАДАНИЕ В УГОЛ 
bool IsHitNotInCorner(char field[Rows][Columns], const CellCoordinates& hit)
{
	if (hit.x == 0 && hit.y == 0)
	{
		if (field[hit.y][hit.x + 1] != ShipPart && field[hit.y + 1][hit.x] != ShipPart)
		{
			field[hit.y][hit.x + 1] = Miss;
			field[hit.y + 1][hit.x] = Miss;
			field[hit.y + 1][hit.x + 1] = Miss;
			return false;
		}
	}

	else if (hit.x == Columns - 1 && hit.y == 0)
	{
		if (field[hit.y][hit.x - 1] != ShipPart && field[hit.y + 1][hit.x] != ShipPart)
		{
			field[hit.y][hit.x - 1] = Miss;
			field[hit.y + 1][hit.x] = Miss;
			field[hit.y + 1][hit.x - 1] = Miss;
			return false;
		}
	}

	else if (hit.x == 0 && hit.y == Rows - 1)
	{
		if (field[hit.y - 1][hit.x] != ShipPart && field[hit.y][hit.x + 1] != ShipPart)
		{
			field[hit.y - 1][hit.x] = Miss;
			field[hit.y][hit.x + 1] = Miss;
			field[hit.y - 1][hit.x + 1] = Miss;
			return false;
		}
	}

	else if (hit.x == Columns - 1 && hit.y == Rows - 1)
	{
		if (field[hit.y][hit.x - 1] != ShipPart && field[hit.y - 1][hit.x] != ShipPart)
		{
			field[hit.y][hit.x - 1] = Miss;
			field[hit.y - 1][hit.x] = Miss;
			field[hit.y - 1][hit.x - 1] = Miss;
			return false;
		}
	}

	return true;
}

//ПОПАДАНИЕ В КРАЙ
bool IsHitNotOnEdge(char field[Rows][Columns], const CellCoordinates& hit)
{
	if (hit.x == 0 && hit.y != 0 && hit.y != Rows - 1)
	{
		if (field[hit.y + 1][hit.x] != ShipPart && field[hit.y - 1][hit.x] != ShipPart && field[hit.y][hit.x + 1] != ShipPart)
		{
			field[hit.y + 1][hit.x] = Miss;
			field[hit.y - 1][hit.x] = Miss;
			field[hit.y][hit.x + 1] = Miss;
			field[hit.y + 1][hit.x + 1] = Miss;
			field[hit.y - 1][hit.x + 1] = Miss;
			return false;
		}
	}

	else if (hit.x == Columns - 1 && hit.y != 0 && hit.y != Rows - 1)
	{
		if (field[hit.y + 1][hit.x] != ShipPart && field[hit.y - 1][hit.x] != ShipPart && field[hit.y][hit.x - 1] != ShipPart)
		{
			field[hit.y + 1][hit.x] = Miss;
			field[hit.y - 1][hit.x] = Miss;
			field[hit.y][hit.x - 1] = Miss;
			field[hit.y + 1][hit.x - 1] = Miss;
			field[hit.y - 1][hit.x - 1] = Miss;
			return false;
		}
	}

	else if (hit.x != 0 && hit.x != Columns - 1 && hit.y == 0)
	{
		if (field[hit.y + 1][hit.x] != ShipPart && field[hit.y][hit.x + 1] != ShipPart && field[hit.y][hit.x - 1] != ShipPart)
		{
			field[hit.y + 1][hit.x] = Miss;
			field[hit.y][hit.x + 1] = Miss;
			field[hit.y][hit.x - 1] = Miss;
			field[hit.y + 1][hit.x + 1] = Miss;
			field[hit.y + 1][hit.x - 1] = Miss;
			return false;
		}
	}

	else if (hit.x != 0 && hit.x != Columns - 1 && hit.y == Rows - 1)
	{
		if (field[hit.y - 1][hit.x] != ShipPart && field[hit.y][hit.x + 1] != ShipPart && field[hit.y][hit.x - 1] != ShipPart)
		{
			field[hit.y - 1][hit.x] = Miss;
			field[hit.y][hit.x + 1] = Miss;
			field[hit.y][hit.x - 1] = Miss;
			field[hit.y - 1][hit.x + 1] = Miss;
			field[hit.y - 1][hit.x - 1] = Miss;
			return false;
		}
	}

	return true;
}

//ПОПАДАНИЕ В ЦЕНТР
void HitInCenter(char field[Rows][Columns], CellCoordinates& hit)
{
	if (field[hit.y - 1][hit.x] != ShipPart && field[hit.y + 1][hit.x] != ShipPart && field[hit.y][hit.x - 1] != ShipPart && field[hit.y][hit.x + 1] != ShipPart)
	{
		field[hit.y - 1][hit.x] = Miss;
		field[hit.y - 1][hit.x + 1] = Miss;
		field[hit.y - 1][hit.x - 1] = Miss;
		field[hit.y + 1][hit.x] = Miss;
		field[hit.y + 1][hit.x + 1] = Miss;
		field[hit.y + 1][hit.x - 1] = Miss;
		field[hit.y][hit.x + 1] = Miss;
		field[hit.y][hit.x - 1] = Miss;
	}
}

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ
void Destroy(char field[Rows][Columns], CellCoordinates &hit)
{
	if (IsHitNotInCorner(field, hit) && IsHitNotOnEdge(field, hit))
		HitInCenter(field, hit);
}

//СТРЕЛЬБА ЛЕГКОГО КОМПЬЮТЕРА
bool IsShootHit(char field[Rows][Columns])
{
	const int BeginRange = 0;
	const int EndRange = 9;

	CellCoordinates shootingAi;

	do
	{
		shootingAi.x = rand() % (EndRange - BeginRange + 1) + BeginRange;
		shootingAi.y = rand() % (EndRange - BeginRange + 1) + BeginRange;

	} while (field[shootingAi.y][shootingAi.x] == Hit || field[shootingAi.y][shootingAi.x] == Miss);


	if (field[shootingAi.y][shootingAi.x] == ShipPart)
	{
		field[shootingAi.y][shootingAi.x] = Hit;
		Destroy(field, shootingAi);
		return true;
	}

	else if (field[shootingAi.y][shootingAi.x] == EmptyCell)
	{
		field[shootingAi.y][shootingAi.x] = Miss;
		return false;
	}
}