#include <iostream>
#include <algorithm>
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
    Str(const char* cp) : data(cp, cp + strlen(cp)) { }

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

Str operator+(const Str& s, const Str& t)
{
    Str r = s;
    r += t;
    return r;
}

ostream& operator<<(ostream& os, const Str& s) {
    for (Str::size_type i = 0; i != s.size(); i++)
        os << s[i];
    return os;

}

istream& operator>>(istream& is, Str& s)
{
    // obliterate existing value(s)
    s.data.uncreate();

    // read and discard leading whitespace
    char c;
    while (is.get(c) && isspace(c)) ; // nothing to do

    // if still something to read, do so until next whitespace character
    if (is) {
        do s.data.push_back(c);
        while (is.get(c) && !isspace(c));

        // if we read whitespace, then put it back on the stream
        if (is)
            is.unget();
    }
    return is;
}


int main()
{
    const char before[] = {"Never be afraid of complexity."};

    Str quote(before);

    cout << quote << endl;


    return 0;
}
