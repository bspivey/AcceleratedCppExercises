#include <iostream>
#include <string>
#include <fstream>

using std::cout;
using std::string;
using std::ifstream;
using std::cerr;
using std::endl;

string letter_grade(double grade)
{
    // range posts for numeric grades
    static const double numbers[] = {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };

    // names for the letter grades
    static const char* const letters[] = {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };

    // compute the number of grades given the size of the array
    // and the size of a single element
    static const size_t ngrades = sizeof(numbers)/sizeof(*numbers);

    // given a numeric grade, find and return the associated letter grade
    for (size_t i = 0; i < ngrades; ++i) {
        if (grade >= numbers[i])
            return letters[i];
    }

    return "?\?\?";
}

int main(int argc, char **argv)
{
    double bens_grade = 93;
    cout << letter_grade(bens_grade) << endl;

    int fail_count = 0;
    // for each file in the input list
    for (int i = 1; i < argc; ++i) {
        ifstream in (argv[i]);

        // if it exists, write its contents, otherwise generate an error message
        if (in) {
            string s;
            while (getline(in, s))
                cout << s << endl;
        } else {
            cerr << "cannot open file " << argv[i] << endl;
            ++fail_count;
        }
    }
    return fail_count;
}


