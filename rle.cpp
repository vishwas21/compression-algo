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
        res.push_back({arr[i], count});
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::endl;
    std::cout << "Run Length Encoding Algorithm: " << std::endl;
    std::cout << "Length : " << res.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * res.size())) << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns" << std::endl;

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


vector<int> rleDriver(vector<int>& data) { 

    vector<pair<int, int> > encoded = rle(data);
    vector<int> decoded = rld(encoded);

    double compressionRatio = (double)data.size() / (double)encoded.size();
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    return decoded;
}
