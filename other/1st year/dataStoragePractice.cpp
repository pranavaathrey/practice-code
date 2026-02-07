#include <iostream>
#include <string>
#include <map>
using namespace std;

template <typename keyType = int, typename valType = string>
class DataStorage{
    private:
    map<keyType, valType> storage;

    public:
    void insert(const KeyType& key, const ValueType& value) {
        storage[key] = value;
    }

    ValueType get(const KeyType& key) const {
        auto it = storage.find(key);
        if (it != storage.end()) return it->second;
        throw std::runtime_error("Key not found");
    }

    const std::map<KeyType, ValueType>& getAll() const {
        return storage;
    }
};

template <typename KeyType>
class DataStorage<KeyType, bool> {
    private:
    map<KeyType, char> storage; // store '1' for true, '0' for false

    public:
    void insert(const KeyType& key, bool value) {
        storage[key] = value ? '1' : '0';
    }
    bool get(const KeyType& key) const {
        auto it = storage.find(key);
        if (it != storage.end()) 
            return it->second == '1';
        throw runtime_error("Key not found");
    }
    const map<KeyType, char>& getAll() const {
        return storage;
    }
};

int main(){

    return 0;
}