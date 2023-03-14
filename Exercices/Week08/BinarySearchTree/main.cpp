#include <iostream>
#include <fstream>
#include <cassert>

#include "BST.hpp"

int main()
{
    BST<int> tree;

    tree.insert(3);
    tree.insert(2);
    tree.insert(4);
    tree.insert(1);
    tree.insert(5);

    assert(tree.isValidBST());
    assert(tree.min() == 1);
    assert(tree.max() == 5);

    std::ofstream file1("BST.dot");
    tree.DOTprint(file1);
    file1.close();

    tree.print();
    std::cout << std::endl;

    assert(tree.erase(2));
    assert(!tree.erase(7));

    std::ofstream file2("BST2.dot");
    tree.DOTprint(file2);
    file2.close();

    tree.print();
    std::cout << std::endl;
    return 0;
}
