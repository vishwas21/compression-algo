#include <fstream>
#include <vector>
#include <iostream>
#include <random>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>
#include <string>
#include <unordered_map>

double measure_compression_ratio(const std::vector<int>& input_sequence, const std::vector<int>& compressed_sequence) {
    double input_size = input_sequence.size() * sizeof(int);
    double output_size = compressed_sequence.size() * sizeof(int);
    return input_size / output_size;
}

void print(std::vector <int> const &a) {
   for(int i=0; i < 1000; i++)
   std::cout << a.at(i) << ' ';
}

void delta_compress(std::vector<int>& data) {
    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = data.size() - 1; i > 0; i--) {
        data[i] -= data[i - 1];
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::endl;
    std::cout << "Delta Algorithm: " << std::endl;
    std::cout << "Length : " << data.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * data.size())) << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " ms" << std::endl;
}

void delta_decompress(std::vector<int>& data) {
    for (int i = 1; i < data.size(); i++) {
        data[i] += data[i - 1];
    }
}

// Function to calculate accuracy, precision, and recall of RLE
void calculateMetrics(std::vector<int>& original, std::vector<int>& decoded) {
    int n = original.size();
    int m = decoded.size();

    int TP = 0; // true positives
    int FP = 0; // false positives
    int TN = 0; // true negatives
    int FN = 0; // false negatives

    for (int i = 0; i < n; i++) {
        if (i < m && original[i] == decoded[i]) {
            TP++;
        } else {
            FN++;
        }
    }

    for (int i = 0; i < m; i++) {
        if (i >= n || original[i] != decoded[i]) {
            FP++;
        } else {
            TN++;
        }
    }

    double accuracy = 100.0 * (double)(TP + TN) / (TP + FP + TN + FN);
    double precision = 100.0 * (double)TP / (TP + FP);
    double recall = 100.0 * (double)TP / (TP + FN);

    std::cout << "Accuracy: " << accuracy << "%" << std::endl;
    std::cout << "Precision: " << precision << "%" << std::endl;
    std::cout << "Recall: " << recall << "%" << std::endl;
}


int main() {
    std::string input_file;

    input_file = "./workloadgen/load/workloadFive.txt";

    std::ifstream infile(input_file);
    std::vector<int> data;

    int num;
    while (infile >> num) {
        data.push_back(num);
    }

    infile.close();

    std::cout << std::endl << std::endl;
    std::cout << "Input Sequence : " << std::endl;
    std::cout << "Length : " << data.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * data.size())) << std::endl;

    std::vector<int> original(data);

    // Compress the data
    delta_compress(data);
    // std::cout << "Compressed data: ";
    // for (int val : data) {
    //     std::cout << val << " ";
    // }
    // std::cout << std::endl;

    // Decompress the data
    delta_decompress(data);

    calculateMetrics(original, data);
    
    return 0;
}
