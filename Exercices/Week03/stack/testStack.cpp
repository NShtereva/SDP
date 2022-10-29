#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/doctest.h"

#include "stack.hpp"
#include "dynamicStack.hpp"
#include "linkedStack.hpp"

TYPE_TO_STRING(Stack<int>);
TYPE_TO_STRING(DynamicStack<int>);
TYPE_TO_STRING(LinkedStack<int>);

TEST_CASE_TEMPLATE("Test default constructor", 
                   TestStack, Stack<int>, DynamicStack<int>, LinkedStack<int>)
{
    TestStack s;
    REQUIRE(s.empty());
}

TEST_CASE_TEMPLATE("Test push",
                    TestStack, Stack<int>, DynamicStack<int>, LinkedStack<int>) {
    TestStack s;
    s.push(10);

    REQUIRE(!s.empty());
    REQUIRE(s.top() == 10);
}

TEST_CASE_TEMPLATE("Test pop",
                    TestStack, Stack<int>, DynamicStack<int>, LinkedStack<int>/**/) {
    TestStack s;
    s.push(1); 
    s.push(2); 
    s.push(3);
    
    REQUIRE(!s.empty());
    REQUIRE(s.top() == 3);
    s.pop();
    REQUIRE(s.top() == 2);
    s.pop();
    REQUIRE(s.top() == 1);
    s.pop();
    REQUIRE(s.empty());
}
