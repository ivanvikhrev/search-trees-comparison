# distutils: language = c++

from libcpp.vector cimport vector
from libcpp.string cimport string
from trees cimport SplayTree, AVLTree, Treap

cdef class SplayTreeInt:
    cdef SplayTree[int] st

    def insert(self, x):
        self.st.Insert(x)

    def search(self, x):
        return self.st.Search(x)

    def delete(self, x):
        return self.st.Delete(x)

    def printData(self):
        self.st.printDataInOrder()

cdef class SplayTreeString:
    cdef SplayTree[string] st

    def insert(self, x):
        self.st.Insert(x)

    def search(self, x):
        return self.st.Search(x)

    def delete(self, x):
        return self.st.Delete(x)

    def printData(self):
        self.st.printDataInOrder()


cdef class AVLTreeInt:
    cdef AVLTree[int] tree
    
    @property
    def rotations_num(self):
        return self.tree.rotations_num

    def insert(self, x):
        self.tree.Insert(x)

    def search(self, x):
        return self.tree.Search(x)

    def delete(self, x):
        return self.tree.Delete(x)

    def printData(self):
        self.tree.printDataInOrder()

cdef class AVLTreeString:
    cdef AVLTree[string] tree

    def insert(self, x):
        self.tree.Insert(x)

    def search(self, x):
        return self.tree.Search(x)

    def delete(self, x):
        return self.tree.Delete(x)

    def printData(self):
        self.tree.printDataInOrder()

cdef class TreapInt:
    cdef Treap[int] tree

    def insert(self, x):
        self.tree.Insert(x)

    def search(self, x):
        return self.tree.Search(x)

    def delete(self, x):
        return self.tree.Delete(x)

    def printData(self):
        self.tree.printDataInOrder()

cdef class TreapString:
    cdef Treap[string] tree

    def insert(self, x):
        self.tree.Insert(x)

    def search(self, x):
        return self.tree.Search(x)

    def delete(self, x):
        return self.tree.Delete(x)

    def printData(self):
        self.tree.printDataInOrder()

cdef class RBTreeInt:
    cdef RBTree[int] tree

    def insert(self, x):
        self.tree.Insert(x)

    def search(self, x):
        return self.tree.Search(x)

    def delete(self, x):
        return self.tree.Delete(x)

    def printData(self):
        self.tree.printDataInOrder()

cdef class RBTreeString:
    cdef RBTree[string] tree

    def insert(self, x):
        self.tree.Insert(x)

    def search(self, x):
        return self.tree.Search(x)

    def delete(self, x):
        return self.tree.Delete(x)

    def printData(self):
        self.tree.printDataInOrder()

cdef class SortedArrInt:
    cdef SortedArray[int] tree

    def insert(self, x):
        self.tree.Insert(x)

    def search(self, x):
        return self.tree.Search(x)

    def delete(self, x):
        return self.tree.Delete(x)

    def printData(self):
        self.tree.printDataInOrder()


cdef class SortedArrString:
    cdef SortedArray[string] tree

    def insert(self, x):
        self.tree.Insert(x)

    def search(self, x):
        return self.tree.Search(x)

    def delete(self, x):
        return self.tree.Delete(x)

    def printData(self):
        self.tree.printDataInOrder()