#include <iostream>

struct BTNode
{
    int data;
    BTNode* left;
    BTNode* right;
};

bool isValidBST(const BTNode* root)
{
    if(!root)
        return true;

    if(root->left && root->left->data >= root->data)
        return false;

    if(root->right && root->right->data < root->data)
        return false;

    return isValidBST(root->left) && isValidBST(root->right);
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
    BTNode* tree1 = new BTNode{1,
                               new BTNode{2,
                                    new BTNode{4, nullptr, nullptr},
                                    new BTNode{5, nullptr, nullptr}},
                               new BTNode{3, nullptr, nullptr}};

    BTNode* tree2 = new BTNode{42,
                               new BTNode{23,
                                    new BTNode{6, nullptr, nullptr},
                                    new BTNode{32, nullptr, nullptr}},
                               new BTNode{78, nullptr, nullptr}};
    
    std::cout << std::boolalpha << isValidBST(tree1) << std::endl;
    std::cout << std::boolalpha << isValidBST(tree2) << std::endl;

    deleteTree(tree1);
    deleteTree(tree2);
    return 0;
}
