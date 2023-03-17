#ifndef __AVLTREE_HPP
#define __AVLTREE_HPP

#include <iostream>

class AVLTree
{
    private:
        struct Node
        {
            int data;
            Node* left;
            Node* right;
            int balanceFactor; // right subtree height - left subtree height
        };
        
        Node* root;

        void copy(const Node* otherRoot);
        void eraseAll(Node*& root);

        void getParent(Node* child, Node*& parent);

        void leftRotation(Node*& root);
        void rightRotation(Node*& root);
        void rebalance(Node*& root);

        void updateBalance(Node*& node); 
        Node* insertHelper(Node*& root, int elem);

        bool eraseHelper(Node*& root, int elem, Node* parent);

        Node* minHelper(Node* root) const;
        Node* maxHelper(Node* root) const;
        int heightHelper(const Node* root) const;

        void printHelper(const Node* root, std::ostream& out = std::cout) const;
        void DOTprintHelper(const Node* root, std::ostream& out = std::cout) const;

    public:
        AVLTree();
        AVLTree(const AVLTree& other);
        ~AVLTree();

        AVLTree& operator = (const AVLTree& other);

        void insert(const int& elem);
        void erase(const int& elem);

        int min() const;
        int max() const;
        int height() const;

        bool member(const int& elem) const;
        bool isEmpty() const;
        
        void print(std::ostream& out = std::cout) const;
        void DOTprint(std::ostream& out = std::cout) const;
};

#endif
