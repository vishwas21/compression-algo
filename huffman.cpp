#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>

#include <random>
#include <set>
#include <algorithm>
#include <functional>
#include <chrono>
#include <string>

using namespace std;

// Huffman Tree Node
class HuffmanNode {
public:
    int data;
    char symbol;
    HuffmanNode *left, *right;

    // Constructor
    HuffmanNode(int data, char symbol) {
        this->data = data;
        this->symbol = symbol;
        left = right = nullptr;
    }

    // Destructor
    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

// Custom comparator for priority_queue
class Compare {
public:
    bool operator() (const HuffmanNode* a, const HuffmanNode* b) const {
        return a->data > b->data;
    }
};

// Build Huffman Tree
HuffmanNode* buildHuffmanTree(unordered_map<char, int>& freq_map) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (auto& p : freq_map) {
        pq.push(new HuffmanNode(p.second, p.first));
    }

    while (pq.size() > 1) {
        HuffmanNode *left = pq.top();
        pq.pop();

        HuffmanNode *right = pq.top();
        pq.pop();

        HuffmanNode *parent = new HuffmanNode(left->data + right->data, '#');

        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    return pq.top();
}

// Traverse Huffman Tree and store code in a map
void traverseHuffmanTree(HuffmanNode* root, string code, unordered_map<char, string>& huffman_code) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        huffman_code[root->symbol] = code;
    }

    traverseHuffmanTree(root->left, code + "0", huffman_code);
    traverseHuffmanTree(root->right, code + "1", huffman_code);
}

// Encode integer array using Huffman Encoding
vector<char> encodeHuffman(vector<int>& arr) {
    // Calculate frequency of each integer in the array
    unordered_map<int, int> freq_map;
    for (int i : arr) {
        freq_map[i]++;
    }

    // Build Huffman Tree
    unordered_map<char, int> freq_map_char;
    for (auto& p : freq_map) {
        freq_map_char[p.first] = p.second;
    }
    HuffmanNode* root = buildHuffmanTree(freq_map_char);

    // Traverse Huffman Tree and store Huffman Code in a map
    unordered_map<char, string> huffman_code;
    traverseHuffmanTree(root, "", huffman_code);

    // Encode array using Huffman Code
    vector<char> encoded_str;
    for (int i : arr) {
        string code = huffman_code[i];
        for (char c : code) {
            encoded_str.push_back(c);
        }
    }

    delete root; // free dynamically allocated memory

    return encoded_str;
}

vector<int> decodeHuffman(vector<char>& encoded_str, HuffmanNode* root) {
    vector<int> decoded_arr;

    HuffmanNode* curr = root;
    for (char c : encoded_str) {
        if (c == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if (curr->left == nullptr && curr->right == nullptr) {
            decoded_arr.push_back(curr->symbol);
            curr = root;
        }
    }

    return decoded_arr;
}

void calculateMetrics(vector<int>& originalData, vector<int>& uncompressedData) {
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
    // Read input array from file
    ifstream infile("./workloadgen/sortedload/workload_N5000000_K1_L50.txt");
    vector<int> input_arr;
    int num;
    while (infile >> num) {
        input_arr.push_back(num);
    }

    // Encode input array using Huffman Encoding
    vector<char> encoded_vec = encodeHuffman(input_arr);

    unordered_map<int, int> freq_map;
    for (int i : input_arr) {
        freq_map[i]++;
    }

    // Build Huffman Tree
    unordered_map<char, int> freq_map_char;
    for (auto& p : freq_map) {
        freq_map_char[p.first] = p.second;
    }
    // Decode Huffman Encoded vector<char> to integer array
    HuffmanNode* root = buildHuffmanTree(freq_map_char);
    vector<int> decoded_arr = decodeHuffman(encoded_vec, root);

    std::cout << std::endl << std::endl;
    std::cout << "Input Data " << std::endl;
    std::cout << "Length : " << input_arr.size() << std::endl;
    std::cout << "Size : " << (sizeof(std::vector<int>) + (sizeof(int) * input_arr.size())) << std::endl;

    double compressionRatio = (double)input_arr.size() / (double)encoded_vec.size();
    std::cout << "Compression ratio: " << compressionRatio << std::endl;

    calculateMetrics(input_arr, decoded_arr);


    // Verify that encoded and decoded arrays are the same
    if (input_arr.size() != decoded_arr.size()) {
        cout << "Error: Size of decoded array does not match size of original array\n";
        return 0;
    }
    for (int i = 0; i < input_arr.size(); i++) {
        if (input_arr[i] != decoded_arr[i]) {
            cout << "Error: Decoded array does not match original array\n";
            return 0;
        }
    }

    cout << "Encoded and decoded arrays are the same\n";

    // Free memory allocated for Huffman Tree
    delete root;

    return 0;
}
