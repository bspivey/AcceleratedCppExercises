#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;

int main()
{
    vector<int> intSet = {1, 25, 51, 76, 100};

    // find the size of the integer set
    typedef vector<int>::size_type vec_sz;
    vec_sz size = intSet.size();

    // sort the integer set
    sort(intSet.begin(), intSet.end());

    // calculate the quartiles
    double q1, median, q3, mid;
    mid = size / 2;
    median = (size % 2 == 0) ? (intSet[mid] + intSet[mid - 1]) / 2
                             : intSet[mid];
    q1 = (size % 4 == 0)     ? (intSet[size / 4] + intSet[size /4 - 1]) /2
                             : intSet[size / 4];
    q3 = (size % 4 == 0)     ? (intSet[size * 3 / 4] + intSet[size * 3 / 4 - 1]) / 2
                             : intSet[size * 3 / 4];

    // display results on the console
    cout << "The quartiles for the integer set are calculated as follows: " << endl;
    cout << "   Q1 = " << q1 << endl;
    cout << "   Q2 = " << median << endl;
    cout << "   Q3 = " << q3 << endl;


    return 0;
}
