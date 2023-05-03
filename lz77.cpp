#include <chrono>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Triple {
    int distance, length, next_char;

    Triple(int d, int l, int c) : distance(d), length(l), next_char(c) {}

    Triple() {}
};

vector<Triple> lz77_compress(const vector<int>& input) {
    vector<Triple> output;
    int inputLength = input.size();
    int pos = 0;
    while (pos < inputLength) {
        int maxMatchOffset = -1;
        int maxMatchLength = -1;
        for (int i = 1; i <= pos; i++) {
            int matchLength = 0;
            while (pos + matchLength < inputLength && input[pos + matchLength] == input[pos - i + matchLength]) {
                matchLength++;
            }
            if (matchLength > maxMatchLength) {
                maxMatchLength = matchLength;
                maxMatchOffset = i;
            }
        }
        if (maxMatchLength > 0) {
            Triple token;
            token.distance = maxMatchOffset;
            token.length = maxMatchLength;
            token.next_char = input[pos + maxMatchLength];
            output.push_back(token);
            pos += maxMatchLength + 1;
        } else {
            Triple token;
            token.distance = 0;
            token.length = 0;
            token.next_char = input[pos];
            output.push_back(token);
            pos++;
        }
    }
    return output;
}


vector<int> lz77_decompress(const vector<Triple>& input) {
    vector<int> output;
    for (const auto& t : input) {
        int pos = output.size() - t.distance;
        int len = t.length;
        int c = t.next_char;
        for (int i = 0; i < len; i++) {
            output.push_back(output[pos + i]);
        }
        output.push_back(c);
    }
    return output;
}

vector<int> lz77Driver(vector<int>& input) {

    auto start_time = std::chrono::high_resolution_clock::now();
    vector<Triple> compressed = lz77_compress(input);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns" << std::endl;

    vector<int> decompressed(lz77_decompress(compressed));

    double compressionRatio =  ((double)compressed.size() / (double)input.size()) * 100;
    std::cout << "Compression ratio: " << compressionRatio << std::endl;


    return decompressed;
}
