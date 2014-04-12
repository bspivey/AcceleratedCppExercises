#include <vector>
#include <iostream>
#include <ios>
#include <string>
#include <algorithm>
#include <cmath>

using std::cin;                 using std::max;
using std::cout;                using std::vector;
using std::endl;                using std::string;
using std::streamsize;

string::size_type width(const vector<string>& v)
{
    string::size_type maxlen = 0;
    for(vector<string>::size_type i = 0; i != v.size(); ++i)
        maxlen = max(maxlen, v[i].size());
    return maxlen;
}

vector<string> split(const string& s)
{
    vector<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    //invariant: we have process characters [original value of i,i)
    while (i != s.size()) {
        //ignore leading blanks
        //invariant: characters in range [original i, current i) are all spaces
        while (i != s.size() && isspace(s[i]))
            ++i;

        // find end of next word
        string_size j = i;

        //invariant: none of the characters in range [original j, current j) is a space
        while (j != s.size() && !isspace(s[j]))
            ++j;

        // if we found some nonwhitespace characters
        if (i != j) {
            // copy from s starting at i and taking j - i chars
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

vector<string> center(const vector<string>& originalVec)
{
    int rem, half;
    vector<string> centerVec;
    string::size_type maxLength = 0;
    vector<string>::size_type elements, diff;

    vector<string>::const_iterator iter = originalVec.begin();
    while (iter != originalVec.end()) {
        maxLength = max(maxLength, iter->size());
        iter++;
    }
    int maxLengthI = maxLength;

    iter = originalVec.begin();
    while (iter != originalVec.end()) {
        int lineSize = iter->size();
        diff = maxLengthI - lineSize;
        half = floor(diff / 2);
        rem = diff % 2;
        if (rem == 0)        // even difference
            centerVec.push_back(string(half, ' ') + *iter + string(half, ' '));
        else                 // odd difference
            centerVec.push_back(string(half, ' ') + *iter + string(half+1, ' '));

        iter++;
    }

    return centerVec;
}



int main()
{
    string s;
    vector<string> v;

    // Split function
    // read and split each line of input
    while (getline(cin, s)) {
        v = split(s);

        // write each word in v
        for (vector<string>::size_type i = 0; i != v.size(); ++i)
            cout << v[i] << endl;
    }

    // Center function
    vector<string> cv = center(v);
    for (vector<string>::size_type i = 0; i != cv.size(); ++i)
        cout << cv[i] << endl;

    cout << endl;

    return 0;
}
