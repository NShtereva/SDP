#include <iostream>
#include <queue>
#include <stdexcept>
#include <cassert>

struct BSTNode
{
    int data;
    BSTNode* left;
    BSTNode* right;
};

void inorder(const BSTNode* root, std::queue<int>& q)
{
    if(!root)
        return;

    inorder(root->left, q);
    q.push(root->data);
    inorder(root->right, q);
}

int kthSmallestElement(const BSTNode* root, int k)
{
    if(k < 1 || !root)
        throw std::logic_error("Invalid k or empty tree!");

    std::queue<int> q;
    inorder(root, q);

    if(k > q.size())
        throw std::logic_error("Too large value for k!");   

    while(k > 1)
    {
        q.pop();
        k--;
    }
    
    return q.front();
}

void deleteTree(BSTNode*& root)
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
    BSTNode* tree = new BSTNode{5,
                                new BSTNode{3,
                                            new BSTNode{2,
                                                        new BSTNode{1, nullptr, nullptr},
                                                        nullptr},
                                            new BSTNode{4, nullptr, nullptr}},
                                new BSTNode{6, nullptr, nullptr}};
    
    assert(kthSmallestElement(tree, 1) == 1);
    assert(kthSmallestElement(tree, 2) == 2);
    assert(kthSmallestElement(tree, 3) == 3);
    assert(kthSmallestElement(tree, 4) == 4);
    assert(kthSmallestElement(tree, 5) == 5);
    assert(kthSmallestElement(tree, 6) == 6);

    deleteTree(tree);
    return 0;
}
