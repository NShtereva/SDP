#include <vector>

struct Node
{
    int data;
    std::vector<Node*> children;

    Node(int data = 0) : data(data)
    { }
};

unsigned int breadth(const Node* root)
{
    unsigned int maxBreadth = 0;

    for(const Node* child : root->children)
    {
        maxBreadth = std::max(maxBreadth, breadth(child));
    }

    return std::max(root->children.size(), maxBreadth);
}
