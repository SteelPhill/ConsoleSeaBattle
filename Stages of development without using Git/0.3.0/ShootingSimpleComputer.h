#pragma once

//ВЫБОР КОРРЕКТНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
inline void SetCorrectCoordinatesForShoot(char field[Rows][Columns], ShootResult& shoot)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	do
	{
		shoot.x = rand() % (EndRange - BeginRange + 1) + BeginRange;
		shoot.y = rand() % (EndRange - BeginRange + 1) + BeginRange;

	} while (field[shoot.y][shoot.x] == Hit || field[shoot.y][shoot.x] == Miss || field[shoot.y][shoot.x] == Killed);
}

//СТРЕЛЬБА ПРОСТОГО КОМПЬЮТЕРА
inline bool IsShootEasyComputerHit(char field[Rows][Columns])
{
	ShootResult shoot;

	shoot.isKilled = true;

	SetCorrectCoordinatesForShoot(field, shoot);

	PrintShootCoordinates(shoot);

	if (field[shoot.y][shoot.x] == Ship)
	{
		field[shoot.y][shoot.x] = Hit;

		if (!(IsShipDefinitelyNotKilled(field, shoot)))
		{
			if (IsShipKilled(field, shoot))
				cout << "Результат: корабль уничтожен!" << endl << endl;
			else
				cout << "Результат: попадание!" << endl << endl;
		}
		else
			cout << "Результат: попадание!" << endl << endl;

		return true;
	}

	else if (field[shoot.y][shoot.x] == Empty)
	{
		field[shoot.y][shoot.x] = Miss;
		cout << "Результат: промах." << endl << endl;

		return false;
	}
}

//СТРАТЕГИЯ СЛОЖНОГО КОМПЬЮТЕРА
inline void Strategy(char field[Rows][Columns], ShootResult& shoot)
{
	if (field[shoot.y][shoot.x - 1] != Hit && field[shoot.y][shoot.x - 1] != Miss && field[shoot.y][shoot.x + 1] != Hit && field[shoot.y - 1][shoot.x] != Hit && field[shoot.y + 1][shoot.x] != Hit)
	{
		shoot.x--;
		return;
	}
	if (field[shoot.y][shoot.x + 1] != Hit && field[shoot.y][shoot.x + 1] != Miss && field[shoot.y][shoot.x - 1] != Hit && field[shoot.y - 1][shoot.x] != Hit && field[shoot.y + 1][shoot.x] != Hit)
	{
		shoot.x++;
		return;
	}
	if (field[shoot.y - 1][shoot.x] != Hit && field[shoot.y - 1][shoot.x] != Miss && field[shoot.y][shoot.x - 1] != Hit && field[shoot.y][shoot.x + 1] != Hit && field[shoot.y + 1][shoot.x] != Hit)
	{
		shoot.y--;
		return;
	}
	if (field[shoot.y + 1][shoot.x] != Hit && field[shoot.y + 1][shoot.x] != Miss && field[shoot.y][shoot.x - 1] != Hit && field[shoot.y][shoot.x + 1] != Hit && field[shoot.y - 1][shoot.x] != Hit)
	{
		shoot.y++;
		return;
	}
		



	if ((field[shoot.y][shoot.x - 1] == Empty || field[shoot.y][shoot.x - 1] == Ship) && (field[shoot.y][shoot.x + 1] == Hit || field[shoot.y][shoot.x + 1] == Ship))
	{
		shoot.x--;
		return;
	}
	if (field[shoot.y][shoot.x - 1] == Hit)
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
		return;
	}
	if (field[shoot.y][shoot.x - 1] == Miss && (field[shoot.y][shoot.x + 1] == Hit || field[shoot.y][shoot.x + 1] == Ship))
	{
		while (field[shoot.y][shoot.x] == Hit)
			shoot.x++;
		return;
	}




	if ((field[shoot.y - 1][shoot.x] == Empty || field[shoot.y - 1][shoot.x] == Ship) && (field[shoot.y + 1][shoot.x] == Hit || field[shoot.y + 1][shoot.x] == Ship))
	{
		shoot.y--;
		return;
	}
	if (field[shoot.y - 1][shoot.x] == Hit)
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
		return;
	}
	if (field[shoot.y - 1][shoot.x] == Miss && (field[shoot.y + 1][shoot.x] == Hit || field[shoot.y + 1][shoot.x] == Ship))
	{
		while (field[shoot.y][shoot.x] == Hit)
			shoot.y++;
		return;
	}

}

//СТРЕЛЬБА СЛОЖНОГО КОМПЬЮТЕРА
inline ShootResult IsShootHardComputerHit(char field[Rows][Columns], ShootResult& shoot)
{
	if(!shoot.isKilled)
	{
		cout << "Заданная точка" << endl << endl;
		Strategy(field, shoot);
	}
	else
	{
		cout << "Случайная точка" << endl << endl;
		SetCorrectCoordinatesForShoot(field, shoot);
	}

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