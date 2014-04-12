#ifndef GUARD_analysis_h

// analysis.h
#include <vector>
#include <iostream>
#include <string>
#include "Student_info.h"

using std::ostream;
using std::string;
using std::vector;

bool did_all_hw(const Student_info&);

void write_analysis(ostream&, const string&, double analysis(const vector<Student_info>&),
                    const vector<Student_info>&, const vector<Student_info>&);

double median_analysis(const vector<Student_info>&);
double grade_aux(const Student_info&);

double average_analysis(const vector<Student_info>&);
double average_grade(const Student_info&);
double average(const vector<double>&);

double optimistic_median_analysis(const vector<Student_info>&);
double optimistic_median(const Student_info&);

#endif // GUARD_analysis_h
