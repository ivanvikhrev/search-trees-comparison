#ifndef TREAP_H_
#define TREAP_H_
template <class T>
class Treap {
    node <T> *LeftRotation(node <T> *p) {
        node <T> *p1 = p->right;
        node <T> *p2 = p->right->left;
        p1->left = p;
        p->right = p2;
        p = p1;
        return p;
    }

    node <T> *RightRotation(node <T> *p) {
        node <T> *p1 = p->left;
        node <T> *p2 = p->left->right;
        p1->right = p;
        p->left = p2;
        p = p1;
        return p;
    }

    node <T> *InsertR(node <T>* p, T data) {
        if (p == nullptr) {
            p = new node <T>(data);
            p->info = rand() % 100;
            return p;
        }
        if (data < p->data) {
            p->left = InsertR(p->left, data);
            if (p->left != nullptr && p->left->info > p->info)
                p = RightRotation(p);
        }
        else {
            p->right = InsertR(p->right, data);
            if (p->right != nullptr && p->right->info > p->info)
                p = LeftRotation(p);
        }
        return p;
    }

    node<T> *DeleteR(node<T> *p, T data) {
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
                node<T> * child = (p->left != nullptr) ? p->left : p->right;
                delete p;
                p = child;
            }
            return p;
        }
        return p;
    }
public:
    node <T> *root;
    Treap(std::vector<T> inp) {
        for (unsigned int i = 0; i < inp.size(); i++)
            Insert(inp[i]);
    }
    Treap() {
        this->root = nullptr;
    }

    double Insert(T data) {
        auto start = std::chrono::high_resolution_clock::now();

        root = InsertR(root, data);
             
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
        //return cur ? cur->data : T();
    }

    double Delete(T data) {
        auto start = std::chrono::high_resolution_clock::now();
        
        root = DeleteR(root, data);

        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> time_span = 
            std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        return static_cast<double>(time_span.count());     
    
    }

    void printDataInOrder() {
        TraverseInOrder(root);
        std::cout << std::endl;
    }

    void TraverseInOrder(node <T> *root)
    {
        if (root != nullptr)
        {
            TraverseInOrder(root->left);
            std::cout << root->data << " ";
            TraverseInOrder(root->right);
        }
    }
};
#endif  // TREAP_H_