#pragma once

#include <iostream>
#include "TryKillShip.h"
#include "MenusAndActions.h"
using namespace std;


enum class SecondHitDirection
{
	Left = 1,
	Up = 2,
	Right = 3,
	Down = 4
};

//ПРОВЕРКА, ЕСТЬ ЛИ В КЛЕТКЕ КОРАБЛЬ ИЛИ НИЧЕГО
inline bool IsCellWhitShipOrEmpty(char field[Rows][Columns], const int ordinate, const int abscissa)
{
	return field[ordinate][abscissa] == Ship || field[ordinate][abscissa] == Empty;
}

//ПРОВЕРКА, ЕСТЬ ЛИ В КЛЕТКЕ КОРАБЛЬ ИЛИ ПОПАДАНИЕ
inline bool IsCellWhitShipOrHit(char field[Rows][Columns], const int ordinate, const int abscissa)
{
	return field[ordinate][abscissa] == Ship || field[ordinate][abscissa] == Hit;
}

//УСТАНОВКА СЛУЧАЙНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
void SetRandomCoordinatesForShot(char field[Rows][Columns], Cell& shot)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	do
	{
		shot.coordinates.abscissa = rand() % (EndRange - BeginRange + 1) + BeginRange;
		shot.coordinates.ordinate = rand() % (EndRange - BeginRange + 1) + BeginRange;

	} while (!IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate, shot.coordinates.abscissa));
}

//ПОПЫТКА ПОПАСТЬ ПОСЛЕ ПЕРВОГО ПОПАДАНИЯ
void TrySecondHit(char field[Rows][Columns], Cell& shot)
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

//ПОПАДАНИЕ В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
void HitHorizontalShip(char field[Rows][Columns], Cell& shot)
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
void HitVerticalShip(char field[Rows][Columns], Cell& shot)
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

//ПРОВЕРКА, ЧТО ПОПАДАНИЕ СОВЕРШЕНО В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
bool IsHorizontalShip(char field[Rows][Columns], const Cell& shot)
{
	return IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa - 1) || IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa + 1);
}

//ПРОВЕРКА, ЧТО ПОПАДАНИЕ СОВЕРШЕНО В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
bool IsVerticalShip(char field[Rows][Columns], const Cell& shot)
{
	return IsCellWhitShipOrHit(field, shot.coordinates.ordinate - 1, shot.coordinates.abscissa) || IsCellWhitShipOrHit(field, shot.coordinates.ordinate + 1, shot.coordinates.abscissa);
}

//УСТАНОВКА УМНЫХ КООРДИНАТ ДЛЯ ВЫСТРЕЛА
void SetSmartCoordinatesForShot(char field[Rows][Columns], Cell& shot)
{
	if (IsNoMoreHitsAround(field, shot))
		TrySecondHit(field, shot);

	else if (IsHorizontalShip(field, shot))
		HitHorizontalShip(field, shot);

	else if (IsVerticalShip(field, shot))
		HitVerticalShip(field, shot);
}

//ЕСЛИ СОВЕРШЕНО ПОПАДАНИЕ
void IfShotHit(char field[Rows][Columns], Cell& shot)
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

//ЕСЛИ ПОСЛЕДНИЙ ВЫСТРЕЛ - ЭТО ПРОМАХ
void IfLastShotMiss(char field[Rows][Columns], Cell& shot)
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
void AIShooting(char field[Rows][Columns], Cell& shot)
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
}

//СТРЕЛЬБА ИГРОКА
void PlayerShooting(char field[Rows][Columns], Cell& shot)
{
	if (!shot.result.isKilled && !shot.result.isHit && field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss)
		IfLastShotMiss(field, shot);

	do
	{
		PrintOnlyOneField(field, NULL);

		InputCoordinates(field, shot, NULL);

		if (IsPossibleShootByCell(field, shot))
		{
			cout << "Выстрел по введенным координатам невозможен! Попробуйте ещё раз!" << endl << endl;
			system("pause");
			system("cls");
		}
	} while (IsPossibleShootByCell(field, shot));

	if (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Ship)
		IfShotHit(field, shot);
	else if (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Empty)
	{
		field[shot.coordinates.ordinate][shot.coordinates.abscissa] = Miss;
		shot.result.isHit = false;
	}
}