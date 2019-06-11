#ifndef _FIBONACCI_HEAP_HPP_
#define _FIBONACCI_HEAP_HPP_

#pragma once

template <typename T>
class node{
    public:
        T        value;
        node<T>* prev;
        node<T>* next;
        node<T>* child;
        node<T>* parent;
        int      degree;
        bool     marked;
        bool     iterMarked = false;

    public:
        node()                  : value(-1), prev(nullptr), next(nullptr), child(nullptr), parent(nullptr), degree(0), marked(false){};
        explicit node(T val)    : value(val), prev(nullptr), next(nullptr), child(nullptr), parent(nullptr), degree(0), marked(false){};
        node(const node &s)     : value(s.getValue()), prev(s.prev), next(s.next), child(s.child), parent(s.parent), degree(s.degree), marked(s.marked){};
        node(node &&s) noexcept : value(s.getValue()), prev(s.prev), next(s.next), child(s.child), parent(s.parent), degree(s.degree), marked(s.marked){};
        ~node() = default;

        inline bool hasChildren() { return child; };
        inline bool hasParent()   { return parent; };
        inline node<T> * getNextNodeForIteration();
        inline node<T> * getPrevNodeForIteration();
        inline void printNode();

        node& operator= (const T &input)          { value = input; return *this; };
        node& operator= (const node<T> &input);
        node& operator= (node<T> &&input) noexcept;
        bool  operator==(const T &input)    const { return value == input; };
        bool  operator!=(const T &input)    const { return value != input; };
        bool  operator> (const T &input)    const { return value > input; };
        bool  operator< (const T &input)    const { return value < input; };
        bool  operator>=(const T &input)    const { return value >= input; };
        bool  operator<=(const T &input)    const { return value <= input; };
        bool  operator==(const node &source) const { return ( (value == source.value) && (parent == source.parent) ); };
        bool  operator!=(const node &source) const { return ( (value != source.value) || (parent != source.parent) ); };
        bool  operator> (const node &source) const { return value > source.value; };
        bool  operator< (const node &source) const { return value < source.value; };
        bool  operator>=(const node &source) const { return value >= source.value; };
        bool  operator<=(const node &source) const { return value <= source.value; };

        friend std::ostream& operator<<(std::ostream& ofs, const node<T>* pt){
            ofs << "Value: " << pt->value << " ,degree: " << pt->degree << (pt->marked ? " ,marked" : " ,not marked") << "\n";

            if(pt->parent) ofs << "Parent value: " << pt->parent->value << " ,degree: " << pt->parent->degree << (pt->parent->marked ? " ,marked" : " ,not marked") << "\n";
            else ofs << "No parent (one of the roots)" << "\n";

            if(pt->next) ofs << "Next node value: " << pt->next->value << " ,degree: " << pt->next->degree << (pt->next->marked ? " ,marked" : " ,not marked") << "\n";
            else ofs << "No next node" << "\n";

            if(pt->prev) ofs << "Previous node value: " << pt->prev->value << " ,degree: " << pt->prev->degree << (pt->prev->marked ? " ,marked" : " ,not marked") << "\n\n";
            else ofs << "No previous node" << "\n\n";

            return ofs;
        };
};

template<typename T>
node<T> &node<T>::operator=(const node<T> &input){
    value = input.value;
    prev = input.prev;
    next = input.next;
    child = input.child;
    parent = input.parent;
    degree = input.degree;
    marked = input.marked;
    iterMarked = input.iterMarked;

    return *this;
}

template<typename T>
node<T> &node<T>::operator=(node<T> &&input) noexcept{
    value = input.value;
    prev = input.prev;
    next = input.next;
    child = input.child;
    parent = input.parent;
    degree = input.degree;
    marked = input.marked;
    iterMarked = input.iterMarked;

    return *this;
}

template<typename T>
inline node<T> *node<T>::getNextNodeForIteration(){
    if(this != nullptr){
        if(hasChildren() && !child->iterMarked){
            child->iterMarked = true;

            return child;
        }
        else if(!prev->iterMarked){
            prev->iterMarked = true;

            return prev;
        }
        else if(!next->iterMarked){
            next->iterMarked = true;

            return next;
        }

        auto* bfs_ = this;

        do{
            bfs_ = bfs_->parent;
        }while(bfs_ != nullptr && bfs_->hasParent() && !bfs_->parent->iterMarked);

        if(bfs_ != nullptr && !bfs_->prev->iterMarked) {
            bfs_->prev->iterMarked = true;

            return bfs_->prev;
        }
        else if(bfs_ != nullptr && !bfs_->next->iterMarked){
            bfs_->next->iterMarked = true;

            return bfs_->next;
        }
        else return nullptr;
    }

    return nullptr;
}

template<typename T>
inline node<T> *node<T>::getPrevNodeForIteration(){
    if(this != nullptr){
        if(hasParent() && !parent->iterMarked){
            parent->iterMarked = true;

            return parent;
        }
        else if(!prev->iterMarked){
            prev->iterMarked = true;

            return prev;
        }
        else if(!next->iterMarked){
            next->iterMarked = true;

            return next;
        }

        auto* bfs_ = this;

        do{
            bfs_ = bfs_->child;
        }while(bfs_ != nullptr && bfs_->hasChildren() && !bfs_->child->iterMarked);

        if(bfs_ != nullptr && !bfs_->prev->iterMarked) {
            bfs_->prev->iterMarked = true;

            return bfs_->prev;
        }
        else if(bfs_ != nullptr && !bfs_->next->iterMarked){
            bfs_->next->iterMarked = true;

            return bfs_->next;
        }
        else return nullptr;
    }

    return nullptr;
}

template<typename T>
void node<T>::printNode(){
    std::cout << "Value: " << value << " ,degree: " << degree << (marked ? " ,marked" : " ,not marked") << std::endl;

    if(parent) std::cout << "Parent value: " << parent->value << " ,degree: " << parent->degree << (parent->marked ? " ,marked" : " ,not marked") << std::endl;
    else std::cout << "No parent (one of the roots)" << std::endl;

    if(next) std::cout << "Next node value: " << next->value << " ,degree: " << next->degree << (next->marked ? " ,marked" : " ,not marked") << std::endl;
    else std::cout << "No next node" << std::endl;

    if(prev) std::cout << "Previous node value: " << prev->value << " ,degree: " << prev->degree << (prev->marked ? " ,marked" : " ,not marked") << std::endl;
    else std::cout << "No previous node" << std::endl;

    if(child)  std::cout << "Child value: " << child->value << " ,degree: " << child->degree << (child->marked ? " ,marked" : " ,not marked") << std::endl;
    else std::cout << "No child node" << std::endl;

    std::cout << std::endl;
}

template <typename T>
class FibonacciHeap{
    public:
        /**
         * TODO : make ReverseIterator and ConstReverseIterator work also after minimum extraction (make getPrevNodeForIteration() works corectly)
        */
        class Iterator{
            private:
                node<T> * Iter;
                node<T> * pomHeap;
                bool      wasExtraction;

            public:
                friend class FibonacciHeap;
                typedef Iterator                  self_type;
                typedef T                         value_type;
                typedef T&                        reference;
                typedef T*                        pointer;
                typedef std::forward_iterator_tag iterator_category;
                typedef int                       difference_type;

                Iterator()                                : Iter(nullptr), pomHeap(nullptr), wasExtraction(false){};
                Iterator(const Iterator &s)               : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
                Iterator(Iterator &&s) noexcept           : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
                explicit Iterator(node<T> *s)             : Iter(s), pomHeap(nullptr), wasExtraction(false){};
                explicit Iterator(bool &s)                : Iter(nullptr), pomHeap(nullptr), wasExtraction(s){}
                Iterator(node<T> *s, node<T> *h)          : Iter(s), pomHeap(h), wasExtraction(false){};
                Iterator(node<T> *s, node<T> *h, bool &w) : Iter(s), pomHeap(h), wasExtraction(w){};

                Iterator       operator++         ();
                const Iterator operator++         (int);
                Iterator       operator--         ();
                const Iterator operator--         (int);
                Iterator &     operator=          (const Iterator &source)       { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
                Iterator &     operator=          (Iterator &&source)   noexcept { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
                bool           operator==         (const Iterator& source) const { return (Iter == source.Iter); };
                bool           operator!=         (const Iterator& source) const { return (Iter != source.Iter); };
                explicit operator node<T> &       ()                             { return (*Iter); };
                explicit operator const node<T> & ()                       const { return (*Iter); };
                T &        operator*              ()                       const { return (Iter->value); };
                node<T> *  operator->             ()                       const { return Iter; };
                explicit operator bool            ()                       const { return (Iter != nullptr); };
        };

        class ConstIterator{
            private:
                node<T> * Iter;
                node<T> * pomHeap;
                bool      wasExtraction;

            public:
                friend class FibonacciHeap;
                typedef ConstIterator             self_type;
                typedef T                         value_type;
                typedef T&                        reference;
                typedef T*                        pointer;
                typedef std::forward_iterator_tag iterator_category;
                typedef int                       difference_type;

                ConstIterator()                                : Iter(nullptr), pomHeap(nullptr), wasExtraction(false){};
                ConstIterator(const ConstIterator &s)          : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
                ConstIterator(ConstIterator &&s) noexcept      : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
                explicit ConstIterator(node<T> *s)             : Iter(s), pomHeap(nullptr), wasExtraction(false){};
                explicit ConstIterator(bool &s)                : Iter(nullptr), pomHeap(nullptr), wasExtraction(s){}
                ConstIterator(node<T> *s, node<T> *h)          : Iter(s), pomHeap(h), wasExtraction(false){};
                ConstIterator(node<T> *s, node<T> *h, bool &w) : Iter(s), pomHeap(h), wasExtraction(w){};

                ConstIterator const operator++    ();
                ConstIterator const operator++    (int);
                ConstIterator const operator--    ();
                ConstIterator const operator--    (int);
                ConstIterator &     operator=     (const ConstIterator &source)       { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
                ConstIterator &     operator=     (ConstIterator &&source)   noexcept { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
                bool                operator==    (const ConstIterator& source) const { return (Iter == source.Iter); };
                bool                operator!=    (const ConstIterator& source) const { return (Iter != source.Iter); };
                explicit operator node<T> &       ()                                  { return (*Iter); };
                explicit operator const node<T> & ()                            const { return (*Iter); };
                T const &           operator*     ()                            const { return (Iter->value); };
                node<T> const *     operator->    ()                            const { return Iter; };
                explicit operator bool            ()                            const { return (Iter != nullptr); };
        };

        class ReverseIterator{
            private:
                node<T> * Iter;
                node<T> * pomHeap;
                bool      wasExtraction;

            public:
                friend class FibonacciHeap;
                typedef ReverseIterator           self_type;
                typedef T                         value_type;
                typedef T&                        reference;
                typedef T*                        pointer;
                typedef std::forward_iterator_tag iterator_category;
                typedef int                       difference_type;

                ReverseIterator()                                : Iter(nullptr), pomHeap(nullptr), wasExtraction(false){};
                ReverseIterator(const ReverseIterator &s)        : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
                ReverseIterator(ReverseIterator &&s) noexcept    : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
                explicit ReverseIterator(node<T> *s)             : Iter(s), pomHeap(nullptr), wasExtraction(false){};
                explicit ReverseIterator(bool &s)                : Iter(nullptr), pomHeap(nullptr), wasExtraction(s){}
                ReverseIterator(node<T> *s, node<T> *h)          : Iter(s), pomHeap(h), wasExtraction(false){};
                ReverseIterator(node<T> *s, node<T> *h, bool &w) : Iter(s), pomHeap(h), wasExtraction(w){};

                ReverseIterator       operator++  ();
                const ReverseIterator operator++  (int);
                ReverseIterator       operator--  ();
                const ReverseIterator operator--  (int);
                ReverseIterator &     operator=   (const ReverseIterator &source)       { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
                ReverseIterator &     operator=   (ReverseIterator &&source)   noexcept { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
                bool                  operator==  (const ReverseIterator& source) const { return (Iter == source.Iter); };
                bool                  operator!=  (const ReverseIterator& source) const { return (Iter != source.Iter); };
                explicit operator node<T> &       ()                                    { return (*Iter); };
                explicit operator const node<T> & ()                              const { return (*Iter); };
                T &                   operator*   ()                              const { return (Iter->value); };
                node<T> *             operator->  ()                              const { return Iter; };
                explicit operator bool            ()                              const { return (Iter != nullptr); };
        };

        class ConstReverseIterator{
            private:
                node<T> * Iter;
                node<T> * pomHeap;
                bool      wasExtraction;

            public:
                friend class FibonacciHeap;
                typedef ConstReverseIterator      self_type;
                typedef T                         value_type;
                typedef T&                        reference;
                typedef T*                        pointer;
                typedef std::forward_iterator_tag iterator_category;
                typedef int                       difference_type;

                ConstReverseIterator()                                  : Iter(nullptr), pomHeap(nullptr), wasExtraction(false){};
                ConstReverseIterator(const ConstReverseIterator &s)     : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
                ConstReverseIterator(ConstReverseIterator &&s) noexcept : Iter(s.Iter), pomHeap(s.pomHeap), wasExtraction(s.wasExtraction){};
                explicit ConstReverseIterator(node<T> *s)               : Iter(s), pomHeap(nullptr), wasExtraction(false){};
                explicit ConstReverseIterator(bool &s)                  : Iter(nullptr), pomHeap(nullptr), wasExtraction(s){}
                ConstReverseIterator(node<T> *s, node<T> *h)            : Iter(s), pomHeap(h), wasExtraction(false){};
                ConstReverseIterator(node<T> *s, node<T> *h, bool &w)   : Iter(s), pomHeap(h), wasExtraction(w){};

                ConstReverseIterator const operator++();
                ConstReverseIterator const operator++(int);
                ConstReverseIterator const operator--();
                ConstReverseIterator const operator--(int);
                ConstReverseIterator &     operator= (const ConstReverseIterator &source)       { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
                ConstReverseIterator &     operator= (ConstReverseIterator &&source)   noexcept { Iter = source.Iter; pomHeap = source.pomHeap; wasExtraction = source.wasExtraction; return (*this); };
                bool                       operator==(const ConstReverseIterator& source) const { return (Iter == source.Iter); };
                bool                       operator!=(const ConstReverseIterator& source) const { return (Iter != source.Iter); };
                explicit operator node<T> &          ()                                         { return (*Iter); };
                explicit operator const node<T> &    ()                                   const { return (*Iter); };
                T const &                  operator* ()                                   const { return (Iter->value); };
                node<T> const *            operator->()                                   const { return Iter; };
                explicit operator bool               ()                                   const { return (Iter != nullptr); };
        };

    protected:
        node<T>* heap;
        T        currMax = T();
        size_t   num_elems;
        bool     wasDeletion = false;

    public:
        FibonacciHeap()                           : heap(_empty()), num_elems(0){};
        explicit FibonacciHeap(node<T> &s)        : heap(s), num_elems(0){};
        FibonacciHeap(const FibonacciHeap &s)     : heap(s.heap), num_elems(s.num_elems){};
        FibonacciHeap(FibonacciHeap &&s) noexcept : heap(s.heap), num_elems(s.num_elems){};

        inline node<T>* insert(T);
        inline void     merge(FibonacciHeap&);
        inline T        removeMinimum();
        inline void     displayHeap();
        inline void     decreaseKey(node<T>* n, T value) { heap = _decreaseKey(heap, n, value); };
        inline node<T>* find(T value)                    { return _find(heap, value); };
        inline bool     isEmpty()                  const { return heap == nullptr; };
        inline T        getMinimum()                     { return heap->value; };
        inline node<T>* getRoot()                  const { return heap; };
        inline size_t   size()                     const { return num_elems; };
        inline node<T>* getCurrMax()               const { return find(currMax); };
        inline void     clear()                          { while(!isEmpty()){ removeMinimum(); } };

        FibonacciHeap<T>& operator= (const FibonacciHeap<T> &o)     { num_elems = o.num_elems; wasDeletion = o.wasDeletion; heap = o.heap; return *this; };
        FibonacciHeap<T>& operator= (FibonacciHeap<T> &&o) noexcept { num_elems = o.num_elems; wasDeletion = o.wasDeletion; heap = o.heap; return *this; };
        bool              operator==(const FibonacciHeap<T> &o)     { return (num_elems == o.num_elems && wasDeletion == o.wasDeletion && heap == o.heap); };
        bool              operator!=(const FibonacciHeap<T> &o)     { return !(*this == o); };
        FibonacciHeap<T>& operator+ (const FibonacciHeap<T> &o)     { merge(o); return *this; };

        inline Iterator             begin()   { return Iterator(heap, heap, wasDeletion); };
        inline Iterator             end()     { return Iterator(wasDeletion); };
        inline ConstIterator        cbegin()  { return ConstIterator(heap, heap, wasDeletion); };
        inline ConstIterator        cend()    { return ConstIterator(wasDeletion); };
        inline ReverseIterator      rbegin()  { return ReverseIterator(heap->prev, heap->prev, wasDeletion); };
        inline ReverseIterator      rend()    { return ReverseIterator(wasDeletion); };
        inline ConstReverseIterator crbegin() { return ConstReverseIterator(heap->prev, heap->prev, wasDeletion); };
        inline ConstReverseIterator crend()   { return ConstReverseIterator(wasDeletion); };

    private:
        inline node<T>* _empty(){ return nullptr; }
        inline node<T>* _singleton(T);
        inline node<T>* _merge(node<T>*, node<T>*);
        inline void     _addChild(node<T>*, node<T>*);
        inline void     _unMarkAndUnParentAll(node<T>*);
        inline node<T>* _removeMinimum(node<T>*);
        inline node<T>* _cut(node<T>*, node<T>*);
        inline node<T>* _decreaseKey(node<T>*, node<T>*, T);
        inline node<T>* _find(node<T>*, T);
        inline void     _displayHeap(node<T>*);
        inline void     _displayChildrens(node<T>*);
};

template<typename T>
typename FibonacciHeap<T>::Iterator FibonacciHeap<T>::Iterator::operator++(){
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
const typename FibonacciHeap<T>::Iterator FibonacciHeap<T>::Iterator::operator++(int){
    auto pom = *this;
    ++(*this);

    return pom;
}

template<typename T>
typename FibonacciHeap<T>::Iterator FibonacciHeap<T>::Iterator::operator--(){
    if(!wasExtraction) {
        if(this->Iter->prev != this->pomHeap) this->Iter = Iter->prev;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getPrevNodeForIteration();

    return *this;
}

template<typename T>
const typename FibonacciHeap<T>::Iterator FibonacciHeap<T>::Iterator::operator--(int){
    auto pom = *this;
    --(*this);

    return pom;
}

template<typename T>
typename FibonacciHeap<T>::ConstIterator const FibonacciHeap<T>::ConstIterator::operator++(){
    if(!wasExtraction){
        if(this->Iter->next != this->pomHeap) this->Iter = Iter->next;
        else this->Iter = nullptr;
    }
    else{
        this->Iter = this->Iter->getNextNodeForIteration();
    }

    return *this;
}

template<typename T>
typename FibonacciHeap<T>::ConstIterator const FibonacciHeap<T>::ConstIterator::operator++(int){
    auto pom = *this;
    ++(*this);

    return pom;
}

template<typename T>
typename FibonacciHeap<T>::ConstIterator const FibonacciHeap<T>::ConstIterator::operator--(){
    if(!wasExtraction) {
        if(this->Iter->prev != this->pomHeap) this->Iter = Iter->prev;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getPrevNodeForIteration();

    return *this;
}

template<typename T>
typename FibonacciHeap<T>::ConstIterator const FibonacciHeap<T>::ConstIterator::operator--(int){
    auto pom = *this;
    --(*this);

    return pom;
}

template<typename T>
typename FibonacciHeap<T>::ReverseIterator FibonacciHeap<T>::ReverseIterator::operator++(){
    if(!wasExtraction) {
        if (this->Iter->prev != this->pomHeap) this->Iter = Iter->prev;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getPrevNodeForIteration();

    return *this;
}

template<typename T>
const typename FibonacciHeap<T>::ReverseIterator FibonacciHeap<T>::ReverseIterator::operator++(int){
    auto pom = *this;
    ++(*this);

    return pom;
}

template<typename T>
typename FibonacciHeap<T>::ReverseIterator FibonacciHeap<T>::ReverseIterator::operator--(){
    if(!wasExtraction){
        if (this->Iter->next != this->pomHeap) this->Iter = Iter->next;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getNextNodeForIteration();

    return *this;
}

template<typename T>
const typename FibonacciHeap<T>::ReverseIterator FibonacciHeap<T>::ReverseIterator::operator--(int){
    auto pom = *this;
    --(*this);

    return pom;
}

template<typename T>
typename FibonacciHeap<T>::ConstReverseIterator const FibonacciHeap<T>::ConstReverseIterator::operator++(){
    if(!wasExtraction) {
        if (this->Iter->prev != this->pomHeap) this->Iter = Iter->prev;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getPrevNodeForIteration();

    return *this;
}

template<typename T>
typename FibonacciHeap<T>::ConstReverseIterator const FibonacciHeap<T>::ConstReverseIterator::operator++(int){
    auto pom = *this;
    ++(*this);

    return pom;
}

template<typename T>
typename FibonacciHeap<T>::ConstReverseIterator const FibonacciHeap<T>::ConstReverseIterator::operator--(){
    if(!wasExtraction){
        if (this->Iter->next != this->pomHeap) this->Iter = Iter->next;
        else this->Iter = nullptr;
    }
    else this->Iter = this->Iter->getNextNodeForIteration();

    return *this;
}

template<typename T>
typename FibonacciHeap<T>::ConstReverseIterator const FibonacciHeap<T>::ConstReverseIterator::operator--(int){
    auto pom = *this;
    --(*this);

    return pom;
}

template<class T>
node<T> *FibonacciHeap<T>::insert(T value){
    node<T>* ret = _singleton(value);
    if(ret){
        num_elems++;

        if(ret->value > currMax) currMax = ret->value;
    }

    heap = _merge(heap, ret);

    return ret;
}

template<class T>
void FibonacciHeap<T>::merge(FibonacciHeap &other){
    heap = _merge(heap, other.heap);
    other.heap = _empty();
}

template<class T>
T FibonacciHeap<T>::removeMinimum(){
    auto* old = heap;
    heap = _removeMinimum(heap);
    auto ret = old->value;
    delete old;
    num_elems--;
    wasDeletion = true;

    return ret;
}

template<typename T>
void FibonacciHeap<T>::displayHeap(){
    if(isEmpty()) std::cout << "Heap is empty!" << std::endl;
    else _displayHeap(heap);
}

template<class T>
node<T> *FibonacciHeap<T>::_singleton(T value){
    auto n = new node<T>;
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
node<T> *FibonacciHeap<T>::_merge(node<T> *a, node<T> *b){
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
void FibonacciHeap<T>::_addChild(node<T> *parent, node<T> *child){
    child->prev = child;
    child->next = child;
    child->parent = parent;
    parent->degree++;
    parent->child = _merge(parent->child, child);
}

template<class T>
void FibonacciHeap<T>::_unMarkAndUnParentAll(node<T> *n){
    if(n == nullptr) return;

    auto* c = n;

    do{
        c->marked = false;
        c->parent = nullptr;
        c = c->next;
    }while(c != n);
}

template<class T>
node<T> *FibonacciHeap<T>::_removeMinimum(node<T> *n){
    _unMarkAndUnParentAll(n->child);

    if(n->next == n) n = n->child;
    else{
        n->next->prev = n->prev;
        n->prev->next = n->next;
        n = _merge(n->next, n->child);
    }

    if(n == nullptr) return n;

    node<T>* trees[64] = {nullptr};

    while(true){
        if(trees[n->degree]!=nullptr){
            auto* t = trees[n->degree];

            if(t == n) break;

            trees[n->degree] = nullptr;

            if(n->value < t->value){
                t->prev->next = t->next;
                t->next->prev = t->prev;
                _addChild(n, t);
            }
            else{
                t->prev->next = t->next;
                t->next->prev = t->prev;

                if(n->next == n){
                    t->next = t;
                    t->prev = t;
                    _addChild(t, n);
                    n = t;
                }
                else{
                    n->prev->next = t;
                    n->next->prev = t;
                    t->next = n->next;
                    t->prev = n->prev;
                    _addChild(t, n);
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
node<T> *FibonacciHeap<T>::_cut(node<T> *heap_, node<T> *n){
    if(n->next == n) n->parent->child = nullptr;
    else{
        n->next->prev = n->prev;
        n->prev->next = n->next;
        n->parent->child = n->next;
    }

    n->next = n->prev=n;
    n->marked = false;

    return _merge(heap_, n);
}

template<class T>
node<T> *FibonacciHeap<T>::_decreaseKey(node<T> *heap_, node<T> *n, T value){
    if(n->value < value) return heap_;

    n->value = value;

    if(n->parent){
        if(n->value < n->parent->value) {
            heap_ = _cut(heap_, n);
            auto* parent = n->parent;
            n->parent = nullptr;

            while(parent != nullptr && parent->marked) {
                heap_ = _cut(heap_, parent);
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
node<T> *FibonacciHeap<T>::_find(node<T> *heap_, T value){
    auto* n = heap_;

    if(n == nullptr) return nullptr;

    do{
        if(n->value == value) return n;
        auto* ret = _find(n->child, value);

        if(ret) return ret;

        n = n->next;
    }while(n != heap_);

    return nullptr;
}

template<typename T>
void FibonacciHeap<T>::_displayHeap(node<T> *in) {
    if(in){
        auto *c = in;

        std::cout << "Minimum -> " << heap->value << std::endl;
        do{
            _displayChildrens(c);
            c = c->next;
        } while(c != in);
    }
}

template<typename T>
void FibonacciHeap<T>::_displayChildrens(node<T> *n){
    if(n){
        std::cout << "value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> next: " << n->next->value << (n->next->marked ? " (marked)" : " (not marked)") << std::endl;
        std::cout << "value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> prev: " << n->prev->value << (n->prev->marked ? " (marked)" : " (not marked)") << std::endl;
        if(n->hasParent()) std::cout << "value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> parent: " << n->parent->value << (n->parent->marked ? " (marked)" : " (not marked)") << std::endl;
        else std::cout << "No parent" << std::endl;

        if(n->hasChildren()){
            auto* c = n->child;
            do {
                std::cout << "parent value: " << n->value << (n->marked ? " (marked)" : " (not marked)") << " -> child: " << n->child->value << (n->child->marked ? " (marked)" : " (not marked)") << std::endl << std::endl;
                _displayChildrens(c);
                c = c->next;
            } while(c != n->child);
        }
        else std::cout << "No child" << std::endl;
    }
}

#endif //FIBONACCI_HEAP__FIBONACCI_HEAP_HPP
