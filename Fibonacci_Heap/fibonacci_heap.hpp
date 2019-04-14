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

public:
    node()                  : value(-1), prev(NULL), next(NULL), child(NULL), parent(NULL), degree(0), marked(false){};
    explicit node(T val)    : value(val), prev(NULL), next(NULL), child(NULL), parent(NULL), degree(0), marked(false){};
    node(const node &s)     : value(s.getValue()), prev(s.prev), next(s.next), child(s.child), parent(s.parent), degree(s.degree), marked(s.marked){};
    node(node &&s) noexcept : value(s.getValue()), prev(s.prev), next(s.next), child(s.child), parent(s.parent), degree(s.degree), marked(s.marked){};
    ~node() = default;

    inline bool hasChildren() { return child; };
    inline bool hasParent()   { return parent; };
    inline void printNode();


    T &  operator= ( const T &input )          { value = input; };
    bool operator==( const T &input )    const { return value == input; };
    bool operator!=( const T &input )    const { return value != input; };
    bool operator> ( const T &input )    const { return value > input; };
    bool operator< ( const T &input )    const { return value < input; };
    bool operator>=( const T &input )    const { return value >= input; };
    bool operator<=( const T &input )    const { return value <= input; };
    bool operator==( const node &source) const { return ( (value == source.value) && (value == source.father) ); };
    bool operator!=( const node &source) const { return ( (value != source.value) || (value != source.father) ); };
    bool operator> ( const node &source) const { return value > source.value; };
    bool operator< ( const node &source) const { return value < source.value; };
    bool operator>=( const node &source) const { return value >= source.value; };
    bool operator<=( const node &source) const { return value <= source.value; };
};

template<typename T>
void node<T>::printNode(){
    std::cout << "Value: " << value << " ,degree: " << degree;
    std::cout << (marked ? " ,marked" : " ,not marked") << std::endl;

    if(parent){
        std::cout << "Parent value: " << parent->value << " ,degree: " << parent->degree;;
        std::cout << (parent->marked ? " ,marked" : " ,not marked") << std::endl;
    }
    else std::cout << "No parent (one of the roots)" << std::endl;

    if(next){
        std::cout << "Next node value: " << next->value << " ,degree: " << next->degree;;
        std::cout << (next->marked ? " ,marked" : " ,not marked") << std::endl;
    }
    else std::cout << "No next node" << std::endl;

    if(prev){
        std::cout << "Previous node value: " << prev->value << " ,degree: " << prev->degree;;
        std::cout << (prev->marked ? " ,marked" : " ,not marked") << std::endl;
    }
    else std::cout << "No previous node" << std::endl;

    if(child){
        std::cout << "Child value: " << child->value << " ,degree: " << child->degree;;
        std::cout << (child->marked ? " ,marked" : " ,not marked") << std::endl;
    }
    else std::cout << "No child node" << std::endl;

    std::cout << std::endl;
}

template <typename T>
class FibonacciHeap{
protected:
    node<T>* heap;
    size_t   num_elems;

public:
    FibonacciHeap()                           : heap(_empty()), num_elems(0){};
    explicit FibonacciHeap(node<T> &s)        : heap(s), num_elems(0){};
    FibonacciHeap(const FibonacciHeap &s)     : heap(s.heap), num_elems(s.num_elems){};
    FibonacciHeap(FibonacciHeap &&s) noexcept : heap(s.heap), num_elems(s.num_elems){};
    //virtual ~FibonacciHeap(){ if(heap) _deleteAll(heap); }

    inline node<T>* insert(T);
    inline void     merge(FibonacciHeap&);
    inline T        removeMinimum();
    inline void     displayHeap();
    inline void     decreaseKey(node<T>* n, T value) { heap = _decreaseKey(heap, n, value); };
    inline node<T>* find(T value)                    { return _find(heap,value); };
    inline bool     isEmpty() const                  { return heap == NULL; };
    inline T        getMinimum()                     { return heap->value; };
    inline node<T>* getRoot() const                  { return heap; };
    inline size_t   size() const                     { return num_elems; };

private:
    inline node<T>* _empty(){ return NULL; }
    inline node<T>* _singleton(T);
    inline node<T>* _merge(node<T>*, node<T>*);
    inline void     _deleteAll(node<T>*);
    inline void     _addChild(node<T>*, node<T>*);
    inline void     _unMarkAndUnParentAll(node<T>*);
    inline node<T>* _removeMinimum(node<T>*);
    inline node<T>* _cut(node<T>*, node<T>*);
    inline node<T>* _decreaseKey(node<T>*, node<T>*, T);
    inline node<T>* _find(node<T>*, T);
    inline void     _displayHeap(node<T>*);
    inline void     _displayChildrens(node<T>*);
};

template<class T>
node<T> *FibonacciHeap<T>::insert(T value){
    node<T>* ret = _singleton(value);
    if(ret) num_elems++;

    heap = _merge(heap, ret);

    return ret;
}

template<class T>
void FibonacciHeap<T>::merge(FibonacciHeap &other){
    heap = _merge(heap,other.heap);
    other.heap = _empty();
}

template<class T>
T FibonacciHeap<T>::removeMinimum(){
    node<T>* old = heap;
    heap = _removeMinimum(heap);
    T ret = old->value;
    delete old;
    num_elems--;

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
    n->child = NULL;
    n->parent = NULL;

    return n;
}

template<class T>
node<T> *FibonacciHeap<T>::_merge(node<T> *a, node<T> *b){
    if(a == NULL) return b;
    if(b == NULL) return a;
    if(a->value > b->value){
        node<T>* temp = a;
        a = b;
        b = temp;
    }

    node<T>* an = a->next;
    node<T>* bp = b->prev;
    a->next = b;
    b->prev = a;
    an->prev = bp;
    bp->next = an;

    return a;
}

template<class T>
void FibonacciHeap<T>::_deleteAll(node<T> *n){
    if(n != NULL) {
        node<T>* c = n;
        do{
            node<T>* d = c;
            c = c->next;
            _deleteAll(d->child);
            delete d;
        }while(c != n);
    }
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
    if(n == NULL) return;

    node<T>* c = n;

    do{
        c->marked = false;
        c->parent = NULL;
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

    if(n == NULL) return n;

    node<T>* trees[64] = {NULL};

    while(true){
        if(trees[n->degree]!=NULL){
            node<T>* t = trees[n->degree];

            if(t == n) break;

            trees[n->degree] = NULL;

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

    node<T>* min = n;
    node<T>* start = n;

    do{
        if(n->value < min->value) min=n;

        n = n->next;
    }while(n!=start);

    return min;
}

template<class T>
node<T> *FibonacciHeap<T>::_cut(node<T> *heap_, node<T> *n){
    if(n->next == n) n->parent->child = NULL;
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
            node<T>* parent = n->parent;
            n->parent = NULL;

            while(parent != NULL && parent->marked) {
                heap_ = _cut(heap_, parent);
                n = parent;
                parent = n->parent;
                n->parent = NULL;
            }

            if(parent != NULL && parent->parent != NULL) parent->marked = true;
        }
    }
    else if(n->value < heap_->value) heap_ = n;

    return heap_;
}

template<class T>
node<T> *FibonacciHeap<T>::_find(node<T> *heap_, T value){
    node<T>* n = heap_;

    if(n == NULL) return NULL;

    do{
        if(n->value == value) return n;
        node<T>* ret = _find(n->child, value);

        if(ret) return ret;

        n = n->next;
    }while(n != heap_);

    return NULL;
}

template<typename T>
void FibonacciHeap<T>::_displayHeap(node<T> *in) {
    if(in){
        node<T> *c = in;

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

        if(n->hasChildren()) {
            node<T>* c = n->child;
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
