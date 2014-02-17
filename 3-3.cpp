#include <algorithm>
#include <iostream>
#include <vector>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::string;

int main()
{
    // prompt the user to enter a set of words
    cout << "Enter a series of words, and  this program"  << endl <<
            "will calculate the frequency of each word: " << endl;

    // store a vector of strings
    vector<string> wordSet;
    typedef vector<string>::size_type vec_sz;
    vec_sz size = 0;
    string word;

    // invariant: the user has entered as many words as the size of wordSet
    while(cin >> word)
        wordSet.push_back(word);
    size = wordSet.size();

    // sort words
    sort (wordSet.begin(), wordSet.end());

    // count the frequency of each identical word in wordSet
    vector<int> wordFreq = {0};
    typedef vector<int>::size_type int_sz;
    int_sz countF = 0;
    int counter = 0;

    vector<string> wordList = {""};
    typedef vector<string>::size_type str_sz;

    string firstWord = wordSet[size-1];
    // invariant: the iterator is looking at the first word from the end that has not been compared
    vector<string>::reverse_iterator rit = wordSet.rbegin();
    for (rit = wordSet.rbegin(); rit != wordSet.rend(); ++rit)
    {
        if (firstWord == *rit) {
            wordFreq[countF] = ++counter;
        }
        else {
            cout << "The count for word " << firstWord << " is " << wordFreq[countF] << "." << endl;
            firstWord = *rit;
            counter = 0;
            wordFreq.push_back(0); // add another element for the new word
            counter++;
            countF++;
        }
    }
    cout << "The count for word " << firstWord << " is " << wordFreq[countF] << "." << endl;

    return 0;
}
