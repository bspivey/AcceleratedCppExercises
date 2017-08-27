#include <iomanip>
#include <ios>
#include <stdexcept>
#include <string>
#include "grad.h"
#include "str.h"

using std::istream;
using std::ostream;
using std::back_inserter;
using std::copy;
using std::strlen;
using std::cout;
using std::cin;
using std::endl;

// Classes
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


//Function definitions
template <class T> T* clone (const T* tp)
{
    return tp->clone();
}

template<>
Vec<char>* clone(const Vec<char>* vp)
{
    return new Vec<char>(*vp);
}

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

// Ch. 13 Function definitions
istream& read_hw(istream& in, vector<double>& hw)
{
    if (in) {
        // get rid of previous contents
        hw.clear();

        // read homework grades
        double x;
        while (in >> x)
            hw.push_back(x);

        // clear the stream so that input will work for the next student
        in.clear();
    }
    return in;
}

string Core::name() const { return n; }

istream& Core::read(istream& in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

istream& Core::read_common(istream& in)
{
    in >> n >> midterm >> final;
    return in;
}

istream& Grad::read(istream& in)
{
    Core::read_common(in);
    in >> thesis;
    read_hw(in, Core::homework);
    return in;
}

// Comparison operations

bool compare(const Core& c1, const Core& c2)
{
    return c1.name() < c2.name();
}

bool compare_Core_Ptrs(const Ptr<Core> pc1, const Ptr<Core> pc2)
{
    return compare(*pc1, *pc2);
}



int main()
{



    return 0;
}
