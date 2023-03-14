#ifndef __BST_HPP
#define __BST_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class BST
{
    private:
        struct Node
        {
            T data;
            Node* left;
            Node* right;
        };

        Node* root;

        void copy(const BST& other);
        void eraseAll(Node*& root);

        bool eraseHelper(const T& elem, Node*& root);

        bool insertHelper(Node*& root, const T& elem); 

        Node* minHelper(Node* root) const;
        Node* maxHelper(Node* root) const;

        bool isValidBSTHelper(const Node* root) const;

        void printHelper(const Node* root, std::ostream& out = std::cout) const;
        void DOTprintHelper(const Node* root, std::ostream& out = std::cout) const;
        
    public:
        BST();
        BST(const BST& other);
        BST(BST&& other);
        ~BST();

        BST& operator = (const BST& other);

        bool insert(const T& elem);
        bool erase(const T& elem);

        T min() const;
        T max() const;

        bool isValidBST() const;

        void print(std::ostream& out = std::cout) const;
        void DOTprint(std::ostream& out = std::cout) const;
};

template <typename T>
BST<T>::BST() : root(nullptr)
{ }

template <typename T>
BST<T>::BST(const BST<T>& other)
{
    this->copy(other);
}

template <typename T>
BST<T>::BST(BST<T>&& other) : root(other.root)
{
    other.root = nullptr;
}

template <typename T>
BST<T>::~BST()
{
    this->eraseAll(this->root);
}

template <typename T>
BST<T>& BST<T>::operator = (const BST<T>& other)
{
    if(this != &other)
    {
        this->eraseAll(this->root);
        this->copy(other);
    }
    return *this;
}

template <typename T>
void BST<T>::copy(const BST& other)
{
    if(!other.root)
        return;

    this->root = new Node{other.root, nullptr, nullptr};

    this->copy(*other.root->left);
    this->copy(*other.root->right);
}

template <typename T>
void BST<T>::eraseAll(Node*& root)
{
    if(!root)
        return;
    
    this->eraseAll(root->left);
    this->eraseAll(root->right);

    delete root;
    root = nullptr;
}

template <typename T>
bool BST<T>::insertHelper(Node*& root, const T& elem)
{
    if(!root)
    {
        root = new Node{elem, nullptr, nullptr};
        return true;
    }

    if(elem == root->data)
    {
        throw std::logic_error("The element has already been added!");
    }

    if(elem < root->data)
    {
        return this->insertHelper(root->left, elem);
    }

    return this->insertHelper(root->right, elem);
}

template <typename T>
bool BST<T>::insert(const T& elem)
{
    return this->insertHelper(this->root, elem);
}

template <typename T>
bool BST<T>::eraseHelper(const T& elem, Node*& root)
{
    if(!root)
    {
        return false;
    }

    if(elem == root->data)
    {
        if(!root->left && !root->right)
        {
            delete root;
            root = nullptr;
        }
        else if(root->left && !root->right)
        {
            Node* save = root;
            root = root->left;

            delete save;
            save = nullptr;
        }
        else if(!root->left && root->right)
        {
            Node* save = root;
            root = root->right;
            
            delete save;
            save = nullptr;
        }
        else // root->left && root->right
        {
            Node* min = this->minHelper(root->right);
            std::swap(root->data, min->data);
            this->eraseHelper(elem, min);
        }

        return true;
    }
    else if(elem < root->data)
    {
        return this->eraseHelper(elem, root->left);
    }

    // elem > root->data
    return this->eraseHelper(elem, root->right);
}

template <typename T>
bool BST<T>::erase(const T& elem)
{
    return this->eraseHelper(elem, this->root);
}

template <typename T>
typename  BST<T>::Node* BST<T>::minHelper(Node* root) const
{
    while(root->left)
    {
        return this->minHelper(root->left);
    }

    return root;
}

template <typename T>
T BST<T>::min() const
{
    if(!this->root)
    {
        throw std::logic_error("Empty tree!");
    }

    return this->minHelper(this->root)->data;
}

template <typename T>
typename  BST<T>::Node* BST<T>::maxHelper(Node* root) const
{
    while(root->right)
    {
        return this->maxHelper(root->right);
    }

    return root;
}

template <typename T>
T BST<T>::max() const
{
    if(!this->root)
    {
        throw std::logic_error("Empty tree!");
    }

    return this->maxHelper(this->root)->data;
}

template <typename T>
bool BST<T>::isValidBSTHelper(const Node* root) const
{
    if(!root)
        return true;

    if(root->left && root->left->data >= root->data)
        return false;

    if(root->right && root->right->data < root->data)
        return false;

    return this->isValidBSTHelper(root->left) && this->isValidBSTHelper(root->right);
}

template <typename T>
bool BST<T>::isValidBST() const
{
    return this->isValidBSTHelper(this->root);
}

template <typename T>
void BST<T>::printHelper(const Node* root, std::ostream& out) const
{
    if(!root)
    {
        out << "()";
        return;
    }

    out << '(' << root->data << ' ';
    this->printHelper(root->left, out);
    out << ' ';
    this->printHelper(root->right, out);
    out << ')';
}

template <typename T>
void BST<T>::print(std::ostream& out) const
{
    this->printHelper(this->root, out);
}

template <typename T>
void BST<T>::DOTprintHelper(const Node* root, std::ostream& out) const
{
    if(!root)
        return;

    if(root->left)
    {
        out << root->data << " -> " << root->left->data << " [color = \"red\"];" << std::endl;
        this->DOTprintHelper(root->left, out);
    }

    if(root->right)
    {
        out << root->data << " -> " << root->right->data << " [color = \"black\"];" << std::endl;
        this->DOTprintHelper(root->right, out);
    }
}

template <typename T>
void BST<T>::DOTprint(std::ostream& out) const
{
    out << "digraph tree {" << std::endl;
    this->DOTprintHelper(this->root, out);
    out << "}" << std::endl;
}

#endif
