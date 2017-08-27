#ifndef GUARD_Ptr
#define GUARD_Ptr

#include <iomanip>
#include <ios>
#include <stdexcept>
#include <string>
#include <iostream>


using std::istream;
using std::ostream;
using std::back_inserter;
using std::copy;
using std::strlen;
using std::cout;
using std::cin;
using std::endl;

//Ptr.h header file

template <class T> class Vec;

template <class T> T* clone (const T*);

template<>
Vec<char>* clone(const Vec<char>*);


template <class T>
class Ptr {
public:
    // new member to copy the object conditionally when needed
    void make_unique()
    {
       if (*refptr != 1) {
            --*refptr;
            refptr = new size_t(1);
            p = p? clone(p) : 0; // call the global version of close
       }
    }

    // the rest of the class looks like Ref_handle except for its name
    Ptr() : p(0) , refptr(new size_t(1)) { }
    Ptr(T* t): p(t), refptr(new size_t(1)) { }
    Ptr(const Ptr& h): p(h.p), refptr(h.refptr) { ++*refptr; }

    Ptr& operator=(const Ptr&);
    ~Ptr();
    operator bool() const { return p; }
    T& operator*() const;
    T* operator->() const;

private:
    T* p;
    std::size_t* refptr;
};

template <class T>
Ptr<T>& Ptr<T>::operator=(const Ptr& rhs)
{
    ++*rhs.refptr;
    // free the lhs, destroying pointers if appropriate
    if (--*refptr == 0) {
        delete refptr;
        delete p;
    }
    // copy in values from the rhs
    refptr = rhs.refptr;
    p = rhs.p;
    return *this;
}

template <class T>
Ptr<T>::~Ptr()
{
    if (--*refptr == 0) {
        delete refptr;
        delete p;
    }
}

template <class T>
T& Ptr<T>::operator*() const {
    if (p)
        return *p;
    throw std::runtime_error("unbound Ptr");
}

template <class T>
T* Ptr<T>::operator->() const {
    if (p)
        return p;
    throw std::runtime_error("unbound Ptr");
}



#endif //GUARD_Ptr
