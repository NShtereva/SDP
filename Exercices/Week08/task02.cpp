#include <iostream>
#include <fstream>
#include <stdexcept>

template <typename T>
struct LinkedListNode
{
    T data;
    LinkedListNode* next;
};

template <typename T>
int listLen(LinkedListNode<T>* head)
{
    int len = 0;
    LinkedListNode<T>* temp = head;

    while(temp)
    {
        temp = temp->next;
        len++;
    }

    return len;
}

template <typename T>
void deleteList(LinkedListNode<T>*& head)
{
    while(head)
    {
        LinkedListNode<T>* save = head;
        head = head->next;

        delete save;
        save = nullptr;
    }
}

template <typename T>
struct BSTNode
{
    T data;
    BSTNode* left;
    BSTNode* right;
};

template <typename T>
bool insert(BSTNode<T>*& root, const T& elem)
{
    if(!root)
    {
        root = new BSTNode<T>{elem, nullptr, nullptr};
        return true;
    }

    if(elem == root->data)
    {
        throw std::logic_error("The element has already been added!");
    }

    if(elem < root->data)
    {
        return insert(root->left, elem);
    }

    return insert(root->right, elem);
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

template <typename T>
void listToBST(LinkedListNode<T>* head, BSTNode<T>*& root)
{
    if(!head)
        return;

    int middle = listLen(head) / 2;
    LinkedListNode<T>* middleElem = head;
    LinkedListNode<T>* prev = head;

    if(middle == 0)
    {
        root = new BSTNode<T>{middleElem->data, nullptr, nullptr};
        return;
    }

    int k = middle;

    while(k > 0)
    {   
        prev = middleElem;
        middleElem = middleElem->next;
        k--;
    }

    prev->next = nullptr;

    root = new BSTNode<T>{middleElem->data, nullptr, nullptr};

    LinkedListNode<T>* save = middleElem;
    middleElem = middleElem->next;
    delete save;

    listToBST(head, root->left);
    listToBST(middleElem, root->right);
}

template <typename T>
void DOTprintHelper(const BSTNode<T>* root, std::ostream& out)
{
    if(!root)
        return;

    if(root->left)
    {
        out << root->data << " -> " << root->left->data << " [color = \"red\"];" << std::endl;
        DOTprintHelper(root->left, out);
    }

    if(root->right)
    {
        out << root->data << " -> " << root->right->data << " [color = \"black\"];" << std::endl;
        DOTprintHelper(root->right, out);
    }
}

template <typename T>
void DOTprint(const BSTNode<T>* root, std::ostream& out)
{
    out << "digraph tree {" << std::endl;
    DOTprintHelper(root, out);
    out << "}" << std::endl;
}

int main()
{
    LinkedListNode<int>* list = new LinkedListNode<int>{-10,
                                    new LinkedListNode<int>{-3,
                                        new LinkedListNode<int>{0,
                                            new LinkedListNode<int>{5,
                                                new LinkedListNode<int>{9, nullptr}}}}};

    BSTNode<int>* tree = nullptr;

    listToBST(list, tree);

    std::ofstream file("task02.dot");
    DOTprint(tree, file);
    file.close();

    deleteList(list);
    deleteTree(tree);
    return 0;
}
