#pragma once

#include <iostream>
#include "TryKillShip.h"
#include "MenusAndActions.h"
#include <Windows.h>
using namespace std;


enum class SecondHitDirection
{
	Left = 1,
	Up = 2,
	Right = 3,
	Down = 4
};

//ПРОВЕРКА, ЕСТЬ ЛИ В КЛЕТКЕ КОРАБЛЬ ИЛИ НИЧЕГО НЕТ
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
	const int beginCoordinateRange = 1;
	const int endCoordinateRange = 10;

	do
	{
		shot.coordinates.abscissa = rand() % (endCoordinateRange - beginCoordinateRange + 1) + beginCoordinateRange;
		shot.coordinates.ordinate = rand() % (endCoordinateRange - beginCoordinateRange + 1) + beginCoordinateRange;

	} while (!IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate, shot.coordinates.abscissa));
}

//ПОПЫТКА ПОПАСТЬ ПОСЛЕ ПЕРВОГО ПОПАДАНИЯ
void TrySecondHit(char field[Rows][Columns], Cell& shot)
{
	const int beginRangeOfDirectionOptions = 1;
	const int endRangeOfDirectionOptions = 4;

	SecondHitDirection secondHitDirection;

	do
	{
		secondHitDirection = (SecondHitDirection)(rand() % 
			(endRangeOfDirectionOptions - beginRangeOfDirectionOptions + 1) + beginRangeOfDirectionOptions);

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
		}

	} while (true);
}

//ПОПАДАНИЕ В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
void HitHorizontalShip(char field[Rows][Columns], Cell& shot)
{
	if (IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate, shot.coordinates.abscissa - 1) &&
		IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa + 1))
	{
		shot.coordinates.abscissa--;
	}
	else if (field[shot.coordinates.ordinate][shot.coordinates.abscissa - 1] == Hit)
	{
		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.abscissa--;

		if (IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate, shot.coordinates.abscissa))
			return;

		shot.coordinates.abscissa++;

		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.abscissa++;
	}
	else if (field[shot.coordinates.ordinate][shot.coordinates.abscissa - 1] == Miss &&
		IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa + 1))
	{
		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.abscissa++;
	}
}

//ПОПАДАНИЕ В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
void HitVerticalShip(char field[Rows][Columns], Cell& shot)
{
	if (IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate - 1, shot.coordinates.abscissa) &&
		IsCellWhitShipOrHit(field, shot.coordinates.ordinate + 1, shot.coordinates.abscissa))
	{
		shot.coordinates.ordinate--;
	}
	else if (field[shot.coordinates.ordinate - 1][shot.coordinates.abscissa] == Hit)
	{
		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.ordinate--;

		if (IsCellWhitShipOrEmpty(field, shot.coordinates.ordinate, shot.coordinates.abscissa))
			return;

		shot.coordinates.ordinate++;
		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.ordinate++;
	}
	else if (field[shot.coordinates.ordinate - 1][shot.coordinates.abscissa] == Miss &&
		IsCellWhitShipOrHit(field, shot.coordinates.ordinate + 1, shot.coordinates.abscissa))
	{
		while (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit)
			shot.coordinates.ordinate++;
	}
}

//ПРОВЕРКА, ЧТО ПОПАДАНИЕ СОВЕРШЕНО В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
bool IsHorizontalShip(char field[Rows][Columns], const Cell& shot)
{
	return IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa - 1) ||
		IsCellWhitShipOrHit(field, shot.coordinates.ordinate, shot.coordinates.abscissa + 1);
}

//ПРОВЕРКА, ЧТО ПОПАДАНИЕ СОВЕРШЕНО В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
bool IsVerticalShip(char field[Rows][Columns], const Cell& shot)
{
	return IsCellWhitShipOrHit(field, shot.coordinates.ordinate - 1, shot.coordinates.abscissa) ||
		IsCellWhitShipOrHit(field, shot.coordinates.ordinate + 1, shot.coordinates.abscissa);
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
	const int signalDuration = 50;

	field[shot.coordinates.ordinate][shot.coordinates.abscissa] = Hit;

	if (!IsShipDefinitelyNotKilled(field, shot))
	{
		if (IsShipKilled(field, shot))
		{
			shot.result.isKilled = true;
			shot.result.ShipsLeftAfterLastShot--;
			Beep(200, signalDuration * 2);
		}
		else
		{
			shot.result.isKilled = false;
			Beep(350, signalDuration);
		}
	}
	else
	{
		shot.result.isKilled = false;
		Beep(350, signalDuration);
	}

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
	if (!shot.result.isKilled && !shot.result.isHit && 
		field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss)
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

//ПРОВЕРКА НА ВОЗМОЖНОСТЬ ВЫСТРЕЛА
inline bool IsShootByCellNotPossible(char field[Rows][Columns], const Cell& shot)
{
	return field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Hit || 
		field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss || 
		field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Killed;
}

//СТРЕЛЬБА ИГРОКА
void PlayerShooting(char field[Rows][Columns], Cell& shot)
{
	if (!shot.result.isKilled && !shot.result.isHit && 
		field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Miss)
		IfLastShotMiss(field, shot);

	bool isNotShot;

	do
	{
		PrintOnlyOneField(field, 0);

		InputCoordinates(field, shot, 0);

		isNotShot = IsShootByCellNotPossible(field, shot);

		if (isNotShot)
		{
			cout << "Выстрел по введенным координатам невозможен! Попробуйте ещё раз!" << endl << endl;
			system("pause");
		}

		system("cls");

	} while (isNotShot);

	if (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Ship)
		IfShotHit(field, shot);
	else if (field[shot.coordinates.ordinate][shot.coordinates.abscissa] == Empty)
	{
		field[shot.coordinates.ordinate][shot.coordinates.abscissa] = Miss;
		shot.result.isHit = false;
	}
}