// source file for Student_info-related functions
#include "Student_info.h"
#include <vector>
#include "grade.h"

using std::istream;             using std::vector;
using std::cout;                using std::endl;

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

istream& read(istream& is, Student_info& s)
{
    double midterm, final;
    vector<double> homework;

        cout << "step0" << endl;
        is >> s.name >> midterm >> final;

     if (is) {
        cout << "step1" << endl;
        read_hw(is, homework);
        cout << "step2" << endl;
        s.final_grade = grade(midterm, final, homework);

        is.clear();
    }
    return is;
}

istream& read_hw(istream& in, vector<double>& hw)
{
    if (in) {
        // get rid of previous contents
        hw.clear();

        // read homework grades
        double x;
        while (in >> x)
            hw.push_back(x);

        // clear the stream so that input will work for the next student
        in.clear();
    }
    return in;
}
