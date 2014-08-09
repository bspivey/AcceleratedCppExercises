#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <list>

using std::vector;
using std::domain_error;
using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::list;


template <class T, class In>
T median (In begin, In end)
{
    int size = end - begin;
    if (size == 0)
        throw domain_error("median of an empty vector");

    sort (begin, end);

    int mid = size / 2;

    return size % 2 == 0 ? (*(begin+mid) + *(begin+mid-1)) / 2 : *(begin+mid);
}

// Sequential RO
template <class In, class X> In find(In begin, In end, const X& x)
{
    while (begin != end && *begin != x)
        ++begin;
    return begin;
}

// Sequential WO
template <class In, class Out>
Out copy(In begin, In end, Out dest)
{
    while (begin != end)
        *dest++ = *begin++;
    return dest;
}

// Sequential RW
template <class For, class X>
void replace(For beg, For end, const X& x, const X& y)
{
    while (beg != end) {
        if (*beg == x)
            *beg = y;
        ++beg;
    }
}

// Reversible
template <class Bi> void reverse(Bi begin, Bi end)
{
    while (begin != end) {
        --end;
        if (begin != end)
            swap(*begin++, *end);
    }
}

// Random access
template <class Ran, class X>
bool binary_search(Ran begin, Ran end, const X& x)
{
    while (begin < end) {
        // find the midpoint of the range
        Ran mid = begin + (end - begin) / 2;

        // see which part of the range contains x; keep looking only in that part
        if (x < *mid)
            end = mid;
        else if (*mid < x)
            begin = mid + 1;
        // if we got here, then *mid == x so we're done
        else return true;
    }
    return false;
}

bool not_space(char c) {
    return !isspace(c);
}

bool space(char c) {
    return isspace(c);
}

template <class cOut>
void split(const string& str, cOut os) {

    typedef string::const_iterator iter;

    iter i = str.begin();
    while (i != str.end()) {
        // ignore leading blanks
        i = find_if(i, str.end(), not_space);

        // find end of next word
        iter j = find_if(i, str.end(), space);

        // copy the characters in [i,j]
        if (i != str.end()) {
            *os++ = string(i, j);   // changed
        }

        i = j;
    }

}

int main()
{
    vector<int> intVector = {25, 34, 57};
    int intMedian = median<int>(intVector.begin(), intVector.end());
    cout << "Median of an int vector is: " << intMedian << endl;

    vector<double> dubVector = {2.2, 5.7, 9.7};
    double dubMedian = median<double>(dubVector.begin(), dubVector.end());
    cout << "Median of a double vector is: " << dubMedian << endl;

    string line;
    getline(cin, line);
    list<string> words;
    split(line, back_inserter(words));

    for (list<string>::const_iterator it = words.begin(); it != words.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}
