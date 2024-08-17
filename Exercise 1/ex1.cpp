#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string x, int size) {

	vector<string> res;
	res.resize(size);
	size_t k = 0;
	int i = 0;
	while (x.length() != 0) {

		k = x.find(",", 0);
		
		if (k == string::npos) {

			res[i] = x.substr(0, x.length());
			break;
		}

		res[i] = x.substr(0, k);

		x = x.substr(k + 1, x.length() - k);
		i++;
	}

	return res;

}

void displayMatrix(vector<vector<int>> a) {

	cout << "\nDispalying Matrix:\n\n";

	for (int i = 0; i < a.size(); i++) {

		string line = "";

		for (int v = 0; v < a.size(); v++) {
			cout << a[i][v] << " ";
			
		}
		cout << "\n";
	}
	cout << "\n\n";

}

void printVect(vector<string> a) {

	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << "\n ";

}

vector<vector<int>> getMatrix(string path) {

	vector<vector<int>> m1;

	ifstream fileReader(path);

	string str_N;
	int N;

	getline(fileReader, str_N);

	N = stoi(str_N);

	if (N <= 1) {
		cout << "\n\nINVALID MATRIX SIZE!\n\n";
		m1.resize(0);
		return m1;
	}

	m1.resize(N);

	string line;

	int i = 0;

	while (getline(fileReader, line)) {
	
		if (line.empty()) {
			continue;
		}
		
		vector<string> data = split(line, N);
		
		vector<int> row;
		row.resize(N);
		m1[i] = row;

		for (int v = 0; v < N; v++) {
		
			

			m1[i][v] = stoi(data[v]);
		}
	
		i++;
	}

	fileReader.close();
	return m1;
}

vector<int> getCol(vector<vector<int>> m, int col) {

	vector<int> res;
	res.resize(m.size());

	for (int i = 0; i < m.size(); i++) {

		res[i] = m[i][col];
	}
	return res;
}

int main() {

	string path; 
	
	while (true) {

		cout << "Insert path to the input file: ";
		cin >> path;
	
		vector<vector<int>> m = getMatrix(path);
		
		if (m.size() == 0) {
			continue;
		}

		displayMatrix(m);
		
		stack<int> s1;

		for (int i = 0; i < m.size(); i++) {
			s1.push(i);
		}

		while (s1.size() > 1) {

			int aux1 = s1.top();
			s1.pop();
			int aux2 = s1.top();
			s1.push(aux1);

			if (m[aux1][aux2] == 1 && m[aux2][aux1] == 1) {

				s1.pop();
				s1.pop();

			}
			else if (m[aux1][aux2] == 1 && m[aux2][aux1] == 0) {

				s1.pop();
			}
			else if (m[aux1][aux2] == 0 && m[aux2][aux1] == 1) {

				s1.pop();
				s1.pop();
				s1.push(aux1);
			}
			else {
				s1.pop();
				s1.pop();
			}
		}
		
		if (s1.empty()) {

			cout << "\n\nHomer wasn't present at the party.\n\n";

		}
		else {

			bool found = true;

			for (int i = 0; i < m.size(); i++) {
				if (m[s1.top()][i] == 1) {

					cout << "\n\nHomer wasn't present at the party.\n\n";
					found = false;
					break;
				}
			}

			if (found) {

				for (int i = 0; i < m.size(); i++) {

					if (m[i][s1.top()] == 0 && i != s1.top()) {
						cout << "\n\nHomer wasn't present at the party.\n\n";
						found = false;
						break;
					}
				}

				if (found == true) {
					cout << "\nHomer was found. His ID = " << s1.top() << " .\n";
				}
			}
		}
		
	}
}