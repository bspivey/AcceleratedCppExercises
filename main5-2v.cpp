#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "grade.h"
#include "Student_info.h"
#include <vector>
#include <sstream>

using std::cin;                 using std::setprecision;
using std::cout;                using std::sort;
using std::domain_error;        using std::streamsize;
using std::endl;                using std::string;
using std::max;                 using std::ifstream;
using std::vector;                using std::istringstream;

// function for parsing  passing and failing students
vector<Student_info> extract_fails(vector<Student_info>& students)
{
    vector<Student_info> fail;
    vector<Student_info>::iterator iter = students.begin();

    while (iter != students.end()) {
        if (fgrade(*iter)) {
            fail.push_back(*iter);
            iter = students.erase(iter);
        } else
            ++iter;
    }
    return fail;
}

int main()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;   // the length of the longest name

    // open the file
    ifstream studentfile;
    studentfile.open ("studentfile.txt");
    if (!studentfile.is_open()) {
        cout << "Student file was not opened succesfully. Program will exit.";
        exit(EXIT_FAILURE);
    }

    // read and storea all the student's data
    // Invariant: students contains all the student records read so far
    //            maxlen contains the length of the longest name in students
    string line;
    while (getline(studentfile, line)) {
        // find length of the longest name
        istringstream iss(line);
        read(iss, record);
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    // alphabetize the student records
    sort(students.begin(), students.end(), compare);

    // parse students into two vectors of passing and failing students
    vector<Student_info> fStudents;
    fStudents = extract_fails(students);

    // write the passing names and grades
    cout << "*** Passing Students ***" << endl;
    for (vector<Student_info>::iterator it = students.begin(); it != students.end(); it++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << it->name << string (maxlen + 1 - it->name.size(), ' ');

        // compute and write the grade
        try {
            double final_grade = grade(*it);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                    << setprecision(prec);
        } catch (domain_error e) {
            cout << e.what();
        }

        cout << endl;
    }


    // write the failing names and grades
    cout << "*** Failing Students ***" << endl;
    for (vector<Student_info>::iterator it = fStudents.begin(); it != fStudents.end(); it++) {
        // write the name, padded on the right to maxlen + 1 characters
        cout << it->name << string (maxlen + 1 - it->name.size(), ' ');

        // compute and write the grade
        try {
            double final_grade = grade(*it);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                    << setprecision(prec);
        } catch (domain_error e) {
            cout << e.what();
        }

        cout << endl;
    }

    return 0;
}
