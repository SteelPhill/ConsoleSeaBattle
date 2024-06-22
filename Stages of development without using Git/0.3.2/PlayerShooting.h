#pragma once

//ВВОД КООРДИНАТ ВЫСТРЕЛА
inline void InputCoordinatesForShot(char field[Rows][Columns], ShotResult& shot)
{
	const int beginRange = 1;
	const int endRange = 10;

	do
	{
		cout << "" << "Этап ввода координат для выстрела" << endl << endl;

		PrintOnlyComputerField(field);

		cout << "Введите координаты выстрела:" << endl << endl;
		cout << "Буква";
		unsigned char letter;
		do
		{
			letter = CinValue<unsigned char>();

			if (!(letter >= (unsigned char)'А' && letter <= (unsigned char)'К') && !(letter >= (unsigned char)'а' && letter <= (unsigned char)'к') || letter == (unsigned char)'Й' || letter == (unsigned char)'й')
				cout << "Ошибка ввода" << endl;

		} while (!(letter >= (unsigned char)'А' && letter <= (unsigned char)'К') && !(letter >= (unsigned char)'а' && letter <= (unsigned char)'к') || letter == (unsigned char)'Й' || letter == (unsigned char)'й');

		switch (letter)
		{
		case (unsigned char)'А':
		case (unsigned char)'а':
			shot.x = 1;
			break;

		case (unsigned char)'Б':
		case (unsigned char)'б':
			shot.x = 2;
			break;

		case (unsigned char)'В':
		case (unsigned char)'в':
			shot.x = 3;
			break;

		case (unsigned char)'Г':
		case (unsigned char)'г':
			shot.x = 4;
			break;

		case (unsigned char)'Д':
		case (unsigned char)'д':
			shot.x = 5;
			break;

		case (unsigned char)'Е':
		case (unsigned char)'е':
			shot.x = 6;
			break;

		case (unsigned char)'Ж':
		case (unsigned char)'ж':
			shot.x = 7;
			break;

		case (unsigned char)'З':
		case (unsigned char)'з':
			shot.x = 8;
			break;

		case (unsigned char)'И':
		case (unsigned char)'и':
			shot.x = 9;
			break;

		case (unsigned char)'К':
		case (unsigned char)'к':
			shot.x = 10;
			break;

		default:
			break;
		}

		cout << "Число";
		shot.y = CinValueInRange(beginRange, endRange);
		cout << endl;

		if (field[shot.y][shot.x] == Hit || field[shot.y][shot.x] == Miss || field[shot.y][shot.x] == Killed)
		{
			cout << "Выстрел по введенным координатам невозможен! Повторите ввод!" << endl << endl;
			system("pause");
			system("cls");
		}

	} while (field[shot.y][shot.x] == Hit || field[shot.y][shot.x] == Miss || field[shot.y][shot.x] == Killed);

	system("pause");
	system("cls");
}

//СТРЕЛЬБА ИГРОКА
inline ShotResult PlayerShooting(char field[Rows][Columns], ShotResult& shot)
{
	InputCoordinatesForShot(field, shot);

	if (field[shot.y][shot.x] == Ship)
		IfShotHit(field, shot);

	else if (field[shot.y][shot.x] == Empty)
		IfShotMiss(field, shot);

	return shot;
}