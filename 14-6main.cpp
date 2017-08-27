#include <iomanip>
#include <ios>
#include <stdexcept>
#include <string>
#include "grad.h"
#include "ptr.h"
#include "Student_info.h"
#include <vector>

#include <cstring>

using std::istream;
using std::ostream;
using std::back_inserter;
using std::copy;
using std::strlen;
using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::setprecision;
using std::domain_error;
using std::vector;
using std::string;




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



vector<Str> split(const Str& s)
{
    typedef Str::size_type string_size;
    string_size i = 0;
    //Str retStr;
    vector<Str> ret;

    while (i < s.size()) {
        while (i < s.size() && isspace(s[i]))
            ++i;

        // find end of next word
        string_size j = i;

        while (j < s.size()) {
            if (!isspace(s[j]))
                ++j;
            else
                break;
        }

        if (i != j) {
            // copy from s starting at i and taking j - i chars
            Str temp = s.substr(i, j - i);
            ret.push_back(temp);
            i = j;
        }

        i = j;
    }
    return ret;
}



int main() {
/*
    Str greeting = "Hello, world!";
    vector<Str> result;
    result = split(greeting);

    cout << greeting << endl;

 for (int i = 0; i != result.size(); i++) {
        cout << result[i] << endl;
}
*/
    return 0;
}
