all: main

main: main.cpp 
	clang++ -std=c++11 -stdlib=libc++ -I/usr/local/include -L/opt/homebrew/lib/ -o $@ $^ -lzstd -lsnappy

clear: 
	rm main
	