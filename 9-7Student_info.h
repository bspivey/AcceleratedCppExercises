#ifndef GUARD_Student_info
#define GUARD_Student_info

// Student_info.h header file
#include <iostream>
#include <string>
#include <vector>
#include "grade.h"

// Created class Student_info Ch. 9
class Student_info {
public:
    Student_info(): midterm(0), final(0) { }
    Student_info(std::istream& is) { read(is); }

    std::string name() const { return n; }
    bool valid() const { return !homework.empty(); }
    std::istream& read(std::istream&);
    double grade() const;
    double grade(double, double, const std::vector<double>&);
private:
    std::string n;
    double midterm, final, finalGrade;
    std::vector<double> homework;

    std::istream& read_hw(std::istream&, std::vector<double>&);
};

bool compare(const Student_info&, const Student_info&);

#endif //GUARD_Student_info
