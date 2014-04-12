#include <iostream>
#include <string>
#include <list>
#include <cctype>

using std::cin;         using std::cout;
using std::string;      using std::list;
using std::endl;

list<string> split(const string& s)
{
    list<string> ret;
    typedef string::size_type string_size;
    string_size i = 0;

    //invariant: we have processed characters [original value of i,i)
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

// findCase receives a string list and modifies the list to
// only contain strings without an upper case letter. The
// function returns a list containing strings having an
// upper case letter.
list<string> separateByCase(list<string>& s)
{
    list<string> upperWords;
    list<string>::size_type sizeV;
    typedef list<string>::iterator vit_type;
    sizeV = s.size();

    for (vit_type iter = s.begin(); iter != s.end(); iter++) {
        string str = *iter;
        char c;
        bool hasCaps = false;

        int j = 0;
        while(str[j]) {
            c = str[j];
            if (isupper(c)) hasCaps = true;
            j++;
        }

        if (hasCaps) {
            upperWords.push_back(*iter);
            iter = s.erase(iter);
        }
    }

    return upperWords;
}

int main() {

    string s;
    list<string> words;
    list<string> upperWords;
    typedef list<string>::const_iterator lit_type;


    // store user input
    getline(cin, s);

    // split the input into a list of words
    words = split(s);

    // modify original word list to contain only lower case letters
    // create a new list with words containing upper case letters
    upperWords = separateByCase(words);

    cout << "Lower case words: " << endl;
    for (lit_type iter = words.begin(); iter != words.end(); iter++)
        cout << *iter << endl;

    cout << "Upper case words: " << endl;
    for (lit_type iter = upperWords.begin(); iter != upperWords.end(); iter++)
        cout << *iter << endl;

  return 0;
}
