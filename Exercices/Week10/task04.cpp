#include <vector>

struct Node
{
    int data;
    std::vector<Node*> children;

    Node(int data = 0) : data(data)
    { }
};

unsigned int numberOfLeaves(const Node* root)
{
    if(root->children.size() == 0)
    {
        return 1;
    }

    unsigned int counter = 0;

    for(const Node* child : root->children)
    {
        counter += numberOfLeaves(child);
    }

    return counter;
}
