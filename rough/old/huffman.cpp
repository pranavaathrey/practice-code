#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

struct TreeNode {
    char character;
    int frequency;
    TreeNode *left, *right;

    TreeNode(char ch, int fr, TreeNode *l = nullptr, 
                              TreeNode *r = nullptr):
        character(ch), frequency(fr), left(l), right(r) {}
};
struct Compare {
    bool operator()(TreeNode* left, TreeNode* right) {
        return left->frequency > right->frequency;
    }
};
TreeNode* huffTreeHead;
unordered_map<char, string> huffmanCodes;

TreeNode* buildHuffTree(string text) {
    unordered_map<char, int> charFreq;
    for(char ch: text)
        charFreq[ch]++;

    priority_queue<TreeNode*, vector<TreeNode*>, Compare> pq;
    for(auto pair: charFreq)
        pq.push(new TreeNode(pair.first, pair.second));
    
    while(pq.size() > 1) {
        TreeNode* left = pq.top(); pq.pop();
        TreeNode* right = pq.top(); pq.pop();

        TreeNode* newNode = new TreeNode('\0', 
            left->frequency + right->frequency, left, right);
        pq.push(newNode);
    }
    return pq.top();
}
void generateCodes(TreeNode* node, string code) {
    if(!node) return;

    if(!node->left && !node->right) 
        huffmanCodes[node->character] = code;
    generateCodes(node->left, code + '0');
    generateCodes(node->right, code + '1');
}
string encode(string text) {
    string encoded;
    for(char ch: text)
        encoded += huffmanCodes[ch] + " ";
    return encoded;
}

int main() {
    string text; getline(cin, text);
    huffTreeHead = buildHuffTree(text);
    generateCodes(huffTreeHead, "");
    cout << encode(text);
}