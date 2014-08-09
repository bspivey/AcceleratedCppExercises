#include <iostream>
#include <list>

using std::list;
using std::string;
using std::endl;
using std::cout;


class String_list
{
public:
    String_list(list<string>::const_iterator start, list<string>::const_iterator finish) :
        start(start), finish(finish)
        {
            for (list<string>::const_iterator i = start; i != finish ;i++)
                list_o_strings.push_back(*i);
        }
    list<string> list_o_strings;

private:

    list<string>::const_iterator start;
    list<string>::const_iterator finish;
};




int main()
{
    list<string> list_o_teams = {"Falcons","Titans","Texans","Colts"};
    String_list los(list_o_teams.begin(), list_o_teams.end());
    cout << los.list_o_strings.back() << endl;

    return 0;
}
