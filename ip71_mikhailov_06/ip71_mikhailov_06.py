class Node:
    def __init__(self, key, next):
        self.key = key
        self.next = next


class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.length = 0

    def unshift(self, key):
        self.length += 1
        temp = Node(key, self.head)
        if self.tail is None:
            self.tail = temp
        self.head = temp

    def shift(self):
        if self.head is not None:
            self.length -= 1
            res = self.head.key
            if self.tail is self.head:
                self.head = self.tail = None
            else:
                self.head = self.head.next
            return res

    def search(self, key):
        temp = self.head
        if temp is not None:
            while (temp.key != key) and (temp.next is not None):
                temp = temp.next
            if temp.key == key:
                return True
        return False


class Hash(object):
    def __init__(self, length):
        self.table = None
        self.length = length
        self.collisions = 0

    def hash(self, key):
        raise NotImplementedError("Please Implement this method")

    def insert(self, key):
        raise NotImplementedError("Please Implement this method")


class ChainedHash(Hash):
    def __init__(self, length):
        super(ChainedHash, self).__init__(length)
        self.table = [LinkedList() for i in range(length)]

    def insert(self, key):
        position = self.hash(key)
        if self.table[position].search(key) is False:
            self.table[position].unshift(key)
            if self.table[position].length > 1:
                self.collisions += 1

    def search(self, key):
        position = self.hash(key)
        return self.table[position].search(key)


class ChainedDivisionHash(ChainedHash):
    def hash(self, key):
        return key % self.length


class ChainedMultiplicationHash(ChainedHash):
    def hash(self, key):
        return int(self.length * ((key * 0.6180339887) % 1))


class OpenAddressHash(Hash):
    def __init__(self, length):
        super(OpenAddressHash, self).__init__(length)
        self.table = [None for i in range(length)]

    def auxiliaryHash(self, key):
        return key % self.length

    def hash(self, key, index):
        raise NotImplementedError("Please Implement this method")

    def insert(self, key):
        index = 0
        position = self.hash(key, index)
        if self.table[position] is not None:
            while self.table[position] is not None and index < self.length:
                if self.table[position] == key:
                    return
                index += 1
                position = self.hash(key, index)
            self.collisions += 1
        if index == self.length:
            raise NameError("The table is full")
        self.table[position] = key

    def search(self, key):
        index = 0
        position = self.hash(key, index)
        while (key != self.table[position]) and (index < self.length):
            temp = self.table[position]
            index += 1
            position = self.hash(key, index)
        if self.table[position] == key:
            return True
        else:
            return False


class OpenAddressLiniarHash(OpenAddressHash):
    def hash(self, key, index):
        return (self.auxiliaryHash(key) + index) % self.length


class OpenAddressQuadraticHash(OpenAddressHash):
    def hash(self, key, index):
        return (self.auxiliaryHash(key) + 3 * index + 5 * index * index) % self.length


class OpenAddressDoubleHash(OpenAddressHash):
    def auxiliaryHashSecond(self, key):
        return int(self.length * ((key * 0.6180339887) % 1))

    def hash(self, key, index):
        return (self.auxiliaryHash(key) + index * self.auxiliaryHashSecond(key)) % self.length


def parseFile(fileName):
    data = []
    sums = []
    fileData = [map(int, i.split()) for i in open(fileName)]
    for index in range(1, fileData[0][0] + 1):
        data.append(fileData[index][0])
    for index in range(fileData[0][0] + 1, fileData[0][0] + fileData[0][1] + 1):
        sums.append(fileData[index][0])
    return data, sums


def writeFile(array, fileName):
    outputFile = open(fileName + '.txt', 'w')
    for item in array:
        if isinstance(item, list):
            outputFile.write("%s %s\n" % (item[0], item[1]))
        else:
            outputFile.write("%s\n" % item)


def writeResult(Division, Multiplication, Liniar, Quadratic, Double):
    fileName = 'ip71_mikhailov_output'
    writeFile(Division, fileName + '_division')
    writeFile(Multiplication, fileName + '_multiplication')
    writeFile(Liniar, fileName + '_liniar')
    writeFile(Quadratic, fileName + '_quadratic')
    writeFile(Double, fileName + '_double')

def test(data, sums, hashTable):
    res = []
    h = hashTable(3 * len(data))

    for x in data:
        h.insert(x)
    res.append(h.collisions)
    for s in sums:
        for x in data:
            if h.search(s - x):
                res.append([x, s - x])
                break
        else:
            res.append([0, 0])
    return res


data, sums = parseFile(raw_input('Write a file name.\n'))

Division = test(data, sums, ChainedDivisionHash)
Multiplication = test(data, sums, ChainedMultiplicationHash)
Liniar = test(data, sums, OpenAddressLiniarHash)
Quadratic = test(data, sums, OpenAddressQuadraticHash)
Double = test(data, sums, OpenAddressDoubleHash)

writeResult(Division, Multiplication, Liniar, Quadratic, Double)
