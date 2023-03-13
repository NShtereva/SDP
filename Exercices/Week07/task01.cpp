#include <iostream>

template <typename T>
struct BTNode
{
    T data;
    BTNode* left;
    BTNode* right;
};

template <typename T>
void inorder(const BTNode<T>* node)
{
    if(!node)
        return;
    
    inorder(node->left);
    std::cout << node->data << " ";
    inorder(node->right);
}

template <typename T>
void preorder(const BTNode<T>* node)
{
    if(!node)
        return;
    
    std::cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

template <typename T>
void postorder(const BTNode<T>* node)
{
    if(!node)
        return;
    
    postorder(node->left);
    postorder(node->right);
    std::cout << node->data << " ";
}

template <typename T>
void deleteTree(BTNode<T>*& root)
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
    BTNode<int>* tree = new BTNode<int>{1,
                                        new BTNode<int>{2,
                                                        new BTNode<int>{4, nullptr, nullptr},
                                                        new BTNode<int>{5, nullptr, nullptr}},
                                        new BTNode<int>{3, nullptr, nullptr}};
    
    std::cout << "Inorder(Left, Root, Right): "; 
    inorder(tree);
    std::cout << std::endl;

    std::cout << "Preorder(Root, Left, Right): "; 
    preorder(tree);
    std::cout << std::endl;

    std::cout << "Postorder(Left, Right, Root): "; 
    postorder(tree);
    std::cout << std::endl;

    deleteTree(tree);
    return 0;
}
