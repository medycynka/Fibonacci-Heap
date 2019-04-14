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

class DotFibonacciHeap : public FibonacciHeap<int> {
public:
    void dump() {
        printf("digraph G {\n");
        if(heap==NULL) {
            printf("empty;\n}\n");
            return;
        }
        cout << "minimum -> " << heap->value << endl;
        node<int>* c=heap;
        do {
            _dumpChildren(c);
            c=c->next;
        } while(c!=heap);
        printf("}\n");
    }

private:
    void _dumpChildren(node<int>* n) {
        cout << "value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> next: " << n->next->value << (n->next->marked ? " (marked)" : " (not marked)") << endl;
        cout << "value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> prev: " << n->prev->value << (n->prev->marked ? " (marked)" : " (not marked)") << endl;
        if(n->hasParent()) cout << "value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> parent: " << n->parent->value << (n->parent->marked ? " (marked)" : " (not marked)") << endl;
        else cout << "No parent" << endl;

        if(n->hasChildren()) {
            node<int>* c=n->child;
            do {
                cout << "parent value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> child: " << n->child->value << (n->child->marked ? " (marked)" : " (not marked)") << endl << endl;
                _dumpChildren(c);
                c=c->next;
            } while(c!=n->child);
        }
        else cout << "No child" << endl;
    }
};


void test() {
    DotFibonacciHeap h;
    for(auto i = 0; i < 11; i++) h.insert(i);

    h.removeMinimum();

    h.dump();
}

int main() {
    cout << setprecision(8) << fixed;

    FibonacciHeap<int> fh;
    for(auto i = 0; i < 11; i++) fh.insert(i);

    fh.removeMinimum();
    fh.displayHeap();

    FibonacciHeap<int> fh_1;
    cout << "Insert and extract-min test for " << test1 << " elements" << endl;
    auto start1_1 = std::chrono::system_clock::now();
    for(auto i = 0; i < test1; ++i) {
        fh_1.insert(i);
    }
    auto end1_1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end1_1 - start1_1;
    cout << "Inserted " << test1 << " elements in " << elapsed_seconds.count() << "s" << endl;

    auto start1_2 = std::chrono::system_clock::now();
    for(auto i = 0; i < test1/1000; ++i){
        fh_1.removeMinimum();
    }
    auto end1_2 = std::chrono::system_clock::now();
    elapsed_seconds = end1_2 - start1_2;
    cout << "Removed minimum " << test1/1000 << " times in " << elapsed_seconds.count() << "s" << endl;
    cout << "Size : " << fh_1.size() << endl << endl;

    FibonacciHeap<int> fh_2;
    cout << "Insert and extract-min test for " << test2 << " elements" << endl;
    auto start2_1 = std::chrono::system_clock::now();
    for(auto i = 0; i < test2; ++i) {
        fh_2.insert(i);
    }
    auto end2_1 = std::chrono::system_clock::now();
    elapsed_seconds = end2_1 - start2_1;
    cout << "Inserted " << test2 << " elements in " << elapsed_seconds.count()<< "s"  << endl;

    auto start2_2 = std::chrono::system_clock::now();
    for(auto i = 0; i < test2/1000; ++i){
        fh_2.removeMinimum();
    }
    auto end2_2 = std::chrono::system_clock::now();
    elapsed_seconds = end2_2 - start2_2;
    cout << "Removed minimum " << test2/1000 << " times in " << elapsed_seconds.count() << "s" << endl;
    cout << "Size : " << fh_2.size() << endl << endl;

    FibonacciHeap<int> fh_3;
    cout << "Insert and extract-min test for " << test3 << " elements" << endl;
    auto start3_1 = std::chrono::system_clock::now();
    for(auto i = 0; i < test3; ++i) {
        fh_3.insert(i);
    }
    auto end3_1 = std::chrono::system_clock::now();
    elapsed_seconds = end3_1 - start3_1;
    cout << "Inserted " << test3 << " elements in " << elapsed_seconds.count() << "s" << endl;

    auto start3_2 = std::chrono::system_clock::now();
    for(auto i = 0; i < test3/1000; ++i){
        fh_3.removeMinimum();
    }
    auto end3_2 = std::chrono::system_clock::now();
    elapsed_seconds = end3_2 - start3_2;
    cout << "Removed minimum " << test3/1000 << " times in " << elapsed_seconds.count() << "s" << endl;
    cout << "Size : " << fh_3.size() << endl << endl;

    FibonacciHeap<int> fh_4;
    cout << "Insert and extract-min test for " << test4 << " elements" << endl;
    auto start4_1 = std::chrono::system_clock::now();
    for(auto i = 0; i < test4; ++i) {
        fh_4.insert(i);
    }
    auto end4_1 = std::chrono::system_clock::now();
    elapsed_seconds = end4_1 - start4_1;
    cout << "Inserted " << test4 << " elements in " << elapsed_seconds.count() << "s" << endl;

    auto start4_2 = std::chrono::system_clock::now();
    for(auto i = 0; i < test4/1000; ++i){
        fh_4.removeMinimum();
    }
    auto end4_2 = std::chrono::system_clock::now();
    elapsed_seconds = end4_2 - start4_2;
    cout << "Removed minimum " << test4/1000 << " times in " << elapsed_seconds.count() << "s" << endl;
    cout << "Size : " << fh_4.size() << endl << endl;

    return 0;
}