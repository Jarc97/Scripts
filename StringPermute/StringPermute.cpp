#ifdef _WIN32
#define OS_WINDOWS 1
#include <Windows.h>
#endif

#ifdef __unix__
#define OS_WINDOWS 0
#endif

#include <iostream>
#include <fstream>
#include <string>			// getline()
#include <vector>
#include <algorithm>		// sort(), next_permutation()
#include <ctime>			// time_t, time()


using namespace std;

int factorial(int x) {
	int valor = 1;
	if (x == 0)
		return 1;

	for (int i = 1; i <= x; i++) {
		valor *= i;
	}
	return valor;
}

int permutation(int n, int r) {
	return factorial(n) / factorial(n-r);
}

void stringPermuteAlgorithm(vector<string> &input, vector<string> &output) {
	int n = input.size();	// total strings to permute
	sort(input.begin(), input.end());	// order the input vector
	do {
		// generate the next permuted line
		string line;
		for (int i = 0; i < n; i++) {
			line.append(input.at(i));
		}
		// save the permuted line in output vector
		output.push_back(line);
	} while (next_permutation(input.begin(), input.end()));		// generate the next permutation
}

string permuteDurationFormatting(time_t start, time_t end) {
	int diff = (int)difftime(end, start);
	if (diff < 1) {
		return "<1 second";
	}
	else {
		return diff + "seconds";
	}
}

void saveResults(vector<string> &results, ofstream &file) {
	for (int i = 0; i < results.size(); i++) {
		file << results.at(i) << endl;
	}
}

bool confirmExecution() {
	string a;
	cout << "Confirm execution(y): ";
	cin >> a;
	if (a == "y" || a == "Y")
		return true;
	else
		return false;
}

void storeFileElements(ifstream &file, vector<string> &v) {
	string line;
	while (!file.eof() && getline(file, line)) {
		v.push_back(line);
	}
}


int main() {
	ifstream iFile("data.txt");
	ofstream oFile("results.txt");

	vector<string> elementsIn;
	storeFileElements(iFile, elementsIn);
	vector<string> elementsOut;

	if (!iFile.is_open()) {
		cout << "Error opening the input file." << endl;
		system("pause");
		return 0;
	}
	else {
		cout << permutation(elementsIn.size(), elementsIn.size()) << " permutations will be stored in results.txt" << endl;
		if (confirmExecution()) {
			cout << "Executing........... ";
		}
		else {
			return 0;
		}
		time_t start = time(0);
		stringPermuteAlgorithm(elementsIn, elementsOut);
		time_t end = time(0);
		cout << "Done" << endl;
		cout << "Saving results...... ";
		saveResults(elementsOut, oFile);
		cout << "Done" << endl << endl;

		cout << "Execution time: " + permuteDurationFormatting(start, end) << endl;
	}

	iFile.close();
	oFile.close();
	system("pause");
	return 0;
}