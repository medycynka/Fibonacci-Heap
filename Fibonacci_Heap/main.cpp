#include <iostream>
#include <iterator>
#include <chrono>
#include <stdio.h>
#include <iomanip>
#include "fibonacci_heap.hpp"

using namespace std;

const size_t test1 = 10000;        // 10^4
const size_t test2 = 100000;       // 10^5
const size_t test3 = 1000000;      // 10^6
const size_t test4 = 10000000;     // 10^7

int main() {
    cout << setprecision(12) << fixed;

    FibonacciHeap<int> fh;
    for(auto i = 0; i < 11; i++) fh.insert(i);

    fh.displayHeap();
    cout << endl;

    cout << "Iterators test (before minimum extraction):" << endl;
    for(auto &e : fh) cout << e << ", ";
    cout << endl;
    for(const auto &e : fh) cout << e << ", ";
    cout << endl;
    for(auto it = fh.rbegin(); it != fh.rend(); ++it) cout << *it << ", ";
    cout << endl;
    for(auto it = fh.crbegin(); it != fh.crend(); ++it) cout << *it << ", ";
    cout << endl;
    cout << endl;

    fh.removeMinimum();
    fh.displayHeap();

    cout << endl << endl;
    for(auto &e : fh) cout << e << ", ";
    cout << endl;
    for(auto it = fh.rbegin(); it != fh.rend(); ++it) cout << *it << ", ";
    cout << endl;
    fh.clear();
    cout << fh.size() << endl;
    for(auto &e : fh) cout << e << ", ";
    cout << endl << endl;

    /**
     * Test1 for 10000 elements
     */
    cout << endl << "Insert and extract-min test for " << test1 << " elements" << endl;
    auto start = std::chrono::system_clock::now();
    for(auto i = 0; i < test1; ++i) {
        fh.insert(i);
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "Inserted " << test1 << " elements in " << elapsed_seconds.count() << "s" << endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test1/1000; ++i){
        fh.removeMinimum();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Removed minimum " << test1/1000 << " times in " << elapsed_seconds.count() << "s" << endl;
    cout << "Size : " << fh.size() << endl << endl;
    fh.clear();


    /**
     * Test2 for 100000 elements
     */
    cout << "Insert and extract-min test for " << test2 << " elements" << endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test2; ++i) {
        fh.insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Inserted " << test2 << " elements in " << elapsed_seconds.count()<< "s"  << endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test2/1000; ++i){
        fh.removeMinimum();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Removed minimum " << test2/1000 << " times in " << elapsed_seconds.count() << "s" << endl;
    cout << "Size : " << fh.size() << endl << endl;
    fh.clear();


    /**
     * Test3 for 1000000 elements
     */
    cout << "Insert and extract-min test for " << test3 << " elements" << endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test3; ++i) {
        fh.insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Inserted " << test3 << " elements in " << elapsed_seconds.count() << "s" << endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test3/1000; ++i){
        fh.removeMinimum();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Removed minimum " << test3/1000 << " times in " << elapsed_seconds.count() << "s" << endl;
    cout << "Size : " << fh.size() << endl << endl;
    fh.clear();


    /**
     * Test4 for 10000000 elements
     */
    cout << "Insert and extract-min test for " << test4 << " elements" << endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test4; ++i) {
        fh.insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Inserted " << test4 << " elements in " << elapsed_seconds.count() << "s" << endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test4/1000; ++i){
        fh.removeMinimum();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout << "Removed minimum " << test4/1000 << " times in " << elapsed_seconds.count() << "s" << endl;
    cout << "Size : " << fh.size() << endl << endl;
    fh.clear();

    return 0;
}