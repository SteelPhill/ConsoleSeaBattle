#pragma once

MainMenuItems MainMenu()
{
	const int BeginRange = 1;
	const int EndRange = 3;

	MainMenuItems choice;

	cout << "\t\\\\\\МОРСКОЙ БОЙ///" << endl << endl;
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

SecondMenuItems SecondMenu()
{
	const int BeginRange = 1;
	const int EndRange = 2;

	SecondMenuItems choice;

	cout << "\t\\\\\\МОРСКОЙ БОЙ///" << endl << endl;
	cout << "Сложность игры:" << endl;
	cout << "1.Легко" << endl;
	cout << "2.Тяжело" << endl << endl;

	cout << "Выберите номер пункта";

	choice = (SecondMenuItems)CinValueInRange(BeginRange, EndRange);

	cout << endl;
	system("pause");
	system("cls");

	return choice;
}