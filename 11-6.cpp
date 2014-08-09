#include <iostream>
#include <memory>
#include <algorithm>

using std::allocator;
using std::cout;
using std::endl;
using std::max;
using std::uninitialized_copy;
using std::ptrdiff_t;
using std::copy;

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

    //void erase2(size_type); // returns an iterator to avail
    iterator clear();

    }

    size_type size() const { return avail - data; }

    iterator begin() { return data; }
    const_iterator begin() const { return data; }

    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    void erase(size_type);

    void clear() { uncreate(); }

private:
    iterator data;
    iterator avail;
    iterator limit;

    allocator<T> alloc;

    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void unchecked_append(const T&);
};

template <class T> void Vec<T>::erase(size_type i)
{
    for (iterator it = begin() + i; it != end(); it++) {
        *it = *(it + 1);
    }
    avail--;
}

template <class T> void Vec<T>::create()
{
    data = avail = limit = 0;
}



template <class T> void Vec<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    uinitialized_fill(data, limit, val);
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
    Vec<int> ages;
    ages.push_back(31);
    ages.push_back(60);
    ages.push_back(0);
    ages.push_back(36);
    ages.push_back(14);
    ages.push_back(0);
    Vec<int>::size_type n = ages.size();
    ages[n-1] = 7;

    ages.erase(2);
    n = ages.size();

    for (Vec<int>::size_type i = 0; i != n; i++)
        cout << ages[i] << endl;

    return 0;
}
