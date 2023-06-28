#include <iostream>
#include <vector>

template<typename T>
struct TreeNode
{
    T value;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : value{T{}}, left{nullptr}, right{nullptr}{}

    TreeNode(T value) : value{value}, left{ nullptr }, right{ nullptr }{}

    TreeNode(T value, TreeNode* left, TreeNode* right) : value{ value }, left{ left }, right{ right }{}

    ~TreeNode()
    {
        if (left != nullptr) { delete left; }

        if (right != nullptr) { delete right; }
    }
};

template<typename T>
class BinaryTree
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
            std::cout << root->value << " ";
            if (root->right != nullptr)
            {
                showNodeInorder(root->right);
            }
        }
    }

    void showNodePreorder(TreeNode<T>* root)
    {
        if (root != nullptr)
        {
            std::cout << root->value << " ";
            if (root->left != nullptr)
            {
                showNodePreorder(root->left);
            }
            if (root->right != nullptr)
            {
                showNodePreorder(root->right);
            }
        }
    }

    void showNodePostorder(TreeNode<T>* root)
    {
        if (root != nullptr)
        {
            if (root->left != nullptr)
            {
                showNodePostorder(root->left);
            }
            if (root->right != nullptr)
            {
                showNodePostorder(root->right);
            }
            std::cout << root->value << " ";
        }
    }

    void checkHeight(TreeNode<T>* root, std::vector<int>& heights, int curr)
    {
        if (root != nullptr)
        {
            curr++;

            if (root->left != nullptr)
            {
                checkHeight(root->left, heights, curr);
            }
            if (root->right != nullptr)
            {
                checkHeight(root->right, heights, curr);
            }

            if (root->left == nullptr && root->right == nullptr)
            {
                heights.push_back(curr - 1);
            }
        }
    }

    std::vector<int> getHeights()
    {
        std::vector<int> heights;

        this->checkHeight(root, heights, 0);

        return heights;
    }

    void showCurrentLevel(TreeNode<T>* root, int level)
    {
        if (level == 0)
        {
            return;
        }
        if (level == 1)
        {
            std::cout << root->value << " ";
        }
        else
        {
            if (root->left != nullptr) { showCurrentLevel(root->left, level - 1); }
            if (root->right != nullptr) { showCurrentLevel(root->right, level - 1); }
        }
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

    void invertNode(TreeNode<T>* root)
    {
        if (root != nullptr)
        {
            if (root->left != nullptr)
            {
                invertNode(root->left);
            }
            if (root->right != nullptr)
            {
                invertNode(root->right);
            }

            TreeNode<T>* temp = root->right;
            root->right = root->left;
            root->left = temp;
        }
    }

public:
    BinaryTree(T value)
    {
        root = new TreeNode<T>(value);
    }

    void insert(T value)
    {
        TreeNode<T>* temp = this->root;

        while (true)
        {
            if (value < temp->value)
            {
                if (temp->left != nullptr)
                {
                    temp = temp->left;
                }
                else
                {
                    temp->left = new TreeNode<T>(value);
                    return;
                }
            }
            else if (value > temp->value)
            {
                if (temp->right != nullptr)
                {
                    temp = temp->right;
                }
                else
                {
                    temp->right = new TreeNode<T>(value);
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }

    bool find(T value)
    {
        TreeNode<T>* temp = this->root;

        while (temp != nullptr)
        {
            if (value < temp->value)
            {
                temp = temp->left;
            }
            else if (value > temp->value)
            {
                temp = temp->right;
            }
            else
            {
                return true;
            }
        }

        delete temp;

        return false;
    }

    void remove(T value)
    {
        TreeNode<T>* temp = root;
        TreeNode<T>* prev = nullptr;

        while (temp != nullptr)
        {
            if (temp->value == value)
            {
                if (prev == nullptr)
                {
                    if (temp->left == nullptr && temp->right == nullptr)
                    {
                        this->root = nullptr;
                        return;
                    }
                    else if (temp->left == nullptr || temp->right == nullptr)
                    {
                        this->root = root->left != nullptr ? root->left : root->right;
                        return;
                    }
                    else
                    {
                        int min = this->min(root->right);
                        root->value = min;
                        value = min;

                        prev = root;
                        temp = temp->right;
                    }
                }
                else
                {
                    if (temp->left == nullptr && temp->right == nullptr)
                    {
                        this->removeLeafNode(temp, prev);

                        return;
                    }
                    else if (temp->left == nullptr || temp->right == nullptr)
                    {
                        if (prev->value > value) { prev->left = temp->left != nullptr ? temp->left : temp->right; }
                        else { prev->right = temp->left != nullptr ? temp->left : temp->right; }

                        return;
                    }
                    else
                    {
                        int min = this->min(temp->right);
                        temp->value = min;
                        value = min;

                        prev = temp;
                        temp = temp->right;
                    }
                }
            }
            else
            {
                if (temp->value > value)
                {
                    if (temp->left == nullptr) { return; }

                    prev = temp;
                    temp = temp->left;
                }
                else if(temp->value < value)
                {
                    if (temp->right == nullptr) { return; }

                    prev = temp;
                    temp = temp->right;
                }
            }
        }
    }

    void invert()
    {
        this->invertNode(this->root);
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

    int minHeight()
    {
        std::vector<int> heights = this->getHeights();
        
        int min{ heights[0] };

        for (int i{1}; i < heights.size(); ++i)
        {
            if (heights[i] < min)
            {
                min = heights[i];
            }
        }

        return min;
    }

    int maxHeight()
    {
        std::vector<int> heights = this->getHeights();

        int max{ heights[0] };

        for (int i{ 1 }; i < heights.size(); ++i)
        {
            if (heights[i] > max)
            {
                max = heights[i];
            }
        }

        return max;
    }

    void showPreorder()
    {
        showNodePreorder(this->root);

        std::cout << "\n";
    }

    void showInorder()
    {
        showNodeInorder(this->root);

        std::cout << "\n";
    }

    void showPostorder()
    {
        showNodePostorder(this->root);

        std::cout << "\n";
    }

    void showLevelOrder()
    {
        int maxHeight = this->maxHeight();

        for (int i{ 1 }; i <= maxHeight + 1; ++i)
        {
            this->showCurrentLevel(root, i);
            std::cout << "\n";
        }
    }

    TreeNode<T>* getRoot()
    {
        return this->root;
    }

    ~BinaryTree()
    {
        delete root;
    }
};

int main()
{
    BinaryTree<int> tree{12};
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    tree.insert(8);
    tree.insert(11);
    tree.insert(14);
    tree.insert(13);
    tree.insert(17);
    tree.insert(20);
    tree.insert(18);

    tree.showInorder();

    tree.invert();

    tree.showInorder();
}
