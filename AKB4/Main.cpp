#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void loadFile();
void print(vector<int>);
void sort(bool);
int sum(vector<int>);
int findSum(int, vector<int>);
void mapp(vector<int>,bool*);

int cuts,max = 0;
bool found = false;
vector<int> solution, input;

int main() {
	loadFile();
	cout << "podaj liczbe ciec: " << endl;
	cin >> cuts;
	cout << endl;
	bool *visited = new bool[input.size()];
	for (int i = 0; i < input.size(); i++) {
		visited[i] = false;
		if (input[i] > max)
			max = input[i];
	}

	for (int i = 0; i < input.size();i++) {
		visited[i] = true;
		solution.push_back(input[i]);
		mapp(solution, visited);
		if (found) {
			break;
		}
		visited[i] = false;
		solution.pop_back();		
	}

	if (solution.size() < 1)
		cout << "brak rozwiazania";

	getchar();
	getchar();
	return 0;
}

void loadFile() {
	cout << "podaj nazwe pliku: " << endl;
	string fileName;
	cin >> fileName;
	fstream file;
	file.open(fileName + ".txt", ios::in);

	string line;
	while (!file.eof()) {
		getline(file, line, ' ');
		input.push_back(stoi(line, nullptr, 10));
	}
	cout << endl << "zaladowano: " << input.size() << " liczb" << endl;
}
void print(vector<int> in) {
	for (auto num : in)
		cout << num << " ";
	cout << endl;
}
int sum(vector<int> map) {
	int sum = 0;
	for (int n : map)
		sum += n;
	return sum;
}
int findSum(int num, vector<int> map) {
	int sum=num;
	for (int n : map)
		sum += n;
	for (int i = 0; i < input.size();i++) {
		if (sum == input[i]) {
			return i;
		}
	}
	return -1;
}
void mapp(vector<int> map, bool *vis) {
	if (found) return;
	if (map.size() == cuts && sum(map) == max) {
		cout << "rozwiazanie to: " << endl;
		print(map);
		found = true;
	}
	else {
		for (int i = 0; i < input.size(); i++) {
			if (!vis[i]) {
				int index = findSum(input[i], map) ;
				if ( index != -1) {
					vis[i] = true;
					vis[index] = true;
					map.push_back(input[i]);
					print(map);
					mapp(map, vis);
					if (found) return;
					map.pop_back();
					vis[i] = false;
					vis[index] = false;
				}
			}
		}
	}
}