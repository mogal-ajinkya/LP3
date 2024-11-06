#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Node structure for the Huffman Tree
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char character = '\0', int frequency = 0) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Global nodes vector
vector<Node*> nodes;

// Calculate frequency of each character and store it in the nodes vector
void calculateFrequencies(const string& word) {
    unordered_map<char, int> frequencies;
    for (char ch : word) {
        frequencies[ch]++;
    }
    for (auto& pair : frequencies) {
        nodes.push_back(new Node(pair.first, pair.second));
    }
}

// Function to build Huffman Tree using a sorted nodes list and combining lowest frequency nodes
Node* buildHuffmanTree() {
    while (nodes.size() > 1) {
        // small are evaluated first 
        sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) { return a->freq < b->freq; });

        Node* left = nodes[0];
        Node* right = nodes[1];
        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());

        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        nodes.push_back(merged);
    }
    return nodes[0];
}

// Recursive function to generate Huffman codes
void generateHuffmanCodes(Node* node, string current_code, unordered_map<char, string>& codes) {
    if (!node) return;

    if (node->ch != '\0') {
        codes[node->ch] = current_code;
    }

    generateHuffmanCodes(node->left, current_code + "0", codes);
    generateHuffmanCodes(node->right, current_code + "1", codes);
}

// Main function for Huffman encoding
unordered_map<char, string> huffmanEncoding(const string& word) {
    nodes.clear();
    calculateFrequencies(word);
    Node* root = buildHuffmanTree();

    unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);
    return codes;
}

// Function to decode an encoded string using the Huffman codes
string huffmanDecoding(const string& encoded_word, unordered_map<char, string>& codes) {
    unordered_map<string, char> code_to_char;
    for (auto& pair : codes) {
        code_to_char[pair.second] = pair.first;
    }

    string current_code = "";
    string decoded_word = "";
    for (char bit : encoded_word) {
        current_code += bit;
        if (code_to_char.find(current_code) != code_to_char.end()) {
            decoded_word += code_to_char[current_code];
            current_code = "";
        }
    }
    return decoded_word;
}

int main() {
    string word = "lossless";

    unordered_map<char, string> codes = huffmanEncoding(word);
    string encoded_word = "";
    for (char ch : word) {
        encoded_word += codes[ch];
    }
    string decoded_word = huffmanDecoding(encoded_word, codes);

    cout << "Initial word: " << word << endl;
    cout << "Huffman code: " << encoded_word << endl;
    cout << "Conversion table: " << endl;
    for (auto& pair : codes) {
        cout << pair.first << " : " << pair.second << endl;
    }
    cout << "Decoded word: " << decoded_word << endl;

    return 0;
}

/*
**** IMP *****
lossless data compression algorithm

assign variable-length codes to input
characters, lengths of the assigned codes are based
on the frequencies of corresponding characters.

The variable-length codes assigned to input characters are
Prefix Codes, means the codes (bit sequences) are assigned
in such a way that the code assigned to one character is not
the prefix of code assigned to any other character. This is
how Huffman Coding makes sure that there is no ambiguity when
decoding the generated bitstream.

In Huffman Encoding, characters with higher frequencies have shorter 
codes, while characters with lower frequencies have longer codes.


python program exectution -> 

PS C:\Users\Dell\Desktop\DESKTOP_\coding\ALL_COLLEGE\BE_PICT_SEM7\DAA> python -u "c:\Users\Dell\Desktop\DESKTOP_\coding\ALL_COLLEGE\BE_PICT_SEM7\DAA\A2.py"  
Initial word: lossless
Huffman code: 10110001011100
Conversion table: {'s': '0', 'l': '10', 'o': '110', 'e': '111'}
Decoded word: lossless

c++ program exectution -> 

PS C:\Users\Dell\Desktop\DESKTOP_\coding\ALL_COLLEGE\BE_PICT_SEM7\DAA> cd "c:\Users\Dell\Desktop\DESKTOP_\coding\ALL_COLLEGE\BE_PICT_SEM7\DAA\" ; if ($?) { g++ HuffmanCoding.cpp -o HuffmanCoding } ; if ($?) { .\HuffmanCoding }
Initial word: lossless
Huffman code: 10111001011000
Conversion table:
o : 111
e : 110
l : 10
s : 0
Decoded word: lossless

'o' and 'e' is swapped in both the codes both are valid

In Huffman Encoding, there can be multiple valid binary trees for the same 
frequency distribution, and the resulting codes can vary depending on the 
order in which nodes of equal frequency are combined.
*/