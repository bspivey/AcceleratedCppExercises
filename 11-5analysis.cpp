#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>
//#include <iterator>
#include "Student_info.h"
#include "analysis.h"
#include "grade.h"
#include "median.h"

using std::vector;
using std::domain_error;
using std::cout;
using std::endl;

void write_analysis(ostream& out, const string& name, double analysis(const vector<Student_info>&),
                    const vector<Student_info>& did, const vector<Student_info>& didnt)
{
    cout << name << ": median(did) = " << analysis(did) <<
                   ", median(didnt) = " << analysis(didnt) << endl;
}

double median_analysis(const vector<Student_info>& students)
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), grade_aux);

    return median(grades);
}

double grade_aux(const Student_info& s)
{
        return s.grade();
}

double average_analysis(const vector<Student_info>& students)
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), average_grade);

    return median(grades);
}

double average_grade(const Student_info& s)
{
    return s.agrade();
}

double average(const vector<double>& v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double optimistic_median_analysis(const vector<Student_info>& students)
{
    vector<double> grades;

    transform(students.begin(), students.end(), back_inserter(grades), optimistic_median);

    return median(grades);
}

double optimistic_median(const Student_info& s)
{
    return s.ograde();
}


