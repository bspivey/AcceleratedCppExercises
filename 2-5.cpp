#include <iostream>
#include <string>

using std::cin;     using std::endl;
using std::cout;    using std::string;

void printQuad (const int &nRow, const int &nCol) {
    const string::size_type lengthI = nCol - 2;
    const string inner( lengthI, ' ');
    const string base( nCol, '*' );

    // invariant: we have printed r number of rows
    for ( int r = 0; r < nRow; r++ ) {

        if ( r == 0 || r == nRow - 1 )
            cout << base;
        else
            cout << "*" << inner << "*";

        cout << endl;

    }
}

int main()
{
    // ask the user to choose a shape to be printed
    cout << "Type the number of shape you would like printed." << endl;
    cout << "(1) Square. (2) Rectangle. (3) Triangle : ";

    // read the user's choice
    int shape;
    cin >> shape;

    // print the desired shape
    const int cols = 5;
    int rows;
    if ( shape == 1 )
        rows = cols;
    else
        rows = cols - 2;

    if ( shape == 1 || shape == 2 )
        printQuad(rows, cols);
    else {
        // invariant: we have printed r number of rows
        for ( int r = 0; r < rows; r++ ) {

            // build outer whitespace
            string::size_type lengthO = rows - r - 1;
            string outer( lengthO,' ' );

            // build inner whitespace
            int lengthIint = 2 * r - 1;
            if ( lengthIint < 0 )
                lengthIint = 0;
            string::size_type lengthI = lengthIint;
            string inner( lengthI, ' ' );

            // print row r
            if ( r == rows - 1 ) {
                string base( cols, '*' );
                cout << base;
            }
            else if ( r == 0 )
                cout << outer << "*" << outer;
            else
                cout << outer << "*" << inner << "*" << outer;

            cout << endl;

        }
    }

    return 0;

}
