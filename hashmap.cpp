#include "hashmap.hpp"

Node::Node(int k, void* v) {
    key = k;
    value = v;
    next = nullptr;
}

int HashMap::hash(int key) {
    if (key < 0) key = -key;
    return key % capacity;
}

HashMap::HashMap(int cap) {
    capacity = cap;
    size = 0;
    buckets = new Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        buckets[i] = nullptr;
    }
}

HashMap::~HashMap() {
    for (int i = 0; i < capacity; i++) {
        Node* current = buckets[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] buckets;
}

void HashMap::insert(int key, void* value) {
    int idx = hash(key);
    Node* current = buckets[idx];
    while (current != nullptr) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    Node* newNode = new Node(key, value);
    newNode->next = buckets[idx];
    buckets[idx] = newNode;
    size++;
}

void* HashMap::find(int key) {
    int idx = hash(key);
    Node* current = buckets[idx];
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return nullptr;
}

bool HashMap::remove(int key) {
    int idx = hash(key);
    Node* current = buckets[idx];
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                buckets[idx] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            size--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

int HashMap::getSize() {
    return size;
}