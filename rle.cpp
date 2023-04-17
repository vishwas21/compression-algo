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

using namespace std;

double measure_compression_ratio(const std::vector<int>& input_sequence, const std::vector<int>& compressed_sequence) {
    double input_size = input_sequence.size() * sizeof(int);
    double output_size = compressed_sequence.size() * sizeof(int);
    return input_size / output_size;
}

void print(std::vector <int> const &a) {
   for(int i=104770; i < 104970; i++)
   std::cout << a.at(i) << ' ';
}

// Function to perform run-length encoding
vector<pair<int, int> > rle(vector<int>& arr) {
    auto start_time = std::chrono::high_resolution_clock::now();
    int n = arr.size();

    vector<pair<int, int> > res;

    for (int i = 0; i < n; i++) {
        int count = 1;
        while (i < n - 1 && arr[i] == arr[i+1]) {
            count++;
            i++;
        }
        res.push_back({ arr[i], count});
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::endl;
    std::cout << "Run Length Encoding Algorithm: " << std::endl;
    std::cout << "Length : " << res.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * res.size())) << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " ms" << std::endl;

    return res;
}

// Function to perform run-length decoding
vector<int> rld(vector<pair<int, int> >& arr) {
    vector<int> res;
    for (auto p : arr) {
        for (int i = 0; i < p.second; i++) {
            res.push_back(p.first);
        }
    }
    return res;
}

// Function to calculate accuracy, precision, and recall of RLE
void calculateMetrics(vector<int>& original, vector<int>& decoded) {
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

    cout << "Accuracy: " << accuracy << "%" << endl;
    cout << "Precision: " << precision << "%" << endl;
    cout << "Recall: " << recall << "%" << endl;
}

int main(int argc, char **argv) {
    // Example usage
    std::string input_file;

    input_file = "./workloadgen/load/workloadOne.txt";

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
    vector<pair<int, int> > encoded = rle(data);
    cout << "Encoded: ";
    for (auto p : encoded) {
        cout << "(" << p.first << ", " << p.second << ") ";
    }
    cout << endl;

    vector<int> decoded = rld(encoded);


    calculateMetrics(data, decoded);

    return 0;
}
