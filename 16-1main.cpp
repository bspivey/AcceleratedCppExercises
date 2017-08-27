// This was my initial attempt using topics the book covered.
// This code is very close to replicated, but handling the \" terms prevented complete replication
// My second attempt was very near the right answer: to use char instead of string (not displayed)
// The trick to this problem is to assign ASCII codes to a char array for all characters in the source code

#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
int main()
{
    string s[] = {
    "#include <string>",
    "#include <iostream>",
    "using std::cout;",
    "using std::endl;",
    "using std::string;",
    "int main()",
    "{",
    "  string s[] = {",
    "  };",
    "  for (int i=0; i != 8; i++)",
    "      cout << s[i] << endl;",
    "  for (int i=0; i != 17; i++)",
    "      cout << \"\\\"\" + s[i] + \"\\\",\"; << endl;",
    "  for (int i=8; i != 17; i++)",
    "      cout << s[i]; << endl;",
    "  return 0;",
    "}"
    };
    for (int i=0; i != 8; i++)
        cout << s[i] << endl;
    for (int i=0; i != 17; i++)
        cout << "\"" + s[i] + "\"," << endl;
    for (int i=8; i != 17; i++)
        cout << s[i] << endl;

    return 0;
}
