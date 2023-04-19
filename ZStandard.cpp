#include <fstream>
#include <iostream>
#include <vector>
#include "zstd.h"

void compress(const std::string& in_filename, const std::string& out_filename) {
  // Read the input file into a buffer
  std::ifstream in_file(in_filename, std::ios::binary);
  std::vector<char> in_buf(std::istreambuf_iterator<char>(in_file), {});

  // Create an output file and write the compressed data to it
  std::ofstream out_file(out_filename, std::ios::binary);
  const size_t max_compressed_size = ZSTD_compressBound(in_buf.size());
  std::vector<char> out_buf(max_compressed_size);
  const size_t compressed_size = ZSTD_compress(out_buf.data(), max_compressed_size, in_buf.data(), in_buf.size(), ZSTD_maxCLevel());
  out_file.write(out_buf.data(), compressed_size);
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

int main() {
  const std::string input_filename = "./workload/data_1000000-elems_1-kperct_1-lperct_1seed1681108605.dat";
  const std::string compressed_filename = "compressed.dat";
  const std::string decompressed_filename = "decompressed.dat";

  // Compress the input file
  compress(input_filename, compressed_filename);

  std::cout << "Ran Compress";

  // Decompress the compressed file
  decompress(compressed_filename, decompressed_filename);

  std::cout << "Ran Decompress";

  std::ifstream og_file(input_filename, std::ios::binary);
  og_file.seekg(0, std::ios::end);
  int file_size = og_file.tellg();
  std::cout << "Size of the og file is " << " " << file_size << " " << "bytes" << std::endl;

  std::ifstream cm_file(compressed_filename, std::ios::binary);
  cm_file.seekg(0, std::ios::end);
  file_size = cm_file.tellg();
  std::cout << "Size of the cm file is " << " " << file_size << " " << "bytes" << std::endl;

  std::ifstream dcm_file(decompressed_filename, std::ios::binary);
  dcm_file.seekg(0, std::ios::end);
  file_size = dcm_file.tellg();
  std::cout << "Size of the dcm file is " << " " << file_size << " " << "bytes" << std::endl;
}
