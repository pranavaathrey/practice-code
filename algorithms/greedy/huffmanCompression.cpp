#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

class HuffmanCoding {
    struct TreeNode {
        char character;
        int count;
        TreeNode *left, *right;

        TreeNode(char ch, int count, TreeNode* l = nullptr, 
                                     TreeNode* r = nullptr): 
            character(ch), count(count), left(l), right(r) {}
    };

    struct Compare { 
        bool operator()(TreeNode* l, TreeNode* r) {
            // min-heap based on frequency
            return l->count > r->count;
        }
    };
    TreeNode *huffmanTreeHead;
    unordered_map<char, string> HuffmanCodes;

    TreeNode* buildHuffmanTree(const string &text) {
        if(text.empty()) return nullptr;

        unordered_map<char, int> charFreq;
        priority_queue<TreeNode*, vector<TreeNode*>, Compare> pq;

        // build character-frequency map
        for(char character: text)
            charFreq[character]++;
        // build priority queue
        for(auto pair: charFreq) 
            pq.push(new TreeNode(pair.first, pair.second));
        
        // TODO: edge case: single unique char in text = breaks algo!
        int n = charFreq.size();
        while(pq.size() > 1) {
            TreeNode *left = pq.top(); pq.pop();
            TreeNode *right = pq.top(); pq.pop();
            TreeNode *newNode = new TreeNode('\0', 
                left->count + right->count, left, right);
            pq.push(newNode);
        }
        return pq.top();
    }
    void generateCodes(TreeNode *node, string code) {
        if(!node) return;

        if(!node->left && !node->right)
            HuffmanCodes[node->character] = code;
        generateCodes(node->left, code + '0');
        generateCodes(node->right, code + '1');
    }
    int countTreeNodes(TreeNode *node) {
        if(!node) return 0;
        return countTreeNodes(node->left) 
             + countTreeNodes(node->right) + 1;
    }
    void deleteTree(TreeNode *node) {
        if(!node) return;

        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    public:
    HuffmanCoding(const string &text) {
        huffmanTreeHead = buildHuffmanTree(text);
        generateCodes(huffmanTreeHead, "");
    }
    ~HuffmanCoding() {
        deleteTree(huffmanTreeHead);
    }

    // note: you'd probably want to use the text the tree was generated with
    string encodeText(const string &text) {
        string encodedText = "";
        for(char character: text) 
            encodedText += HuffmanCodes[character];
        return encodedText;
    }
    string decodeText(const string &binary) {
        if(!huffmanTreeHead) return "Empty Tree!";
        string decodedText = "";
        TreeNode *temp = huffmanTreeHead;

        for(char bit: binary) {
            if(bit == '0') 
                temp = temp->left;
            else if(bit == '1')
                temp = temp->right;

            if(!temp->left && !temp->right) {
                decodedText += temp->character;
                temp = huffmanTreeHead;
            }
        }
        return decodedText;
    }
    // returns tree overhead (in memory) in bytes
    int getTreeSize() {
        return countTreeNodes(huffmanTreeHead) * sizeof(TreeNode);
    }
    // TODO: Tree serialization
};

int main() {
    string text; 
    cout << "Enter text that is to be compressed using "
         << "the Huffman Coding technique: \n"; 
    getline(cin, text); cout << endl;
    HuffmanCoding huffedText(text);

    string encodedText = huffedText.encodeText(text);
    cout << "The encoded text: " << encodedText << endl;
    cout << "Decoding the encoded text gives: " 
         << huffedText.decodeText(encodedText) << endl << endl;
    
    int encodedTextSize = (encodedText.length() + 7) / 8;
    cout << "Original size: " << text.length() << " bytes" << endl;
    cout << "Compressed size: " << encodedTextSize << " bytes" << endl;
    float compRatio = (1 - ((float) encodedTextSize / text.length())) * 100;
    cout << "Compression ratio: " << compRatio << "% reduction" << endl;
    cout << "Huffman tree overhead: " << huffedText.getTreeSize() << " bytes";
    return 0;
}