#include <iostream>
#include <vector>
#include <zstd.h>

using namespace std;

// Compress the input data using zstandard
vector<char> compress(const char* data, size_t size) {
    size_t compressed_size = ZSTD_compressBound(size);
    vector<char> compressed_data(compressed_size);

    size_t actual_size = ZSTD_compress(compressed_data.data(), compressed_size, data, size, ZSTD_maxCLevel());
    if (ZSTD_isError(actual_size)) {
        cerr << "Compression failed: " << ZSTD_getErrorName(actual_size) << endl;
        exit(1);
    }

    compressed_data.resize(actual_size);
    return compressed_data;
}

// Decompress the input data using zstandard
vector<char> decompress(const char* data, size_t size, size_t decompressed_size) {
    vector<char> decompressed_data(decompressed_size);

    size_t actual_size = ZSTD_decompress(decompressed_data.data(), decompressed_size, data, size);
    if (ZSTD_isError(actual_size)) {
        cerr << "Decompression failed: " << ZSTD_getErrorName(actual_size) << endl;
        exit(1);
    }

    return decompressed_data;
}

int main() {
    const char* input_data = "Hello, world!";
    size_t input_size = strlen(input_data);

    // Compress the input data
    vector<char> compressed_data = compress(input_data, input_size);
    cout << "Compressed data size: " << compressed_data.size() << endl;

    // Decompress the compressed data
    vector<char> decompressed_data = decompress(compressed_data.data(), compressed_data.size(), input_size);
    cout << "Decompressed data: " << decompressed_data.data() << endl;

    return 0;
}
