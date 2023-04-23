#include <iostream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <fstream>

using namespace std;

// A Huffman tree node
struct HuffmanNode {
    int data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(int data, int freq) {
        this->data = data;
        this->freq = freq;
        this->left = nullptr;
        this->right = nullptr;
    }

    HuffmanNode(HuffmanNode* left, HuffmanNode* right) {
        this->data = -1;
        this->freq = left->freq + right->freq;
        this->left = left;
        this->right = right;
    }
};

// Compare two Huffman tree nodes by frequency
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// Generate the code table for a Huffman tree
void generate_code_table(HuffmanNode* node, string code, unordered_map<int, string>& code_table) {
    if (node->data != -1) {
        code_table[node->data] = code;
    } else {
        generate_code_table(node->left, code + "0", code_table);
        generate_code_table(node->right, code + "1", code_table);
    }
}

// // Compress a vector of integers using variable-length encoding
// string compress(vector<int> data) {
//     // Calculate the frequency of each integer
//     unordered_map<int, int> freq;
//     for (int d : data) {
//         freq[d]++;
//     }

//     // Build the Huffman tree
//     priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
//     for (auto p : freq) {
//         pq.push(new HuffmanNode(p.first, p.second));
//     }
//     while (pq.size() > 1) {
//         HuffmanNode* left = pq.top(); pq.pop();
//         HuffmanNode* right = pq.top(); pq.pop();
//         pq.push(new HuffmanNode(left, right));
//     }
//     HuffmanNode* root = pq.top();

//     // Generate the code table
//     unordered_map<int, string> code_table;
//     generate_code_table(root, "", code_table);
//     delete root;

//     // Compress the data using the code table
//     string compressed = "";
//     for (int d : data) {
//         string code = code_table[d];
//         compressed += code;
//     }

//     // Pad the compressed data to a multiple of 8 bits
//     int padding = 8 - compressed.length() % 8;
//     if (padding < 8) {
//         compressed += string(padding, '0');
//     }

//     // Convert the compressed data to bytes
//     string bytes = "";
//     for (int i = 0; i < (int)compressed.length(); i += 8) {
//         bitset<8> bits(compressed.substr(i, 8));
//         bytes += char(bits.to_ulong());
//     }

//     return bytes;
// }

void deleteTree(HuffmanNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

std::pair<std::string, HuffmanNode*> compress(const std::vector<int>& data) {
    // Count the frequency of each integer in the data
    std::unordered_map<int, int> freq;
    for (int x : data) {
        freq[x]++;
    }

    // Build the Huffman tree
    auto cmp = [](HuffmanNode* a, HuffmanNode* b) { return a->frequency > b->frequency; };
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, decltype(cmp)> pq(cmp);
    for (auto p : freq) {
        pq.push(new HuffmanNode(p.first, p.second));
    }
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        pq.push(new HuffmanNode(left, right));
    }

    // Build the codewords for each integer
    std::unordered_map<int, std::string> codewords;
    buildCodewords(pq.top(), "", codewords);

    // Encode the data using the codewords
    std::string encoded_data;
    for (int x : data) {
        encoded_data += codewords[x];
    }

    // Convert the encoded data to a string of bytes
    std::string compressed_data;
    for (size_t i = 0; i < encoded_data.size(); i += 8) {
        std::bitset<8> byte;
        for (size_t j = 0; j < 8 && i + j < encoded_data.size(); j++) {
            if (encoded_data[i + j] == '1') {
                byte.set(7 - j);
            }
        }
        compressed_data += static_cast<char>(byte.to_ulong());
    }

    // Free the memory used by the Huffman tree
    HuffmanNode* root = pq.top();
    pq.pop();
    deleteTree(root);

    return std::make_pair(compressed_data, root);
}

// Decompress a string of bytes using a Huffman tree
vector<int> decompress(string bytes, HuffmanNode* root) {
    // Convert the bytes to bits
    string bits = "";
    for (char byte : bytes) {
        bits += bitset<8>(byte).to_string();
    }

    // Get the number of unused bits in the last byte
    int unused_bits = bits[bits.size() - 1] - '0';
    bits = bits.substr(0, bits.size() - unused_bits - 1);

    // Decompress the bits using the Huffman tree
    vector<int> data;
    HuffmanNode* node = root;
    for (char bit : bits) {
        if (bit == '0') {
            node = node->left;
        } else {
            node = node->right;
        }
        if (node->data != -1) {
            data.push_back(node->data);
            node = root;
        }
    }

    return data;
}

int main() {
    // Read the original data from a text file
    ifstream in("input.txt");
    vector<int> data;
    int x;
    while (in >> x) {
        data.push_back(x);
    }
    in.close();

    // Compress the data
    auto [compressed_data, root] = compress(data);

    // Write the compressed data to a binary file
    ofstream out("compressed.bin", ios::binary);
    out.write(compressed_data.c_str(), compressed_data.size());
    out.close();

    // Read the compressed data from the binary file
    ifstream in2("compressed.bin", ios::binary);
    string compressed_bytes((istreambuf_iterator<char>(in2)), istreambuf_iterator<char>());
    in2.close();

    // Decompress the data
    auto decompressed_data = decompress(compressed_bytes, root);

    // Print the results
    cout << "Compressed data: ";
    for (char byte : compressed_bytes) {
        cout << (int)byte << " ";
    }
    cout << endl;

    cout << "Original data: ";
    for (int x : data) {
        cout << x << " ";
    }
    cout << endl;

    cout << "Decompressed data: ";
    for (int x : decompressed_data) {
        cout << x << " ";
    }
    cout << endl;

    // Free the memory used by the Huffman tree
    deleteTree(root);

    return 0;
}
