#include <string>
#include <random>
#include <chrono> 
#include "searchtrees.h"
using namespace std::chrono;
std::vector<int> UniqueRandN(int n) {
    std::vector<int> res(n);
    for (int i = 0; i < n; i++) res[i] = 2 * i + 1;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(res.begin(), res.end(), g);
    return res;
}

std::vector<std::string> UniqueRandS(int n) {
    std::string letters = "adhtiyxrokuinb";
    std::vector<std::string> res(n);
    int l = int(log10(n) + 1);
    for (int i = 0; i < n; i++) {
        int p = 2 * i + 1; 
        res[i] = "";
        for (int j = 0; j < l; j++) {
            res[i] += letters[p % 10];
            p /= 10;
        }
        
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(res.begin(), res.end(), g);
    return res;
}

int main() {
    int n = 10;
    std::vector<int> init = UniqueRandN(n);
    Treap<int> test(init);
    test.Insert(4);
    test.Delete(5);
    test.TraverseInOrder(test.root);
    //test.Delete(5);
    //AVLTree<int> test;
    //for (int i = 0; i < n/2; i++) {

    //    auto start = high_resolution_clock::now();
    //    test.Insert(init[i]);
    //    auto stop = high_resolution_clock::now();
    //    auto duration = duration_cast<microseconds>(stop - start).count();
    //    std::cout << "Insert in " << i << " size tree: " << (double)duration / 1000 << std::endl;
    //}
    return 0;
}