// Derived from Ch. 9-0. Uses 9-0 .cpp and .h files for any files
// not updated for Ch. 13.

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.h"
#include "Student_info.h"
#include "core.h"
#include "grad.h"

#include <fstream>

using std::cin;                 using std::setprecision;
using std::cout;                using std::sort;
using std::domain_error;        using std::streamsize;
using std::endl;                using std::string;
using std::max;                 using std::vector;
using std::ifstream;

int main()
{
    Core* p1 = new Core;
    Core* p2 = new Grad;
    Core s1;
    Grad s2;

    p1->grade();
    p1->name();

    p2->grade();
    p2->name();

    s1.grade();
    s1.name();

    s2.grade();
    s2.name();

    return 0;
}
