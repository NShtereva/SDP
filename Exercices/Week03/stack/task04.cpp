#include <iostream>
#include <string>
#include <stack>

void reverseText(std::string& str)
{
    std::stack<std::string> stack;
    int len = str.size(), i = 0;

    while(i < len)
    {
        std::string currWord;
        while(i < len && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
        {
            currWord += str[i];
            i++;
        }

        stack.push(currWord);

        i++;
    }

    str.erase();

    while(!stack.empty())
    {
        str += stack.top();
        stack.pop();
        str += ' ';
    }
}

int main()
{
    std::string str = "Technical Interview Preparation";
    reverseText(str);
    std::cout << str << std::endl;    
    return 0;
}
