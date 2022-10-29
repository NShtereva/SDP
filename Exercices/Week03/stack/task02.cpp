#include <iostream>
#include <string>
#include <cassert>

// #include "stack.hpp"
#include "dynamicStack.hpp"
// #include "linkedStack.hpp"

std::string& reverse(std::string& str)
{
    // Stack<char> stack;
    DynamicStack<char> stack;
    // LinkedStack<char> stack;

    size_t size = str.size();
    for(size_t i = 0; i < size; i++)
    {
        stack.push(str[i]);
    }

    for(size_t i = 0; i < size; i++)
    {
        str[i] = stack.top();
        stack.pop();
    }

    return str;
}

int main()
{
    std::string str("Stacks are cool!");
    assert(reverse(str) == "!looc era skcatS");
    return 0;
}
