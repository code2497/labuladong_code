#include <iostream>
#include <vector>
using namespace std;

class MyMinHeap
{
    vector<int> heap;
    int size;

    static int parent(int node)
    {
        return (node - 1) / 2;
    }    

    static int left(int node)
    {
        return node * 2 + 1;
    }

    static int right(int node)
    {
        return node * 2 + 2;
    }

    void swim(int node)
    {
        while (node > 0 && heap[parent(node)] > heap[node])
        {
            swap(heap[node], heap[parent(node)]);
            node = parent(node); // 记得修改node值
        }
    }

    void sink(int node)
    {
        while (left(node) < size || right(node) < size)
        {
            int minIdx = node; // 这里用index
            if (left(node) < size && heap[minIdx] > heap[left(node)])
            {
                minIdx = left(node);
            }
            if (right(node) < size && heap[minIdx] > heap[right(node)])
            {
                minIdx = right(node);
            }
            if (minIdx == node)
            {
                break;
            }
            swap(heap[minIdx], heap[node]);
            node = minIdx; // 记得修改node值
        }
        
    }

public:
    MyMinHeap (int cap)
    {
        heap.resize(cap);
        size = 0;
    }

    int peek()
    {
        return heap[0];
    }

    int getSize()
    {
        return size;
    }

    void push(int nodeVal)
    {
        heap[size] = nodeVal;
        swim(size);
        size ++;
    }

    int pop()
    {
        int res = heap[0];
        heap[0] = heap[size - 1];
        size --; // 注意先size--再sink
        sink(0);
        return res;
    }
};


int main() {
    MyMinHeap pq(5);
    pq.push(3);
    pq.push(2);
    pq.push(1);
    pq.push(5);
    pq.push(4);

    cout << pq.pop() << endl; // 1
    cout << pq.pop() << endl; // 2
    cout << pq.pop() << endl; // 3
    cout << pq.pop() << endl; // 4
    cout << pq.pop() << endl; // 5

    return 0;
}