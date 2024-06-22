#pragma once

#include <iostream>
using namespace std;


//ПЕЧАТАТЬ ПОБЕДИТЕЛЯ
void PrintTheWinner(const string& playerName)
{
	cout << "\t\t" << "Игра окончена!" << endl << endl;
	cout << "Победа: " << playerName << endl << endl;
	system("pause");
	system("cls");
}

//ПЕЧАТАТЬ ЧЕЙ ХОД
inline void PrintWhoseMove(const string& playerName)
{
	cout << "\t\t\t    " << "Стреляет: " << playerName << endl << endl;
}

//ПЕЧАТАТЬ КООРДИНАТЫ ВЫСТРЕЛА
void PrintShootCoordinates(const Cell& shot)
{
	cout << "Координаты выстрела: ";

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
		cout << "Результат: попадание!" << endl << endl;
	else if(shot.result.isHit && shot.result.isKilled)
		cout << "Результат: корабль уничтожен!" << endl << endl;
	else if(!shot.result.isHit)
		cout << "Результат: промах" << endl << endl;
}

//ПЕЧАТАТЬ ИМЕНА ИГРОКОВ	
inline void PrintPlayerNames(const string& firstPlayerName, const string& secondPlayerName)
{
	cout << "\t    " << firstPlayerName << "\t\t\t\t    " << secondPlayerName << endl << endl;
}

//ПЕЧАТАТЬ КООРДИНАТНЫЕ БУКВЫ	
void PrintCoordinateLetters()
{
	cout << "  ";
	for (unsigned char ch = (unsigned char)'А'; ch <= (unsigned char)'К'; ch++)
		if (ch != (unsigned char)'Й')
			cout << " " << ch << " ";
}

//ПЕЧАТАТЬ, СКОЛЬКО КОРАБЛЕЙ ОСТАЛОСЬ
inline void PrintHowManyShipsLeft(const Cell& shot)
{
	cout << "Осталось уничтожить кораблей: " << shot.result.howManyShipsLeft << endl << endl;
}

//ПЕЧАТАТЬ СТРОКУ ОДНОГО ПОЛЯ С КОРАБЛЯМИ 
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

//ПЕЧАТАТЬ СТРОКУ ОДНОГО ПОЛЯ БЕЗ КОРАБЛЕЙ 
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

//ПЕЧАТАТЬ ПОЛЕ ДЛЯ "КОМПЬЮТЕР ПРОТИВ КОМПЬЮТЕРА"
void PrintAiVsAiBattlefield(char firstAiField[Rows][Columns], char secondAiField[Rows][Columns], const string& firstAiName, const string& secondAiName, const Cell& shot)
{
	cout << endl;

	PrintPlayerNames(firstAiName, secondAiName);

	PrintCoordinateLetters();
	cout << "\t";
	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintRowFromOneFieldWithShips(firstAiField, i);

		cout << "\t";

		PrintRowFromOneFieldWithShips(secondAiField, i);

		cout << endl;
	}

	cout << endl;
	PrintShootCoordinates(shot);
	PrintShotResult(shot);
	PrintHowManyShipsLeft(shot);

	system("pause");
	system("cls");
}

//ПЕЧАТАТЬ ПОЛЕ ДЛЯ "ИГРОК ПРОТИВ КОМПЬЮТЕРА"
void PrintPlayerVsAiBattlefield(char aiField[Rows][Columns], char playerField[Rows][Columns], const string& playerName, const string& aiName, const Cell& shot)
{
	cout << endl;

	PrintPlayerNames(playerName, aiName);

	PrintCoordinateLetters();
	cout << "\t";
	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintRowFromOneFieldWithoutShips(aiField, i);

		cout << "\t";

		PrintRowFromOneFieldWithShips(playerField, i);

		cout << endl;
	}

	cout << endl;
	PrintShootCoordinates(shot);
	PrintShotResult(shot);
	PrintHowManyShipsLeft(shot);

	system("pause");
	system("cls");
}

//ПЕЧАТАТЬ ПОЛЕ КОМПЬЮТЕРА ВО ВРЕМЯ СТРЕЛЬБЫ
void PrintFieldForShot(char field[Rows][Columns])
{
	cout << "\t" << "Поле противника" << endl << endl;

	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintRowFromOneFieldWithoutShips(field, i);

		cout << endl;
	}

	cout << endl;
}

//ПЕЧАТАТЬ ПОЛЕ ИГРОКА ВО ВРЕМЯ РАССТАНОВКИ
void PrintFieldForPlacement(char field[Rows][Columns])
{
	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintRowFromOneFieldWithShips(field, i);

		cout << endl;
	}

	cout << endl;
}