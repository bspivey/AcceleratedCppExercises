#ifndef GUARD_Student_info
#define GUARD_Student_info

// Student_info.h header file
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "grade.h"

// Function declarations
bool compare(const Core& c1, const Core& c2);
bool compare_Core_Ptrs(const Ptr<Core> pc1, const Ptr<Core> pc2);

// Handle class for Core and Grad classes
class Student_info {
public:
    Student_info() { }
    Student_info(std::istream& is) { read(is); }

    std::istream& read(std::istream&);
    std::string name() const {
        if (cp) return cp->name();
        else throw std::runtime_error("uninitialized Student");
    }

    double grade() const {
        if (cp) return cp->grade();
        else throw std::runtime_error("uninitialized Student");
    }

    static bool compare(const Student_info& s1,
                        const Student_info& s2) {
        return s1.name() < s2.name();
    }

private:
    Ptr<Core> cp;
};

//bool compare(const Student_info&, const Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif //GUARD_Student_info
