#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

class HuffmanNode {
public:
    int data;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(int d) {
        data = d;
        left = right = nullptr;
    }
};

struct compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->data > r->data;
    }
};

void generateCodes(HuffmanNode* root, string str, unordered_map<int, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->data] = str;
        return;
    }
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

string encodeHuffman(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int i = 0; i < arr.size(); i++) {
        freq[arr[i]]++;
    }
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> minHeap;
    for (auto p : freq) {
        minHeap.push(new HuffmanNode(p.second));
    }
    while (minHeap.size() != 1) {
        HuffmanNode* left = minHeap.top(); minHeap.pop();
        HuffmanNode* right = minHeap.top(); minHeap.pop();
        HuffmanNode* node = new HuffmanNode(left->data + right->data);
        node->left = left;
        node->right = right;
        minHeap.push(node);
    }
    unordered_map<int, string> huffmanCode;
    generateCodes(minHeap.top(), "", huffmanCode);
    string encoded_str = "";
    for (int i = 0; i < arr.size(); i++) {
        encoded_str += huffmanCode[arr[i]];
    }
    return encoded_str;
}

vector<int> decodeHuffman(string encoded_str, HuffmanNode* root) {
    vector<int> decoded_arr;
    HuffmanNode* curr = root;
    for (int i = 0; i < encoded_str.size(); i++) {
        if (encoded_str[i] == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
        if (!curr->left && !curr->right) {
            decoded_arr.push_back(curr->data);
            curr = root;
        }
    }
    return decoded_arr;
}

int main() {
    vector<int> arr = {2, 2, 2, 2, 2, 2, 2, 2};
    string encoded_str = encodeHuffman(arr);
    cout << "Encoded string is: " << encoded_str << endl;
    HuffmanNode* root = new HuffmanNode(-1);
    vector<int> decoded_arr = decodeHuffman(encoded_str, root);
    cout << "Decoded array is: ";
    for (int i = 0; i < decoded_arr.size(); i++) {
        cout << decoded_arr[i] << " ";
    }
    cout << endl;
    delete root;
    return 0;
}
