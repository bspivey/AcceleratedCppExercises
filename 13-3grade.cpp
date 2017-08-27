#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
#include "grade.h"
#include "median.h"
#include "Student_info.h"
#include "core.h"
#include "grad.h"

using std::domain_error;        using std::vector;
using std::min;


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

// Modified for Ch. 13
double Core::grade() const
{
    return ::grade(midterm, final, homework);
}

double Grad::grade() const
{
    return min(Core::grade(), thesis);
}
