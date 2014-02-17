#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::string;
using std::getline;

bool strLengthComp (const string a, const string b) {
    return (a.size() < b.size());
}

int main()
{
    // prompt the user to enter a set of strings
    cout << "Enter a series of strings. Enter \"exit\" to break the loop." << endl;

    // store a vector of strings
    vector<string> strSet;

    // invariant: the number of elements in strSet equals the number of lines entered
    string currentLine;
    while(getline(cin, currentLine))
        strSet.push_back(currentLine);

    // sort strings by length
    sort (strSet.begin(), strSet.end(), strLengthComp);

    // return the shortest and longest strings
    typedef vector<string>::size_type sz_vStr;
    sz_vStr size = strSet.size();

    cout << "The shortest string : "  << *strSet.begin()   << endl;
    cout << "The longest string : "   << strSet[size - 1] << endl;


    return 0;
}
