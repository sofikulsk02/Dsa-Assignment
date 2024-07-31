#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> map;

    void moveToFront(int key, int value) {
        cache.erase(map[key]);
        cache.push_front({key, value});
        map[key] = cache.begin();
    }

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (map.find(key) == map.end()) {
            return -1;
        }
        int value = map[key]->second;
        moveToFront(key, value);
        return value;
    }

    void put(int key, int value) {
        if (map.find(key) != map.end()) {
            moveToFront(key, value);
        } else {
            if (cache.size() == capacity) {
                int leastUsedKey = cache.back().first;
                cache.pop_back();
                map.erase(leastUsedKey);
            }
            cache.push_front({key, value});
            map[key] = cache.begin();
        }
    }

    void print() {
        for (auto it = cache.begin(); it != cache.end(); ++it) {
            cout << "{" << it->first << ", " << it->second << "} ";
        }
        cout << endl;
    }
};

int main() {
    LRUCache lruCache(2);
    lruCache.put(1, 1);
    lruCache.put(2, 2);
    lruCache.print();
    cout<< lruCache.get(1) << endl; 
    lruCache.print();
    lruCache.put(3, 3); 
    lruCache.print();
    cout <<  lruCache.get(2) << endl; 
    lruCache.put(4, 4); 
    lruCache.print();
    cout <<  lruCache.get(1) << endl; 
    cout << lruCache.get(3) << endl; 
    cout << lruCache.get(4) << endl; 
    lruCache.print();

    return 0;
}
