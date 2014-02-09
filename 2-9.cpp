#include <iostream>

int main()
{
    double num1, num2, prod;

    // ask to enter two numbers
    std::cout << "Please enter two numbers separated by a space: ";

    // read two numbers
    std::cin >> num1;
    std::cin >> num2;

    // calculate and return the product
    prod = num1 * num2;
    std::cout << "The product of the two numbers is: " << prod << " ." << std::endl;

    return 0;

}
