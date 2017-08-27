#ifndef GUARD_passFail
#define GUARD_passFail

// Core.h header file
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "grade.h"

using std::endl;

class passFail: public Core {
public:
    passFail() { std::cerr << "passFail:passFail()" << endl; }
    passFail(std::istream& is)
    {
        std::cerr << "passFail::passFail(istream&)" << endl;
        read(is);
    }

    double grade() const;
    std::string letter(double) const;
    bool valid() const { return true; }


protected:
    virtual passFail* clone() const { return new passFail(*this); }

};


#endif //GUARD_passFail
