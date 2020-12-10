#include <algorithm>
#include <vector>
#include <iostream>
#include "node.h"

#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_
using namespace std;
using intnode = node<int>;
using stringnode = node<std::string>;

template<class T>
class SplayTree {
private:
    void splay(node<T>* n) {
        if (n == nullptr) {
            return;
        }

        if (n->parent != nullptr) {
            node<T>* p = n->parent;
            if (p->parent == nullptr) {
                if (p->left == n) {
                    zig(n, p);
                }
                else {
                    zag(n, p);
                }
            }
            else {
                node<T>* g = p->parent;
                if (g->left == p && p->left == n) {
                    zig(p, g);
                    zig(n, p);
                }
                else if (g->right == p && p->right == n) {
                    zag(p, g);
                    zag(n, p);
                }
                else {
                    if (p->left == n) {
                        zig(n, p);
                        g->right = n;
                        zag(n, g);
                    }
                    else {
                        zag(n, p);
                        g->left = n;
                        zig(n, g);
                    }
                }
            }
            splay(n);
        }
        else {
            root = n;
        }
    }

    //
    void zig(node<T>* n, node<T>* p) {
        p->left = n->right;
        if (p->left != nullptr) {
            p->left->parent = p;
        }
        n->right = p;
        n->parent = p->parent;
        p->parent = n;
        if (n->parent != nullptr) {
            if (n->parent->left == p) {
                n->parent->left = n;
            }
            else {
                n->parent->right = n;
            }
        }
    }

    //
    void zag(node<T>* n, node<T>* p) {
        p->right = n->left;
        if (p->right != nullptr) {
            p->right->parent = p;
        }
        n->left = p;
        n->parent = p->parent;
        p->parent = n;
        if (n->parent != nullptr) {
            if (n->parent->left == p) {
                n->parent->left = n;
            }
            else {
                n->parent->right = n;
            }
        }
    }
    node<T>* _search(T data, node<T>* n)
    {
        if (n == nullptr) {
            return n;
        }
        else if (data == n->data) {
            return n;
        }
        else {
            node<T>* s = nullptr;
            if (data < n->data)
                s = _search(data, n->left);
            else
                s = _search(data, n->right);

            // if data not found - return last accessed element it path - closest element to the desired one
            if (s == nullptr || (s->data < data && data < n->data)) {
                s = n;
            }

            return s;
        }
    }

    void _insert(T data, node<T>* n) {
        if (n == nullptr) {
            root = new node<T>(data, n);
        }
        else {
            if (data < n->data) {
                if (n->left == nullptr) {
                    n->left = new node<T>(data, n);
                    splay(n->left);
                }
                else
                    _insert(data, n->left);
            }
            else {
                if (n->right == nullptr)
                {
                    n->right = new node<T>(data, n);
                    splay(n->right);
                }
                else {
                    _insert(data, n->right);
                }
            }
        }
    }

    void _delete(node<T>* n) {
        if (n == nullptr)
            return;

        if (n->left == nullptr && n->right == nullptr && n->parent == nullptr) {
            delete n;
            root = nullptr;
        } else {
            splay(n);
            root = merge(n->left, n->right);
            delete n;
        }
    }

    node<T>* merge(node<T>* l, node<T>* r) {
        if (l == nullptr && r == nullptr) {
            return nullptr;
        }
        else if (l == nullptr) {
            r->parent = nullptr;
            return r;
        }
        else if (r == nullptr) {
            l->parent = nullptr;
            return l;
        }
        else {
            node<T>* m = max(l);
            splay(m);
            m->right = r;
            r->parent = m;
            m->parent = nullptr;
            return m;
        }
    }

    node<T>* max(node<T>* n) {
        if (n == nullptr)
            return nullptr;

        if (n->right != nullptr)
            return max(n->right);
        else
            return n;
    }

    std::pair<node<T>*, node<T>*> split(node<T>* n, T data)
    {
        node<T>* x = _search(data, n);
        splay(x);
        if (x == nullptr) {
            return { nullptr, nullptr };
        }
        else {
            if (x->data < data) {
                return { x, nullptr };
            }
            else {
                if (x->left != nullptr)
                    x->left->parent = nullptr;
                node<T>* left = x->left;
                x->left = nullptr;
                return { left, x };
            }
        }
    }

    void Clear(node<T>* p) {
        if (p) {
            Clear(p->left);
            Clear(p->right);
            delete p;
        }
    }

public:
    node<T>* root;

    SplayTree() { root = nullptr; }
    SplayTree(std::vector<T> vec) : SplayTree() {
        for (auto v : vec) {
            Insert(v);
        }
    }

    ~SplayTree() {
        Clear(root);
    }

    T Search(T data) {
        node<T>* x = _search(data, root); // if data not fount return the closest element
        splay(x);
        return x ? x->data : T();
    }

    void Insert(T data) {
        node<T>* s = _search(data, root);
        if (s == nullptr || s->data != data) // unique insert
            _insert(data, root);
        else
            splay(s); // just splay on top
    }

    void Delete(T data) {
        node<T>* s = _search(data, root);
        if (s != nullptr && s->data == data) // data found
            _delete(s);
        else
            splay(s); // just splay on top
    }

    void printDataInOrder() {
        TraverseInOrder(root);
        std::cout << std::endl;
    }

    void TraverseInOrder(node<T>* root) {
        if (root != nullptr) {
            TraverseInOrder(root->left);
            std::cout << root->data << " ";
            TraverseInOrder(root->right);
        }
    }
};

#endif  // SPLAY_TREE_H_