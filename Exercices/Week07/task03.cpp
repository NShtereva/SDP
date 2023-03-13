#include <iostream>
#include <vector>
#include <queue>

template <typename T>
struct BTNode
{
    T data;
    BTNode* left;
    BTNode* right;
};

template <typename T>
void printLevels(BTNode<T>* root)
{
    if(!root) 
        return;

    std::queue<BTNode<T>*> q;
    q.push(root);

    std::vector<std::vector<T>> levels;

    while(!q.empty())
    {
        int size = q.size();
        std::vector<T> currLevel;

        for(int i = 0; i < size; i++)
        {
            BTNode<T>* node = q.front();
            q.pop();

            currLevel.push_back(node->data);

            if(node->left)
            {
                q.push(node->left);
            }

            if(node->right)
            {
                q.push(node->right);
            }
        }

        levels.push_back(currLevel);
    }

    int numberOfLevels = levels.size();

    for(int i = 0; i < numberOfLevels; i++)
    {
        int numberOfElements = levels[i].size();
        for(int j = 0; j < numberOfElements; j++)
        {
            std::cout << levels[i][j] << " ";
        }
        std::cout << std::endl;
    }
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
    
    printLevels(tree);
    deleteTree(tree);
    return 0;
}
