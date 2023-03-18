#include <iostream>
#include <vector>

struct Node
{
    int data;
    std::vector<Node*> children;

    Node(int data = 0) : data(data)
    { }
};

void printLevel(const Node* root, unsigned int n)
{
    if(n == 0)
    {
        std::cout << root->data << ' ';
        return;
    }

    for(const Node* child : root->children)
    {
        printLevel(child, n - 1);
    }
}
