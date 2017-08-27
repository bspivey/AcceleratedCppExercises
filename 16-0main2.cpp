#include <iomanip>
#include <ios>
#include <stdexcept>
#include <string>
#include "grad.h"
#include "str.h"
#include "ptr.h"
#include "Student_info.h"

using std::istream;
using std::ostream;
using std::back_inserter;
using std::copy;
using std::strlen;
using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::setprecision;
using std::domain_error;

int main()
{
    vector< Ptr<Core> > students;
    Ptr<Core> record;
    char ch;
    string::size_type maxlen = 0;

    // read and store the data
    while (cin >> ch) {
        if (ch == 'U')
            record = new Core;
        else
            record = new Grad;

        record->read(cin); // Ptr<T>::-> then virtual call to read
        maxlen = max(maxlen, record->name().size());
        students.push_back(record);
    }

    // compare must be rewritten to work on const Ptr<Cor>&
    sort(students.begin(), students.end(), compare_Core_Ptrs);

    // write the names and grades
    for (vector< Ptr<Core> >::size_type i = 0; i != students.size(); ++i) {
        // students[i] is a Ptr, which we derefence to call the functions
        cout << students[i]->name()
             << string(maxlen + 1 - students[i]->name().size(), ' ');
        try {
            double final_grade = students[i]->grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        } catch (domain_error e) {
            cout << e.what() << endl;
        }
        // no delete statement
    }


    return 0;
}
