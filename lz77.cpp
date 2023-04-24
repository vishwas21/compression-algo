#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

struct Triple {
    int distance, length, next_char;

    Triple(int d, int l, int c) : distance(d), length(l), next_char(c) {}
};

// void print(std::vector <int> const &a) {
//    for(int i=5890; i < 6234; i++)
//    std::cout << a.at(i) << ' ';
// }


vector<Triple> lz77_compress(const vector<int>& input) {
    vector<Triple> output;
    int pos = 0;
    while (pos < input.size()) {
        int max_match_len = 0;
        int max_match_pos = 0;

        // std::cout << "Pos: " << pos << std::endl;
        // std::cout << "Max Len: " << max_match_len << std::endl;
        // std::cout << "Max Pos: " << max_match_pos << std::endl;
        // std::cout << std::endl;

        for (int i = 1; i <= min(4095, (int)pos); i++) {
            auto it = search(input.begin() + pos - i, input.begin() + pos, input.begin() + pos, input.end());
            if (it != input.begin() + pos - 1) {
                int match_pos = pos - (it - input.begin());
                int match_len = i;
                if (match_len > max_match_len) {
                    max_match_len = match_len;
                    max_match_pos = match_pos;
                }
            }
        }
        if (max_match_len == 0) {
            output.emplace_back(0, 0, input[pos]);
            pos++;
        } else {
            output.emplace_back(max_match_pos, max_match_len, input[pos + max_match_len]);
            pos += max_match_len + 1;
        }
    }
    return output;
}


vector<int> lz77_decompress(const vector<Triple>& input) {
    vector<int> output;
    for (const auto& t : input) {
        int pos = output.size() - t.distance;
        int len = t.length;
        int c = t.next_char;
        for (int i = 0; i < len; i++) {
            output.push_back(output[pos + i]);
        }
        output.push_back(c);
    }
    return output;
}

// Function to calculate accuracy, precision, and recall of RLE
void calculateMetrics(std::vector<int>& originalData, std::vector<int>& uncompressedData) {
    int originalSize = originalData.size();
    int uncompressedSize = uncompressedData.size();
    double mse = 0.0;
    for (int i = 0; i < originalSize; ++i) {
        mse += std::pow((double)originalData[i] - (double)uncompressedData[i], 2.0);
    }
    mse /= (double)originalSize;
    double psnr;
    if (mse == 0.0) {
        psnr = 100.0;
    } else {
        psnr = 20.0 * std::log10(255.0 / std::sqrt(mse));
    }
    std::cout << "PSNR: " << psnr << " dB" << std::endl;

    int matchedCount = 0;
    for(int i = 0; i < originalSize; ++i) {
        if(originalData[i] == uncompressedData[i]) {
            matchedCount ++;
        }
    }

    double accuracy = ((double)matchedCount / originalSize) * 100;
    std::cout << "Accuracy : " << accuracy << "%" << std::endl;
}

int main() {
    string line;
    vector<int> input;
    ifstream file("workloadgen/load/workloadOne.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream iss(line);
            int num;
            while (iss >> num) {
                input.push_back(num);
            }
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
        return 1;
    }

    std::cout << "File Read successfull" << std::endl;

    vector<Triple> compressed = lz77_compress(input);
    // cout << "Compressed:" << endl;
    // for (const auto& t : compressed) {
    //     cout << "<" << t.distance << ", " << t.length << ", " << t.next_char << "> ";
    // }
    // cout << endl;

    std::cout << "File Compress successfull" << std::endl;

    vector<int> decompressed = lz77_decompress(compressed);
    // cout << "Decompressed:" << endl;
    // for (int i : decompressed) {
    //     cout << i << " ";
    // }
    // cout << endl;

    std::cout << "File Decompress successfull" << std::endl;

    double compressionRatio = (double)decompressed.size() / (double)compressed.size();
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    calculateMetrics(input, decompressed);

    // std::cout << std::endl;
    // print(input);
    // std::cout << std::endl;
    // print(decompressed);

    return 0;
}
