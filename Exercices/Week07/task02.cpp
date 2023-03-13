#include <iostream>
#include <stack>

template <typename T>
struct BTNode
{
    T data;
    BTNode* left;
    BTNode* right;
};

template <typename T>
void printPathsHelper(const BTNode<T>* root, std::stack<T>& st)
{
    if(!root->left && !root->right)
    {
        std::stack<T> helper;

        while(!st.empty())
        {
            helper.push(st.top());
            st.pop();
        }
        
        while(!helper.empty())
        {
            std::cout << helper.top() << " ";
            st.push(helper.top());
            helper.pop();
        }

        st.pop();
        std::cout << std::endl;

        return;
    }
    
    if(root->left)
    {
        st.push(root->left->data);
        printPathsHelper(root->left, st);
    }

    if(root->right)
    {
        st.push(root->right->data);
        printPathsHelper(root->right, st);
    }

    st.pop();
}

template <typename T>
void printPaths(const BTNode<T>* root)
{
    if(!root) return;

    if(!root->left && !root->right)
    {
        std::cout << root->data << "\n";
        return;
    }

    std::stack<T> st;
    st.push(root->data);
    printPathsHelper(root, st);
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

    printPaths(tree);
    deleteTree(tree);
    return 0;
}
