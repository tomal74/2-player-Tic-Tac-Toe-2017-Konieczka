/*
	Tomasz Konieczka 2017
	Aisseratti Systems LTD
	
	Tic Tac Toe Game
*/

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




int main()
{
	
	
	rand_color();
	

	bool delay = getdelay();
	int rozmiar = b_size();
	
	int k, w;
	char tura = 'O';

	vector <vector<char> > board(rozmiar);
	
	init(board);
	
	bool wygrana = false;

	while (!wygrana)
	{
		printb(board, tura, delay);
		getcoor(k, w, rozmiar);
		tura = enter(board, k, w);
		int w_win = win(board, tura);
		if(w_win == 'O' || w_win == 'X') printw(w_win, wygrana, board);
	}


	cout << endl << endl << endl << endl;
	system("pause");
	return 0;
}