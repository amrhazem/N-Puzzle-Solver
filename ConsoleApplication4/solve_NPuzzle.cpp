#include "solve_NPuzzle.h"


solve_NPuzzle::solve_NPuzzle()
{
	lvl = 0;
	wgt = 0;
	props = 0;
	answer = 0;
	
	
	fill();//O(Nsqr)
}

void solve_NPuzzle::fill()
{
	ifstream file;
	file.open("8 Puzzle (1).txt", ios::in);
	file >> n; //reading size of matrix
	Current = new int* [n];
	for (int i = 0; i < n; i++)
		Current[i] = new int[n];

	GOAL = new int* [n];
	for (int i = 0; i < n; i++)
		GOAL[i] = new int[n];
	int k = 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == n - 1 && j == n - 1)
			{
				k = 0;
			}
			GOAL[i][j] = k;
			k++;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			file >> Current[i][j];  //reading matrix
		}
	}
	BQ.push(make_pair(0, Current));  //Bonus BFS
}

int solve_NPuzzle::Hamming(int** HAMM) {
	int Ham = 0;
	int H = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == n - 1 && j == n - 1)
				break;
			if (HAMM[i][j] != H)
				Ham++;
			H++;
		}
	return Ham;
}

int solve_NPuzzle::MannHelper(int** parent, int x1, int y1)  //O(N^2)
{
	int counter = 1;
	int x2 = -1, y2 = -1;
	bool br = false;
	for (int i = 0; i < n; i++)
	{
		if (br == true)
			break;
		for (int j = 0; j < n; j++)
		{
			if (parent[x1][y1] != counter)
			{
				counter++;
				continue;
			}
			else
			{
				x2 = i;
				y2 = j;
				br = true;
				break;
			}
			if (counter == n - 1) {
				counter = 0;
			}
			else {
				counter++;
			}
		}
	}
	int ManH = 0;
	ManH = abs(x1 - x2) + abs(y1 - y2);
	return ManH;
}

int solve_NPuzzle::Manhattan(int** parent) 
{
	int c = 1;
	int m = 0;
	int x2, y2;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((parent[i][j] == c) || (parent[i][j] == 0)) {
				c++;
				continue;
			}
			else
			{
				x2 = (parent[i][j] - 1) / n;
				y2 = (parent[i][j] - 1) % n;
				m+= abs(i - x2) + abs(j - y2);
			}
			c++;
		}
	}

	return m;
}

void solve_NPuzzle::copyarray(int** New, int** Old)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			New[i][j] = Old[i][j];
	}
}


void solve_NPuzzle::propHam(int** Parent, int parentLevel)
{
	check1 = new int* [n];
	check2 = new int* [n];
	check3 = new int* [n];
	check4 = new int* [n];
	for (int i = 0; i < n; i++) {
		check1[i] = new int[n];
		check2[i] = new int[n];
		check3[i] = new int[n];
		check4[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			check1[i][j] = Parent[i][j];
			check2[i][j] = Parent[i][j];
			check3[i][j] = Parent[i][j];
			check4[i][j] = Parent[i][j];
		}
	}

	int** tmparr = new  int* [n];
	for (int i = 0; i < n; i++)
		tmparr[i] = new int[n];
	bool c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	copyarray(tmparr, Parent);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Parent[i][j] == 0 && i == 0 && j == 0 && props == 2)
			{

				swap(check1[i][j], check1[i][j + 1]);
				c1 = 1;
				swap(check2[i][j], check2[i + 1][j]);
				c2 = 1;
				break;

			}
			if (Parent[i][j] == 0 && i == n - 1 && j == n - 1 && props == 2)
			{
				swap(check1[i][j], check1[i - 1][j]);
				c1 = 1;
				swap(check2[i][j], check2[i][j - 1]);
				c2 = 1;
				break;

			}
			if (Parent[i][j] == 0 && i == 0 && j == n - 1 && props == 2)
			{
				swap(check1[i][j], check1[i][j - 1]);
				c1 = 1;
				swap(check2[i][j], check2[i + 1][j]);
				c2 = 1;
				break;

			}
			if (Parent[i][j] == 0 && i == n - 1 && j == 0 && props == 2)
			{
				swap(check1[i][j], check1[i - 1][j]);
				c1 = 1;
				swap(check2[i][j], check2[i][j + 1]);
				c2 = 1;
				break;

			}
			if (Parent[i][j] == 0 && i == 0 && props == 3)
			{
				swap(check1[i][j], check1[i][j - 1]);
				c1 = 1;

				swap(check2[i][j], check2[i][j + 1]);
				c2 = 1;
				swap(check3[i][j], check3[i + 1][j]);
				c3 = 1;
				break;

			}
			if (Parent[i][j] == 0 && j == 0 && props == 3)
			{
				swap(check1[i][j], check1[i + 1][j]);
				c1 = 1;

				swap(check2[i][j], check2[i - 1][j]);
				c2 = 1;


				swap(check3[i][j], check3[i][j + 1]);
				c3 = 1;

				break;

			}
			if (Parent[i][j] == 0 && j == n - 1 && props == 3)
			{
				swap(check1[i][j], check1[i + 1][j]);
				c1 = 1;


				swap(check2[i][j], check2[i - 1][j]);
				c2 = 1;


				swap(check3[i][j], check3[i][j - 1]);
				c3 = 1;

				break;

			}
			if (Parent[i][j] == 0 && i == n - 1 && props == 3)
			{
				swap(check1[i][j], check1[i][j - 1]);
				c1 = 1;


				swap(check2[i][j], check2[i][j + 1]);
				c2 = 1;

				swap(check3[i][j], check3[i - 1][j]);

				c3 = 1;
				break;

			}
			if (Parent[i][j] == 0 && props == 4)
			{
				swap(check1[i][j], check1[i][j - 1]);

				c1 = 1;

				swap(check2[i][j], check2[i][j + 1]);

				c2 = 1;


				swap(check3[i][j], check3[i - 1][j]);

				c3 = 1;
				swap(check4[i][j], check4[i + 1][j]);
				c4 = 1;
				break;

			}
		}
	}
	if (c1) {
		if (!overlap(check1)) {
			PQ.push(make_pair(make_pair(-1 * (Hamming(check1) + parentLevel + 1), parentLevel + 1), check1));
			map[hashing(check1)] = tmparr;
		}
	}
	if (c2) {
		if (!overlap(check2)) {
			PQ.push(make_pair(make_pair(-1 * (Hamming(check2) + parentLevel + 1), parentLevel + 1), check2));
			map[hashing(check2)] = tmparr;
		}
	}
	if (c3) {
		if (!overlap(check3)) {
			PQ.push(make_pair(make_pair(-1 * (Hamming(check3) + parentLevel + 1), parentLevel + 1), check3));
			map[hashing(check3)] = tmparr;
		}
	}
	if (c4) {
		if (!overlap(check4)) {
			PQ.push(make_pair(make_pair(-1 * (Hamming(check4) + parentLevel + 1), parentLevel + 1), check4));
			map[hashing(check4)] = tmparr;
		}
	}

}

void solve_NPuzzle::propMan(int** Parent, int parentLevel)
{
	check1 = new int* [n];
	check2 = new int* [n];
	check3 = new int* [n];
	check4 = new int* [n];
	for (int i = 0; i < n; i++) {
		check1[i] = new int[n];
		check2[i] = new int[n];
		check3[i] = new int[n];
		check4[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			check1[i][j] = Parent[i][j];
			check2[i][j] = Parent[i][j];
			check3[i][j] = Parent[i][j];
			check4[i][j] = Parent[i][j];
		}
	}

	int** tmparr = new  int* [n];
	for (int i = 0; i < n; i++)
		tmparr[i] = new int[n];
	bool c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	copyarray(tmparr, Parent);
	//int parentLevel = PQ.top().first.second;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Parent[i][j] == 0 && i == 0 && j == 0 && props == 2)
			{

				swap(check1[i][j], check1[i][j + 1]); //O(1)
				c1 = 1;
				swap(check2[i][j], check2[i + 1][j]);
				c2 = 1;
				break;
			}
			if (Parent[i][j] == 0 && i == n - 1 && j == n - 1 && props == 2)
			{
				swap(check1[i][j], check1[i - 1][j]);
				c1 = 1;
				swap(check2[i][j], check2[i][j - 1]);
				c2 = 1;
				break;
			}
			if (Parent[i][j] == 0 && i == 0 && j == n - 1 && props == 2)
			{
				swap(check1[i][j], check1[i][j - 1]);
				c1 = 1;
				swap(check2[i][j], check2[i + 1][j]);
				c2 = 1;
				break;

			}
			if (Parent[i][j] == 0 && i == n - 1 && j == 0 && props == 2)
			{
				swap(check1[i][j], check1[i - 1][j]);
				c1 = 1;
				swap(check2[i][j], check2[i][j + 1]);
				c2 = 1;
				break;

			}
			if (Parent[i][j] == 0 && i == 0 && props == 3)
			{
				swap(check1[i][j], check1[i][j - 1]);
				c1 = 1;

				swap(check2[i][j], check2[i][j + 1]);
				c2 = 1;
				swap(check3[i][j], check3[i + 1][j]);
				c3 = 1;
				break;

			}
			if (Parent[i][j] == 0 && j == 0 && props == 3)
			{
				swap(check1[i][j], check1[i + 1][j]);
				c1 = 1;

				swap(check2[i][j], check2[i - 1][j]);
				c2 = 1;


				swap(check3[i][j], check3[i][j + 1]);
				c3 = 1;

				break;

			}
			if (Parent[i][j] == 0 && j == n - 1 && props == 3)
			{
				swap(check1[i][j], check1[i + 1][j]);
				c1 = 1;


				swap(check2[i][j], check2[i - 1][j]);
				c2 = 1;


				swap(check3[i][j], check3[i][j - 1]);
				c3 = 1;
				break;


			}
			if (Parent[i][j] == 0 && i == n - 1 && props == 3)
			{
				swap(check1[i][j], check1[i][j - 1]);
				c1 = 1;


				swap(check2[i][j], check2[i][j + 1]);
				c2 = 1;

				swap(check3[i][j], check3[i - 1][j]);

				c3 = 1;
				break;

			}
			if (Parent[i][j] == 0 && props == 4)
			{
				swap(check1[i][j], check1[i][j - 1]);

				c1 = 1;

				swap(check2[i][j], check2[i][j + 1]);

				c2 = 1;


				swap(check3[i][j], check3[i - 1][j]);

				c3 = 1;
				swap(check4[i][j], check4[i + 1][j]);
				c4 = 1;
				break;

				//cout << "lvl of children is:" << parentLevel + 1 << endl;
			}
		}
	}
	if (c1) {
		PQ.push(make_pair(make_pair(-1 * (Manhattan(check1) + parentLevel + 1), parentLevel + 1), check1));
		map[hashing(check1)] = tmparr;
	}
	if (c2) {
		PQ.push(make_pair(make_pair(-1 * (Manhattan(check2) + parentLevel + 1), parentLevel + 1), check2));
		map[hashing(check2)] = tmparr;
	}
	if (c3) {
		PQ.push(make_pair(make_pair(-1 * (Manhattan(check3) + parentLevel + 1), parentLevel + 1), check3));
		map[hashing(check3)] = tmparr;
	}
	if (c4) {
		PQ.push(make_pair(make_pair(-1 * (Manhattan(check4) + parentLevel + 1), parentLevel + 1), check4));
		map[hashing(check4)] = tmparr;
	}

} //O(S^2)


string solve_NPuzzle::hashing(int** mat)
{
	string hash;
	string temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp = to_string(mat[i][j]);
			hash += temp;
		}
	}
	return hash;
}

bool solve_NPuzzle::overlap(int** mat1)
{
	string tmp = hashing(mat1);
	if (freqT.find(tmp) == freqT.end()) {
		freqT.insert(tmp);
		return false;
	}
	else {
		return true;
	}
}

void solve_NPuzzle::NumberOfSwaps(int** PLACE)
{
	bool br = true;
	for (int i = 0; i < n; i++)
	{
		if (!br)
			break;
		for (int j = 0; j < n; j++)
		{
			if ((PLACE[i][j] == 0 && i == 0 && j == 0) || (PLACE[i][j] == 0 && i == n - 1 && j == n - 1) || (PLACE[i][j] == 0 && i == n - 1 && j == 0) || (PLACE[i][j] == 0 && i == 0 && j == n - 1))
			{
				props = 2;
				br = false;
				break;
			}
			else if ((PLACE[i][j] == 0 && j == 0))
			{
				props = 3;
				br = false;
				break;
			}
			else if ((PLACE[i][j] == 0 && i == 0) || (PLACE[i][j] == 0 && j == 0) || (PLACE[i][j] == 0 && j == n - 1) || (PLACE[i][j] == 0 && i == n - 1))
			{
				props = 3;
				br = false;
				break;
			}
			else if (PLACE[i][j] == 0)
			{
				props = 4;
				br = false;
				break;
			}
		}
	}
}

int solve_NPuzzle::AStarHam()
{
	int parentLevel = 0;
	NumberOfSwaps(Current); //(N^2)
	propHam(Current, 0);	//(S^2)
	freqT.insert(hashing(Current)); //(N^2)
	int** Parent = new int* [n];
	for (int i = 0; i < n; i++)
		Parent[i] = new int[n];
	copyarray(Parent, Current);
	int it = 0;
	while (true)
	{
		if (Hamming(Parent) == 0) //(N^2)
		{
			answer = parentLevel;
			return parentLevel;
		}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					Parent[i][j] = PQ.top().second[i][j];
				}
			}//(N^2)
			parentLevel = PQ.top().first.second;
			PQ.pop();
			NumberOfSwaps(Parent); //(N^2)
			propHam(Parent, parentLevel); //(S^2)
			it++;
	}
}
int solve_NPuzzle::AStarMan()
{
	int parentLevel = 0;
	NumberOfSwaps(Current);
	propMan(Current, 0);
	freqT.insert(hashing(Current));
	int** Parent = new int* [n];
	for (int i = 0; i < n; i++)
		Parent[i] = new int[n];
	copyarray(Parent, Current);
	int it = 0;
	while (true)
	{

		if (Manhattan(Parent) == 0)
		{
			answer = parentLevel;
			return parentLevel;
		}
		if (!overlap(PQ.top().second)) {
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					Parent[i][j] = PQ.top().second[i][j];
				}
			}
			parentLevel = PQ.top().first.second;
			PQ.pop();
			NumberOfSwaps(Parent);
			propMan(Parent, parentLevel);
		}
		else {
			PQ.pop();
		}
		it++;
	}
}

bool solve_NPuzzle::solvable(int** nw) {
	int* sol = new int[n * n];
	int k = 0;
	int zeroPos;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sol[k] = nw[i][j];
			k++;
			if (nw[i][j] == 0)
			{
				zeroPos = (n - i);
			}
		}
	}
	int invCount = 0;
	for (int i = 0; i < (n * n) - 1; i++)
	{
		for (int j = i + 1; j < (n * n); j++)
		{
			if (sol[i] != 0 && sol[i] > sol[j] && sol[j] != 0)
			{
				invCount++;
			}
		}
	}
	if (n % 2 == 0)  //even
	{
		if (invCount % 2 == 0)
		{
			if (zeroPos % 2 == 0)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			if (zeroPos % 2 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else           //odd
	{
		if (invCount % 2 == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return true;
}

void solve_NPuzzle::backtrack() {
	vec.push_back(GOAL);
	string currentChild = hashing(GOAL);
	for (int i = 0; i < answer; i++) {
		vec.push_back(map[currentChild]);
		currentChild = hashing(map[currentChild]);
	}
}
void solve_NPuzzle::displayBK() {
	backtrack();
	int  counter = 0;
	for (int k = vec.size() - 1; k >= 0; k--) {
		cout << "#" << counter << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << vec[k][i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		counter++;
	}
}
solve_NPuzzle::~solve_NPuzzle()
{
	for (int i = 0; i < n; i++)
	{
		Current[i] = NULL;
		delete[] Current[i];
	}
	Current = NULL;
	delete[] Current;
	for (int i = 0; i < n; i++)
	{
		check1[i] = NULL;
		delete[] check1[i];
	}
	check1 = NULL;
	delete[] check1;
	for (int i = 0; i < n; i++)
	{
		check2[i] = NULL;
		delete[] check2[i];
	}
	check2 = NULL;
	delete[] check2;
	for (int i = 0; i < n; i++)
	{
		check3[i] = NULL;
		delete[] check3[i];
	}
	check3 = NULL;
	delete[] check3;
	for (int i = 0; i < n; i++)
	{
		check4[i] = NULL;
		delete[] check4[i];
	}
	check4 = NULL;
	delete[] check4;

}


//BONUS BFS Functions

void solve_NPuzzle::propBFS(int** parent, int parentlvl) {
	check1 = new int* [n];
	for (int i = 0; i < n; i++)
		check1[i] = new int[n];
	check2 = new int* [n];
	for (int i = 0; i < n; i++)
		check2[i] = new int[n];
	check3 = new int* [n];
	for (int i = 0; i < n; i++)
		check3[i] = new int[n];
	check4 = new int* [n];
	for (int i = 0; i < n; i++)
		check4[i] = new int[n];
	swapup(parent, parentlvl);
	swapdowen(parent, parentlvl);
	swapleft(parent, parentlvl);
	swapright(parent, parentlvl);

}

void  solve_NPuzzle::swapup(int** parent, int parentlvl) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			check1[i][j] = parent[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (parent[i][j] == 0 && i != 0) {
				swap(check1[i][j], check1[i - 1][j]);
				if (!overlap(check1))
				{
					BQ.push(make_pair(parentlvl + 1, check1));
				}
			}
		}
	}
}
void  solve_NPuzzle::swapdowen(int** parent, int parentlvl) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			check2[i][j] = parent[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (parent[i][j] == 0 && i != n - 1)
			{
				swap(check2[i][j], check2[i + 1][j]);
				if (!overlap(check2))
				{
					BQ.push(make_pair(parentlvl + 1, check2));
				}
			}
		}
	}
}
void  solve_NPuzzle::swapleft(int** parent, int parentlvl) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			check4[i][j] = parent[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (parent[i][j] == 0 && j != 0)
			{
				swap(check4[i][j], check4[i][j - 1]);
				if (!overlap(check4))
				{
					BQ.push(make_pair(parentlvl + 1, check4));
				}
			}
		}
	}
}
void  solve_NPuzzle::swapright(int** parent, int parentlvl) {
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			check3[i][j] = parent[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (parent[i][j] == 0 && j != n - 1)
			{
				swap(check3[i][j], check3[i][j + 1]);
				if (!overlap(check3))
				{
					BQ.push(make_pair(parentlvl + 1, check3));
				}
			}
		}
	}
}
int solve_NPuzzle::AStarBFS() {
	int parentLevel, it = 0;
	NumberOfSwaps(Current);
	propBFS(Current, 0);
	freqT.insert(hashing(Current));
	int** Parent = new int* [n];
	for (int i = 0; i < n; i++)
		Parent[i] = new int[n];
	while (!BQ.empty())
	{
		cout << "Iterations----------->" << it << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				Parent[i][j] = BQ.front().second[i][j];
				cout << BQ.front().second[i][j] << " ";
			}
			cout << endl;
		}
		parentLevel = BQ.front().first;
		if (Hamming(Parent) == 0)
		{
			return BQ.front().first;
		}
		BQ.pop();
		NumberOfSwaps(Parent);
		propBFS(Parent, parentLevel);
		it++;
	}
	return 0;
}

///////////////////GUI FNS//////////////

void solve_NPuzzle::GUI()
{
	int posx, posy, shift, size;
	int posx1, posy1, shift1, l, w;
	font.loadFromFile("lala.ttf");



	int lvl = vec.size() - 1;
	int level = 0;
	RenderWindow NPuzzle(VideoMode(1000, 950), "8-Puzzle Solver", Style::Fullscreen | Style::Close);


	while (NPuzzle.isOpen())
	{
		sf::Event evn;
		bool next = false, previ = false, choice = true;
		while (NPuzzle.pollEvent(evn))
		{
			if (evn.type == sf::Event::Closed)
			{
				NPuzzle.close();
			}
			else if (evn.type == evn.KeyPressed)
			{
				if (evn.key.code == sf::Keyboard::Escape) {
					NPuzzle.close();
				}
				else if (evn.key.code == Keyboard::Right) {
					next = true;
					previ = false;

					drawButtons(NPuzzle, next, previ);

				}
				else if (evn.key.code == Keyboard::Left) {
					previ = true;
					next = false;

					drawButtons(NPuzzle, next, previ);

				}
			}

		}
		NPuzzle.clear();
		drawBackGround(NPuzzle);
		if (next == true && lvl>=1)
		{

			previ = false;
			lvl--;
			level++;
			if (n == 10)
			{
				posx = 510;
				posy = 115;
				size = 70;
				shift = 90;
				posx1 = 490;
				posy1 = 130;
				shift1 = 90;
				l = 80;
				w = 80;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);
			}
			else if (n == 3)
			{
				posx = 670;
				posy = 220;
				size = 100;
				shift = 210;
				posx1 = 600;
				posy1 = 200;
				shift1 = 210;
				l = 200;
				w = 200;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}
			else if (n == 4)
			{
				posx = 570;
				posy = 150;
				size = 100;
				shift = 210;
				posx1 = 500;
				posy1 = 130;
				shift1 = 210;
				l = 200;
				w = 200;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}
			else if (n == 5)
			{
				posx = 550;
				posy = 130;
				size = 100;
				shift = 160;
				posx1 = 500;
				posy1 = 130;
				shift1 = 160;
				l = 150;
				w = 150;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);
			}
		}

		else if (previ == true)
		{
			next = false;
			lvl++;
			level--;
			if (n == 10)
			{
				posx = 510;
				posy = 115;
				size = 70;
				shift = 90;
				posx1 = 490;
				posy1 = 130;
				shift1 = 90;
				l = 80;
				w = 80;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}
			else if (n == 3)
			{
				posx = 670;
				posy = 220;
				size = 100;
				shift = 210;
				posx1 = 600;
				posy1 = 200;
				shift1 = 210;
				l = 200;
				w = 200;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}
			else if (n == 4)
			{
				posx = 570;
				posy = 150;
				size = 100;
				shift = 210;
				posx1 = 500;
				posy1 = 130;
				shift1 = 210;
				l = 200;
				w = 200;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}
			else if (n == 5)
			{
				posx = 550;
				posy = 130;
				size = 100;
				shift = 160;
				posx1 = 500;
				posy1 = 130;
				shift1 = 160;
				l = 150;
				w = 150;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}
		}
		else
		{
			if (n == 10)
			{
				posx = 510;
				posy = 115;
				size = 70;
				shift = 90;
				posx1 = 490;
				posy1 = 130;
				shift1 = 90;
				l = 80;
				w = 80;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}
			else if (n == 3)
			{
				posx = 670;
				posy = 220;
				size = 100;
				shift = 210;
				posx1 = 600;
				posy1 = 200;
				shift1 = 210;
				l = 200;
				w = 200;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}
			else if (n == 4)
			{
				posx = 570;
				posy = 150;
				size = 100;
				shift = 210;
				posx1 = 500;
				posy1 = 130;
				shift1 = 210;
				l = 200;
				w = 200;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}
			else if (n == 5)
			{
				posx = 550;
				posy = 130;
				size = 100;
				shift = 160;
				posx1 = 500;
				posy1 = 130;
				shift1 = 160;
				l = 150;
				w = 150;
				drawNumbers(NPuzzle, lvl, posx, posy, shift, size);
				drawBox(NPuzzle, posx1, posy1, shift1, l, w);

			}

		}
		drawTitle(NPuzzle);
		drawButtons(NPuzzle, next, previ);
		drawLevel(NPuzzle, level);
		NPuzzle.display();

	}



}

void solve_NPuzzle::drawTitle(RenderWindow& window) {
	font.loadFromFile("lala.ttf");
	sf::Text name;
	name.setFont(font);
	name.setString("N-Puzzle Solver");
	name.setCharacterSize(70);
	name.setFillColor(sf::Color::Cyan);
	name.setPosition(660, 20);
	window.draw(name);

}

void solve_NPuzzle::drawBox(RenderWindow& window, int posx, int posy, int shift, int l, int w)
{
	int initialization = posx;
	sf::RectangleShape box(sf::Vector2f(l, w));									// 10 x 10
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			box.setPosition(posx, posy);
			box.setFillColor(sf::Color::Transparent);
			box.setOutlineThickness(3);
			box.setOutlineColor(Color::Cyan);
			window.draw(box);
			posx = posx + shift;
		}
		posy = posy + shift;
		posx = initialization;
	}

}

void solve_NPuzzle::drawButtons(RenderWindow& window, bool next, bool prev) {
	font.loadFromFile("lala.ttf");
	sf::Text previ;
	previ.setFont(font);
	previ.setString("Previous");
	previ.setPosition(115, 950);
	previ.setCharacterSize(45);

	sf::RectangleShape box(sf::Vector2f(230, 70));
	box.setPosition(100, 950);
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineThickness(3);
	sf::Text nextt;
	nextt.setFont(font);
	nextt.setString("Next");
	nextt.setCharacterSize(50);
	nextt.setPosition(1600, 945);

	sf::RectangleShape boxx(sf::Vector2f(230, 70));
	boxx.setPosition(1550, 950);
	boxx.setFillColor(sf::Color::Transparent);
	boxx.setOutlineThickness(3);
	if (next == 0 && prev == 1) {
		previ.setFillColor(sf::Color::Red);
		box.setOutlineColor(Color::Red);
	}

	else {
		previ.setFillColor(sf::Color::Cyan);
		box.setOutlineColor(Color::Cyan);
	}
	if (next == 1 && prev == 0)
	{
		nextt.setFillColor(Color::Red);
		boxx.setOutlineColor(Color::Red);
	}
	else {
		nextt.setFillColor(Color::Cyan);
		boxx.setOutlineColor(Color::Cyan);
	}

	window.draw(previ);
	window.draw(nextt);
	window.draw(box);
	window.draw(boxx);


}

void solve_NPuzzle::drawNumbers(RenderWindow& window, int lvl, int posx, int posy, int shift, int size) {
	
	Text** myText = new Text*[n];
	for (int i = 0; i < n; i++)
		myText[i] = new Text[n];
	stringstream** ss = new stringstream*[n];
	for (int i = 0; i < n; i++)
		ss[i] = new stringstream[n];
	int initilaization = posx;// 10 x 10 !!!
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			myText[i][j].setPosition(posx, posy);
			posx = posx + shift;
			ss[i][j] << vec[lvl][i][j];
			myText[i][j].setFont(font);
			myText[i][j].setCharacterSize(size);
			myText[i][j].setFillColor(sf::Color::Cyan);
			myText[i][j].setString(ss[i][j].str().c_str());
			window.draw(myText[i][j]);
		}
		posy = posy + shift;
		posx = initilaization;
	}
}

void solve_NPuzzle::drawBackGround(RenderWindow& window) {
	sf::RectangleShape photo(sf::Vector2f(1920.0f, 1080.0f));
	photo.setPosition(0, 0);
	sf::Texture Wallpaper;
	Wallpaper.loadFromFile("image.jpg");
	photo.setTexture(&Wallpaper);
	window.draw(photo);
}

void solve_NPuzzle::drawLevel(RenderWindow& window, int level) {
	font.loadFromFile("lala.ttf");
	sf::Text name;
	name.setFont(font);
	name.setString("Level : ");
	name.setCharacterSize(50);
	name.setFillColor(sf::Color::Cyan);
	name.setPosition(20, 100);
	window.draw(name);
	Text myText;
	stringstream ss;

	myText.setPosition(200, 100);
	ss << level;
	myText.setFont(font);
	myText.setCharacterSize(50);
	myText.setFillColor(sf::Color::Cyan);
	myText.setString(ss.str().c_str());
	window.draw(myText);
}