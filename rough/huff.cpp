#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

struct TreeNode {
    char character;
    int count;
    TreeNode *left, *right;

    TreeNode(char character, int count, TreeNode* left = nullptr,
                                        TreeNode* right = nullptr):
        character(character), count(count), left(left), right(right) {}
};
struct Compare {
    bool operator()(TreeNode* left, TreeNode* right) {
        return left->count > right->count;
    }
};

class HuffmanCoding {
    TreeNode* huffmanTreeHead;
    unordered_map<char, string> huffmanCodes;
    
    TreeNode* buildTree(string text) {
        if(text.length() == 0)
            return nullptr;

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
                left->count + right->count, left, right);
            pq.push(newNode);
        }
        return pq.top();
    }

    void generateCodes(TreeNode* root, string code) {
        if(!root) return;

        if(!root->left && !root->right) 
            huffmanCodes[root->character] = code;
        generateCodes(root->left, code + "0");
        generateCodes(root->right, code + "1");
    }

    public:
    HuffmanCoding(string text) {
        huffmanTreeHead = buildTree(text);
        generateCodes(huffmanTreeHead, "");
    }

    string encode(string text) {
        string encodedText = "";
        for(char ch: text) 
            encodedText += huffmanCodes[ch];
        return encodedText;
    }
    string decode(string binary) {
        string decodedText = "";
        TreeNode* temp = huffmanTreeHead;

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
};

int main() {
    string text = "bruh man dan yeah boi f***";
    HuffmanCoding huffin(text);

    string e = huffin.encode(text);
    cout << text << endl << e << endl;
    cout << huffin.decode(e);
}