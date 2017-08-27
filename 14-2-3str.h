#include <vector>
#include <cstring>
#include "11-0.h"


using std::istream;
using std::ostream;
using std::back_inserter;
using std::copy;
using std::strlen;
using std::cout;
using std::cin;
using std::endl;

class Str {
    friend std::istream& operator>>(istream&, Str&);

public:
    // as before
    typedef Vec<char>::size_type size_type;
    Str() { }
    Str(size_type n, char c): data(n, c) { }
    Str(const char* cp) {
        std::copy(cp, cp + strlen(cp), back_inserter(data));
    }
    template <class In> Str(In b, In e) {
        std::copy(b, e, std::back_inserter(data));
    }

    char& operator[](size_type i) { return data[i]; }
    const char& operator[] (size_type i) const { return data[i]; }
    size_type size() const { return data.size(); }

    Str& operator+=(const Str& s) {
        copy(s.data.begin(), s.data.end(), back_inserter(data));
        return *this;
    }

private:
    Vec<char> data;
};
