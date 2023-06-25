#include <iostream>

template <typename T>
struct Node
{
    T value;
    Node* next;
    Node* prev;

    Node() : value{ 0 }, next{ nullptr }, prev{nullptr}{}

    Node(T val) : value{ val }, next{ nullptr }, prev{ nullptr }{}

    Node(T val, Node* next) : value{ val }, next{ next }, prev{ nullptr }{}

    Node(T val, Node* next, Node* prev) : value{ val }, next{ next }, prev{ prev }{}

    ~Node()
    {
        if (next != nullptr)
        {
            delete next;
        }
    }
};

template <typename T>
class List
{
private:
    Node<T>* head;
    Node<T>* tail;
    int length;

    void sortArray(T* array)
    {
        int minIndex{}, minVal{}, temp{};

        for (int i{}; i < length - 1; ++i)
        {
            minVal = array[i];
            minIndex = i;

            for (int j{ i }; j < length; ++j)
            {
                if (array[j] < minVal)
                {
                    minVal = array[j];
                    minIndex = j;
                }
            }

            temp = array[i];
            array[i] = minVal;
            array[minIndex] = temp;
        }
    }

public:
    List()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    void push_front(T value)
    {
        if (length == 0)
        {
            head = new Node<T>(value);
            tail = head;
        }
        else
        {
            Node<T>* temp = new Node<T>(value, head);

            head->prev = temp;

            head = temp;
        }

        ++length;
    }

    void push_back(T value)
    {
        if (length == 0)
        {
            head = new Node<T>(value);
            tail = head;
        }
        else
        {
            Node<T>* temp = new Node<T>(value, nullptr, tail);

            tail->next = temp;

            tail = temp;
        }

        ++length;
    }

    void pop_front()
    {
        if (head != nullptr)
        {
            if (length == 1)
            {
                head = nullptr;
                tail = nullptr;
            }
            else
            {
                head = head->next;
                head->prev = nullptr;
            }
            
            --length;
        }
    }

    void pop_back()
    {
        if (tail != nullptr)
        {
            if (length == 1)
            {
                tail = nullptr;
                head = nullptr;
            }
            else
            {
                tail->prev->next = nullptr;
                tail = tail->prev;
            }

            --length;
        }
    }

    void remove(T value)
    {
        if (head != nullptr)
        {
            Node<T>* curr = head;

            while (curr != nullptr)
            {
                if (curr->value == value)
                {
                    if (curr->next != nullptr && curr->prev != nullptr)
                    {
                        curr->prev->next = curr->next;
                        curr->next->prev = curr->prev;
                    }
                    else if (curr->next != nullptr)
                    {
                        curr->next->prev = nullptr;
                        head = curr->next;
                    }
                    else if (curr->prev != nullptr)
                    {
                        curr->prev->next = nullptr;
                        tail = curr->prev;
                    }
                    else
                    {
                        head = nullptr;
                        tail = head;
                    }

                    --length;
                }

                curr = curr->next;
            }

            if (curr != nullptr) { delete curr; }
        }
    }

    void sort()
    {
        T* array = new T[length];

        Node<T>* temp = head;

        for (int i{};; ++i)
        {
            if (temp == nullptr)
            {
                break;
            }

            array[i] = temp->value;

            temp = temp->next;
        }

        this->sortArray(array);

        temp = head;

        for (int i{};; ++i)
        {
            if (temp == nullptr)
            {
                break;
            }

            temp->value = array[i];

            temp = temp->next;
        }

        if (temp != nullptr) { delete temp; }
    }

    void reverse()
    {
        Node<T>* temp = nullptr;

        tail = head;

        while (head->next != nullptr)
        {
            temp = head->prev;
            head->prev = head->next;
            head->next = temp;

            head = head->prev;
        }

        head->next = head->prev;
    }

    T& front()
    {
        return head;
    }

    T& back()
    {
        return tail;
    }

    bool isEmpty()
    {
        return length == 0;
    }

    int getLength()
    {
        return length;
    }

    void show()
    {
        Node<T>* temp = head;

        while (temp != nullptr)
        {
            std::cout << temp->value << " ";

            temp = temp->next;
        }

        std::cout << "\n";

        if (temp != nullptr) { delete temp; }
    }

    ~List()
    {
        if (head != nullptr)
        {
            delete head;
        }
    }
};

int main()
{
    List<int> a;
    a.push_front(2);
    a.push_front(2);
    a.push_front(2);
    a.push_front(1);
    a.push_front(3);
    a.push_front(6);
    a.push_front(2);
    a.push_front(3);
    a.push_front(1);

    a.show();

    a.sort();

    a.show();

    a.remove(2);

    a.show();

    a.reverse();

    a.show();
}