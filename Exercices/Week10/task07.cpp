#include <iostream>
#include <vector>
#include <string>

using Type = std::vector<std::string>;

struct Node
{
    std::string data;
    std::vector<Node*> children;

    Node(std::string data) : data(data) 
    { }
};

void find(const Node* root, const std::string& begin, const std::string& end, Type& result)
{
    if(!root)
    {
        return;
    }

    if(root->data == begin)
    {
        for(const Node* child : root->children)
        {
            result.push_back(child->data);

            find(child, child->data, end, result);

            if(result.back() == end)
                return;
            else
                result.pop_back();
        }

        return;
    }

    for(const Node* child : root->children)
    {
        if(child->data == begin)
        {
            find(child, begin, end, result);
        }
    }
}

void printPath(const Node* root, const std::string& begin, const std::string& end)
{
    Type result;

    find(root, begin, end, result);

    if(result.size() == 0)
    {
        std::cout << "Not found!" << std::endl;
        return;
    }

    int size = result.size();

    std::cout << "./";
    for(int i = 0; i < size; i++)
    {
        std::cout << result[i]; 
        std::cout << ((i == size - 1) ? '\n' : '/');
    }
}

void fillInTree(Node*& root)
{
    root = new Node("/");

    root->children.push_back(new Node("bin"));
    root->children[0]->children.push_back(new Node("cp"));
    root->children[0]->children.push_back(new Node("ksh"));
    root->children[0]->children.push_back(new Node("is"));
    root->children[0]->children.push_back(new Node("pwd"));

    root->children.push_back(new Node("dev"));

    root->children.push_back(new Node("etc"));
    root->children[2]->children.push_back(new Node("passwd"));

    root->children.push_back(new Node("home"));
    root->children[3]->children.push_back(new Node("mthomas"));
    root->children[3]->children[0]->children.push_back(new Node("bin"));
    root->children[3]->children[0]->children.push_back(new Node("class_stuff"));
    root->children[3]->children[0]->children[1]->children.push_back(new Node("foo"));
    root->children[3]->children[0]->children[1]->children.push_back(new Node("bar"));
    root->children[3]->children[0]->children.push_back(new Node("profile"));
    root->children[3]->children.push_back(new Node("stul"));

    root->children.push_back(new Node("lib"));

    root->children.push_back(new Node("mnt"));

    root->children.push_back(new Node("proc"));

    root->children.push_back(new Node("root"));

    root->children.push_back(new Node("sbin"));

    root->children.push_back(new Node("tmp"));

    root->children.push_back(new Node("usr"));
    root->children[10]->children.push_back(new Node("bin"));
}

void deleteTree(Node*& root)
{
    for(Node*& child : root->children)
    {
        deleteTree(child);
    }

    delete root;
    root = nullptr;
}

int main()
{
    Node* root = nullptr;
    fillInTree(root);

    printPath(root, "home", "bar");
    printPath(root, "proc", "file");

    deleteTree(root);
    return 0;
}
