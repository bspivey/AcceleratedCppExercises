#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
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

double grade(double midterm, double final)
{
    return 0.5 * midterm + 0.5 * final;
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

double passFail::grade() const
{
    if (homework.size() == 0) {
        return ::grade(midterm, final);
    }
    else {
        return Core::grade();
    }
}

std::string Core::letter(double grade) const
{

    static const double numbers[] = {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };

    static const char* const letters[] = {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
    };

    static const size_t ngrades = sizeof(numbers)/sizeof(*numbers);

    for (size_t i = 0; i < ngrades; i++) {
        if (grade >= numbers[i])
            return letters[i];
    }

    return "?/?/?";
}

std::string passFail::letter(double grade) const
{
    static const double numbers[] = {60, 0};

    static const char* const letters[] = {"P", "F"};

    static const size_t ngrades = sizeof(numbers)/sizeof(*numbers);

    for (size_t i = 0; i < ngrades; i++) {
        if(grade >= numbers[i])
            return letters[i];
    }

    return "?/?/?";
}
