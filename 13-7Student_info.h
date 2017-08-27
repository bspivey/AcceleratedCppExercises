#ifndef GUARD_Student_info
#define GUARD_Student_info

// Student_info.h header file
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <string>
#include "grade.h"
#include "core.h"
#include "grad.h"
#include "passfail.h"
#include "audit.h"

// Handle class for Core, Grad, and passFail classes
class Student_info {
public:
    Student_info(): cp(0) { }
    Student_info(std::istream& is): cp(0) { read(is); }
    Student_info(const Student_info&);
    Student_info& operator=(const Student_info&);
    ~Student_info() { delete cp; }

    std::istream& read(std::istream&);
    std::string name() const {
        if (cp) return cp->name();
        else throw std::runtime_error("uninitialized Student");
    }

    double grade() const {
        if (cp) return cp->grade();
        else throw std::runtime_error("uninitialized Student");
    }

    std::string letter(double g) const { return cp->letter(g); }

    bool valid() const { return cp->valid(); }

    static bool compare(const Student_info& s1,
                        const Student_info& s2) {
        return s1.name() < s2.name();
    }

private:
    Core* cp;
};

std::istream& read_hw(std::istream&, std::vector<double>&);

#endif //GUARD_Student_info
