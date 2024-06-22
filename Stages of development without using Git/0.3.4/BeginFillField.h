#pragma once

//НАЧАЛЬНОЕ ЗАПОЛНЕНИЕ ПОЛЯ
inline void FieldInitialFill(char playField[Rows][Columns])
{
	const int firstRowIndex = 0;
	const int lastRowIndex = 11;
	const int firstColumnsIndex = 0;
	const int lastColumnsIndex = 11;

	for (int j = 0; j < Columns; j++)
		playField[firstRowIndex][j] = Miss;

	for (int i = 1; i < Rows - 1; i++)
		for (int j = 1; j < Columns - 1; j++)
		{
			playField[i][firstColumnsIndex] = Miss;
			playField[i][j] = Empty;
			playField[i][lastColumnsIndex] = Miss;
		}

	for (int j = 0; j < Columns; j++)
		playField[lastRowIndex][j] = Miss;
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
inline bool IsPossibleToPlaceHorizontalShip(char field[Rows][Columns], const int shipSize, const ShotResult& startCoordinate)
{
	for (int i = startCoordinate.x - 1; i <= startCoordinate.x + shipSize; i++)
	{
		if (field[startCoordinate.y - 1][i] == Ship)
			return true;
		if (field[startCoordinate.y][i] == Ship)
			return true;
		if (field[startCoordinate.y + 1][i] == Ship)
			return true;
	}

	return false;
}

//УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ
inline void GetStartPointsForHorizontalShip(char field[Rows][Columns], const int shipSize, ShotResult& startCoordinate)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	bool isSetNotPossible = true;

	do
	{
		startCoordinate.y = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCoordinate.x = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCoordinate.x + shipSize >= Columns)
			continue;

		isSetNotPossible = IsPossibleToPlaceHorizontalShip(field, shipSize, startCoordinate);

	} while (isSetNotPossible);
}

//ПРОВЕРКА НА РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ
inline bool IsPossibleToPlaceVerticalShip(char field[Rows][Columns], const int shipSize, const ShotResult& startCoordinate)
{
	for (int i = startCoordinate.y - 1; i <= startCoordinate.y + shipSize; i++)
	{
		if (field[i][startCoordinate.x - 1] == Ship)
			return true;
		if (field[i][startCoordinate.x] == Ship)
			return true;
		if (field[i][startCoordinate.x + 1] == Ship)
			return true;
	}

	return false;
}

//АВТОМАТИЧЕСКАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
inline void AutoGetStartPointsForVerticalShip(char field[Rows][Columns], const int shipSize, ShotResult& startCoordinate)
{
	const int BeginRange = 1;
	const int EndRange = 10;

	bool isSetNotPossible = true;

	do
	{
		startCoordinate.y = rand() % (EndRange - BeginRange + 1) + BeginRange;
		startCoordinate.x = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (startCoordinate.y + shipSize >= Rows)
			continue;

		isSetNotPossible = IsPossibleToPlaceVerticalShip(field, shipSize, startCoordinate);

	} while (isSetNotPossible);
}

//РАЗМЕЩЕНИЕ ГОРИЗАНТАЛЬНОГО КОРАБЛЯ 
inline void PlacementHorizontalShip(char field[Rows][Columns], const int shipSize, const ShotResult& startCoordinate)
{
	for (int i = startCoordinate.x; i < startCoordinate.x + shipSize; i++)
		field[startCoordinate.y][i] = Ship;
}

//РАЗМЕЩЕНИЕ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
inline void PlacementVerticalShip(char playField[Rows][Columns], const int shipSize, const ShotResult& startCoordinate)
{
	for (int i = startCoordinate.y; i < startCoordinate.y + shipSize; i++)
		playField[i][startCoordinate.x] = Ship;
}

//АВТОМАТИЧЕСКОЕ РАЗМЕЩЕНИЕ КОРАБЛЕЙ ЗАДАННЫМ РАЗМЕРОМ И КОЛИЧЕСТВОМ
inline void AutoShipsPlacement(char field[Rows][Columns], const int shipSize, const int shipsNumber)
{
	const int BeginRange = 1;
	const int EndRange = 2;
	const int HorizontalDirection = 1;
	const int VerticalDirection = 2;

	for (int i = 1; i <= shipsNumber; i++)
	{

		int shipDirection = rand() % (EndRange - BeginRange + 1) + BeginRange;

		ShotResult startCoordinate;

		if (shipDirection == HorizontalDirection)
		{
			GetStartPointsForHorizontalShip(field, shipSize, startCoordinate);
			PlacementHorizontalShip(field, shipSize, startCoordinate);
		}

		else if (shipDirection == VerticalDirection)
		{
			AutoGetStartPointsForVerticalShip(field, shipSize, startCoordinate);
			PlacementVerticalShip(field, shipSize, startCoordinate);
		}
	}
}

//АВТОМАТИЧЕСКОЕ ЗАПОЛНЕНИЕ ПОЛЯ КОРАБЛЯМИ
inline void AutoFillBattleField(char field[Rows][Columns])
{
	const int OneDeckSize = 1;
	const int TwoDeckSize = 2;
	const int ThreeDeckSize = 3;
	const int FourDeckSize = 4;

	const int OneDeckNumber = 4;
	const int TwoDeckNumber = 3;
	const int ThreeDeckNumber = 2;
	const int FourDeckNumber = 1;

	FieldInitialFill(field);

	AutoShipsPlacement(field, FourDeckSize, FourDeckNumber);
	AutoShipsPlacement(field, ThreeDeckSize, ThreeDeckNumber);
	AutoShipsPlacement(field, TwoDeckSize, TwoDeckNumber);
	AutoShipsPlacement(field, OneDeckSize, OneDeckNumber);
}

















//РУЧНАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ КОРАБЛЯ 
inline void InputStartCoordinates(char field[Rows][Columns], const int shipSize, ShotResult& startCoordinate)
{
	const int beginRange = 1;
	const int endRange = 10;

	cout << "Введите начальные координаты установки:" << endl << endl;
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
		startCoordinate.x = 1;
		break;

	case (unsigned char)'Б':
	case (unsigned char)'б':
		startCoordinate.x = 2;
		break;

	case (unsigned char)'В':
	case (unsigned char)'в':
		startCoordinate.x = 3;
		break;

	case (unsigned char)'Г':
	case (unsigned char)'г':
		startCoordinate.x = 4;
		break;

	case (unsigned char)'Д':
	case (unsigned char)'д':
		startCoordinate.x = 5;
		break;

	case (unsigned char)'Е':
	case (unsigned char)'е':
		startCoordinate.x = 6;
		break;

	case (unsigned char)'Ж':
	case (unsigned char)'ж':
		startCoordinate.x = 7;
		break;

	case (unsigned char)'З':
	case (unsigned char)'з':
		startCoordinate.x = 8;
		break;

	case (unsigned char)'И':
	case (unsigned char)'и':
		startCoordinate.x = 9;
		break;

	case (unsigned char)'К':
	case (unsigned char)'к':
		startCoordinate.x = 10;
		break;

	default:
		break;
	}

	cin.clear();
	cin.get();

	cout << "Число";
	startCoordinate.y = CinValueInRange(beginRange, endRange);
	cout << endl;

	cin.clear();
	cin.get();
}

//РУЧНАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНОГО КОРАБЛЯ 
inline bool TryManuallyGetStartPointsForHorizontalShip(char field[Rows][Columns], const int shipSize, ShotResult& startCoordinate)
{
	InputStartCoordinates(field, shipSize, startCoordinate);

	bool isSetNotPossible = IsPossibleToPlaceHorizontalShip(field, shipSize, startCoordinate);

	if (startCoordinate.x + shipSize >= Columns || isSetNotPossible)
	{
		cout << "Установка корабля по заданным координатам невозможна! Повторите ввод!" << endl << endl;
		return true;
	}

	return false;
}

//РУЧНАЯ УСТАНОВКА НАЧАЛЬНЫХ ТОЧЕК ДЛЯ РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНОГО КОРАБЛЯ 
inline bool TryManuallyGetStartPointsForVerticalShip(char field[Rows][Columns], const int shipSize, ShotResult& startCoordinate)
{
	InputStartCoordinates(field, shipSize, startCoordinate);

	bool isSetNotPossible = IsPossibleToPlaceVerticalShip(field, shipSize, startCoordinate);

	if (startCoordinate.y + shipSize >= Rows || isSetNotPossible)
	{
		cout << "Установка корабля по заданным координатам невозможна! Повторите ввод!" << endl << endl;
		return true;
	}

	return false;
}

//РУЧНОЕ РАЗМЕЩЕНИЕ КОРАБЛЕЙ ЗАДАННЫМ РАЗМЕРОМ И КОЛИЧЕСТВОМ
inline bool TryManuallyShipsPlacement(char field[Rows][Columns], const int shipSize, const int shipsNumber)
{
	const int BeginRange = 0;
	const int EndRange = 2;

	bool isShipNotSet;

	int i = 1;

	do
	{
		for (; i <= shipsNumber; i++)
		{
			cout << "     " << "Размещение " << shipSize << "-палубника" << endl << endl;

			PrintOnlyOneField(field);

			ShipsDirectionMenuItems shipDirection = ShipsDirectionMenu();

			ShotResult startCoordinate;

			switch (shipDirection)
			{
			case ShipsDirectionMenuItems::Horizontal:
			{
				isShipNotSet = TryManuallyGetStartPointsForHorizontalShip(field, shipSize, startCoordinate);
				break;
			}

			case ShipsDirectionMenuItems::Vertical:
			{
				isShipNotSet = TryManuallyGetStartPointsForVerticalShip(field, shipSize, startCoordinate);
				break;
			}

			case ShipsDirectionMenuItems::GoToMainMenu:
			{
				return false;
			}

			default:
				break;
			}

			if (isShipNotSet)
			{
				system("pause");
				system("cls");
				break;
			}

			switch (shipDirection)
			{
			case ShipsDirectionMenuItems::Horizontal:
			{
				PlacementHorizontalShip(field, shipSize, startCoordinate);
				break;
			}

			case ShipsDirectionMenuItems::Vertical:
			{
				PlacementVerticalShip(field, shipSize, startCoordinate);
				break;
			}

			default:
				break;
			}

			system("pause");
			system("cls");
		}

	} while (isShipNotSet);

	return true;
}

//РУЧНОЕ ЗАПОЛНЕНИЕ ПОЛЯ КОРАБЛЯМИ
inline bool TryManuallyFillBattleField(char field[Rows][Columns])
{
	const int OneDeckSize = 1;
	const int TwoDeckSize = 2;
	const int ThreeDeckSize = 3;
	const int FourDeckSize = 4;

	const int OneDeckNumber = 4;
	const int TwoDeckNumber = 3;
	const int ThreeDeckNumber = 2;
	const int FourDeckNumber = 1;

	FieldInitialFill(field);

	bool isShipPlacement;

	isShipPlacement = TryManuallyShipsPlacement(field, FourDeckSize, FourDeckNumber);
	if (!isShipPlacement)
		return false;

	isShipPlacement = TryManuallyShipsPlacement(field, ThreeDeckSize, ThreeDeckNumber);
	if (!isShipPlacement)
		return false;

	isShipPlacement = TryManuallyShipsPlacement(field, TwoDeckSize, TwoDeckNumber);
	if (!isShipPlacement)
		return false;

	isShipPlacement = TryManuallyShipsPlacement(field, OneDeckSize, OneDeckNumber);
	if (!isShipPlacement)
		return false;

	return true;
}