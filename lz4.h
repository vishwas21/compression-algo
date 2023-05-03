/*
 * lz4.h provides block compression functions, returning the size of compressed block
 * lz4 frame header functions, compressing input into frame format (requires write permissions)
 * lz4 skippable frame header functions, compressing input into skippable frame format (requires write permissions)
 * lz4 block maximum size
 */

/* --- Dependency --- */
#include <stddef.h>   /* size_t */


/* --- Simple Functions --- */

unsigned LZ4_compress_default(const char* src, char* dst, int srcSize, int dstCapacity);
int      LZ4_decompress_safe(const char* src, char* dst, int compressedSize, int dstCapacity);

/* --- Advanced Compression Routines --- */

int LZ4_compress_fast(const char* source, char* dest, int sourceSize, int maxDestSize, int acceleration);
int LZ4_compress_HC(const char* source, char* dest, int inputSize, int maxDestSize, int compressionLevel);

int LZ4_compressBound(int inputSize);

/* --- lz4 frame format --- */

/*
 * A few definitions first
 */

#define LZ4F_VERSION 100

typedef enum {
    LZ4F_default=0,
    LZ4F_blockLinked=1,
    LZ4F_noContentChecksum=4,
    LZ4F_blockChecksum=8,
    LZ4F_frameChecksum=16,
    LZ4F_contentSize=32,
    LZ4F_contentChecksum=64,
    LZ4F_dict = 128
} LZ4FFrameType_t;

typedef struct {
    unsigned blockSizeID;
    unsigned blockMode;
    unsigned contentChecksumFlag;
    unsigned frameType;
    size_t contentSize;
    size_t dictID;
} LZ4F_frameInfo_t;

typedef struct {
    size_t  dstCapacity;
    size_t  maxBlockSize;
    char*   dst;
    void*   reserved[4];
} LZ4F_compressOptions_t;

typedef struct {
    size_t  dstCapacity;
    size_t  dictSize;
    const void* dict;
    void*   reserved[3];
} LZ4F_decompressOptions_t;


/*
 * Frame compression functions
 */

size_t LZ4F_compressFrameBound(size_t srcSize, const LZ4F_compressOptions_t* cOptionsPtr);
size_t LZ4F_compressFrame(void* dstBuffer, size_t dstCapacity,
                          const void* srcBuffer, size_t srcSize,
                          const LZ4F_compressOptions_t* compressOptionsPtr);

/*
 * Skippable Frame compression functions
 */

size_t LZ4F_compressBound(size_t srcSize, const LZ4F_compressOptions_t* cOptionsPtr);
size_t LZ4F_compressBegin(void* dstBuffer, size_t dstCapacity,
                          const LZ4F_compressOptions_t* compressOptionsPtr);
size_t LZ4F_compressUpdate(void* dstBuffer, size_t dstCapacity,
                           const void* srcBuffer, size_t srcSize,
                           const LZ4F_compressOptions_t* compressOptionsPtr);
size_t LZ4F_compressEnd(void* dstBuffer, size_t dstCapacity,
                        const LZ4F_compressOptions_t* compressOptionsPtr);


/*
 * Frame decompression functions
 */

size_t LZ4F_getFrameInfo(LZ4F_frameInfo_t* frameInfoPtr,
                         const void* srcBuffer, size_t* srcSizePtr);

size_t LZ4F_decompress(void* dstBuffer, size_t dstCapacity,
                       const void* srcBuffer, size_t* srcSizePtr,
                       const LZ4F_decompressOptions_t* decompressOptionsPtr);

/*
 * Error management
 */

const char* LZ4F_getErrorName(size_t errorCode);
