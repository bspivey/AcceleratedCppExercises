#ifndef GUARD_Ptr
#define GUARD_Ptr

//Ptr.h header file
#include "vec.h"

template <class T> T* clone (const T* tp);
template<> Vec<char>* clone(const Vec<char>* vp);

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

    Ptr<T>& operator=(const Ptr<T>& rhs)
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

    ~Ptr()
    {
        if (--*refptr == 0) {
            delete refptr;
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
    std::size_t* refptr;
};

#endif //GUARD_Ptr
