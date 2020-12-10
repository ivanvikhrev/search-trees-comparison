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

    T Search(T data) {
        auto el = m.find(data);
        return el != m.end() ? *el : T();
    }

    void Insert(T data) {
        m.insert(data);
    }

    void Delete(T data) {
        m.erase(data);
    }

    void printDataInOrder() {
        for(auto i : m) {
            std::cout <<  i << " " ;
        }
        std::cout << std::endl;
    }
};

#endif  // REDBLACK_TREE_H_