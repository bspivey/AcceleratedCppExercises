#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.h"
#include "Student_info.h"

using std::cin;                 using std::setprecision;
using std::cout;                using std::sort;
using std::domain_error;        using std::streamsize;
using std::endl;                using std::string;
using std::max;                 using std::vector;

int main()
{
    vector<Student_info_PF> students;
    Student_info_PF record;
    string::size_type maxlen = 0;   // the length of the longest name
    char finalGrade;

    // read and storea all the student's data
    // Invariant: students contains all the student records read so far
    //            maxlen contains the length of the longest name in students
    while (record.read(cin)) { // Modified for class Student_info Ch. 9
        // find length of the longest name
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    // alphebetize the student records
    sort(students.begin(), students.end(), (bool (&)(const Student_info_PF&, const Student_info_PF&))compare);

    // write the names and grades
    for (vector<Student_info_PF>::size_type i = 0; i != students.size(); i++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << students[i].name() << string (maxlen + 1 - students[i].name().size(), ' ');

        // compute and write the grade
        double final_grade = students[i].gradePF();
        if (final_grade > 60)
            finalGrade = 'P';
        else
            finalGrade = 'F';

        cout << finalGrade;
        cout << endl;
    }

    return 0;
}
