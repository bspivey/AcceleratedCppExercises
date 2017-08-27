#ifndef GUARD_Grad
#define GUARD_Grad

// Grad.h header file
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "grade.h"
#include "core.h"

using std::endl;

class Grad: public Core {
public:
    Grad(): thesis(0) { std::cerr << "Grad::Grad()" << endl; }
    Grad(std::istream& is)
    {
        std::cerr << "Grad::Grad(istream&)" << endl;
        read(is);
    }

    std::istream& read(std::istream&);
    double grade() const;

protected:
    Grad* clone() const { return new Grad(*this); }
    std::vector<double> homework;

private:
    double thesis;
};

#endif //GUARD_Grad
