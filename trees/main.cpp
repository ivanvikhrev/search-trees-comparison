// Copyright 2020 Vikhrev Ivan

#include <vector>
#include <iostream>
#include <utility>
#include <random>
#include "gtest/gtest.h"
#include "splay_tree.h"
#include "avl_tree.h"
#include "treap.h"
#include "sorted_array.h"
#include "rbtree.h"
using std::vector;
using std::pair;

std::vector<int> randVec(size_t size) {
    // First create an instance of an engine.
    std::random_device rnd_device;
    // Specify the engine and distribution.
    std::mt19937 mersenne_engine{ rnd_device() };  // Generates random integers
    uniform_int_distribution<int> dist{ 1, 52 };

    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };

    vector<int> vec(size);
    std::generate(std::begin(vec), std::end(vec), gen);
    return vec;
}

std::vector<int> UniqueRandN(int n) {
    std::vector<int> res(n);
    for (int i = 0; i < n; i++) res[i] = 2 * i + 1;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(res.begin(), res.end(), g);
    return res;
}

TEST(node, can_create_node_with_data) {
    ASSERT_NO_THROW(node<int> n(5));
}

TEST(avl_tree, can_create_avl_tree) {
    ASSERT_NO_THROW(AVLTree<int> tree);
}

TEST(avl_tree, can_insert_avl_tree) {
    AVLTree<int> tree;
    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(5);
    tree.Insert(6);
   // ASSERT_EQ(tree.Search(1), 1);
   // ASSERT_EQ(tree.Search(6), 6);
}

TEST(treap, can_create_treap) {
    ASSERT_NO_THROW(Treap<int> tree);
}

TEST(rbtree, can_create_rbtree) {
    ASSERT_NO_THROW(RBTree<int> tree);
}

TEST(rbtree, can_insert_in_rbtree) {
    RBTree<int> rb;
    rb.Insert(1);
    rb.Insert(4);
    rb.Insert(2);
    rb.printDataInOrder();
   // ASSERT_EQ(rb.Search(1), 1);
}

TEST(rbtree, find_element_in_rbtree) {
    RBTree<int> rb;
    rb.Insert(1);
    //ASSERT_EQ(rb.Search(2), int());
}

TEST(sorted_array, can_create_sorted_array) {
    ASSERT_NO_THROW(SortedArray<int> tree);
}


TEST(splay_tree, can_create_splay_tree) {
    ASSERT_NO_THROW(SplayTree<int> st); 
}

TEST(splay_tree, can_create_splay_tree_out_of_vec) {
    std::vector<int> v = randVec(10);
    ASSERT_NO_THROW(SplayTree<int> st(v));
}

TEST(splay_tree, splay_tree_out_of_vec_is_correct) {
    std::vector<int> v({ 1,2,3 });
    SplayTree<int> st(v);
    ASSERT_EQ(st.root->data, 3);
    ASSERT_EQ(st.root->left->data, 2);
    ASSERT_EQ(st.root->left-> left->data, 1);
}

TEST(splay_tree, splay_tree_out_of_vec_is_correct2) {
    std::vector<int> v({ 3,2,1 });
    SplayTree<int> st(v);
    ASSERT_EQ(st.root->data, 1);
    ASSERT_EQ(st.root->right->data, 2);
    ASSERT_EQ(st.root->right->right->data, 3);
}
TEST(splay_tree, can_insert_in_empty_splay_tree) {
    SplayTree<int> st;
    st.Insert(5);
    ASSERT_EQ(st.root->data, 5);
}

TEST(splay_tree, can_insert_in_splay_tree_with_only_root) {
    SplayTree<int> st;
    st.Insert(5);
    st.Insert(10);
    ASSERT_EQ(st.root->data, 10);
    ASSERT_EQ(st.root->left->data, 5);
}

TEST(splay_tree, can_search_in_empty_splay_tree) {
    SplayTree<int> st;
    ASSERT_NO_THROW(st.Search(1));
}

TEST(splay_tree, can_search_in_splay_tree) {
    SplayTree<int> st;
    st.Insert(1);
    //ASSERT_EQ(st.Search(1), 1);
    ASSERT_EQ(st.root->data, 1); // data splayed on top after search
}

TEST(splay_tree, can_search_in_splay_tree_with_many_elements) {
    SplayTree<int> st(std::vector<int>({1,2,4,5,6,7}));
    st.Search(4);
    ASSERT_EQ(st.root->data, 4); // data splayed on top after search
}

TEST(splay_tree, can_delete_from_empty_splay_tree) {
    SplayTree<int> st;
   // ASSERT_NO_THROW(st.Delete(1));
}

TEST(splay_tree, can_delete_one_element_at_the_root_of_splay_tree) {
    SplayTree<int> st;
    st.Insert(1);
    st.Delete(1);
    ASSERT_EQ(st.root, nullptr);
}

TEST(splay_tree, can_delete_one_element_from_splay_tree) {
    std::vector<int> v({ 1,2,4,5,6,7 });
    SplayTree<int> st(v);
    st.Delete(1);
    //ASSERT_EQ(st.Search(1), 2);
}

TEST(splay_tree, can_delete_one_element_from_splay_tree2) {
    std::vector<int> v({ 1,2,4,5,6,7 });
    SplayTree<int> st(v);

    st.Delete(7);
    //ASSERT_EQ(st.Search(7), 6); 
}

TEST(splay_tree, can_delete_all_elemens_from_splay_tree) {
    std::vector<int> v({ 1,2,4,5,6,7});
    SplayTree<int> st(v);
    for (auto i : v) {
        st.Delete(i);
    }
    ASSERT_EQ(st.root, nullptr);
}


TEST(splay_tree, can_insert_strings_in_splay_tree) {
    SplayTree<std::string> st;
    st.Insert("a");
    ASSERT_EQ(st.root->data, "a");
}

TEST(splay_tree, strings_in_splay_tree_are_ordered) {
    SplayTree<std::string> st;
    st.Insert("a");
    st.Insert("b");
    st.Insert("c");
    ASSERT_EQ(st.root->data, "c");
    ASSERT_EQ(st.root->left->data, "b");
    ASSERT_EQ(st.root->left->left->data, "a");
}

TEST(treap, can_create_treap_with_strings) {
    ASSERT_NO_THROW(Treap<std::string> st;);
}

TEST(treap, can_create_treap_with_int) {
    ASSERT_NO_THROW(Treap<int> st;);
} 

TEST(treap, stress_test) {
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    Treap<int> st;
    std::vector<int> v = randVec(1000000);

    double mi = 0, md = 0, ms = 0;

    auto start = std::chrono::high_resolution_clock::now();
    int k = 0;
    for (auto el : v) {
        st.Insert(el);
        if (k == 0) { k++; continue; }
        std::uniform_int_distribution<int> uni(0, k);
        for (int i = 0; i < 5; ++i) {
            auto randNum = uni(rng);
            //std::cout << "k is : " <<  k << "rand num is " << randNum << std::endl;
            md += st.Delete(v[randNum]) / 5;
            mi += st.Insert(v[randNum]) / 5;
            ms += st.Search(v[uni(rng)]) / 5;
        }
        k++;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span =
        std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
    std::cout << "time " << time_span.count() << std::endl;
    std::cout << "mi " << mi * 10*10*10 / k << std::endl;
    std::cout << "md " << md * 10 * 10 * 10 / k << std::endl;
    std::cout << "ms " << ms * 10 * 10 * 10 / k << std::endl;
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}