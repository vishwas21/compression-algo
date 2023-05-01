/*
 * LZ4 - Fast LZ compression algorithm
 * Header File
 * 
 * Copyright (c) 2010-2013, Yann Collet
 * All rights reserved.
 *
 * BSD license
 */

#ifndef _LZ4_H
#define _LZ4_H 1

#if defined (__cplusplus)
extern "C" {
#endif

/**************************************
*  Version
**************************************/
#define LZ4_VERSION_MAJOR    1    /* for breaking interface changes  */
#define LZ4_VERSION_MINOR    9    /* for new (non-breaking) interface capabilities */
#define LZ4_VERSION_RELEASE  3    /* for tweaks, bug-fixes, or development */

#define LZ4_VERSION_NUMBER (LZ4_VERSION_MAJOR *100*100 + LZ4_VERSION_MINOR *100 + LZ4_VERSION_RELEASE)
int LZ4_versionNumber (void);

/**************************************
*  Simple Functions
**************************************/

int LZ4_compress(const char* source, char* dest, int sourceSize, int maxDestSize);
int LZ4_decompress_safe(const char* source, char* dest, int compressedSize, int maxDecompressedSize);
int LZ4_compressBound(int inputSize);

/**************************************
*  Advanced Functions
**************************************/

/* Custom memory allocation functions */
typedef void* (*LZ4_mallocFunction_t) (size_t);
typedef void  (*LZ4_freeFunction_t) (void*);

void* LZ4_malloc (size_t);
void  LZ4_free (void*);
void LZ4_setMemoryFunctions(LZ4_mallocFunction_t, LZ4_freeFunction_t);

/* Streaming functions */

typedef void* LZ4_stream_t;

int LZ4_sizeofStreamState(void);
LZ4_stream_t* LZ4_createStream(void);
int LZ4_resetStream(LZ4_stream_t* streamPtr);
void LZ4_freeStream(LZ4_stream_t* streamPtr);

/* One-time compression functions */
int LZ4_compress_limitedOutput(const char* source, char* dest, int sourceSize, int maxOutputSize);
int LZ4_compress_fast(const char* source, char* dest, int sourceSize, int maxDestSize, int acceleration);
int LZ4_compress_HC(const char* source, char* dest, int inputSize, int maxDestSize, int compressionLevel);

/* One-time decompression functions */
int LZ4_decompress_fast(const char* source, char* dest, int originalSize);
int LZ4_decompress_safe_partial(const char* source, char* dest, int compressedSize, int targetOutputSize, int dstCapacity);

/* Streaming compression functions */
int LZ4_compress_continue(LZ4_stream_t* streamPtr, const char* source, char* dest, int inputSize, int maxDestSize);
int LZ4_compress_limitedOutput_continue(LZ4_stream_t* streamPtr, const char* source, char* dest, int inputSize, int maxDestSize);
int LZ4_compress_HC_continue(LZ4_stream_t* streamPtr, const char* source, char* dest, int inputSize, int maxDestSize, int compressionLevel);

/* Streaming decompression functions */
int LZ4_decompress_safe_continue(LZ4_stream_t* streamPtr, const char* source, char* dest, int compressedSize, int maxOutputSize);
int LZ4_decompress_fast_continue(LZ4_stream_t* streamPtr, const char* source, char* dest, int originalSize);

#if defined (__cplusplus)
}
#endif

#endif /* _LZ4_H */
