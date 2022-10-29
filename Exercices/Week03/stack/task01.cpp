#include <iostream>
#include <cstring>
#include <cassert>

// #include "stack.hpp"
#include "dynamicStack.hpp"
// #include "linkedStack.hpp"

bool isOpeningBracket(char c)
{
    return c == '(' || c == '[' || c == '{';
}

bool isClosingBracket(char c)
{
    return c == ')' || c == ']' || c == '}';
}

char getOppositeBracket(char c)
{
    switch(c)
    {
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
    }

    return '\0';
}

bool properlyPlacedBrackets(const char* str)
{
    // Stack<char> stack;
    DynamicStack<char> stack;
    // LinkedStack<char> stack;

    int len = strlen(str);

    for(int i = 0; i < len; i++)
    {
        if(isOpeningBracket(str[i]))
        {
            stack.push(str[i]);
        }
        else if(isClosingBracket(str[i]))
        {
            char top;

            try
            {
                top = stack.top();
            }
            catch(const std::exception& e)
            {
                return false;
            }

            if(str[i] != getOppositeBracket(top))
            {
                return false;
            }

            stack.pop();
        }
    }

    return true;
}

int main()
{
    assert(properlyPlacedBrackets("(3+6) / {54g( p3[jw ][])}") == true);
    assert(properlyPlacedBrackets("{(526)}[91]}") == false);
    return 0;
}
