#include "stdafx.h"
#include <fstream>
#include <iostream>

int **tasteAssessment(int **data, int height, int length, int standart);
int *similarityTasteOfPrsn(int *reference, int *comparable, int length);

int countInv(int *arrayToCount, int begin, int end);
int countSplitInv(int *arrayToCount, int begin, int middle, int end);

void mergeSort(int **arrayToSort, int begin, int end);
void merge(int **arrayToSort, int begin, int middle, int end);

int main() {
	int standart, people, films;
	int **data;

	std::ifstream fromFile("../ip71_mikhailov_input.txt");
	if (fromFile.is_open()) {
		fromFile >> people;
		fromFile >> films;

		std::cout << "Choose persone from 1 to " << people << ": ";
		std::cin >> standart;

		data = new int*[people];
		int row;
		for (int i = 0; i < people; i++) {
			data[i] = new int[films];
			for (int j = 0; j < films + 1; j++) {
				if (j != 0) {
					fromFile >> data[i][j - 1];
				} else {
					fromFile >> row;
				}
			}
		}
		fromFile.close();
	} else {
		std::cout << "No such file." << std::endl;
		return 0;
	}

	int **result = tasteAssessment(data, people, films, standart -1);
	
	mergeSort(result, 0, people - 1);
	
	std::ofstream intoFile("../ip71_mikhailov_output.txt");
	intoFile << standart << std::endl;
	for (int i = 1; i < people; i++) {
		for (int j = 0; j < 2; j++)
			intoFile << result[i][j] << " ";
		intoFile << std::endl;
	}
	intoFile << standart << std::endl;
	intoFile.close();

	std::cout << standart << std::endl;
	for (int i = 1; i < people; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			std::cout << result[i][j] << " ";
		}
		std::cout << std::endl;
	}
	delete data;
	delete result;
	system("pause");
	return 0;
}

int **tasteAssessment(int **data, int height, int length, int standart) {
	int **res = new int*[height];
	for (int i = 0; i < height; i++) {
		res[i] = new int[2];
		res[i][0] = i + 1;
		res[i][1] = countInv(similarityTasteOfPrsn(data[standart], data[i], length), 0, length - 1);
	}
	return res;
}

int *similarityTasteOfPrsn(int *reference, int *comparable, int length) {
	int *similarity = new int[length];
	for (int i = 0; i < length; i++) {
		for(int j = 0; j < length; j++) {
			if (reference[j] == i + 1)
				similarity[i] = comparable[j];
		}
	}
	return similarity;
}

int countInv(int *arrayToCount, int begin, int end) {
	if (begin >= end) {
		return 0;
	} else {
		int middle = (begin + end) / 2;

		int leftInv = countInv(arrayToCount, begin, middle);
		int rightInv = countInv(arrayToCount, middle + 1, end);
		int splitInv = countSplitInv(arrayToCount, begin, middle, end);

		return leftInv + rightInv + splitInv;
	}
}

int countSplitInv(int *arrayToCount, int begin, int middle, int end) {
	int sizeLeft = middle - begin + 1;
	int sizeRight = end - middle;
	int *arrayLeft = new int[sizeLeft + 1];
	int *arrayRight = new int[sizeRight + 1];

	int counter = 0;
	int counterLeft, counterRight, counterArray;

	for (counterLeft = 0; counterLeft < sizeLeft; counterLeft++)
		arrayLeft[counterLeft] = arrayToCount[begin + counterLeft];

	for (counterRight = 0; counterRight < sizeRight; counterRight++)
		arrayRight[counterRight] = arrayToCount[middle + counterRight + 1];

	counterLeft = 0;
	counterRight = 0;
	counterArray = begin;
	while (counterLeft < sizeLeft && counterRight < sizeRight) {
		if (arrayLeft[counterLeft] <= arrayRight[counterRight]) {
			arrayToCount[counterArray++] = arrayLeft[counterLeft++];
		} else {
			arrayToCount[counterArray++] = arrayRight[counterRight++];
			counter += (sizeLeft - counterLeft);
		}
	}

	while (counterLeft < sizeLeft)
		arrayToCount[counterArray++] = arrayLeft[counterLeft++];

	while (counterRight < sizeRight)
		arrayToCount[counterArray++] = arrayRight[counterRight++];

	delete arrayRight;
	delete arrayLeft;

	return counter;
}

void mergeSort(int **arrayToSort, int begin, int end) {
	if (begin < end) {
		int middle = (begin + end) / 2;
		mergeSort(arrayToSort, begin, middle);
		mergeSort(arrayToSort, middle + 1, end);
		merge(arrayToSort, begin, middle, end);
	}
}

void merge(int **arrayToSort, int begin, int middle, int end) {
	int sizeLeft = middle - begin + 1;
	int sizeRight = end - middle;
	int **arrayLeft = new int*[sizeLeft + 1];
	int **arrayRight = new int*[sizeRight + 1];

	int counterLeft, counterRight, counterArray;
	for (counterLeft = 0; counterLeft < sizeLeft; counterLeft++) {
		arrayLeft[counterLeft] = new int[2];
		arrayLeft[counterLeft][0] = arrayToSort[begin + counterLeft][0];
		arrayLeft[counterLeft][1] = arrayToSort[begin + counterLeft][1];
	}
	for (counterRight = 0; counterRight < sizeRight; counterRight++) {
		arrayRight[counterRight] = new int[2];
		arrayRight[counterRight][0] = arrayToSort[middle + counterRight + 1][0];
		arrayRight[counterRight][1] = arrayToSort[middle + counterRight + 1][1];
	}
	counterLeft = 0;
	counterRight = 0;
	counterArray = begin;
	while (counterLeft < sizeLeft && counterRight < sizeRight) {
		if (arrayLeft[counterLeft][1] <= arrayRight[counterRight][1]) {
			arrayToSort[counterArray][0] = arrayLeft[counterLeft][0];
			arrayToSort[counterArray++][1] = arrayLeft[counterLeft++][1];
		} else {
			arrayToSort[counterArray][0] = arrayRight[counterRight][0];
			arrayToSort[counterArray++][1] = arrayRight[counterRight++][1];
		}
	}

	while (counterLeft < sizeLeft) {
		arrayToSort[counterArray][0] = arrayLeft[counterLeft][0];
		arrayToSort[counterArray++][1] = arrayLeft[counterLeft++][1];
	}

	while (counterRight < sizeRight) {
		arrayToSort[counterArray][0] = arrayRight[counterRight][0];
		arrayToSort[counterArray++][1] = arrayRight[counterRight++][1];
	}

	delete arrayRight;
	delete arrayLeft;
}
