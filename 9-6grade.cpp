#include <stdexcept>
#include <vector>
#include "grade.h"
#include "median.h"
#include "Student_info.h"

using std::domain_error;        using std::vector;

double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double>& hw)
{
    if (hw.size() == 0)
        throw domain_error("student has done no homework");
    return grade(midterm, final, median(hw));
}

// Modified for class Student_info Ch. 9
double Student_info::grade() const
{
    return ::grade(midterm, final, homework);
}

double gradePF(double midterm, double final, char& pf)
{
    double final_grade;
    final_grade = 0.33 * midterm + 0.67 * final;

    if (final_grade > 60)
        pf = 'P';
    else
        pf = 'F';

    return final_grade;
}

double Student_info_PF::gradePF()
{
    return ::gradePF(midterm, final, passfail);
}



