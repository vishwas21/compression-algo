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

std::vector<int>& deltaDriver(std::vector<int>& data) {

    std::vector<int> original(data);

    // Compress the data
    delta_compress(data);
    double compressionRatio =  ((double)data.size() / (double)original.size()) * 100;
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    // Decompress the data
    delta_decompress(data);
    
    return data;
}
