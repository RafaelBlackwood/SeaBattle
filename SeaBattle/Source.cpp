#include<iostream>
#include<time.h>
#include"windows.h"

using namespace std;


 HANDLE my_color = GetStdHandle(STD_OUTPUT_HANDLE);//HANDLE - это Дескриптор. этим мы задаём атрибуты для шрифта консоли, можем и покрасить его.
	//STD_OUTPUT_HANDLE - Стандартное устройство вывода. Первоначально это активный буфер экрана консоли

void gotoxy(int x, int y)//Отрисовывает данные по заданным координатам на командой строке
{
	COORD pos = { x,y };// структура, указывающая текущие координаты столбца и строки курсора.
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);//Установить курсор на позицию 
}

int** CreateArray(const int size1, const int size2)
{
	SetConsoleTextAttribute(my_color, FOREGROUND_RED | FOREGROUND_INTENSITY);
	if (size1 <= 0 || size2 <= 0)
	{
		cout << "Invalid size\n";
		return nullptr;
	}
	int** temp = new int* [size1];
	for (int i = 0; i < size1; i++)
	{
		temp[i] = new int[size2];
	}
	return temp;
}
void Instructions()
{
	SetConsoleTextAttribute(my_color, FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "Welcome to the sea battle!\n\nAllocate your ships onto the map.\n\nMake sure that your ships don't stand nearby one another. Try to desyroy enemy's ships\n\n";
}

void FillArrayByZeros(int* arr, const int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = 0;
	}
}
void FillArrayByZeros(int** arr, const int size1, const int size2)
{
	for (int i = 0; i < size1; i++)
	{
		FillArrayByZeros(arr[i], size2);
	}
}


void PrintArray(int** arr, const int size1, const int size2)
{

	char ship = 127;
	SetConsoleTextAttribute(my_color, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "   0 1 2 3 4 5 6 7 8 9\n";
	cout << "   ___________________\n";
	for (int i = 1; i < size1 - 1; i++)
	{

		cout << i - 1 << " |";
		for (int j = 1; j < size2 - 1; j++)
		{

			if (arr[i][j] == 0)
			{
				cout << "- ";
			}
			else if (arr[i][j] == 1)
			{
				cout << ship << " ";
			}


		}
		cout << endl;
	}
}

void ShipsCoordinates(int& x, int& y, int& vertical_or_horizontal)
{
	SetConsoleTextAttribute(my_color, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	do
	{
		cout << "Input X coordinate => ";
		cin >> x;
		cout << endl << endl;
	} while (x < 0 || x > 10);
	do
	{
		cout << "Input Y coordinate => ";
		cin >> y;
		cout << "\n\n";
	} while (y < 0 || y > 10);

	do
	{
		cout << "vertical_or_horizontal horizontal or vertical: ";
		cout << "1 if horizontal, 2 if vertcial => ";

		cin >> vertical_or_horizontal;
		cout << "\n\n";
	} while (vertical_or_horizontal < 1 || vertical_or_horizontal > 2);
}
void ShipsCoordinatesForOneDeck(int& x, int& y)
{

	SetConsoleTextAttribute(my_color, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	do
	{
		cout << "Input X coordinate => ";
		cin >> x;
		cout << endl << endl;
	} while (x < 0 || x > 10);
	do
	{

		cout << "Input Y coordinate => ";
		cin >> y;
		cout << "\n\n";
	} while (y < 0 || y > 10);

}

bool FourDeckShip(int** map, int x, int y, int vertical_or_horizontal)
{
	x ++;
	y ++;
	if (vertical_or_horizontal == 1 && y <= 7)
	{
		map[x][y] = 1;
		map[x][y + 1] = 1;
		map[x][y + 2] = 1;
		map[x][y + 3] = 1;
		return true;
	}

	else if (vertical_or_horizontal == 2 && x <= 7)
	{
		map[x][y] = 1;
		map[x + 1][y] = 1;
		map[x + 2][y] = 1;
		map[x + 3][y] = 1;
		return true;
	}
	return false;

}
bool ThreeDeckShip(int** map, int x, int y, int vertical_or_horizontal)
{
	x++;
	y++;

	if (vertical_or_horizontal == 1 && y <= 8)
	{
		if (map[x][y - 1] != 1 && map[x][y + 3] != 1 &&
			map[x - 1][y - 1] != 1 && map[x - 1][y] != 1 && map[x - 1][y + 1] != 1 && map[x - 1][y + 2] != 1 && map[x - 1][y + 3] != 1 &&
			map[x + 1][y - 1] != 1 && map[x + 1][y] != 1 && map[x + 1][y + 1] != 1 && map[x + 1][y + 2] != 1 && map[x + 1][y + 1] != 1)
		{
			map[x][y] = 1;
			map[x][y + 1] = 1;
			map[x][y + 2] = 1;
			return true;
		}
	}
	else if (vertical_or_horizontal == 2 && x <= 8)
	{
		if (map[x - 1][y] != 1 && map[x + 3][y] != 1 && map[x - 1][y - 1] != 1 && map[x - 1][y + 1] != 1 && map[x + 3][y - 1] != 1 && map[x + 3][y + 1] != 1 &&
			map[x][y - 1] != 1 && map[x][y + 1] != 1 && map[x + 1][y - 1] != 1 && map[x + 1][y + 1] != 1 && map[x + 2][y - 1] != 1 && map[x + 2][y + 1] != 1)
		{
			map[x][y] = 1;
			map[x + 1][y] = 1;
			map[x + 2][y] = 1;
			return true;
		}
	}
	return false;

}
bool TwoDeckShip(int** map, int x, int y, int vertical_or_horizontal)
{
	x++;
	y++;

	if (vertical_or_horizontal == 1 && y <= 9)
	{
		if (map[x][y - 1] != 1 && map[x - 1][y] != 1 && map[x + 1][y] != 1
			&& map[x + 1][y - 1] != 1 && map[x + 1][y + 1] != 1 && map[x - 1][y + 2] != 1
			&& map[x + 1][y + 2] != 1 && map[x - 1][y - 1] != 1 && map[x - 1][y + 1] != 1 && map[x][y + 2] != 1)
		{
			map[x][y] = 1;
			map[x][y + 1] = 1;

			return true;
		}
	}
	else if (vertical_or_horizontal == 2 && x <= 9)
	{
		if (map[x - 1][y] != 1 && map[x][y] != 1 && map[x + 2][y] != 1 && map[x][y] != 1 && map[x - 1][y - 1] != 1 && map[x - 1][y + 1] != 1 &&
			map[x][y] != 1 && map[x][y - 1] != 1 && map[x][y + 1] != 1 && map[x + 1][y - 1] != 1 && map[x + 1][y + 1] != 1 && map[x + 2][y - 1] != 1 && map[x + 2][y + 1] != 1)
		{
			map[x][y] = 1;
			map[x + 1][y] = 1;

			return true;
		}
	}
	return false;
}
bool OneDeckShip(int** map, int x, int y)
{
	x++;
	y++;
	if (map[x][y + 1] != 1 && map[x][y - 1] != 1 && map[x - 1][y] != 1 && map[x + 1][y] != 1 && map[x - 1][y - 1] != 1 && map[x - 1][y + 1] != 1 &&
		map[x + 1][y - 1] != 1 && map[x + 1][y + 1] != 1)
	{
		map[x][y] = 1;
		return true;
	}
	return false;
}
void ManualInput(int** map, int x, int y, int vertical_or_horizontal)
{
	bool input_is_possible = 0;
	cout << "Input coordinates of your 4-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = FourDeckShip(map, x, y, vertical_or_horizontal);
	}
	cout << "\n\n";
	PrintArray(map, 12, 12);

	input_is_possible = 0;
	cout << "Input coordinates of your first 3-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = ThreeDeckShip(map, x, y, vertical_or_horizontal);

	}
	cout << "\n\n";
	PrintArray(map, 12, 12);

	input_is_possible = 0;
	cout << "Input coordinates of your second 3-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = ThreeDeckShip(map, x, y, vertical_or_horizontal);

	}
	cout << "\n\n";
	PrintArray(map, 12, 12);

	input_is_possible = 0;
	cout << "Input coordinates of your first 2-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = TwoDeckShip(map, x, y, vertical_or_horizontal);

	}
	cout << "\n\n";
	PrintArray(map, 12, 12);

	input_is_possible = 0;
	cout << "Input coordinates of your second 2-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = TwoDeckShip(map, x, y, vertical_or_horizontal);

	}
	cout << "\n\n";
	PrintArray(map, 12, 12);

	input_is_possible = 0;
	cout << "Input coordinates of your third 2-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = TwoDeckShip(map, x, y, vertical_or_horizontal);

	}
	cout << "\n\n";
	PrintArray(map, 12, 12);

	input_is_possible = 0;
	cout << "Input coordinates of your first 1-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinatesForOneDeck(x, y);
		input_is_possible = OneDeckShip(map, x, y);

	}
	cout << "\n\n";
	PrintArray(map, 12, 12);

	input_is_possible = 0;
	cout << "Input coordinates of your second 1-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinatesForOneDeck(x, y);
		input_is_possible = OneDeckShip(map, x, y);

	}
	cout << "\n\n";
	PrintArray(map, 12, 12);


	input_is_possible = 0;
	cout << "Input coordinates of your third 1-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinatesForOneDeck(x, y);
		input_is_possible = OneDeckShip(map, x, y);

	}
	cout << "\n\n";
	PrintArray(map, 12, 12);

	input_is_possible = 0;
	cout << "Input coordinates of your fourth 1-deck ship\n\n";
	while (!input_is_possible)
	{
		ShipsCoordinatesForOneDeck(x, y);
		input_is_possible = OneDeckShip(map, x, y);

	}
	cout << "\n\n";
	PrintArray(map, 12, 12);

}


void RandomShipsCoordinates(int& x, int& y, int& vertical_or_horizontal)
{
	x = rand() % 10;
	y = rand() % 10;
	vertical_or_horizontal = 1 + rand() % 2; 
}
void RandomShipsCoordinatesForOneDeck(int& x, int& y)
{
	x = rand() % 10;
	y = rand() % 10;
}

bool RandomFourDeckShip(int** map, int x, int y, int vertical_or_horizontal)
{

	x++;
	y++;
	if (vertical_or_horizontal == 1 && y <= 7)
	{

		map[x][y] = 1;
		map[x][y + 1] = 1;
		map[x][y + 2] = 1;
		map[x][y + 3] = 1;
		return true;
	}

	else if (vertical_or_horizontal == 2 && x <= 7)


	{
		map[x][y] = 1;
		map[x + 1][y] = 1;
		map[x + 2][y] = 1;
		map[x + 3][y] = 1;
		return true;
	}
	RandomShipsCoordinates(x, y, vertical_or_horizontal);
	/*x = rand() % 10;
	y = rand() % 10;
	vertical_or_horizontal = rand() % 2;*/
	return false;


}
bool RandomThreeDeckShip(int** map, int x, int y, int vertical_or_horizontal)
{
	x++;
	y++;

	if (vertical_or_horizontal == 1 && y <= 8)
	{
		if (map[x][y - 1] != 1 && map[x][y + 3] != 1 &&
			map[x - 1][y - 1] != 1 && map[x - 1][y] != 1 && map[x - 1][y + 1] != 1 && map[x - 1][y + 2] != 1 && map[x - 1][y + 3] != 1 &&
			map[x + 1][y - 1] != 1 && map[x + 1][y] != 1 && map[x + 1][y + 1] != 1 && map[x + 1][y + 2] != 1 && map[x + 1][y + 1] != 1)
		{
			map[x][y] = 1;
			map[x][y + 1] = 1;
			map[x][y + 2] = 1;
			return true;
		}


	}
	else if (vertical_or_horizontal == 2 && x <= 8)
	{
		if (map[x - 1][y] != 1 && map[x + 3][y] != 1 && map[x - 1][y - 1] != 1 && map[x - 1][y + 1] != 1 && map[x + 3][y - 1] != 1 && map[x + 3][y + 1] != 1 &&
			map[x][y - 1] != 1 && map[x][y + 1] != 1 && map[x + 1][y - 1] != 1 && map[x + 1][y + 1] != 1 && map[x + 2][y - 1] != 1 && map[x + 2][y + 1] != 1)
		{
			map[x][y] = 1;
			map[x + 1][y] = 1;
			map[x + 2][y] = 1;
			return true;
		}

	}

	RandomShipsCoordinates(x, y, vertical_or_horizontal);
	/*x = rand() % 10;
	y = rand() % 10;
	vertical_or_horizontal = rand() % 2;*/
	return false;

}
bool RandomTwoDeckShip(int** map, int x, int y, int vertical_or_horizontal)
{
	x++;
	y++;

	if (vertical_or_horizontal == 1 && y <= 9)
	{
		if (map[x][y - 1] != 1 && map[x - 1][y] != 1 && map[x + 1][y] != 1
			&& map[x + 1][y - 1] != 1 && map[x + 1][y + 1] != 1 && map[x - 1][y + 2] != 1
			&& map[x + 1][y + 2] != 1 && map[x - 1][y - 1] != 1 && map[x - 1][y + 1] != 1 && map[x][y + 2] != 1)
		{
			map[x][y] = 1;
			map[x][y + 1] = 1;

			return true;
		}


	}
	else if (vertical_or_horizontal == 2 && x <= 9)
	{
		if (map[x - 1][y] != 1 && map[x][y] != 1 && map[x + 2][y] != 1 && map[x][y] != 1 && map[x - 1][y - 1] != 1 && map[x - 1][y + 1] != 1 &&
			map[x][y] != 1 && map[x][y - 1] != 1 && map[x][y + 1] != 1 && map[x + 1][y - 1] != 1 && map[x + 1][y + 1] != 1 && map[x + 2][y - 1] != 1 && map[x + 2][y + 1] != 1)
		{
			map[x][y] = 1;
			map[x + 1][y] = 1;

			return true;
		}

	}
	RandomShipsCoordinates(x, y, vertical_or_horizontal);
	/*x = rand() % 10;
	y = rand() % 10;
	vertical_or_horizontal = rand() % 2;*/
	return false;

}
bool RandomOneDeckShip(int** map, int x, int y)
{
	x++;
	y++;

	if (map[x][y + 1] != 1 && map[x][y - 1] != 1 && map[x - 1][y] != 1 && map[x + 1][y] != 1 && map[x - 1][y - 1] != 1 && map[x - 1][y + 1] != 1 &&
		map[x + 1][y - 1] != 1 && map[x + 1][y + 1] != 1)
	{
		map[x][y] = 1;
		return true;
	}
	RandomShipsCoordinatesForOneDeck(x, y);
	return false;

}
void RandomInput(int** map, int x, int y, int vertical_or_horizontal)
{
	bool input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = RandomFourDeckShip(map, x, y, vertical_or_horizontal);

	}

	input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = RandomThreeDeckShip(map, x, y, vertical_or_horizontal);
	}

	input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = RandomThreeDeckShip(map, x, y, vertical_or_horizontal);
	}

	input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = RandomTwoDeckShip(map, x, y, vertical_or_horizontal);
	}

	input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = RandomTwoDeckShip(map, x, y, vertical_or_horizontal);
	}

	input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinates(x, y, vertical_or_horizontal);
		input_is_possible = RandomTwoDeckShip(map, x, y, vertical_or_horizontal);
	}

	input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinatesForOneDeck(x, y);
		input_is_possible = RandomOneDeckShip(map, x, y);
	}

	input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinatesForOneDeck(x, y);
		input_is_possible = RandomOneDeckShip(map, x, y);
	}

	input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinatesForOneDeck(x, y);
		input_is_possible = RandomOneDeckShip(map, x, y);
	}


	input_is_possible = 0;
	while (!input_is_possible)
	{
		RandomShipsCoordinatesForOneDeck(x, y);
		input_is_possible = RandomOneDeckShip(map, x, y);
	}
	cout << "\n\n";
	PrintArray(map, 12, 12);
}

void BotRandomMapFill(int** map, int size)
{
	int x = 0;
	int y = 0;
	int vertical_or_horizontal = 0;
	RandomInput(map, x, y, vertical_or_horizontal);
}

void MapFill(int** map, int size)
{
	int x = 0;
	int y = 0;
	int vertical_or_horizontal = 0;

	int user_choice;
	do
	{
		cout << "Press \"1\" for manual ships allocation\n\n";
		cout << "Press \"2\" for random ships allocation\n\n";
		cout << "Choose input mode => ";
		cin >> user_choice;
		cout << endl << endl;


	} while (user_choice < 1 || user_choice > 2);

	if (user_choice == 1)
	{
		PrintArray(map, size, size);
		ManualInput(map, x, y, vertical_or_horizontal);
	}
	else if (user_choice == 2)
	{
		RandomInput(map, x, y, vertical_or_horizontal);
	}
}

void PrintMyMap(int** first_player_map, int size)
{
	char ship = 127;
	SetConsoleTextAttribute(my_color, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "   0 1 2 3 4 5 6 7 8 9\n";
	cout << "   ___________________\n";
	for (int i = 1; i < size - 1; i++)
	{

		cout << i - 1 << " |";
		for (int j = 1; j < size - 1; j++)
		{

			if (first_player_map[i][j] == 0)
			{
				cout << "~ ";
			}
			else if (first_player_map[i][j] == 1)
			{
				cout << ship << " ";
			}
			else if (first_player_map[i][j] == 5) {
				cout << "* ";
			}
			else if (first_player_map[i][j] == 2) {
				cout << "x ";
			}
			else if (first_player_map[i][j] == 3) {
				cout << "X ";
			}

		}
		cout << endl;
	}
}
void PrintMyField(int** first_player_field, int size)
{
	char ship = 127;
	gotoxy(30, 0);
	SetConsoleTextAttribute(my_color, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout << "   0 1 2 3 4 5 6 7 8 9\n";
	gotoxy(30, 1);
	cout << "   ___________________\n";
	for (int i = 1; i < size - 1; i++)
	{
		gotoxy(30, i + 1);
		cout << i - 1 << " |";

		for (int j = 1; j < size - 1; j++)
		{

			if (first_player_field[i][j] == 0)
			{
				cout << "~ ";
			}
			else if (first_player_field[i][j] == 1)
			{
				cout << ship << " ";
			}
			else if (first_player_field[i][j] == 5) {
				cout << "* ";
			}
			else if (first_player_field[i][j] == 2) {
				cout << "x ";
			}
			else if (first_player_field[i][j] == 3) {
				cout << "X ";
			}

		}

		cout << endl;
	}
}
void PrintEnemyMap(int** second_player_map, int size)
{
	char ship = 127;
	gotoxy(60, 0);
	
	cout << "   0 1 2 3 4 5 6 7 8 9\n";
	gotoxy(60, 1);
	cout << "   ___________________\n";
	for (int i = 1; i < size - 1; i++)
	{
		gotoxy(60, i + 1);
		cout << i - 1 << " |";


		for (int j = 1; j < size - 1; j++)
		{

			if (second_player_map[i][j] == 0)
			{
				cout << "~ ";
			}
			else if (second_player_map[i][j] == 1)
			{
				cout << ship << " ";
			}
			else if (second_player_map[i][j] == 5) {
				cout << "* ";
			}
			else if (second_player_map[i][j] == 2) {
				cout << "x ";
			}
			else if (second_player_map[i][j] == 3) {
				cout << "X ";
			}

		}

		cout << endl;
	}

}
void PrintEnemyField(int** second_player_field, int size)
{
	char ship = 127;
	gotoxy(90, 0);
	
	cout << "   0 1 2 3 4 5 6 7 8 9\n";
	gotoxy(90, 1);
	cout << "   ___________________\n";
	for (int i = 1; i < size - 1; i++)
	{
		gotoxy(90, i + 1);
		cout << i - 1 << " |";
		for (int j = 1; j < size - 1; j++)
		{
			if (second_player_field[i][j] == 0)
			{
				cout << "~ ";
			}
			else if (second_player_field[i][j] == 1)
			{
				cout << ship << " ";
			}
			else if (second_player_field[i][j] == 5) {
				cout << "* ";
			}
			else if (second_player_field[i][j] == 2) {
				cout << "x ";
			}
			else if (second_player_field[i][j] == 3) {
				cout << "X ";
			}
		}
		cout << endl;
	}
}
bool WinCheck(int** map, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (map[i][j] == 1)
			{
				return false;
			}
		}
	}
	return true;
}

bool Logic(int** my_empty_map, int** enemy_full_map, int& x, int& y)
{
	//есть корабль = 1
	//ранил = 2 
	//убил = 3 
	//промах = 5

	if (enemy_full_map[x][y] == 1)
	{
		bool check = false;
		if (enemy_full_map[x - 1][y] == 1 || enemy_full_map[x + 1][y] == 1 || enemy_full_map[x][y - 1] == 1 || enemy_full_map[x][y + 1] == 1)
		{
			enemy_full_map[x][y] = 2;
			my_empty_map[x][y] = 2;
			check = true;
		}
		else if (enemy_full_map[x - 1][y] == 2 || enemy_full_map[x + 1][y] == 2 || enemy_full_map[x][y - 1] == 2 || enemy_full_map[x][y + 1] == 2)
		{
			enemy_full_map[x][y] = 2;
			my_empty_map[x][y] = 2;
			check = false;
			if (enemy_full_map[x - 1][y] == 2)
			{
				if (enemy_full_map[x - 2][y] == 1)
				{
					check = true;
				}
				else if (enemy_full_map[x - 2][y] == 2)
				{
					if (enemy_full_map[x - 3][y] == 1)
					{
						check = true;
					}
				}
			}
			if (enemy_full_map[x + 1][y] == 2)
			{
				if (enemy_full_map[x + 2][y] == 1)
				{
					check = true;
				}
				else if (enemy_full_map[x + 2][y] == 2)
				{
					if (enemy_full_map[x + 3][y] == 1)
					{
						check = true;
					}
				}
			}
			if (enemy_full_map[x][y - 1] == 2)
			{
				if (enemy_full_map[x][y - 2] == 1)
				{
					check = true;
				}
				else if (enemy_full_map[x][y - 2] == 2)
				{
					if (enemy_full_map[x][y - 3] == 1)
					{
						check = true;
					}
				}
			}
			if (enemy_full_map[x][y + 1] == 2)
			{
				if (enemy_full_map[x][y + 2] == 1)
				{
					check = true;
				}
				else if (enemy_full_map[x][y + 2] == 2)
				{
					if (enemy_full_map[x][y + 3] == 1)
					{
						check = true;
					}
				}
			}
		}

		if (!check)
		{
			enemy_full_map[x][y] = 3;
			my_empty_map[x][y] = 3;
			int i = 1;
			while (true)
			{

				if (enemy_full_map[x - i][y] == 2)
				{
					enemy_full_map[x - i][y] = 3;
					my_empty_map[x - i][y] = 3;

					i++;
				}
				else if (enemy_full_map[x - i][y] == 0 || enemy_full_map[x - i][y] == 5)
				{
					break;
				}
				else break;
			}
			i = 1;
			while (true)
			{

				if (enemy_full_map[x + i][y] == 2)
				{
					enemy_full_map[x + i][y] = 3;
					my_empty_map[x + i][y] = 3;

					i++;
				}
				else if (enemy_full_map[x + i][y] == 0 || enemy_full_map[x + i][y] == 5)
				{
					break;
				}
				else break;
			}
			i = 1;
			while (true)
			{

				if (enemy_full_map[x][y - i] == 2)
				{
					enemy_full_map[x][y - i] = 3;
					my_empty_map[x][y - i] = 3;

					i++;
				}
				else if (enemy_full_map[x][y - i] == 0 || enemy_full_map[x][y - i] == 5)
				{
					break;
				}
				else break;
			}
			i = 1;
			while (true)
			{
				if (enemy_full_map[x][y + i] == 2)
				{
					enemy_full_map[x][y + i] = 3;
					my_empty_map[x][y + i] = 3;

					i++;
				}
				else if (enemy_full_map[x][y + i] == 0 || enemy_full_map[x][y + i] == 5)
				{
					break;
				}
				else break;
			}

		}
		return true;
	}
	else if (enemy_full_map[x][y] == 0)
	{
		enemy_full_map[x][y] = 5;
		my_empty_map[x][y] = 5;
		return false;
	}
	return false;
}

bool ShootingRulesForThePlayer(int** my_empty_map, int** enemy_full_map)
{
	int x;
	int y;
	cout << "Input coordinates to shoot\n\n";
	ShipsCoordinatesForOneDeck(x, y);
	x ++;
	y ++;
	return Logic(my_empty_map, enemy_full_map, x, y);
}

void FirstPlayerTurn(int** first_player_map, int** first_player_field, int** second_player_map, int size, bool& turn_end, bool& end)
{
	system("cls");

	PrintMyMap(first_player_map, size);
	PrintMyField(first_player_field, size);
	cout << "\n\nFirst player's turn \n\n";
	turn_end = ShootingRulesForThePlayer(first_player_field, second_player_map);

	system("cls");
	PrintMyMap(first_player_map, size);
	PrintMyField(first_player_field, size);
	if (WinCheck(second_player_map, size))
	{
		turn_end = false;
		end = true;
		cout << "\n\n\n Firts player has won! \n\n";
	}
}

void EasyBot(int** my_empty_map, int** const enemy_full_map, bool& turn_end, bool& end)
{
	int x;
	int y;
	bool random_end = true;
	while (random_end)
	{
		x = rand() % 10;
		y = rand() % 10;
		x++;
		y++;
		if (enemy_full_map[x][y] == 1 || enemy_full_map[x][y] == 0)
		{
			random_end = false;
		}
	}
	turn_end = Logic(my_empty_map, enemy_full_map, x, y);
	if (WinCheck(enemy_full_map, 12))
	{
		turn_end = false;
		end = true;
		system("cls");
		PrintEnemyMap(enemy_full_map, 12);

		cout << "\n\n\n Bot has won!\n\n";
	}
}

bool HaveWounded(int** map, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (map[i][j] == 2) {
				return true;
			}
		}
	}
	return false;
}

void SmartBot(int** my_empty_map, int** enemy_full_map, bool& turn_end, bool& end)
{
	int x;
	int y;
	bool random_end = true;
	if (HaveWounded(enemy_full_map, 12))
	{
		int corX = 0;
		int corY = 0;

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				if (enemy_full_map[i][j] == 2)
				{
					corX = i;
					corY = j;
					break;
				}
			}
		}

		if (enemy_full_map[corX + 1][corY] == 1)
		{
			x = corX + 1;
			y = corY;
		}

		else if (enemy_full_map[corX - 1][corY] == 1)
		{
			x = corX - 1;
			y = corY;
		}



		else if (enemy_full_map[corX][corY + 1] == 1)
		{
			x = corX;
			y = corY + 1;
		}


		else if (enemy_full_map[corX][corY - 1] == 1)
		{
			x = corX;
			y = corY - 1;
		}

	}
	else
	{
		while (random_end)
		{
			x = rand() % 10;
			y = rand() % 10;
			x ++;
			y ++;
			if (enemy_full_map[x][y] == 1 || enemy_full_map[x][y] == 0)
			{
				random_end = false;
			}
		}
	}
	turn_end = Logic(my_empty_map, enemy_full_map, x, y);
	if (WinCheck(enemy_full_map, 12)) {
		turn_end = false;
		end = true;
		cout << "\n\n\n Bot has won!\n\n";
	}
}

void Play(int** first_player_map, int** first_player_field, int** second_player_map, int** second_player_field, int size)
{
	int choose;
	do
	{
		Instructions();
		cout << "_____________________________________________________________________________________\n\n";
		SetConsoleTextAttribute(my_color, FOREGROUND_BLUE | FOREGROUND_INTENSITY);//Функция SetConsoleTextAttribute устанавливает атрибуты символов, записанных в экранный буфер консоли 
		cout << "Press \"1\" to play with silly bot\n\n";
		SetConsoleTextAttribute(my_color, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Press \"2\" to play with smart bot\n\n";
		SetConsoleTextAttribute(my_color, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Press \"3\" to exit\n\n";
		SetConsoleTextAttribute(my_color, FOREGROUND_RED | FOREGROUND_GREEN);
		cout << "Input your choice => ";
		cin >> choose;
		system("cls");

	} while (choose > 3 || choose < 1);

	bool end = false;
	bool turn_end;

	switch (choose)
	{

	case 1:
	{
		end = false;
		MapFill(first_player_map, size);
		BotRandomMapFill(second_player_map, size);
		while (!end)
		{
			turn_end = true;
			while (turn_end)
			{
				FirstPlayerTurn(first_player_map, first_player_field, second_player_map, size, turn_end, end);
			}
			if (!end) turn_end = true;
			while (turn_end)
			{
				EasyBot(second_player_field, first_player_map, turn_end, end);
			}
		}

	}
	break;
	case 2:
	{
		end = false;
		MapFill(first_player_map, size);
		BotRandomMapFill(second_player_map, size);
		while (!end) {
			turn_end = true;
			while (turn_end)
			{
				FirstPlayerTurn(first_player_map, first_player_field, second_player_map, size, turn_end, end);

			}
			if (!end) turn_end = true;
			while (turn_end)
			{
				SmartBot(second_player_field, first_player_map, turn_end, end);
			}
		}
	}
	break;
	case 3:
	{
		cout << "Goodbye\n\n";
	}
	break;
	default:
	{
		cout << "Wrong button try again\n\n";
	}
	break;
	}
}

int main()
{
	srand(time(NULL));
	const int size = 12;



	int** map = CreateArray(size, size);
	FillArrayByZeros(map, size, size);

	int** map2 = CreateArray(size, size);
	FillArrayByZeros(map2, size, size);

	int** first_player_field = CreateArray(size, size);
	int** second_player_field = CreateArray(size, size);
	FillArrayByZeros(first_player_field, size, size);
	FillArrayByZeros(second_player_field, size, size);
	system("cls");
	Play(map, first_player_field, map2, second_player_field, size);
}