#ifndef GUARD_Audit
#define GUARD_Audit

// audit.h header file
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "grade.h"

using std::endl;

class Audit: public Core {
public:
    friend class Student_info;

    Audit() { std::cerr << "Audit:Audit()" << endl; }
    Audit(std::istream& is)
    {
        std::cerr << "Audit:Audit(istream&)" << endl;
        read(is);
    }
    ~Audit() { }

    std::string name() const;
    std::istream& read(std::istream& in) { in >> n; return in; }

protected:
    Audit* clone() const { return new Audit(*this); }

};



#endif //GUARD_Audit
