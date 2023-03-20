#include <iostream>

struct Node
{
    int data;
    Node* left;
    Node* right;
};

int maxPath(Node* t)
{
    if(!t)
        return 0;

    if(!t->left && !t->left)
        return t->data;

    int left = 0, right = 0;

    if(t->left && t->left->data > t->data)
    {
        left = t->data + maxPath(t->left);
    }

    if(t->right && t->right->data > t->data)
    {
        right = t->data + maxPath(t->right);
    }

    return std::max(left, right);
}

void deleteTree(Node*& root)
{
    if(!root)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
    root = nullptr;
}

int main()
{
    Node* root = new Node{1,
                          new Node{2,
                                   new Node{3, nullptr, nullptr},
                                   nullptr},
                          new Node{1,
                                   new Node{9, nullptr, nullptr},
                                   new Node{8, nullptr, nullptr}}};                      

    std::cout << maxPath(root) << std::endl;
    deleteTree(root);
    return 0;
}
