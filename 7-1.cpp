#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::pair;
using std::sort;

bool firstLess (const pair<string, int>& p1, const pair<string, int>& p2)
{
    return p1.second < p2.second;
}

int main()
{
    string s;
    map<string, int> counters;

    // read the input
    while (cin >> s)
        ++counters[s];

    // sort the words
    vector<pair<string, int> > mapvec(counters.begin(), counters.end());
    sort(mapvec.begin(), mapvec.end(), firstLess);

    // write the words
    for (vector<pair<string, int> >::const_iterator it = mapvec.begin();
        it != mapvec.end(); ++it) {

        cout << it->first << "\t" << it->second << endl;
    }

    return 0;

}
