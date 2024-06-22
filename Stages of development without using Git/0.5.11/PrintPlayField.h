#pragma once

#define NOMINMAX

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
	cout << "\t\t\t " << "Координаты выстрела: ";

	switch (shot.coordinates.abscissa)
	{
	case 1:
		cout << "А-";
		break;
	case 2:
		cout << "Б-";
		break;
	case 3:
		cout << "В-";
		break;
	case 4:
		cout << "Г-";
		break;
	case 5:
		cout << "Д-";
		break;
	case 6:
		cout << "Е-";
		break;
	case 7:
		cout << "Ж-";
		break;
	case 8:
		cout << "З-";
		break;
	case 9:
		cout << "И-";
		break;
	case 10:
		cout << "К-";
		break;
	}

	cout << shot.coordinates.ordinate << endl << endl;
}

//ПЕЧАТЬ РЕЗУЛЬТАТОВ СТРЕЛЬБЫ
void PrintShotResult(const Cell& afterShot)
{
	if(afterShot.result.isHit && !afterShot.result.isKilled)
		cout << "\t\t\t " << "Результат: попадание!" << endl << endl;
	else if(afterShot.result.isHit && afterShot.result.isKilled)
		cout << "\t\t\t " << "Результат: корабль уничтожен!" << endl << endl;
	else if(!afterShot.result.isHit)
		cout << "\t\t\t " << "Результат: промах" << endl << endl;
}

//ПЕЧАТЬ КОЛИЧЕСТВА ОСТАВШИХСЯ КОРАБЛЕЙ У ПРОТИВНИКА
inline void PrintHowManyShipsLeft(const Cell& afterShot)
{
	cout << "\t\t\t " << "Осталось уничтожить кораблей: " << afterShot.result.ShipsLeftAfterLastShot << endl << endl;
}

//ПЕЧАТЬ ИМЁН ИГРОКОВ	
inline void PrintPlayerNames(const string& firstPlayerName, const string& secondPlayerName, const string& shooterName)
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

	if(shooterName == firstPlayerName)
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
	for (unsigned char ch = (unsigned char)'А'; ch <= (unsigned char)'К'; ch++)
		if (ch != (unsigned char)'Й')
			cout << " " << ch << " ";
}

//ПЕЧАТЬ ОДНОЙ СТРОКИ ОДНОГО ПОЛЯ
void PrintRowFromOneField(char field[Rows][Columns], const int rowNumber, const bool isShowShips)
{
	if (rowNumber == 10)
		cout << rowNumber;
	else
		cout << " " << rowNumber;

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

//ПЕЧАТЬ ПОЛЯ
void PrintBattlefield(
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

	if (shooterName != noOneShot)
	{
		PrintWhoseShot(shooterName);
		PrintShotCoordinates(shot);
		PrintShotResult(shot);
		PrintHowManyShipsLeft(shot);
	}
}

//ПЕЧАТЬ ПОЛЯ ТОЛЬКО КОМПЬЮТЕРА ИЛИ ТОЛЬКО ИГРОКА
void PrintOnlyOneField(char field[Rows][Columns], const int shipSize)
{
	bool isShowShips;

	if (shipSize == NULL)
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