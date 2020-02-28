#ifndef FIBONACCIHEAP_FIBONACCI_HEAP_HPP
#define FIBONACCIHEAP_FIBONACCI_HEAP_HPP

#pragma once

#include "fibonacci_node.hpp"
#include "fibonacci_iterator.hpp"
#include "fibonacci_reverse_iterator.hpp"
#include "fibonacci_const_iterator.hpp"
#include "fibonacci_const_reverse_iterator.hpp"

template <typename T>
class FibonacciHeap{
public:
    /**
     * TODO : make ReverseIterator and ConstReverseIterator work also after minimum extraction (make getPrevNodeForIteration() works corectly)
    */

protected:
    FiboNode<T>* heap;
    T            currMax = T();
    size_t       num_elems;
    bool         wasDeletion = false;

public:
    FibonacciHeap()                           : heap(empty_()), num_elems(0){};
    explicit FibonacciHeap(FiboNode<T> &s)    : heap(s), num_elems(0){};
    FibonacciHeap(const FibonacciHeap &s)     : heap(s.heap), num_elems(s.num_elems){};
    FibonacciHeap(FibonacciHeap &&s) noexcept : heap(s.heap), num_elems(s.num_elems){};

    inline FiboNode<T>* insert(T);
    inline void         merge(FibonacciHeap&);
    inline T            removeMinimum();
    inline void         displayHeap();
    inline void         decreaseKey(FiboNode<T>* n, T value) { heap = decreaseKey_(heap, n, value); };
    inline FiboNode<T>* find(T value)                        { return find_(heap, value); };
    [[nodiscard]] inline bool   isEmpty()              const { return heap == nullptr; };
    [[nodiscard]] inline size_t size()                 const { return num_elems; };
    inline T            getMinimum()                         { return heap->value; };
    inline FiboNode<T>* getRoot()                      const { return heap; };
    inline FiboNode<T>* getCurrMax()                   const { return find(currMax); };
    inline void         clear()                              { while(!isEmpty()){ removeMinimum(); } };

    FibonacciHeap<T>& operator= (const FibonacciHeap<T> &o)     { if(this != &o){ num_elems = o.num_elems; wasDeletion = o.wasDeletion; heap = o.heap; } return *this; };
    FibonacciHeap<T>& operator= (FibonacciHeap<T> &&o) noexcept { num_elems = o.num_elems; wasDeletion = o.wasDeletion; heap = o.heap; return *this; };
    bool              operator==(const FibonacciHeap<T> &o)     { return (num_elems == o.num_elems && wasDeletion == o.wasDeletion && heap == o.heap); };
    bool              operator!=(const FibonacciHeap<T> &o)     { return !(*this == o); };
    FibonacciHeap<T>& operator+ (const FibonacciHeap<T> &o)     { merge(o); return *this; };

    inline Iterator<T>             begin()   { return Iterator<T>(heap, heap, wasDeletion); };
    inline Iterator<T>             end()     { return Iterator<T>(wasDeletion); };
    inline ConstIterator<T>        cbegin()  { return ConstIterator<T>(heap, heap, wasDeletion); };
    inline ConstIterator<T>        cend()    { return ConstIterator<T>(wasDeletion); };
    inline ReverseIterator<T>      rbegin()  { return ReverseIterator<T>(heap->prev, heap->prev, wasDeletion); };
    inline ReverseIterator<T>      rend()    { return ReverseIterator<T>(wasDeletion); };
    inline ConstReverseIterator<T> crbegin() { return ConstReverseIterator<T>(heap->prev, heap->prev, wasDeletion); };
    inline ConstReverseIterator<T> crend()   { return ConstReverseIterator<T>(wasDeletion); };

private:
    inline FiboNode<T>* empty_(){ return nullptr; }
    inline FiboNode<T>* singleton_(T);
    inline FiboNode<T>* merge_(FiboNode<T>*, FiboNode<T>*);
    inline void         addChild(FiboNode<T>*, FiboNode<T>*);
    inline void         unMarAndUnParentAll_(FiboNode<T>*);
    inline FiboNode<T>* removeMinimum_(FiboNode<T>*);
    inline FiboNode<T>* cut_(FiboNode<T>*, FiboNode<T>*);
    inline FiboNode<T>* decreaseKey_(FiboNode<T>*, FiboNode<T>*, T);
    inline FiboNode<T>* find_(FiboNode<T>*, T);
    inline void         displayHeap_(FiboNode<T>*);
    inline void         displayChildrens_(FiboNode<T>*);
};

template<class T>
FiboNode<T> *FibonacciHeap<T>::insert(T value){
    FiboNode<T>* ret = singleton_(value);
    if(ret){
        num_elems++;

        if(ret->value > currMax) currMax = ret->value;
    }

    heap = merge_(heap, ret);

    return ret;
}

template<class T>
void FibonacciHeap<T>::merge(FibonacciHeap &other){
    heap = merge_(heap, other.heap);
    other.heap = empty_();
}

template<class T>
T FibonacciHeap<T>::removeMinimum(){
    auto* old = heap;
    heap = removeMinimum_(heap);
    auto ret = old->value;
    delete old;
    num_elems--;
    wasDeletion = true;

    return ret;
}

template<typename T>
void FibonacciHeap<T>::displayHeap(){
    if(isEmpty()) std::cout << "Heap is empty!" << std::endl;
    else displayHeap_(heap);
}

template<class T>
FiboNode<T> *FibonacciHeap<T>::singleton_(T value){
    auto n = new FiboNode<T>;
    n->value = value;
    n->prev = n;
    n->next = n;
    n->degree = 0;
    n->marked = false;
    n->child = nullptr;
    n->parent = nullptr;

    return n;
}

template<class T>
FiboNode<T> *FibonacciHeap<T>::merge_(FiboNode<T> *a, FiboNode<T> *b){
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(a->value > b->value){
        auto* temp = a;
        a = b;
        b = temp;
    }

    auto* an = a->next;
    auto* bp = b->prev;
    a->next = b;
    b->prev = a;
    an->prev = bp;
    bp->next = an;

    return a;
}

template<class T>
void FibonacciHeap<T>::addChild(FiboNode<T> *parent, FiboNode<T> *child){
    child->prev = child;
    child->next = child;
    child->parent = parent;
    parent->degree++;
    parent->child = merge_(parent->child, child);
}

template<class T>
void FibonacciHeap<T>::unMarAndUnParentAll_(FiboNode<T> *n){
    if(n == nullptr) return;

    auto* c = n;

    do{
        c->marked = false;
        c->parent = nullptr;
        c = c->next;
    }while(c != n);
}

template<class T>
FiboNode<T> *FibonacciHeap<T>::removeMinimum_(FiboNode<T> *n){
    unMarAndUnParentAll_(n->child);

    if(n->next == n) n = n->child;
    else{
        n->next->prev = n->prev;
        n->prev->next = n->next;
        n = merge_(n->next, n->child);
    }

    if(n == nullptr) return n;

    FiboNode<T>* trees[64] = {nullptr};

    while(true){
        if(trees[n->degree]!=nullptr){
            auto* t = trees[n->degree];

            if(t == n) break;

            trees[n->degree] = nullptr;

            if(n->value < t->value){
                t->prev->next = t->next;
                t->next->prev = t->prev;
                addChild(n, t);
            }
            else{
                t->prev->next = t->next;
                t->next->prev = t->prev;

                if(n->next == n){
                    t->next = t;
                    t->prev = t;
                    addChild(t, n);
                    n = t;
                }
                else{
                    n->prev->next = t;
                    n->next->prev = t;
                    t->next = n->next;
                    t->prev = n->prev;
                    addChild(t, n);
                    n = t;
                }
            }

            continue;
        }
        else  trees[n->degree] = n;

        n = n->next;
    }

    auto* min = n;
    auto* start = n;

    do{
        if(n->value < min->value) min=n;

        n = n->next;
    }while(n!=start);

    return min;
}

template<class T>
FiboNode<T> *FibonacciHeap<T>::cut_(FiboNode<T> *heap_, FiboNode<T> *n){
    if(n->next == n) n->parent->child = nullptr;
    else{
        n->next->prev = n->prev;
        n->prev->next = n->next;
        n->parent->child = n->next;
    }

    n->next = n->prev=n;
    n->marked = false;

    return merge_(heap_, n);
}

template<class T>
FiboNode<T> *FibonacciHeap<T>::decreaseKey_(FiboNode<T> *heap_, FiboNode<T> *n, T value){
    if(n->value < value) return heap_;

    n->value = value;

    if(n->parent){
        if(n->value < n->parent->value) {
            heap_ = cut_(heap_, n);
            auto* parent = n->parent;
            n->parent = nullptr;

            while(parent != nullptr && parent->marked) {
                heap_ = cut_(heap_, parent);
                n = parent;
                parent = n->parent;
                n->parent = nullptr;
            }

            if(parent != nullptr && parent->parent != nullptr) parent->marked = true;
        }
    }
    else if(n->value < heap_->value) heap_ = n;

    return heap_;
}

template<class T>
FiboNode<T> *FibonacciHeap<T>::find_(FiboNode<T> *heap_, T value){
    auto* n = heap_;

    if(n == nullptr) return nullptr;

    do{
        if(n->value == value) return n;
        auto* ret = find_(n->child, value);

        if(ret) return ret;

        n = n->next;
    }while(n != heap_);

    return nullptr;
}

template<typename T>
void FibonacciHeap<T>::displayHeap_(FiboNode<T> *in) {
    if(in){
        auto *c = in;

        std::cout << "Minimum -> " << heap->value << std::endl;
        do{
            displayChildrens_(c);
            c = c->next;
        } while(c != in);
    }
}

template<typename T>
void FibonacciHeap<T>::displayChildrens_(FiboNode<T> *n) {
    if (n) {
        std::cout << "value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> next: "
                  << n->next->value << (n->next->marked ? " (marked)" : " (not marked)") << std::endl;
        std::cout << "value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> prev: "
                  << n->prev->value << (n->prev->marked ? " (marked)" : " (not marked)") << std::endl;
        if (n->hasParent())
            std::cout << "value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> parent: "
                      << n->parent->value << (n->parent->marked ? " (marked)" : " (not marked)") << std::endl;
        else std::cout << "No parent" << std::endl;

        if (n->hasChildren()) {
            auto *c = n->child;
            do {
                std::cout << "parent value: " << n->value << (n->marked ? " (marked)" : " (not marked)")
                          << " -> child: " << n->child->value << (n->child->marked ? " (marked)" : " (not marked)")
                          << std::endl << std::endl;
                displayChildrens_(c);
                c = c->next;
            } while (c != n->child);
        } else std::cout << "No child" << std::endl;
    }
}

#endif //FIBONACCIHEAP_FIBONACCI_HEAP_HPP
