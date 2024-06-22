#pragma once

enum class MainMenuItems
{
	PlayerVsComputer = 1,
	ComputerVsComputer = 2,
	Rules = 3
};

enum class DifficultySelectionMenuItems
{
	Easy = 1,
	Hard = 2
};

MainMenuItems MainMenu()
{
	const int BeginRange = 1;
	const int EndRange = 3;

	MainMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Главное меню:" << endl << endl;
	cout << "1.Игрок против компьютера" << endl;
	cout << "2.Компьютер против компьютера" << endl;
	cout << "3.Правила игры" << endl << endl;

	cout << "Выберите номер пункта";

	choice = (MainMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;
	system("pause");
	system("cls");

	return choice;
}

DifficultySelectionMenuItems DifficultySelectionMenu()
{
	const int BeginRange = 1;
	const int EndRange = 2;

	DifficultySelectionMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Сложность игры:" << endl << endl;
	cout << "1.Легко" << endl;
	cout << "2.Тяжело" << endl << endl;

	cout << "Выберите номер пункта";

	choice = (DifficultySelectionMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;
	system("pause");
	system("cls");

	return choice;
}