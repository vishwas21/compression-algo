import random
import numpy as np
from scipy.stats import norm


uniqueNumbers = []
blocks = []

def generateUniformDist(loadlen):
    file = open("./load/workloadUniformDist.txt", "w")

    with open("./load/workloadUniformDist.txt", "w") as file:
        for i in range(len(uniqueNumbers)):
            for _ in range(int(loadlen / len(uniqueNumbers))):
                file.write(str(uniqueNumbers[i]) + "\n")
    
    with open("./metadata/workload.txt", "w") as file:
        file.write("Length of Load: " + str(loadlen))
        file.write("\n\n")
        file.write("Uniform Distribution Workload: \n")
        for i in range(len(uniqueNumbers)):
            file.write(str(int(loadlen / len(uniqueNumbers))) + " " + str(uniqueNumbers[i]) + " ")
        file.write("\n")


def generateNormalDist(loadlen):
    data = np.arange(1,10,10/len(uniqueNumbers))
    pdf = norm.pdf(data , loc = 5.3 , scale = 1 )

    newBlocks = [int((p/sum(pdf)) * loadlen) for p in pdf]

    newBlocks[-1] += (loadlen - sum(newBlocks))

    if(len(uniqueNumbers) != len(newBlocks)):
        diff = len(uniqueNumbers) - len(newBlocks)

        for i in range(diff):
            newBlocks.append(0)

    with open("./load/workloadNormalDist.txt", "w") as file:
        for i in range(len(uniqueNumbers)):
            for _ in range(int((newBlocks[i]))):
                file.write(str(uniqueNumbers[i]) + "\n")
    
    with open("./metadata/workload.txt", "a") as file:
        file.write("Normal Distribution Workload: \n")
        for i in range(len(uniqueNumbers)):
            file.write(str(int((newBlocks[i]))) + " " + str(uniqueNumbers[i]) + " ")
        file.write("\n")

def generateUQuadDist(loadlen):
    data = np.arange(1,10,10/len(uniqueNumbers))
    pdf = norm.pdf(data , loc = 5.3 , scale = 1 )

    maxElement = max(pdf)

    pdf = [abs(p - maxElement) for p in pdf]

    newBlocks = [int((p/sum(pdf)) * loadlen) for p in pdf]

    newBlocks[-1] += (loadlen - sum(newBlocks))

    if(len(uniqueNumbers) != len(newBlocks)):
        diff = len(uniqueNumbers) - len(newBlocks)

        for i in range(diff):
            newBlocks.append(0)

    with open("./load/workloadUQuadDist.txt", "w") as file:
        for i in range(len(uniqueNumbers)):
            for _ in range(int((newBlocks[i]))):
                file.write(str(uniqueNumbers[i]) + "\n")
    
    with open("./metadata/workload.txt", "a") as file:
        file.write("U Quadratic Distribution Workload: \n")
        for i in range(len(uniqueNumbers)):
            file.write(str(int((newBlocks[i]))) + " " + str(uniqueNumbers[i]) + " ")
        file.write("\n")


def generateWorkloadNormal(loadlen):
    file = open("./load/workloadNormal.txt", "w")

    global blocks

    for i in range(len(uniqueNumbers)):
        for _ in range(int((blocks[i]))):
            file.write(str(uniqueNumbers[i]) + "\n")

    file.close()
    file = open("./metadata/workload.txt", "a")
    file.write("Length of Load : " + str(loadlen) + "\n")

    file.write("Workload Normal: \n")
    for i in range(len(uniqueNumbers)):
        file.write(str(int((blocks[i]))) + " " + str(uniqueNumbers[i]) + " ")
    file.write("\n")
    file.close()

def swapNumbers(arr, indexOne, indexTwo):
    temp = arr[indexOne]
    arr[indexOne] = arr[indexTwo]
    arr[indexTwo] = temp

def generateWorkloadGlobalDisorder(loadlen):
    file = open("./load/workloadGlobalDisorder.txt", "w")

    numShuffles = 4

    blocksNew = [i for i in blocks]
    uniqueNumbersNew = [i for i in uniqueNumbers]

    index = []

    while numShuffles > 0:
        i = random.randint(0, len(uniqueNumbersNew) - 1)
        j = random.randint(0, len(uniqueNumbersNew) - 1)
        while j == i:
            j = random.randint(0, len(uniqueNumbersNew) - 1)
        
        if i in index or j in index:
            continue
        
        swapNumbers(uniqueNumbersNew, i, j)
        swapNumbers(blocksNew, i, j)
        
        index.append(i)
        index.append(j)
        numShuffles -= 1


    for i in range(len(uniqueNumbersNew)):
        for _ in range(int((blocksNew[i]))):
            file.write(str(uniqueNumbersNew[i]) + "\n")

    file.close()
    file = open("./metadata/workload.txt", "a")
    file.write("Length of Load : " + str(loadlen) + "\n")

    file.write("Workload Global Disorder: \n")
    for i in range(len(uniqueNumbersNew)):
        file.write(str(int((blocksNew[i]))) + " " + str(uniqueNumbersNew[i]) + " ")
    file.write("\n")
    file.close()
    
def generateWorkloadLocalDisorder(loadlen):
    file = open("./load/workloadLocalDisorder.txt", "w")

    i = 0

    while True:
        swapNumbers(uniqueNumbers, i, i + 1)
        swapNumbers(blocks, i, i + 1)
        i += 2
        if(i >= len(uniqueNumbers) - 1):
            break

    for i in range(len(uniqueNumbers)):
        for _ in range(int((blocks[i]))):
            file.write(str(uniqueNumbers[i]) + "\n")

    file.close()
    file = open("./metadata/workload.txt", "a")
    file.write("Length of Load : " + str(loadlen) + "\n")

    file.write("Workload Local Disorder: \n")
    for i in range(len(uniqueNumbers)):
        file.write(str(int((blocks[i]))) + " " + str(uniqueNumbers[i]) + " ")
    file.write("\n")
    file.close()
    

def generateBlocks(n, loadlen):
    global blocks

    blocks = []

    remaining_size = loadlen
    min_block = 1
    max_block = loadlen // n
    for i in range(n - 1):
        block_size = random.randint(min_block, max_block)
        if block_size == 25:
            block_size = random.randint(min_block, max_block)
        blocks.append(block_size)
        remaining_size -= block_size
    blocks.append(remaining_size)

    return blocks

def generateWorkloadScalable(scaleText, loadlen):
    file = open("./load/workloadScale" + scaleText + ".txt", "w")

    global blocks

    for i in range(len(uniqueNumbers)):
        for _ in range(int((blocks[i]))):
            file.write(str(uniqueNumbers[i]) + "\n")

    file.close()
    file = open("./metadata/workload.txt", "a")
    file.write("Length of Load : " + str(loadlen) + "\n")

    file.write("Workload Scalable " + scaleText + ": \n")
    for i in range(len(uniqueNumbers)):
        file.write(str(int((blocks[i]))) + " " + str(uniqueNumbers[i]) + " ")
    file.write("\n")
    file.close()

def main(n, loadlen):
    for i in range(100, 100 + n):
        uniqueNumbers.append(i)

    generateUniformDist(loadlen)
    generateNormalDist(loadlen)
    generateUQuadDist(loadlen)

    generateBlocks(n, loadlen)

    generateWorkloadNormal(loadlen)
    generateWorkloadGlobalDisorder(loadlen)
    generateWorkloadLocalDisorder(loadlen)

    # Generating Scalability Workloads
    generateBlocks(n, 100000)
    generateWorkloadScalable("One", 100000)

    generateBlocks(n, 1000000)
    generateWorkloadScalable("Two", 1000000)

    generateBlocks(n, 10000000)
    generateWorkloadScalable("Three", 10000000)

    generateBlocks(n, 100000000)
    generateWorkloadScalable("Four", 100000000)

if __name__ == "__main__":
    main(25, 10000000)