#include <iostream>
#include <unordered_map>

class cacheNode {
public:
    int key, value;
    cacheNode* prev, * next;

    cacheNode(int key, int value) {
        this->prev = nullptr;
        this->next = nullptr;
        this->key = key;
        this->value = value;
    }
};

class LRUCache {
public:
    int capacity;
    cacheNode* head, * tail;
    std::unordered_map<int, cacheNode*> mp;

    LRUCache(int capacity) {
        this->capacity = capacity;
        this->head = new cacheNode(-1, -1);
        this->tail = new cacheNode(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    void removeNode(cacheNode* node) {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    }

    cacheNode* removeLast() {
        cacheNode* last = tail->prev;
        removeNode(last);
        return last;
    }

    void addFirst(cacheNode* node) {
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
        node->prev = head;
    }

    int get(int key) {
        if (mp.find(key) != mp.end()) {
            cacheNode* node = mp[key];
            removeNode(node);
            addFirst(node);
            return node->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            cacheNode* node = mp[key];
            removeNode(node);
            node->value = value;
            addFirst(node);
        } else {
            if (mp.size() >= capacity) {
                cacheNode* removedNode = removeLast();
                mp.erase(removedNode->key);
                delete removedNode;
            }
            cacheNode* node = new cacheNode(key, value);
            mp[key] = node;
            addFirst(node);
        }
    }

    ~LRUCache() {
        // Clean up allocated memory
        cacheNode* current = head;
        while (current != nullptr) {
            cacheNode* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LRUCache cache(2);  // Create an LRU cache with capacity 2

    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << cache.get(1) << std::endl;  // Output: 1

    cache.put(3, 3);  // Evicts key 2
    std::cout << cache.get(2) << std::endl;  // Output: -1 (not found)

    cache.put(4, 4);  // Evicts key 1
    std::cout << cache.get(1) << std::endl;  // Output: -1 (not found)
    std::cout << cache.get(3) << std::endl;  // Output: 3
    std::cout << cache.get(4) << std::endl;  // Output: 4

    return 0;
}
