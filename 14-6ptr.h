#ifndef GUARD_Ptr
#define GUARD_Ptr

//Ptr.h header file
#include "vec.h"

using std::size_t;

template <class T> T* clone (const T* tp);
template<> Vec<char>* clone(const Vec<char>* vp);
template <class T> class Ptr;

class Cntr {
public:
    size_t* refptr; // member made public while debugging

    Cntr() : refptr(new size_t(1)) { }
    Cntr(const Cntr& cntptr) : refptr(cntptr.refptr) { ++*refptr; }
    Cntr(size_t* t) : refptr(t) { }

    ~Cntr()
    {
        delete refptr;
    }

    size_t value() {
        return *refptr;
    }

    size_t add() {
        ++*refptr;
        return *refptr;
    }

    size_t subtract() {
        --*refptr;
        return *refptr;
    }

};


template <class T>
class Ptr {
public:
    // new member to copy the object conditionally when needed
    void make_unique()
    {
       if (cntptr.value() != 1) {
            cntptr.subtract();
            cntptr(new size_t(1));
            p = p? clone(p) : 0; // call the global version of close
       }
    }

    // the rest of the class looks like Ref_handle except for its name
    Ptr() : p(0), cntptr()  { }
    Ptr(T* t): p(t), cntptr() { }
    Ptr(const Ptr<T>& h): p(h.p), cntptr(h.cntptr) { }

    Ptr<T>& operator=(const Ptr<T>& rhs)
    {
        cntptr.add();
        // free the lhs, destroying pointers if appropriate
        if (cntptr.subtract() == 0) {
            ~cntptr();
            delete p;
        }
        // copy in values from the rhs
        cntptr(rhs.cntptr);
        p = rhs.p;
        return *this;
    }

    ~Ptr()
    {
        if (cntptr.subtract() == 0) {
            ~cntptr();
            delete p;
        }
    }

    operator bool() const { return p; }
    T& operator*() const {
        if (p)
            return *p;
        throw std::runtime_error("unbound Ptr");
    }

    T* operator->() const {
        if (p)
            return p;
        throw std::runtime_error("unbound Ptr");
    }

private:
    T* p;
    Cntr cntptr;
};


#endif //GUARD_Ptr
