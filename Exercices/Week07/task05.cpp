#include <iostream>

struct BTNode
{
    int data;
    BTNode* left;
    BTNode* right;
};

void rightSideView(const BTNode* root)
{
    if(!root)
        return;

    std::cout << root->data << " ";

    if(root->right)
        rightSideView(root->right);
    else
        std::cout << std::endl;
}

void deleteTree(BTNode*& root)
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
    BTNode* tree = new BTNode{1,
                              new BTNode{2,
                                   new BTNode{4, nullptr, nullptr},
                                   new BTNode{5, nullptr, nullptr}},
                              new BTNode{3, nullptr, nullptr}};

    rightSideView(tree);
    deleteTree(tree);
    return 0;
}
