#ifndef GUARD_Student_info
#define GUARD_Student_info

// Student_info.h header file
#include <iostream>
#include <string>
#include <vector>
#include "grade.h"
#include <algorithm>

using std::find;
using std::cout;
using std::endl;

// Created class Student_info Ch. 9
class Student_info {
public:
    Student_info(): midterm(0), final(0) { cout << "Default constructor" << endl; }
    Student_info(std::istream& is) { read(is); cout << "Read constructor" << endl; }
    Student_info(const Student_info& s) {
        n = s.n; midterm = s.midterm; final = s.final; homework = s.homework;
        cout << "Copy constructor" << endl;
    }

    std::string name() const { return n; }
    bool valid() const { return !homework.empty(); }
    std::istream& read(std::istream&);
    double grade() const;
    double agrade() const;
    double ograde() const;
    bool did_all_hw(){ return ((find(homework.begin(), homework.end(), 0)) == homework.end()); }
private:
    std::string n;
    double midterm, final;
    std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif //GUARD_Student_info
