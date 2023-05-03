#include <iostream>
#include <vector>
#include "zstd.h"

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

std::vector<int> read_file(const std::string& filename) {
  // Open the input file
  std::ifstream in_file(filename, std::ios::binary);
  if (!in_file) {
    throw std::runtime_error("Could not open file " + filename);
  }

  // Read the contents of the file into a vector
  std::vector<int> data((std::istreambuf_iterator<char>(in_file)),
                         std::istreambuf_iterator<char>());

  // Return the vector
  return data;
}

std::vector<int> zStandardDriver(std::vector<int>& input_data) {

    // Sort input data
    std::sort(input_data.begin(), input_data.end());

    auto start_time = std::chrono::high_resolution_clock::now();

    // Compress input data
    const size_t input_size = input_data.size() * sizeof(int);
    const size_t max_compressed_size = ZSTD_compressBound(input_size);
    std::vector<char> compressed_data(max_compressed_size);
    const size_t compressed_size = ZSTD_compress(compressed_data.data(), max_compressed_size, input_data.data(), input_size, 1);

    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::endl;
    std::cout << "ZStandard Algorithm: " << std::endl;
    std::cout << "Length : " << compressed_data.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * compressed_size)) << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns" << std::endl;

    std::cout << std::endl;

    // Output compression ratio
    std::cout << "Original size: " << input_data.size() * sizeof(int) << std::endl;
    std::cout << "Compressed size: " << compressed_size << std::endl;
    std::cout << "Compression ratio: " << (compressed_size / (double)input_data.size() * sizeof(int)) * 100 << std::endl;


    // Decompress compressed data
    std::vector<int> decompressed_data(input_data.size());
    const size_t decompressed_size = ZSTD_decompress(decompressed_data.data(), input_size, compressed_data.data(), compressed_size);

    std::vector<int> decoded(decompressed_data);
    
    return decoded;
}
