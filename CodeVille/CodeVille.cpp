// CodeVille.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>


using namespace std;

class FileValidator {
public:
	bool validateFile(string filepath) {
		fstream scores;

		if (scores.is_open()) {
			return true;
		}
		else {
			return false;
		}
	};
};

class FileReader {
public:

	list<string> contestants;
	vector<int> contestantsScores;

	bool isString = false;

	void reader(string filepath) {

		ifstream scores(filepath);


		while(scores) {

		string s;
		if (!getline(scores, s)) break;
		istringstream ss(s);

			while (ss) {
				string s;
				if (!getline(ss, s, ',')) break;

				if (isString == false) {
					contestants.push_back(s);
					isString = true;
				}
				else if (isString == true) {
					contestantsScores.push_back(stoi(s));
					isString = false;
				}
			}
		}
	}
};

class Contestants:FileReader {
public:
	vector<string> contestantsArray;
	int i = 0;

	void listtoArray(list<string> competitor) {
		for (auto v : competitor) {
			if (i == 1 || i == 3 || i == 0) {
				contestantsArray.push_back(v);
			}
			i++;
		}

	}



};

class OutputFormatter:Contestants {
public:


	void FormatHighestScores(vector<int> arr, vector<string> names) {
		cout << "The top three scores are: " << arr[4] << " " << names[1] << " " <<  arr[3] << " " << names[2] << " " <<arr[2] << " " << names[0];
	}
};


class ListSorter:OutputFormatter {
public:
	vector<int> results;


	void sort(vector<int> arr,vector<string> names) {
		quicksort(arr,0,arr.size() - 1);
		OutputFormatter output;
		output.FormatHighestScores(arr,names);
	}

	int partition(vector<int>& values, int left, int right) {
		int pivotIndex = left + (right - left) / 2;
		int pivotValue = values[pivotIndex];
		int i = left, j = right;
		int temp;
		while (i <= j) {
			while (values[i] < pivotValue) {
				i++;
			}
			while (values[j] > pivotValue) {
				j--;
			}
			if (i <= j) {
				temp = values[i];
				values[i] = values[j];
				values[j] = temp;
				i++;
				j--;
			}
		}
		return i;
	}

	void quicksort(vector<int>& values, int left, int right) {
		if (left < right) {
			int pivotIndex = partition(values, left, right);
			quicksort(values, left, pivotIndex - 1);
			quicksort(values, pivotIndex, right);
		}
	}
};


int main()
{
	FileValidator file;
	file.validateFile("scores.csv");

	FileReader r;
	r.reader("scores.csv");


	ListSorter sort;


	vector<int> scores = r.contestantsScores;
	list<string> competitors = r.contestants;

	Contestants cont;
	cont.listtoArray(competitors);

	sort.sort(scores,cont.contestantsArray);


	
}

