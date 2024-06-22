#pragma once

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


//СОХРАНЕНИЕ ИГРЫ
void SaveGame(
	const ModeMenuItems& gameMode,
	const DifficultyMenuItems& difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	const Cell& firstPlayerLastShot,
	const Cell& secondPlayerLastShot,
	const PlayerData& firstPlayerData,
	const PlayerData& secondPlayerData)
{
	ofstream saveFile;

	saveFile.open("Sea battle.save");

	if (!saveFile.is_open())
	{
		cout << "Не удалось сохранить игру!" << endl << endl;
		system("pause");
		system("cls");
		return;
	}

	saveFile << firstPlayerData.isMove << endl;
	saveFile << secondPlayerData.isMove << endl;

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

	saveFile << firstPlayerData.name << endl;
	saveFile << firstPlayerData.isPlayer << endl;
	saveFile << firstPlayerData.isFirstAI << endl;
	saveFile << firstPlayerData.isEasyAI << endl;
	saveFile << firstPlayerLastShot.result.isHit << endl;
	saveFile << firstPlayerLastShot.result.isKilled << endl;
	saveFile << firstPlayerLastShot.result.ShipsLeftAfterLastShot << endl;
	saveFile << firstPlayerLastShot.coordinates.abscissa << endl;
	saveFile << firstPlayerLastShot.coordinates.ordinate << endl;

	saveFile << secondPlayerData.name << endl;
	saveFile << secondPlayerData.isPlayer << endl;
	saveFile << secondPlayerData.isFirstAI << endl;
	saveFile << secondPlayerData.isEasyAI << endl;
	saveFile << secondPlayerLastShot.result.isHit << endl;
	saveFile << secondPlayerLastShot.result.isKilled << endl;
	saveFile << secondPlayerLastShot.result.ShipsLeftAfterLastShot << endl;
	saveFile << secondPlayerLastShot.coordinates.abscissa << endl;
	saveFile << secondPlayerLastShot.coordinates.ordinate;

	cout << "Игра сохранена!" << endl << endl;
	system("pause");
	system("cls");

	saveFile.close();
}

//ПОПЫТКА ЗАГРУЗКИ ИГРЫ
bool TryLoadGame(
	ModeMenuItems& gameMode,
	DifficultyMenuItems& difficulty,
	char firstPlayerField[Rows][Columns],
	char secondPlayerField[Rows][Columns],
	Cell& firstPlayerLastShot,
	Cell& secondPlayerLastShot,
	PlayerData& firstPlayerData,
	PlayerData& secondPlayerData)
{
	system("cls");

	ifstream loadFile;

	loadFile.open("Sea battle.save");

	if (!loadFile.is_open())
	{
		cout << "Не удалось загрузить игру!" << endl << endl;
		system("pause");
		system("cls");
		return false;
	}

	char tempCh;
	string tempStr;

	getline(loadFile, tempStr);
	firstPlayerData.isMove = stoi(tempStr);

	getline(loadFile, tempStr);
	secondPlayerData.isMove = stoi(tempStr);

	getline(loadFile, tempStr);
	gameMode = (ModeMenuItems)stoi(tempStr);

	getline(loadFile, tempStr);
	difficulty = (DifficultyMenuItems)stoi(tempStr);

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

	getline(loadFile, firstPlayerData.name);
	getline(loadFile, tempStr);
	firstPlayerData.isPlayer = stoi(tempStr);
	getline(loadFile, tempStr);
	firstPlayerData.isFirstAI = stoi(tempStr);
	getline(loadFile, tempStr);
	firstPlayerData.isEasyAI = stoi(tempStr);
	getline(loadFile, tempStr);
	firstPlayerLastShot.result.isHit = stoi(tempStr);
	getline(loadFile, tempStr);
	firstPlayerLastShot.result.isKilled = stoi(tempStr);
	getline(loadFile, tempStr);
	firstPlayerLastShot.result.ShipsLeftAfterLastShot = stoi(tempStr);
	getline(loadFile, tempStr);
	firstPlayerLastShot.coordinates.abscissa = stoi(tempStr);
	getline(loadFile, tempStr);
	firstPlayerLastShot.coordinates.ordinate = stoi(tempStr);

	getline(loadFile, secondPlayerData.name);
	getline(loadFile, tempStr);
	secondPlayerData.isPlayer = stoi(tempStr);
	getline(loadFile, tempStr);
	secondPlayerData.isFirstAI = stoi(tempStr);
	getline(loadFile, tempStr);
	secondPlayerData.isEasyAI = stoi(tempStr);
	getline(loadFile, tempStr);
	secondPlayerLastShot.result.isHit = stoi(tempStr);
	getline(loadFile, tempStr);
	secondPlayerLastShot.result.isKilled = stoi(tempStr);
	getline(loadFile, tempStr);
	secondPlayerLastShot.result.ShipsLeftAfterLastShot = stoi(tempStr);
	getline(loadFile, tempStr);
	secondPlayerLastShot.coordinates.abscissa = stoi(tempStr);
	getline(loadFile, tempStr);
	secondPlayerLastShot.coordinates.ordinate = stoi(tempStr);

	cout << "Загруженно последнее сохранение!" << endl << endl;
	system("pause");
	system("cls");

	loadFile.close();

	return true;
}