#ifndef TK_OX
#define TK_OX

#include <iostream>
#include <vector>

using namespace std;

void rand_color(void);
int b_size(void);
bool getdelay(void);
void init(vector < vector<char> > &plansza);
void printb(const vector < vector<char> > &plansza, char tura, bool delay = false);
void getcoor(int &x, int &y, int rozmiar);
char enter(vector < vector<char> > &plansza, int &x, int &y);
char win(const vector < vector<char> > &plansza, char &tura);
void printw(char who, bool &end, const vector < vector<char> > &plansza);


#endif