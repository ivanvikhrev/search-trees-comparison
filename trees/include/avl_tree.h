#include <algorithm>
#include <vector>
#include <iostream>
#include "node.h"
#ifndef  AVL_TREE_H_
#define AVL_TREE_H_
template <class T>
class AVLTree {
private:
    node<T> *RightRotation(node<T> *n) {
        node<T> *p, *p1;
        p = n;
        p1 = p->left;

        p->left = p1->right;
        p1->right = p;

        return p1;
    }

    node<T> *LeftRotation(node<T> *n) {
        node<T> *p, *p1;
        p = n;
        p1 = p->right;

        p->right = p1->left;
        p1->left = p;

        return p1;
    }

    node<T> *DoubleLeftRotation(node<T> *n) {
        node<T> *p, *p1, *p2;
        p = n;
        p1 = p->right;
        p2 = p1->left;

        p->right = p2->left;
        p1->left = p2->right;
        p2->left = p;
        p2->right = p1;

        return p2;
    }

    node<T> *DoubleRightRotation(node<T> *n) {
        node<T> *p, *p1, *p2;
        p = n;
        p1 = p->left;
        p2 = p1->right;

        p->left = p2->right;
        p1->right = p2->left;
        p2->right = p;
        p2->left = p1;

        return p2;
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
            while (rc->left != nullptr)
                min = rc;
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

    node<T> *Balance(node<T> *p) {
        CalcHeight(p);

        if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == 1) p = RightRotation(p);
        if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == -1) p = LeftRotation(p);
        if (BalanceFactor(p) == 2 && BalanceFactor(p->left) == 1) p = DoubleRightRotation(p);
        if (BalanceFactor(p) == -2 && BalanceFactor(p->right) == 1) p = DoubleLeftRotation(p);
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

    AVLTree(std::vector<T> inp) {
        for (unsigned int i = 0; i < inp.size(); i++)
            Insert(inp[i]);
    }

    AVLTree() {
        this->root = nullptr;
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

    void Insert(T data) { root = InsertR(root, data); }

    void Delete(T data) { root = DeleteR(root, data); }

    T Search(T data) {
        node<T> *cur = root;
        while (cur != nullptr && cur->data != data)
            if (data > cur->data)
                cur = cur->right;
            else
                cur = cur->left;
        return cur ? cur->data : T();
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