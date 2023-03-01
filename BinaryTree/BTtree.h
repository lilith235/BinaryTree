#ifndef BTTREE_H
#define BTTREE_H

//定义树的元素
class BTtree
{
public:
    BTtree();
    BTtree* lchild;//右子结点
    BTtree* rchild;//左子结点
    char data;//结点数据
    int weight;//当前结点权重
    int D;//当前衰减量最大值
};

#endif // SADEF_H
