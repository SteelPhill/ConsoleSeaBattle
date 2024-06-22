#pragma once

#include <fstream>
#include <string>
#include <iostream>
using namespace std;


//СОХРАНЕНИЕ ИГРЫ
void SaveGame(
	ModeMenuItems& gameMode,
	DifficultySelectionMenuItems& difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	Cell& firstPlayerLastShot,
	Cell& secondPlayerLastShot,
	string& firstPlayerName,
	string& secondPlayerName)
{
	ofstream saveFile;

	saveFile.open("Sea battle save.txt");

	if (!saveFile.is_open())
	{
		cout << "Не удалось сохранить игру!" << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	else
	{
		saveFile << (int)gameMode << endl;
		saveFile << (int)difficulty << endl;

		for (int i = 0; i < Rows; i++)
			for (int j = 0; j < Columns; j++)
				saveFile << firstPlayerField[i][j];

		saveFile << endl;
		
		for (int i = 0; i < Rows; i++)
			for (int j = 0; j < Columns; j++)
				saveFile << secondPlayerField[i][j];

		saveFile << endl;

		saveFile << firstPlayerLastShot.result.isHit << endl;
		saveFile << firstPlayerLastShot.result.isKilled << endl;
		saveFile << firstPlayerLastShot.result.howManyShipsLeft << endl;

		saveFile << secondPlayerLastShot.result.isHit << endl;
		saveFile << secondPlayerLastShot.result.isKilled << endl;
		saveFile << secondPlayerLastShot.result.howManyShipsLeft << endl;

		saveFile << firstPlayerName << endl;
		saveFile << secondPlayerName;

		cout << "Игра сохранена!" << endl << endl;
		system("pause");
		system("cls");
	}

	saveFile.close();
}

//ЗАГРУЗКА ИГРЫ
void LoadGame(
	ModeMenuItems& gameMode,
	DifficultySelectionMenuItems& difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	Cell& firstPlayerLastShot,
	Cell& secondPlayerLastShot,
	string& firstPlayerName,
	string& secondPlayerName)
{
	system("cls");

	ifstream loadFile;

	loadFile.open("Sea battle save.txt");

	if (!loadFile.is_open())
	{
		cout << "Не удалось загрузить игру!" << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	else
	{
		char tempCh;
		string tempStr;

		getline(loadFile, tempStr);
		gameMode = (ModeMenuItems)stoi(tempStr);
		
		getline(loadFile, tempStr);
		difficulty = (DifficultySelectionMenuItems)stoi(tempStr);

		for (int i = 0; i < Rows; i++)
			for (int j = 0; j < Columns; j++)
			{
				loadFile.get(tempCh);
				firstPlayerField[i][j] = tempCh;
			}

		getline(loadFile, tempStr);

		for (int i = 0; i < Rows; i++)
			for (int j = 0; j < Columns; j++)
			{
				loadFile.get(tempCh);
				secondPlayerField[i][j] = tempCh;
			}

		getline(loadFile, tempStr);

		getline(loadFile, tempStr);
		firstPlayerLastShot.result.isHit = stoi(tempStr);
		getline(loadFile, tempStr);
		firstPlayerLastShot.result.isKilled = stoi(tempStr);
		getline(loadFile, tempStr);
		firstPlayerLastShot.result.howManyShipsLeft = stoi(tempStr);

		getline(loadFile, tempStr);
		secondPlayerLastShot.result.isHit = stoi(tempStr);
		getline(loadFile, tempStr);
		secondPlayerLastShot.result.isKilled = stoi(tempStr);
		getline(loadFile, tempStr);
		secondPlayerLastShot.result.howManyShipsLeft = stoi(tempStr);

		getline(loadFile, firstPlayerName);
		getline(loadFile, secondPlayerName);

		cout << "Загруженно последнее сохранение!" << endl << endl;
		system("pause");
		system("cls");
	}

	loadFile.close();
}