#include <iostream>
#include <vector>

using std::vector;              using std::string;
using std::cin;                 using std::istream;
using std::cout;
using std::endl;



istream& wordProcessing (istream& in, vector<string>& wordVector)
{
    if(in) {
        wordVector.clear();

        string word;
        while(in >> word)  // breaks out with end-of-file or non-string
            wordVector.push_back(word);

        in.clear(); // allows program to take input later in the run
    }
}


int main()
{
    cout << "Enter a series of words: " << endl;

    vector<string> userWords;

    wordProcessing(cin, userWords);

    // count the number of words
    int numWords = userWords.size();
    cout << "Vector size = " << numWords << endl;

    // count the occurence of each word
    vector<string> wordList;
    vector<int> wordCount;
    int curCount = 0;
    vector<string>::iterator it;

    for(it = userWords.begin(); it < userWords.end(); it++) {
        // current word
        string curWord = *it;

        // check if first occurence of the word
        bool firstOccurence = true; // default to first occurence
        vector<string>::iterator jt;

        for(jt = wordList.begin(); jt < wordList.end(); jt++) {
            if(curWord == *jt)
                firstOccurence = false;
        }

        // count occurences if a first occurence is found
        if(firstOccurence) {
            wordList.push_back(curWord);
            wordCount.push_back(0);

            // increment the count for curWord if another word matches it
            for(jt = userWords.begin(); jt < userWords.end(); jt++) {
                if(curWord == *jt)
                    wordCount[curCount]++;
            }
            cout << wordList[curCount] << " " << wordCount[curCount] << endl;
            curCount++;
        }

    }


    return 0;
}
