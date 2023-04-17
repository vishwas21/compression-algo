all: main workloadgenerator

main: main.cpp 
	g++ -g -std=c++11 -o $@ $^

workloadgenerator: workload_generator.cpp
	g++ -g -std=c++0x -o $@ $^

zstd: ZStandard.cpp
	g++ -g -std=c++11 -o $@ $^

rle: rle.cpp
	g++ -g -std=c++11 -o $@ $^

clear: 
	rm main
	rm workloadgenerator