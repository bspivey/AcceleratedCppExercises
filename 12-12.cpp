#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <vector>

using std::allocator;
using std::cout;
using std::endl;
using std::max;
using std::uninitialized_copy;
using std::uninitialized_fill;
using std::ptrdiff_t;
using std::string;
using std::vector;

template <class T> class Vec {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;

    Vec() { create(); } // default constructor
    explicit Vec(size_type n, const T& t = T()) { create(n, t); }
    Vec(const Vec& v) { create(v.begin(), v.end()); } // copy constructor
    Vec& operator=(const Vec&);
    ~Vec() {uncreate(); }

    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }

    void push_back(const T& t) {
        if (avail == limit)
            grow();
        unchecked_append(t);

    }

    void insert(iterator pos, iterator first, iterator last) {
        size_type delta = last - first;

        // grow Vec size enough to incorporate the additional range
        while ((limit - avail) < delta)
            grow();

        // initialize current as the object at the back of Vec
        iterator currentO = avail-1;
        iterator currentN = last-1;

        // invariant: currentO is the back-most object in Vec that has not been
        //            ovewritten with the new range.
        while (currentO >= pos) {
            alloc.construct(currentO+delta, *currentO);
            *currentO = *currentN;
            if (currentO == begin() || currentN == first)
                break;
            else {
                --currentO;
                --currentN;
            }
        }
        avail = avail + delta;
    }

    size_type size() const { return avail - data; }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }

    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    void uncreate();

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void grow();
    void unchecked_append(const T&);

};

template <class T> void Vec<T>::create()
{
    data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate()
{
    if (data) {
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);

        alloc.deallocate(data, limit - data);
    }

    data = limit = avail = 0;
}

template <class T> void Vec<T>::grow()
{
    size_type new_size = max(2 * (limit - data), ptrdiff_t(1));

    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);

    uncreate();

    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T> void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}


int main()
{
    Vec<string> mtnbiking;
    mtnbiking.push_back("berms");
    mtnbiking.push_back("fireroads");
    mtnbiking.push_back("singletrack");

    Vec<string> temp;
    temp.push_back("hardtail");
    temp.push_back("softtail");

    Vec<string>::iterator insertPos = mtnbiking.begin()+2;
    mtnbiking.insert(insertPos, temp.begin(), temp.end());

    for (Vec<string>::iterator it = mtnbiking.begin(); it != mtnbiking.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}
