#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <list>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::istream;
using std::domain_error;
using std::logic_error;
using std::list;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

bool bracketed(const string& s)
{
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

int nrand(int n)
{
    if (n <= 0 || n > RAND_MAX)
        throw domain_error("Argument to nrand is out of range");

    const int bucket_size = RAND_MAX / n;
    int r;

    do r = rand() / bucket_size;
    while (r >= n);

    return r;
}

template <class In>
In gen_aux(const Grammar& g, const string& word, In begin)
{
    if (!bracketed(word)) {
        *begin++ = word;
        cout << *begin << endl;
    } else {
        // locate the rule that corresponds to the word
        Grammar::const_iterator it = g.find(word);
        if (it == g.end())
            throw logic_error("empty rule");

        // fetch the set of possible rules
        const Rule_collection& c = it->second;

        // from which we select one at random
        const Rule& r = c[nrand(c.size())];

        // recursively expand the selected rule
        for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
            gen_aux(g, *i, begin);
    }
    return begin;
}

template <class In>
In gen_sentence(const Grammar& g, In begin)
{
    In end = gen_aux(g, "<sentence>", begin);
    return end;
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

Grammar read_grammar(istream& in)
{
    Grammar ret;
    string line;

    // read the input
    while (getline(in, line)) {

        // split the input into words
        vector<string> entry = split(line);

        if (!entry.empty())
            // use the category to store the associated rule
            ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end() ));
    }
    return ret;
}

int main()
{
    // generate the sentence
    list<string> sentence;
    list<string>::iterator end = gen_sentence(read_grammar(cin),sentence.begin());

    // write the first word, if any
    list<string>::const_iterator it = sentence.begin();
    if (!sentence.empty()) {
        cout << *it;
        ++it;
    }

    // write the rest of the words, each preceded by a space
    while (it != sentence.end()) {
        cout << " " << *it;
        ++it;
    }

    cout << endl;
    return 0;
}
