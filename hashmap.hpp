#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <iostream>

struct Node {
    int key;
    void* value;
    Node* next;
    Node(int k, void* v);
};

class HashMap {
private:
    Node** buckets;
    int capacity;
    int size;
    int hash(int key);

public:
    HashMap(int cap = 101);
    ~HashMap();
    void insert(int key, void* value);
    void* find(int key);
    bool remove(int key);
    int getSize();
};

#endif // HASHMAP_HPP