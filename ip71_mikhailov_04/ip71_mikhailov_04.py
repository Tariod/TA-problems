def countingSort(arrayToSort, diapason, discharge):
    arrayLength = len(arrayToSort)
    temp = [0] * diapason
    arraySorted = [-1] * arrayLength
    index = 0
    for counter in range(0, arrayLength):
        index = arrayToSort[counter] / discharge % 10
        temp[index] += 1
    for counter in range(1, diapason):
        temp[counter] += temp[counter - 1]
    for counter in range(arrayLength - 1, -1, -1):
        index = arrayToSort[counter] / discharge % 10
        arraySorted[temp[index] - 1] = arrayToSort[counter]
        temp[index] -= 1
    return arraySorted


def radixSort(arrayToSort, discharge):
    currDischarge = 1
    result = arrayToSort
    while currDischarge <= discharge:
        result = countingSort(result, 10, currDischarge)
        currDischarge *= 10
    return result


arrayToSort = [int(s) for s in [line.strip() for line in open(raw_input('Enter file name:\n'), 'r')]]
arrayToSort.pop(0)

discharge = int(raw_input('Choose discharge:\n'))
result = radixSort(arrayToSort, discharge)

outputFile = open('ip71_mikhailov_output.txt', 'w')
for item in result:
    outputFile.write("%s\n" % item)
