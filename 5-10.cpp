#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::streamsize;
using std::endl;                using std::string;
using std::max;                 using std::vector;
using std::ifstream;            using std::istringstream;
using std::exception;

int main()
{
    vector<string> palindromes;
    string::size_type maxlen = 0;   // the length of the longest palindronme

    // open the file
    ifstream dictionary;
    try {
        dictionary.open ("dictionary.txt");
    }
    catch (exception& e) {
        cout << "Standard exception: " << e.what() << endl;
    }

    // read and store the dictionary words
    // Invariant: word contains the most recent word read so far
    string word;
    string longestPal;

    while (getline(dictionary, word)) {
        // check whether the word is a palindrome
        bool isPalindrome;
        int i, j;

        // Invariant: i and j refer to the next two characters
        //            not checked in the word.
        i = 0;
        j = word.size() - 1;
        while (i <= j) {
            isPalindrome = true;

            if (word[i] != word[j]) {
                isPalindrome = false;
                break;
            }
            i++;
            j--;
        }

        // store the palindrome into a vector
        if (isPalindrome) {
            palindromes.push_back(word);

            // record the longest palindrome
            if (word.size() > maxlen) {
                longestPal = word;
                maxlen = max(maxlen, word.size());
            }

            // print palindrome
            cout << word << endl;
        }
    }

    cout << "The longest palindrome is: " << longestPal << endl;

    dictionary.close();
    return 0;
}
