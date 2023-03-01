#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H
#include <algorithm>
#include <sstream>
#include "errorinfo.h"

template <class T>
class arrayQueue
{
public:
    arrayQueue(int initialCapacity = 10);
    ~arrayQueue() { delete[] queue; }
    bool empty() const { return queueFront == queueBack; }
    int size() const { return (queueBack + arrayCapacity - queueFront) % arrayCapacity; }
    T* getFront() const { return queue[(queueFront + 1) % arrayCapacity]; }
    void push(const T & theElement);
    void pop(T & theElement);
private:
    T* queue;//队列元素数组
    int queueFront;//队首
    int queueBack;//队尾
    int arrayCapacity;//队列容量
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayCapacity = initialCapacity;
    queue = new T[arrayCapacity];
    queueFront = queueBack = 0;
}

template<class T>
void arrayQueue<T>::push(const T & theElement)
{
    if ((queueBack + 1) % arrayCapacity == queueFront)
    {
        // 分配新的数组空间
        T* newQueue = new T[2 * arrayCapacity];

        // 把原数组元素复制到新数组
        // 找到头元素的位置(下标)
        int start = (queueFront + 1) % arrayCapacity;
        if (start < 2)
            // 没有形成环
            std::copy(queue + start, queue + start + arrayCapacity - 1, newQueue);
        else
        {
            // 队列形成环
            std::copy(queue + start, queue + arrayCapacity, newQueue);
            std::copy(queue, queue + queueBack + 1, newQueue + arrayCapacity - start);
        }

        // 设置新队列的首和尾的元素位置
        queueFront = 2 * arrayCapacity - 1;
        queueBack = arrayCapacity - 2;
        arrayCapacity *= 2;
        delete[] queue;
        queue = newQueue;
    }
    queueBack = (queueBack + 1) % arrayCapacity;
    queue[queueBack] = theElement;
}

template<class T>
void arrayQueue<T>::pop(T & theElement)
{
    if (empty())
        throw queueEmpty();
    theElement = queue[(queueFront + 1) % arrayCapacity];
    queueFront = (queueFront + 1) % arrayCapacity;
    queue[queueFront].~T();		// 给T析构
}

#endif // ARRAYQUEUE_H
