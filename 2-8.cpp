#include <iostream>

int main()
{
    int product = 1;

    // invariant: we have assigned product equal to every number between 1 and i
    for ( int i = 1; i < 10; i++) {

        product *= i;

    }

    std::cout << product;

    return 0;

}
