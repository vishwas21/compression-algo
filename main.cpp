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

void newRLEncoder(std::vector <int> const &input_sequence)  {
    // Initialize the random number generator
    srand(time(NULL));
    std::vector<int> output_sequence;

    const int num_trials = 10;

    // Measure the compression ratio using the run-length encoding algorithm
    auto start_time = std::chrono::high_resolution_clock::now();
    double average_ratio = 0.0;
    for (int i = 0; i < num_trials; i++) {
        int count = 1;
        int current_element = input_sequence[0];

        for (size_t i = 1; i < input_sequence.size(); i++) {
            if (input_sequence[i] == current_element) {
                count++;
            } else {
                output_sequence.push_back(count);
                output_sequence.push_back(current_element);
                current_element = input_sequence[i];
                count = 1;
            }
        }
        output_sequence.push_back(count);
        output_sequence.push_back(current_element);
        average_ratio += measure_compression_ratio(input_sequence, output_sequence);
    }
    average_ratio /= num_trials;
    auto end_time = std::chrono::high_resolution_clock::now();


    // Output the results
    std::cout << std::endl << std::endl;
    std::cout << "New Run Length Encoding Algorithm: " << std::endl;
    std::cout << "Length : " << output_sequence.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * output_sequence.size())) << std::endl;
    std::cout << "Compression ratio : " << average_ratio << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " ms" << std::endl;

}

vector<Match> compress(const vector<int>& input) {
    auto start_time = std::chrono::high_resolution_clock::now();

     const int window_size = 256;
    const int lookahead_buffer_size = 16;
    std::vector<Match> matches;
    std::unordered_map<std::vector<int>::const_iterator, std::vector<int>::const_iterator> dictionary;
    auto dict_end = dictionary.end();
    auto pos = input.begin();
    
    while (pos != input.end()) {
        Match best_match = {0, 0};
        const int max_offset = std::min<int>(window_size, std::distance(input.begin(), pos));
        const auto dict_begin = std::max(input.begin(), pos - max_offset);
        const auto dict_range = std::make_pair(dict_begin, pos);
        
        for (int offset = 1; offset <= max_offset; ++offset) {
            const auto search_begin = std::max(dict_begin, pos - offset);
            const auto search_end = std::min(input.end(), pos + lookahead_buffer_size);
            const auto substring = std::vector<int>(pos, search_end);
            
            auto dict_match = dictionary.find(search_begin);
            while (dict_match != dict_end && dict_match->first < search_end) {
                int length = 0;
                const auto dict_pos = dict_match->first;
                const auto dict_val = dict_match->second;
                
                while (pos + length != input.end() && dict_pos + length != dict_val) {
                    if (*(pos + length) != *(dict_pos + length)) {
                        break;
                    }
                    ++length;
                }
                
                if (length > best_match.length) {
                    best_match = {std::distance(dict_pos, pos), length};
                }
                
                ++dict_match;
            }
            
            if (pos + best_match.length >= search_end) {
                break;
            }
        }
        
        matches.push_back(best_match);
        const auto new_pos = pos + best_match.length + 1;
        dictionary[std::make_pair(pos, new_pos)] = dict_range;
        pos = new_pos;
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << std::endl;
    std::cout << "LZ new Encoding Algorithm: " << std::endl;
    std::cout << "Length : " << matches.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * matches.size())) << std::endl;
    std::cout << "Time : " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " ms" << std::endl;

    return matches;
}

int LZCompress(std::vector <int> const &input_sequence) {
    vector<Match> tokens = compress(input_sequence);
    // cout << "Compressed data:" << endl;
    // for (Token token : tokens) {
    //     cout << "(" << token.offset << "," << token.length << "," << token.next << ")" << endl;
    // }
    cout << endl;
    return 0;
}

namespace std {
    template<>
    struct hash<std::__wrap_iter<const int*> > {
        size_t operator()(std::__wrap_iter<const int*> const& iter) const noexcept {
            return std::hash<const int*>{}(&*iter);
        };
    };
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
  // newRLEncoder(data);
  LZCompress(data);
}