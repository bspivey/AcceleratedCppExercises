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
    vector<string> noAsDes;
    string::size_type maxlen = 0;   // the length of the longest word without ascenders or descenders
    vector<char> AsDes = {'b', 'd', 'f', 'h', 'k', 'l', 't',
                            'g', 'j', 'p', 'q', 'y'}; // letters with ascenders or descenders
    typedef vector<char>::size_type vs_type;
    vs_type sizeAsDes = AsDes.size();

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
    string longestWord;

    while (getline(dictionary, word)) {
        // check whether the word is a palindrome
        bool hasAsDes;

        // Invariant: i refers to the next character
        //            not checked in the vector of ascending and descending letters
        for (int i = 0; i != sizeAsDes; i++) {
            hasAsDes = false;
            if (word.find(AsDes[i]) != string::npos) {
                hasAsDes = true;
                break;
            }
        }

        // store the word without ascenders or descenders into a vector
        if (!hasAsDes) {
            noAsDes.push_back(word);

            // record the longest palindrome
            if (word.size() > maxlen) {
                longestWord = word;
                maxlen = max(maxlen, word.size());
            }

            // print word without ascenders or descenders
            cout << word << endl;
        }

    }

    cout << "The longest word without ascenders or descenders is: " << longestWord << endl;

    dictionary.close();
    return 0;
}
