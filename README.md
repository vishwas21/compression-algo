# Compression Algorithms

### Workload Generator

Commands:

-   make workloadgenerator
-   ./workloadgenerator <domain_size> <noise_percentage> <windowThreshold>
-   ./workloadgenerator 1000000 1 1

### Main

Commands:

Snappy

-   clang++ -std=c++11 -stdlib=libc++ -I/usr/local/include -L/opt/homebrew/lib/ -o snappy Snappy.cpp -lsnappy && ./snappy

Snappy

-   clang++ -std=c++11 -stdlib=libc++ -I/usr/local/include -L/opt/homebrew/lib/ -o snappy Snappy.cpp -lsnappy && ./snappy

LZ4

-   clang++ -std=c++11 -stdlib=libc++ -I/usr/local/include -L/opt/homebrew/lib/ -o lz4 lz4.cpp -llz4 && ./lz4

Main

-   clang++ -std=c++11 -stdlib=libc++ -I/usr/local/include -L/opt/homebrew/lib/ -o main main.cpp -lzstd -lsnappy
