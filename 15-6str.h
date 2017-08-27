#ifndef GUARD_str
#define GUARD_str

#include <vector>
#include <cstring>
#include <iomanip>
#include <ios>
#include <stdexcept>
#include <string>
#include <iostream>
#include "vec.h"
#include "ptr.h"

using std::istream;
using std::ostream;
using std::back_inserter;
using std::copy;
using std::strlen;
using std::cout;
using std::cin;
using std::endl;

template <class T> class Vec;
template <class T> class Ptr;

class Str;
ostream& operator<<(ostream& os, const Str& );

class Str {
    friend std::istream& operator>>(istream&, Str&);

public:
    Str& operator+=(const Str& s) {
        data.make_unique();
        std::copy(s.data->begin(), s.data->end(), std::back_inserter(*data));
        return *this;
    }

    // as before
    typedef Vec<char>::size_type size_type;
    typedef Vec<char>::const_iterator const_iterator;

    Str(): data(new Vec<char>) { }
    Str(const char* cp): data(new Vec<char>) {
        std::copy(cp, cp + strlen(cp), back_inserter(*data));
    }
    Str(size_type n, char c): data(new Vec<char>(n, c)) { }
    template <class In> Str(In b, In e): data(new Vec<char>) {
        std::copy(b, e, std::back_inserter(*data));
    }

    char& operator[](size_type i) {
        data.make_unique();
        return (*data)[i];
    }
    const char& operator[] (size_type i) const { return (*data)[i]; }
    size_type size() const { return data->size(); }

    // Code for 14-4
    Str substr(size_type i, size_type d) const {
        const_iterator cStart, cTerm;
        cStart = this->data->begin() + i;
        cTerm  = this->data->begin() + i + d;
        Str sub(cStart, cTerm);
        return sub;
    }

private:
    Ptr< Vec<char> > data;
};



#endif //GUARD_vec
