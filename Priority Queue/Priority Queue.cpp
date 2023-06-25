#include <iostream>
#include <stdexcept>

template <typename T>
class Queue
{
private:
    int* priorities;
    int count;
    T* array;
    int size;

    void displaceArray(int size, int priority, int index)
    {
        for (int i{ size }; i >= index; --i)
        {
            array[i] = array[i - 1];
        }
    }

    void expandPriorities(int count, int size, int priority)
    {
        int* temp = new int[priority];

        for (int i{}; i < count; ++i)
        {
            temp[i] = priorities[i];
        }

        temp[priority - 1] = size;

        count = priority;

        priorities = temp;
    }

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
        priorities = new int[3]{};
        array = new T[3];
        size = 0;
        count = 3;
    }

    void enqueue(T value, int priority)
    {
        if (!isEmpty() && size % 3 == 0)
        {
            this->resize();
        }

        if (priority > count)
        {
            this->expandPriorities(count, size, priority);
        }

        int index = priorities[priority - 1];

        this->displaceArray(size, priority, index);

        array[index] = value;

        for (int i{priority - 1}; i < count; ++i)
        {
            priorities[i]++;
        }

        ++size;
    }

    void dequeue()
    {
        if (!isEmpty())
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
        if (isEmpty())
        {
            throw std::invalid_argument("");
        }

        return array[0];
    }

    T& back()
    {
        if (isEmpty())
        {
            throw std::invalid_argument("");
        }

        return array[size];
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void show()
    {
        for (int i{}; i < size; ++i)
        {
            std::cout << array[i] << " ";
        }
        std::cout << "\n";
    }

    ~Queue()
    {
        if (priorities != nullptr)
        {
            delete[] priorities;
        }
        if (array != nullptr)
        {
            delete[] array;
        }
    }
};

int main()
{
    Queue<int> a;

    a.enqueue(2, 1);
    a.enqueue(4, 2);
    a.enqueue(5, 1);
    a.enqueue(6, 3);
    a.enqueue(7, 4);
    a.enqueue(8, 2);

    a.show();
}