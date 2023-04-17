#include <fstream>
#include <vector>
#include <iostream>
#include <random>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>
#include <string>
#include <unordered_map>

using namespace std;


struct Match {
    int offset;
    int length;
};


void print(std::vector <int> const &a) {
   for(int i=0; i < 100; i++)
   std::cout << a.at(i) << ' ';
}

double measure_compression_ratio(const std::vector<int>& input_sequence, const std::vector<int>& compressed_sequence) {
    double input_size = input_sequence.size() * sizeof(int);
    double output_size = compressed_sequence.size() * sizeof(int);
    return input_size / output_size;
}

vector<pair<int, int> > compress(const vector<int>& data) {
    auto start_time = std::chrono::high_resolution_clock::now();

    int n = data.size();
    vector<pair<int, int> > output;

    for (int i = 0; i < n; i++) {
        int j = i + 1;
        while (j < n && data[j] == data[i]) j++;
        int len = j - i;
        int dist = i;
        output.push_back(make_pair(len, dist));
        i = j - 1;
    }

    for (auto p : output) {
        cout << p.first << " " << p.second << " ";
    }
    cout << endl;
    
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::endl;
    std::cout << "LZ new Encoding Algorithm: " << std::endl;
    std::cout << "Length : " << output.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * output.size())) << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " ms" << std::endl;

    return output;
}

int main(int argc, char **argv)
{
  std::string input_file;
  if (argc < 2)
  {
    std::string read_file = "./dataledger.txt";
    std::ifstream myfile (read_file);
    if (myfile.is_open())
    {
      getline (myfile,input_file);
      myfile.close();
    }
  } else {
    input_file = argv[1];
  }

  // read data
  std::ifstream ifs;
  std::vector<int> data;

  ifs.open(input_file, std::ios::binary);
  ifs.seekg(0, std::ios::end);
  size_t filesize = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  data.resize(filesize / sizeof(int));
  ifs.read((char *)data.data(), filesize);

    

  std::cout << std::endl << std::endl;
  std::cout << "Input Sequence : " << std::endl;
  std::cout << "Length : " << data.size() << std::endl;
  std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * data.size()));

  
  // Compression Algorithm calls
  newRLEncoder(data);
//   LZCompress(data);
}