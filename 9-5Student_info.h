#ifndef GUARD_Student_info
#define GUARD_Student_info

// Student_info.h header file
#include <iostream>
#include <string>
#include <vector>
#include "grade.h"

class Student_info_PF {
public:
    Student_info_PF(): midterm(0), final(0) { }
    Student_info_PF(std::istream& is) { read(is); }

    std::string name() const { return n; }
    std::istream& read(std::istream&);
    double gradePF() const;
private:
    std::string n;
    double midterm, final, finalGrade;
    std::vector<double> homework;
};

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
};

bool compare(const Student_info&, const Student_info&);
bool compare(const Student_info_PF&, const Student_info_PF&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif //GUARD_Student_info
