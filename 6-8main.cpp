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

int classifyStudents (vector<Student_info>& groupOne, vector<Student_info>& groupTwo, bool predicate(const Student_info&))
{
    // read the students records
    Student_info student;
    while (read(cin, student)) {
        groupOne.push_back(student);
    }

    // classify students
    vector<Student_info>::iterator iter;
    iter = stable_partition(groupOne.begin(), groupOne.end(), predicate);
    copy(iter, groupOne.end(), back_inserter(groupTwo));
    groupOne.erase(iter, groupOne.end());

    // verify that the analysis will show us something
    if (groupOne.empty() || groupTwo.empty()) {
        cout << "All students either meet or fail the criteria!" << endl;
        return 1;
    }

    return 0;
}

int main()
{
    // students who did and didn't do all of their homework
    vector<Student_info> groupOne, groupTwo;
    int sts;

    // request user to choose classification approach
    cout << "Choose how to classify students: " << endl;
    cout << "  Enter 1 for pass/fail" << endl;
    cout << "  Enter 2 for did homework" << endl;

    int choice;
    cin >> choice;

    if (choice == 1)
        sts = classifyStudents(groupOne, groupTwo, pgrade);
    else if (choice == 2)
        sts = classifyStudents(groupOne, groupTwo, did_all_hw);
    else {
        cout << "You entered an invalid choice. Good-bye." << endl;
        exit(EXIT_FAILURE);
    }

    if (sts == 1)
        return 1;

    // do the analyses
    write_analysis(cout, "median", analysis, groupOne, groupTwo);
    write_analysis(cout, "average", analysis, groupOne, groupTwo);
    write_analysis(cout, "median of homework turned in", analysis, groupOne, groupTwo);

    return 0;
}
