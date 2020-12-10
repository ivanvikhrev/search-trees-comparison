#ifndef TREE_NODE_H_
#define TREE_NODE_H_
template <class T>
struct node {
    int info;
    T data;
    node<T> *right;
    node<T> *left;
    node<T>* parent;
    node(T d) { data = d;  parent = left = right = nullptr; }
    node(T d, node<T>* p) { data = d;  parent = p; left = right = nullptr; }

    int max_depth() const {
        const int left_depth = left ? left->max_depth() : 0;
        const int right_depth = right ? right->max_depth() : 0;
        return (left_depth > right_depth ? left_depth : right_depth) + 1;
    }
};

#endif  // TREE_NODE_H