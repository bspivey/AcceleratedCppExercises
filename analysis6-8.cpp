#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>
#include "Student_info.h"
#include "analysis.h"
#include "grade.h"
#include "median.h"


using std::vector;
using std::domain_error;
using std::cout;
using std::endl;

bool did_all_hw(const Student_info& s)
{
    return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end());
}

void write_analysis(ostream& out, const string& name, double analysis(const string&, const vector<Student_info>&),
                    const vector<Student_info>& did, const vector<Student_info>& didnt)
{
    out << name << ": median(Group 1) = " << analysis(name, did) <<
                   ", median(Group 2) = " << analysis(name, didnt) << endl;
}

double analysis(const string& name, const vector<Student_info>& students)
{
    vector<double> grades;

    if (name == "median")
        transform(students.begin(), students.end(), back_inserter(grades), grade_aux);
    else if (name == "average")
        transform(students.begin(), students.end(), back_inserter(grades), average_grade);
    else
        transform(students.begin(), students.end(), back_inserter(grades), optimistic_median);

    return median(grades);
}

double grade_aux(const Student_info& s)
{
    try {
        return grade(s);
    } catch (domain_error) {
        return grade(s.midterm, s.final, 0);
    }
}

double average_grade(const Student_info& s)
{
    return grade(s.midterm, s.final, average(s.homework));
}

double average(const vector<double>& v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}


double optimistic_median(const Student_info& s)
{
    vector<double> nonzero;
    remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);

    if (nonzero.empty())
        return grade(s.midterm, s.final, 0);
    else
        return grade(s.midterm, s.final, median(nonzero));
}


