
cdef extern from "../trees/include/splay_tree.h":
    cdef cppclass SplayTree[T]:
        SplayTree()
        void Insert(T)
        T Search(T)
        void Delete(T)
        void printDataInOrder()

cdef extern from "../trees/include/avl_tree.h":
    cdef cppclass AVLTree[T]:
        int rotations_num
        AVLTree()
        void Insert(T)
        T Search(T)
        void Delete(T)
        void printDataInOrder()

cdef extern from "../trees/include/treap.h":
    cdef cppclass Treap[T]:
        Treap()
        void Insert(T)
        T Search(T)
        void Delete(T)
        void printDataInOrder()

cdef extern from "../trees/include/sorted_array.h":
    cdef cppclass SortedArray[T]:
        SortedArray()
        void Insert(T)
        T Search(T)
        void Delete(T)
        void printDataInOrder()

cdef extern from "../trees/include/rbtree.h":
    cdef cppclass RBTree[T]:
        SortedArray()
        void Insert(T)
        T Search(T)
        void Delete(T)
        void printDataInOrder()