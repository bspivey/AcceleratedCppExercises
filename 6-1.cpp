#include <vector>
#include <iostream>
#include <ios>
#include <string>
#include <algorithm>

using std::cin;                 using std::max;
using std::cout;                using std::vector;
using std::endl;                using std::string;

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

vector<string> frame(const vector<string>& v)
{
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');

    // write the top border
    ret.push_back(border);

    // write each interior row, bordered by an asterisk and a space
    for (vector<string>::const_iterator iter = v.begin(); iter != v.end(); ++iter) {
        ret.push_back("* " + *iter + string(maxlen - iter->size(), ' ') + " *");
    }

    // write the bottom border
    ret.push_back(border);
    return ret;

}

vector<string> vcat(const vector<string>& top, const vector<string>& bottom)
{
    // copy the top picture
    vector<string> ret = top;

    // copy entire bottom picture
    for (vector<string>::const_iterator it = bottom.begin(); it != bottom.end(); ++it)
        ret.push_back(*it);

    return ret;
}

vector<string> hcat(const vector<string>& left, const vector<string>& right)
{
    vector<string> ret;

    // add 1 to leave a space between pictures
    string::size_type width1 = width(left) + 1;

    // indices to look at elements from left and right respectively
    vector<string>::const_iterator i = left.begin();
    vector<string>::const_iterator j = right.begin();

    // continue until we've seen all rows from both pictures
    while (i != left.end() || j != right.end()) {
        // construct new string to hold characters from both pictures
        string s;

        // copy a row from the left-hand side, if there is one
        if (i != left.end()) {
            s = *i;
            i++;
        }

        // pad to full width
        s += string (width1 - s.size(), ' ');

        // copy a row form the right-hand side, if there is one
        if (j != right.end()) {
            s += *j;
            j++;
        }

        // add s to the picture we're creating
        ret.push_back(s);
    }
    return ret;
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

    // Frame function
    vector<string> fv = frame(v);
    // write each line in fv
    for (vector<string>::size_type i = 0; i != fv.size(); ++i)
        cout << fv[i] << endl;

    // Vcat function
    vector<string> vv = vcat(fv, fv);
    for (vector<string>::size_type i = 0; i != vv.size(); ++i)
        cout << vv[i] << endl;

    // Hcat function
    vector<string> hv = hcat(fv, fv);
    for (vector<string>::size_type i = 0; i != hv.size(); ++i)
        cout << hv[i] << endl;



    return 0;
}
