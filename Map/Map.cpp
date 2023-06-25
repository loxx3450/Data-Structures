#include <iostream>

template <typename T, typename K>
class MapItem
{
private:
    T key;
    K value;

public:
    MapItem(T key, K value)
    {
        this->key = key;
        this->value = value;
    }

    T getKey()
    {
        return this->key;
    }

    void setValue(K value)
    {
        this->value = value;
    }

    K getValue()
    {
        return this->value;
    }
};

template <typename T, typename K>
class Map
{
private:
    MapItem<T, K>** array;
    int size;

    struct Iterator
    {
        public:
            Iterator(MapItem<T, K>** arr) : index{ 0 }, array{ arr }
            {
                this->first = this->array[index]->getKey();
                this->second = this->array[index]->getValue();
            }

            Iterator(int id, MapItem<T, K>** arr) : index{ id }, array{ arr }
            {
                if (array[index] != nullptr)
                {
                    this->first = this->array[index]->getKey();
                    this->second = this->array[index]->getValue();
                }
            }

            T first;
            K second;

            Iterator& operator++()
            {
                index++;

                if (array[index] != nullptr)
                {
                    this->first = this->array[index]->getKey();
                    this->second = this->array[index]->getValue();
                }

                return *this;
            }

            bool operator==(const Iterator& other)
            {
                if (this->index != other.index)
                {
                    return false;
                }
                if (this->array != other.array)
                {
                    return false;
                }

                return true;
            }

            bool operator!=(const Iterator& other)
            {
                return !(*this == other);
            }

            K operator*()
            {
                return this->array[index]->getValue();
            };

        private:
            MapItem<T, K>** array;
            int index;
    };

    void resize()
    {
        MapItem<T, K>** temp = new MapItem<T, K>*[this->size + 3]{};

        for (int i{}; i < size; ++i)
        {
            temp[i] = array[i];
        }

        array = temp;
    }

public:
    Map()
    {
        array = new MapItem<T, K>*[3]{};
        size = 0;
    }

    void insert(T key, K value)
    {
        if (!isEmpty() && size % 3 == 0)
        {
            this->resize();
        }

        array[size++] = new MapItem<T, K>(key, value);
    }

    K at(T key)
    {
        return find(key);
    }

    K find(T key)
    {
        if (!isEmpty())
        {
            for (int i{}; i < size; ++i)
            {
                if (array[i]->getKey() == key)
                {
                    return array[i]->getValue();
                }
            }
        }

        throw K{};
    }

    int count(T key)
    {
        if (!isEmpty())
        {
            int result{};

            for (int i{}; i < size; ++i)
            {
                if (array[i]->getKey() == key)
                {
                    result++;
                }
            }

            return result;
        }

        throw K{};
    }

    void erase(T key)
    {
        if (!isEmpty())
        {
            for (int i{}; i < size; ++i)
            {
                if (array[i]->getKey() == key)
                {
                    for (int j{ i }; j < size; ++j)
                    {
                        array[j] = array[j + 1];
                    }

                    delete array[--size];

                    return;
                }
            }
        }
    }

    int getSize()
    {
        return size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void show()
    {
        for (int i{}; i < size; ++i)
        {
            std::cout << "{" << array[i]->getKey() << ", " << array[i]->getValue() << "}    ";
        }
        std::cout << "\n";
    }

    K operator[](T key)
    {
        return find(key);
    }

    Iterator begin()
    {
        if (!isEmpty())
        {
            return Iterator(0, this->array);
        }
        throw T{};
    }

    Iterator end()
    {
        if (!isEmpty())
        {
            return Iterator(size, this->array);
        }
        throw T{};
    }

    ~Map()
    {
        if (array != nullptr)
        {
            for (int i{}; i < size; ++i)
            {
                if (array[i] != nullptr)
                {
                    delete array[i];
                }
            }

            delete[] array;
        }
    }
};

int main()
{
    Map<std::string, int> a;

    a.insert("Yehor", 127);
    a.insert("Nikita", 123);
    a.insert("Polina", 117);
    a.insert("Vova", 142);
    a.insert("Glib", 15);

    for (auto it = a.begin(); it != a.end(); ++it)
    {
        std::cout << it.first << " => " << it.second << "\n";
    }
}