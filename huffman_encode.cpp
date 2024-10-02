#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct MinHeapNode {
    char data;
    unsigned freq;
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);
    }
};

void printCodes(MinHeapNode* root, string str) {
    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(vector<char>& data, vector<int>& freq) {
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, Compare> minHeap;

    for (size_t i = 0; i < data.size(); ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    while (minHeap.size() != 1) {
        MinHeapNode *left = minHeap.top();
        minHeap.pop();

        MinHeapNode *right = minHeap.top();
        minHeap.pop();

        MinHeapNode *top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    printCodes(minHeap.top(), "");
}

int main() {
    int size;
    cout << "Enter the number of characters: ";
    while (!(cin >> size) || size <= 0) {
        cout << "Invalid input. Please enter a positive integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<char> data(size);
    vector<int> freq(size);

    cout << "Enter " << size << " characters: ";
    for (int i = 0; i < size; ++i) {
        cin >> data[i];
    }

    cout << "Enter " << size << " frequencies: ";
    for (int i = 0; i < size; ++i) {
        while (!(cin >> freq[i]) || freq[i] < 0) {
            cout << "Invalid frequency. Please enter a non-negative integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "\nHuffman Codes:\n";
    HuffmanCodes(data, freq);

    return 0;
}