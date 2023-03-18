#include <vector>

struct Node
{
    int data;
    std::vector<Node*> children;

    Node(int data = 0) : data(data)
    { }
};

bool pathWithSumN(const Node* root, int n)
{
    int sum = n - root->data;

    if(sum == 0)
    {
        return root->children.size() == 0;
    }

    if(sum < 0)
    {
        return false;
    }

    for(const Node* child : root->children)
    {
        if(pathWithSumN(child, sum))
        {
            return true;
        }
    }

    return false;
}
