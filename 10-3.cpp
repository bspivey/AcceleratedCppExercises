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
T median (T* a, size_t size)
{
    T b[size];
    for (size_t i = 0; i != size; i++) {
        b[i] = *(a + i);
    }

    if (size == 0)
        throw domain_error("median of an empty array");

    sort(b, b + size);

    size_t mid = size / 2;
    cout << mid << endl;

    return size % 2 == 0 ? (b[mid] + b[mid-1]) / 2 : b[mid];


}

int main()
{
    vector<int> intVector = {25, 34, 57};
    int intMedian = median(intVector);
    cout << "Median of an int vector is: " << intMedian << endl;

    vector<double> dubVector = {2.2, 5.7, 9.7};
    double dubMedian = median(dubVector);
    cout << "Median of a double vector is: " << dubMedian << endl;

    double numbers[] = {5, 4, 3, 2, 1};
    size_t size = sizeof(numbers)/sizeof(*numbers);
    double arrMedian = median(numbers, size);
    cout << "Median of a double array is: " << arrMedian << endl;
    cout << "First element is: " << numbers[0];


    return 0;
}
