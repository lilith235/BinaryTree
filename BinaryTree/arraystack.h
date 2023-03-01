#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
#include <sstream>
#include <algorithm>
#include "errorInfo.h"

template <class T>
class arrayStack
{
public:
    arrayStack(int initialCapacity = 10);//构造函数
    ~arrayStack() { delete[] stack; }
    bool empty() const { return stackTop == -1; }
    int size() const { return stackTop + 1; }
    T & top()
    {
        if (stackTop == -1)
            throw stackEmpty();
        return stack[stackTop];
    }
    void pop(T& theElement)
    {
        if (stackTop == -1)
            throw stackEmpty();
        theElement = stack[stackTop];
        stack[stackTop--].~T();		// T的析构函数
    }
    void push(const T & theElement);
    void changelength1D(T *& a, int oldLength, int newLength);

private:
    int stackTop;//栈顶
    int arrayLength;//栈的高度
    T *stack;//栈内元素数组
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1;
}

template<class T>
void arrayStack<T>::push(const T & theElement)
{
    if (stackTop == arrayLength - 1)
    {
        changelength1D(stack, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    stack[++stackTop] = theElement;
}

template<class T>
void arrayStack<T>::changelength1D(T *& a, int oldLength, int newLength)
{
    if (newLength < 0)
        throw illegalParameterValue("new length must be >= 0");

    T *temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a + number, temp);
    delete[] a;
    a = temp;
}

#endif // ARRAYSTACK_H
