#pragma once

//ПЕЧАТАТЬ ПОБЕДИТЕЛЯ
inline void PrintTheWinner(const string& playerName)
{
	cout << "\t\t" << "Игра окончена!" << endl << endl;
	cout << "Победа: " << playerName << endl << endl;
}

//ПЕЧАТАТЬ ЧЕЙ ХОД
inline void PrintWhoseMove(const string& playerName)
{
	cout << "\t\t\t" << "Стреляет: " << playerName << endl << endl;
}

//ПЕЧАТАТЬ КООРДИНАТЫ ВЫСТРЕЛА
inline void PrintShootCoordinates(const ShotResult& shot)
{
	cout << "Координаты выстрела: ";

	switch (shot.x)
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

	cout << shot.y << endl << endl;
}

//ПЕЧАТАТЬ РЕЗУЛЬТАТОВ СТРЕЛЬБЫ
inline void PrintShotResult(const ShotResult& shot)
{
	if(shot.isHit && !shot.isKilled)
		cout << "Результат: попадание!" << endl << endl;
	else if(shot.isHit && shot.isKilled)
		cout << "Результат: корабль уничтожен!" << endl << endl;
	else if(!shot.isHit)
		cout << "Результат: промах" << endl << endl;
}

//ПЕЧАТАТЬ ИМЕНА ИГРОКОВ	
inline void PrintPlayerNames(const string& firstPlayerName, const string& secondPlayerName)
{
	cout << "\t    " << firstPlayerName << "\t\t\t\t    " << secondPlayerName << endl << endl;
}

//ПЕЧАТАТЬ БУКВЫ	
inline void PrintCoordinateLetters()
{
	cout << "  ";
	for (unsigned char ch = 192; ch <= 202; ch++)
		if (ch != 201)
			cout << " " << ch << " ";
}

//ПЕЧАТАТЬ ОДНУ СТРОКУ ПОЛЯ КОМПЬЮТЕРА
inline void PrintSingleRowFromComputerField(char field[Rows][Columns], const int rowNumber)
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
inline void PrintComputerVsComputerBattlefield(char field1[Rows][Columns], char field2[Rows][Columns], const string& firstPlayerName, const string& secondPlayerName, const ShotResult& shot)
{
	cout << endl;

	PrintPlayerNames(firstPlayerName, secondPlayerName);

	PrintCoordinateLetters();
	cout << "\t";
	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintSingleRowFromComputerField(field1, i);

		cout << "\t";

		PrintSingleRowFromComputerField(field2, i);

		cout << endl;
	}

	cout << endl;

	PrintShootCoordinates(shot);
	PrintShotResult(shot);

	system("pause");
	system("cls");
}

//ПЕЧАТАТЬ ОДНУ СТРОКУ ПОЛЯ ИГРОКА
inline void PrintSingleRowFromPlayerField(char field[Rows][Columns], const int rowNumber)
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

//ПЕЧАТАТЬ ПОЛЕ ДЛЯ "ИГРОК ПРОТИВ КОМПЬЮТЕРА"
inline void PrintPlayerVsComputerBattlefield(char field1[Rows][Columns], char field2[Rows][Columns], const string& firstPlayerName, const string& secondPlayerName, const ShotResult& shot)
{
	cout << endl;

	PrintPlayerNames(firstPlayerName, secondPlayerName);

	PrintCoordinateLetters();
	cout << "\t";
	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintSingleRowFromComputerField(field1, i);

		cout << "\t";

		PrintSingleRowFromPlayerField(field2, i);

		cout << endl;
	}

	cout << endl;

	PrintShootCoordinates(shot);
	PrintShotResult(shot);

	system("pause");
	system("cls");
}

//ПЕЧАТАТЬ ПОЛЕ КОМПЬЮТЕРА ВО ВРЕМЯ ВЫБОРА КООРДИНАТ
inline void PrintOnlyComputerField(char field[Rows][Columns])
{
	cout << endl;

	cout << "\t  Поле противника" << endl << endl;

	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintSingleRowFromComputerField(field, i);
		cout << endl;
	}

	cout << endl;
}