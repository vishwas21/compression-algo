all: main workloadgenerator

main: main.cpp 
	g++ -g -std=c++11 -o $@ $^

workloadgenerator: workload_generator.cpp
	g++ -g -std=c++0x -o $@ $^

zstd: ZStandard.cpp
	g++ -g -std=c++11 -o $@ $^

rle: rle.cpp
	g++ -g -std=c++11 -o $@ $^

snappy: snappy.cpp
	g++ -g -std=c++11 -o $@ $^

delta: delta.cpp
	g++ -g -std=c++11 -o $@ $^

bods: sortedness_data_generator.cpp
	g++ -g -std=c++11 -o $@ $^

huffman: huffman.cpp
	g++ -g -std=c++14 -o $@ $^

lz: lz77.cpp
	g++ -g -std=c++11 -o $@ $^

clear: 
	rm main
	rm workloadgenerator
	rm delta
	rm snappy
	rm rle
	rm zstd
	rm huffman
	