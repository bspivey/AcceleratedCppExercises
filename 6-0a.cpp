#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::string;
using std::exception;

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e);
bool not_url_char(char c);
string::const_iterator url_end(string::const_iterator b, string::const_iterator e);
vector<string> find_urls(const string& s);

string::const_iterator url_beg(string::const_iterator b, string::const_iterator e)
{
    static const string sep ="://";

    typedef string::const_iterator iter;

    // i marks where the separator was found
    iter i = b;

    while ((i = search(i, e, sep.begin(), sep.end())) != e) {

        // make sure the separator isn't at the beginning or end of the line
        if (i != b && i + sep.size() != e) {

            // beg marks the beginning of the protocol-name
            iter beg = i;
            while (beg != b && isalpha(beg[-1]))
                --beg;

            // is there at least one appropriate character before and after the separator
            if (beg != i && !not_url_char(i[sep.size()]))
                return beg;
        }

        // the separator we've found wasn't part of a URL; advance i past this separator
        i += sep.size();
    }
    return e;
}

bool not_url_char(char c)
{
    // characters, in addition to alphanumerics, than can appear in a URL
    static const string url_ch = "~;/?:@=$-_.+!*'(),";

    // see whether c cna appear in a URL and return the negative
    return !(isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}

vector<string> find_urls(const string& s)
{
    vector<string> ret;
    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();

    // look through the entire input
    while (b != e) {

        // look for one or more letters followed by ://
        b = url_beg(b, e);

        // if we found it
        if (b != e) {
            // get the rest of the URL
            iter after = url_end(b, e);
            // remember the URL
            ret.push_back(string(b, after));

            // advance b and check for more URLs on this line
            b = after;
        }
    }
    return ret;
}

int main()
{
    // open the file
    ifstream webURLs;
    try {
        webURLs.open ("webURLs.txt");
    }
    catch (exception& e) {
        cout << "Standard exception: " << e.what() << endl;
    }

    // extract URLS from the file
    vector<string> allURLs;
    string line;

    while(getline(webURLs, line)) {
        vector<string> lineURLs;
        vector<string>::const_iterator beg, end;

        lineURLs = find_urls(line);
        beg = lineURLs.begin();
        end = lineURLs.end();

        copy(lineURLs.begin(), lineURLs.end(), back_inserter(allURLs));
    }

    // print the URLs
    for (vector<string>::size_type i = 0; i != allURLs.size(); ++i) {
        cout << allURLs[i] << endl;
    }


    return 0;
}
