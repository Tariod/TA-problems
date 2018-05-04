class Heap:

    def __init__(self, array, isMax):
        self.heap = array
        self.isMax = isMax

    size = -1
    isMax = False
    heap = []

    def parent(self, counter):
        return (counter - 1) // 2

    def buildHeap(self):
        self.size = len(self.heap) - 1
        for i in range(len(self.heap) // 2, -1, -1):
            self.heapify(self.heap, i)

    def heapify(self, array, counter):
        leftChild = 2 * counter + 1
        rightChild = 2 * counter + 2
        peak = counter

        if self.isMax:
            if leftChild <= self.size and array[leftChild] > array[counter]:
                peak = leftChild

            if rightChild <= self.size and array[rightChild] > array[peak]:
                peak = rightChild
        else:
            if leftChild <= self.size and array[leftChild] < array[counter]:
                peak = leftChild

            if rightChild <= self.size and array[rightChild] < array[peak]:
                peak = rightChild

        if peak is not counter:
            array[counter], array[peak] = array[peak], array[counter]
            self.heapify(array, peak)

    def insert(self, key):
        self.size += 1
        counter = self.size
        self.heap.append(key)
        while counter > 0 and (
                (self.heap[self.parent(counter)] < key and self.isMax) or
                (self.heap[self.parent(counter)] > key and not self.isMax)
        ):
            self.heap[counter] = self.heap[self.parent(counter)]
            counter = self.parent(counter);
        self.heap[counter] = key


def balanceHeaps(heapLow, heapHigh):
    if heapHigh.size - heapLow.size > 1:
        heapLow.insert(heapHigh.heap.pop(0))
        heapHigh.buildHeap()

    if heapLow.size - heapHigh.size > 1:
        heapHigh.insert(heapLow.heap.pop(0))
        heapLow.buildHeap()


def findMedian(heapLow, heapHigh, length):
    if(length + 1) % 2:
        if heapLow.size > heapHigh.size:
            res = heapLow.heap[0]
        else:
            res = heapHigh.heap[0]
    else:
        res = [heapLow.heap[0], heapHigh.heap[0]]

    return res


def medianSequence(array):
    heapLow = Heap([], True)
    heapHigh = Heap([], False)
    result = []

    heapLow.insert(array[0])
    result.append(array[0])

    for counter in range(1, len(array)):
        temp = array[counter]
        if temp < heapLow.heap[0]:
            heapLow.insert(temp)
        else:
            heapHigh.insert(temp)

        balanceHeaps(heapLow, heapHigh)

        result.append(findMedian(heapLow, heapHigh, counter))
    return result


arr = [int(s) for s in [line.strip() for line in open(raw_input('Enter file name:\n'), 'r')]]
arr.pop(0)

resu1t = medianSequence(arr)

outputFile = open('ip71_mikhailov_output.txt', 'w')
for item in resu1t:
    if isinstance(item, list):
        outputFile.write("%s %s\n" % (item[0], item[1]))
    else:
        outputFile.write("%s\n" % item)