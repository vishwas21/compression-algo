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
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns" << std::endl;
}

void delta_decompress(std::vector<int>& data) {
    for (int i = 1; i < data.size(); i++) {
        data[i] += data[i - 1];
    }
}

void calculateMetrics(std::vector<int>& originalData, std::vector<int>& uncompressedData) {
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


int main() {
    std::string input_file;

    input_file = "./workloadgen/load/workloadScaleFour.txt";
    // input_file = "./workloadgen/sortedload/workload_N5000000_K100_L100.txt";

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
    double compressionRatio = (double)original.size() / (double)data.size();
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    // Decompress the data
    delta_decompress(data);

    calculateMetrics(original, data);
    
    return 0;
}
