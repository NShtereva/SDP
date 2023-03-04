#include <iostream>
#include <cassert>
#include <stack>

template <class T>
struct Node 
{
    T data; 
    Node<T> *next;
};

template <class T>
void equalize(Node<T>* ptr)
{
    Node<T>* temp = ptr;

    while(temp)
    {
        Node<T>* helper = temp->next;
        while(helper)
        {
            int tempSize = temp->data.size();
            int helperSize = helper->data.size();

            int diff = std::abs(tempSize - helperSize);
            if(diff > 1)
            {
                Node<T>* smallerStack = nullptr;
                Node<T>* largerStack = nullptr;

                if(temp->data.size() > helper->data.size())
                {
                    smallerStack = helper;
                    largerStack = temp;
                }
                else
                {
                    smallerStack = temp;
                    largerStack = helper;
                }

                while(diff > 1)
                {
                    smallerStack->data.push(largerStack->data.top());
                    largerStack->data.pop();
                    
                    tempSize = temp->data.size();
                    helperSize = helper->data.size();
            
                    diff = std::abs(tempSize - helperSize);
                }
            }
            helper = helper->next;
        }
        temp = temp->next;
    }
}

template <class T>
void check(Node<T>* ptr)
{
    Node<T>* temp = ptr;

    while(temp)
    {
        Node<T>* helper = temp->next;
        while(helper)
        {
            int tempSize = temp->data.size();
            int helperSize = helper->data.size();
            int diff = std::abs(tempSize - helperSize);

            assert(diff <= 1);

            helper = helper->next;
        }
        temp = temp->next;
    }
}

template <typename T>
void deallocate(Node<T>*& ptr)
{
    while(ptr)
    {
        Node<T>* save = ptr;
        ptr = ptr->next;
        delete save;
    }                      
}

int main()
{
    std::stack<int> s1;
    for(int i : {5,4,3,2,1})
    {
        s1.push(i);
    }

    std::stack<int> s2;
    for(int i : {7,6})
    {
        s2.push(i);
    }

    std::stack<int> s3;
    for(int i : {11,10,9,8})
    {
        s3.push(i);
    }
    
    std::stack<int> s4;
    s4.push(12);

    Node<std::stack<int>>* L = new Node<std::stack<int>>{s1, 
                                    new Node<std::stack<int>>{s2,
                                        new Node<std::stack<int>>{s3, 
                                            new Node<std::stack<int>>{s4, nullptr}}}};

    equalize(L);
    check(L);
    
    deallocate(L); 
    return 0;
}
