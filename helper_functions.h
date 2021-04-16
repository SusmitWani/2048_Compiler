#ifndef _HELPER_FUNCTIONS_
#define _HELPER_FUNCTIONS_

#include <bits/stdc++.h>
using namespace std;
extern void red();
extern void blue();
extern void yellow();
extern void green();
extern void reset();
extern void makezero(int g[16]);
extern void printGrid(int g[16]);       //done
extern void printVars (map <char*, pair<int,int>> &m);
extern int printError (int g[], map <char*, pair<int,int>> &m);
extern void check_map(int g[], map <char*, pair<int,int>> &m);
extern void insertRandom(int g[16]);    //done
extern int return_value (int g[], int x, int y);
extern void assign_val (int g[], map<char*, pair <int, int>> &m, int val, int x, int y);
extern void assign_var (int g[], map<char*, pair <int, int>> &m, char* id, int x, int y);
extern int sumCells(int g[16]);         //done
extern void start(int g[16]);           //done
extern int shift_up_all(int g[16], map <char*, pair<int,int>> &m);
extern int move_up(int g[16], map <char*, pair<int,int>> &m, int op);
extern int shift_down_all(int g[16], map <char*, pair<int,int>> &m);
extern int move_down(int g[16], map <char*, pair<int,int>> &m, int op);
extern int shift_right_all(int g[16], map <char*, pair<int,int>> &m);
extern int move_right(int g[16], map <char*, pair<int,int>> &m, int op);
extern int shift_left_all(int g[16], map <char*, pair<int,int>> &m);
extern int move_left(int g[16], map <char*, pair<int,int>> &m, int op);
extern void move(int g[16], map <char*, pair<int,int>> &m, int op, int dir);
#endif
