#pragma once

#include <iostream>
using namespace std;


//ПЕЧАТЬ ИМЕНИ ПОБЕДИТЕЛЯ
void PrintTheWinner(const string& playerName)
{
	cout << "\t\t" << "Игра окончена!" << endl << endl;
	cout << "Победитель: " << playerName << endl << endl;
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
	default:
		break;
	}

	cout << shot.coordinates.ordinate << endl << endl;
}

//ПЕЧАТЬ РЕЗУЛЬТАТОВ СТРЕЛЬБЫ
void PrintShotResult(const Cell& shot)
{
	if(shot.result.isHit && !shot.result.isKilled)
		cout << "\t\t\t " << "Результат: попадание!" << endl << endl;
	else if(shot.result.isHit && shot.result.isKilled)
		cout << "\t\t\t " << "Результат: корабль уничтожен!" << endl << endl;
	else if(!shot.result.isHit)
		cout << "\t\t\t " << "Результат: промах" << endl << endl;
}

//ПЕЧАТЬ КОЛИЧЕСТВА ОСТАВШИХСЯ КОРАБЛЕЙ У ПРОТИВНИКА
inline void PrintHowManyShipsLeft(const Cell& shot)
{
	cout << "\t\t\t " << "Осталось уничтожить кораблей: " << shot.result.howManyShipsLeft << endl << endl;
}

//ПЕЧАТЬ ИМЁН ИГРОКОВ	
inline void PrintPlayerNames(const string& firstPlayerName, const string& secondPlayerName, const string& shooterName)
{
	const int maxNameSize = 10;

	int spacesNumberBeforeName = (maxNameSize - firstPlayerName.size()) / 2;
	int spacesNumberAfterName = maxNameSize - firstPlayerName.size() - spacesNumberBeforeName;

	cout << "\t    ";

	for (int i = 1; i <= spacesNumberBeforeName; i++)
		cout << " ";

	cout << firstPlayerName;
	
	for (int i = 1; i <= spacesNumberAfterName; i++)
		cout << " ";

	cout << "\t\t   ";

	if(shooterName == firstPlayerName)
		cout << "--->";
	else if (shooterName == secondPlayerName)
		cout << "<---";
	else 
		cout << "    ";

	spacesNumberBeforeName = (maxNameSize - secondPlayerName.size()) / 2;

	cout << "\t\t    ";

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

//ПЕЧАТЬ ОДНОЙ СТРОКИ ОДНОГО ПОЛЯ (С КОРАБЛЯМИ) 
void PrintRowFromOneFieldWithShips(char field[Rows][Columns], const int rowNumber)
{
	if (rowNumber == 10)
		cout << rowNumber;
	else
		cout << " " << rowNumber;

	for (int i = 1; i < Columns - 1; i++)
	{
		cout << "[";

			cout << field[rowNumber][i];

		cout << "]";
	}
}

//ПЕЧАТЬ ОДНОЙ СТРОКИ ОДНОГО ПОЛЯ (БЕЗ КОРАБЛЕЙ) 
void PrintRowFromOneFieldWithoutShips(char field[Rows][Columns], const int rowNumber)
{
	if (rowNumber == 10)
		cout << rowNumber;
	else
		cout << " " << rowNumber;

	for (int i = 1; i < Columns - 1; i++)
	{
		cout << "[";

		if (field[rowNumber][i] == Ship)
			cout << Empty;

		else
			cout << field[rowNumber][i];

		cout << "]";
	}
}

//ПЕЧАТЬ ПОЛЯ ДЛЯ РЕЖИМА "КОМПЬЮТЕР ПРОТИВ КОМПЬЮТЕРА"
void PrintAIVsAIBattlefield(
	char firstAIField[Rows][Columns],
	char secondAIField[Rows][Columns],
	const string& firstAIName,
	const string& secondAIName,
	const Cell& shot,
	const string& shooterName)
{
	const string NoOneShot = "";

	if (shooterName != NoOneShot)
		cout << endl << endl;

	PrintPlayerNames(firstAIName, secondAIName, shooterName);

	PrintCoordinateLetters();
	cout << "\t";
	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintRowFromOneFieldWithShips(firstAIField, i);

		cout << "\t";

		PrintRowFromOneFieldWithShips(secondAIField, i);

		cout << endl;
	}
	cout << endl;

	if (shooterName != NoOneShot)
	{
		PrintWhoseShot(shooterName);
		PrintShotCoordinates(shot);
		PrintShotResult(shot);
		PrintHowManyShipsLeft(shot);
	}
}

//ПЕЧАТЬ ПОЛЯ ДЛЯ РЕЖИМА "ИГРОК ПРОТИВ КОМПЬЮТЕРА"
void PrintPlayerVsAIBattlefield(
	char AIField[Rows][Columns],
	char playerField[Rows][Columns],
	const string& playerName,
	const string& AIName,
	const Cell& shot,
	const string& shooterName)
{
	const string NoOneShot = "";

	if (shooterName != NoOneShot)
		cout << endl << endl;

	PrintPlayerNames(playerName, AIName, shooterName);

	PrintCoordinateLetters();
	cout << "\t";
	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintRowFromOneFieldWithoutShips(AIField, i);

		cout << "\t";

		PrintRowFromOneFieldWithShips(playerField, i);

		cout << endl;
	}
	cout << endl;

	if (shooterName != NoOneShot)
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
	if (shipSize == NULL)
	{
		cout << "\t " << "Фаза стрельбы" << endl << endl;
		cout << "\t  " << "Противник" << endl << endl;
	}
	else
	{
		cout << "     " << "Фаза размещения кораблей" << endl << endl;
		cout << "      " << "Размещение " << shipSize << "-палубника" << endl << endl;
	}

	PrintCoordinateLetters();
	cout << endl;

	if (shipSize == NULL)
	{
		for (int i = 1; i < Rows - 1; i++)
		{
			PrintRowFromOneFieldWithoutShips(field, i);

			cout << endl;
		}

		cout << endl;

	}
	else
	{
		for (int i = 1; i < Rows - 1; i++)
		{
			PrintRowFromOneFieldWithShips(field, i);

			cout << endl;
		}

		cout << endl;

	}
}