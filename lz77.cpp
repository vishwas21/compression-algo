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

    Triple() {}
};

// void print(std::vector <int> const &a) {
//    for(int i=5890; i < 6234; i++)
//    std::cout << a.at(i) << ' ';
// }


vector<Triple> lz77_compress(const vector<int>& input) {
    vector<Triple> output;
    int inputLength = input.size();
    int pos = 0;
    while (pos < inputLength) {
        int maxMatchOffset = -1;
        int maxMatchLength = -1;
        for (int i = 1; i <= pos; i++) {
            int matchLength = 0;
            while (pos + matchLength < inputLength && input[pos + matchLength] == input[pos - i + matchLength]) {
                matchLength++;
            }
            if (matchLength > maxMatchLength) {
                maxMatchLength = matchLength;
                maxMatchOffset = i;
            }
        }
        if (maxMatchLength > 0) {
            Triple token;
            token.distance = maxMatchOffset;
            token.length = maxMatchLength;
            token.next_char = input[pos + maxMatchLength];
            output.push_back(token);
            pos += maxMatchLength + 1;
        } else {
            Triple token;
            token.distance = 0;
            token.length = 0;
            token.next_char = input[pos];
            output.push_back(token);
            pos++;
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

    std::cout << "File Compress successfull" << std::endl;

    vector<int> decompressed = lz77_decompress(compressed);

    std::cout << "File Decompress successfull" << std::endl;

    double compressionRatio = (double)decompressed.size() / (double)compressed.size();
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    calculateMetrics(input, decompressed);

    return 0;
}
