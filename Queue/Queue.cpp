#include <iostream>
#include <stdexcept>

template <typename T>
class Queue
{
private:
    T* array;
    int size;

    void resize()
    {
        T* temp = new T[size + 3];

        for (int i{}; i < size; ++i)
        {
            temp[i] = array[i];
        }

        array = temp;
    }

public:
    Queue()
    {
        array = new T[3];
        size = 0;
    }

    void enqueue(T value)
    {
        array[size++] = value;
    }

    void dequeue()
    {
        if (size != 0)
        {
            --size;

            for (int i{}; i < size; ++i)
            {
                array[i] = array[i + 1];
            }
        }
    }

    T& front()
    {
        if (size == 0)
        {
            throw std::invalid_argument("");
        }

        return array[0];
    }

    T& back()
    {
        if (size == 0)
        {
            throw std::invalid_argument("");
        }

        return array[size];
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

int main()
{
    Queue<int> myqueue;

    for (int i{ 2 }; i < 9; ++i) { myqueue.enqueue(i); }

    std::cout << "myqueue contains: ";

    while (!myqueue.isEmpty())
    {
        std::cout << ' ' << myqueue.front();
        myqueue.dequeue();
    }
    std::cout << '\n';

    return 0;
}