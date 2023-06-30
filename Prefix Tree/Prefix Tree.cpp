#include <iostream>
#include <vector>

struct Node
{
    char symbol;
    Node** childrens;
    bool isEnd;

    Node() : symbol{ ' ' }, isEnd{ false }, childrens{ new Node * [26]{nullptr} }{}

    Node(char symbol) : symbol{ symbol }, isEnd{ false }, childrens{ new Node* [26]{nullptr} }{}

    void setFlag()
    {
        this->isEnd = true;
    }

    void addChildren(char symbol)
    {
        childrens[symbol - 'a'] = new Node(symbol);
    }

    ~Node()
    {
        if (childrens != nullptr)
        {
            for (int i{}; i < 26; ++i)
            {
                if (childrens[i] != nullptr)
                {
                    delete childrens[i];
                }
            }

            delete[] childrens;
        }
    }
};

class PrefixTree
{
private:
    Node* root;

    void checkWordsForPrefix(std::string prefix, std::vector<std::string>& result, Node* temp)
    {
        if (temp->isEnd)
        {
            result.push_back(prefix);
        }

        for (int i{}; i < 26; ++i)
        {
            if (temp->childrens[i] != nullptr)
            {
                this->checkWordsForPrefix(prefix + temp->childrens[i]->symbol, result, temp->childrens[i]);
            }
        }
    }

public:
    PrefixTree()
    {
        root = new Node(' ');
    }

    void addWord(std::string word)
    {
        if (root != nullptr)
        {
            Node* temp = root;

            for (int i{}; i < word.length(); ++i)
            {
                if (temp->childrens[word[i] - 'a'] == nullptr)
                {
                    temp->addChildren(word[i]);
                }

                temp = temp->childrens[word[i] - 'a'];
            }

            temp->setFlag();
        }
    }

    bool findWord(std::string word)
    {
        if (root != nullptr)
        {
            Node* temp = root;

            for (int i{}; i < word.length(); ++i)
            {
                if (temp->childrens[word[i] - 'a'] == nullptr)
                {
                    return false;
                }

                temp = temp->childrens[word[i] - 'a'];
            }

            return temp->isEnd;
        }
    }

    std::vector<std::string> findWordsByPrefix(std::string prefix)
    {
        if (root != nullptr)
        {
            std::vector<std::string> result;
            
            Node* temp = root;

            for (int i{}; i < prefix.length(); ++i)
            {
                if (temp->childrens[prefix[i] - 'a'] == nullptr)
                {
                    return result;
                }

                temp = temp->childrens[prefix[i] - 'a'];
            }

            this->checkWordsForPrefix(prefix, result, temp);

            return result;
        }
    }

    ~PrefixTree()
    {
        delete root;
    }
};

int main()
{
    PrefixTree a;
    a.addWord("aboba");
    a.addWord("aboard");
    a.addWord("abolish");
    a.addWord("abort");
    a.addWord("abound");
    a.addWord("about");

    std::vector<std::string> wordsABO = a.findWordsByPrefix("abo");
    std::vector<std::string> wordsABOU = a.findWordsByPrefix("abou");

    for (int i{}; i < wordsABO.size(); ++i)
    {
        std::cout << wordsABO[i] << "   ";
    }
    std::cout << "\n";

    for (int i{}; i < wordsABOU.size(); ++i)
    {
        std::cout << wordsABOU[i] << "   ";
    }
    std::cout << "\n";
}