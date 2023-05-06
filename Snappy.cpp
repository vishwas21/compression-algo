#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#include "snappy-c.h"

int snappyDriver(std::string workloadPath) {
  FILE* fp = fopen(workloadPath.c_str(), "rb");
  if (!fp) {
    printf("Failed to open input file.\n");
    return 1;
  }

  // Determine the size of the input file
  fseek(fp, 0, SEEK_END);
  size_t input_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  // Print the size of the compressed data
  printf("Input size: %zu\n", input_size);

  // Read the input file into a buffer
  uint64_t* input_data = (uint64_t*)malloc(input_size);
  size_t count = fread(input_data, sizeof(uint64_t), input_size / sizeof(uint64_t), fp);
  fclose(fp);

  // Compress the input data using Snappy
  size_t compressed_size = snappy_max_compressed_length(input_size);
  char* compressed_data = (char*)malloc(compressed_size);
  auto start_time = std::chrono::high_resolution_clock::now();
  snappy_status status = snappy_compress((const char*)input_data, count * sizeof(uint64_t), compressed_data, &compressed_size);
  if (status != SNAPPY_OK) {
    printf("Failed to compress data.\n");
    free(input_data);
    free(compressed_data);
    return 1;
  }
  auto end_time = std::chrono::high_resolution_clock::now();

  std::cout << "Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns" << std::endl;

  // Print the size of the compressed data
  printf("Compressed size: %zu\n", compressed_size);

  // Decompress the data
  size_t uncompressed_size = 0;
  status = snappy_uncompressed_length(compressed_data, compressed_size, &uncompressed_size);
  if (status != SNAPPY_OK) {
    printf("Failed to get uncompressed size.\n");
    free(input_data);
    free(compressed_data);
    return 1;
  }

  uint64_t* uncompressed_data = (uint64_t*)malloc(uncompressed_size);
  status = snappy_uncompress(compressed_data, compressed_size, (char*)uncompressed_data, &uncompressed_size);
  if (status != SNAPPY_OK) {
    printf("Failed to uncompress data.\n");
    free(input_data);
    free(compressed_data);
    free(uncompressed_data);
    return 1;
  }

  // Print the size of the compressed data
  printf("Uncompressed size: %zu\n", uncompressed_size);


  // Calculate accuracy, precision
    std::vector<int> originalData(input_data, input_data + input_size / sizeof(uint64_t));
    std::vector<int> uncompressedData(uncompressed_data, uncompressed_data + uncompressed_size / sizeof(uint64_t));
    int originalSize = originalData.size();
    int uncompressedSize = uncompressedData.size();
    double compressionRatio = ((double)compressed_size / (double)input_size) * 100;
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    int matchedCount = 0;
    for(int i = 0; i < originalSize; ++i) {
        if(originalData[i] == uncompressedData[i]) {
            matchedCount ++;
        }
    }

    double accuracy = ((double)matchedCount / originalSize) * 100;
    std::cout << "Accuracy : " << accuracy << "%" << std::endl;

  // Free memory
  free(input_data);
  free(compressed_data);
  free(uncompressed_data);

  return 0;
}
