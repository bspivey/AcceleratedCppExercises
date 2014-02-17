#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

using std::cin;             using std::sort;
using std::cout;            using std::streamsize;
using std::endl;            using std::string;
using std::setprecision;    using std::vector;

int main()
{
    vector<string> names;
    vector<double> finalGrades;
    typedef vector<double>::size_type sz_vDoub;
    string newName;

    // intro
    cout << "This program calculates the final grade for multiple students." << endl;
    cout << "Enter the first student's name: " << endl;

    //invariant: the length of names vector equals the number of names entered by user
    while(cin >> newName) {
        double midterm, final, x, median, classGrade;
        vector<double> homework;
        typedef vector<double>::size_type vec_sz;
        vec_sz size;

        // store name in a vector
        names.push_back(newName);

        // ask for and read the midterm and final grades
        cout << "Please enter the midterm and final exam grades for " << newName << ": " << endl;;
        cin >> midterm >> final;

        // ask for and read the homework grades
        cout << "Enter all the four homework grades: " << endl;

        // invariant: the iterator is equal to the number of homework grades entered
        for (vec_sz it = 0; it < 4; it++) {
            cin >> x;
            homework.push_back(x);
        }

        // check that the student entered some homework grades
        size = homework.size();
        if (size == 0)
        {
            cout << endl << "You must enter the homework grades. "
                            "Please try again." << endl;
            return 1;
        }

        // sort the grades
        sort (homework.begin(), homework.end());

        // compute the median homework grade
        vec_sz mid = size/2;
        median = size % 2 == 0 ? (homework[mid] + homework[mid-1]) / 2
                               :  homework[mid];

        // compute and write the final grade
        classGrade = 0.2 * midterm + 0.4 * final + 0.4 * median;
        finalGrades.push_back(classGrade);

        // request the next student's grade
        cout << "Enter the next student's name: " << endl;
    }

    sz_vDoub length = finalGrades.size();

    for(int i = 0; i < length; i++) {
        cout << "Student " << names[i] << "   Final Grade " << finalGrades[i] << endl;
    }


    return 0;
}
