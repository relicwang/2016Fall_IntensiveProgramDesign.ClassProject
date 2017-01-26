#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <utility>
#include <cmath>
#include <math.h>
#include <vector>


namespace ipd {

// The main `FibonacciHeap` class
    template<typename T>
    class FibonacciHeap {
    public:
        // Constructs a new, empty Fibonacci Heap.
        FibonacciHeap() noexcept;

        // Constructs a new Fibonacci Heap with only one element;
        FibonacciHeap(const T &);

        // Constructs a new Fibonacci Heap with the given elements;
        FibonacciHeap(std::initializer_list<T>);

        // Move constructor.
        FibonacciHeap(FibonacciHeap &&) noexcept;

        // Move assignment operator.
        FibonacciHeap &operator=(FibonacciHeap &&) noexcept;

        // Returns true if the deque is empty.
        bool empty() const noexcept;

        // Returns the number of elements in the deque.
        size_t size() const noexcept;

        // Inserts a new element in the Fibonacci Heap
        void insert(const T &);

        void insert(T &&);

        // Returns a reference to the minimum element of the Fibonacci Heap . If the Fibonacci Heap  is
        // empty then the behavior is undefined.
        const T &minimum() const;

        T &minimum();

        // Constructs a new element in the Fibonacci Heap
        template<typename... Args>
        void emplace(Args &&...);

        // Deletes the element from Fibonacci Heap  whose key is minimum,
        // returning a pointer to the element. Undefined if the deque is empty.
        const T &extract_min();

        //Delete the minimum element.
        void remove_min();

        //Union two Fibonacci Heap without copying.
        void merge(FibonacciHeap &) noexcept;

        // Removes all elements from the Fibonacci Heap .
        void clear() noexcept;

        // Exchanges the contents of two Fibonacci Heap without copying.
        void swap(FibonacciHeap &) noexcept;

    private:
        // The linked list is made out of nodes, each of which contains a data
        // element and pointers to next and previous nodes.
        struct node_ {
            T data;
            node_ *parent;
            node_ *child;
            node_ *left;
            node_ *right;
            int rank;

            // Constructs a new node, forwarding the arguments to construct the
            // data element. The prev and next pointers are initialized to nullptr.
            template<typename... Args>
            explicit node_(Args &&... args)
            noexcept(noexcept(T(std::forward<Args>(args)...)))
                    : data(std::forward<Args>(args)...),
                      parent(nullptr),
                      child(nullptr),
                      left(nullptr),
                      right(nullptr),
                      rank(0)
                      {}
        };

        // Private member variables:
        node_ *min_ = nullptr;

        size_t size_ = 0;

        // Attaches a new node to the FibonacciHeap.
        void insert_(node_ *) noexcept;

        void consolidate_();

        void link_(node_ *, node_ *);
    };

    template<typename T>
    FibonacciHeap<T>::FibonacciHeap() noexcept {}

    template<typename T>
    FibonacciHeap<T>::FibonacciHeap(const T &value) {
        node_ *temp = new node_(value);
        temp->rank = 0;

        temp->parent = nullptr;
        temp->child = nullptr;
        temp->left = temp;
        temp->right = temp;

        min_ = temp;

        size_++;
    }


    template<typename T>
    template<typename... Args>
    void FibonacciHeap<T>::emplace(Args &&... args) {
        insert_(new node_(std::forward(args)...));
    }

    template<typename T>
    void FibonacciHeap<T>::insert_(node_ *new_node) noexcept {
        if (min_ == nullptr) {
            min_ = &*new_node;
        } else {
            //Ref:http://stackoverflow.com/questions/25606848/concatenate-2-circular-double-linked-list-without-using-extra-pointer
            node_ *t1 = min_->left;
            node_ *t2 = new_node->left;

            min_->left = new_node;
            new_node->left = t1;
            t1->right = new_node;
            new_node->right = min_;

            if (new_node->data < min_->data) {
                min_ = new_node;
            }
        }
        size_ = size_ + 1;
    }

    template<typename T>
    FibonacciHeap<T>::FibonacciHeap(FibonacciHeap &&other) noexcept
            : min_(other.min_), size_(other.size_) {
        other.min_ = nullptr;
        other.size_ = 0;
    }

    template<typename T>
    FibonacciHeap<T> &FibonacciHeap<T>::operator=(FibonacciHeap &&other) noexcept {
        clear();

        min_ = other.min_;
        size_ = other.size_;

        other.min_ = nullptr;
        other.size_ = 0;
    }

    template<typename T>
    void FibonacciHeap<T>::clear() noexcept {
        while (!empty()) remove_min();
    }

    template<typename T>
    void FibonacciHeap<T>::swap(FibonacciHeap &other) noexcept {
        std::swap(min_, other.min_);
        std::swap(size_, other.size_);
    }

    template<typename T>
    const T &FibonacciHeap<T>::extract_min() {
        node_ *curt_min = min_;
        node_ *next_sib;

        if (curt_min != nullptr) {
            node_ *child = curt_min->child;

            std::vector<node_ *> children;

            if (child != nullptr) {
                next_sib = child;
                for (int i = 0; i < curt_min->rank; ++i) {
                    children.push_back(next_sib);
                    next_sib = next_sib->right;
                }

                for (int i = 0; i < curt_min->rank; ++i) {
                    next_sib = children[i];

                    node_ *t1 =  min_->left;
                    node_ *t2 = next_sib->left;

                    min_->left =  next_sib;
                    next_sib->left = t1;
                    t1->right =  next_sib;
                    next_sib->right =  min_;

                    next_sib->parent = nullptr;
                }
            }

            //Delete min
            curt_min->left->right = curt_min->right;
            curt_min->right->left = curt_min->left;

            if (curt_min == curt_min->right) {
                min_ = nullptr;
            } else {
                min_ = curt_min->right;
                consolidate_();
            }
            --size_;
        }

        return curt_min->data;
    }

    template<typename T>
    void FibonacciHeap<T>::remove_min() {
        extract_min();
    }

    template<typename T>
    void FibonacciHeap<T>::consolidate_() {

        int ranking = log2(size_)  + 1;

        node_ *curt_node;
        node_ *next_node;
        node_ *pair_node;
        int curt_degree;

        std::vector<node_ *> node_rank_list(ranking);
        std::vector<node_ *> node_loop_list;

        //Clear the node ranking list
        for (int i = 0; i < ranking; ++i) {
            node_rank_list[i] = nullptr;
        }

        curt_node = min_;
        next_node = curt_node->right;
        node_loop_list.push_back(curt_node);

        while (next_node != curt_node){
            node_loop_list.push_back(next_node);
            next_node = next_node->right;
        }

        for (int i = 0; i < node_loop_list.size(); i++) {
            curt_node = node_loop_list[i];
            curt_degree = curt_node->rank;

            while (node_rank_list[curt_degree] != nullptr) {
                pair_node = node_rank_list[curt_degree];

                if (curt_node->data > pair_node->data) {
                    std::swap(curt_node,pair_node);
                }
                link_(pair_node, curt_node);

                node_rank_list[curt_degree] = nullptr;
                ++curt_degree;
            }
            node_rank_list[curt_degree] = curt_node;
        }

        min_ = nullptr;

        for (int i = 0; i < ranking; ++i) {
            if (node_rank_list[i] != nullptr) {
                if (min_ == nullptr) {
                    min_ = node_rank_list[i]->left = node_rank_list[i]->right = node_rank_list[i];
                } else {
                    node_ *t1 =  min_->left;
                    node_ *t2 =  node_rank_list[i]->left;

                    min_->left =  node_rank_list[i];
                    node_rank_list[i]->left = t1;
                    t1->right =  node_rank_list[i];
                    node_rank_list[i]->right =  min_;


                    if (node_rank_list[i]->data < min_->data) {
                        min_ = node_rank_list[i];
                    }
                }
            }
        }
    }

    template<typename T>
    void FibonacciHeap<T>::link_(node_ *n1, node_ *n2) {

        n1->left->right = n1->right;
        n1->right->left = n1->left;

        if (n2->child == nullptr) {
            n2->child = n1;
            n1->right = n1;
            n1->left =n1;
        } else {

            node_ *t1 =  n2->child->left;
            node_ *t2 = n1->left;

            n2->child->left = n1;
            n1->left = t1;
            t1->right = n1;
            n1->right =  n2->child;
        }
        n1->parent = n2;
        n2->rank++;
    }

    template<typename T>
    FibonacciHeap<T>::FibonacciHeap(std::initializer_list<T> args) {
        for (const auto &arg : args)
            insert(arg);
    }

    template<typename T>
    bool FibonacciHeap<T>::empty() const noexcept {
        return size_ == 0;
    }

    template<typename T>
    size_t FibonacciHeap<T>::size() const noexcept {
        return size_;
    }

    template<typename T>
    void FibonacciHeap<T>::insert(const T &value) {
        FibonacciHeap<T> fh(value);
        merge(fh);
    }

    template<typename T>
    void FibonacciHeap<T>::insert(T &&value) {
        FibonacciHeap<T> fh(std::move(value));
        merge(fh);
    }

    template<typename T>
    const T &FibonacciHeap<T>::minimum() const {
        return min_->data;
    }

    template<typename T>
    T &FibonacciHeap<T>::minimum() {
        return min_->data;
    }

    template<typename T>
    void FibonacciHeap<T>::merge(FibonacciHeap &other) noexcept {
        if (min_ == nullptr) {
            min_ = other.min_;
        } else if (other.min_ == nullptr) {

        } else {
            //Ref:http://stackoverflow.com/questions/25606848/concatenate-2-circular-double-linked-list-without-using-extra-pointer
            node_ *t1 = min_->left;
            node_ *t2 = other.min_->left;

            min_->left = t2;
            t1->right = other.min_;
            other.min_->left = t1;
            t2->right = min_;
            if (other.min_->data < min_->data) {
                min_ = other.min_;
            }
        }
        size_ = size_ + other.size_;
        other.min_ = nullptr;
    }

}