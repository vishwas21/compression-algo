#include "lz4.h"
#include <vector>
#include <iostream>

void compress(const std::vector<int>& numbers, std::vector<char>& compressed) {
    // Compress the vector using LZ4
    compressed.resize(LZ4_compressBound(numbers.size() * sizeof(int)));
    int compressed_size = LZ4_compress_default((const char*)numbers.data(), compressed.data(), numbers.size() * sizeof(int), compressed.size());

    // Resize the compressed vector to the actual compressed size
    compressed.resize(compressed_size);
}

void decompress(const std::vector<char>& compressed, std::vector<int>& numbers) {
    // Calculate the maximum possible uncompressed size
    int uncompressed_size = LZ4_decompress_safe_max_input_size(compressed.size(), LZ4_MAX_INPUT_SIZE);

    // Allocate a buffer for the uncompressed data
    std::vector<char> uncompressed(uncompressed_size);

    // Decompress the data
    int decompressed_size = LZ4_decompress_safe(compressed.data(), uncompressed.data(), compressed.size(), uncompressed.size());

    // Resize the numbers vector to hold the uncompressed data
    numbers.resize(decompressed_size / sizeof(int));

    // Copy the uncompressed data into the numbers vector
    std::memcpy(numbers.data(), uncompressed.data(), decompressed_size);
}

int main() {
    // Generate a vector of large integers that are nearly sorted
    std::vector<int> numbers;
    for (int i = 0; i < 1000000; i++) {
        numbers.push_back(i + rand() % 10 - 5);
    }

    // Compress the vector using LZ4
    std::vector<char> compressed;
    compress(numbers, compressed);

    // Decompress the compressed data
    std::vector<int> decompressed;
    decompress(compressed, decompressed);

    // Verify that the original and decompressed vectors are equal
    bool equal = (numbers == decompressed);
    std::cout << "Original and decompressed vectors are " << (equal ? "equal" : "not equal") << std::endl;

    return 0;
}
