#ifndef FIBONACCIHEAP_FIBONACCI_CONST_ITERATOR_HPP
#define FIBONACCIHEAP_FIBONACCI_CONST_ITERATOR_HPP

#pragma once

#include "fibonacci_node.hpp"

namespace algo::ds::fibo::iterators {

    template <typename T>
    class ConstIterator {
    private:
        algo::ds::fibo::node_impl::FiboNode<T>* Iter;
        algo::ds::fibo::node_impl::FiboNode<T>* pomHeap;
        bool                                    wasExtraction;

    public:
        typedef ConstIterator             self_type;
        typedef T                         value_type;
        typedef T&                        reference;
        typedef T*                        pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int                       difference_type;

        ConstIterator()                                                                                              : Iter{ nullptr }, pomHeap{ nullptr }, wasExtraction{ false } {};
        ConstIterator(const ConstIterator& s)                                                                        : Iter{ s.Iter }, pomHeap{ s.pomHeap }, wasExtraction{ s.wasExtraction } {};
        ConstIterator(ConstIterator&& s) noexcept                                                                    : Iter{ s.Iter }, pomHeap{ s.pomHeap }, wasExtraction{ s.wasExtraction } {};
        explicit ConstIterator(algo::ds::fibo::node_impl::FiboNode<T>* s)                                            : Iter{ s }, pomHeap{ nullptr }, wasExtraction{ false } {};
        explicit ConstIterator(bool& s)                                                                              : Iter{ nullptr }, pomHeap{ nullptr }, wasExtraction{ s } {}
        ConstIterator(algo::ds::fibo::node_impl::FiboNode<T>* s, algo::ds::fibo::node_impl::FiboNode<T>* h)          : Iter{ s }, pomHeap{ h }, wasExtraction{ false } {};
        ConstIterator(algo::ds::fibo::node_impl::FiboNode<T>* s, algo::ds::fibo::node_impl::FiboNode<T>* h, bool& w) : Iter{ s }, pomHeap{ h }, wasExtraction{ w } {};

        ConstIterator const operator++                                             ();
        ConstIterator const operator++                                             (int);
        ConstIterator const operator--                                             ();
        ConstIterator const operator--                                             (int);
        ConstIterator&      operator=                                              (const ConstIterator& source)       { if (this != &source) { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; } return (*this); };
        ConstIterator&      operator=                                              (ConstIterator&& source)   noexcept { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
        bool                operator==                                             (const ConstIterator& source) const { return (Iter == source.Iter); };
        bool                operator!=                                             (const ConstIterator& source) const { return (Iter != source.Iter); };
        explicit            operator algo::ds::fibo::node_impl::FiboNode<T>&       ()                                  { return (*Iter); };
        explicit            operator const algo::ds::fibo::node_impl::FiboNode<T>& ()                            const { return (*Iter); };
        T const&            operator*                                              ()                            const { return (Iter->value); };
        algo::ds::fibo::node_impl::FiboNode<T> const* operator->                   ()                            const { return Iter; };
        explicit            operator bool()                                                                      const { return (Iter != nullptr); };
    };

    template<typename T>
    ConstIterator<T> const ConstIterator<T>::operator++() {
        if (!wasExtraction) {
            if (this->Iter->next != this->pomHeap) this->Iter = Iter->next;
            else this->Iter = nullptr;
        }
        else {
            this->Iter = this->Iter->getNextNodeForIteration();
        }

        return *this;
    }

    template<typename T>
    ConstIterator<T> const ConstIterator<T>::operator++(int) {
        auto pom = *this;
        ++(*this);

        return pom;
    }

    template<typename T>
    ConstIterator<T> const ConstIterator<T>::operator--() {
        if (!wasExtraction) {
            if (this->Iter->prev != this->pomHeap) this->Iter = Iter->prev;
            else this->Iter = nullptr;
        }
        else this->Iter = this->Iter->getPrevNodeForIteration();

        return *this;
    }

    template<typename T>
    ConstIterator<T> const ConstIterator<T>::operator--(int) {
        auto pom = *this;
        --(*this);

        return pom;
    }

}

#endif
