#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>
using namespace std;

template <typename K, typename V>
struct Node
{
    K key;
    V val;
    Node *next;
    Node *prev;

    Node(K key, V val) : key(key), val(val), next(NULL), prev(NULL){}
};

template <typename K, typename V>
class MyLinkedHashMap
{
public:
    MyLinkedHashMap ()
    {
        head = new Node<K, V>(K(), V());
        tail = new Node<K, V>(K(), V());
        head->next = tail;
        tail->prev = head;
    }

    V get(K key)
    {
        if (map.find(key) == map.end())
        {
            return V();
        }
        return map[key];
    }

    void put(K key, V val)
    {
        if (map.find(key) == map.end())
        {
            Node<K, V>* node = new Node<K, V>(key, val);
            addLastNode(node);
            map[key] = node;
            return;
        }
        map[key]->val = val;
    }

    void remove(K key)
    {
        if (map.find(key) == map.end())
        {
            return;
        }
        removeNode(map[key]);
        map.erase(key);
    }

    vector<K> keys()
    {
        vector<K> keyList;
        for(Node<K, V>* x = head->next;x != tail;x = x->next)
        {
            keyList.push_back(x->key);
        }
        return keyList;
    }
private:
    unordered_map<K, Node<K, V>*> map; //注意unordered_map写法
    Node<K, V>* head;
    Node<K, V>* tail;

    void addLastNode(Node<K, V>* x)
    {
        Node<K, V>* temp = tail->prev;
        // temp <> x
        x->prev = temp;
        temp->next = x;
        // temp <> x <> tail
        x->next = tail;
        tail->prev = x;
    }

    void removeNode(Node<K, V>* x)
    {
        Node<K, V>* prev = x->prev;
        Node<K, V>* next = x->next;

        prev->next = next;
        next->prev = prev;

        x->next = nullptr;
        x->prev = nullptr;
    }
};

int main() {
    MyLinkedHashMap<string, int> map;
    map.put("a", 1);
    map.put("b", 2);
    map.put("c", 3);
    map.put("d", 4);
    map.put("e", 5);
    cout << map.keys().size() << endl;
    // output: a b c d e
    for (const auto& key : map.keys()) {
        cout << key << " ";
    }
    cout << endl;

    map.remove("c");

    // output: a b d e
    for (const auto& key : map.keys()) {
        cout << key << " ";
    }
    cout << endl;

    return 0;
}