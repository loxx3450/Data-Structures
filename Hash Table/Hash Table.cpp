#include <iostream>

template <typename T>
struct Node
{
    std::string key;
    T value;
    bool deleted;

    Node(std::string key, T value) : key{ key }, value { value }, deleted{ false }{}

    Node(Node* other) : key{ other->key }, value{ other->value }, deleted{ other->deleted }{}
};

template <typename T>
class HashTable
{
private:
    int size;
    int buffer_size;
    int deleted_elements;
    static double rehash_factor;
    Node<T>** array;

    int getHash(std::string key, int size, int mod)
    {
        int result{};

        for (int i{}; i < key.length(); ++i)
        {
            result = (mod * result + key[i]) % size;
        }

        result *= 2;

        return ++result;
    }

    int getIndex(std::string key)
    {
        return this->getHash(key, buffer_size, buffer_size + 1) % buffer_size;
    }

    int getStep(std::string key)
    {
        return this->getHash(key, buffer_size, buffer_size - 1) % buffer_size;
    }

    void deleteArray(Node<T>** array, int size)
    {
        for (int i{}; i < size; ++i)
        {
            if (array[i] != nullptr) { delete array[i]; }
        }

        delete[] array;
    }

    void reallocateMemory(int last_buffer)
    {
        this->size = 0;

        Node<T>** temp = new Node<T>*[last_buffer];

        for (int i{}; i < last_buffer; ++i)
        {
            if (this->array[i] != nullptr) { temp[i] = new Node<T>{ this->array[i] }; }
            else { temp[i] = nullptr; }
        }

        this->deleteArray(array, last_buffer);

        array = new Node<T>*[this->buffer_size];
        for (int i{}; i < buffer_size; ++i) { array[i] = nullptr; }

        for (int i{}; i < last_buffer; ++i)
        {
            if (temp[i] != nullptr && temp[i]->deleted == false) { this->add(temp[i]->key, temp[i]->value); }
        }

        this->deleteArray(temp, last_buffer);
    }

    void resize()
    {
        int last_buffer = this->buffer_size;
        this->buffer_size *= 2;

        this->reallocateMemory(last_buffer);
    }   

    void rehash()
    {
        this->deleted_elements = 0;

        this->reallocateMemory(this->buffer_size);
    }

public:
    HashTable()
    {
        buffer_size = 8;
        deleted_elements = 0;
        size = 0;
        array = new Node<T>*[buffer_size];

        for (int i{}; i < buffer_size; ++i) { array[i] = nullptr; }
    }

    bool find(std::string key)
    {
        int index = this->getIndex(key);
        int step = this->getStep(key);

        if (array[index] != nullptr)
        {
            if (array[index]->key != key)
            {
                for (int i{}; i < buffer_size; ++i)
                {
                    index = (index + step) % buffer_size;

                    if (array[index] == nullptr) { return false; }
                    else if (array[index]->key == key && array[index]->deleted == false) { return true; }
                }
            }

            return true;
        }

        return false;
    }

    void add(std::string key, T value)
    {
        int index = this->getIndex(key);
        int step = this->getStep(key);

        int deleted_index{ -1 };

        for (int i{}; i < buffer_size; ++i) 
        {
            if (array[index] == nullptr) { break; }
            else if (array[index]->key == key && array[index]->deleted == false) { return; }
            else if (array[index]->deleted == true && deleted_index == -1) { deleted_index = index; }

            index = (index + step) % buffer_size;
        }

        if (deleted_index == -1)
        {
            array[index] = new Node<T>(key, value);
        }
        else
        {
            delete array[deleted_index];
            array[deleted_index] = new Node<T>(key, value);
        }

        ++size;

        if (size == buffer_size * 0.75)
        {
            this->resize();
        }
        if (deleted_elements >= buffer_size / 2)
        {
            this->rehash();
        }
    }

    bool remove(std::string key)
    {
        int index = this->getIndex(key);
        int step = this->getStep(key);

        if (array[index] != nullptr)
        {
            if (array[index]->key != key)
            {
                for (int i{}; i < buffer_size; ++i)
                {
                    index = (index + step) % buffer_size;

                    if (array[index] == nullptr) { return false; }
                    else if (array[index]->key == key && array[index]->deleted == false) { break; }
                }
            }

            array[index]->deleted = true;

            this->deleted_elements++;

            return true;
        }

        return false;
    }

    void show()
    {
        for (int i{}; i < buffer_size; ++i)
        {
            std::cout << i << "        ";
            if (this->array[i] != nullptr && this->array[i]->deleted == false)
            {
                std::cout << this->array[i]->key << "   " << this->array[i]->value;
            }
            std::cout << "\n";
        }
    }

    ~HashTable()
    {
        this->deleteArray(array, buffer_size);
    }
};

template <typename T>
double HashTable<T>::rehash_factor = 0.75;

int main()
{
    HashTable<int> a;
    a.add("Hello", 5);
    a.add("Public", 5);
    a.add("Cat", 5);
    a.add("JUIL", 5);
    a.add("Opa", 5);
    a.add("Vater", 5);
    a.add("Oma", 5);
    a.add("Mutter", 5);
    a.add("Schwester", 5);
    a.add("Bruder", 5);

    a.remove("Cat");
    a.remove("JUIL");
    a.remove("Opa");
    a.remove("Vater");
    a.remove("Oma");
    a.remove("Mutter");
    a.remove("Schwester");
    a.remove("Bruder");

    a.add("rahit", 4);
    a.show();
}