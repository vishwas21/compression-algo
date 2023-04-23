# import random

# uniqueNumbers = []
# blocks = []

# def generateWorkloadOne(loadlen):
#     file = open("./load/workloadOne.txt", "w")

#     global blocks
#     random.shuffle(blocks)

#     for i in range(len(uniqueNumbers)):
#         for _ in range(int((blocks[i]))):
#             file.write(str(uniqueNumbers[i]) + "\n")

#     file.close()
#     file = open("./metadata/workload.txt", "w")
#     file.write("Length of Load : " + str(loadlen) + "\n")

#     file.write("Workload One: \n")
#     for i in range(len(uniqueNumbers)):
#         file.write(str(int((blocks[i]))) + " " + str(uniqueNumbers[i]) + " ")
#     file.write("\n")
#     file.close()
    

# def generateWorkloadTwo(loadlen):
#     file = open("./load/workloadTwo.txt", "w")

#     for _ in range(int((loadlen * ratios[1]))):
#         file.write(str(uniqueNumbers[1]) + "\n")
    
#     for _ in range(int((loadlen * ratios[0]))):
#         file.write(str(uniqueNumbers[0]) + "\n")

#     for _ in range(int((loadlen * ratios[3]))):
#         file.write(str(uniqueNumbers[3]) + "\n")
    
#     for _ in range(int((loadlen * ratios[2]))):
#         file.write(str(uniqueNumbers[2]) + "\n")

#     for i in range(4, len(uniqueNumbers)):
#         for _ in range(int((loadlen * ratios[i]))):
#             file.write(str(uniqueNumbers[i]) + "\n")

#     file.close()

#     file = open("./metadata/workload.txt", "a")

#     file.write("Workload Two: \n")
#     file.write(str(int((loadlen * ratios[1]))) + " " + str(uniqueNumbers[1]) + " ")
#     file.write(str(int((loadlen * ratios[0]))) + " " + str(uniqueNumbers[0]) + " ")
#     file.write(str(int((loadlen * ratios[3]))) + " " + str(uniqueNumbers[3]) + " ")
#     file.write(str(int((loadlen * ratios[2]))) + " " + str(uniqueNumbers[4]) + " ")
#     for i in range(4, len(uniqueNumbers)):
#         file.write(str(int((loadlen * ratios[i]))) + " " + str(uniqueNumbers[i]) + " ")
    
#     file.write("\n")
#     file.close()


# def generateWorkloadThree(loadlen):
#     file = open("./load/workloadThree.txt", "w")

#     for i in range(1, len(uniqueNumbers)):
#         for _ in range(int((loadlen * ratios[i]))):
#             file.write(str(uniqueNumbers[i]) + "\n")
    
#     for _ in range(int((loadlen * ratios[0]))):
#         file.write(str(uniqueNumbers[0]) + "\n")

#     file.close()

#     file = open("./metadata/workload.txt", "a")
#     file.write("Workload Three: \n")

#     for i in range(1, len(uniqueNumbers)):
#         file.write(str(int((loadlen * ratios[i]))) + " " + str(uniqueNumbers[i]) + " ")
#     file.write(str(int((loadlen * ratios[0]))) + " " + str(uniqueNumbers[0]) + " ")
#     file.write("\n")
#     file.close()


# def generateWorkloadFour(loadlen):
#     file = open("./load/workloadFour.txt", "a")

#     for i in range(2, len(uniqueNumbers)):
#         for _ in range(int((loadlen * ratios[i]))):
#             file.write(str(uniqueNumbers[i]) + "\n")
    
#     for _ in range(int((loadlen * ratios[0]))):
#         file.write(str(uniqueNumbers[0]) + "\n")
    
#     for _ in range(int((loadlen * ratios[1]))):
#         file.write(str(uniqueNumbers[1]) + "\n")
    

#     file.close()
#     file = open("./metadata/workload.txt", "a")

#     file.write("Workload Four: \n")

#     for i in range(1, len(uniqueNumbers)):
#         file.write(str(int((loadlen * ratios[i]))) + " " + str(uniqueNumbers[i]) + " ")
#     file.write(str(int((loadlen * ratios[0]))) + " " + str(uniqueNumbers[0]) + " ")
#     file.write("\n")
#     file.close()

# def generateWorkloadFive(loadlen):
#     file = open("./load/workloadFive.txt", "w")

#     oneCount = int((loadlen * ratios[0]))
#     onePart1 = int(oneCount * random.uniform(0, 1))
#     onePart2 = oneCount - onePart1

#     for _ in range(onePart1):
#         file.write(str(uniqueNumbers[0]) + "\n")
    
#     for _ in range(int((loadlen * ratios[1]))):
#         file.write(str(uniqueNumbers[1]) + "\n")

#     for _ in range(int((loadlen * ratios[2]))):
#         file.write(str(uniqueNumbers[2]) + "\n")

#     for _ in range(int((loadlen * ratios[3]))):
#         file.write(str(uniqueNumbers[3]) + "\n")
    
#     for _ in range(onePart2):
#         file.write(str(uniqueNumbers[0]) + "\n")
    
#     for i in range(4, len(uniqueNumbers)):
#         for _ in range(int((loadlen * ratios[i]))):
#             file.write(str(uniqueNumbers[i]) + "\n")
        
#     file.close()
#     file = open("./metadata/workload.txt", "a")

#     file.write("Workload Five: \n")

#     file.write(str(onePart1) + " " + str(uniqueNumbers[0]) + " ")
#     file.write(str(int((loadlen * ratios[1]))) + " " + str(uniqueNumbers[1]) + " ")
#     file.write(str(onePart2) + " " + str(uniqueNumbers[0]) + " ")
#     file.write(str(int((loadlen * ratios[2]))) + " " + str(uniqueNumbers[4]) + " ")
#     file.write(str(int((loadlen * ratios[3]))) + " " + str(uniqueNumbers[3]) + " ")

#     for i in range(4, len(uniqueNumbers)):
#         file.write(str(int((loadlen * ratios[i]))) + " " + str(uniqueNumbers[i]) + " ")
#     file.write("\n")
#     file.close()

# def main(n, loadlen):
#     for i in range(1, n + 1):
#         uniqueNumbers.append(i)

#     global blocks

#     remaining_size = loadlen
#     min_block = 1
#     max_block = loadlen // n
#     for i in range(n - 1):
#         block_size = random.randint(min_block, max_block)
#         if block_size == 25:
#             block_size = random.randint(min_block, max_block)
#         blocks.append(block_size)
#         remaining_size -= block_size
#     blocks.append(remaining_size)

#     generateWorkloadOne(loadlen)
#     # generateWorkloadTwo(loadlen)
#     # generateWorkloadThree(loadlen)
#     # generateWorkloadFour(loadlen)
#     # generateWorkloadFive(loadlen)



# if __name__ == "__main__":
#     main(50, 10000000)


import random

uniqueNumbers = []
blocks = []

def generateWorkloadOne(loadlen, sortedness):
    file = open("./load/workloadOne.txt", "w")

    global blocks
    random.shuffle(blocks)

    for i in range(len(uniqueNumbers)):
        block = []
        for _ in range(int(blocks[i])):
            block.append(uniqueNumbers[i])
        if sortedness > 0:
            block.sort()
            if sortedness < 100:
                pivot = int((sortedness / 100.0) * len(block))
                left = block[:pivot]
                right = block[pivot:]
                right.sort(reverse=True)
                block = left + right
        for j in block:
            file.write(str(j) + "\n")

    file.close()
    file = open("./metadata/workload.txt", "w")
    file.write("Length of Load : " + str(loadlen) + "\n")
    file.write("Sortedness : " + str(sortedness) + "\n")

    file.write("Workload One: \n")
    for i in range(len(uniqueNumbers)):
        file.write(str(int((blocks[i]))) + " " + str(uniqueNumbers[i]) + " ")
    file.write("\n")
    file.close() 

def main(n, loadlen, sortedness):
    for i in range(1, n + 1):
        uniqueNumbers.append(i)

    global blocks

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

    generateWorkloadOne(loadlen, sortedness)
   

if __name__ == "__main__":
    main(50, 10000000, 50)
