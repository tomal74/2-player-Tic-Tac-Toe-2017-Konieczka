#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <algorithm>
#include <time.h>
#include "tk_ox.h"


using namespace std;

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);



void rand_color(void)
{
	int x;
	char color[2];
	string comand = "color ";

	srand(time(NULL));
	x = rand() % 16;
	(x == 1) ? (x = 6) : x; // ZAMIANA KOLORU NA ZOLTY JESLI ZOSTAL WYLOSOWANY NIEBESKI (SLABO WIDOCZNY)
	_itoa(x, color, 16);
	comand += color;

	system(comand.c_str());

	return;
}

int b_size(void)
{
	int size;

	cout << "Podaj rozmiar tablicy (od 2 do 9 ): ";
	do
	{
		/*
		if (!_kbhit())
		{
		cin.clear();
		cin.ignore();
		}
		*/
		cin >> size;
		system("cls");
		if (!(size > 1 && size < 10)) cout << "Podano zly wymiar planszy... podaj ponownie: ";
	} while (!(size > 1 && size < 10));

	system("cls");
	return size;
}


bool getdelay(void)
{
	char sign;

	cout << "Dynamiczne rysowanie ;) (y/n): ";
	sign = _getch();
	if (sign == 'y' || sign == 'Y')
	{
		system("cls");
		return true;
	}
	else
	{
		system("cls");
		return false;
	}
}


void init(vector < vector<char> > &plansza)
{
	for (int k = 0; k < plansza.size(); k++)
	{
		vector<char> temp(plansza.size());

		for (int w = 0; w < plansza.size(); w++)
		{
			temp[w] = ' ';
		}
		plansza[k] = temp;
	}
	return;
}




void printb(const vector < vector<char> > &plansza, char tura, bool delay)
{
	int t;
	if (plansza.size() >= 13) t = 0;
	else t = 100 - 10 * plansza.size();

	system("cls");

	for (int w = 0; w < plansza.size(); w++)
	{
		cout << "   ";

		for (int k = 0; k < plansza.size(); k++)
		{
			if (plansza[w][k] == ' ')
			{

				SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);

				cout << '\b' << static_cast <char>(w + 'A') << k + 1;

				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);

			}
			else
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << plansza[w][k];
				SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
			}
			if (k < plansza.size() - 1)
			{
				cout << "   ";
				cout << '|';
				cout << "   ";
				if (delay) Sleep(t);
			}
		}
		if (w == 1)
		{
			cout << "\t\t" << "Tura gracza: ";
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << tura;
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
		cout << endl;

		for (int i = 0; i < plansza.size(); i++)
		{
			if (w < plansza.size() - 1)
			{
				cout << "--------";
				if (delay) Sleep(t);
			}
		}

		cout << endl;
	}
	return;
}



void getcoor(int &x, int &y, int rozmiar)
{
	int temp_x, temp_y;

	do
	{
		cout << endl << endl << "Podaj nr wiersza: ";
		temp_y = _getch();
		cout << static_cast <char>(temp_y) << endl;
		if (temp_y >= 'a' && temp_y <= 'z') temp_y -= 32;
		temp_y -= 'A';
		y = temp_y;


		cout << "Podaj nr kolumny: ";
		temp_x = _getch();
		temp_x -= '0';
		x = temp_x - 1;
		cout << x + 1 << endl;

		if (!((y >= 0 && y < rozmiar) && (x >= 0 && x < rozmiar))) cout << endl << "Zle dane !";

	} while (!((y >= 0 && y < rozmiar) && (x >= 0 && x < rozmiar)));

	return;
}


char enter(vector < vector<char> > &plansza, int &x, int &y)
{
	static char tura = 'O';

	if (plansza[y][x] == 'O' || plansza[y][x] == 'X')
	{
		cout << "\07";
		return tura;
	}
	else plansza[y][x] = tura;

	if (tura == 'O') tura = 'X';
	else tura = 'O';

	return tura;
}


char win(const vector < vector<char> > &plansza, char &tura)
{
	bool equ = false;
	int przekatnalp = 0;
	int przekatnapl = 0;
	int horizontal = 0;
	int vertical = 0;

	for (int i = 0; i < plansza.size(); i++)	// SPRAWDZANIE PRZEKATNEJ L-P
	{
		if ((plansza[i][i] == 'X' && tura == 'O') || (plansza[i][i] == 'O' && tura == 'X')) przekatnalp++;
	}

	int temp = plansza.size() - 1;

	for (int i = 0; i < plansza.size(); i++)	// SPRAWDZANIE PRZEKATNEJ P-L
	{
		if ((plansza[temp][i] == 'X' && tura == 'O') || (plansza[temp][i] == 'O' && tura == 'X')) przekatnapl++;
		temp--;
	}


	for (int w = 0; w < plansza.size(); w++)	// SPRAWDZANIE WIERSZY (POZIOMO)
	{
		if (horizontal == plansza.size()) break;
		else horizontal = 0;

		for (int k = 0; k < plansza.size(); k++)
		{
			if ((plansza[w][k] == 'X' && tura == 'O') || (plansza[w][k] == 'O' && tura == 'X')) horizontal++;
		}
	}


	for (int k = 0; k < plansza.size(); k++)	// SPRAWDZANIE KOLUMN (PIONOWO)
	{
		if (vertical == plansza.size()) break;
		else vertical = 0;

		for (int w = 0; w < plansza.size(); w++)
		{
			if ((plansza[w][k] == 'X' && tura == 'O') || (plansza[w][k] == 'O' && tura == 'X')) vertical++;
		}
	}

	if (przekatnalp == plansza.size() || przekatnapl == plansza.size()
		|| horizontal == plansza.size() || vertical == plansza.size()) equ = true;

	if (equ && tura == 'O') return 'X';
	else if (equ && tura == 'X') return 'O';
	else return ' ';
}


void printw(char who, bool &end, const vector < vector<char> > &plansza)
{


	if (who == 'O' || who == 'X')
	{
		const int DELAY = 300;
		string napis = "WYGRYWA";

		cout << '\07';

		for (int i = 0; i < napis.size(); i++)
		{
			printb(plansza, '-', false);
			cout << endl << endl << endl << "\t\t\t\t";
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			for (int j = 0; j <= i; j++) cout << endl << "\t\t\t\t" << napis[j];

			Sleep(DELAY - 100);
			if (i == napis.size() - 1) break;
			system("cls");
			Sleep(DELAY - 100);
		}

		Sleep(DELAY);
		cout << endl << endl << "\t\t\t\t" << who;
		Sleep(DELAY);

		end = true;
	}
	else return;

	return;
}