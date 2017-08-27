// Derived from Ch. 9-0. Uses 9-0 .cpp and .h files for any files
// not updated for Ch. 13.

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.h"
#include "Student_info.h"

#include <fstream>

using std::cin;                 using std::setprecision;
using std::cout;                using std::sort;
using std::domain_error;        using std::streamsize;
using std::endl;                using std::string;
using std::max;                 using std::vector;
using std::ifstream;

int main()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;   // the length of the longest name

    // read input file (added for 13-1)
    ifstream studentFile("students.txt");

    // read and storea all the student's data
    // Invariant: students contains all the student records read so far
    //            maxlen contains the length of the longest name in students
    while (record.read(studentFile)) { // Modified for class Student_info Ch. 9
        // find length of the longest name
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    cout << "sort function" << endl;
    // alphebetize the student records
    sort(students.begin(), students.end(), Student_info::compare);

    cout << "write loop" << endl;
    // write the names and grades
    for (vector<Student_info>::size_type i = 0; i != students.size(); i++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << students[i].name() << string (maxlen + 1 - students[i].name().size(), ' ');
        string validity = students[i].valid() ? "valid" : "not valid";
        cout << validity << endl;

        // compute and write the grade
        try {
            double final_grade = students[i].grade();
            string letter_grade = students[i].letter(final_grade);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                    << setprecision(prec) << " " << letter_grade << endl;
        } catch (domain_error e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}
