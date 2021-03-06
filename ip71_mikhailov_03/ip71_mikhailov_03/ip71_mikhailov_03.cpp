#include "stdafx.h"
#include <fstream>
#include <iostream>

void QuickSort(int *arrayToSort, int begin, int end);
int PartitionLomuto(int *arrayToSort, int begin, int end);
void QuickSortMedian(int *arrayToSort, int begin, int end);
void findMedian(int *arrayToSort, int begin, int end);

void QuickSort3Pivot(int *arrayToSort, int begin, int end);
void Partition3Pivot(int *arrayToSort, int begin, int end, int &partitionLeft, int &partitionMiddle, int &partitionRight);
void sortPivots(int *arrayToSort, int begin, int end);

void Sort(int *arrayToSort, int begin, int end);
void swap(int &element1, int &element2);
int *copyArray(int *array, int size);

int countComprasion = 0;

int main() {
	int size;
	int *data;
	int *result = new int[3];

	std::ifstream fromFile("../ip71_mikhailov_input.txt");
	if (fromFile.is_open()) {
		fromFile >> size;
		data = new int[size];
		for (int i = 0; i < size; i++)
			fromFile >> data[i];
		fromFile.close();
	} else {
		std::cout << "No such file." << std::endl;
		system("pause");
		return 0;
	}

	QuickSort(copyArray(data, size), 0, size - 1);
	result[0] = countComprasion;
	countComprasion = 0;

	QuickSortMedian(copyArray(data, size), 0, size - 1);
	result[1] = countComprasion;
	countComprasion = 0;

	QuickSort3Pivot(data, 0, size - 1);
	for (int i = 0; i < size; i++)
	{
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "countComprasion: " << countComprasion << std::endl;
	result[2] = countComprasion;

	std::ofstream intoFile("../ip71_mikhailov_output.txt");
	for (int i = 0; i < 3; i++)
		intoFile << result[i] << " ";
	intoFile.close();

	delete data;
	delete result;
	system("pause");
	return 0;
}

void QuickSort(int *arrayToSort, int begin, int end) {
	if (begin < end) {
		int partition = PartitionLomuto(arrayToSort, begin, end);
		QuickSort(arrayToSort, begin, partition - 1);
		QuickSort(arrayToSort, partition + 1, end);
	}
}

int PartitionLomuto(int *arrayToSort, int begin, int end) {
	int lastElement = arrayToSort[end];
	int partition = begin - 1;
	for (int j = begin; j < end; j++) {
		countComprasion++;
		if (arrayToSort[j] <= lastElement)
			swap(arrayToSort[++partition], arrayToSort[j]);
	}
	swap(arrayToSort[++partition], arrayToSort[end]);
	return partition;
}

void QuickSortMedian(int *arrayToSort, int begin, int end) {
	int size = end - begin + 1;
	if (size <= 3) {
			Sort(arrayToSort, begin, end);
	} else {
		findMedian(arrayToSort, begin, end);
		int partition = PartitionLomuto(arrayToSort, begin, end);
		QuickSortMedian(arrayToSort, begin, partition - 1);
		QuickSortMedian(arrayToSort, partition + 1, end);
	}
}

void findMedian(int *arrayToSort, int begin, int end) {
	int middle = (begin + end) / 2;
	int beginVal = arrayToSort[begin];
	int middleVal = arrayToSort[middle];
	int endVal = arrayToSort[end];
	if (beginVal > middleVal) {
		if (endVal > beginVal) {
			swap(arrayToSort[begin], arrayToSort[end]);
		} else {
			if (endVal < middleVal)
				swap(arrayToSort[middle], arrayToSort[end]);
		}
	} else {
		if (endVal > middleVal) {
			swap(arrayToSort[middle], arrayToSort[end]);
		} else {
			if (endVal < beginVal)
				swap(arrayToSort[begin], arrayToSort[end]);
		}
	}
}

void QuickSort3Pivot(int *arrayToSort, int begin, int end) {
	int size = end - begin + 1;
	if (size <= 3) {
		if (size > 1)
			Sort(arrayToSort, begin, end);
	} else {
		int partitionLeft, partitionRight, partitionMiddle;
		sortPivots(arrayToSort, begin, end);
		Partition3Pivot(arrayToSort, begin, end, partitionLeft, partitionMiddle, partitionRight);

		QuickSort3Pivot(arrayToSort, begin, partitionLeft - 1);
		QuickSort3Pivot(arrayToSort, partitionLeft + 1, partitionMiddle - 1);
		QuickSort3Pivot(arrayToSort, partitionMiddle + 1, partitionRight - 1);
		QuickSort3Pivot(arrayToSort, partitionRight + 1, end);
	}
}

void Partition3Pivot(int *arrayToSort, int begin, int end, int &partitionLeft, int &partitionMiddle, int &partitionRight) {
	int index;
	partitionLeft = partitionMiddle = begin + 2;
	index = partitionRight = end - 1;
	int pivotLeft = arrayToSort[begin];
	int pivotMiddle = arrayToSort[begin + 1];
	int pivotRight = arrayToSort[end];
	while (partitionMiddle <= index) {

		countComprasion++;
		while (arrayToSort[partitionMiddle] < pivotMiddle && partitionMiddle <= index) {
			countComprasion += 2;
			if (arrayToSort[partitionMiddle] < pivotLeft) {
				swap(arrayToSort[partitionLeft], arrayToSort[partitionMiddle]);
				++partitionLeft;
			}
			++partitionMiddle;
		}

		countComprasion++;
		while (arrayToSort[index] > pivotMiddle && partitionMiddle <= index) {
			countComprasion += 2;
			if (arrayToSort[index] > pivotRight) {
				swap(arrayToSort[index], arrayToSort[partitionRight]);
				--partitionRight;
			}
			--index;
		}

		if (partitionMiddle <= index) {
			countComprasion++;
			if (arrayToSort[partitionMiddle] > pivotRight) {
				countComprasion++;
				if (arrayToSort[index] < pivotLeft) {
					swap(arrayToSort[partitionMiddle], arrayToSort[partitionLeft]);
					swap(arrayToSort[partitionLeft], arrayToSort[index]);
					++partitionLeft;
				} else {
					swap(arrayToSort[partitionMiddle], arrayToSort[index]);
				}
				swap(arrayToSort[index], arrayToSort[partitionRight]);
				++partitionMiddle; --index; --partitionRight;
			} else {
				countComprasion++;
				if (arrayToSort[index] < pivotLeft) {
					swap(arrayToSort[partitionMiddle], arrayToSort[partitionLeft]);
					swap(arrayToSort[partitionLeft], arrayToSort[index]);
					++partitionLeft;
				} else {
					swap(arrayToSort[partitionMiddle], arrayToSort[index]);
				}
				++partitionMiddle; --index;
			}
		}
	}
	--partitionLeft; --partitionMiddle; ++partitionRight; ++index;
	swap(arrayToSort[begin + 1], arrayToSort[partitionLeft]);
	swap(arrayToSort[partitionLeft], arrayToSort[partitionMiddle]);
	--partitionLeft;
	swap(arrayToSort[begin], arrayToSort[partitionLeft]);
	swap(arrayToSort[end], arrayToSort[partitionRight]);
}

void Sort(int *arrayToSort, int begin, int end) {
	int curr, index;
	for (int i = begin; i <= end; i++) {
		curr = arrayToSort[i];
		index = i - 1;
		countComprasion++;
		while (index >= 0 && arrayToSort[index] > curr) {
			countComprasion++;
			arrayToSort[index + 1] = arrayToSort[index];
			arrayToSort[index] = curr;
			index--;
		}
	}
}

void sortPivots(int *arrayToSort, int begin, int end) {
	if (arrayToSort[end] < arrayToSort[begin])
		swap(arrayToSort[begin], arrayToSort[end]);
	if (arrayToSort[begin + 1] < arrayToSort[begin])
		swap(arrayToSort[begin + 1], arrayToSort[begin]);
	if (arrayToSort[end] < arrayToSort[begin + 1])
		swap(arrayToSort[end], arrayToSort[begin + 1]);
}

void swap(int &element1, int &element2) {
	int temp = element1;
	element1 = element2;
	element2 = temp;
}

int *copyArray(int *array, int size) {
	int *copy = new int[size];
	for (int i = 0; i < size; i++)
		copy[i] = array[i];
	return copy;
}
