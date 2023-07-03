#include <iostream>
#include <vector>

class Heap
{
private:
    std::vector<int> array;

public:
    Heap(int* arr, int size)
    {
        for (int i{}; i < size; ++i)
        {
            array.push_back(arr[i]);
        }

        for (int i{ static_cast<int>(array.size() / 2) }; i >= 0; --i)
        {
            this->heapify(i);
        }
        
    }

    Heap()
    {
        
    }

    void add(int value)
    {
        int temp{}, index = { static_cast<int>((array.size() - 1) / 2)}, curr{static_cast<int>(array.size())};

        array.push_back(value);

        while (index >= 0 && array[index] < value)
        {
            temp = array[index];
            array[index] = array[curr];
            array[curr] = temp;

            curr = index;

            index--;
            index /= 2;
        }
    }

    int removeMax()
    {
        int result = array[0];
        array[0] = array[array.size() - 1];
        array.pop_back();

        this->heapify(0);

        return result;
    }

    void heapify(int i)
    {
        int temp{}, curr{i}, index{}, left{}, right{};

        while (true)
        {
            temp = array[curr];
            left = curr * 2 + 1;
            right = curr * 2 + 2;

            if (left < array.size() && array[left] > temp)
            {
                index = left;
                temp = array[left];
            }
            if (right < array.size() && array[right] > temp)
            {
                index = right;
                temp = array[right];
            }

            if (temp == array[curr])
            {
                return;
            }

            temp = array[index];
            array[index] = array[curr];
            array[curr] = temp;

            curr = index;
        }
    }

    void show()
    {
        int levels{ 1 };
        for (int i{}; i < array.size(); ++i)
        {
            if (i == levels)
            {
                std::cout << "\n";
                levels += ((levels + 1) / 2) * 2;
            }
            std::cout << array[i] << " ";
        }
        std::cout << "\n\n";
    }
};

int main()
{
    srand(time(NULL));
    rand();

    Heap a;
    a.add(20);
    a.add(15);
    a.add(11);
    a.add(6);
    a.add(9);
    a.add(7);
    a.add(8);
    a.add(1);
    a.add(3);
    a.add(5);
    a.add(17);
    a.add(27);
    a.show();

    a.removeMax();
    a.show();

    int* array = new int[12]{ 3, 6, 12, 67, 23, 989, 34, 1, 23, -4, 6, 78 };

    Heap b{ array, 12 };
    b.show();
}