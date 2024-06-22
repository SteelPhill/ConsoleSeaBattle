#pragma once

#include <iostream>
#include <Windows.h>
using namespace std;


//ВОСПРОИЗВЕДЕНИЕ ПОБЕДНОЙ МУЗЫКИ 
void PlayingVictoryMusic()
{
	const int signalDuration = 300;

	Beep(392, signalDuration);
	Beep(392, signalDuration);
	Beep(392, signalDuration);
	Beep(311, signalDuration * 0.75);
	Beep(466, signalDuration * 0.25);
	Beep(392, signalDuration);
	Beep(311, signalDuration * 0.75);
	Beep(466, signalDuration * 0.25);
	Beep(392, signalDuration * 2);
}

//ПЕЧАТЬ ИМЕНИ ПОБЕДИТЕЛЯ
void PrintTheWinner(const string& playerName)
{
	cout << "\t" << "Игра окончена!" << endl << endl;
	cout << "Победитель: " << playerName << endl << endl;

	PlayingVictoryMusic();

	system("pause");
	system("cls");
}

//ПЕЧАТЬ ИМЕНИ ИГРОКА, КОТОРЫЙ СЕЙЧАС СТРЕЛЯЕТ
inline void PrintWhoseShot(const string& playerName)
{
	cout << "\t\t\t " << "Стреляет: " << playerName << endl << endl;
}

//ПЕЧАТЬ КООРДИНАТОВ ВЫСТРЕЛА
void PrintShotCoordinates(const Cell& shot)
{
	const int symbolCodeLocatedBeforeSymbolA = 64;

	cout << "\t\t\t " << "Координаты выстрела: ";
	cout << (char)(symbolCodeLocatedBeforeSymbolA + shot.coordinates.abscissa) <<
		"-" << shot.coordinates.ordinate - 1 << endl << endl;
}

//ПЕЧАТЬ РЕЗУЛЬТАТОВ СТРЕЛЬБЫ
void PrintShotResult(const Cell& lastShot)
{
	if (lastShot.result.isHit && !lastShot.result.isKilled)
		cout << "\t\t\t " << "Результат: попадание!" << endl << endl;
	else if (lastShot.result.isHit && lastShot.result.isKilled)
		cout << "\t\t\t " << "Результат: корабль уничтожен!" << endl << endl;
	else if (!lastShot.result.isHit)
		cout << "\t\t\t " << "Результат: промах" << endl << endl;
}

//ПЕЧАТЬ КОЛИЧЕСТВА ОСТАВШИХСЯ КОРАБЛЕЙ ПРОТИВНИКА
inline void PrintHowManyShipsLeft(const Cell& lastShot)
{
	cout << "\t\t\t " << "Осталось уничтожить кораблей: " <<
		lastShot.result.ShipsLeftAfterLastShot << endl << endl;
}

//ПЕЧАТЬ УРОВЕНЬ СЛОЖНОСТИ КОМПЬЮТЕРА(-ОВ)
void PrintDifficulty(const DifficultyMenuItems& difficulty)
{
	switch (difficulty)
	{
	case DifficultyMenuItems::Easy:
		cout << "\t\t\t " << "Сложность: низкая" << endl << endl;
		break;
	case DifficultyMenuItems::Hard:
		cout << "\t\t\t " << "Сложность: высокая" << endl << endl;
		break;
	}
}

//ПЕЧАТЬ ИМЁН ИГРОКОВ	
void PrintPlayerNames(
	const string& firstPlayerName,
	const string& secondPlayerName,
	const string& shooterName)
{
	const int maxNameSize = 14;

	int spacesNumberBeforeName = (maxNameSize - firstPlayerName.size()) / 2;
	int spacesNumberAfterName = maxNameSize - firstPlayerName.size() - spacesNumberBeforeName;

	cout << "\t  ";

	for (int i = 1; i <= spacesNumberBeforeName; i++)
		cout << " ";

	cout << firstPlayerName;

	for (int i = 1; i <= spacesNumberAfterName; i++)
		cout << " ";

	cout << "\t   ";

	if (shooterName == firstPlayerName)
		cout << "--->";
	else if (shooterName == secondPlayerName)
		cout << "<---";
	else
		cout << "    ";

	spacesNumberBeforeName = (maxNameSize - secondPlayerName.size()) / 2;

	cout << "\t\t  ";

	for (int i = 1; i <= spacesNumberBeforeName; i++)
		cout << " ";

	cout << secondPlayerName << endl << endl;
}

//ПЕЧАТЬ КООРДИНАТНЫХ БУКВ	
void PrintCoordinateLetters()
{
	cout << "  ";
	for (char ch = 'A'; ch <= 'J'; ch++)
		cout << " " << ch << " ";
}

//ПЕЧАТЬ ОДНОЙ СТРОКИ ОДНОГО ПОЛЯ
void PrintRowFromOneField(char field[Rows][Columns], const int rowNumber, const bool isShowShips)
{
	cout << " " << rowNumber - 1;

	for (int i = 1; i < Columns - 1; i++)
	{
		cout << "[";

		if (isShowShips)
			cout << field[rowNumber][i];
		else
		{
			if (field[rowNumber][i] == Ship)
				cout << Empty;
			else
				cout << field[rowNumber][i];
		}

		cout << "]";
	}
}

//ПЕЧАТЬ ПОЛЕЙ
void PrintBattlefield(
	const bool isStartGame,
	const DifficultyMenuItems& difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	const Cell& shot,
	const string& shooterName,
	const PlayerData& firstPlayerData,
	const PlayerData& secondPlayerData)
{
	const string noOneShot = "";
	const bool isShowSecondPlayerShips = true;

	if (shooterName != noOneShot)
		cout << endl << endl;

	PrintPlayerNames(firstPlayerData.name, secondPlayerData.name, shooterName);

	PrintCoordinateLetters();
	cout << "\t";
	PrintCoordinateLetters();
	cout << endl;

	bool isShowFirstPlayerShips;

	if (!firstPlayerData.isPlayer && !secondPlayerData.isPlayer)
		isShowFirstPlayerShips = true;
	else
		isShowFirstPlayerShips = false;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintRowFromOneField(firstPlayerField, i, isShowFirstPlayerShips);

		cout << "\t";

		PrintRowFromOneField(secondPlayerField, i, isShowSecondPlayerShips);

		cout << endl;
	}

	cout << endl;

	PrintWhoseShot(shooterName);

	if (!isStartGame)
	{
		PrintShotCoordinates(shot);
		PrintShotResult(shot);
		PrintHowManyShipsLeft(shot);
	}

	PrintDifficulty(difficulty);
}

//ПЕЧАТЬ ПОЛЯ ТОЛЬКО КОМПЬЮТЕРА ИЛИ ТОЛЬКО ИГРОКА
void PrintOnlyOneField(char field[Rows][Columns], const int shipSize)
{
	bool isShowShips;

	if (shipSize == 0)
	{
		cout << "\t  " << "Фаза стрельбы" << endl << endl;
		cout << "\t    " << "Противник" << endl << endl;

		isShowShips = false;
	}
	else
	{
		cout << "     " << "Фаза размещения кораблей" << endl << endl;
		cout << "      " << "Размещение " << shipSize << "-палубника" << endl << endl;

		isShowShips = true;
	}

	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintRowFromOneField(field, i, isShowShips);
		cout << endl;
	}

	cout << endl;
}