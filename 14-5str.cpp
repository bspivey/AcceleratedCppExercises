#include <vector>
#include <cstring>
#include "str.h"

using std::istream;
using std::ostream;
using std::back_inserter;
using std::copy;
using std::strlen;
using std::cout;
using std::cin;
using std::endl;

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
    s.data->uncreate();

    // read and discard leading whitespace
    char c;
    while (is.get(c) && isspace(c)) ; // nothing to do

    // if still something to read, do so until next whitespace character
    if (is) {
        do s.data->push_back(c);
        while (is.get(c) && !isspace(c));

        // if we read whitespace, then put it back on the stream
        if (is)
            is.unget();
    }
    return is;
}
