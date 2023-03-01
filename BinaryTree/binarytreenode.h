#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

template <class T>
struct binaryTreeNode//二叉树结点
{
    T element;//结点元素
    binaryTreeNode<T> *leftChild;//左子结点
    binaryTreeNode<T> *rightChild;//右子结点
    binaryTreeNode() : leftChild(nullptr), rightChild(nullptr) { }
    binaryTreeNode(const T &theElement) :
        element(theElement), leftChild(nullptr), rightChild(nullptr) { }
    binaryTreeNode(const T &theElement, binaryTreeNode *theLeftChild, binaryTreeNode *theRightChild) :
        element(theElement), leftChild(theLeftChild), rightChild(theRightChild) { }
};


#endif // BINARYTREENODE_H
