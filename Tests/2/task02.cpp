#include <iostream>
#include <vector>
#include <queue>

using Type = std::vector<int>;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

void deleteTree(Node*& root)
{
    if(!root)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
    root = nullptr;
}

std::vector<Type> bfs(Node* root)
{
    if(!root)
        return std::vector<Type>();

    std::vector<Type> result;

    std::queue<Node*> q;
    q.push(root);

    while(!q.empty())
    {
        Type level;
        int levelSize = q.size();

        for(int i = 0; i < levelSize; i++)
        {
            Node* curr = q.front();
            level.push_back(curr->data);
            q.pop();

            if(curr->left) 
                q.push(curr->left);

            if(curr->right) 
                q.push(curr->right);
        }

        result.push_back(level);
    }
    return result;
}

Type average(Node* root)
{
    std::vector<Type> levels = bfs(root);
    Type result;

    int numberOfLevels = levels.size();

    for(int i = 0; i < numberOfLevels; i++)
    {
        int size = levels[i].size(), sum = 0;
        for(int j = 0; j < size; j++)
        {
            sum += levels[i][j];
        }
        result.push_back(sum / size);
    }

    return result;
}

void print(const Type& arr)
{
    int size = arr.size();

    std::cout << '{';
    for(int i = 0; i < size; i++)
    {
        std::cout << arr[i];

        if(i != size - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "}\n";
}

int main()
{
    Node* root = new Node{1,
                          new Node{2,
                                   nullptr,
                                   new Node{5, nullptr, nullptr}},
                          new Node{5, nullptr, nullptr}};

    Type avg = average(root);
    print(avg);    

    deleteTree(root);
    return 0;
}
