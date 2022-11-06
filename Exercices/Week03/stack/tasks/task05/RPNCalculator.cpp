#include "RPNCalculator.hpp"

#include <stdexcept>

bool RPNCalculator::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool RPNCalculator::isOperation(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/'; 
}

double RPNCalculator::charToDouble(char digit)
{
    return digit - '0';
}

unsigned int RPNCalculator::priority(char c)
{
    switch(c)
    {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '(': return 1000;
        default: return 0;
    }

    return 0;
}

double RPNCalculator::applyOperation(double left, char op, double right)
{
    switch(op)
    {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': 
        {
            if(right == 0)
            {
                throw std::logic_error("Attempt to divide by 0!");
            }
            return left / right;
        }
        default: 
            throw std::runtime_error("Invalid operation!");
    }

    return 0;
}

void RPNCalculator::applyAnOperationToTheResult(char op)
{
    double right = this->result.top();
    this->result.pop();

    double left = this->result.top();
    this->result.pop();

    this->result.push(applyOperation(left, op, right));
}

std::string RPNCalculator::toRPN(const std::string& expression)
{
    std::string rpnExpression;

    size_t size = expression.size();
    for(size_t i = 0; i < size; i++)
    {
        if(expression[i] == '(')
        {
            this->operations.push(expression[i]);
        }
        else if(isDigit(expression[i]))
        {
            rpnExpression += expression[i];
        }
        else if(isOperation(expression[i]))
        {
            while(!this->operations.empty() && this->operations.top() != '(' &&
                  priority(this->operations.top()) >= priority(expression[i]))
            {
                rpnExpression += this->operations.top();
                this->operations.pop();
            }

            this->operations.push(expression[i]);
        }
        else if(expression[i] == ')')
        {
            while(this->operations.top() != '(')
            {
                rpnExpression += this->operations.top();
                this->operations.pop();
            }

            this->operations.pop();     // '('
        }
        else
        {
            throw std::runtime_error("Invalid expression!");
        }
    }

    while(!this->operations.empty())
    {
        rpnExpression += this->operations.top();
        this->operations.pop();
    }

    return rpnExpression;
}

double RPNCalculator::calculateFromRPN(const std::string& rpnExpression)
{
    size_t size = rpnExpression.size();
    for(size_t i = 0; i < size; i++)
    {
        if(isDigit(rpnExpression[i]))
        {
            this->result.push(charToDouble(rpnExpression[i]));
        }
        else if(isOperation(rpnExpression[i]))
        {
            this->applyAnOperationToTheResult(rpnExpression[i]);
        }
        else
        {
            throw std::runtime_error("Invalid RPN expression!");
        }
    }

    double result = this->result.top();
    this->result.pop();

    if(!this->result.empty())
    {
        throw std::runtime_error("Invalid expression!");
    }

    return result;
}

double RPNCalculator::calculate(std::string const& expression)
{
    size_t size = expression.size();
    for(size_t i = 0; i < size; i++)
    {
        if(expression[i] == '(')
        {
            this->operations.push(expression[i]);
        }
        else if(isDigit(expression[i]))
        {
            this->result.push(charToDouble(expression[i]));
        }
        else if(isOperation(expression[i]))
        {
            while(!this->operations.empty() && this->operations.top() != '(' &&
                  priority(this->operations.top()) >= priority(expression[i]))
            {
                this->applyAnOperationToTheResult(this->operations.top());
                this->operations.pop();
            }

            this->operations.push(expression[i]);
        }
        else if(expression[i] == ')')
        {
            while(this->operations.top() != '(')
            {
                this->applyAnOperationToTheResult(this->operations.top());
                this->operations.pop();
            }

            this->operations.pop();     // '('
        }
        else
        {
            throw std::runtime_error("Invalid expression!");
        }
    }

    while(!this->operations.empty())
    {
        this->applyAnOperationToTheResult(this->operations.top());
        this->operations.pop();
    }

    double result = this->result.top();
    this->result.pop();

    if(!this->result.empty())
    {
        throw std::runtime_error("Invalid expression!");
    }

    return result;
} 
