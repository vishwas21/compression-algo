#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
  int frequency;
  Node *left, *right;
};

Node *buildHuffmanTree(vector<int> frequencies) {
  priority_queue<Node*, vector<Node*>, greater<Node*> > pq;
  for (int frequency : frequencies) {
    pq.push(new Node{frequency, nullptr, nullptr});
  }

  while (pq.size() > 1) {
    Node *left = pq.top();
    pq.pop();
    Node *right = pq.top();
    pq.pop();

    Node *parent = new Node{left->frequency + right->frequency, left, right};
    pq.push(parent);
  }

  return pq.top();
}

vector<int> huffmanEncode(Node *root, int value) {
  vector<int> codes;
  while (root != nullptr) {
    codes.push_back(root->frequency == value);
    root = root->left;
  }

  reverse(codes.begin(), codes.end());
  return codes;
}

int huffmanDecode(Node *root, vector<int> codes) {
  for (int code : codes) {
    if (code) {
      root = root->right;
    } else {
      root = root->left;
    }
  }

  return root->frequency;
}

int main() {
  vector<int> frequencies = {10, 20, 30};
  Node *root = buildHuffmanTree(frequencies);

  vector<int> codes = huffmanEncode(root, 10);
  std::cout << "The code for 10 is " << codes << endl;

  int value = huffmanDecode(root, codes);
  std::cout << "The decoded value is " << value << endl;

  return 0;
}