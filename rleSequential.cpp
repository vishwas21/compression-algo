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

std::vector<std::pair<int, int> > rles(std::vector<int>& arr) {
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

std::vector<int> rlds(std::vector<std::pair<int, int> >& pairs) {
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

vector<int> rleSequentialDriver(vector<int> data) {

    vector<pair<int, int> > encoded = rles(data);

    vector<int> decoded = rlds(encoded);

    double compressionRatio =  ((double)encoded.size() / (double)data.size()) * 100;
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    return decoded;
}
