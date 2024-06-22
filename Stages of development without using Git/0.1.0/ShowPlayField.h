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
	if (rowNumber == 9)
		cout << rowNumber + 1;
	else
		cout << " " << rowNumber + 1;

	for (int i = 0; i < Columns; i++)
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

	for (int i = 0; i < Rows; i++)
	{
		PrintFieldRow(field1, i);

		cout << "\t";

		PrintFieldRow(field2, i);

		cout << endl;
	}

	cout << endl;
}