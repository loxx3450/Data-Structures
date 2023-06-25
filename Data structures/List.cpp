#include <iostream>

template <typename T>
struct Node
{
    T value;
    Node* next;

    Node() : value{0}, next{nullptr}{}

    Node(T val) : value{val}, next{nullptr}{}

    Node(T val, Node* next) : value{val}, next{next}{}

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
    int length;
    Node<T>* head;
    Node<T>* tail;

    void sortArray(T* array, int length)
    {
        T temp;
        bool isChanged{ true };

        while(isChanged)
        {
            isChanged = false;

            for (int i{}; i < length - 1; ++i)
            {
                if (array[i] <= array[i + 1])
                {
                    continue;
                }
                else
                {
                    temp = array[i];
                    array[i] = array[i + 1];
                    array[i + 1] = temp;

                    isChanged = true;
                }
            }
        }
    }

public:
    List()
    {
        this->head = nullptr;
        this->tail = nullptr;
        length = 0;
    }

    void push_front(T value)
    {
        if (length == 0)
        {
            this->head = new Node<T>(value);

            this->tail = this->head;
        }
        else
        {
            Node<T>* temp = new Node<T>(value, this->head);

            this->head = temp;
        }

        ++length;
    }

    void push_back(T value)
    {
        if (length == 0)
        {
            this->head = new Node<T>(value);

            this->tail = this->head;
        }
        else
        {
            Node<T>* temp = new Node<T>(value);

            this->tail->next = temp;

            this->tail = this->tail->next;
        }

        ++length;
    }

    void pop_front()
    {
        if (head != nullptr)
        {
            head = head->next;

            --length;
        }
    }

    void pop_back()
    {
        if (head != nullptr)
        {
            if (head->next == nullptr)
            {
                head = nullptr;

                --length;

                return;
            }

            Node<T>* temp = head;

            while (temp->next->next != nullptr)
            {
                temp = temp->next;
            }

            temp->next = nullptr;

            tail = temp;

            --length;
        }
    }

    void remove(int value)
    {
        if (head != nullptr)
        {
            Node<T>* temp = head;
            Node<T>* prev = nullptr;

            while (temp != nullptr)
            {
                if (temp->value == value)
                {
                    if (prev == nullptr)
                    {
                        head = temp->next;
                    }
                    else
                    {
                        prev->next = temp->next;
                    }

                    --length;
                }
                else
                {
                    prev = temp;
                }

                temp = temp->next;
            }

            if (temp != nullptr) { delete temp; }
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

        this->sortArray(array, length);

        temp = head;

        for (int i{};;++i)
        {
            if (temp == nullptr) { break; }

            temp->value = array[i];

            temp = temp->next;
        }

        delete[] array;
        if (temp != nullptr) { delete temp; }
    }

    void reverse()
    {
        Node<T>* curr = head;
        Node<T>* prev = nullptr;
        Node<T>* temp = nullptr;

        this->tail = head;

        while (curr != nullptr)
        {
            temp = curr->next;

            curr->next = prev;

            prev = curr;

            curr = temp;
        }

        head = prev;

        if (temp != nullptr) { delete temp; }

        if (curr != nullptr) { delete curr; }
    }

    T& front()
    {
        return head->value;
    }

    T& back()
    {
        return tail->value;
    }

    bool isEmpty()
    {
        return this->length == 0;
    }

    int getLength()
    {
        return this->length;
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
    a.push_back(4);
    a.push_back(5);
    a.push_front(1);
    a.push_front(3);
    a.push_front(2);
    a.push_back(2);

    a.sort();

    a.show();

    a.reverse();
    a.push_back(4);

    a.show();

    a.remove(2);
    a.show();
}