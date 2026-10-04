#ifndef HEAPS_HPP
#define HEAPS_HPP

#include "file.hpp"
#include <vector>

class Recent_Heap {
private:
    std::vector<File*> heap;
public:
    void heapifyUp(int i);
    void heapifyDown(int i);
    void heapifyDown(int i, std::vector<File*>& target_heap);
    void insert(File* file);
    int size();
    std::vector<File*> getSortedFiles(int count);
};

class Big_Heap {
private:
    std::vector<File*> heap;
public:
    void heapifyUp(int i);
    void heapifyDown(int i);
    void heapifyDown(int i, std::vector<File*>& target_heap);
    void insert(File* file);
    int size();
    std::vector<File*> getSortedFiles(int count);
};

#endif // HEAPS_HPP