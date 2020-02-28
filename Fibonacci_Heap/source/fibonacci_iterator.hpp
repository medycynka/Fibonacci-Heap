#ifndef FIBONACCIHEAP_FIBONACCI_ITERATOR_HPP
#define FIBONACCIHEAP_FIBONACCI_ITERATOR_HPP

#pragma once

#include "fibonacci_node.hpp"


template <typename T>
class Iterator{
private:
    FiboNode<T> * Iter;
    FiboNode<T> * pomHeap;
    bool          wasExtraction;

public:
    typedef Iterator                  self_type;
    typedef T                         value_type;
    typedef T&                        reference;
    typedef T*                        pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int                       difference_type;

    Iterator()                                        : Iter(nullptr), pomHeap(nullptr), wasExtraction(false){};
    Iterator(const Iterator &s)                       : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
    Iterator(Iterator &&s) noexcept                   : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
    explicit Iterator(FiboNode<T> *s)                 : Iter(s), pomHeap(nullptr), wasExtraction(false){};
    explicit Iterator(bool &s)                        : Iter(nullptr), pomHeap(nullptr), wasExtraction(s){}
    Iterator(FiboNode<T> *s, FiboNode<T> *h)          : Iter(s), pomHeap(h), wasExtraction(false){};
    Iterator(FiboNode<T> *s, FiboNode<T> *h, bool &w) : Iter(s), pomHeap(h), wasExtraction(w){};

    Iterator       operator++                   ();
    const Iterator operator++                   (int);
    Iterator       operator--                   ();
    const Iterator operator--                   (int);
    Iterator &     operator=                    (const Iterator &source)       { if(this != &source){ Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; } return (*this); };
    Iterator &     operator=                    (Iterator &&source)   noexcept { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
    bool           operator==                   (const Iterator& source) const { return (Iter == source.Iter); };
    bool           operator!=                   (const Iterator& source) const { return (Iter != source.Iter); };
    explicit       operator FiboNode<T> &       ()                             { return (*Iter); };
    explicit       operator const FiboNode<T> & ()                       const { return (*Iter); };
    T &            operator*                    ()                       const { return (Iter->value); };
    FiboNode<T> *  operator->                   ()                       const { return Iter; };
    explicit       operator bool                ()                       const { return (Iter != nullptr); };
};

template<typename T>
Iterator<T> Iterator<T>::operator++(){
    if(!wasExtraction){
        if(this->Iter->next != this->pomHeap) this->Iter = this->Iter->next;
        else this->Iter = nullptr;
    }
    else{
        this->Iter = this->Iter->getNextNodeForIteration();
    }

    return *this;
}

template<typename T>
const Iterator<T> Iterator<T>::operator++(int){
    auto pom = *this;
    ++(*this);

    return pom;
}

template<typename T>
Iterator<T> Iterator<T>::operator--(){
    if(!wasExtraction) {
        if(this->Iter->prev != this->pomHeap) this->Iter = Iter->prev;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getPrevNodeForIteration();

    return *this;
}

template<typename T>
const Iterator<T> Iterator<T>::operator--(int){
    auto pom = *this;
    --(*this);

    return pom;
}

#endif //FIBONACCIHEAP_FIBONACCI_ITERATOR_HPP
