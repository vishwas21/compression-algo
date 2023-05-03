#include <iostream>
#include <vector>

#include <chrono>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <sstream>


#include "lz4.h"

using namespace std;

// void compress(const std::vector<int>& input, std::vector<char>& output) {
//     int uncompressed_size = input.size() * sizeof(int);
//     int max_compressed_size = LZ4_compressBound(uncompressed_size);
//     output.resize(max_compressed_size);

//     int compressed_size = LZ4_compress_fast(
//         reinterpret_cast<const char*>(input.data()), output.data(),
//         uncompressed_size, max_compressed_size, 1
//     );

//     if (compressed_size <= 0) {
//         throw std::runtime_error("compression error");
//     }

//     output.resize(compressed_size);
// }

// void decompress(const std::vector<char>& input, std::vector<int>& output) {
//     int uncompressed_size = output.size() * sizeof(int);
//     int decompressed_size = LZ4_decompress_safe(
//         input.data(), reinterpret_cast<char*>(output.data()),
//         input.size(), uncompressed_size
//     );

//     if (decompressed_size <= 0) {
//         throw std::runtime_error("decompression error");
//     }

//     output.resize(decompressed_size / sizeof(int));
// }

void calculateMetrics(std::vector<int>& originalData, std::vector<int>& uncompressedData) {
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

int main() {
    // Sorted integer data
    std::vector<int> input = {1, 2, 2, 3, 3, 3, 4, 4, 5, 6, 7, 8, 9, 10};

    // Compute input size and allocate input buffer
    const size_t input_size = input.size() * sizeof(int);
    std::unique_ptr<char[]> input_data(new char[input_size]);

    // Copy sorted integer data to input buffer
    std::memcpy(input_data.get(), input.data(), input_size);

    // Compute maximum compressed size and allocate compressed buffer
    const size_t max_compressed_size = LZ4_compressBound(input_size);
    std::unique_ptr<char[]> compressed_data(new char[max_compressed_size]);

    // Compress the input data
    const auto compressed_size = LZ4_compress_default(input_data.get(), compressed_data.get(), input_size, max_compressed_size);

    // Check if compression succeeded
    if (compressed_size > 0) {
        std::cout << "Compressed size: " << compressed_size << std::endl;
        // ...
    } else {
        std::cerr << "Compression failed" << std::endl;
    }

    return 0;
}

