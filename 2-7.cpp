#include <iostream>

int main()
{
    // Prints integers down from 10 to -5 on the console
    int i = 0;
    // invariant: we have printed i integers with the printed number == i + 10
    while ( i > -16 ) {

        std::cout << i + 10 << std::endl;
        i -= 1;

    }

    return 0;

}
