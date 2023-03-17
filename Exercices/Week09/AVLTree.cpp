#include "AVLTree.hpp"

#include <stdexcept>

AVLTree::AVLTree() : root(nullptr)
{ }

AVLTree::AVLTree(const AVLTree& other)
{
    this->copy(other.root);
}

AVLTree::~AVLTree()
{
    this->eraseAll(this->root);
}

AVLTree& AVLTree::operator = (const AVLTree& other)
{
    if(this != &other)
    {
        this->eraseAll(this->root);
        this->copy(other.root);
    }
    return *this;
}

void AVLTree::copy(const Node* otherRoot)
{
    if(!otherRoot)
        return;

    this->root = new Node{otherRoot->data, 
                          nullptr, 
                          nullptr, 
                          otherRoot->balanceFactor};

    this->copy(otherRoot->left);
    this->copy(otherRoot->right);
}

void AVLTree::eraseAll(Node*& root)
{
    if(!root)
        return;
    
    this->eraseAll(root->left);
    this->eraseAll(root->right);

    delete root;
    root = nullptr;
}

void AVLTree::getParent(Node* child, Node*& parent)
{
    while(parent != child)
    {
        if(parent->data < child->data)
        {
            if(parent->right == child)
                return;

            parent = parent->right;
        }

        if(parent->data > child->data)
        {
            if(parent->left == child)
                return;

            parent = parent->right;
        }
    }
}

void AVLTree::leftRotation(Node*& root)
{
    Node* leftGrandChild = root->right->left;

    root->right->left = root;
    root = root->right;
    root->left->right = leftGrandChild;

    if(root->left)
        root->left->balanceFactor = this->heightHelper(root->left->right) - this->heightHelper(root->left->left);

    if(root->right)
        root->right->balanceFactor = this->heightHelper(root->right->right) - this->heightHelper(root->right->left);

    root->balanceFactor = this->heightHelper(root->right) - this->heightHelper(root->left);
}

void AVLTree::rightRotation(Node*& root)
{
    Node* rightGrandChild = root->left->right;

    root->left->right = root;
    root = root->left;
    root->right->left = rightGrandChild;

    if(root->left)
        root->left->balanceFactor = this->heightHelper(root->left->right) - this->heightHelper(root->left->left);

    if(root->right)
        root->right->balanceFactor = this->heightHelper(root->right->right) - this->heightHelper(root->right->left);

    root->balanceFactor = this->heightHelper(root->right) - this->heightHelper(root->left);
}

void AVLTree::rebalance(Node*& root)
{
    if(root->balanceFactor > 0)
    {
        if(root->right->balanceFactor < 0)
        {
            this->rightRotation(root->right);
            this->leftRotation(root);
        }
        else
        {
            this->leftRotation(root);
        }
    }
    else if(root->balanceFactor < 0)
    {
        if(root->left->balanceFactor > 0)
        {
            this->leftRotation(root->left);
            this->rightRotation(root);
        }
        else
        {
            this->rightRotation(root);
        }
    }
}

void AVLTree::updateBalance(Node*& node)
{
    while(node)
    {
        if(node->balanceFactor < -1 || node->balanceFactor > 1)
        {
            this->rebalance(node);
        }

        Node* parent = this->root;
        this->getParent(node, parent);

        if(parent == node)
        {
            break;
        }

        node = parent;
    }
}

AVLTree::Node* AVLTree::insertHelper(Node*& root, int elem)
{
    if(!root)
    {
        root = new Node{elem, nullptr, nullptr, 0};
        return root;
    }

    if(root->data == elem)
    {
        throw std::logic_error("The element has already been added!");
    }

    if(root->data > elem)
    {
        root->balanceFactor--;
        return this->insertHelper(root->left, elem);
    }

    root->balanceFactor++;
    return this->insertHelper(root->right, elem);
}

void AVLTree::insert(const int& elem)
{
    Node* newNode = this->insertHelper(this->root, elem);
    this->updateBalance(newNode);  
}

bool AVLTree::eraseHelper(Node*& root, int elem, Node* parent)
{
    if(!root)
    {
        return false;
    }

    if(root->data == elem)
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
            return this->eraseHelper(min, elem, parent);
        }

        return true;
    }
    else if(elem < root->data)
    {
        return this->eraseHelper(root->left, elem, root);
    }

    // elem > root->data
    return this->eraseHelper(root->right, elem, root);
}

void AVLTree::erase(const int& elem)
{
    Node* parent = this->root;
    this->eraseHelper(this->root, elem, parent);
    this->updateBalance(parent);
}

AVLTree::Node* AVLTree::minHelper(Node* root) const
{
    while(root->left)
    {
        return this->minHelper(root->left);
    }

    return root;
}

int AVLTree::min() const
{
    if(!this->root)
    {
        throw std::logic_error("Empty tree!");
    }

    return this->minHelper(this->root)->data;
}

AVLTree::Node* AVLTree::maxHelper(Node* root) const
{
    while(root->right)
    {
        return this->maxHelper(root->right);
    }

    return root;
}

int AVLTree::max() const
{
    if(!this->root)
    {
        throw std::logic_error("Empty tree!");
    }

    return this->maxHelper(this->root)->data;
}

int AVLTree::heightHelper(const Node* root) const
{
    if(!root)
        return -1;

    return 1 + std::max(this->heightHelper(root->left), this->heightHelper(root->right));
}

int AVLTree::height() const
{
    return this->heightHelper(this->root);
}

bool AVLTree::member(const int& elem) const
{
    Node* temp = this->root;

    while(temp && temp->data != elem)
    {
        if(temp->data > elem)
        {
            temp = temp->left;
        }
        else // temp->data < elem
        {
            temp = temp->right;
        }
    }

    if(!temp || temp->data != elem)
        return false;

    return true;
}

bool AVLTree::isEmpty() const
{
    return this->root == nullptr;
}

void AVLTree::printHelper(const Node* root, std::ostream& out) const
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

void AVLTree::print(std::ostream& out) const
{
    this->printHelper(this->root, out);
}

void AVLTree::DOTprintHelper(const Node* root, std::ostream& out) const
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

void AVLTree::DOTprint(std::ostream& out) const
{
    out << "digraph tree {" << std::endl;
    this->DOTprintHelper(this->root, out);
    out << "}" << std::endl;
}
