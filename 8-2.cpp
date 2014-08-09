#include <iostream>
#include <vector>
#include <stdexcept>
#include <list>

using std::vector;
using std::domain_error;
using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::list;

namespace ben {

// equal
// sequential read only iterators
template <class In, class In2> bool equal(In begin, In end, In2 begin2)
{
    do {
        if (*begin != *begin2)
            return false;
        begin2++;
    } while (++begin != end);

    return true;
}

// find
// sequential read only iterators
template <class In, class X> In find(In begin, In end, const X& x)
{
    while (begin != end && *begin != x)
        begin++;

    return begin;
}

// copy
// sequential write only iterators
template <class In, class Out> Out copy(In begin, In end, Out dest)
{
    while (begin != end)
        *dest++ = *begin++;
    return dest;
}

// remove_copy_if
// sequential read and sequential write iterators
template <class In, class Out, class UnaryPredicate>
Out remove_copy_if(In begin, In end, Out dest, UnaryPredicate predicate)
{
    while (begin != end) {
        if (!predicate(*begin))
            *dest++ = *begin;
        begin++;
    }
    return dest;
}

// transform
// sequential read and sequential write iterators
template <class In, class Out, class X> Out transform(In begin, In end, Out dest, X func(In))
{
    while (begin != end)
        *dest++ = func(begin++);

    return dest;
}

// accumulate
// sequential read only iterators
template <class In, class X> X accumulate(In begin, In end, const X& x)
{
    X tempX = x;
    while (begin != end)
        tempX += *begin++;
        cout << tempX << endl;

    return tempX;
}

// search
// sequential read only iterators
template <class In, class In2> bool search(In begin, In end, In2 begin2, In2 end2)
{
    bool ret = false;

    while (begin != end && *begin != *begin2)
        begin++;

    while (begin != end && *begin == *begin2) {
        begin++;
        begin2++;
    }

    if (begin2 == end2)
        ret = true;

    return ret;
}

// find_if
// sequential read only iterators
template <class In, class UnaryPredicate> In find_if(In begin, In end, UnaryPredicate predicate)
{
    while (begin != end && !predicate(*begin))
        begin++;

    return begin;
}

// remove_copy
// sequential read and sequential write iterators
template <class In, class Out, class X> Out remove_copy(In begin, In end, Out dest, const X& x)
{
    while (begin != end) {
        if (*begin != x)
            *dest++ = *begin;
        begin++;
    }
    return dest;
}

// remove
// sequential read and write iterators
template <class In, class X> In remove(In begin, In end, const X& x)
{
    In ret = begin;
    while (begin != end) {
        if (*begin != x)
            *ret++ = *begin++;
        else
            begin++;
    }
    return ret;
}

// partition
// sequential read and write iterators
template <class In, class X> In partition(In begin, In end, const X& x)
{
    In ret = begin;
    while (++begin != end) {
        if (*begin == x) {
            In swapIt = begin;
            X temp = *swapIt;
            while (swapIt != ret)
                *swapIt-- = *(swapIt-1);
            *swapIt = temp;
            ret = begin+1;
        }
    }
}

}

bool isA(string element) {
    if(element == "B")
        return true;
    else
        return false;
}

string gradePlus(vector<string>::iterator element) {
    return *element + "+";
}

int main()
{
    vector<string> grades = {"A", "B", "A", "A", "C", "B", "B", "A"};
    vector<string> grades2;
    grades2 = grades;

    typedef vector<string>::iterator vcIt;
    string grade = "A";

    // Equal test
    bool equalResult = ben::equal(grades.begin(), grades.end(), grades2.begin());
    cout << "Equal function test: " << equalResult << endl;

    // Find test
    vcIt findResult = ben::find(grades.begin(), grades.end(), grade);
    cout << "Find function test: " << *findResult << endl;

    // Copy test
    vector<string> grades3;
    ben::copy(grades.begin(), grades.end(), back_inserter(grades3));
    cout << "Copy function test: " << grades3.back() << endl;

    // Remove_copy_if test
    vector<string> grades4;
    ben::remove_copy_if(grades.begin(), grades.end(), back_inserter(grades4), isA);
    cout << "Remove_copy_if function test: " << grades4.back() << endl;

    // Transform test
    vector<string> grades5;
    ben::transform(grades.begin(), grades.end(), back_inserter(grades5), gradePlus);
    cout << "Transform function test: " << grades5.back() << endl;

    // Accumulate test
    string sum = "";
    sum = ben::accumulate(grades.begin(), grades.end(), sum);
    cout << "Accumulate function test: " << sum << endl;

    // Search test
    bool searchResult = ben::search(grades.begin(), grades.end(), grades2.begin(), grades2.end());
    cout << "Search function test: " << searchResult << endl;

    // Find_if test
    vcIt found = ben::find_if(grades.begin(), grades.end(), isA);
    cout << "Find_if function test: " << *found << endl;

    // Remove_copy test
    string letter = "A";
    ben::remove_copy(grades.begin(), grades.end(), back_inserter(grades4), letter);
    cout << "Remove_copy function test: " << grades4.back() << endl;

    // Remove test
    ben::remove(grades2.begin(), grades2.end(), letter);
    cout << "Remove function test: " << grades4.back() << endl;

    // Partition test
    grades2 = grades;
    ben::partition(grades2.begin(), grades2.end(), letter);
    cout << "Partition function test: " << grades2.back() << endl;

    return 0;
}
