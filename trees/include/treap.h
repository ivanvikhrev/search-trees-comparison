#include <random>
#ifndef TREAP_H_
#define TREAP_H_
template <class T>
class Treap {
    node<T, size_t> *LeftRotation(node<T, size_t> *p) {
        node<T, size_t> *p1 = p->right;
        node<T, size_t> *p2 = p->right->left;
        p1->left = p;
        p->right = p2;
        p = p1;
        return p;
    }

    node<T, size_t> *RightRotation(node<T, size_t> *p) {
        node<T, size_t> *p1 = p->left;
        node<T, size_t> *p2 = p->left->right;
        p1->right = p;
        p->left = p2;
        p = p1;
        return p;
    }

    node<T, size_t> *InsertR(node<T, size_t>* p, T data) {
        if (p == nullptr) {
            p = new node<T, size_t>(data);
            p->info = dist(gen);
            return p;
        }
        if (data < p->data) {
            p->left = InsertR(p->left, data);
            if (p->left != nullptr && p->left->info > p->info)
                p = RightRotation(p);
        }
        else if (data > p->data) {
            p->right = InsertR(p->right, data);
            if (p->right != nullptr && p->right->info > p->info)
                p = LeftRotation(p);
        }
        return p;
    }

    node<T, size_t> *DeleteR(node<T, size_t> *p, T data) {
        if (p == nullptr) return nullptr;
        if (data < p->data)
            p->left = DeleteR(p->left, data);
        else if (data > p->data)
            p->right = DeleteR(p->right, data);
        else {
            if (p->left == nullptr && p->right == nullptr) {
                delete p;
                p = nullptr;
            }
            else if (p->left && p->right) {
                if (p->left->info < p->right->info) {
                    p = LeftRotation(p);
                    p->left = DeleteR(p->left, data);
                }
                else {
                    p = RightRotation(p);
                    p->right = DeleteR(p->right, data);
                }
            }
            else {
                node<T, size_t> * child = (p->left != nullptr) ? p->left : p->right;
                delete p;
                p = child;
            }
            return p;
        }
        return p;
    }

    void Clear(node<T, size_t>* p) {
        if (p) {
            Clear(p->left);
            Clear(p->right);
            delete p;
        }
    }
public:
    node <T, size_t> *root;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<size_t> dist;

    Treap(std::vector<T> inp) {
        root = nullptr;
        for (unsigned int i = 0; i < inp.size(); i++)
            Insert(inp[i]);
    }

    Treap() : gen(rd()), dist(0, std::numeric_limits<size_t>::max()) {
      this->root = nullptr;
    }

    ~Treap() {
        Clear(root);
    }

    double Insert(T data) {
        auto start = std::chrono::high_resolution_clock::now();

        root = InsertR(root, data);

        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span =
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        //BrokenStateCheck(root);
        return static_cast<double>(time_span.count());
    }

    double Search(T data) {
        auto start = std::chrono::high_resolution_clock::now();

        node<T, size_t> *cur = root;
        while (cur != nullptr && cur->data != data)
            if (data > cur->data)
                cur = cur->right;
            else
                cur = cur->left;

        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span =
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        //BrokenStateCheck(root);
        return static_cast<double>(time_span.count());
        //return cur ? cur->data : T();
    }

    double Delete(T data) {
        auto start = std::chrono::high_resolution_clock::now();

        root = DeleteR(root, data);

        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span =
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        //BrokenStateCheck(root);
        return static_cast<double>(time_span.count());

    }

    void printDataInOrder() {
        TraverseInOrder(root);
        std::cout << std::endl;
    }

    void TraverseInOrder(node<T, size_t> *root)
    {
        if (root != nullptr)
        {
            TraverseInOrder(root->left);
            std::cout << root->data << " ";
            TraverseInOrder(root->right);
        }
    }

    void BrokenStateCheck(node<T, size_t> *p) {
        if (p != nullptr) {
            if (p->left != nullptr) {
                if (p->left->data > p->data)
                    std::cout << "Broken BST\n";
                if (p->left->info > p->info)
                    std::cout << "Broken Heap\n";
                BrokenStateCheck(p->left);
            }
            if (p->right != nullptr) {
                if (p->right->data < p->data)
                    std::cout << "Broken BST\n";
                if (p->right->info > p->info)
                    std::cout << "Broken Heap\n";
                BrokenStateCheck(p->right);
            }
        }
    }
};
#endif  // TREAP_H_