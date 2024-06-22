#pragma once

enum class SecondHitDirection
{
	Left = 1,
	Up = 2,
	Right = 3,
	Down = 4
};

//УСТАНОВКА СЛУЧАЙНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
inline void SetRandomCoordinatesForShoot(char field[Rows][Columns], ShootResult& shoot)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	do
	{
		shoot.x = rand() % (EndRange - BeginRange + 1) + BeginRange;
		shoot.y = rand() % (EndRange - BeginRange + 1) + BeginRange;

	} while (field[shoot.y][shoot.x] == Hit || field[shoot.y][shoot.x] == Miss || field[shoot.y][shoot.x] == Killed);
}

//ПОПЫТКА ПОПАСТЬ ПОСЛЕ ПЕРВОГО ПОПАДАНИЯ
inline void TrySecondHit(char field[Rows][Columns], ShootResult& shoot)
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
			if (field[shoot.y][shoot.x - 1] != Miss)
			{
				shoot.x--;
				return;
			}
			break;
		}
		case SecondHitDirection::Up:
		{
			if (field[shoot.y - 1][shoot.x] != Miss)
			{
				shoot.y--;
				return;
			}
			break;
		}
		case SecondHitDirection::Right:
		{
			if (field[shoot.y][shoot.x + 1] != Miss)
			{
				shoot.x++;
				return;
			}
			break;
		}
		case SecondHitDirection::Down:
		{
			if (field[shoot.y + 1][shoot.x] != Miss)
			{
				shoot.y++;
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
inline void HitHorizontalShip(char field[Rows][Columns], ShootResult& shoot)
{
	if ((field[shoot.y][shoot.x - 1] == Empty || field[shoot.y][shoot.x - 1] == Ship) && (field[shoot.y][shoot.x + 1] == Hit || field[shoot.y][shoot.x + 1] == Ship))
		shoot.x--;

	else if (field[shoot.y][shoot.x - 1] == Hit)
	{
		while (field[shoot.y][shoot.x] == Hit)
			shoot.x--;

		if (field[shoot.y][shoot.x] == Empty || field[shoot.y][shoot.x] == Ship)
			return;
		else
		{
			shoot.x++;
			while (field[shoot.y][shoot.x] == Hit)
				shoot.x++;
		}
	}

	else if (field[shoot.y][shoot.x - 1] == Miss && (field[shoot.y][shoot.x + 1] == Hit || field[shoot.y][shoot.x + 1] == Ship))
		while (field[shoot.y][shoot.x] == Hit)
			shoot.x++;
}

//ПОПАДАНИЕ В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
inline void HitVerticalShip(char field[Rows][Columns], ShootResult& shoot)
{
	if ((field[shoot.y - 1][shoot.x] == Empty || field[shoot.y - 1][shoot.x] == Ship) && (field[shoot.y + 1][shoot.x] == Hit || field[shoot.y + 1][shoot.x] == Ship))
		shoot.y--;

	else if (field[shoot.y - 1][shoot.x] == Hit)
	{
		while (field[shoot.y][shoot.x] == Hit)
			shoot.y--;
		if (field[shoot.y][shoot.x] == Empty || field[shoot.y][shoot.x] == Ship)
			return;
		else
		{
			shoot.y++;
			while (field[shoot.y][shoot.x] == Hit)
				shoot.y++;
		}
	}

	else if (field[shoot.y - 1][shoot.x] == Miss && (field[shoot.y + 1][shoot.x] == Hit || field[shoot.y + 1][shoot.x] == Ship))
		while (field[shoot.y][shoot.x] == Hit)
			shoot.y++;
}

//УСТАНОВКА УМНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
inline void SetSmartCoordinatesForShoot(char field[Rows][Columns], ShootResult& shoot)
{
	if (IsNoMoreHitsAround(field, shoot))
		TrySecondHit(field, shoot);

	else if (field[shoot.y][shoot.x - 1] == Hit || field[shoot.y][shoot.x - 1] == Ship || field[shoot.y][shoot.x + 1] == Hit || field[shoot.y][shoot.x + 1] == Ship)
		HitHorizontalShip(field, shoot);

	else if (field[shoot.y - 1][shoot.x] == Hit || field[shoot.y - 1][shoot.x] == Ship || field[shoot.y + 1][shoot.x] == Hit || field[shoot.y + 1][shoot.x] == Ship)
		HitVerticalShip(field, shoot);
}

//СТРЕЛЬБА КОМПЬЮТЕРА
inline ShootResult ComputerShooting(char field[Rows][Columns], ShootResult& shoot)
{
	if(!shoot.isKilled)
		SetSmartCoordinatesForShoot(field, shoot);
	else
		SetRandomCoordinatesForShoot(field, shoot);

	PrintShootCoordinates(shoot);

	if (field[shoot.y][shoot.x] == Ship)
	{
		field[shoot.y][shoot.x] = Hit;

		if (!(IsShipDefinitelyNotKilled(field, shoot)))
		{
			if (IsShipKilled(field, shoot))
			{
				cout << "Результат: корабль уничтожен!" << endl << endl;
				shoot.isKilled = true;
			}
			else
			{
				cout << "Результат: попадание!" << endl << endl;
				shoot.isKilled = false;
			}
		}
		else
		{
			cout << "Результат: попадание!" << endl << endl;
			shoot.isKilled = false;
		}

		shoot.isHit = true;
	}

	else if (field[shoot.y][shoot.x] == Empty)
	{
		field[shoot.y][shoot.x] = Miss;
		cout << "Результат: промах." << endl << endl;

		if (!shoot.isKilled)
		{
			if (field[shoot.y][shoot.x + 1] == Hit)
				shoot.x++;
			else if (field[shoot.y + 1][shoot.x] == Hit)
				shoot.y++;
			else if (field[shoot.y - 1][shoot.x] == Hit)
				shoot.y--;
			else if (field[shoot.y][shoot.x - 1] == Hit)
				shoot.x--;
		}

		shoot.isHit = false;
	}

	return shoot;
}