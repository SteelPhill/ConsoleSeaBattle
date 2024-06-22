#pragma once

//ПЕЧАТЬ НОМЕРА ХОДА
void PrintRound(const int round)
{
	cout << "\t\t\t\t" << "Раунд " << round << endl << endl;
}

//ПЕЧАТЬ ИМЁН ИГРОКОВ	
void PrintPlayers(const string& firstPlayer, const string& secondPlayer)
{
	cout << "\t    " << firstPlayer << "\t\t\t\t    " << secondPlayer << endl << endl;
}

//ПЕЧАТЬ БУКВ	
void PrintLetters()
{
	cout << "  ";
	for (unsigned char c = 224; c <= 234; c++)
		if (c != 233)
			cout << " " << c << " ";
}

//ПЕЧАТЬ СТРОКИ ПОЛЯ ИГРОКА
void PrintFieldRow(char field[Rows][Columns], const int rowNumber)
{
	if (rowNumber == 10)
		cout << rowNumber;
	else
		cout << " " << rowNumber;

	for (int i = 1; i < Columns - 1; i++)
	{
		cout << "[";

		if (field[rowNumber][i] == ShipPart)
			cout << EmptyCell;
		else
			cout << field[rowNumber][i];

		cout << "]";
	}
}

//ПЕЧАТЬ ПОЛЯ
void PrintOpenField(char field1[Rows][Columns], char field2[Rows][Columns], const string& firstPlayerName, const string& secondPlayerName, const int round)
{
	PrintRound(round);
	PrintPlayers(firstPlayerName, secondPlayerName);

	PrintLetters();
	cout << "\t";
	PrintLetters();
	cout << endl;

	for (int i = 1; i < Rows - 1; i++)
	{
		PrintFieldRow(field1, i);

		cout << "\t";

		PrintFieldRow(field2, i);

		cout << endl;
	}

	cout << endl;
}