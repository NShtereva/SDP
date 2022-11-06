#include <iostream>
#include <cassert>

#include "RPNCalculator.hpp"

int main()
{
    RPNCalculator calc;
    const double eps = 0.0001;

    assert(calc.toRPN("(1+2)*(3/4-5)") == "12+34/5-*");
    assert(std::abs(calc.calculateFromRPN("12+34/5-*") - (-12.75)) < eps);
    
    assert(calc.toRPN("(1+2)*(3-4/5)") == "12+345/-*");
    assert(std::abs(calc.calculateFromRPN("12+345/-*") - 6.6) < eps);

    assert(std::abs(calc.calculate("(1+2)*(3/4-5)") - (-12.75)) < eps);
    assert(std::abs(calc.calculate("(1+2)*(3-4/5)") - 6.6) < eps);
    return 0;
}
