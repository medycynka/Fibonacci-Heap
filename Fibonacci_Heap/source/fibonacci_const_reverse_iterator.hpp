#ifndef FIBONACCIHEAP_FIBONACCI_CONST_REVERSE_ITERATOR_HPP
#define FIBONACCIHEAP_FIBONACCI_CONST_REVERSE_ITERATOR_HPP

#pragma once

#include "fibonacci_node.hpp"


template <typename T>
class ConstReverseIterator{
private:
    FiboNode<T> * Iter;
    FiboNode<T> * pomHeap;
    bool          wasExtraction;

public:
    typedef ConstReverseIterator      self_type;
    typedef T                         value_type;
    typedef T&                        reference;
    typedef T*                        pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef int                       difference_type;

    ConstReverseIterator()                                          : Iter(nullptr), pomHeap(nullptr), wasExtraction(false){};
    ConstReverseIterator(const ConstReverseIterator &s)             : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
    ConstReverseIterator(ConstReverseIterator &&s) noexcept         : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
    explicit ConstReverseIterator(FiboNode<T> *s)                   : Iter(s), pomHeap(nullptr), wasExtraction(false){};
    explicit ConstReverseIterator(bool &s)                          : Iter(nullptr), pomHeap(nullptr), wasExtraction(s){}
    ConstReverseIterator(FiboNode<T> *s, FiboNode<T> *h)            : Iter(s), pomHeap(h), wasExtraction(false){};
    ConstReverseIterator(FiboNode<T> *s, FiboNode<T> *h, bool &w)   : Iter(s), pomHeap(h), wasExtraction(w){};

    ConstReverseIterator const operator++                   ();
    ConstReverseIterator const operator++                   (int);
    ConstReverseIterator const operator--                   ();
    ConstReverseIterator const operator--                   (int);
    ConstReverseIterator &     operator=                    (const ConstReverseIterator &source)       { if(this != &source){ Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; } return (*this); };
    ConstReverseIterator &     operator=                    (ConstReverseIterator &&source)   noexcept { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
    bool                       operator==                   (const ConstReverseIterator& source) const { return (Iter == source.Iter); };
    bool                       operator!=                   (const ConstReverseIterator& source) const { return (Iter != source.Iter); };
    explicit                   operator FiboNode<T> &       ()                                         { return (*Iter); };
    explicit                   operator const FiboNode<T> & ()                                   const { return (*Iter); };
    T const &                  operator*                    ()                                   const { return (Iter->value); };
    FiboNode<T> const *        operator->                   ()                                   const { return Iter; };
    explicit                   operator bool                ()                                   const { return (Iter != nullptr); };
};

template<typename T>
ConstReverseIterator<T> const ConstReverseIterator<T>::operator++(){
    if(!wasExtraction) {
        if (this->Iter->prev != this->pomHeap) this->Iter = Iter->prev;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getPrevNodeForIteration();

    return *this;
}

template<typename T>
ConstReverseIterator<T> const ConstReverseIterator<T>::operator++(int){
    auto pom = *this;
    ++(*this);

    return pom;
}

template<typename T>
ConstReverseIterator<T> const ConstReverseIterator<T>::operator--(){
    if(!wasExtraction){
        if (this->Iter->next != this->pomHeap) this->Iter = Iter->next;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getNextNodeForIteration();

    return *this;
}

template<typename T>
ConstReverseIterator<T> const ConstReverseIterator<T>::operator--(int){
    auto pom = *this;
    --(*this);

    return pom;
}

#endif //FIBONACCIHEAP_FIBONACCI_CONST_REVERSE_ITERATOR_HPP
