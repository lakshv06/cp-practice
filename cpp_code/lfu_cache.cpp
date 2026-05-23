#include <bits/stdc++.h>
using namespace std;

class cacheNode{
    public:
    int key, value, freq;
    cacheNode * prev, *next;
    
    cacheNode(int key, int value){
        this->key = key;
        this->value = value;
        this->next = nullptr;
        this->prev = nullptr;
        this->freq = 1;
    }
};

class cacheList{
  public:
    cacheNode * head, * tail;
    
    cacheList(){
        this->head = new cacheNode(-1, -1);
        this->tail = new cacheNode(-1, -1);
        head->next = tail;
        tail->prev = head;
    }
    
    void removeNode(cacheNode * node){
        node->next->prev = node->prev;
        node->prev->next = node->next;
        node->next = nullptr;
        node->prev = nullptr;
    }
    
    void addNode(cacheNode * node){
        node->next = head->next;
        head->next->prev = node;
        node->prev = head;
        head->next = node;
    }
    
    bool isEmpty(){
        return tail->prev==head && head->next == tail;
    }
    
    ~cacheList() {
        delete head;
        delete tail;
    }
    
};

class LFUCache{
    public:
        int capacity;
        int min_freq;
        unordered_map<int, cacheNode*>mp1;
        unordered_map<int, cacheList*>mp2;
        
        LFUCache(int capacity){
            this->capacity = capacity;
            this->min_freq = 0;
        }
        
        void increaseFreq(cacheNode * node){
            int nodeFreq = node->freq;
            cacheList * nodeList = mp2[nodeFreq];
            nodeList->removeNode(node);
            if(nodeList->isEmpty() && this->min_freq==nodeFreq){
                this->min_freq++;
            }
            nodeFreq++;
            node->freq +=1;
            if(mp2.find(nodeFreq)==mp2.end()){
                cacheList * newList = new cacheList();
                mp2[nodeFreq]=newList;
            }
            mp2[nodeFreq]->addNode(node);
        }
        
        int get(int key){
            if(mp1.find(key)!=mp1.end()){
                cacheNode * node = mp1[key];
                increaseFreq(node);
                return node->value;
            }
            return -1;
        }
        
        void removeLFUNode(){
            cacheList * minFreqNodeList = mp2[this->min_freq];
            cacheNode * toRemove = minFreqNodeList->tail->prev;
            minFreqNodeList->removeNode(toRemove);
            if(minFreqNodeList->isEmpty()){
                mp2.erase(this->min_freq);
            }
            mp1.erase(toRemove->key);
            delete toRemove;
        }
        
        void put(int key, int value){
            if(this->capacity==0)return;
            if(mp1.find(key)!=mp1.end()){
                cacheNode * node = mp1[key];
                node->value = value;
                increaseFreq(node);
            }
            else{
                while(mp1.size()>=capacity){
                    removeLFUNode();
                }
                cacheNode * node = new cacheNode(key, value);
                mp1[key] = node;
                if(mp2.find(node->freq)==mp2.end()){
                    cacheList * newList = new cacheList();
                    mp2[node->freq] = newList;
                }
                mp2[node->freq]->addNode(node);
                this->min_freq=1;
            }
        }
        
        ~LFUCache() {
        for (auto& pair : mp2) {
            delete pair.second;
        }
    }
};

int main() {
  LFUCache cache(2);  // Capacity of 2

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;  // Output: 1

    cache.put(3, 3);  // Evicts key 2
    cout << cache.get(2) << endl;  // Output: -1 (not found)

    cout << cache.get(3) << endl;  // Output: 3

    cache.put(4, 4);  // Evicts key 1
    cout << cache.get(1) << endl;  // Output: -1 (not found)
    cout << cache.get(3) << endl;  // Output: 3
    cout << cache.get(4) << endl;  // Output: 4

    return 0;
}
