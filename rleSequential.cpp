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
   for(int i=5890; i < 6234; i++)
   std::cout << a.at(i) << ' ';
}

void printPairs(const vector<pair<int, int> >& pairs) {
    for (const auto& p : pairs) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
}

std::vector<std::pair<int, int> > rle(std::vector<int>& arr) {
    auto start_time = std::chrono::high_resolution_clock::now();
    std::vector<std::pair<int, int> > res;
    int n = arr.size();
    if (n == 0) {
        return res;
    }
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i-1]+1) {
            count++;
        } else {
            res.push_back({arr[i-1]-count+1, count});
            count = 1;
        }
    }
    res.push_back({arr[n-1]-count+1, count});

    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::endl;
    std::cout << "Run Length Encoding Algorithm: " << std::endl;
    std::cout << "Length : " << res.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * res.size())) << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns" << std::endl;

    return res;
}

std::vector<int> rld(std::vector<std::pair<int, int> >& pairs) {
    std::vector<int> res;
    for (auto p : pairs) {
        int start = p.first;
        int length = p.second;
        for (int i = start; i < start+length; i++) {
            res.push_back(i);
        }
    }
    return res;
}



// Function to calculate accuracy, precision, and recall of RLE
void calculateMetrics(vector<int>& originalData, vector<int>& uncompressedData) {
    int originalSize = originalData.size();
    int uncompressedSize = uncompressedData.size();
    double mse = 0.0;
    for (int i = 0; i < originalSize; ++i) {
        mse += std::pow((double)originalData[i] - (double)uncompressedData[i], 2.0);
    }
    mse /= (double)originalSize;
    double psnr;
    if (mse == 0.0) {
        psnr = 100.0;
    } else {
        psnr = 20.0 * std::log10(255.0 / std::sqrt(mse));
    }
    std::cout << "PSNR: " << psnr << " dB" << std::endl;

    int matchedCount = 0;
    for(int i = 0; i < originalSize; ++i) {
        if(originalData[i] == uncompressedData[i]) {
            matchedCount ++;
        }
    }

    double accuracy = ((double)matchedCount / originalSize) * 100;
    std::cout << "Accuracy : " << accuracy << "%" << std::endl;
}

int main(int argc, char **argv) {
    // Example usage
    std::string input_file;

    input_file = "./workloadgen/sortedload/workload_N5000000_K1_L100.txt";

    std::ifstream infile(input_file);
    std::vector<int> data;

    int num;
    while (infile >> num) {
        data.push_back(num);
    }

    infile.close();

    std::cout << std::endl << std::endl;
    std::cout << "Input Data " << std::endl;
    std::cout << "Length : " << data.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * data.size())) << std::endl;

    vector<pair<int, int> > encoded = rle(data);

    // printPairs(encoded);

    vector<int> decoded = rld(encoded);

    double compressionRatio = (double)data.size() / (double)encoded.size();
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    calculateMetrics(data, decoded);

    return 0;
}
