#include <iostream>
#include <ctime>
using namespace std;


//ЗАПОЛНЕНИЕ ПОЛЯ ПРОБЕЛАМИ
void FillFieldToSpaces(char playField[10][10], const int rows, const int columns)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			playField[i][j] = ' ';
}

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК РАЗМЕЩЕНИЯ ГОРИЗОНТАЛЬНЫХ КОРАБЛЕЙ ДЛЯ КОМПА
void RandomisesStartPointsForHorizontalShips(char playField[10][10], const int rows, const int columns, const int shipSize, int& horizontalStartPoint, int& verticalStartPoint, const char shipsSymbol)
{
	const int BeginRange = 0;
	const int EndRange = 9;

	bool isSetNotPossible = true;

	do
	{
		verticalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;
		horizontalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (horizontalStartPoint + shipSize > columns)
			continue;

		isSetNotPossible = false;

		if (horizontalStartPoint == 0 && verticalStartPoint == 0)
		{
			for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			{
				if (playField[verticalStartPoint][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint + 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint + shipSize == columns && verticalStartPoint == 0)
		{
			for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			{
				if (playField[verticalStartPoint][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint + 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == 0 && verticalStartPoint == rows - 1)
		{
			for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			{
				if (playField[verticalStartPoint - 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint + shipSize == columns && verticalStartPoint == rows - 1)
		{
			for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			{
				if (playField[verticalStartPoint - 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == 0 && verticalStartPoint != 0 && verticalStartPoint != rows - 1)
		{
			for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			{
				if (playField[verticalStartPoint - 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint + 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint + shipSize == columns && verticalStartPoint != 0 && verticalStartPoint != rows - 1)
		{
			for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			{
				if (playField[verticalStartPoint - 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint + 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint != 0 && horizontalStartPoint + shipSize != columns && verticalStartPoint == 0)
		{
			for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
			{
				if (playField[verticalStartPoint][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint + 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint != 0 && horizontalStartPoint + shipSize != columns && verticalStartPoint == rows - 1)
		{
			for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
			{
				if (playField[verticalStartPoint][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint - 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else
		{
			for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
			{
				if (playField[verticalStartPoint - 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[verticalStartPoint + 1][i] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

	} while (isSetNotPossible);
}

//РАНДОМ НАЧАЛЬНЫХ ТОЧЕК РАЗМЕЩЕНИЯ ВЕРТИКАЛЬНЫХ КОРАБЛЕЙ ДЛЯ КОМПА
void RandomisesStartPointsForVerticalShips(char playField[10][10], const int rows, const int columns, const int shipSize, int& horizontalStartPoint, int& verticalStartPoint, const char shipsSymbol)
{
	const int BeginRange = 0;
	const int EndRange = 9;

	bool isSetNotPossible = true;

	do
	{
		verticalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;
		horizontalStartPoint = rand() % (EndRange - BeginRange + 1) + BeginRange;

		if (verticalStartPoint + shipSize > rows)
			continue;

		isSetNotPossible = false;

		if (horizontalStartPoint == 0 && verticalStartPoint == 0)
		{
			for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == columns - 1 && verticalStartPoint == 0)
		{
			for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint - 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == 0 && verticalStartPoint + shipSize == rows)
		{
			for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == columns - 1 && verticalStartPoint + shipSize == rows)
		{
			for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == 0 && verticalStartPoint != 0 && verticalStartPoint + shipSize != rows)
		{
			for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint + 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint == columns - 1 && verticalStartPoint != 0 && verticalStartPoint + shipSize != rows)
		{
			for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint != 0 && horizontalStartPoint != columns - 1 && verticalStartPoint == 0)
		{
			for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else if (horizontalStartPoint != 0 && horizontalStartPoint != columns - 1 && verticalStartPoint + shipSize == rows) 
		{
			for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

		else
		{
			for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			{
				if (playField[i][horizontalStartPoint - 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
				if (playField[i][horizontalStartPoint + 1] == shipsSymbol)
				{
					isSetNotPossible = true;
					break;
				}
			}

			if (isSetNotPossible)
				continue;
		}

	} while (isSetNotPossible);
}

//ГОРИЗАНТАЛЬНОЕ РАЗМЕЩЕНИЕ КОРАБЛЯ ДЛЯ КОМПА
void SetShipHorizontal(char playField[10][10], const int rows, const int columns, const int shipSize, const int horizontalStartPoint, const int verticalStartPoint, const char shipsSymbol)
{
	const char CellNextToShip = '-';

	if (horizontalStartPoint == 0 && verticalStartPoint == 0)
	{
		for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint][i] = shipsSymbol;

		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint + 1][i] = CellNextToShip;

		playField[verticalStartPoint][horizontalStartPoint + shipSize] = CellNextToShip;
	}

	else if (horizontalStartPoint + shipSize == columns && verticalStartPoint == 0)
	{
		for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint][i] = shipsSymbol;

		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint + 1][i] = CellNextToShip;

		playField[verticalStartPoint][horizontalStartPoint - 1] = CellNextToShip;
	}

	else if (horizontalStartPoint == 0 && verticalStartPoint == rows - 1)
	{
		for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint][i] = shipsSymbol;

		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint - 1][i] = CellNextToShip;

		playField[verticalStartPoint][horizontalStartPoint + shipSize] = CellNextToShip;
	}

	else if (horizontalStartPoint + shipSize == columns && verticalStartPoint == rows - 1)
	{
		for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint][i] = shipsSymbol;

		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint - 1][i] = CellNextToShip;

		playField[verticalStartPoint][horizontalStartPoint - 1] = CellNextToShip;
	}

	else if (horizontalStartPoint == 0 && verticalStartPoint != 0 && verticalStartPoint != rows - 1)
	{
		for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint][i] = shipsSymbol;

		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint + 1][i] = CellNextToShip;

		for (int i = horizontalStartPoint; i <= horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint - 1][i] = CellNextToShip;

		playField[verticalStartPoint][horizontalStartPoint + shipSize] = CellNextToShip;
	}

	else if (horizontalStartPoint + shipSize == columns && verticalStartPoint != 0 && verticalStartPoint != rows - 1)
	{
		for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint][i] = shipsSymbol;

		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint + 1][i] = CellNextToShip;

		for (int i = horizontalStartPoint - 1; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint - 1][i] = CellNextToShip;

		playField[verticalStartPoint][horizontalStartPoint - 1] = CellNextToShip;
	}

	else if (horizontalStartPoint != 0 && horizontalStartPoint + shipSize != columns && verticalStartPoint == 0)
	{
		for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint][i] = shipsSymbol;

		for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint + 1][i] = CellNextToShip;

		playField[verticalStartPoint][horizontalStartPoint + shipSize] = CellNextToShip;
		playField[verticalStartPoint][horizontalStartPoint - 1] = CellNextToShip;
	}

	else if (horizontalStartPoint != 0 && horizontalStartPoint + shipSize != columns && verticalStartPoint == rows - 1)
	{
		for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint][i] = shipsSymbol;

		for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint - 1][i] = CellNextToShip;

		playField[verticalStartPoint][horizontalStartPoint + shipSize] = CellNextToShip;
		playField[verticalStartPoint][horizontalStartPoint - 1] = CellNextToShip;
	}

	else
	{
		for (int i = horizontalStartPoint; i < horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint][i] = shipsSymbol;

		for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint - 1][i] = CellNextToShip;

		for (int i = horizontalStartPoint - 1; i <= horizontalStartPoint + shipSize; i++)
			playField[verticalStartPoint + 1][i] = CellNextToShip;

		playField[verticalStartPoint][horizontalStartPoint + shipSize] = CellNextToShip;
		playField[verticalStartPoint][horizontalStartPoint - 1] = CellNextToShip;
	}
}

//ВЕРТИКАЛЬНОЕ РАЗМЕЩЕНИЕ КОРАБЛЯ ДЛЯ КОМПА
void SetShipVertical(char playField[10][10], const int rows, const int columns, const int shipSize, const int horizontalStartPoint, const int verticalStartPoint, const char shipsSymbol)
{
	const char CellNextToShip = '-';

	if (horizontalStartPoint == 0 && verticalStartPoint == 0)
	{
		for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint] = shipsSymbol;

		for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint + 1] = CellNextToShip;

		playField[verticalStartPoint + shipSize][horizontalStartPoint] = CellNextToShip;
	}

	else if (horizontalStartPoint == columns - 1 && verticalStartPoint == 0)
	{
		for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint] = shipsSymbol;

		for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint - 1] = CellNextToShip;

		playField[verticalStartPoint + shipSize][horizontalStartPoint] = CellNextToShip;
	}

	else if (horizontalStartPoint == 0 && verticalStartPoint + shipSize == rows)
	{
		for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint] = shipsSymbol;

		for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint + 1] = CellNextToShip;

		playField[verticalStartPoint - 1][horizontalStartPoint] = CellNextToShip;
	}

	else if (horizontalStartPoint == columns - 1 && verticalStartPoint + shipSize == rows)
	{
		for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint] = shipsSymbol;

		for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint - 1] = CellNextToShip;

		playField[verticalStartPoint - 1][horizontalStartPoint] = CellNextToShip;
	}

	else if (horizontalStartPoint == 0 && verticalStartPoint != 0 && verticalStartPoint + shipSize != rows)
	{
		for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint] = shipsSymbol;

		for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint + 1] = CellNextToShip;

		playField[verticalStartPoint + shipSize][horizontalStartPoint] = CellNextToShip;
		playField[verticalStartPoint - 1][horizontalStartPoint] = CellNextToShip;
	}

	else if (horizontalStartPoint == columns - 1 && verticalStartPoint != 0 && verticalStartPoint + shipSize != rows)
	{
		for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint] = shipsSymbol;

		for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint - 1] = CellNextToShip;

		playField[verticalStartPoint + shipSize][horizontalStartPoint] = CellNextToShip;
		playField[verticalStartPoint - 1][horizontalStartPoint] = CellNextToShip;
	}

	else if (horizontalStartPoint != 0 && horizontalStartPoint != columns - 1 && verticalStartPoint == 0)
	{
		for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint] = shipsSymbol;

		for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint - 1] = CellNextToShip;

		for (int i = verticalStartPoint; i <= verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint + 1] = CellNextToShip;

		playField[verticalStartPoint + shipSize][horizontalStartPoint] = CellNextToShip;
	}

	else if (horizontalStartPoint != 0 && horizontalStartPoint != columns - 1 && verticalStartPoint + shipSize == rows)
	{
		for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint] = shipsSymbol;

		for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint - 1] = CellNextToShip;

		for (int i = verticalStartPoint - 1; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint + 1] = CellNextToShip;

		playField[verticalStartPoint - 1][horizontalStartPoint] = CellNextToShip;
	}

	else
	{
		for (int i = verticalStartPoint; i < verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint] = shipsSymbol;

		for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint - 1] = CellNextToShip;

		for (int i = verticalStartPoint - 1; i <= verticalStartPoint + shipSize; i++)
			playField[i][horizontalStartPoint + 1] = CellNextToShip;

		playField[verticalStartPoint + shipSize][horizontalStartPoint] = CellNextToShip;
		playField[verticalStartPoint - 1][horizontalStartPoint] = CellNextToShip;
	}
}

//РАЗМЕЩЕНИЕ КОРАБЛЕЙ ДЛЯ КОМПА
void SetShip(char playField[10][10], const int rows, const int columns, const int shipSize)
{
	const char ShipsSymbol = 'S';
	const int BeginRange = 1;
	const int EndRange = 2;
	const int HorizontalShipDirection = 1;
	const int VerticalShipDirection = 2;

	int shipDirection = rand() % (EndRange - BeginRange + 1) + BeginRange;

	int horizontalStartPoint;
	int verticalStartPoint;

	if (shipDirection == HorizontalShipDirection)
	{
		RandomisesStartPointsForHorizontalShips(playField, rows, columns, shipSize, horizontalStartPoint, verticalStartPoint, ShipsSymbol);
		SetShipHorizontal(playField, rows, columns, shipSize, horizontalStartPoint, verticalStartPoint, ShipsSymbol);
	}

	else if (shipDirection == VerticalShipDirection)
	{
		RandomisesStartPointsForVerticalShips(playField, rows, columns, shipSize, horizontalStartPoint, verticalStartPoint, ShipsSymbol);
		SetShipVertical(playField, rows, columns, shipSize, horizontalStartPoint, verticalStartPoint, ShipsSymbol);
	}
}

//ПЕЧАТЬ БУКВ ДЛЯ ОБОЗНАЧЕНИЯ СТОЛБЦОВ
void PrintLetter()
{
	cout << "  ";
	for (unsigned char c = 224; c <= 234; c++)
		if (c != 233)
			cout << " " << c << " ";
	cout << endl;
}

//ПЕЧАТЬ ПОЛЯ - В РАЗРАБОТКЕ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void PrintField(char field[10][10], const int rows, const int columns)
{
	PrintLetter();

	for (int i = 0; i < rows; i++)
	{
		if (i == 9)
			cout << i + 1;
		else
			cout << " " << i + 1;

		for (int j = 0; j < columns; j++)
			cout << "[" << field[i][j] << "]";
		cout << endl;
	}

	cout << endl;
}

//MAIN()
void main()
{
	const int Rows = 10;
	const int Columns = 10;
	const int OneDeckSize = 1;
	const int TwoDeckSize = 2;
	const int ThreeDeckSize = 3;
	const int FourDeckSize = 4;

	setlocale(LC_ALL, "ru");
	srand(time(0));

	char playField[Rows][Columns];

	FillFieldToSpaces(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, FourDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, ThreeDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, ThreeDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, TwoDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, TwoDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, TwoDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, OneDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, OneDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, OneDeckSize);
	//PrintField(playField, Rows, Columns);

	SetShip(playField, Rows, Columns, OneDeckSize);
	//PrintField(playField, Rows, Columns);

	PrintField(playField, Rows, Columns);

	system("pause");
}