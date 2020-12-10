#include <vector>
#include <iostream>
#ifndef SORTED_ARR_H_
#define SORTED_ARR_H_
template <class T>
class SortedArray {
public:
    std::vector<T> m;

    SortedArray() {
        m = std::vector<T>();
    }

    SortedArray(std::vector<T> inp) {
        m = inp;
        std::sort(m.begin(), m.end());
    }

    T Search(T data) { return  m[std::find(m.begin(), m.end(), data) - m.begin()]; }

    void Insert(T data) {
        std::vector<T>::iterator pos = std::upper_bound(m.begin(), m.end(), data);
        if (m.size() != 0 && *std::prev(pos) != data)
            m.insert(pos, data);
        else
            pos = m.begin();
    }

    void Delete(T data) {
        std::vector<T>::iterator pos = std::find(m.begin(), m.end(), data);
        if (*pos == data)
            m.erase(pos);
    }

    void printDataInOrder() {
        for(auto i : m) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

#endif  // SORTED_ARR_H