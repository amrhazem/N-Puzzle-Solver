#pragma once
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <ctime>
#include <set>
#include <string>
#include <string.h> 
#include <SFML/Graphics.hpp>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace sf;
class solve_NPuzzle
{
public:
	int lvl, wgt, props, n,answer;
	priority_queue<pair<pair<int, int>, int**>> PQ;
	set<string> freqT; 
	vector<int**> vec;
	int** Current, **check1, **check2, **check3, **check4 , **GOAL;
	unordered_map<string , int**> map;
	/////////////////////BONUS//////////////////////
	queue<pair<int, int**>> BQ;
	void propBFS(int**, int);
	void swapup(int**, int);
	void swapdowen(int**, int);
	void swapleft(int**, int);
	void swapright(int**, int);
	int AStarBFS();
	///////////////////////////////////////////////
	void fill();
	int Hamming(int**);
	void NumberOfSwaps(int**);
	void copyarray(int** New, int** Old);
	void propHam(int**,int);
	void propMan(int**, int);
	string hashing(int**);
	bool overlap(int**);
	int MannHelper(int**, int, int);
	int Manhattan(int**);
	int AStarHam();
	int AStarMan();
	bool solvable(int**);
	void backtrack();
	void displayBK();
	solve_NPuzzle();
	~solve_NPuzzle();
	///////////////GUI FNS/////////////////////
	Font font;
	void GUI();
	void drawTitle(RenderWindow& window);
	void drawBox(RenderWindow& window, int, int, int, int, int);
	void drawButtons(RenderWindow& window, bool, bool);
	void drawNumbers(RenderWindow& window, int lvl, int, int, int, int);
	void drawBackGround(RenderWindow& window);
	void drawLevel(RenderWindow& window, int level);
};
