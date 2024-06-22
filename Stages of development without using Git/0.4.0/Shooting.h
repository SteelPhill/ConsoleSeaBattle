#pragma once

#include "TryKillShip.h"
#include "InputDataFromConsole.h"
using namespace std;


enum class SecondHitDirection
{
	Left = 1,
	Up = 2,
	Right = 3,
	Down = 4
};

//УСТАНОВКА СЛУЧАЙНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
inline void SetRandomCoordinatesForShot(char field[Rows][Columns], Cell& shot)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	do
	{
		shot.coordinates.abscissa = rand() % (EndRange - BeginRange + 1) + BeginRange;
		shot.coordinates.ordinate = rand() % (EndRange - BeginRange + 1) + BeginRange;

	} while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit || field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss || field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Killed);
}

//ПОПЫТКА ПОПАСТЬ ПОСЛЕ ПЕРВОГО ПОПАДАНИЯ
inline void TrySecondHit(char field[Rows][Columns], Cell& shot)
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
			if (field[shot.coordinates.ordinate][shot.coordinates.abscissa - 1] != Miss)
			{
				shot.coordinates.abscissa--;
				return;
			}
			break;
		}
		case SecondHitDirection::Up:
		{
			if (field[shot.coordinates.ordinate - 1][shot.coordinates.abscissa] != Miss)
			{
				shot.coordinates.ordinate--;
				return;
			}
			break;
		}
		case SecondHitDirection::Right:
		{
			if (field[shot.coordinates.ordinate][shot.coordinates.abscissa + 1] != Miss)
			{
				shot.coordinates.abscissa++;
				return;
			}
			break;
		}
		case SecondHitDirection::Down:
		{
			if (field[shot.coordinates.ordinate + 1][shot.coordinates.abscissa] != Miss)
			{
				shot.coordinates.ordinate++;
				return;
			}
			break;
		}
		default:
			break;
		}

	} while (true);
}

//ПРОВЕРКА, ЕСТЬ ЛИ В КЛЕТКЕ КОРАБЛЬ ИЛИ ПРОБЕЛ
inline bool IsCellWhitShipOrEmpty(char field[Rows][Columns], const int ordinate, const int abscissa)
{
	return field[ordinate][abscissa] == Ship || field[ordinate][abscissa] == Empty;
}

//ПРОВЕРКА, ЕСТЬ ЛИ В КЛЕТКЕ КОРАБЛЬ ИЛИ ПОПАДАНИЕ
inline bool IsCellWhitShipOrHit(char field[Rows][Columns], const int ordinate, const int abscissa)
{
	return field[ordinate][abscissa] == Ship || field[ordinate][abscissa] == Hit;
}

//ПОПАДАНИЕ В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
inline void HitHorizontalShip(char field[Rows][Columns], Cell& shot)
{
	if (IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate, shot.coordinates.abscissa - 1) && IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa + 1))
		shot.coordinates.abscissa--;

	else if (field[shot.coordinates.ordinate][shot.coordinates.abscissa - 1] == Hit)
	{
		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.abscissa--;

		if (IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate, shot.coordinates.abscissa))
			return;
		else
		{
			shot.coordinates.abscissa++;
			while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
				shot.coordinates.abscissa++;
		}
	}

	else if (field[shot.coordinates.ordinate][shot.coordinates.abscissa - 1] == Miss && IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa + 1))
		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.abscissa++;
}

//ПОПАДАНИЕ В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
inline void HitVerticalShip(char field[Rows][Columns], Cell& shot)
{
	if (IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate - 1, shot.coordinates.abscissa) && IsCellWhitShipOrHit(field, shot.coordinates.ordinate + 1, shot.coordinates.abscissa))
		shot.coordinates.ordinate--;

	else if (field[shot.coordinates.ordinate - 1][shot.coordinates.abscissa] == Hit)
	{
		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.ordinate--;

		if (IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate, shot.coordinates.abscissa))
			return;
		else
		{
			shot.coordinates.ordinate++;
			while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
				shot.coordinates.ordinate++;
		}
	}

	else if (field[shot.coordinates.ordinate - 1][shot.coordinates.abscissa] == Miss && IsCellWhitShipOrHit(field, shot.coordinates.ordinate + 1, shot.coordinates.abscissa))
		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.ordinate++;
}

//ПРОВЕРКА, ЧТО ЭТО ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
inline bool IsHorizontalShip(char field[Rows][Columns], const Cell& shot)
{
	return IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa - 1) || IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa + 1);
}

//ПРОВЕРКА, ЧТО ЭТО ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
inline bool IsVerticalShip(char field[Rows][Columns], const Cell& shot)
{
	return IsCellWhitShipOrHit(field, shot.coordinates.ordinate - 1, shot.coordinates.abscissa) || IsCellWhitShipOrHit(field, shot.coordinates.ordinate + 1, shot.coordinates.abscissa);
}

//УСТАНОВКА УМНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
inline void SetSmartCoordinatesForShot(char field[Rows][Columns], Cell& shot)
{
	if (IsNoMoreHitsAround(field, shot))
		TrySecondHit(field, shot);

	else if (IsHorizontalShip(field, shot))
		HitHorizontalShip(field, shot);

	else if (IsVerticalShip(field, shot))
		HitVerticalShip(field, shot);
}

//ЕСЛИ ПОПАДАНИЕ
inline void IfShotHit(char field[Rows][Columns], Cell& shot)
{
	field[shot.coordinates.ordinate][shot.coordinates.abscissa] = Hit;

	if (!(IsShipDefinitelyNotKilled(field, shot)))
		if (IsShipKilled(field, shot))
		{
			shot.result.isKilled = true;
			shot.result.howManyShipsLeft--;
		}
		else
			shot.result.isKilled = false;
	else
		shot.result.isKilled = false;

	shot.result.isHit = true;
}

//ЕСЛИ ПОСЛЕДНИЙ ВЫСТРЕЛ ЭТО ПРОМАХ
inline void IfLastShotMiss(char field[Rows][Columns], Cell& shot)
{
	if (field[shot.coordinates.ordinate][shot.coordinates.abscissa + 1] == Hit)
		shot.coordinates.abscissa++;
	else if (field[shot.coordinates.ordinate + 1][shot.coordinates.abscissa] == Hit)
		shot.coordinates.ordinate++;
	else if (field[shot.coordinates.ordinate - 1][shot.coordinates.abscissa] == Hit)
		shot.coordinates.ordinate--;
	else if (field[shot.coordinates.ordinate][shot.coordinates.abscissa - 1] == Hit)
		shot.coordinates.abscissa--;
}

//СТРЕЛЬБА КОМПЬЮТЕРА
inline Cell ComputerShooting(char field[Rows][Columns], Cell& shot)
{
	if (!shot.result.isKilled && !shot.result.isHit && field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss)
		IfLastShotMiss(field, shot);

	if(!shot.result.isKilled)
		SetSmartCoordinatesForShot(field, shot);
	else
		SetRandomCoordinatesForShot(field, shot);

	if (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Ship)
		IfShotHit(field, shot);
	else if (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Empty)
	{
		field[shot.coordinates.ordinate][shot.coordinates.abscissa] = Miss;
		shot.result.isHit = false;
	}

	return shot;
}

//СТРЕЛЬБА ИГРОКА
inline Cell PlayerShooting(char field[Rows][Columns], Cell& shot)
{
	if (!shot.result.isKilled && !shot.result.isHit && field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss)
		IfLastShotMiss(field, shot);

	InputCoordinates(field, shot, 0);
	system("pause");
	system("cls");

	if (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Ship)
		IfShotHit(field, shot);
	else if (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Empty)
	{
		field[shot.coordinates.ordinate][shot.coordinates.abscissa] = Miss;
		shot.result.isHit = false;
	}

	return shot;
}