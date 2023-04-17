#include <cstdio>
#include <cstdlib>
#include <cstring>

#define SNAPPY_MAX_INPUT_SIZE (1 << 28)
#define SNAPPY_MAX_OUTPUT_SIZE (1 << 28)

// Compresses the given data and returns the compressed data.
// The compressed data is stored in a buffer of the given size.
// The return value is the number of bytes written to the buffer.
size_t snappy_compress(const char* input, size_t input_size, char* output, size_t output_size) {
  // Initialize the dynamic dictionary.
  snappy_dictionary_t dictionary;
  snappy_dictionary_initialize(&dictionary);

  // Search for repeated sequences in the input data.
  size_t offset = 0;
  while (offset < input_size) {
    // Find the next repeated sequence.
    size_t length = snappy_find_match(&dictionary, input, offset);

    // If no match was found, write the next byte to the output buffer.
    if (length == 0) {
      output[output_size - 1] = input[offset];
      output_size--;
      offset++;
    } else {
      // Write the length of the match to the output buffer.
      output[output_size - 1] = length;
      output_size--;

      // Write the offset of the match to the output buffer.
      output[output_size - 1] = offset - length;
      output_size--;

      // Write the bytes of the match to the output buffer.
      memcpy(output + output_size - length, input + offset, length);
      output_size -= length;

      offset += length;
    }
  }

  // Return the number of bytes written to the output buffer.
  return output_size;
}

// Decompresses the given data and returns the decompressed data.
// The decompressed data is stored in a buffer of the given size.
// The return value is the number of bytes written to the buffer.
size_t snappy_decompress(const char* input, size_t input_size, char* output, size_t output_size) {
  // Initialize the dynamic dictionary.
  snappy_dictionary_t dictionary;
  snappy_dictionary_initialize(&dictionary);

  // Read the length of the next match from the input buffer.
  size_t length = input[0];

  // Read the offset of the next match from the input buffer.
  size_t offset = input[1];

  // Write the bytes of the match to the output buffer.
  memcpy(output + output_size - length, input + 2, length);
  output_size -= length;

  // Recursively decompress the rest of the input data.
  size_t bytes_decompressed = snappy_decompress(input + 2 + length, input_size - 2 - length, output + output_size - length, output_size);
  output_size -= bytes_decompressed;

  // Return the number of bytes written to the output buffer.
  return output_size;
}

int main() {
  // Compress some data.
  char input[] = "Hello, world!";
  size_t input_size = strlen(input);
  char output[SNAPPY_MAX_OUTPUT_SIZE];
  size_t output_size = SNAPPY_MAX_OUTPUT_SIZE;
  size_t bytes_compressed = snappy_compress(input, input_size, output, output_size);

  // Print the compressed data.
  printf("Compressed data: ");
  for (size_t i = 0; i < bytes_compressed; i++) {
    printf("%02x ", output[i]);
  }
  printf("\n");

  // Decompress the data.
  char decompressed[SNAPPY_MAX_INPUT_SIZE];
  size_t decompressed_size = SNAPPY_MAX_INPUT_SIZE;
  size_t bytes_decompressed = snappy_decompress(output, bytes_compressed, decompressed, decompressed_size);

  // Print the decompressed data.
  printf("Decompressed data: %s\n", decompressed);

  return 0;
}

// int main(int argc, char **argv)
// {
//   std::string input_file;
//   if (argc < 2)
//   {
//     std::string read_file = "./dataledger.txt";
//     std::ifstream myfile (read_file);
//     if (myfile.is_open())
//     {
//       getline (myfile,input_file);
//       myfile.close();
//     }
//   } else {
//     input_file = argv[1];
//   }

//   // read data
//   std::ifstream ifs;
//   std::vector<int> data;

//   ifs.open(input_file, std::ios::binary);
//   ifs.seekg(0, std::ios::end);
//   size_t filesize = ifs.tellg();
//   ifs.seekg(0, std::ios::beg);

//   data.resize(filesize / sizeof(int));
//   ifs.read((char *)data.data(), filesize);

//   std::cout << std::endl << std::endl;
//   std::cout << "Input Sequence : " << std::endl;
//   std::cout << "Length : " << data.size() << std::endl;
//   std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * data.size()));

  
//   // Compression Algorithm calls
//   Compress(data);
// //   LZCompress(data);
// }