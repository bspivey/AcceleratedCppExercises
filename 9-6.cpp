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

    // sort students by pass fail
    typedef vector<Student_info_PF>::iterator vs_it;
    vector<Student_info_PF> studentsF = students;
    vs_it students_end = remove_if(students.begin(), students.end(), testfail);
    vs_it studentsF_end = remove_if(studentsF.begin(), studentsF.end(), testpass);

    // write the names and grades
    cout << "Passing Students: " << endl;
    for (vector<Student_info_PF>::iterator it = students.begin(); it != students_end; it++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << it->name() << string (maxlen + 1 - it->name().size(), ' ');

        // compute and write the grade
        double final_grade = it->gradePF();

        cout << it->get_passfail() << " " << final_grade;
        cout << endl;
    }

    cout << "Failing Students: " << endl;
    for (vector<Student_info_PF>::iterator it = studentsF.begin(); it != studentsF_end; it++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << it->name() << string (maxlen + 1 - it->name().size(), ' ');

        // compute and write the grade
        double final_grade = it->gradePF();

        cout << it->get_passfail() << " " << final_grade;
        cout << endl;
    }

    return 0;
}
