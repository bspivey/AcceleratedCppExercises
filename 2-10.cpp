#include <iostream>

int main()
{

    int k = 0;
    while ( k != 10 ) {
        // 'std' is used to define the namespace to be applied when using 'cout' alone.
        // this using command is only applicable within the while loop scope.
        using std::cout;
        cout << "*";
        ++k;
    }
    // 'std' is used to state the namespace context for cout and endl
    std::cout << std::endl;
    return 0;
}
