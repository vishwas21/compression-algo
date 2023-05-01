#include <iostream>
#include <vector>
#include "lz4.h"

void compress(const std::vector<int>& input, std::vector<char>& output) {
    int uncompressed_size = input.size() * sizeof(int);
    int max_compressed_size = LZ4_compressBound(uncompressed_size);
    output.resize(max_compressed_size);

    int compressed_size = LZ4_compress_fast(
        reinterpret_cast<const char*>(input.data()), output.data(),
        uncompressed_size, max_compressed_size, 1
    );

    if (compressed_size <= 0) {
        throw std::runtime_error("compression error");
    }

    output.resize(compressed_size);
}

void decompress(const std::vector<char>& input, std::vector<int>& output) {
    int uncompressed_size = output.size() * sizeof(int);
    int decompressed_size = LZ4_decompress_safe(
        input.data(), reinterpret_cast<char*>(output.data()),
        input.size(), uncompressed_size
    );

    if (decompressed_size <= 0) {
        throw std::runtime_error("decompression error");
    }

    output.resize(decompressed_size / sizeof(int));
}

int main() {
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<char> compressed;
    std::vector<int> decompressed;

    // compress the input
    compress(input, compressed);

    // decompress the compressed data
    decompressed.resize(input.size());
    decompress(compressed, decompressed);

    // check if the decompressed data matches the input
    if (input != decompressed) {
        std::cerr << "decompression error: data mismatch" << std::endl;
        return 1;
    }

    std::cout << "data compressed from " << input.size() * sizeof(int) << " bytes to "
              << compressed.size() << " bytes" << std::endl;

    return 0;
}
