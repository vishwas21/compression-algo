# Compression Algorithms

RLE
Delta
Snappy
Zstandard
LZ77

### Workloads

Frequency Worloads

-   Uniform Distrubution
-   U Quadratic Distrubution
-   Normal Distrubution
-   Local Disorder
-   Global Disorder
-   Normal Order

Scalabity Workloads

-   400 KB
-   4 MB
-   40 MB
-   400 MB

K-L Workloads

-   values of K and L ranges from 0, 1 , 5, 10 , 25, 50, 100

## Execution

The exceution of this is implemented in two ways :

-   Command Line Arguments
-   Using the Menu options

1.  Command Line Arguments :
    ./main -A "option" -T "option" -W "option"

2.  Using menu options : <br />

        Please choose one algorithm to run :<br />
        Algorithm 1: Run Length Encoding (RLE)<br />
        Algorithm 2: Delta Compression<br />
        Algorithm 3: LZ77 Compression<br />
        Algorithm 4: Google's Snappy Compression<br />
        Algorithm 5: Meta's ZStandard<br />
        Which algorithm would you like to test? 5<br />

        Below are the types of tests which we have designed :<br />
        Test Type 1: Frequency Distribution Tests<br />
        Test Type 2: K-L Sortedness Tests<br />
        Test Type 3: Scalability Tests<br />
        Which test would you like to run? 2<br />

        Please choose a workload to run:<br />
        Workload 1: K = 100 & L = 1<br />
        Workload 2: K = 50 & L = 1<br />
        Workload 3: K = 25 & L = 1<br />
        Workload 4: K = 10 & L = 1<br />
        Workload 5: K = 5 & L = 1<br />
        Workload 6: K = 1 & L = 1<br />
        Workload 7: K = 0 & L = 0<br />
        Workload 8: K = 1 & L = 5<br />
        Workload 9: K = 1 & L = 10<br />
        Workload 10: K = 1 & L = 25<br />
        Workload 11: K = 1 & L = 50<br />
        Workload 12: K = 1 & L = 100<br />
        Workload 13: K = 100 & L = 100<br />
        Which workload would you like to use? 3<br />

        Input Data<br />
        Length : 5000000<br />
        Size : 20000024<br />

    <br />
        ZStandard Compression Results:<br />
    <br />
        ZStandard Algorithm:<br />
        Length : 20078125<br />
        Size : 54025416<br />
        Time : 181334500 ns<br />
    <br />
        Original size: 20000000<br />
        Compressed size: 13506348<br />
        Compression ratio: 1080.51<br />
        Accuracy : 100%<br />
    <br />
        Would you like to run more tests? (y/N) :<br />

### Code

    1. workloadgen.py - used to generate the frequency and scalability workloads. Code is written in python.
    2. K-L workloads are generated using BoDS workload generator code.
    2. All compression algorithm codes are written in cpp.

### Commands used for indivual code execution

Commands:

Workload Generator

-   python3 ./workloadgen/workgen.py

Main Driver

-   make clear && make main && ./main

or

-   make clear && make main && ./main -A "AlgorithmNumber" -T "Test Type Number" -W "Workload Number"

## Main Driver

This program is designed to test different compression algorithms and compare their performance on different types of data sets. The program allows you to select from different test types, experiment options, and compression algorithms.

The available compression algorithms are:

1. Run Length Encoding (RLE)
2. Delta Compression
3. LZ77 Compression
4. Google's Snappy Compression
5. Meta's ZStandard

Test Types
The available test types are:

1. Frequency Distribution Tests
2. K-L Sortedness Tests
3. Scalability Tests

Experiment Options for Frequency Distribution Tests <br>
The available experiment options for Frequency Distribution Tests are: <br>

1. Uniform Distribution
2. Normal Distribution
3. U Quadratic/Parabolic Distribution
4. Random Workload
5. Local Disorder Workload
6. Global Disorder Workload

Experiment Options for Scalability Tests <br>
The available experiment options for Scalability Tests are:<br>

1. Workload Size: 400 Kb
2. Workload Size: 4 Mb
3. Workload Size: 40 Mb
4. Workload Size: 400 Mb

Experiment Options for K-L Sortedness Tests <br>
The available experiment options for K-L Sortedness Tests are: <br>

1. K = 100 & L = 1
2. K = 50 & L = 1
3. K = 25 & L = 1
4. K = 10 & L = 1
5. K = 5 & L = 1
6. K = 1 & L = 1
7. K = 0 & L = 0
8. K = 1 & L = 5
9. K = 1 & L = 10
10. K = 1 & L = 25
11. K = 1 & L = 50
12. K = 1 & L = 100
13. K = 100 & L = 100

To run the program, simply select the compression algorithm you want to test, followed by the test type and experiment option. The program will then perform the selected test and provide you with the results.

Note that the program assumes that the data sets to be compressed are located in the same directory as the program. If your data sets are located elsewhere, you will need to update the file paths accordingly.
