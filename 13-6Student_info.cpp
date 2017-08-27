// source file for Student_info-related functions
#include "Student_info.h"
#include "core.h"
#include "grad.h"
#include <memory>
#include <string>

using std::istream;             using std::vector;
using std::cout;                using std::endl;
using std::string;


Student_info::Student_info(const Student_info& s): cp(0)
{
    if (s.cp) cp = s.cp->clone();
}

Student_info& Student_info::operator=(const Student_info& s)
{
    if (&s != this) {
        delete cp;
        if (s.cp)
            cp = s.cp->clone();
        else
            cp = 0;
    }
    return *this;
}

istream& Student_info::read(istream& is)
{
    delete cp;

    char ch;
    is >> ch;

    if (ch == 'U') {
        cp = new Core(is);
    } else if (ch == 'G') {
        cp = new Grad(is);
    } else {
        cp = new passFail(is);
    }

    return is;
}

// Modified for Ch. 13
string Core::name() const { return n; }

istream& Core::read(istream& in)
{
    read_common(in);
    read_hw(in, homework);
    return in;
}

istream& Core::read_common(istream& in)
{
    in >> n >> midterm >> final;
    return in;
}

istream& Grad::read(istream& in)
{
    Core::read_common(in);
    in >> thesis;
    read_hw(in, Core::homework);
    return in;
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
