// source file for Student_info-related functions
#include "core.h"
#include "grad.h"
#include "ptr.h"
#include "str.h"
#include "Student_info.h"
#include <memory>
#include <string>

using std::istream;             using std::vector;
using std::cout;                using std::endl;
using std::string;



// Comparison operations
// Had to move these functions from main.cpp to Student_info.cpp
// due to compiler issues. Should be ok to have these two in main.cpp.

bool compare(const Core& c1, const Core& c2)
{
    return c1.name() < c2.name();
}

bool compare_Core_Ptrs(const Ptr<Core> pc1, const Ptr<Core> pc2)
{
    return compare(*pc1, *pc2);
}


istream& Student_info::read(istream& is)
{
    char ch;
    is >> ch;

    // allocate new object of the appropriate type
    // use Ptr<T>(T*) to build a Ptr<Core> from the pointer to that object
    // call Ptr<T>::operator= to assign the Ptr<Core> to the left-hand side
    if (ch == 'U') {
        cp = new Core(is);
    } else {
        cp = new Grad(is);
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
