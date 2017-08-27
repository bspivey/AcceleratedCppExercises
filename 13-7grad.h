#ifndef GUARD_Grad
#define GUARD_Grad

// Grad.h header file
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "grade.h"
#include "core.h"

using std::endl;
using std::cout;

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
    bool valid() const {
        std::cerr << "thesis: " << thesis << endl;
        std::cerr << "homework: " << homework.size() << endl;
        return (thesis>0 && !homework.empty());
    }

protected:
    Grad* clone() const { return new Grad(*this); }

private:
    double thesis;
};

#endif //GUARD_Grad
