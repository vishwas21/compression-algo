import random

uniqueNumbers = []
ratios = []

def generateWorkloadOne(loadlen):
    file = open("./load/workloadOne.txt", "w")

    for i in range(len(uniqueNumbers)):
        for _ in range(int((loadlen * ratios[i]))):
            file.write(str(uniqueNumbers[i]) + "\n")

    file.close()
    file = open("./metadata/workload.txt", "w")
    file.write("Length of Load : " + str(loadlen) + "\n")

    file.write("Workload One: \n")
    for i in range(len(uniqueNumbers)):
        file.write(str(int((loadlen * ratios[i]))) + " " + str(uniqueNumbers[i]) + " ")
    file.write("\n")
    file.close()
    

def generateWorkloadTwo(loadlen):
    file = open("./load/workloadTwo.txt", "w")

    for _ in range(int((loadlen * ratios[1]))):
        file.write(str(uniqueNumbers[1]) + "\n")
    
    for _ in range(int((loadlen * ratios[0]))):
        file.write(str(uniqueNumbers[0]) + "\n")

    for _ in range(int((loadlen * ratios[3]))):
        file.write(str(uniqueNumbers[3]) + "\n")
    
    for _ in range(int((loadlen * ratios[2]))):
        file.write(str(uniqueNumbers[2]) + "\n")

    for i in range(4, len(uniqueNumbers)):
        for _ in range(int((loadlen * ratios[i]))):
            file.write(str(uniqueNumbers[i]) + "\n")

    file.close()

    file = open("./metadata/workload.txt", "a")

    file.write("Workload Two: \n")
    file.write(str(int((loadlen * ratios[1]))) + " " + str(uniqueNumbers[1]) + " ")
    file.write(str(int((loadlen * ratios[0]))) + " " + str(uniqueNumbers[0]) + " ")
    file.write(str(int((loadlen * ratios[3]))) + " " + str(uniqueNumbers[3]) + " ")
    file.write(str(int((loadlen * ratios[2]))) + " " + str(uniqueNumbers[4]) + " ")
    for i in range(4, len(uniqueNumbers)):
        file.write(str(int((loadlen * ratios[i]))) + " " + str(uniqueNumbers[i]) + " ")
    
    file.write("\n")
    file.close()


def generateWorkloadThree(loadlen):
    file = open("./load/workloadThree.txt", "w")

    for i in range(1, len(uniqueNumbers)):
        for _ in range(int((loadlen * ratios[i]))):
            file.write(str(uniqueNumbers[i]) + "\n")
    
    for _ in range(int((loadlen * ratios[0]))):
        file.write(str(uniqueNumbers[0]) + "\n")

    file.close()

    file = open("./metadata/workload.txt", "a")
    file.write("Workload Three: \n")

    for i in range(1, len(uniqueNumbers)):
        file.write(str(int((loadlen * ratios[i]))) + " " + str(uniqueNumbers[i]) + " ")
    file.write(str(int((loadlen * ratios[0]))) + " " + str(uniqueNumbers[0]) + " ")
    file.write("\n")
    file.close()


def generateWorkloadFour(loadlen):
    file = open("./load/workloadFour.txt", "a")

    for i in range(2, len(uniqueNumbers)):
        for _ in range(int((loadlen * ratios[i]))):
            file.write(str(uniqueNumbers[i]) + "\n")
    
    for _ in range(int((loadlen * ratios[0]))):
        file.write(str(uniqueNumbers[0]) + "\n")
    
    for _ in range(int((loadlen * ratios[1]))):
        file.write(str(uniqueNumbers[1]) + "\n")
    

    file.close()
    file = open("./metadata/workload.txt", "a")

    file.write("Workload Four: \n")

    for i in range(1, len(uniqueNumbers)):
        file.write(str(int((loadlen * ratios[i]))) + " " + str(uniqueNumbers[i]) + " ")
    file.write(str(int((loadlen * ratios[0]))) + " " + str(uniqueNumbers[0]) + " ")
    file.write("\n")
    file.close()

def generateWorkloadFive(loadlen):
    file = open("./load/workloadFive.txt", "w")

    oneCount = int((loadlen * ratios[0]))
    onePart1 = int(oneCount * random.uniform(0, 1))
    onePart2 = oneCount - onePart1

    for _ in range(onePart1):
        file.write(str(uniqueNumbers[0]) + "\n")
    
    for _ in range(int((loadlen * ratios[1]))):
        file.write(str(uniqueNumbers[1]) + "\n")

    for _ in range(int((loadlen * ratios[2]))):
        file.write(str(uniqueNumbers[2]) + "\n")

    for _ in range(int((loadlen * ratios[3]))):
        file.write(str(uniqueNumbers[3]) + "\n")
    
    for _ in range(onePart2):
        file.write(str(uniqueNumbers[0]) + "\n")
    
    for i in range(4, len(uniqueNumbers)):
        for _ in range(int((loadlen * ratios[i]))):
            file.write(str(uniqueNumbers[i]) + "\n")
        
    file.close()
    file = open("./metadata/workload.txt", "a")

    file.write("Workload Five: \n")

    file.write(str(onePart1) + " " + str(uniqueNumbers[0]) + " ")
    file.write(str(int((loadlen * ratios[1]))) + " " + str(uniqueNumbers[1]) + " ")
    file.write(str(onePart2) + " " + str(uniqueNumbers[0]) + " ")
    file.write(str(int((loadlen * ratios[2]))) + " " + str(uniqueNumbers[4]) + " ")
    file.write(str(int((loadlen * ratios[3]))) + " " + str(uniqueNumbers[3]) + " ")

    for i in range(4, len(uniqueNumbers)):
        file.write(str(int((loadlen * ratios[i]))) + " " + str(uniqueNumbers[i]) + " ")
    file.write("\n")
    file.close()

def main(n, loadlen):
    for i in range(1, n + 1):
        uniqueNumbers.append(i)

    total = 1 
    avg = total / n
    ratio = 0
    global ratios

    for i in range(n - 1):
        deviation = random.uniform(-0.1, 0.1)
        ratio = avg * (1 + deviation)
        ratios.append(ratio)

    ratios.append(1 - sum(ratios))
    sum_ratios = sum(ratios)
    ratios = [round(ratio / sum_ratios, 5) for ratio in ratios]

    generateWorkloadOne(loadlen)
    generateWorkloadTwo(loadlen)
    generateWorkloadThree(loadlen)
    generateWorkloadFour(loadlen)
    generateWorkloadFive(loadlen)



if __name__ == "__main__":
    main(10, 1000000)