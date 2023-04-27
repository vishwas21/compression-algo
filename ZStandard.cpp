#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include "zstd.h"

void compress(const std::string& in_filename, const std::string& out_filename) {
  auto start_time = std::chrono::high_resolution_clock::now();

  // Read the input file into a buffer
  std::ifstream in_file(in_filename, std::ios::binary);
  std::vector<char> in_buf(std::istreambuf_iterator<char>(in_file), {});

  // Create an output file and write the compressed data to it
  std::ofstream out_file(out_filename, std::ios::binary);
  const size_t max_compressed_size = ZSTD_compressBound(in_buf.size());
  std::vector<char> out_buf(max_compressed_size);
  const size_t compressed_size = ZSTD_compress(out_buf.data(), max_compressed_size, in_buf.data(), in_buf.size(), ZSTD_maxCLevel());
  auto end_time = std::chrono::high_resolution_clock::now();
  out_file.write(out_buf.data(), compressed_size);

  std::cout << std::endl << std::endl;
    std::cout << "ZStandard Compression Algorithm: " << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count() << " ns" << std::endl;
}

void decompress(const std::string& in_filename, const std::string& out_filename) {
  // Read the input file into a buffer
  std::ifstream in_file(in_filename, std::ios::binary);
  std::vector<char> in_buf(std::istreambuf_iterator<char>(in_file), {});

  // Determine the size of the decompressed data
  const size_t decomp_size = ZSTD_getFrameContentSize(in_buf.data(), in_buf.size());

  // Create an output file and write the decompressed data to it
  std::ofstream out_file(out_filename, std::ios::binary);
  std::vector<char> out_buf(decomp_size);
  const size_t decompressed_size = ZSTD_decompress(out_buf.data(), decomp_size, in_buf.data(), in_buf.size());
  out_file.write(out_buf.data(), decompressed_size);
}

// Function to calculate accuracy, precision, and recall of RLE
void calculateMetrics(std::vector<int>& originalData, std::vector<int>& uncompressedData) {
    int originalSize = originalData.size();
    int uncompressedSize = uncompressedData.size();
    double mse = 0.0;
    for (int i = 0; i < originalSize; ++i) {
        mse += std::pow((double)originalData[i] - (double)uncompressedData[i], 2.0);
    }
    mse /= (double)originalSize;
    // double psnr;
    // if (mse == 0.0) {
    //     psnr = 100.0;
    // } else {
    //     psnr = 20.0 * std::log10(255.0 / std::sqrt(mse));
    // }
    // std::cout << "PSNR: " << psnr << " dB" << std::endl;

    int matchedCount = 0;
    for(int i = 0; i < originalSize; ++i) {
        if(originalData[i] == uncompressedData[i]) {
            matchedCount ++;
        }
    }

    double accuracy = ((double)matchedCount / originalSize) * 100;
    std::cout << "Accuracy : " << accuracy << "%" << std::endl;
}

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

int main() {
  const std::string input_filename = "./workloadgen/load/workloadUQuadDist.txt";
  const std::string compressed_filename = "compressed.dat";
  const std::string decompressed_filename = "decompressed.dat";

  // Compress the input file
  compress(input_filename, compressed_filename);

  std::cout << "Ran Compress" << std::endl;

  // Decompress the compressed file
  decompress(compressed_filename, decompressed_filename);

  std::cout << "Ran Decompress" << std::endl;

  std::ifstream og_file(input_filename, std::ios::binary);
  og_file.seekg(0, std::ios::end);
  int og_size = og_file.tellg();
  std::cout << "Size of the og file is " << " " << og_size << " " << "bytes" << std::endl;

  std::ifstream cm_file(compressed_filename, std::ios::binary);
  cm_file.seekg(0, std::ios::end);
  int cm_size = cm_file.tellg();
  std::cout << "Size of the cm file is " << " " << cm_size << " " << "bytes" << std::endl;

  std::ifstream dcm_file(decompressed_filename, std::ios::binary);
  dcm_file.seekg(0, std::ios::end);
  int dcm_size = dcm_file.tellg();
  std::cout << "Size of the dcm file is " << " " << dcm_size << " " << "bytes" << std::endl;

  std::vector<int> input = read_file(input_filename);
  std::vector<int> decompressed = read_file(decompressed_filename);

  double compressionRatio = (double)og_size / (double)cm_size;
  std::cout << "Compression ratio: " << compressionRatio << std::endl;

  calculateMetrics(input, decompressed);
}
