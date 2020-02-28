#ifndef FIBONACCIHEAP_FIBONACCI_REVERSE_ITERATOR_HPP
#define FIBONACCIHEAP_FIBONACCI_REVERSE_ITERATOR_HPP

#pragma once

#include "fibonacci_node.hpp"


template <typename T>
class ReverseIterator{
private:
    FiboNode<T> * Iter;
    FiboNode<T> * pomHeap;
    bool          wasExtraction;

public:
    typedef ReverseIterator           self_type;
    typedef T                         value_type;
    typedef T&                        reference;
    typedef T*                        pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int                       difference_type;

    ReverseIterator()                                        : Iter(nullptr), pomHeap(nullptr), wasExtraction(false){};
    ReverseIterator(const ReverseIterator &s)                : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
    ReverseIterator(ReverseIterator &&s) noexcept            : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
    explicit ReverseIterator(FiboNode<T> *s)                 : Iter(s), pomHeap(nullptr), wasExtraction(false){};
    explicit ReverseIterator(bool &s)                        : Iter(nullptr), pomHeap(nullptr), wasExtraction(s){}
    ReverseIterator(FiboNode<T> *s, FiboNode<T> *h)          : Iter(s), pomHeap(h), wasExtraction(false){};
    ReverseIterator(FiboNode<T> *s, FiboNode<T> *h, bool &w) : Iter(s), pomHeap(h), wasExtraction(w){};

    ReverseIterator       operator++                   ();
    const ReverseIterator operator++                   (int);
    ReverseIterator       operator--                   ();
    const ReverseIterator operator--                   (int);
    ReverseIterator &     operator=                    (const ReverseIterator &source)       { if(this != &source){ Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; } return (*this); };
    ReverseIterator &     operator=                    (ReverseIterator &&source)   noexcept { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
    bool                  operator==                   (const ReverseIterator& source) const { return (Iter == source.Iter); };
    bool                  operator!=                   (const ReverseIterator& source) const { return (Iter != source.Iter); };
    explicit              operator FiboNode<T> &       ()                                    { return (*Iter); };
    explicit              operator const FiboNode<T> & ()                              const { return (*Iter); };
    T &                   operator*                    ()                              const { return (Iter->value); };
    FiboNode<T> *         operator->                   ()                              const { return Iter; };
    explicit              operator bool                ()                              const { return (Iter != nullptr); };
};

template<typename T>
ReverseIterator<T> ReverseIterator<T>::operator++(){
    if(!wasExtraction) {
        if (this->Iter->prev != this->pomHeap) this->Iter = Iter->prev;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getPrevNodeForIteration();

    return *this;
}

template<typename T>
const ReverseIterator<T> ReverseIterator<T>::operator++(int){
    auto pom = *this;
    ++(*this);

    return pom;
}

template<typename T>
ReverseIterator<T> ReverseIterator<T>::operator--(){
    if(!wasExtraction){
        if (this->Iter->next != this->pomHeap) this->Iter = Iter->next;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getNextNodeForIteration();

    return *this;
}

template<typename T>
const ReverseIterator<T> ReverseIterator<T>::operator--(int){
    auto pom = *this;
    --(*this);

    return pom;
}

#endif //FIBONACCIHEAP_FIBONACCI_REVERSE_ITERATOR_HPP
