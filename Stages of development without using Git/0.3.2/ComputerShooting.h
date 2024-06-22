#pragma once

enum class SecondHitDirection
{
	Left = 1,
	Up = 2,
	Right = 3,
	Down = 4
};

//УСТАНОВКА СЛУЧАЙНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
inline void SetRandomCoordinatesForShot(char field[Rows][Columns], ShotResult& shot)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	do
	{
		shot.x = rand() % (EndRange - BeginRange + 1) + BeginRange;
		shot.y = rand() % (EndRange - BeginRange + 1) + BeginRange;

	} while (field[shot.y][shot.x] == Hit || field[shot.y][shot.x] == Miss || field[shot.y][shot.x] == Killed);
}

//ПОПЫТКА ПОПАСТЬ ПОСЛЕ ПЕРВОГО ПОПАДАНИЯ
inline void TrySecondHit(char field[Rows][Columns], ShotResult& shot)
{
	const int beginRange = 1;
	const int endRange = 4;

	SecondHitDirection secondHitDirection;

	do
	{
		secondHitDirection = (SecondHitDirection)(rand() % (endRange - beginRange + 1) + beginRange);

		switch (secondHitDirection)
		{
		case SecondHitDirection::Left:
		{
			if (field[shot.y][shot.x - 1] != Miss)
			{
				shot.x--;
				return;
			}
			break;
		}
		case SecondHitDirection::Up:
		{
			if (field[shot.y - 1][shot.x] != Miss)
			{
				shot.y--;
				return;
			}
			break;
		}
		case SecondHitDirection::Right:
		{
			if (field[shot.y][shot.x + 1] != Miss)
			{
				shot.x++;
				return;
			}
			break;
		}
		case SecondHitDirection::Down:
		{
			if (field[shot.y + 1][shot.x] != Miss)
			{
				shot.y++;
				return;
			}
			break;
		}
		default:
			break;
		}

	} while (true);
}

//ПОПАДАНИЕ В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
inline void HitHorizontalShip(char field[Rows][Columns], ShotResult& shot)
{
	if ((field[shot.y][shot.x - 1] == Empty || field[shot.y][shot.x - 1] == Ship) && (field[shot.y][shot.x + 1] == Hit || field[shot.y][shot.x + 1] == Ship))
		shot.x--;

	else if (field[shot.y][shot.x - 1] == Hit)
	{
		while (field[shot.y][shot.x] == Hit)
			shot.x--;

		if (field[shot.y][shot.x] == Empty || field[shot.y][shot.x] == Ship)
			return;
		else
		{
			shot.x++;
			while (field[shot.y][shot.x] == Hit)
				shot.x++;
		}
	}

	else if (field[shot.y][shot.x - 1] == Miss && (field[shot.y][shot.x + 1] == Hit || field[shot.y][shot.x + 1] == Ship))
		while (field[shot.y][shot.x] == Hit)
			shot.x++;
}

//ПОПАДАНИЕ В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
inline void HitVerticalShip(char field[Rows][Columns], ShotResult& shot)
{
	if ((field[shot.y - 1][shot.x] == Empty || field[shot.y - 1][shot.x] == Ship) && (field[shot.y + 1][shot.x] == Hit || field[shot.y + 1][shot.x] == Ship))
		shot.y--;

	else if (field[shot.y - 1][shot.x] == Hit)
	{
		while (field[shot.y][shot.x] == Hit)
			shot.y--;
		if (field[shot.y][shot.x] == Empty || field[shot.y][shot.x] == Ship)
			return;
		else
		{
			shot.y++;
			while (field[shot.y][shot.x] == Hit)
				shot.y++;
		}
	}

	else if (field[shot.y - 1][shot.x] == Miss && (field[shot.y + 1][shot.x] == Hit || field[shot.y + 1][shot.x] == Ship))
		while (field[shot.y][shot.x] == Hit)
			shot.y++;
}

//ПРОВЕРКА, ЧТО ЭТО ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
inline bool IsHorizontalShip(char field[Rows][Columns], const ShotResult& shot)
{
	return field[shot.y][shot.x - 1] == Hit || field[shot.y][shot.x - 1] == Ship || field[shot.y][shot.x + 1] == Hit || field[shot.y][shot.x + 1] == Ship;
}

//ПРОВЕРКА, ЧТО ЭТО ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
inline bool IsVerticalShip(char field[Rows][Columns], const ShotResult& shot)
{
	return field[shot.y - 1][shot.x] == Hit || field[shot.y - 1][shot.x] == Ship || field[shot.y + 1][shot.x] == Hit || field[shot.y + 1][shot.x] == Ship;
}

//УСТАНОВКА УМНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
inline void SetSmartCoordinatesForShot(char field[Rows][Columns], ShotResult& shot)
{
	if (IsNoMoreHitsAround(field, shot))
		TrySecondHit(field, shot);

	else if (IsHorizontalShip(field, shot))
		HitHorizontalShip(field, shot);

	else if (IsVerticalShip(field, shot))
		HitVerticalShip(field, shot);
}

//ПОПАДАНИЕ
inline void IfShotHit(char field[Rows][Columns], ShotResult& shot)
{
	field[shot.y][shot.x] = Hit;

	if (!(IsShipDefinitelyNotKilled(field, shot)))
		if (IsShipKilled(field, shot))
			shot.isKilled = true;
		else
			shot.isKilled = false;
	else
		shot.isKilled = false;

	shot.isHit = true;
}

//ПРОМАХ
inline void IfShotMiss(char field[Rows][Columns], ShotResult& shot)
{
	field[shot.y][shot.x] = Miss;

	if (!shot.isKilled)
	{
		if (field[shot.y][shot.x + 1] == Hit)
			shot.x++;
		else if (field[shot.y + 1][shot.x] == Hit)
			shot.y++;
		else if (field[shot.y - 1][shot.x] == Hit)
			shot.y--;
		else if (field[shot.y][shot.x - 1] == Hit)
			shot.x--;
	}

	shot.isHit = false;
}

//СТРЕЛЬБА КОМПЬЮТЕРА
inline ShotResult ComputerShooting(char field[Rows][Columns], ShotResult& shot)
{
	if(!shot.isKilled)
		SetSmartCoordinatesForShot(field, shot);

	else
		SetRandomCoordinatesForShot(field, shot);

	if (field[shot.y][shot.x] == Ship)
		IfShotHit(field, shot);

	else if (field[shot.y][shot.x] == Empty)
		IfShotMiss(field, shot);

	return shot;
}