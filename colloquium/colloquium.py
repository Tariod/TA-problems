def findMaxMin(array):
    min = max = array[0]
    for value in array:
        if value < min:
            min = value
        if value > max:
            max = value
    return [max, min]


def createY(array, arrayMaxMin):
    yMax = 5587.65
    yMin = 16.3516
    coefficient = (yMax - yMin) / (arrayMaxMin[0] - arrayMaxMin[1])
    Y = []
    for value in array:
        Y.append(value * coefficient)
    return Y


def createZ(Y, yWithDash):
    Z = []
    counter = coefficient = 0
    for value in Y:
        if value > yWithDash[-1]:
            Z.append(yWithDash[-1])
            continue
        if value < yWithDash[0]:
            Z.append(yWithDash[0])
            continue
        for j in range(0, len(yWithDash) - 1):
            if yWithDash[j] < value < yWithDash[j + 1]:
                counter = j
                break
        coefficient = (yWithDash[counter] + yWithDash[counter + 1]) / 2
        if value < coefficient:
            Z.append(yWithDash[counter])
        else:
            Z.append(yWithDash[counter + 1])
    return Z


with open('s&p500.csv', 'r') as file:
    X = []
    for line in file:
        data = line.split(',')
        X.append(float(data[1]))

yWithDash = [float(s) for s in [line.strip() for line in open('with-dash.txt', 'r')]]

Y = createY(X, findMaxMin(X))
Z = createZ(Y, yWithDash)

outputFile = open('arrayY.txt', 'w')
for item in Y:
    outputFile.write("%s\n" % item)

outputFile = open('arrayZ.txt', 'w')
for item in Z:
    outputFile.write("%s\n" % item)
