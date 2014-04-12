// Permuted index algorithm

#include <vector>
#include <iostream>
#include <ios>
#include <string>
#include <algorithm>

using std::cin;                 using std::sort;
using std::cout;                using std::vector;
using std::endl;                using std::string;

int main()
{
    typedef string::size_type string_size;
    string s;

    // read a line of input from the user
    getline(cin,s);
    string_size length = s.size();

    // generate rotations of the phrase
    string_size i = 0;
    int j = 0;
    vector<string> rotations;

    //invariant: we have processed characters [original value of i,i)
    while (i != length) {
        //ignore leading blanks
        //invariant: characters in range [original i, current i) are all spaces
        while (i != s.size() && isspace(s[i]))
            i++;

        // i is now the index at the start of the latest word
        // create a rotation string starting with this word
        string curRotation;
        int j = i - 2;
        (j > 0) ? (curRotation = (s.substr(i, length - i) + "AA" + s.substr(0, i - 1))) : (curRotation = (s.substr(i, length - i)));
        rotations.push_back(curRotation);

        cout << i << " " << curRotation << endl;

        // find next whitespace character
        //invariant: none of the characters in range [original j, current j) is a space
        while (i != s.size() && !isspace(s[i]))
            i++;
    }

    // sort the rotations
    sort(rotations.begin(), rotations.end());

    // unrotate the strings
    int sizeRotations = rotations.size();
    vector<string> left, right;
    string_size start;
    for (int i = 0; i != sizeRotations; i++) {
        string_size n = rotations[i].find("AA");
        if (n == string::npos)
            left.push_back("");
        else
            left.push_back(rotations[i].substr(n + 2, length));

        right.push_back(rotations[i].substr(0, n));

        cout.width(length);
        cout << left[i] << " " << right[i] << endl;
    }


    return 0;
}
