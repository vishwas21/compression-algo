#ifndef _SNAPPY_H_
#define _SNAPPY_H_

#include <cstdlib>
#include <string>

namespace snappy {

// Compresses the given input data into the given output buffer.
// Returns the number of bytes written to the output buffer, or -1 on error.
// The output buffer must be large enough to hold the compressed data.
// The size of the compressed data can be pre-computed using the
// SnappyCompressBound() function.
int SnappyCompress(const char* input, size_t input_size, char* output);

// Decompresses the given compressed data into the given output buffer.
// Returns the number of bytes written to the output buffer, or -1 on error.
// The output buffer must be large enough to hold the decompressed data.
// The size of the decompressed data can be pre-computed using the
// SnappyUncompressBound() function.
int SnappyUncompress(const char* input, size_t input_size, char* output);

// Returns the maximum number of bytes that SnappyCompress() can write to the
// given output buffer for the given input data.
size_t SnappyCompressBound(size_t input_size);

// Returns the maximum number of bytes that SnappyUncompress() can read from
// the given input buffer and decompress into the given output buffer.
size_t SnappyUncompressBound(size_t input_size);

}  // namespace snappy

#endif  // _SNAPPY_H_