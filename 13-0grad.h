#ifndef GUARD_Grad
#define GUARD_Grad

// Grad.h header file
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "grade.h"
#include "core.h"

class Grad: public Core {
public:
    Grad(): thesis(0) { }
    Grad(std::istream& is) { read(is); }

    std::istream& read(std::istream&);
    double grade() const;

protected:
    Grad* clone() const { return new Grad(*this); }
    std::vector<double> homework;

private:
    double thesis;
};

#endif //GUARD_Grad
