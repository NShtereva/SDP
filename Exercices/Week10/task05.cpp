#include <vector>

struct Node
{
    int data;
    std::vector<Node*> children;

    Node(int data = 0) : data(data)
    { }
};

bool allNodesEqualSumOfChildren(const Node* root)
{
    if(root->children.size() == 0)
    {
        return true;
    }

    int sum = 0;

    for(const Node* child : root->children)
    {
        sum += child->data;
    }

    if(root->data != sum)
    {
        return false;
    }

    for(const Node* child : root->children)
    {
        if(!allNodesEqualSumOfChildren(child))
        {
            return false;
        }
    }

    return true;
}
