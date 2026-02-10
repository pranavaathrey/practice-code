#include <iostream>

using namespace std;

// TODO: make this use templates
class Set {
    struct Node {
        string value;
        Node *next;
    };
    
    static const int TABLE_SIZE = 1024;
    Node *table[TABLE_SIZE];

    unsigned int getHashIndex(const string &key) const {
        unsigned int h = 0;
        for (char c : key) {
            h = h * 31 + c;
        }
        return h % TABLE_SIZE;
    }

    public:
    Set() {
        for (int i = 0; i < TABLE_SIZE; i++) 
            table[i] = nullptr;
    }
    Set(const Set&) = delete;
    Set& operator=(const Set&) = delete;

    ~Set() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node *cur = table[i];
            while (cur) {
                Node *next = cur->next;
                delete cur;
                cur = next;
            }
            table[i] = nullptr;
        }
    }

    bool contains(const string &key) const {
        unsigned int idx = getHashIndex(key);
        Node *cur = table[idx];

        while (cur) {
            if (cur->value == key) 
                return true;
            cur = cur->next;
        }
        return false;
    }
    void insert(const string &key) {
        if (contains(key)) 
            return; 
            
        unsigned int idx = getHashIndex(key);
        Node *n = new Node;
        n->value = key;
        n->next = table[idx]; 
        table[idx] = n;
    }
    void remove(const string &key) {
        unsigned int idx = getHashIndex(key);
        Node *cur = table[idx];
        Node *prev = nullptr;

        while(cur) {
            if(cur->value == key) {
                if(prev) 
                    prev->next = cur->next;
                else 
                    table[idx] = cur->next;            
                delete cur;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }
    void printSet() const {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node *cur = table[i];
            while (cur) {
                cout << cur->value << endl;
                cur = cur->next;
            }
        }
    }
};

int main() {
    Set testSet;
    testSet.insert("apple");
    testSet.insert("banana");
    testSet.insert("cherry");
    
    testSet.insert("apple"); 

    testSet.remove("banana");
    testSet.remove("zucchini"); 

    testSet.printSet();

    return 0;
}