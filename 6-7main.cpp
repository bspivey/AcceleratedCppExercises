#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.h"
#include "Student_info.h"
#include "analysis.h"
#include <sstream>

using std::cin;                 using std::setprecision;
using std::cout;                using std::sort;
using std::domain_error;        using std::streamsize;
using std::endl;                using std::string;
using std::max;                 using std::vector;
using std::ifstream;            using std::istringstream;

int classifyStudents (const string name, vector<Student_info>& groupOne, vector<Student_info>& groupTwo)
{
    // read the students records
    Student_info student;
    while (read(cin, student)) {
        groupOne.push_back(student);
    }

    // classify students
    transform(groupOne.begin(), groupOne.end(), back_inserter(groupTwo), name)

    // verify that the analysis will show us something
    if (groupOne.empty() || groupTwo.empty())
        cout << "All students either meet or fail the criteria!" << endl;
        return 1;
    }

    return 0;
}

int main()
{
    // students who did and didn't do all of their homework
    vector<Student_info> did, didnt, fail;

    int sts;
    sts = classifyStudents(did, didnt);
    if (sts == 1)
        return 1;

    // do the analyses
    write_analysis(cout, "median", analysis, did, didnt);
    write_analysis(cout, "average", analysis, did, didnt);
    write_analysis(cout, "median of homework turned in", analysis, did, didnt);

    return 0;
}
