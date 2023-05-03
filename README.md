# Compression Algorithms

### Workload Generator

Commands:

-   make workloadgenerator
-   ./workloadgenerator <domain_size> <noise_percentage> <windowThreshold>
-   ./workloadgenerator 1000000 1 1

### Main

Commands:

-   make main
-   ./main <input_file>
-   Eg: ./main ./data_1000000-elems_1-kperct_1-lperct_1seed1680539487.dat
-   g++ -I/Users/vishwasb/personal/masters/Spring2023/CS561/FinalProject/compression-code ZStandard.cpp -o ZStandard
-   clang++ -std=c++11 -stdlib=libc++ -I/usr/local/include -L/opt/homebrew/lib/ -o zstd ZStandard.cpp -lzstd && ./zstd
-   brew install zstd
-   /Users/vishwasb/Downloads/boost_1_82_0

Snappy

-   clang++ -std=c++11 -stdlib=libc++ -I/usr/local/include -L/opt/homebrew/lib/ -o snappy Snappy.cpp -lsnappy && ./snappy

LZ4

-   clang++ -std=c++11 -stdlib=libc++ -I/usr/local/include -L/opt/homebrew/lib/ -o lz4 lz4.cpp -llz4 && ./lz4

Main

-   clang++ -std=c++11 -stdlib=libc++ -I/usr/local/include -L/opt/homebrew/lib/ -o main main.cpp -lzstd -lsnappy
