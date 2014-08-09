#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using std::vector;
using std::domain_error;
using std::string;
using std::endl;
using std::cout;
using std::sort;


template <class T>
T median (vector<T> v)
{
    typedef typename vector<T>::size_type vec_sz;

    vec_sz size = v.size();
    if (size == 0)
        throw domain_error("median of an empty vector");

    sort (v.begin(), v.end());

    vec_sz mid = size / 2;

    return size % 2 == 0 ? (v[mid] + v[mid-1]) / 2 : v[mid];
}


template <class T>
T median (T* a)
{

    const size_t size = sizeof(a);
    if (size == 0)
        throw domain_error("median of an empty array");

    sort(a, a + size);

    size_t mid = size / 2;

    return size % 2 == 0 ? (a[mid] + a[mid-1]) / 2 : a[mid];


}

int main()
{
    vector<int> intVector = {25, 34, 57};
    int intMedian = median(intVector);
    cout << "Median of an int vector is: " << intMedian << endl;

    vector<double> dubVector = {2.2, 5.7, 9.7};
    double dubMedian = median(dubVector);
    cout << "Median of a double vector is: " << dubMedian << endl;

    double numbers[] = {1, 2, 3, 4, 5};
    double arrMedian = median(numbers);
    cout << "Median of a double array is: " << arrMedian << endl;


    return 0;
}
