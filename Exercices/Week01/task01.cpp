#include <iostream>

unsigned numberOfDigits(const unsigned& number1, const unsigned& number2)
{
    unsigned long long product = number1 * number2;
    unsigned counter = 0;

    while(product != 0)
    {
        counter++;
        product = product / 10;
    }

    return counter;
}

int main()
{
    unsigned num1, num2;
    std::cin >> num1 >> num2;

    std::cout << std::endl
              << numberOfDigits(num1, num2)
              << std::endl;
    return 0;
}
