#ifndef LINKEDBINARYTREE_H
#define LINKEDBINARYTREE_H
#include "binarytreenode.h"
#include "arrayqueue.h"
#include "arraystack.h"
#include <string>
#include <queue>
#include <iostream>
#include <QDebug>
using namespace std;


template <class E>
class linkedBinaryTree//二叉树
{
public:
    string s1="";
    string s2="";
    string s3="";
    string s4="";

    binaryTreeNode<E>* root;//根节点
    linkedBinaryTree() { root = NULL; treeSize = 0; }	// 构造函数
    ~linkedBinaryTree() { erase(root); }// 析构函数
    int getHeight() const//获取树高
    { return height(root);}
    binaryTreeNode<E> * getRoot() const { return root; }
    int getSize()//获取结点数
        {
            treeSize = 0;
            // 调用后序遍历递归函数，将私有成员size函数作为对节点的访问方式赋值给visit
            postOrder(root);
            return treeSize;
        }

    // 前序递归创建二叉树
    void preCreatBinaryTree(std::string thePre)
    {
        unsigned int preSize = thePre.length();
        for (int i = 0; i < static_cast<int>(preSize); input.push(thePre[i]), i++);
        E ch;
        input.pop(ch);
        if (ch == '#') throw invalidSequence();
        root = new binaryTreeNode<E>(ch);		// 生成根节点
        // 调用私有的递归函数
        preCreat(root);
    }

    // 层次非递归创建二叉树
    void levelCreatBinaryTree(std::string thelevel);

    // 前序 + 中序非递归创建二叉树
    void preAndInCreatBinaryTree(std::string thePre, std::string theIn);

    // 销毁函数
    void erase(binaryTreeNode<E>* t);

    //四种遍历方式
    void preorders(binaryTreeNode<E>* t)
    {
        if(t!=NULL)
        {
            s1 += t->element;
            preorders(t->leftChild);
            preorders(t->rightChild);
        }
    }
    void inorders(binaryTreeNode<E>* t)
    {
        if(t!=NULL)
        {
            inorders(t->leftChild);
            s2 += t->element;
            inorders(t->rightChild);
        }
    }
    void postorders(binaryTreeNode<E>* t)
    {
        if(t!=NULL)
        {
            postorders(t->leftChild);
            postorders(t->rightChild);
            s3 += t->element;
        }
    }

    void levelorders()
    {
        binaryTreeNode<E>* btn = root;
            queue<binaryTreeNode<E>*> q;
            q.push(root);
            char str[50];
            for (int i = 0; !q.empty(); i++) {
                //qDebug()<<"i="<<i;
                str[i] = q.front()->element;
                if (q.front()->leftChild) {
                    q.push(q.front()->leftChild);
                }
                if (q.front()->rightChild) {
                    q.push(q.front()->rightChild);
                }
                q.pop();
            }
            s4=str;
    }


private:
    arrayQueue<E> input;//输入序列
    void postOrder(binaryTreeNode<E>* t);
    void preCreat(binaryTreeNode<E>*& t);
    int height(binaryTreeNode<E>* t) const;
    int treeSize;//结点数
};

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E>* t)
{
    if (t != NULL)
    {
        postOrder(t->leftChild);
        postOrder(t->rightChild);
        treeSize++;
    }
}

template<class E>
void linkedBinaryTree<E>::preAndInCreatBinaryTree(std::string pre, std::string in)
{
    unsigned int seqSize = pre.length();
    unsigned int inSize = in.length();
    if (seqSize != inSize) throw invalidSequence();
    bool *flag = new bool[seqSize] {false};				// 标记该节点是否已被创建
    arrayStack<binaryTreeNode<E>*> s;
    unsigned int preIndex = 0;
    int inIndex;
    binaryTreeNode<E>* t;
    root = new binaryTreeNode<E>(pre[preIndex]);		// 生成根节点
    inIndex = static_cast<int>(in.find(pre[preIndex]));
    flag[inIndex] = true;
    t = root;

    while (1)
    {
        unsigned int offset = 1;				// 偏移量
        if (inIndex + 1 < static_cast<int>(seqSize) && !flag[inIndex + 1])
        {// 存在右子树

            // 找到右孩子节点在 前序序列 中的位置
            for (int i = inIndex - 1; !flag[i] && i >= 0; i--, offset++);
            unsigned int rChildIndex = preIndex + offset;

            t->rightChild = new binaryTreeNode<E>(pre[rChildIndex]);
            s.push(t->rightChild);	// 右孩子节点入栈

            // 在 中序序列 中标记一下
            flag[in.find(pre[rChildIndex])] = true;
        }
        if (inIndex - 1 >= 0 && !flag[inIndex - 1])
        {// 存在左子树

            preIndex++;				// 则左子树的根节点在 前序序列 中一定在其父节点的下一个位置
            t->leftChild = new binaryTreeNode<E>(pre[preIndex]);
            inIndex = static_cast<int>(in.find(pre[preIndex]));
            flag[inIndex] = true;
            t = t->leftChild;
        }
        else
        {
            // 不存在左子树的话，从栈里面弹出最近的一个右子树节点
            preIndex++;
            try { s.pop(t); }
            catch (stackEmpty)
            {
                if (static_cast<int>(seqSize) != getSize())
                    throw invalidSequence();
                return;
            }
            inIndex = static_cast<int>(in.find(pre[preIndex]));
        }
    }
}

template<class E>
void linkedBinaryTree<E>::levelCreatBinaryTree(std::string thelevel)
{
    unsigned int seqSize = thelevel.length();
    for (int i = 0; i < static_cast<int>(seqSize); input.push(thelevel[i]), i++);
    E ch;
    arrayQueue<binaryTreeNode<E>*> q;
    input.pop(ch);
    if (ch == '#') throw invalidSequence();
    root = new binaryTreeNode<E>(ch);		// 生成根节点
    binaryTreeNode<E>* t = root;
    do {
        if (!input.empty())
        {
            input.pop(ch);
            if (ch != '#')
            {
                t->leftChild = new binaryTreeNode<E>(ch);
                q.push(t->leftChild);
            }
        }
        if (!input.empty())
        {
            input.pop(ch);
            if (ch != '#')
            {
                t->rightChild = new binaryTreeNode<E>(ch);
                q.push(t->rightChild);
            }
        }
        try { q.pop(t); }
        catch (queueEmpty) { return; }
    } while (!input.empty());
}

template<class E>
void linkedBinaryTree<E>::preCreat(binaryTreeNode<E>*& t)
{
    E ch;
    if (!input.empty())
    {
        input.pop(ch);
        if (ch != '#')
        {
            t->leftChild = new binaryTreeNode<E>(ch);
            preCreat(t->leftChild);
        }
    }
    if (!input.empty())
    {
        input.pop(ch);
        if (ch != '#')
        {
            t->rightChild = new binaryTreeNode<E>(ch);
            preCreat(t->rightChild);
        }
    }
}

template<class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t) const
{
    if (t == NULL) return 0;			// 空节点
    int hl = height(t->leftChild);		// 左树高
    int hr = height(t->rightChild);		// 右树高
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}

template<class E>
void linkedBinaryTree<E>::erase(binaryTreeNode<E>* t)
{
    if (t != NULL)
    {
        erase(t->leftChild);
        erase(t->rightChild);
        delete t;
    }
}

#endif // LINKEDBINARYTREE_H
