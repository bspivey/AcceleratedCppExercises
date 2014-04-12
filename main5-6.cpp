#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <deque>
#include "grade.h"
#include "Student_info.h"
#include <sstream>

using std::cin;                 using std::setprecision;
using std::cout;                using std::sort;
using std::domain_error;        using std::streamsize;
using std::endl;                using std::string;
using std::max;                 using std::deque;
using std::ifstream;            using std::istringstream;

// function for parsing  passing and failing students
deque<Student_info> extract_fails(deque<Student_info>& students)
{
    deque<Student_info> fail;
    deque<Student_info>::iterator iter = students.begin();
    int sizeStudents, sizeFail;
    sizeStudents = students.size();

    int i = 0;
    while (i < students.size()) {
        if (fgrade(students[i]))
            fail.push_back(students[i]);
        else {
            students.push_front(students[i]);
            ++i; // increment an extra time after push_front
        }
        ++i;
    }
    sizeFail = fail.size();
    students.resize(sizeStudents - sizeFail);

    return fail;
}

int main()
{
    deque<Student_info> students;
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

    // alphebetize the student records
    sort(students.begin(), students.end(), compare);

    // parse students into two deques of passing and failing students
    deque<Student_info> fStudents;
    fStudents = extract_fails(students);

    // write the passing names and grades
    cout << "*** Passing Students ***" << endl;
    for (deque<Student_info>::iterator it = students.begin(); it != students.end(); it++) {
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
    for (deque<Student_info>::iterator it = fStudents.begin(); it != fStudents.end(); it++) {
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

    studentfile.close();
    return 0;
}
