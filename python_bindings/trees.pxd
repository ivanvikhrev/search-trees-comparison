
cdef extern from "../trees/include/splay_tree.h":
    cdef cppclass SplayTree[T]:
        SplayTree()
        double Insert(T)
        double Search(T)
        double Delete(T)
        void printDataInOrder()

cdef extern from "../trees/include/avl_tree.h":
    cdef cppclass AVLTree[T]:
        int rotations_num;
        AVLTree()
        double Insert(T)
        double Search(T)
        double Delete(T)
        void printDataInOrder()

cdef extern from "../trees/include/treap.h":
    cdef cppclass Treap[T]:
        Treap()
        double Insert(T)
        double Search(T)
        double Delete(T)
        void printDataInOrder()

cdef extern from "../trees/include/sorted_array.h":
    cdef cppclass SortedArray[T]:
        SortedArray()
        double Insert(T)
        double Search(T)
        double Delete(T)
        void printDataInOrder()

cdef extern from "../trees/include/rbtree.h":
    cdef cppclass RBTree[T]:
        SortedArray()
        double Insert(T)
        double Search(T)
        double Delete(T)
        void printDataInOrder()