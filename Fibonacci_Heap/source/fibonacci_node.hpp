#ifndef FIBONACCIHEAP_FIBONACCI_NODE_HPP
#define FIBONACCIHEAP_FIBONACCI_NODE_HPP

#pragma once

#include <iostream>
#include <exception>
#include <utility>

namespace algo::ds::fibo::node_impl {

    template <typename T>
    class FiboNode {
    public:
        T            value;
        FiboNode<T>* prev;
        FiboNode<T>* next;
        FiboNode<T>* child;
        FiboNode<T>* parent;
        int          degree;
        bool         marked;
        bool         iterMarked = false;

    public:
        FiboNode()                      : value{ -1 }, prev{ nullptr }, next{ nullptr }, child{ nullptr }, parent{ nullptr }, degree{ 0 }, marked{ false } {};
        explicit FiboNode(T val)        : value{ val }, prev{ nullptr }, next{ nullptr }, child{ nullptr }, parent{ nullptr }, degree{ 0 }, marked{ false } {};
        FiboNode(const FiboNode& s)     : value{ s.value }, prev{ s.prev }, next{ s.next }, child{ s.child }, parent{ s.parent }, degree{ s.degree }, marked{ s.marked } {};
        FiboNode(FiboNode&& s) noexcept : value{ s.value }, prev{ s.prev }, next{ s.next }, child{ s.child }, parent{ s.parent }, degree{ s.degree }, marked{ s.marked } {};
        ~FiboNode() = default;

        bool         hasChildren() { return child; };
        bool         hasParent()   { return parent; };
        FiboNode<T>* getNextNodeForIteration();
        FiboNode<T>* getPrevNodeForIteration();
        void         printNode();

        FiboNode<T>& operator= (const T& input)               { value = input; return *this; };
        FiboNode<T>& operator= (const FiboNode<T>& input);
        FiboNode<T>& operator= (FiboNode<T>&& input) noexcept;
        bool         operator==(const T& input)         const { return value == input; };
        bool         operator!=(const T& input)         const { return value != input; };
        bool         operator> (const T& input)         const { return value > input; };
        bool         operator< (const T& input)         const { return value < input; };
        bool         operator>=(const T& input)         const { return value >= input; };
        bool         operator<=(const T& input)         const { return value <= input; };
        bool         operator==(const FiboNode& source) const { return ((value == source.value) && (parent == source.parent)); };
        bool         operator!=(const FiboNode& source) const { return ((value != source.value) || (parent != source.parent)); };
        bool         operator> (const FiboNode& source) const { return value > source.value; };
        bool         operator< (const FiboNode& source) const { return value < source.value; };
        bool         operator>=(const FiboNode& source) const { return value >= source.value; };
        bool         operator<=(const FiboNode& source) const { return value <= source.value; };

        friend std::ostream& operator<<(std::ostream& ofs, const FiboNode<T>* pt) {
            ofs << "Value: " << pt->value << " ,degree: " << pt->degree << (pt->marked ? " ,marked" : " ,not marked") << "\n";

            if (pt->parent) ofs << "Parent value: " << pt->parent->value << " ,degree: " << pt->parent->degree << (pt->parent->marked ? " ,marked" : " ,not marked") << "\n";
            else ofs << "No parent (one of the roots)" << "\n";

            if (pt->next) ofs << "Next FiboNode value: " << pt->next->value << " ,degree: " << pt->next->degree << (pt->next->marked ? " ,marked" : " ,not marked") << "\n";
            else ofs << "No next FiboNode" << "\n";

            if (pt->prev) ofs << "Previous FiboNode value: " << pt->prev->value << " ,degree: " << pt->prev->degree << (pt->prev->marked ? " ,marked" : " ,not marked") << "\n\n";
            else ofs << "No previous FiboNode" << "\n\n";

            return ofs;
        };

        friend std::ostream& operator<<(std::ostream& ofs, const FiboNode<T>& pt) {
            ofs << "Value: " << pt.value << " ,degree: " << pt.degree << (pt.marked ? " ,marked" : " ,not marked") << "\n";

            if (pt.parent) ofs << "Parent value: " << pt.parent->value << " ,degree: " << pt.parent->degree << (pt.parent->marked ? " ,marked" : " ,not marked") << "\n";
            else ofs << "No parent (one of the roots)" << "\n";

            if (pt.next) ofs << "Next FiboNode value: " << pt.next->value << " ,degree: " << pt.next->degree << (pt.next->marked ? " ,marked" : " ,not marked") << "\n";
            else ofs << "No next FiboNode" << "\n";

            if (pt.prev) ofs << "Previous FiboNode value: " << pt.prev->value << " ,degree: " << pt.prev->degree << (pt.prev->marked ? " ,marked" : " ,not marked") << "\n\n";
            else ofs << "No previous FiboNode" << "\n\n";

            return ofs;
        };
    };

    template<typename T>
    FiboNode<T>& FiboNode<T>::operator=(const FiboNode<T>& input) {
        if (this != &input) {
            auto* newPrev = FiboNode<T>();
            auto* newChild = FiboNode<T>();
            auto* newNext = FiboNode<T>();
            auto* newParent = FiboNode<T>();

            try {
                newPrev = new FiboNode<T>(*input.prev);
                newChild = FiboNode<T>(*input.child);
                newNext = FiboNode<T>(*input.next);
                newParent = FiboNode<T>(*input.parent);
            }
            catch (...) {
                delete newPrev;
                delete newChild;
                delete newNext;
                delete newParent;

                throw std::bad_alloc();
            }

            value = input.value;
            degree = input.degree;
            marked = input.marked;
            iterMarked = input.iterMarked;
            std::swap(prev, newPrev);
            std::swap(child, newChild);
            std::swap(next, newNext);
            std::swap(parent, newParent);

            delete newPrev;
            delete newChild;
            delete newNext;
            delete newParent;
        }

        return *this;
    }

    template<typename T>
    FiboNode<T>& FiboNode<T>::operator=(FiboNode<T>&& input) noexcept {
        auto* newPrev = FiboNode<T>();
        auto* newChild = FiboNode<T>();
        auto* newNext = FiboNode<T>();
        auto* newParent = FiboNode<T>();

        try {
            newPrev = new FiboNode<T>(*input.prev);
            newChild = FiboNode<T>(*input.child);
            newNext = FiboNode<T>(*input.next);
            newParent = FiboNode<T>(*input.parent);
        }
        catch (...) {
            delete newPrev;
            delete newChild;
            delete newNext;
            delete newParent;

            throw std::bad_alloc();
        }

        value = input.value;
        degree = input.degree;
        marked = input.marked;
        iterMarked = input.iterMarked;
        std::swap(prev, newPrev);
        std::swap(child, newChild);
        std::swap(next, newNext);
        std::swap(parent, newParent);

        delete newPrev;
        delete newChild;
        delete newNext;
        delete newParent;

        return *this;
    }

    template<typename T>
    inline FiboNode<T>* FiboNode<T>::getNextNodeForIteration() {
        if (this != nullptr) {
            if (hasChildren() && !child->iterMarked) {
                child->iterMarked = true;

                return child;
            }
            else if (!prev->iterMarked) {
                prev->iterMarked = true;

                return prev;
            }
            else if (!next->iterMarked) {
                next->iterMarked = true;

                return next;
            }

            auto* bfs_ = this;

            do {
                bfs_ = bfs_->parent;
            } while (bfs_ != nullptr && bfs_->hasParent() && !bfs_->parent->iterMarked);

            if (bfs_ != nullptr && !bfs_->prev->iterMarked) {
                bfs_->prev->iterMarked = true;

                return bfs_->prev;
            }
            else if (bfs_ != nullptr && !bfs_->next->iterMarked) {
                bfs_->next->iterMarked = true;

                return bfs_->next;
            }
            else return nullptr;
        }

        return nullptr;
    }

    template<typename T>
    inline FiboNode<T>* FiboNode<T>::getPrevNodeForIteration() {
        if (this != nullptr) {
            if (hasParent() && !parent->iterMarked) {
                parent->iterMarked = true;

                return parent;
            }
            else if (!prev->iterMarked) {
                prev->iterMarked = true;

                return prev;
            }
            else if (!next->iterMarked) {
                next->iterMarked = true;

                return next;
            }

            auto* bfs_ = this;

            do {
                bfs_ = bfs_->child;
            } while (bfs_ != nullptr && bfs_->hasChildren() && !bfs_->child->iterMarked);

            if (bfs_ != nullptr && !bfs_->prev->iterMarked) {
                bfs_->prev->iterMarked = true;

                return bfs_->prev;
            }
            else if (bfs_ != nullptr && !bfs_->next->iterMarked) {
                bfs_->next->iterMarked = true;

                return bfs_->next;
            }
            else return nullptr;
        }

        return nullptr;
    }

    template<typename T>
    void FiboNode<T>::printNode() {
        std::cout << "Value: " << value << " ,degree: " << degree << (marked ? " ,marked" : " ,not marked") << std::endl;

        if (parent) std::cout << "Parent value: " << parent->value << " ,degree: " << parent->degree << (parent->marked ? " ,marked" : " ,not marked") << std::endl;
        else std::cout << "No parent (one of the roots)" << std::endl;

        if (next) std::cout << "Next FiboNode value: " << next->value << " ,degree: " << next->degree << (next->marked ? " ,marked" : " ,not marked") << std::endl;
        else std::cout << "No next FiboNode" << std::endl;

        if (prev) std::cout << "Previous FiboNode value: " << prev->value << " ,degree: " << prev->degree << (prev->marked ? " ,marked" : " ,not marked") << std::endl;
        else std::cout << "No previous FiboNode" << std::endl;

        if (child)  std::cout << "Child value: " << child->value << " ,degree: " << child->degree << (child->marked ? " ,marked" : " ,not marked") << std::endl;
        else std::cout << "No child FiboNode" << std::endl;

        std::cout << std::endl;
    }

}

#endif
