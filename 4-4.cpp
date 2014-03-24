#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>


using std::vector;              using std::string;
using std::cin;                 using std::istream;
using std::max;                 using std::cout;
using std::setw;                using std::endl;
        using std::fixed;
         using std::setprecision;

int main()
{
    // while loop receiving input from user and calculating square
    // populate value and square vectors
    vector<double> nominal;
    vector<double> square;
    double maxLength = 0;
    char entry[256];


    // Invariant: the size of nominal matches the number of entries read into a vector
    while(true) {
        int size;
        double entryDub;
        cin.get(entry,256);

        if (cin.get() == EOF) break;

        stringstream str(entry);
        str >> entryDub;

        nominal.push_back(entryDub);
        square.push_back(pow(entryDub, 2));

        // find length of longest squared term
        double order;
        order = floor(log10( square.back() ));
        maxLength = max(maxLength, order + 1) + 3; // plus three for period and decimal
    }

    // write two columns to the console
    streamsize prec = cout.precision();
    for(vector<int>::size_type i = 0; i != nominal.size(); i++) {
        cout << fixed << setprecision(2) << nominal[i];
        cout << setw(maxLength);
        cout << square[i] << endl;
    }


    return 0;
}
