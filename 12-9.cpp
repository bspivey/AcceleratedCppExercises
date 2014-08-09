#include <iostream>
#include <memory>
#include <algorithm>
#include <cstring>
#include <iterator>

using std::allocator;
using std::cout;
using std::cin;
using std::endl;
using std::min;
using std::max;
using std::uninitialized_copy;
using std::uninitialized_fill;
using std::ptrdiff_t;
using std::back_inserter;
using std::istream;
using std::ostream;
using std::ostream_iterator;


class Str {
    friend std::istream& operator>>(istream&, Str&);
public:
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef size_t size_type;
    typedef char value_type;
    typedef char& reference;
    typedef const char& const_reference;

    Str() { create(); } // default constructor
    Str(size_type n, char c) { create(n,c); }
    Str(const char* cp) {
        create(cp, cp + strlen(cp));
    }

    explicit operator bool() const {
        if (size() == 0)
            return false;
        else
            return true;
    }

    Str& operator=(const Str& s) {
        uncreate();
        create(s.begin(), s.end());
    };

    Str& operator+=(const Str& s) {
        for (const_iterator it = s.begin(); it != s.end(); it++) {
            grow();
            const_reference itcr = *it;
            push_back(itcr);
        }
        return *this;
    }

     Str& operator+=(const char* c) {
        for (size_type i = 0; i != strlen(c); i++) {
            grow();
            push_back(c[i]);
        }
        return *this;
    }

    ~Str() {uncreate(); }

    char& operator[](size_type i) { return data[i]; }
    const char& operator[](size_type i) const { return data[i]; }

    bool operator==(Str& s) {
        Str temp = *this;
        size_type minLen = min(this->size(), s.size());
        for (size_type i = 0; i != minLen; i++) {
            if (temp[i] != s[i])
                return false;
        }
        return true;
    }

    bool operator!=(Str& s) {
        Str temp = *this;
        size_type minLen = min(this->size(), s.size());
        for (size_type i = 0; i != minLen; i++) {
            if (temp[i] != s[i])
                return true;
        }
        return false;
    }

    bool operator<(Str& s) {
        size_type l1, l2;
        l1 = this->size();
        l2 = s.size();
        if (l1 < l2)
            return true;
        else
            return false;
    }

    bool operator<=(Str& s) {
        size_type l1, l2;
        l1 = this->size();
        l2 = s.size();
        if (l1 <= l2)
            return true;
        else
            return false;
    }

    bool operator>(Str& s) {
        size_type l1, l2;
        l1 = this->size();
        l2 = s.size();
        if (l1 > l2)
            return true;
        else
            return false;
    }

    bool operator>=(Str& s) {
        size_type l1, l2;
        l1 = this->size();
        l2 = s.size();
        if (l1 >= l2)
            return true;
        else
            return false;
    }

    void push_back(const char& t) {
        if (avail == limit)
            grow();
        unchecked_append(t);
    }

    const_iterator c_str() {
        char temp[strlen(begin())+1];
        size_type j = 0;
        for (iterator it = begin(); it != end(); it++) {
            temp[j] = *it;
            j++;
        }
        temp[j] = '\0';
        const_iterator t_it = temp;
        return t_it;
    }

    const_iterator _data() {
        char temp[strlen(begin())];
        size_type j = 0;
        for (iterator it = begin(); it != end(); it++) {
            temp[j] = *it;
            j++;
        }
        const_iterator t_it = temp;
        return t_it;
    }

    void copy(char* p, size_type n) {
        size_type j = 0;
        for (iterator it = begin(); it != begin() + n; it++) {
            p[j] = *it;
            j++;
        }
    }

    istream& getline (istream& is, Str& s) {
        // obliterate existing value(s)
        s.uncreate();

        // check whether is exists and read the line
        char c;
        while(is.get(c) && c != '\n') {
            s.push_back(c);
        }

        return is;
    }

    istream& getline (istream& is, Str& s, char delim) {
        // obliterate existing value(s)
        s.uncreate();

        // check whether is exists and read the line
        char c;
        while(is.get(c) && c != '\n' && c != delim) {
            s.push_back(c);
        }

        return is;
    }

    size_type size() const { return avail - data; }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }

    iterator end() { return avail; }
    const_iterator end() const { return avail; }


private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<char> alloc;

    void create();
    void create(size_type, const char&);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void unchecked_append(const char&);

};

void Str::create()
{
    data = avail = limit = 0;
}

void Str::create(size_type n, const char& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

void Str::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}

void Str::uncreate()
{
    if (data) {
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);

        alloc.deallocate(data, limit - data);
    }

    data = limit = avail = 0;
}

void Str::grow()
{
    size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

void Str::unchecked_append(const char& val)
{
    alloc.construct(avail++, val);
}

Str operator+(const Str& s, const Str& t)
{
    Str r = s;
    r += t;
    return r;
}

Str operator+(const Str& s, const char* c)
{
    Str r = s;
    r += c;
    return r;
}

//ostream& operator<<(ostream& os, const Str& s) {
//    for (Str::size_type i = 0; i != s.size(); i++)
//        os << s[i];
//    return os;
//
//}

ostream& operator<<(ostream& os, const Str& s) {
    ostream_iterator<int> out_it (std::cout);
    copy ( s.begin(), s.end(), out_it );
    return os;
}


istream& operator>>(istream& is, Str& s)
{
    // obliterate existing value(s)
    s.uncreate();

    // read and discard leading whitespace
    char c;
    while (is.get(c) && isspace(c)) ; // nothing to do

    // if still something to read, do so until next whitespace character
    if (is) {
        do s.push_back(c);
        while (is.get(c) && !isspace(c));

        // if we read whitespace, then put it back on the stream
        if (is)
            is.unget();
    }
    return is;
}

int main() {

    Str city = "Atlanta";
    char name[] = {"Braves"};

    Str full;
    full += city;
    full += name;

    cout << full << endl;

    Str full2;
    if (full2)
        cout << "full is true" << endl;
    else
        cout << "full is false";

    return 0;
}
