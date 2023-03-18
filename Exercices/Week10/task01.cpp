#include <vector>

struct Node
{
    int data;
    std::vector<Node*> children;

    Node(int data = 0) : data(data)
    { }
};

unsigned int height(const Node* root)
{
    unsigned int maxChildHeight = 0;

    for(const Node* child : root->children)
    {
        maxChildHeight = std::max(maxChildHeight, height(child));
    }

    return 1 + maxChildHeight;
}
