#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

vector<int> insertionSort(vector<int> arraySorted)
{
	int curr, index;
	for (unsigned int i = 1; i < arraySorted.size(); i++)
	{
		curr = arraySorted[i];
		index = i - 1;
		while (index >= 0 &&
			((arraySorted[index] % 2 && !(curr % 2)) ||
			(arraySorted[index] % 2 == curr % 2 && curr % 2 == arraySorted[index] < curr))
		)
		{
			arraySorted[index + 1] = arraySorted[index];
			arraySorted[index] = curr;
			index--;
		}
	}
	return arraySorted;
}

int main()
{
	string fileName;
	cout << "Choose file: ";
	getline(cin, fileName);
	vector<int> arrForSort;
	ifstream fromFile("../" + fileName);
	if (!fromFile)
	{
		return 0;
	}
	int number;
	while (fromFile >> number)
	{
		arrForSort.push_back(number);
	}
	fromFile.close();

	arrForSort.erase(arrForSort.begin());

	vector<int> arraySorted = insertionSort(arrForSort);

	ofstream intoFile("../ip71_mikhailov_output.txt");
	int numberRes;
	for (unsigned int i = 0; i < arraySorted.size(); i++)
	{
		numberRes = arraySorted[i];
		intoFile << numberRes << endl;
	}
	intoFile.close();

	return 0;
}