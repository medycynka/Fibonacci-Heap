#ifndef FIBONACCIHEAP_EXAMPLE_HPP
#define FIBONACCIHEAP_EXAMPLE_HPP

#include <iostream>
#include <iterator>
#include <chrono>
#include <cstdio>
#include <iomanip>
#include "fibonacci_heap.hpp"


const size_t test1 = 10000;        // 10^4
const size_t test2 = 100000;       // 10^5
const size_t test3 = 1000000;      // 10^6
const size_t test4 = 10000000;     // 10^7


void example(){
    std::cout << std::setprecision(12) << std::fixed;

    FibonacciHeap<int> fh;
    for(auto i = 0; i < 11; i++) fh.insert(i);

    fh.displayHeap();
    std::cout << std::endl;

    std::cout << "Iterators test (before minimum extraction):" << std::endl;
    for(auto &e : fh) std::cout << e << ", ";
    std::cout << std::endl;
    for(const auto &e : fh) std::cout << e << ", ";
    std::cout << std::endl;
    for(auto it = fh.rbegin(); it != fh.rend(); ++it) std::cout << *it << ", ";
    std::cout << std::endl;
    for(auto it = fh.crbegin(); it != fh.crend(); ++it) std::cout << *it << ", ";
    std::cout << std::endl;
    std::cout << std::endl;

    fh.removeMinimum();
    fh.displayHeap();

    std::cout << std::endl << std::endl;
    for(auto &e : fh) std::cout << e << ", ";
    std::cout << std::endl;
    for(auto it = fh.rbegin(); it != fh.rend(); ++it) std::cout << *it << ", ";
    std::cout << std::endl;
    fh.clear();
    std::cout << fh.size() << std::endl;
    for(auto &e : fh) std::cout << e << ", ";
    std::cout << std::endl << std::endl;

    /**
     * Test1 for 10000 elements
     */
    std::cout << std::endl << "Insert and extract-min test for " << test1 << " elements" << std::endl;
    auto start = std::chrono::system_clock::now();
    for(auto i = 0; i < test1; ++i) {
        fh.insert(i);
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Inserted " << test1 << " elements in " << elapsed_seconds.count() << "s" << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test1/1000; ++i){
        fh.removeMinimum();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Removed minimum " << test1/1000 << " times in " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << "Size : " << fh.size() << std::endl << std::endl;
    fh.clear();


    /**
     * Test2 for 100000 elements
     */
    std::cout << "Insert and extract-min test for " << test2 << " elements" << std::endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test2; ++i) {
        fh.insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Inserted " << test2 << " elements in " << elapsed_seconds.count()<< "s"  << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test2/1000; ++i){
        fh.removeMinimum();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Removed minimum " << test2/1000 << " times in " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << "Size : " << fh.size() << std::endl << std::endl;
    fh.clear();


    /**
     * Test3 for 1000000 elements
     */
    std::cout << "Insert and extract-min test for " << test3 << " elements" << std::endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test3; ++i) {
        fh.insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Inserted " << test3 << " elements in " << elapsed_seconds.count() << "s" << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test3/1000; ++i){
        fh.removeMinimum();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Removed minimum " << test3/1000 << " times in " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << "Size : " << fh.size() << std::endl << std::endl;
    fh.clear();


    /**
     * Test4 for 10000000 elements
     */
    std::cout << "Insert and extract-min test for " << test4 << " elements" << std::endl;
    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test4; ++i) {
        fh.insert(i);
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Inserted " << test4 << " elements in " << elapsed_seconds.count() << "s" << std::endl;

    start = std::chrono::system_clock::now();
    for(auto i = 0; i < test4/1000; ++i){
        fh.removeMinimum();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Removed minimum " << test4/1000 << " times in " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << "Size : " << fh.size() << std::endl << std::endl;
    fh.clear();
}

#endif //FIBONACCIHEAP_EXAMPLE_HPP
