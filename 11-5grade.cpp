#include <stdexcept>
#include <vector>
#include "grade.h"
#include "median.h"
#include "Student_info.h"
#include "analysis.h"

using std::domain_error;        using std::vector;
using std::remove_copy;



double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(double midterm, double final, const vector<double>& hw)
{
    if (hw.size() == 0)
        return grade(midterm, final, 0);
    return grade(midterm, final, median(hw));
}

double agrade(double midterm, double final, const vector<double>& hw)
{
    if (hw.size() == 0)
        return grade(midterm, final, 0);
    return grade(midterm, final, average(hw));
}

double ograde(double midterm, double final, const vector<double>& hw)
{
    vector<double> nonzero;
    if (hw.size() == 0)
        return grade(midterm, final, 0);
    remove_copy(hw.begin(), hw.end(), back_inserter(nonzero), 0);
    return grade(midterm, final, median(nonzero));
}


// Modified for class Student_info Ch. 9
double Student_info::grade() const
{
    return ::grade(midterm, final, homework);
}

double Student_info::agrade() const
{
    return ::agrade(midterm, final, homework);
}

double Student_info::ograde() const
{
    return ::ograde(midterm, final, homework);
}

//bool fgrade(const Student_info& s)
//{
//    return grade(s) < 60;
//}
