#include <iostream>

template<typename T>
struct TreeNode
{
    T value;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode() : value{ T{} }, left{ nullptr }, right{ nullptr }, height{ 0 }{}

    TreeNode(T value) : value{ value }, left{ nullptr }, right{ nullptr }, height{ 1 }{}

    TreeNode(T value, TreeNode* left, TreeNode* right) : value{ value }, left{ left }, right{ right }, height{ 1 }{}

    TreeNode<T>& operator= (const TreeNode<T>& node)
    {
        this->value = node.value;
        this->left = node.left;
        this->right = node.right;
        this->height = node.height;

        return *this;
    }

    void changeHeight()
    {
        int h1 = this->left != nullptr ? this->left->height : 0;
        int h2 = this->right != nullptr ? this->right->height : 0;

        this->height = h1 >= h2 ? h1 : h2;
        this->height++;
    }

    int getDifference()
    {
        int h1 = this->left != nullptr ? this->left->height : 0;
        int h2 = this->right != nullptr ? this->right->height : 0;

        return h1 - h2;
    }

    ~TreeNode()
    {
        if (left != nullptr) { delete left; }

        if (right != nullptr) { delete right; }
    }
};

template<typename T>
class AVLTree
{
private:
    TreeNode<T>* root;

    void showNodeInorder(TreeNode<T>* root)
    {
        if (root != nullptr)
        {
            if (root->left != nullptr)
            {
                showNodeInorder(root->left);
            }
            std::cout << root->value << " " << root->height << "\n";
            if (root->right != nullptr)
            {
                showNodeInorder(root->right);
            }
        }
    }

    TreeNode<T>* balanceNode(TreeNode<T>* temp)
    {
        if (temp->getDifference() == 2)
        {
            if (temp->left->getDifference() < 0)
            {
                temp->left = this->smallLeftRotation(temp->left);
            }
            temp = this->smallRightRotation(temp);
        }
        else if (temp->getDifference() == -2)
        {
            if (temp->right->getDifference() > 0)
            {
                temp->right = this->smallRightRotation(temp->right);
            }
            temp = this->smallLeftRotation(temp);
        }

        temp->changeHeight();

        return temp;
    }

    TreeNode<T>* insertNode(TreeNode<T>* temp, T value)
    {
        if (temp->value > value)
        {
            if (temp->left == nullptr)
            {
                temp->left = new TreeNode<T>(value);
            }
            else
            {
                temp->left = insertNode(temp->left, value);
            }
        }
        else
        {
            if (temp->right == nullptr)
            {
                temp->right = new TreeNode<T>(value);
            }
            else
            {
                temp->right = insertNode(temp->right, value);
            }
        }

        temp->changeHeight();

        temp = this->balanceNode(temp);

        return temp;
    }

    TreeNode<T>* removeNode(TreeNode<T>* temp, TreeNode<T>* prev, T value)
    {
        if (temp != nullptr)
        {
            if (temp->value == value)
            {
                if (temp->left == nullptr && temp->right == nullptr)
                {
                    if (prev != nullptr) { this->removeLeafNode(temp, prev); }

                    return nullptr;
                }
                else if (temp->left == nullptr || temp->right == nullptr)
                {
                    if (prev == nullptr) { return root->left != nullptr ? root->left : root->right; }

                    if (prev->value > value) { prev->left = temp->left != nullptr ? temp->left : temp->right; }
                    else { prev->right = temp->left != nullptr ? temp->left : temp->right; }

                    return prev->value > value ? prev->left : prev->right;
                }
                else
                {
                    temp->value = this->min(temp->right);

                    temp->right = this->removeNode(temp->right, temp, temp->value);
                }
            }
            else
            {
                if (temp->value > value)
                {
                    if (temp->left == nullptr) { return temp; }

                    temp->left = this->removeNode(temp->left, temp, value);
                }
                else if (temp->value < value)
                {
                    if (temp->right == nullptr) { return temp; }

                    temp->right = this->removeNode(temp->right, temp, value);
                }
            }

            return this->balanceNode(temp);
        }

        return nullptr;
    }

    TreeNode<T>* smallLeftRotation(TreeNode<T>* root)
    {
        TreeNode<T>* temp = root->right;
        root->right = temp->left;
        temp->left = root;

        root->changeHeight();
        temp->changeHeight();

        return temp;
    }

    TreeNode<T>* smallRightRotation(TreeNode<T>* root)
    {
        TreeNode<T>* temp = root->left;
        root->left = temp->right;
        temp->right = root;

        root->changeHeight();
        temp->changeHeight();

        return temp;
    }

    void removeLeafNode(TreeNode<T>* temp, TreeNode<T>* prev)
    {
        if (prev->left == temp)
        {
            delete prev->left;
            prev->left = nullptr;
        }
        else
        {
            delete prev->right;
            prev->right = nullptr;
        }
    }


public:
    AVLTree(T value)
    {
        root = new TreeNode<T>(value);
    }

    void insert(T value)
    {
        if (this->root == nullptr)
        {
            this->root = new TreeNode<T>{ value };
        }
        else
        {
            this->root = insertNode(root, value);
        }
    }

    void remove(T value)
    {
        this->root = this->removeNode(this->root, nullptr, value);
    }

    T min()
    {
        TreeNode<T>* temp = new TreeNode<T>();

        temp = root;

        while (temp->left != nullptr)
        {
            temp = temp->left;
        }

        return temp->value;
    }

    T min(TreeNode<T>* temp)
    {
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }

        return temp->value;
    }

    T max()
    {
        TreeNode<T>* temp = new TreeNode<T>();

        temp = root;

        while (temp->right != nullptr)
        {
            temp = temp->right;
        }

        return temp->value;
    }

    T max(TreeNode<T>* temp)
    {
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }

        return temp->value;
    }

    void show()
    {
        this->showNodeInorder(root);
        std::cout << "\n\n\n";
    }

    ~AVLTree()
    {
        if (this->root != nullptr) { delete root; }
    }
};

int main()
{
    AVLTree<int> a{ 13 };

    a.insert(8);
    a.insert(18);
    a.insert(5);
    a.insert(11);
    a.insert(20);
    a.insert(3);
    a.insert(16);
    a.insert(17);
    a.insert(10);
    a.insert(12);
    a.show();

    a.remove(13);
    a.remove(16);
    a.remove(17);
    a.remove(8);
    a.remove(10);
    a.remove(11);
    a.remove(12);
    a.remove(18);
    a.remove(5);
    a.remove(20);
    a.remove(3);
    a.remove(5);
    a.remove(5);
    a.remove(5);
    a.remove(5);

    a.insert(2);
    a.show();
}
