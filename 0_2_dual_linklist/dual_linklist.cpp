
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
template <typename E>
class MyDualLinklist {
    struct Node {
        E val;
        Node *next;
        Node *prev;
        Node (E nodeVal) : val(nodeVal), next(NULL), prev(NULL) {} // 注意初始化写法
    };
    int size;
    Node *head;
    Node *tail;
public:
    MyDualLinklist()
    {
        head = new Node(E()); // 注意E()写法
        tail = new Node(E()); // 注意E()写法
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    void addLast(E addData)
    {
        Node *x = new Node(addData);
        Node *temp = tail->prev;
        // temp <-> x
        x->prev = temp;
        temp->next = x;
        // temp <-> x <-> tail
        x->next = tail;
        tail->prev = x;
        size ++;
    }

    void addFirst(E addData)
    {
        // x <-> temp
        Node *x = new Node(addData);
        Node *temp = head->next;
        x->next = temp;
        temp->prev = x;
        // head <-> x <-> temp
        x->prev = head;
        head->next = x;
        size ++;
    }

    void add(E addData, int index)
    {
        checkPositionIndex(index);
        if (index == size) { //注意简化
            addLast(addData);
            return;
        }
        Node *x = new Node(addData);
        Node *p = getNode(index);
        Node *temp = p->prev;

        // temp <-> x
        x->prev = temp;
        temp->next = x;

        // temp <-> x <-> p
        x->next = p;
        p->prev = x;
        size ++;
    }

    E removeFirst()
    {
        if (size == 0)
        {
            throw out_of_range("No elements to remove");
        }
        Node *x = head->next;
        E val = x->val;
        Node *temp = x->next;

        head->next = temp;
        temp->prev = head;
        delete x;
        size --;
        return val;
    }

    E removeLast()
    {
        if (size == 0)
        {
            throw out_of_range("No elements to remove");
        }
        Node *x = tail->prev;
        Node *temp = x->prev;
        E val = x->val;

        tail->prev = temp;
        temp->next = tail;
        delete x;
        size --;
        return val;
    }

    E remove(int index) {
        checkElementIndex(index);
        // 找到 index 对应的 Node
        Node* x = getNode(index);
        Node* prev = x->prev;
        Node* next = x->next;
        // prev <-> x <-> next
        prev->next = next;
        next->prev = prev;

        delete x;
        // prev <-> next

        size--;

        return next->val;
    }



    bool isPositionIndex(int index)
    {
        return index >= 0 && index <= size; 
    }

    void checkPositionIndex(int index)
    {
        if (!isPositionIndex(index))
        {
            throw out_of_range("Index:" + std::to_string(index) +"Size:" + std::to_string(size));
        }
    }

    bool isElementIndex(int index)
    {
        return index >= 0 && index < size; 
    }

    void checkElementIndex(int index)
    {
        if (!isElementIndex(index))
        {
            throw out_of_range("Index:" + std::to_string(index) +"Size:" + std::to_string(size));
        }
    }

    Node *getNode(int index)
    {
        checkElementIndex(index);
        Node *p = head->next;
        for(int i = 0;i < index; i ++)
        {
            p = p->next;
        }
        return p;
    }


    E get(int index) {
        checkElementIndex(index);
        // 找到 index 对应的 Node
        Node* p = getNode(index);

        return p->val;
    }

    E getFirst() {
        if (size < 1) {
            throw std::out_of_range("No elements in the list");
        }

        return head->next->val;
    }

    E getLast() {
        if (size < 1) {
            throw std::out_of_range("No elements in the list");
        }

        return tail->prev->val;
    }

    // ***** 改 *****

    E set(int index, E val) {
        checkElementIndex(index);
        // 找到 index 对应的 Node
        Node* p = getNode(index);

        E oldVal = p->val;
        p->val = val;

        return oldVal;
    }

    // ***** 其他工具函数 *****

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }


    void display()
    {
        cout << "Size : " << size << endl;
        for(Node *p = head->next;p != tail;p = p->next)
        {
            cout << p->val << " <-> ";
        }
        cout << "null" << endl;
    }
};


int main() {
    MyDualLinklist<int> list;
    list.addLast(1);
    list.addLast(2);
    list.addLast(3);

    list.addFirst(0);
    list.add(100, 2);
    list.display();

    // list.removeFirst();
    // list.removeLast();
    list.remove(2);
    list.remove(1);
    list.display();

    
    // size = 5
    // 0 <-> 1 <-> 100 <-> 2 <-> 3 <-> null

    return 0;
}