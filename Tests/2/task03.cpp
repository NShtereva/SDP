#include <iostream>
#include <vector>
#include <string>
#include <queue>

using Type = std::vector<std::string>;

struct CharNode
{
    char data;
    CharNode* left;
    CharNode* right;
};

void dfs(CharNode* root, Type& words, std::string& currWord)
{
    if(!root)
        return;

    if(!root->left && !root->right)
    {
        currWord += root->data;
        words.push_back(currWord);
        return;
    }

    std::string copy = currWord;

    if(root->left)
    {
        currWord += root->data;
        dfs(root->left, words, currWord);
    }

    if(root->right)
    {
        copy += root->data;
        dfs(root->right, words, copy);
    }
}

void bfs(CharNode* root, Type& words)
{
    if(!root)
        return;

    std::queue<CharNode*> q;
    q.push(root);

    while(!q.empty())
    {
        std::string currWord;
        int size = q.size();

        for(int i = 0; i < size; i++)
        {
            CharNode* node = q.front();
            currWord += node->data;
            q.pop();

            if(node->left)
                q.push(node->left);

            if(node->right)
                q.push(node->right);
        }

        words.push_back(currWord);
    }
}

std::string mostFrequent(CharNode* root)
{
    std::string word;
    Type words;

    dfs(root, words, word);
    bfs(root, words);

    int maxCount = 0;
    word = "";

    for(std::string w1 : words)
    {
        int count = 0;

        for(std::string w2 : words)
        {
            if(w1 == w2)
                count++;
        }

        if(count > maxCount && word != w1)
        {
            maxCount = count;
            word = w1;
        }
    }

    return word;
}

void deleteTree(CharNode*& root)
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
    CharNode* root = new CharNode{'c',
                                  new CharNode{'a',
                                               new CharNode{'c', nullptr, nullptr},
                                               nullptr},
                                  new CharNode{'a',
                                               new CharNode{'a', nullptr, nullptr},
                                               new CharNode{'c', nullptr, nullptr}}};                      
    
    std::cout << mostFrequent(root) << std::endl;
    deleteTree(root);
    return 0;
}
