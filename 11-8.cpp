#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>

using std::allocator;
using std::cout;
using std::endl;
using std::max;
using std::uninitialized_copy;
using std::ptrdiff_t;
using std::copy;
using std::vector;

template <class T>
class Node;

template <class T>
class LList {
public:

    typedef Node<T> value_type;
    typedef Node<T>& reference;
    typedef const Node<T>& const_reference;
    typedef int size_type;

    class iterator {
    public:
        typedef iterator self_type;
        typedef Node<T>& reference;
        typedef Node<T>* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        typedef int size_type;
        typedef Node<T> value_type;

        iterator() { }
        iterator(pointer ptr) : ptr_(ptr) { }
        self_type operator++() { self_type it = *this; ptr_ = ptr_->next; return it; }
        self_type operator+(int junk) { self_type it = *this;
                                        for (int i = 1; i != junk; i++) {
                                            ptr_ = ptr_->next;
                                        }
                                        return it; }

        self_type operator-(int junk) { self_type it = *this;
                                        for (int i = junk; i != 0; i--) {
                                            ptr_ = ptr_->previous;
                                        }
                                        return it; }
        self_type operator++(int junk) { ptr_ = ptr_->next ; return *this; }
        self_type operator--() { self_type it = *this; ptr_ = ptr_->previous; return it; }
        self_type operator--(int junk) { ptr_ = ptr_->previous; return *this; }
        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        pointer getPtr() { return ptr_; }
    private:
        pointer ptr_;
    };

    LList() { create(); } // default constructor
    LList(LList& ll) { create(ll.begin(), ll.end()); } // copy constructor
    //Vec& operator=(const Vec&);
    //~Vec() {uncreate(); }

    void push_back(const T& t) {
        iterator lastIter;
        iterator nextIter;
        // handle assigning start if first element
        if (finish == 0) {
            Node<T>* st = alloc.allocate(1);
            iterator start_(st);
            start = start_;
            start->object = t;
            start->previous = 0;
            start->next = 0;
            lastIter = start;
        }
        else {
            finish->object = t;
            lastIter = finish;
        }

        // create empty final element
        Node<T>* fn = alloc.allocate(1);
        iterator finish_(fn);
        finish = finish_;
        finish->previous = lastIter.getPtr();
        lastIter->next = finish.getPtr();
        finish->next = 0;
    }

    iterator begin() { return start; }
    iterator end() { return finish; }

private:
    iterator start;
    iterator finish;
    size_type size_;
    allocator<Node<T> > alloc;

    void create();
    void create(iterator, iterator);
    void uncreate();
};

template <class T>
class Node {
public:
    Node() : previous(0), next(0) { };

    typedef Node<T>* ptr;
    typedef T value_type;

    value_type object;
    ptr previous;
    ptr next;

// should define operator=

};


template <class T>
void LList<T>::create()
{
    start = finish = 0;
}

template <class T>
void LList<T>::create(iterator i, iterator j)
{
    iterator lastIter;
    iterator nextIter;

    for (LList<T>::iterator it = i; it != j; it++) {

        // assign iterator values for start, previous, and next
        if (it == i) {
            Node<T>* st = alloc.allocate(1);
            iterator start_(st);
            start = start_;
            nextIter = uninitialized_copy(it, it+1, start);
            // since copy copies the previous and next members from the original list
            // we need to negate them here
            start->previous = 0;
            start->next = 0;
            lastIter = start;
        }
        else {
            nextIter = uninitialized_copy(it, it+1, finish);
            lastIter = finish;
        }
        // create empty final element
        Node<T>* fn = alloc.allocate(1);
        iterator finish_(fn);
        finish = finish_;
        finish->previous = lastIter.getPtr();
        lastIter->next = finish.getPtr();
        finish->next = 0;
    }
}


template <class T>
void LList<T>::uncreate()
{
    if (start) {
        iterator it = finish;
        while (it != start)
            alloc.destroy(--it);

        alloc.deallocate(start, finish - start);
    }

    start = finish = 0;
}


int main()
{
    LList<int> ages;
    ages.push_back(31);
    ages.push_back(60);
    ages.push_back(0);
    ages.push_back(36);
    ages.push_back(14);
    ages.push_back(0);

    LList<int> copyAges(ages);

    int x = ages.begin()->object;
    int y = ages.begin()->object;

    cout << x << " " << y << endl;

    //for (LList<int>::iterator it = ages.begin(); it != ages.end(); it++)
    //    cout << it->object << endl;

    return 0;
}
