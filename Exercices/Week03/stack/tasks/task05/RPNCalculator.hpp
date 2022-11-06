#ifndef __RPN_CALCULATOR
#define __RPN_CALCULATOR

#include <stack>
#include <string>

class RPNCalculator
{
    private:
        std::stack<char> operations;
        std::stack<double> result;

        static bool isDigit(char c);
        static bool isOperation(char c);

        static double charToDouble(char digit);
        static unsigned int priority(char c);
        
        static double applyOperation(double left, char op, double right);
        void applyAnOperationToTheResult(char op);

    public:
        std::string toRPN(const std::string& expression);
        double calculateFromRPN(const std::string& rpnExpression);
        double calculate(std::string const& expression); 
};

#endif
