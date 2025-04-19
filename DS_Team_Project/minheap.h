//
// Created by jenna on 4/18/2025.
//

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
using namespace std;

template <typename T>
class MinHeap {
public:
    MinHeap() {}
    MinHeap(vector<T> v);
    void insert(const T& val);
    void print() const;
    T delete_min();
    bool empty() const;

private:
    vector<T> data;
    void swap(T& v1, T& v2) {
        T tmp = v1;
        v1 = v2;
        v2 = tmp;
    }

    void percolate_down(int i);
    int min_index(int i1, int i2) const;
};


#endif
