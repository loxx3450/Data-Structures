#include <iostream>

template <typename T>
class Stack
{
private:
    T* array;
    int length;
    
    void resize()
    {
        T* temp = new T[length + 3];

        for (int i{}; i < length; ++i)
        {
            temp[i] = array[i];
        }

        array = temp;
    }

public:
    Stack()
    {
        array = new T[3];
        length = 0;
    }

    void push(T value)
    {
        if (length > 0 && length % 3 == 0)
        {
            this->resize();
        }

        this->array[length++] = value;
    }

    void pop()
    {
        if (length > 0)
        {
            --length;
        }
    }

    T peek()
    {
        if (length != 0)
        {
            return this->array[length - 1];
        }
    }

    bool isEmpty()
    {
        return length == 0;
    }

    void show()
    {
        for (int i{}; i < length; ++i)
        {
            std::cout << array[i] << " ";
        }
        std::cout << "\n";
    }
};

int main()
{
    Stack<int> mystack;

    for (int i = 0; i < 5; ++i) mystack.push(i);

    std::cout << "Popping out elements...";
    while (!mystack.isEmpty())
    {
        std::cout << ' ' << mystack.peek();
        mystack.pop();
    }
    std::cout << '\n';

    return 0;
}