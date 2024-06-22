#pragma once

//ПРОВЕРКА НА ПОБЕДУ
inline bool isGameOver(char field[Rows][Columns])
{
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Columns; j++)
			if (field[i][j] == Ship)
				return false;

	return true;
}

//ПРОВЕРКА, ЧТО КОРАБЛЬ ТОЧНО НЕ УНИЧТОЖЕН
inline bool IsShipDefinitelyNotKilled(char field[Rows][Columns], const ShootResult& hit)
{
	if (field[hit.y][hit.x - 1] == Ship)
		return true;
	else if (field[hit.y][hit.x + 1] == Ship)
		return true;
	else if (field[hit.y - 1][hit.x] == Ship)
		return true;
	else if (field[hit.y + 1][hit.x] == Ship)
		return true;

	return false;
}

//ПРОВЕРКА НА ПОПАДАНИЕ В ОДНОПАЛУБНИК
inline bool IsHitOneDeck(char field[Rows][Columns], const ShootResult& hit)
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

//ПРОВЕРКА НА ПОПАДАНИЕ В ГОРИЗОНТАЛЬНЫЙ КОРАБЛЬ
inline bool IsHitHorizontalShip(char field[Rows][Columns], const ShootResult& hit)
{
	return field[hit.y][hit.x - 1] == Hit || field[hit.y][hit.x + 1] == Hit;
}

//ПРОВЕРКА НА ПОПАДАНИЕ В ВЕРТИКАЛЬНЫЙ КОРАБЛЬ
inline bool IsHitVerticalShip(char field[Rows][Columns], const ShootResult& hit)
{
	return field[hit.y - 1][hit.x] == Hit || field[hit.y + 1][hit.x] == Hit;
}

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
inline bool IsHorizontalShipKilled(char field[Rows][Columns], const ShootResult& hit)
{
	for (int i = hit.x - 1; field[hit.y][i] != Empty && field[hit.y][i] != Miss; i--)
		if (field[hit.y][i] == Ship)
			return false;

	for (int i = hit.x + 1; field[hit.y][i] != Empty && field[hit.y][i] != Miss; i++)
		if (field[hit.y][i] == Ship)
			return false;

	return true;
}

//ПРОВЕРКА НА УНИЧТОЖЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
inline bool IsVerticalShipKilled(char field[Rows][Columns], const ShootResult& hit)
{
	for (int i = hit.y - 1; field[i][hit.x] != Empty && field[i][hit.x] != Miss; i--)
		if (field[i][hit.x] == Ship)
			return false;

	for (int i = hit.y + 1; field[i][hit.x] != Empty && field[i][hit.x] != Miss; i++)
		if (field[i][hit.x] == Ship)
			return false;

	return true;
}