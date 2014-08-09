#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.h"
#include "Student_info.h"
#include <cstring>

using std::cin;                 using std::setprecision;
using std::cout;                using std::sort;
using std::domain_error;        using std::streamsize;
using std::endl;                using std::string;
using std::max;                 using std::vector;


int main()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;   // the length of the longest name

    // letter grade arrays
    static const char* const letters[] = {
        "A+", "A", "A-", "B", "C", "D", "F"
    };
    static const double cutoffs[] = {
        97, 93, 90, 80, 70, 60, 0
    };

    // read and storea all the student's data
    // Invariant: students contains all the student records read so far
    //            maxlen contains the length of the longest name in students
    while (record.read(cin)) { // Modified for class Student_info Ch. 9
        // find length of the longest name
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    // alphebetize the student records
    sort(students.begin(), students.end(), compare);

    // write the names and grades
    for (vector<Student_info>::size_type i = 0; i != students.size(); i++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << students[i].name() << string (maxlen + 1 - students[i].name().size(), ' ');

        // compute and write the grade
        double final_grade = students[i].grade();
        char letter_grade[2];
        static const size_t ngrades = sizeof(cutoffs)/sizeof(*cutoffs);

        for (size_t i = 0; i < ngrades; i++) {
            if (final_grade >= cutoffs[i]) {
                strcpy(letter_grade, letters[i]);
                break;
            }
        }

        streamsize prec = cout.precision();
        cout << setprecision(3) << final_grade
                << setprecision(prec) << " " << letter_grade;

        cout << endl;
    }

    return 0;
}
