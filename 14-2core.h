#ifndef GUARD_Core
#define GUARD_Core

// Core.h header file
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::istream;
using std::string;
using std::vector;

class Core {
public:
    //friend class Ptr;

    Core(): midterm(0), final(0) { }
    Core(std::istream& is) { read(is); }
    virtual ~Core() { }

    std::string name() const;
    virtual std::istream& read(std::istream&);
    virtual double grade() const;

protected:
    virtual Core* clone() const { return new Core(*this); }
    std::istream& read_common(std::istream&);
    double midterm, final;
    std::vector<double> homework;

private:
    std::string n;
};


#endif //GUARD_Core
