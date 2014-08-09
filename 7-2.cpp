#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.h"
#include "Student_info.h"
#include <map>

using std::cin;                 using std::setprecision;
using std::cout;                using std::sort;
using std::domain_error;        using std::streamsize;
using std::endl;                using std::string;
using std::max;                 using std::vector;
using std::bad_function_call;
using std::map;


map<int, char>::const_iterator findLetter(const map<int, char>& gradeMap, int g)
{
    map<int, char>::const_iterator it;
    it = gradeMap.find(g);

    if (it == gradeMap.end())
        g = 0;

    it = gradeMap.find(g);

    if (it == gradeMap.end()) {
        throw bad_function_call();
    }

    return it;
}

int main()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;   // the length of the longest name

    // create map of letter grades
    map<int, char> letterGrades;
    letterGrades[90] = 'A';
    letterGrades[80] = 'B';
    letterGrades[70] = 'C';
    letterGrades[60] = 'D';
    letterGrades[0]  = 'F';

    // read and storea all the student's data
    // Invariant: students contains all the student records read so far
    //            maxlen contains the length of the longest name in students
    while (read(cin, record)) {
        // find length of the longest name
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    // alphebetize the student records
    sort(students.begin(), students.end(), compare);

    // write the names and grades
    for (vector<Student_info>::size_type i = 0; i != students.size(); i++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << students[i].name << string (maxlen + 1 - students[i].name.size(), ' ');

        // compute and write the grade
        try {
            double final_grade = grade(students[i]);

            // find letter grade
            int rounded_grade = floor(final_grade / 10) * 10;
            map<int, char>::const_iterator it = findLetter(letterGrades, rounded_grade);

            streamsize prec = cout.precision();
            cout << setprecision(3) << it->second << ": " << final_grade
                    << setprecision(prec);
        } catch (domain_error e) {
            cout << e.what();
        }

        cout << endl;
    }

    return 0;
}
