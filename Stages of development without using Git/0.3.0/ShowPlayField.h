#pragma once


//ПЕЧАТАТЬ КООРДИНАТЫ ВЫСТРЕЛА
void PrintShootCoordinates(const ShootResult& shoot)
{
	cout << "Координаты выстрела: ";

	switch (shoot.x)
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

	cout << shoot.y << endl << endl;
}

//ПЕЧАТАТЬ НОМЕРА РАУНДА И ЧЕЙ ХОД
void PrintRoundNumberAndWhoseMove(const int round, const string& playerName)
{
	cout << "\t\t\t\t" << "Раунд " << round << endl << endl;
	cout << "\t\t\t" << "Стреляет: " << playerName << endl << endl;
}

//ПЕЧАТАТЬ ИМЕНА ИГРОКОВ	
void PrintPlayerNames(const string& firstPlayer, const string& secondPlayer)
{
	cout << "\t    " << firstPlayer << "\t\t\t\t    " << secondPlayer << endl << endl;
}

//ПЕЧАТАТЬ БУКВЫ	
void PrintCoordinateLetters()
{
	cout << "  ";
	for (unsigned char ch = 192; ch <= 202; ch++)
		if (ch != 201)
			cout << " " << ch << " ";
}

//ПЕЧАТАТЬ ОДНУ СТРОКУ ПОЛЯ
void PrintSingleRowFromField(char field[Rows][Columns], const int rowNumber)
{
	if (rowNumber == 10)
		cout << rowNumber;
	else
		cout << " " << rowNumber;

	for (int i = 1; i < Columns - 1; i++)
	{
		cout << "[";

	/*	if (field[rowNumber][i] == ShipPart)
			cout << EmptyCell;
		else*/
			cout << field[rowNumber][i];

		cout << "]";
	}
}

//ПЕЧАТАТЬ ПОЛЕ
void PrintBothBattlefields(char field1[Rows][Columns], char field2[Rows][Columns], const string& firstPlayerName, const string& secondPlayerName)
{
	cout << endl;

	PrintPlayerNames(firstPlayerName, secondPlayerName);

	PrintCoordinateLetters();
	cout << "\t";
	PrintCoordinateLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintSingleRowFromField(field1, i);

		cout << "\t";

		PrintSingleRowFromField(field2, i);

		cout << endl;
	}

	cout << endl;

	system("pause");
	system("cls");
}