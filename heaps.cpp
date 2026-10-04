#include "heaps.hpp"

using namespace std;

// --- Recent_Heap Implementation ---
void Recent_Heap::heapifyUp(int i) {
    int parent = (i - 1) / 2;
    if (parent >= 0) {
        time_t parent_time = heap[parent]->getLastModified();
        time_t current_time = heap[i]->getLastModified();
        if (parent_time < current_time || (parent_time == current_time && heap[parent]->getFileName() < heap[i]->getFileName())) {
            swap(heap[parent], heap[i]);
            heapifyUp(parent);
        }
    }
}

void Recent_Heap::heapifyDown(int i, vector<File*>& target_heap) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int n = target_heap.size();
    int largest = i;
    if (left < n) {
        time_t left_time = target_heap[left]->getLastModified();
        time_t current_time = target_heap[largest]->getLastModified();
        if (left_time > current_time || (left_time == current_time && target_heap[left]->getFileName() > target_heap[largest]->getFileName())) {
            largest = left;
        }
    }
    if (right < n) {
        time_t right_time = target_heap[right]->getLastModified();
        time_t current_time = target_heap[largest]->getLastModified();
        if (right_time > current_time || (right_time == current_time && target_heap[right]->getFileName() > target_heap[largest]->getFileName())) {
            largest = right;
        }
    }
    if (largest != i) {
        swap(target_heap[largest], target_heap[i]);
        heapifyDown(largest, target_heap);
    }
}

void Recent_Heap::heapifyDown(int i) {
    heapifyDown(i, heap);
}

void Recent_Heap::insert(File* file) {
    for (int i = 0; i < heap.size(); i++) {
        if (heap[i] == file) {
            heapifyUp(i);
            heapifyDown(i);
            return;
        }
    }
    heap.push_back(file);
    heapifyUp(heap.size() - 1);
}

int Recent_Heap::size() {
    return heap.size();
}

vector<File*> Recent_Heap::getSortedFiles(int count) {
    vector<File*> result;
    vector<File*> temp_heap = heap;
    for (int i = 0; i < count && !temp_heap.empty(); i++) {
        result.push_back(temp_heap[0]);
        temp_heap[0] = temp_heap.back();
        temp_heap.pop_back();
        if (!temp_heap.empty()) {
            heapifyDown(0, temp_heap);
        }
    }
    return result;
}


// --- Big_Heap Implementation ---
void Big_Heap::heapifyUp(int i) {
    int parent = (i - 1) / 2;
    if (parent >= 0 && heap[parent]->getTotalV() < heap[i]->getTotalV()) {
        swap(heap[parent], heap[i]);
        heapifyUp(parent);
    }
}

void Big_Heap::heapifyDown(int i, vector<File*>& target_heap) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int n = target_heap.size();
    int largest = i;
    if (left < n && target_heap[left]->getTotalV() > target_heap[largest]->getTotalV()) {
        largest = left;
    }
    if (right < n && target_heap[right]->getTotalV() > target_heap[largest]->getTotalV()) {
        largest = right;
    }
    if (largest != i) {
        swap(target_heap[largest], target_heap[i]);
        heapifyDown(largest, target_heap);
    }
}

void Big_Heap::heapifyDown(int i) {
    heapifyDown(i, heap);
}

void Big_Heap::insert(File* file) {
    for (int i = 0; i < heap.size(); i++) {
        if (heap[i] == file) {
            heapifyUp(i);
            heapifyDown(i);
            return;
        }
    }
    heap.push_back(file);
    heapifyUp(heap.size() - 1);
}

int Big_Heap::size() {
    return heap.size();
}

vector<File*> Big_Heap::getSortedFiles(int count) {
    vector<File*> result;
    vector<File*> temp_heap = heap;
    for (int i = 0; i < count && !temp_heap.empty(); i++) {
        result.push_back(temp_heap[0]);
        temp_heap[0] = temp_heap.back();
        temp_heap.pop_back();
        if (!temp_heap.empty()) {
            heapifyDown(0, temp_heap);
        }
    }
    return result;
}