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

    double Search(T data) {
        auto start = std::chrono::high_resolution_clock::now();
        
        m[std::find(m.begin(), m.end(), data) - m.begin()];
        
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count()); 
        //return  m[std::find(m.begin(), m.end(), data) - m.begin()];
    }

    double Insert(T data) {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<T>::iterator pos = std::upper_bound(m.begin(), m.end(), data);
        if (m.size() != 0 && *std::prev(pos) != data)
            m.insert(pos, data);
        else
            m.insert(m.begin(), data);
        
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count()); 
    }

    double Delete(T data) {
        auto start = std::chrono::high_resolution_clock::now();
        
        std::vector<T>::iterator pos = std::find(m.begin(), m.end(), data);
        if (*pos == data)
            m.erase(pos);

        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count()); 
    }

    void printDataInOrder() {
        for(auto i : m) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

#endif  // SORTED_ARR_H