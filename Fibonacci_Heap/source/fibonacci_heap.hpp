#ifndef FIBONACCIHEAP_FIBONACCI_HEAP_HPP
#define FIBONACCIHEAP_FIBONACCI_HEAP_HPP

#pragma once

#include "fibonacci_iterator.hpp"
#include "fibonacci_reverse_iterator.hpp"
#include "fibonacci_const_iterator.hpp"
#include "fibonacci_const_reverse_iterator.hpp"

namespace algo::ds::fibo {

    template <typename T>
    class FibonacciHeap {
    public:
        /**
         * TODO : make ReverseIterator and ConstReverseIterator work also after minimum extraction (make getPrevNodeForIteration() works corectly)
        */

    protected:
        algo::ds::fibo::node_impl::FiboNode<T>* heap;
        T                                       currMax = -1;
        size_t                                  num_elems;
        bool                                    wasDeletion = false;

    public:
        FibonacciHeap() : heap{ empty_() }, num_elems{ 0 } {};
        explicit FibonacciHeap(algo::ds::fibo::node_impl::FiboNode<T>& s) : heap{ s }, num_elems{ 0 } {};
        FibonacciHeap(const FibonacciHeap& s) : heap{ s.heap }, num_elems{ s.num_elems } {};
        FibonacciHeap(FibonacciHeap&& s) noexcept : heap{ s.heap }, num_elems{ s.num_elems } {};

        algo::ds::fibo::node_impl::FiboNode<T>* insert(T);
        void                                    merge(FibonacciHeap&);
        T                                       removeMinimum();
        void                                    displayHeap();
        void                                    decreaseKey(algo::ds::fibo::node_impl::FiboNode<T>* n, T value) { heap = decreaseKey_(heap, n, value); };
        algo::ds::fibo::node_impl::FiboNode<T>* find(T value) { return find_(heap, value); };
        [[nodiscard]] bool                      isEmpty()                                                 const { return heap == nullptr; };
        [[nodiscard]] size_t                    size()                                                    const { return num_elems; };
        T                                       getMinimum() { return heap->value; };
        algo::ds::fibo::node_impl::FiboNode<T>* getRoot()                                                 const { return heap; };
        algo::ds::fibo::node_impl::FiboNode<T>* getCurrMax()                                              const { return find(currMax); };
        void                                    clear() { while (!isEmpty()) { removeMinimum(); } };

        FibonacciHeap<T>& operator= (const FibonacciHeap<T>& o) { if (this != &o) { num_elems = o.num_elems; wasDeletion = o.wasDeletion; heap = o.heap; } return *this; };
        FibonacciHeap<T>& operator= (FibonacciHeap<T>&& o) noexcept { num_elems = o.num_elems; wasDeletion = o.wasDeletion; heap = o.heap; return *this; };
        bool              operator==(const FibonacciHeap<T>& o) { return (num_elems == o.num_elems && wasDeletion == o.wasDeletion && heap == o.heap); };
        bool              operator!=(const FibonacciHeap<T>& o) { return !(*this == o); };
        FibonacciHeap<T>& operator+ (const FibonacciHeap<T>& o) { merge(o); return *this; };

        algo::ds::fibo::iterators::Iterator<T>             begin() { return algo::ds::fibo::iterators::Iterator<T>(heap, heap, wasDeletion); };
        algo::ds::fibo::iterators::Iterator<T>             end() { return algo::ds::fibo::iterators::Iterator<T>(wasDeletion); };
        algo::ds::fibo::iterators::ConstIterator<T>        cbegin() { return algo::ds::fibo::iterators::ConstIterator<T>(heap, heap, wasDeletion); };
        algo::ds::fibo::iterators::ConstIterator<T>        cend() { return algo::ds::fibo::iterators::ConstIterator<T>(wasDeletion); };
        algo::ds::fibo::iterators::ReverseIterator<T>      rbegin() { return algo::ds::fibo::iterators::ReverseIterator<T>(heap->prev, heap->prev, wasDeletion); };
        algo::ds::fibo::iterators::ReverseIterator<T>      rend() { return algo::ds::fibo::iterators::ReverseIterator<T>(wasDeletion); };
        algo::ds::fibo::iterators::ConstReverseIterator<T> crbegin() { return algo::ds::fibo::iterators::ConstReverseIterator<T>(heap->prev, heap->prev, wasDeletion); };
        algo::ds::fibo::iterators::ConstReverseIterator<T> crend() { return algo::ds::fibo::iterators::ConstReverseIterator<T>(wasDeletion); };

    private:
        algo::ds::fibo::node_impl::FiboNode<T>* empty_() { return nullptr; }
        algo::ds::fibo::node_impl::FiboNode<T>* singleton_(T);
        algo::ds::fibo::node_impl::FiboNode<T>* merge_(algo::ds::fibo::node_impl::FiboNode<T>*, algo::ds::fibo::node_impl::FiboNode<T>*);
        void                                    addChild(algo::ds::fibo::node_impl::FiboNode<T>*, algo::ds::fibo::node_impl::FiboNode<T>*);
        void                                    unMarAndUnParentAll_(algo::ds::fibo::node_impl::FiboNode<T>*);
        algo::ds::fibo::node_impl::FiboNode<T>* removeMinimum_(algo::ds::fibo::node_impl::FiboNode<T>*);
        algo::ds::fibo::node_impl::FiboNode<T>* cut_(algo::ds::fibo::node_impl::FiboNode<T>*, algo::ds::fibo::node_impl::FiboNode<T>*);
        algo::ds::fibo::node_impl::FiboNode<T>* decreaseKey_(algo::ds::fibo::node_impl::FiboNode<T>*, algo::ds::fibo::node_impl::FiboNode<T>*, T);
        algo::ds::fibo::node_impl::FiboNode<T>* find_(algo::ds::fibo::node_impl::FiboNode<T>*, T);
        void                                    displayHeap_(algo::ds::fibo::node_impl::FiboNode<T>*);
        void                                    displayChildrens_(algo::ds::fibo::node_impl::FiboNode<T>*);
    };

    template<class T>
    inline algo::ds::fibo::node_impl::FiboNode<T>* FibonacciHeap<T>::insert(T value) {
        algo::ds::fibo::node_impl::FiboNode<T>* ret = singleton_(value);
        if (ret) {
            num_elems++;

            if (ret->value > currMax) currMax = ret->value;
        }

        heap = merge_(heap, ret);

        return ret;
    }

    template<class T>
    inline void FibonacciHeap<T>::merge(FibonacciHeap& other) {
        heap = merge_(heap, other.heap);
        other.heap = empty_();
    }

    template<class T>
    inline T FibonacciHeap<T>::removeMinimum() {
        auto* old = heap;
        heap = removeMinimum_(heap);
        auto ret = old->value;
        delete old;
        num_elems--;
        wasDeletion = true;

        return ret;
    }

    template<typename T>
    inline void FibonacciHeap<T>::displayHeap() {
        if (isEmpty()) std::cout << "Heap is empty!" << std::endl;
        else displayHeap_(heap);
    }

    template<class T>
    inline algo::ds::fibo::node_impl::FiboNode<T>* FibonacciHeap<T>::singleton_(T value) {
        auto n = new algo::ds::fibo::node_impl::FiboNode<T>;
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
    inline algo::ds::fibo::node_impl::FiboNode<T>* FibonacciHeap<T>::merge_(algo::ds::fibo::node_impl::FiboNode<T>* a, algo::ds::fibo::node_impl::FiboNode<T>* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a->value > b->value) {
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
    inline void FibonacciHeap<T>::addChild(algo::ds::fibo::node_impl::FiboNode<T>* parent, algo::ds::fibo::node_impl::FiboNode<T>* child) {
        child->prev = child;
        child->next = child;
        child->parent = parent;
        parent->degree++;
        parent->child = merge_(parent->child, child);
    }

    template<class T>
    inline void FibonacciHeap<T>::unMarAndUnParentAll_(algo::ds::fibo::node_impl::FiboNode<T>* n) {
        if (n == nullptr) return;

        auto* c = n;

        do {
            c->marked = false;
            c->parent = nullptr;
            c = c->next;
        } while (c != n);
    }

    template<class T>
    inline algo::ds::fibo::node_impl::FiboNode<T>* FibonacciHeap<T>::removeMinimum_(algo::ds::fibo::node_impl::FiboNode<T>* n) {
        unMarAndUnParentAll_(n->child);

        if (n->next == n) n = n->child;
        else {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n = merge_(n->next, n->child);
        }

        if (n == nullptr) return n;

        algo::ds::fibo::node_impl::FiboNode<T>* trees[64] = { nullptr };

        while (true) {
            if (trees[n->degree] != nullptr) {
                auto* t = trees[n->degree];

                if (t == n) break;

                trees[n->degree] = nullptr;

                if (n->value < t->value) {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;
                    addChild(n, t);
                }
                else {
                    t->prev->next = t->next;
                    t->next->prev = t->prev;

                    if (n->next == n) {
                        t->next = t;
                        t->prev = t;
                        addChild(t, n);
                        n = t;
                    }
                    else {
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

        do {
            if (n->value < min->value) min = n;

            n = n->next;
        } while (n != start);

        return min;
    }

    template<class T>
    inline algo::ds::fibo::node_impl::FiboNode<T>* FibonacciHeap<T>::cut_(algo::ds::fibo::node_impl::FiboNode<T>* heap_, algo::ds::fibo::node_impl::FiboNode<T>* n) {
        if (n->next == n) n->parent->child = nullptr;
        else {
            n->next->prev = n->prev;
            n->prev->next = n->next;
            n->parent->child = n->next;
        }

        n->next = n->prev = n;
        n->marked = false;

        return merge_(heap_, n);
    }

    template<class T>
    inline algo::ds::fibo::node_impl::FiboNode<T>* FibonacciHeap<T>::decreaseKey_(algo::ds::fibo::node_impl::FiboNode<T>* heap_, algo::ds::fibo::node_impl::FiboNode<T>* n, T value) {
        if (n->value < value) return heap_;

        n->value = value;

        if (n->parent) {
            if (n->value < n->parent->value) {
                heap_ = cut_(heap_, n);
                auto* parent = n->parent;
                n->parent = nullptr;

                while (parent != nullptr && parent->marked) {
                    heap_ = cut_(heap_, parent);
                    n = parent;
                    parent = n->parent;
                    n->parent = nullptr;
                }

                if (parent != nullptr && parent->parent != nullptr) parent->marked = true;
            }
        }
        else if (n->value < heap_->value) heap_ = n;

        return heap_;
    }

    template<class T>
    inline algo::ds::fibo::node_impl::FiboNode<T>* FibonacciHeap<T>::find_(algo::ds::fibo::node_impl::FiboNode<T>* heap_, T value) {
        auto* n = heap_;

        if (n == nullptr) return nullptr;

        do {
            if (n->value == value) return n;
            auto* ret = find_(n->child, value);

            if (ret) return ret;

            n = n->next;
        } while (n != heap_);

        return nullptr;
    }

    template<typename T>
    inline void FibonacciHeap<T>::displayHeap_(algo::ds::fibo::node_impl::FiboNode<T>* in) {
        if (in) {
            auto* c = in;

            std::cout << "Minimum -> " << heap->value << std::endl;
            do {
                displayChildrens_(c);
                c = c->next;
            } while (c != in);
        }
    }

    template<typename T>
    inline void FibonacciHeap<T>::displayChildrens_(algo::ds::fibo::node_impl::FiboNode<T>* n) {
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
                auto* c = n->child;
                do {
                    std::cout << "parent value: " << n->value << (n->marked ? " (marked)" : " (not marked)")
                        << " -> child: " << n->child->value << (n->child->marked ? " (marked)" : " (not marked)")
                        << std::endl << std::endl;
                    displayChildrens_(c);
                    c = c->next;
                } while (c != n->child);
            }
            else std::cout << "No child" << std::endl;
        }
    }

}

#endif
