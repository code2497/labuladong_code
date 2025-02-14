#include <iostream>
#include <ostream>
#include <stdexcept>
#include <memory>
using namespace std;
template<typename T>
class MyCycleArray 
{
    unique_ptr<T[]> arr;
    int size;
    int start;
    int end;
    int count;
    

    void resize(int newSize)
    {
        unique_ptr<T[]> newArr = make_unique<T[]>(newSize);

        for (int i = 0;i < count;i ++)
        {
            newArr[i] = arr[(i + start) % size]; // 注意整个for循环
        }

        arr = move(newArr);
        start = 0;
        end = count;
        size = newSize;
    }

    

public:
    MyCycleArray() : MyCycleArray(1) {}

    explicit MyCycleArray(int size) : start(0), end(0), count(0), size(size)
    {
        arr = make_unique<T[]>(size); //注意这里用make_unique不是直接用unique_ptr生成指针
    }

    void addFirst(T addData)
    {
        if (count == size)
        {
            resize(size * 2);
        }
        start = (start - 1 + size) % size;
        arr[start] = addData;
        count++;
    }

    void addLast(T addData)
    {
        if (count == size)
        {
            resize(size * 2);
        }
        arr[end] = addData;
        end = (end + 1) % size;
        count ++;
    }

    T removeFirst()
    {
        if (isEmpty()) { // 注意判空
            throw std::runtime_error("Array is empty");
        }
        
        arr[start] = T();
        start = (start + 1) % size;
        count --; 
        
        if (count == size / 4)
        {
            resize(size / 2);
        }
    }

    T removeLast()
    {
        if (isEmpty()) {
            throw std::runtime_error("Array is empty");
        }
        
        end = (end - 1 + size) % size;
        arr[end] = T();
        count --;
        if (count == size / 4)
        {
            resize(count / 2);
        }
    }

    void display()
    {
        for (int i = 0;i < count;i ++)
        {
            cout << arr[(i + start) % size] << " ";
        }
        cout << endl;
        cout << "size  : " << size << endl;
        cout << "count : " << count << endl;
        cout << "start : " << start << endl;
        cout << "end   : " << end << endl;
    }

    bool isEmpty() const {
        return count == 0;
    }
};


int main()
{
    MyCycleArray<int> cycArr(4);
    cycArr.addLast(1); // end == 1
    cycArr.display();
    cycArr.addLast(2); // end == 2
    cycArr.display();
    cycArr.addLast(3); // end == 3
    cycArr.display();
    cycArr.addFirst(-1); // 
    cycArr.display();

    cycArr.removeFirst();
    cycArr.display();
    cycArr.removeLast();
    cycArr.display();
    cycArr.removeLast();
    cycArr.display();

}