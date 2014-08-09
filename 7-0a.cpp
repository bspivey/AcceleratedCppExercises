#include <iostream>
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;


int main()
{
    string s;
    map<string, int> counters;

    // read the input
    while (cin >> s)
        ++counters[s];

    // write the words
    for (map<string, int>::const_iterator it = counters.begin();
        it != counters.end(); ++it) {

        cout << it->first << "\t" << it->second << endl;
    }

    return 0;

}
