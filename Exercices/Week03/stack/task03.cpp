#include <iostream>
#include <stack>

void sort(std::stack<int>& stack)
{
    if(stack.empty())
    {
        return;
    }

    std::stack<int> helper;

    helper.push(stack.top());
    stack.pop();

    while(!stack.empty())
    {
        int elem1 = stack.top();
        stack.pop();

        int elem2 = helper.top();
        helper.pop();

        if(elem1 > elem2) // '>' -> ascending; '<' -> descending
        {
            stack.push(elem2);

            while(!helper.empty() && helper.top() < elem1) // '<' -> ascending; '>' -> descending
            {
                stack.push(helper.top());
                helper.pop();
            }

            helper.push(elem1);
        }
        else
        {
            helper.push(elem2);
            helper.push(elem1);
        }
    }

    stack = helper;    
}

void print(std::stack<int> stack)
{
    while(!stack.empty())
    {
        std::cout << stack.top() << ' ';
        stack.pop();
    }
    std::cout << std::endl;
}

int main()
{
    std::stack<int> stack;
    stack.push(-9);
    stack.push(3);
    stack.push(7);
    stack.push(0);
    stack.push(-5);

    sort(stack);
    print(stack);

    return 0;
}
