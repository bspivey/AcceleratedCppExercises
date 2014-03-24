#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>

using std::vector;              using std::string;
using std::cin;                 using std::istream;
using std::max;                 using std::cout;
using std::setw;                using std::endl;
using std::stringstream;        using std::fixed;

int main()
{
    // while loop receiving input from user and calculating square
    // populate value and square vectors
    vector<int> nominal;
    vector<int> square;
    double maxLength = 0;
    char entry[256];


    // Invariant: the size of nominal matches the number of entries read into a vector
    while(true) {
        int size, entryInt;
        cin.get(entry,256);

        if (cin.get() == EOF) break;

        stringstream str(entry);
        str >> entryInt;

        nominal.push_back(entryInt);
        square.push_back(pow(entryInt, 2));

        // find length of longest squared term
        double order;
        order = floor(log10( square.back() ));
        maxLength = max(maxLength, order) + 2;
    }

    // write two columns to the console
    for(vector<int>::size_type i = 0; i != nominal.size(); i++) {
        cout << fixed << nominal[i];
        cout << setw(maxLength);
        cout << square[i] << endl;
    }


    return 0;
}
