#include <iostream>
#include <vector>
#include <list>
#include <utility>

using namespace std;
class HashMapLinearProbing {
private:
    vector<pair<int, int>> table;
    vector<bool> occupied;
    int capacity;
    int size;

    int hash(int key) {
        return key % capacity;
    }

public:
    HashMapLinearProbing(int cap = 101) : capacity(cap), size(0) {
        table.resize(capacity, {-1, -1});
        occupied.resize(capacity, false);
    }

    bool find(int key) {
        int index = hash(key);
        int originalIndex = index;
        while (occupied[index]) {
            if (table[index].first == key) {
                return true;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) break;
        }
        return false;
    }

    void insert(int key, int value) {
        if (size >= capacity) {
            cout << "HashMap is full" << endl;
            return;
        }

        int index = hash(key);
        while (occupied[index]) {
            if (table[index].first == key) {
                table[index].second = value;
                return;
            }
            index = (index + 1) % capacity;
        }

        table[index] = {key, value};
        occupied[index] = true;
        size++;
    }

    void remove(int key) {
        int index = hash(key);
        int originalIndex = index;
        while (occupied[index]) {
            if (table[index].first == key) {
                table[index] = {-1, -1};
                occupied[index] = false;
                size--;
                return;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) break;
        }
    }

    void print() {
        for (int i = 0; i < capacity; ++i) {
            if (occupied[i]) {
                cout << "{" << table[i].first << ", " << table[i].second << "} ";
            }
        }
        cout << endl;
    }
};
class HashMapSeparateChaining {
private:
    vector<list<pair<int, int>>> table;
    int capacity;
    int size;

    int hash(int key) {
        return key % capacity;
    }

public:
    HashMapSeparateChaining(int cap = 101) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    bool find(int key) {
        int index = hash(key);
        for (auto &entry : table[index]) {
            if (entry.first == key) {
                return true;
            }
        }
        return false;
    }

    void insert(int key, int value) {
        int index = hash(key);
        for (auto &entry : table[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        table[index].emplace_back(key, value);
        size++;
    }

    void remove(int key) {
        int index = hash(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                size--;
                return;
            }
        }
    }

    void print() {
        for (int i = 0; i < capacity; ++i) {
            for (auto &entry : table[i]) {
                cout << "{" << entry.first << ", " << entry.second << "} ";
            }
        }
        cout << endl;
    }
};

int main() {
    HashMapLinearProbing hashMapLP;
    hashMapLP.insert(1, 100);
    hashMapLP.insert(2, 200);
    hashMapLP.insert(3, 300);
    hashMapLP.print();
    cout << hashMapLP.find(2) << endl;
    hashMapLP.remove(2);
    hashMapLP.print();
    cout << hashMapLP.find(2) << endl;

    cout << "\nHashMap with Separate Chaining:" << endl;
    HashMapSeparateChaining hashMapSC;
    hashMapSC.insert(1, 100);
    hashMapSC.insert(2, 200);
    hashMapSC.insert(3, 300);
    hashMapSC.print();
    cout <<hashMapSC.find(2) << endl;
    hashMapSC.remove(2);
    hashMapSC.print();
    cout <<hashMapSC.find(2) << endl;

    return 0;
}
