#include <iostream>
#include <vector>

#define LOOPSTART 3
using namespace std;

// singly linked list
struct Node {
    int value; Node *nextNode;
    Node(int value): 
        value(value), nextNode(nullptr) {}
};
class LinkedList {
    protected:
    Node *head; int length;

    public:
    LinkedList(): head(nullptr), length(0) {}
    ~LinkedList() {
        while(head != NULL) deleteStart();
    }

    void print() const {
        if(head == NULL) {
            cout << "Empty List!" << endl;
            return;
        }
        Node *temp = head;
        while(temp->nextNode != NULL) {
            cout << temp->value << "->";
            temp = temp->nextNode;
        }
        cout << temp->value << endl;
    }
    int size() const {
        return length;
    }
    //------------insertions------------//
    void insertStart(int value) {
        Node* newNode = new Node(value);
        newNode->nextNode = head;
        head = newNode; length++;
    }
    void insertAt(int value, int index = 0) {
        if(index <= 0 || head == NULL) 
            return insertStart(value);

        Node* temp = head;
        while(index > 1 && temp->nextNode != NULL){
            temp = temp->nextNode;
            index--;
        }
        Node* newNode = new Node(value);
        newNode->nextNode = temp->nextNode;
        temp->nextNode = newNode; length++;
    }
    //------------deletions------------//
    void deleteStart() {
        if(head == NULL)
            return;
        Node* deletedNode = head;
        head = head->nextNode;
        delete deletedNode; length--;
    }
    void deleteAt(int index = 0) {
        if(head == NULL) return;
        if(index == 0) 
            return deleteStart();

        Node* temp = head;
        while(index > 1 && temp->nextNode != NULL){
            temp = temp->nextNode;
            index--;
        }
        if(temp->nextNode == NULL) return; // out of bounds

        Node* deletedNode = temp->nextNode;
        temp->nextNode = temp->nextNode->nextNode;
        delete deletedNode; length--;  
    }
    void deleteByVal(int value) {
        if(head == NULL || head->value == value) 
            return deleteStart();

        Node* temp = head;
        while(temp->nextNode != NULL && temp->nextNode->value != value)
            temp = temp->nextNode;
        if(temp->nextNode == NULL)
            return; // not found
        Node* deletedNode = temp->nextNode;
        temp->nextNode = temp->nextNode->nextNode;
        delete deletedNode; length--;  
    }
    
    friend bool hasLoop(const LinkedList &list);
    friend LinkedList createLoopingList();
};

// tortoise-hare algorithm
bool hasLoop(const LinkedList &list) {
    if(!list.head || !list.head->nextNode)
        return false;

    Node *slow = list.head;
    Node *fast = list.head;
    while(fast != NULL && fast->nextNode != NULL) {
        slow = slow->nextNode;
        fast = fast->nextNode->nextNode;

        if(slow == fast) {
            slow = list.head;
            while(slow != fast) {
                slow = slow->nextNode;
                fast = fast->nextNode;
            }
            cout << "Loop start node value: " 
                 << slow->value << endl;
            return true;
        }
    }
    cout << "No loops found." << endl; 
    return false;
}
LinkedList createLoopingList() {
    LinkedList list; 

    vector<int> array = {9, 42, 2, 4, 2};
    for(int i = 0; i < array.size(); i++)
        list.insertAt(array[i], i); 
    
    Node *temp = list.head;
    for(int i = 0; i < LOOPSTART; i++)
        temp = temp->nextNode;
    Node *loopStart = temp; // i+1th node

    while(temp->nextNode != NULL)
        temp = temp->nextNode;
    temp->nextNode = loopStart;
    
    return list;
}

int main() {
    LinkedList list = createLoopingList();
    hasLoop(list);
    // freeing a list with loops is gonna have a lot of double free's, so broken shit.
    // not gonna be fixed, but remember.
    return 0;
}