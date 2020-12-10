#include <algorithm>
#include <vector>
#include <iostream>
#include <set>
#include "node.h"

#ifndef REDBLACK_TREE_H_
#define REDBLACK_TREE_H_

template <class T>
class RBTree {
public:
    std::set<T> m;

    RBTree() {
        m = std::set<T>();
    }

    RBTree(std::vector<T> inp) {
        for (auto const & x : inp) { m[x] = x; }
    }

    double Search(T data) {
        auto start = std::chrono::high_resolution_clock::now();
        
        auto el = m.find(data);
        
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count());  
        //return el != m.end() ? *el : T();
    }

    double Insert(T data) {
        auto start = std::chrono::high_resolution_clock::now();

        m.insert(data);
        
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count());  

    }

    double Delete(T data) {
        auto start = std::chrono::high_resolution_clock::now();

        m.erase(data);

                
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count());  
    }

    void printDataInOrder() {
        for(auto i : m) {
            std::cout <<  i << " " ;
        }
        std::cout << std::endl;
    }
};

#endif  // REDBLACK_TREE_H_