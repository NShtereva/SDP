#include <iostream>
#include <stdexcept>
#include <cassert>

template <typename T>
struct BSTNode
{
    T data;
    BSTNode* left;
    BSTNode* right;
};

template <typename T>
bool search(BSTNode<T>* root, const T& elem)
{
    BSTNode<T>* temp = root;

    while(temp && temp->data != elem)
    {
        if(temp->data > elem)
        {
            temp = temp->left;
        }
        else // temp->data < elem
        {
            temp = temp->right;
        }
    }

    if(!temp || temp->data != elem)
        return false;

    return true;
}

template <typename T>
bool searchRec(const BSTNode<T>* root, const T& elem)
{
    if(!root)
    {
        return false;
    }

    if(root->data == elem)
    {
        return true;
    }
    else if(root->data > elem)
    {
        return searchRec(root->left, elem);
    }

    return searchRec(root->right, elem);
}

template <typename T>
void deleteTree(BSTNode<T>*& root)
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
    BSTNode<int>* tree = new BSTNode<int>{5,
                                          new BSTNode<int>{3,
                                                           new BSTNode<int>{2,
                                                                            new BSTNode<int>{1, nullptr, nullptr},
                                                                            nullptr},
                                                           new BSTNode<int>{4, nullptr, nullptr}},
                                          new BSTNode<int>{6, nullptr, nullptr}};

    assert(search(tree, 1));
    assert(search(tree, 2));
    assert(search(tree, 3));
    assert(search(tree, 4));
    assert(search(tree, 5));
    assert(search(tree, 6));
    assert(!search(tree, -9));

    assert(searchRec(tree, 1));
    assert(searchRec(tree, 2));
    assert(searchRec(tree, 3));
    assert(searchRec(tree, 4));
    assert(searchRec(tree, 5));
    assert(searchRec(tree, 6));
    assert(!searchRec(tree, -9));

    deleteTree(tree);
    return 0;
}
