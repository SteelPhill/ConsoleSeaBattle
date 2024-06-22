#pragma once

enum class MainMenuItems
{
	PlayerVsComputer = 1,
	ComputerVsComputer = 2,
	Rules = 3,
	ExitProgram = 0
};

enum class DifficultySelectionMenuItems
{
	Easy = 1,
	Hard = 2,
	GoToMainMenu = 0
};

enum class ShipPlacementVariantsMenuItems
{
	AutoPlacement = 1,
	ManuallyPlacement = 2,
	GoToMainMenu = 0
};

MainMenuItems MainMenu()
{
	const int BeginRange = 0;
	const int EndRange = 3;

	MainMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Главное меню:" << endl << endl;
	cout << "1.Игрок против компьютера" << endl;
	cout << "2.Компьютер против компьютера" << endl;
	cout << "3.Правила игры" << endl;
	cout << "0.Выйти из игры" << endl << endl;

	cout << "Выберите номер пункта";
	choice = (MainMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;
	system("pause");
	system("cls");

	return choice;
}

DifficultySelectionMenuItems DifficultySelectionMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	DifficultySelectionMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Уровень сложности:" << endl << endl;
	cout << "1.Низкий" << endl;
	cout << "2.Высокий" << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта";
	choice = (DifficultySelectionMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;
	system("pause");
	system("cls");

	return choice;
}

ShipPlacementVariantsMenuItems ShipPlacementVariantsMenu()
{
	const int BeginRange = 0;
	const int EndRange = 2;

	ShipPlacementVariantsMenuItems choice;

	cout << "\t===\\\\\\МОРСКОЙ БОЙ///===" << endl << endl;
	cout << "Варианты размещения кораблей:" << endl << endl;
	cout << "1.Автоматическое размещение" << endl;
	cout << "2.Ручное размещение" << endl;
	cout << "0.Выйти в главное меню" << endl << endl;

	cout << "Выберите номер пункта";
	choice = (ShipPlacementVariantsMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;
	system("pause");
	system("cls");

	return choice;
}