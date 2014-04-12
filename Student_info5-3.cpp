// source file for Student_info-related functions
#include "Student_info.h"

using std::istream;             using std::vector;
using std::cout;                using std::endl;

bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

istream& read(istream& is, Student_info& s)
{
    cout << "step0" << endl;
    is >> s.name >> s.midterm >> s.final;
    cout << "step1" << endl;
    read_hw(is, s.homework);
    cout << "step2" << endl;
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
