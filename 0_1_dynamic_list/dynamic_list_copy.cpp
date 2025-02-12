#include <iostream>
using namespace std;

template<typename E>
class MyDynamicList {
private:
    E *data;
    int size;
    int cap;
    static const int INIT_CAP = 1;

public:
    MyDynamicList()
    {
        this->data = new E[INIT_CAP]; // 注意INIT_CAP不用this
        this->cap = INIT_CAP;
        this->size = 0;
    }

    MyDynamicList(int initCap)
    {
        this->data = new E[initCap];
        this->cap = initCap;
        this->size = 0;
    }

    void addLast(E addData)
    {
        if (size == cap) //注意增容条件
        {
            resize(cap * 2);
        }
        data[size ++] = addData;
    }

    void add(E addData, int index)
    {
        checkPositionIndex(index);
        if (size == cap)
        {
            resize(2 * cap);
        }
        for(int i = size - 1;i >= index;i --)
        {
            data[i + 1] = data[i];
        }
        data[index] = addData;
        size ++;
    }

    

    void addFirst(E addData)
    {
        add(addData, 0);
    }

    E removeLast()
    {
        if (size == 0) // 注意删除空列表
        {
            throw out_of_range("NoSuchElementExecption");
        }
        if (size == cap / 4)
        {
            resize(cap / 2);
        }
        E removeData = data[size - 1];
        data[size - 1] = NULL;
        size --;
        return removeData;
    }

    E remove(int index)
    {
        checkElementIndex(index);
        if (size == cap / 4)
        {
            resize(cap / 2);
        }
        E removeData = data[size - 1];
        for(int i = index + 1;i < size;i ++)
        {
            data[i - 1] = data[i];
        }
        data[size - 1] = NULL;
        size --;
        return removeData;
    }

    void removeFirst()
    {
        remove(0);
    }

    E get(int index)
    {
        checkElementIndex(index);
        return data[index];
    }

    E set(E setData, int index)
    {
        checkElementIndex(index);
        E oldData = data[index];
        data[index] = setData;
        // 注意返回旧值
        return oldData;
    }

    bool isPositionIndex(int index)
    {
        return index >= 0 && index <= size;
    }

    bool isElementIndex(int index)
    {
        return index >= 0 && index < size;
    }

    void checkElementIndex(int index)
    {
        if (!isElementIndex(index))
        {
            // 注意错误类型
            throw out_of_range("Index out of bounds");
        }
    }
    void checkPositionIndex(int index)
    {
        if (!isPositionIndex(index))
        {
            // 注意错误类型
            throw out_of_range("Index out of bounds");
        }
    }

    void resize(int newCap)
    {
        E *temp = new E[newCap];
        for(int i = 0;i < size;i ++)
        {
            temp[i] = data[i];
        }
        // 注意释放原数组内存
        delete[] data;

        data = temp; // 注意修改地址
        cap = newCap;
    }

    void display() {
        std::cout << "size = " << size << " cap = " << cap << std::endl;
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    int getSize()
    {
        return size;
    }

    ~MyDynamicList() {
        delete[] data;
    }
};


int main() {
    // 初始容量设置为 3
    MyDynamicList<int> arr(3);

    // 添加 5 个元素
    for (int i = 1; i <= 5; i++) {
        arr.addLast(i);
    }
    arr.display();

    arr.remove(3);
    arr.display();

    arr.add(9, 1);
    arr.display();

    arr.addFirst(100);
    int val = arr.removeLast();

    // 100 1 9 2 3
    for (int i = 0; i < arr.getSize(); i++) {
        std::cout << arr.get(i) << std::endl;
    }

    return 0;
}