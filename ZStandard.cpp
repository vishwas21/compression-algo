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

std::vector<int> zStandardDriver(std::vector<int>& nums) {

    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<char> compressed(ZSTD_compressBound(nums.size() * sizeof(int)));
    size_t compressed_size = ZSTD_compress(compressed.data(), compressed.size(), nums.data(), nums.size() * sizeof(int), ZSTD_maxCLevel());

    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::endl;
    std::cout << "ZStandard Algorithm: " << std::endl;
    std::cout << "Length : " << compressed_size << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * compressed_size)) << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns" << std::endl;

    // Output compression ratio
    std::cout << "Original size: " << nums.size() * sizeof(int) << std::endl;
    std::cout << "Compressed size: " << compressed_size << std::endl;
    std::cout << "Compression ratio: " << (double)nums.size() * sizeof(int) / compressed_size << std::endl;

    // Decompress the compressed data
    std::vector<int> decompressed(nums.size());
    size_t decompressed_size = ZSTD_decompress(decompressed.data(), decompressed.size() * sizeof(int), compressed.data(), compressed_size);

    std::vector<int> decoded(decompressed);
    
    return decoded;
}
