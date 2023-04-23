#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <fstream>

using namespace std;

// Define a structure for Huffman tree nodes
struct HuffmanNode {
    int value;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(int value, int frequency) {
        this->value = value;
        this->frequency = frequency;
        left = right = nullptr;
    }
    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

// Define a custom comparator for the priority queue
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Function to generate Huffman tree
HuffmanNode* generateHuffmanTree(const unordered_map<int, int>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (const auto& freq : frequencies) {
        pq.push(new HuffmanNode(freq.first, freq.second));
    }
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();
        HuffmanNode* parent = new HuffmanNode(-1, left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    return pq.top();
}

// Function to generate Huffman codes
void generateHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<int, string>& codes) {
    if (!root) {
        return;
    }
    if (root->value != -1) {
        codes[root->value] = code;
    }
    generateHuffmanCodes(root->left, code + "0", codes);
    generateHuffmanCodes(root->right, code + "1", codes);
}

string compress(const vector<int>& workload) {
    // Generate frequency map for each unique integer in the workload
    unordered_map<int, int> frequencies;
    for (const auto& i : workload) {
        frequencies[i]++;
    }
    // Generate Huffman tree
    HuffmanNode* root = generateHuffmanTree(frequencies);
    // Generate Huffman codes for each integer
    unordered_map<int, string> codes;
    generateHuffmanCodes(root, "", codes);
    // Encode the integer workload using Huffman codes
    string compressedWorkload;
    for (const auto& i : workload) {
        compressedWorkload += codes[i];
    }
    // Pad the compressed workload with zeros so that the length is a multiple of 8 bits
    int padding = 8 - (compressedWorkload.length() % 8);
    compressedWorkload.append(padding, '0');
    // Convert compressed workload to binary string and return
    string binaryString;
    for (size_t i = 0; i < compressedWorkload.length(); i += 8) {
        bitset<8> byte(compressedWorkload.substr(i, 8));
        binaryString += char(byte.to_ulong());
    }
    return binaryString;
}


// Function to decompress integer workload from Huffman encoding
vector<int> decompress(const string& compressedWorkload, const unordered_map<int, string>& codes) {
    string binaryString;
    for (const auto& c : compressedWorkload) {
        bitset<8> byte(c);
        binaryString += byte.to_string();
    }
    // Remove padding from binary string
    int padding = binaryString.back() - '0';
    binaryString.erase(binaryString.length() - padding);
    // Decode the binary string using Huffman codes
    vector<int> workload;
    string code;
    for (const auto& c : binaryString) {
        code += c;
        for (const auto& pair : codes) {
            if (pair.second == code) {
                workload.push_back(pair.first);
                code = "";
                break;
            }
        }
    }
    return workload;
}

int main() {
    // Load integer workload from file
    vector<int> workload;
    ifstream inputFile("./workloadgen/load/workloadSix.txt");
    int num;
    while (inputFile >> num) {
        workload.push_back(num);
    }
    inputFile.close();

    // Compress the workload using Huffman encoding
    string compressedWorkload = compress(workload);

    std::cout << "File Compress Successful" << std::endl;

    if (compressedWorkload.length() % 8 != 0) {
    throw std::invalid_argument("compressed workload length not multiple of 8");
}

    // Write compressed output to binary file
    ofstream outputFile("./compressed.bin", ios::out | ios::binary);
    for (size_t i = 0; i < compressedWorkload.size(); i += 8) {
        bitset<8> byte(compressedWorkload.substr(i, 8));
        outputFile.write((char*)&byte, sizeof(byte));
    }
    outputFile.close();

    std::cout << "File Compress Write Successful" << std::endl;

    // Read compressed data from binary file
    string compressedData;
    ifstream inputBinaryFile("./compressed.bin", ios::binary);
    char byte;
    while (inputBinaryFile.get(byte)) {
        compressedData += byte;
    }
    inputBinaryFile.close();

    std::cout << "File Compress Read Successful" << std::endl;

    // Generate Huffman tree and codes
    unordered_map<int, int> frequencies;
    for (const auto& integer : workload) {
        frequencies[integer]++;
    }
    auto huffmanTree = generateHuffmanTree(frequencies);
    unordered_map<int, string> codes;
    generateHuffmanCodes(huffmanTree, "", codes);

    // Decompress the compressed workload
    vector<int> decompressedWorkload = decompress(compressedData, codes);

    std::cout << "File Decompress Successful" << std::endl;

    // Verify that the decompressed workload matches the original workload
    if (workload == decompressedWorkload) {
        cout << "Compression and decompression successful!" << endl;
    } else {
        cout << "Compression and decompression unsuccessful!" << endl;
    }

    return 0;
}







// int main() {
//     // Read the original data from a text file
//     ifstream in("input.txt");
//     vector<int> data;
//     int x;
//     while (in >> x) {
//         data.push_back(x);
//     }
//     in.close();

//     // Compress the data
//     auto [compressed_data, root] = compress(data);

//     // Write the compressed data to a binary file
//     ofstream out("compressed.bin", ios::binary);
//     out.write(compressed_data.c_str(), compressed_data.size());
//     out.close();

//     // Read the compressed data from the binary file
//     ifstream in2("compressed.bin", ios::binary);
//     string compressed_bytes((istreambuf_iterator<char>(in2)), istreambuf_iterator<char>());
//     in2.close();

//     // Decompress the data
//     auto decompressed_data = decompress(compressed_bytes, root);

//     // Print the results
//     cout << "Compressed data: ";
//     for (char byte : compressed_bytes) {
//         cout << (int)byte << " ";
//     }
//     cout << endl;

//     cout << "Original data: ";
//     for (int x : data) {
//         cout << x << " ";
//     }
//     cout << endl;

//     cout << "Decompressed data: ";
//     for (int x : decompressed_data) {
//         cout << x << " ";
//     }
//     cout << endl;

//     // Free the memory used by the Huffman tree
//     deleteTree(root);

//     return 0;
// }