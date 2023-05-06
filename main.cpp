#include <iostream>
#include <map>
#include <chrono>
#include <vector>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "args.hxx"

#include "rle.cpp"
#include "rleSequential.cpp"
#include "delta.cpp"
#include "lz77.cpp"
#include "Snappy.cpp"
#include "ZStandard.cpp"

using namespace std;

// Function to calculate compression ratio
double measure_compression_ratio(const std::vector<int>& input_sequence, const std::vector<int>& compressed_sequence) {
    double input_size = input_sequence.size() * sizeof(int);
    double output_size = compressed_sequence.size() * sizeof(int);
    return input_size / output_size;
}

// Function to calculate accuracy, precision, and recall of RLE
void calculateMetrics(vector<int>& originalData, vector<int>& uncompressedData) {
    int originalSize = originalData.size();
    int uncompressedSize = uncompressedData.size();

    int matchedCount = 0;
    for(int i = 0; i < originalSize; ++i) {
        if(originalData[i] == uncompressedData[i]) {
            matchedCount ++;
        }
    }

    double accuracy = ((double)matchedCount / originalSize) * 100;
    std::cout << "Accuracy : " << accuracy << "%" << std::endl;
}

std::vector<int> readInputData(string inputDataPath) {
    std::ifstream infile(inputDataPath);
    std::vector<int> data;

    int num;
    while (infile >> num) {
        data.push_back(num);
    }

    infile.close();

    return data;
}

int mainDriver(int selectedAlgo, int selectedTestType, string selectedWorkloadPath) {

    vector<int> originalData;
    vector<int> decoded;

    if (selectedAlgo == 4) {
        cout << endl << endl << "Snappy Compression Results: " << endl;
        snappyDriver(selectedWorkloadPath);
    } else {
        originalData = readInputData(selectedWorkloadPath);

        std::cout << std::endl << std::endl;
        std::cout << "Input Data " << std::endl;
        std::cout << "Length : " << originalData.size() << std::endl;
        std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * originalData.size())) << std::endl;

        if (selectedAlgo == 1) {
            cout << endl << endl << "Run Length Encoding Results: " << endl;
            if(selectedTestType == 1 || selectedTestType == 3) {
                decoded = rleDriver(originalData);
            } else {
                decoded = rleSequentialDriver(originalData);
            }
        } else if (selectedAlgo == 2) {
            cout << endl << endl << "Delta Compression Results: " << endl;
            decoded = deltaDriver(originalData);
        } else if (selectedAlgo == 3) {
            cout << endl << endl << "LZ77 Compression Results: " << endl;
            decoded = lz77Driver(originalData);
        } else if (selectedAlgo == 5) {
            cout << endl << endl << "ZStandard Compression Results: " << endl;
            decoded = zStandardDriver(originalData);
        }
        calculateMetrics(originalData, decoded);

        return 0;
    } 
    return 1;

}

int main(int argc, char **argv) {

    // Different possible algorithms
    map<int, string> algoMenu;

    algoMenu[1] = "Run Length Encoding (RLE)";
    algoMenu[2] = "Delta Compression";
    algoMenu[3] = "LZ77 Compression";
    algoMenu[4] = "Google's Snappy Compression";
    algoMenu[5] = "Meta's ZStandard";

    // Frequency Experiment Options
    map<int, string> frequencyMenu;

    frequencyMenu[1] = "Uniform Distribution";
    frequencyMenu[2] = "Normal Distribution";
    frequencyMenu[3] = "U Quadratic/Parabolic Distribution";
    frequencyMenu[4] = "Random Workload";
    frequencyMenu[5] = "Local Disorder Workload";
    frequencyMenu[6] = "Global Disorder Workload";

    map<int, string>  frequencyWorkloadPath;

    frequencyWorkloadPath[1] = "./workloadgen/load/workloadUniformDist.txt";
    frequencyWorkloadPath[2] = "./workloadgen/load/workloadNormalDist.txt";
    frequencyWorkloadPath[3] = "./workloadgen/load/workloadUQuadDist.txt";
    frequencyWorkloadPath[4] = "./workloadgen/load/workloadNormal.txt";
    frequencyWorkloadPath[5] = "./workloadgen/load/workloadLocalDisorder.txt";
    frequencyWorkloadPath[6] = "./workloadgen/load/workloadGlobalDisorder.txt";

    // Scalability Tests Experiment Options
    map<int, string> scaleMenu;

    scaleMenu[1] = "Workload Size: 400 Kb";
    scaleMenu[2] = "Workload Size: 4 Mb";
    scaleMenu[3] = "Workload Size: 40 Mb";
    scaleMenu[4] = "Workload Size: 400 Mb";

    map<int, string>  scaleWorkloadPath;

    scaleWorkloadPath[1] = "./workloadgen/load/workloadScaleOne.txt";
    scaleWorkloadPath[2] = "./workloadgen/load/workloadScaleTwo.txt";
    scaleWorkloadPath[3] = "./workloadgen/load/workloadScaleThree.txt";
    scaleWorkloadPath[4] = "./workloadgen/load/workloadScaleFour.txt";

    // K-L Workload Experiment Options

    map<int, string> klWorkloadMenu;

    klWorkloadMenu[1] = "K = 100 & L = 1";
    klWorkloadMenu[2] = "K = 50 & L = 1";
    klWorkloadMenu[3] = "K = 25 & L = 1";
    klWorkloadMenu[4] = "K = 10 & L = 1";
    klWorkloadMenu[5] = "K = 5 & L = 1";
    klWorkloadMenu[6] = "K = 1 & L = 1";
    klWorkloadMenu[7] = "K = 0 & L = 0";
    klWorkloadMenu[8] = "K = 1 & L = 5";
    klWorkloadMenu[9] = "K = 1 & L = 10";
    klWorkloadMenu[10] = "K = 1 & L = 25";
    klWorkloadMenu[11] = "K = 1 & L = 50";
    klWorkloadMenu[12] = "K = 1 & L = 100";
    klWorkloadMenu[13] = "K = 100 & L = 100";

    map<int, string> klWorkloadPath;

    klWorkloadPath[1] = "./workloadgen/sortedload/workload_N5000000_K100_L1.txt";
    klWorkloadPath[2] = "./workloadgen/sortedload/workload_N5000000_K50_L1.txt";
    klWorkloadPath[3] = "./workloadgen/sortedload/workload_N5000000_K25_L1.txt";
    klWorkloadPath[4] = "./workloaydgen/sortedload/workload_N5000000_K10_L1.txt";
    klWorkloadPath[5] = "./workloadgen/sortedload/workload_N5000000_K5_L1.txt";
    klWorkloadPath[6] = "./workloadgen/sortedload/workload_N5000000_K1_L1.txt";
    klWorkloadPath[7] = "./workloadgen/sortedload/workload_N5000000_K0_L0.txt";
    klWorkloadPath[8] = "./workloadgen/sortedload/workload_N5000000_K1_L5.txt";
    klWorkloadPath[9] = "./workloadgen/sortedload/workload_N5000000_K1_L10.txt";
    klWorkloadPath[10] = "./workloadgen/sortedload/workload_N5000000_K1_L25.txt";
    klWorkloadPath[11] = "./workloadgen/sortedload/workload_N5000000_K1_L50.txt";
    klWorkloadPath[12] = "./workloadgen/sortedload/workload_N5000000_K1_L100.txt";
    klWorkloadPath[13] = "./workloadgen/sortedload/workload_N5000000_K100_L100.txt";

    int selectedAlgo = 0, selectedTestType = 0, selectedWorkload = 0;
    string selectedWorkloadPath = "";

    if(argc > 2) {
        args::ArgumentParser parser("Sortedness workload generator.");

        args::Group group(parser, "These arguments are REQUIRED as a group:", args::Group::Validators::All);
        args::ValueFlag<int> selected_algo_cmd(group, "A", "Algorithm to test", {'A', "selected_algorithm"});
        args::ValueFlag<int> test_type_cmd(group, "T", "Type of the test", {'T', "test_type"});
        args::ValueFlag<int> workload_num_cmd(group, "W", "Workload Number", {'W', "workload_num"});

        try
        {
            parser.ParseCLI(argc, argv);
            selectedAlgo = args::get(selected_algo_cmd);
            selectedTestType = args::get(test_type_cmd);
            selectedWorkload = args::get(workload_num_cmd);

            if (selectedTestType == 1) {
                selectedWorkloadPath = frequencyWorkloadPath[selectedWorkload];
            } else if (selectedTestType == 2) {
                selectedWorkloadPath = klWorkloadPath[selectedWorkload];
            } else if (selectedTestType == 3) {
                selectedWorkloadPath = scaleWorkloadPath[selectedWorkload];
            }

            mainDriver(selectedAlgo, selectedTestType, selectedWorkloadPath);
        }
        catch (args::Help &)
        {
            std::cout << parser;
            return 0;
        }
        catch (args::ParseError &e)
        {
            std::cerr << e.what() << std::endl;
            std::cerr << parser;
            return 1;
        }
        catch (args::ValidationError &e)
        {
            std::cerr << e.what() << std::endl;
            std::cerr << parser;
            return 1;
        }
        return 0;
    }


    while (true) {

        selectedAlgo = 0;
        selectedTestType = 0;
        selectedWorkload = 0;
        selectedWorkloadPath = "";

        cout << endl << endl << "Please choose one algorithm to run : " << endl;
        for(auto algo: algoMenu) {
            cout << "Algorithm " << algo.first << ": " << algo.second << endl;
        }
        cout << "Which algorithm would you like to test? ";
        cin >> selectedAlgo;

        cout << endl << endl << "Below are the types of tests which we have designed : " << endl;
        cout << "Test Type 1: Frequency Distribution Tests" << endl;
        cout << "Test Type 2: K-L Sortedness Tests" << endl;
        cout << "Test Type 3: Scalability Tests" << endl;
        cout << "Which test would you like to run? ";
        cin >> selectedTestType;

        cout << endl << endl << "Please choose a workload to run: " << endl;
        if (selectedTestType == 1) {
            for(auto freq: frequencyMenu) {
                cout << "Workload " << freq.first << ": " << freq.second << endl;
            }
            cout << "Which workload would you like to use? ";
            cin >> selectedWorkload;
            selectedWorkloadPath = frequencyWorkloadPath[selectedWorkload];
        } else if (selectedTestType == 2) {
            for(auto klFreq: klWorkloadMenu) {
                cout << "Workload " << klFreq.first << ": " << klFreq.second << endl;
            }
            cout << "Which workload would you like to use? ";
            cin >> selectedWorkload;
            selectedWorkloadPath = klWorkloadPath[selectedWorkload];
        } else if (selectedTestType == 3) {
            for(auto scale: scaleMenu) {
                cout << "Workload " << scale.first << ": " << scale.second << endl;
            }
            cout << "Which workload would you like to use? ";
            cin >> selectedWorkload;
            selectedWorkloadPath = scaleWorkloadPath[selectedWorkload];
        }

        mainDriver(selectedAlgo, selectedTestType, selectedWorkloadPath);
        
        // End Condition Code
        cout << endl << "Would you like to run more tests? (y/N) : ";
        char continueChoice;
        cin >> continueChoice;

        if(continueChoice == 'N' || continueChoice == 'n') {
            break;
        }
    }

    return 0;
}
