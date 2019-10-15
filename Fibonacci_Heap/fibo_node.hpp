#ifndef _FIBO_NODE_HPP_
#define _FIBO_NODE_HPP_


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

#endif //_FIBO_NODE_HPP_
