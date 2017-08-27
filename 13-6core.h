#ifndef GUARD_Core
#define GUARD_Core

// Core.h header file
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "grade.h"

using std::endl;

class Core {
public:
    friend class Student_info;

    Core(): midterm(0), final(0) { std::cerr << "Core::Core()" << endl; }
    Core(std::istream& is)
    {
        std::cerr << "Core:Core(istream&)" << endl;
        read(is);
    }
    virtual ~Core() { }

    std::string name() const;
    virtual std::istream& read(std::istream&);
    virtual double grade() const;
    virtual std::string letter(double) const;
    virtual bool valid() const { return !homework.empty(); }

protected:
    virtual Core* clone() const { return new Core(*this); }
    std::istream& read_common(std::istream&);
    double midterm, final;
    std::vector<double> homework;

private:
    std::string n;
};


#endif //GUARD_Core
