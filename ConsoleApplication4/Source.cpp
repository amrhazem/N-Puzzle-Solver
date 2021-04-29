#include <iostream>
#include "solve_NPuzzle.h"
using namespace std;

int main() {
	solve_NPuzzle S;
	if (!S.solvable(S.Current))
	{
		cout << "UnSolvable\n";
		return 0;
	}
	int choice , x;
	cout << "1-Hamming\n2-Manhattan\n3-BFS\n4-GUI\n";
	cin >> choice;
  	clock_t start = clock();
	switch (choice)
	{
	case 1:
		x = S.AStarHam();
		if(S.n == 3)
		S.displayBK();
		cout << "Solvable\nNumber of moves: " << x << endl;
		break;
	case 2:
		x = S.AStarMan();
		cout << "Solvable\nNumber of moves: " << x << endl;
		break;
	case 3:
		x = S.AStarBFS();
		cout << "Solvable\nNumber of moves: " << x << endl;
		break;
	case 4:
		x = S.AStarHam();
		S.backtrack();
		if (S.n == 3)
			S.GUI();
		cout << "Solvable\nNumber of moves: " << x << endl;
		break;
	}
	clock_t end = clock();	
	double duration = end - start / (CLOCKS_PER_SEC/1000);
	double duration2 = duration / 1000;
	cout << duration << " milliseconds" << endl;
	cout << duration2 << " seconds" << endl;

	return 0;
}