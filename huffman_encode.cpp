#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <memory>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct MinHeapNode {
    wchar_t data;
    unsigned freq;
    shared_ptr<MinHeapNode> left, right;

    MinHeapNode(wchar_t data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(const shared_ptr<MinHeapNode>& l, const shared_ptr<MinHeapNode>& r) const {
        return l->freq > r->freq || (l->freq == r->freq && l->data > r->data);
    }
};

void printCodes(const shared_ptr<MinHeapNode>& root, wstring str) {
    if (!root)
        return;

    if (root->data != L'$')
        wcout << root->data << L": " << str << L"\n";

    printCodes(root->left, str + L"0");
    printCodes(root->right, str + L"1");
}

void HuffmanCodes(const vector<wchar_t>& data, const vector<int>& freq) {
    priority_queue<shared_ptr<MinHeapNode>, vector<shared_ptr<MinHeapNode>>, Compare> minHeap;

    for (size_t i = 0; i < data.size(); ++i)
        minHeap.push(make_shared<MinHeapNode>(data[i], freq[i]));

    while (minHeap.size() > 1) {
        auto left = minHeap.top();
        minHeap.pop();

        auto right = minHeap.top();
        minHeap.pop();

        auto top = make_shared<MinHeapNode>(L'$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    if (!minHeap.empty())
        printCodes(minHeap.top(), L"");
}

int main() {
    int size;
    wcout << L"Enter the number of characters: ";
    while (!(wcin >> size) || size <= 0) {
        wcout << L"Invalid input. Please enter a positive integer: ";
        wcin.clear();
        wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
    }

    vector<wchar_t> data(size);
    vector<int> freq(size);
    unordered_map<wchar_t, int> char_freq_map;

    wcout << L"Enter " << size << L" characters: ";
    for (int i = 0; i < size; ++i) {
        wcin >> data[i];
        if (char_freq_map.find(data[i]) != char_freq_map.end()) {
            wcout << L"Error: Duplicate character '" << data[i] << L"'. Each character must be unique.\n";
            return 1;
        }
        char_freq_map[data[i]] = i;
    }

    wcout << L"Enter " << size << L" frequencies: ";
    for (int i = 0; i < size; ++i) {
        while (!(wcin >> freq[i]) || freq[i] < 0) {
            wcout << L"Invalid frequency. Please enter a non-negative integer: ";
            wcin.clear();
            wcin.ignore(numeric_limits<streamsize>::max(), L'\n');
        }
    }

    // Sort data and freq based on frequency (descending) and then character (ascending)
    vector<pair<wchar_t, int>> char_freq_pairs(size);
    for (int i = 0; i < size; ++i) {
        char_freq_pairs[i] = {data[i], freq[i]};
    }
    sort(char_freq_pairs.begin(), char_freq_pairs.end(),
         [](const auto& a, const auto& b) {
             return a.second > b.second || (a.second == b.second && a.first < b.first);
         });

    for (int i = 0; i < size; ++i) {
        data[i] = char_freq_pairs[i].first;
        freq[i] = char_freq_pairs[i].second;
    }

    wcout << L"\nHuffman Codes:\n";
    HuffmanCodes(data, freq);

    return 0;
}