#include <iostream>
#include <list>
#include <iterator>
#include <cassert>
#include <algorithm>

using std::list;
using std::string;
using std::endl;
using std::cout;


class String_list
{
public:
    typedef int size_type;

    // the bulk of the iterator code comes from the following reference
    // http://www.dreamincode.net/forums/topic/58468-making-your-own-iterators/
    // i have modified the iterator code to be bi-directional and modified
    // scope to use this iterator
    class iterator
    {
    public:
        typedef iterator self_type;
        typedef string value_type;
        typedef string& reference;
        typedef string* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        iterator(pointer ptr) : ptr_(ptr) { }
        self_type operator++() { self_type i = *this; ptr_++; return i; }
        self_type operator++(int junk) { ptr_++; return *this; }
        self_type operator--() { self_type i = *this; ptr_--; return i; }
        self_type operator--(int junk) { ptr_--; return *this; }
        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
    private:
        pointer ptr_;
    };

    String_list(list<string>::const_iterator start, list<string>::const_iterator finish) :
        start(start), finish(finish)
        {
            for (list<string>::const_iterator i = start; i != finish ;i++)
                list_o_strings.push_back(*i);
        }

    String_list(size_type size) : size_(size) {
        data_ = new string[size_];
    }

    size_type size() const { return size_; }

    string& operator[](size_type index)
    {
        assert(index < size_);
        return data_[index];
    }

    iterator begin()
    {
        return iterator(data_);
    }

    iterator end()
    {
        return iterator(data_ + size_);
    }

private:
    list<string> list_o_strings;
    list<string>::const_iterator start;
    list<string>::const_iterator finish;
    string* data_;
    size_type size_;
};

bool not_space(char c) {
    return !isspace(c);
}

bool space(char c) {
    return isspace(c);
}


template <class cOut>
void split(const string& str, cOut os) {

    typedef string::const_iterator iter;
    String_list::iterator it = os.begin();

    iter i = str.begin();
    while (i != str.end()) {
        // ignore leading blanks
        i = find_if(i, str.end(), not_space);

        // find end of next word
        iter j = find_if(i, str.end(), space);

        // copy the characters in [i,j]
        if (i != str.end()) {
            *it = string(i, j);   // changed
            cout << *it << endl;
            it++;
        }

        i = j;
    }
}

int main()
{
    typedef String_list::size_type sl_sz;
    sl_sz size = 30;
    String_list list_o_strings(size);

    string sentence = "We should note this curious mark of our own age: the only absolute allowed is the absolute insistence that there is no absolute.";
    split(sentence, list_o_strings);

    return 0;
}
