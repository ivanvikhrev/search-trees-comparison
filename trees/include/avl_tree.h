#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>
#include "node.h"
#ifndef  AVL_TREE_H_
#define AVL_TREE_H_
template <class T>
class AVLTree {
private:
    node<T> *RightRotation(node <T> *n) {
        node<T> *p, *p1;
        p = n;
        p1 = p->left;
 
        p->left = p1->right;
        p1->right = p;
 
        p->info = std::max(Height(p->left), Height(p->right));
        p1->info = std::max(Height(p1->left), p->info);
 
        return p1;
    }

    node<T> *LeftRotation(node <T> *n) {
        node<T> *p, *p1;
        p = n;
        p1 = p->right;
 
        p->right = p1->left;
        p1->left = p;
 
        p->info = std::max(Height(p->left), Height(p->right));
        p1->info = std::max(Height(p1->left), p->info);
 
        return p1;
    }

    node<T> *DoubleLeftRotation(node <T> *n) {
        n->right = RightRotation(n->right);
        return LeftRotation(n);
    }
 
    node<T> *DoubleRightRotation(node <T> *n) {    
        n->left = LeftRotation(n->left);
        return RightRotation(n);
    }

    node<T> *DeleteR(node<T> *p, T data) {
        if (p == nullptr) return nullptr;

        if (data < p->data)
            p->left = DeleteR(p->left, data);
        else if (data > p->data) {
            p->right = DeleteR(p->right, data);
        }
        else {
            node<T>* lc = p->left;
            node<T>* rc = p->right;
            delete p;

            if (!rc) return lc;
            node<T>* min = rc;
            while (min->left != nullptr)
                min = min->left;
            min->right = DeleteMinR(rc);
            min->left = lc;

            return Balance(min);
        }
        return Balance(p);
    }

    void CalcHeight(node<T> *p) {

        int lh = Height(p->left);
        int rh = Height(p->right);
        p->info = std::max(lh, rh) + 1;
    }

    int BalanceFactor(node<T> *p) {
        return Height(p->left) - Height(p->right);
    }

    node<T> *Balance(node <T> *p) {
        CalcHeight(p);
 
        if (BalanceFactor(p) > 1 && BalanceFactor(p->left) >= 0) { p = RightRotation(p); rotations_num++; }
        if (BalanceFactor(p) < -1 && BalanceFactor(p->right) <= 0) { p = LeftRotation(p); rotations_num++;}
        if (BalanceFactor(p) > 1 && BalanceFactor(p->left) <0) { p = DoubleRightRotation(p); rotations_num++; }
        if (BalanceFactor(p) < -1 && BalanceFactor(p->right) >0) { p = DoubleLeftRotation(p); rotations_num++; }
        return p;
    }

    node<T> *InsertR(node<T> *p, T data) {

        if (p == nullptr) {
            p = new node<T>(data);
            p->info = 1;
            return p;
        }

        if (data < p->data)
            p->left = InsertR(p->left, data);
        else if (data > p->data)
            p->right = InsertR(p->right, data);
        else
            return p;
        return Balance(p);
    }

    node<T>* DeleteMinR(node<T>* p) {
        if (p->left == nullptr)
            return p->right;
        p->left = DeleteMinR(p->left);
        return Balance(p);
    }

public:
    node<T> *root;
    int rotations_num;

    AVLTree(std::vector<T> inp) : rotations_num(0) {
        for (unsigned int i = 0; i < inp.size(); i++)
            Insert(inp[i]);
    }

    AVLTree() {
        this->root = nullptr;
        rotations_num = 0;
    }

    void Clear(node<T> *p) {
        if (p) {
            Clear(p->left);
            Clear(p->right);
            delete p;
        }
    }

    int Height(node<T> *p) {
        return p ? p->info : 0;
    }

    double Insert(T data) {
        auto start = std::chrono::high_resolution_clock::now();

        rotations_num = 0; 
        root = InsertR(root, data);

        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count());
    }

    double Delete(T data) { 
        auto start = std::chrono::high_resolution_clock::now();

        root = DeleteR(root, data);

        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count());    
    }

    double Search(T data) {
        auto start = std::chrono::high_resolution_clock::now();

        node<T> *cur = root;
        while (cur != nullptr && cur->data != data)
            if (data > cur->data)
                cur = cur->right;
            else
                cur = cur->left;
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count());    
       // return cur ? cur->data : T();
    }

    void printDataInOrder() {
        TraverseInOrder(root);
        std::cout << std::endl;
    }

    void TraverseInOrder(node<T> *root) {
        if (root != nullptr) {
            TraverseInOrder(root->left);
            std::cout << root->data << " ";
            TraverseInOrder(root->right);
        }
    }

    ~AVLTree() {
        Clear(root);
    }

};

#endif  // AVL_TREE_H_