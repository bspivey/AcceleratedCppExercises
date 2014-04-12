#include <vector>
#include <iostream>
#include <ios>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;                using std::vector;
using std::endl;                using std::string;



int main()
{
    string phrase = "";
    vector<string> words = {"Let ", "food ", "be ", "thy ", "medicene"};

    phrase = accumulate(words.begin(), words.end(), phrase);

    cout << phrase << endl;


    return 0;
}
