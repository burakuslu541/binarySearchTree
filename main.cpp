#include <iostream>
using namespace std;

template<class T>
class TreeNode
{
public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode(T data = T(), TreeNode<T> *left = NULL, TreeNode<T> *right = NULL) : data(data), left(left), right(right) {}
};
enum MOD
{
    PREORDER,
    INORDER,
    POSTORDER
};
template<class T>
class BinarySearchTree
{
    TreeNode<T> *root;
    TreeNode<T> *insert(TreeNode<T> *start, T data)
    {
        if (start)
        {
            if (data < start->data)
                start->left = insert(start->left, data);
            else
            {
                start->right = insert(start->right, data);
            }
        }
        else
        {
            return new TreeNode<T>(data);
        }
        return start;
    }
    TreeNode<T> *mirror(TreeNode<T> *start)
    {
        if (start)
        {
            mirror(start->left);
            mirror(start->right);
            TreeNode<T> *tmp = start->left;
            start->left = start->right;
            start->right = tmp;
        }
        return start;
    }

public:
    BinarySearchTree(TreeNode<T> *root = NULL) : root(root) {}
    bool isEmpty() const { return root == NULL; }
    TreeNode<T> *getRoot() const { return root; }
    TreeNode<T> *find(TreeNode<T> *start, T data)
    {
        if (start)
        {
            if (data < start->data)
            {
                return find(start->left, data);
            }
            else if (start->data < data)
            {
                return find(start->right, data);
            }
        }

        return start;
    }
    TreeNode<T> *find(T data, bool last = false)
    {
        TreeNode<T> *before = find(root, data);
        TreeNode<T> *after = before;
        if (last)
        {
            while (before && (before = find(before->right, data)))
            {
                after = before;
            }
        }
        return after;
    }

    void insert(T data)
    {
        root = insert(root, data);
    }
    TreeNode<T> *getMin(TreeNode<T> *start)
    {
        while (start && start->left)
        {
            start = start->left;
        }
        return start;
    }
    TreeNode<T> *getMin()
    {
        return getMin(root);
    }
    TreeNode<T> *getMax(TreeNode<T> *start)
    {
        while (start && start->right)
        {
            start = start->right;
        }
        return start;
    }
    TreeNode<T> *getMax()
    {
        return getMax(root);
    }
    TreeNode<T> *remove(TreeNode<T> *start, TreeNode<T> *deleted)
    {
        if (start)
        {
            if (deleted->data < start->data)
                start->left = remove(start->left, deleted);
            else if (start->data < deleted->data)
                start->right = remove(start->right, deleted);
            else if (start == deleted)
            {
                TreeNode<T> *tmp = NULL;
                if (start->left && start->right)
                {
                    tmp = getMin(start->right);
                    remove(start, tmp);
                    tmp->left = start->left;
                    tmp->right = start->right;
                }
                else if (start->left)
                {
                    tmp = start->left;
                }
                else if (start->right)
                {
                    tmp = start->right;
                }
                return tmp;
            }
            else
                start->right = remove(start->right, deleted);
        }
        return start;
    }
    void remove(TreeNode<T> *node)
    {
        if (node)
        {
            root = remove(root, node);
            delete node;
        }
    }
    void remove(T data, bool last = false)
    {
        remove(find(data, last));
    }

    int height(TreeNode<T> *node)
    {
        if (node)
        {
            int left = height(node->left);
            int right = height(node->right);
            return 1 + max(left, right);
        }
        else
        {
            return -1;
        }
    }
    int depth(TreeNode<T> *start, TreeNode<T> *finish)
    {
        if (start)
        {
            if (start == finish)
            {
                return 0;
            }
            int left = depth(start->left, finish);
            int right = depth(start->right, finish);
            return 1 + max(left, right);
        }
        else
        {
            return INT32_MIN;
        }
    }
    int depth(TreeNode<T> *finish)
    {
        return depth(root, finish);
    }
    void preorder(TreeNode<T> *start)
    {
        if (start)
        {
            cout << start->data << " ";
            preorder(start->left);
            preorder(start->right);
        }
    }
    void inorder(TreeNode<T> *start)
    {
        if (start)
        {
            inorder(start->left);
            cout << start->data << " ";
            inorder(start->right);
        }
    }
    void postorder(TreeNode<T> *start)
    {
        if (start)
        {
            postorder(start->left);
            postorder(start->right);
            cout << start->data << " ";
        }
    }
    void print(MOD mod)
    {
        switch (mod)
        {
        case PREORDER:
            preorder(root);
            break;
        case INORDER:
            inorder(root);
            break;
        case POSTORDER:
            postorder(root);
            break;
        }
        if (!isEmpty())
            cout << endl;
    }

    void mirror()
    {
        root = mirror(root);
    }
};

int main()
{
    BinarySearchTree<int> bst;
    cout << bst.isEmpty() << endl;
    bst.insert(20);
    bst.insert(5);
    bst.insert(10);
    bst.insert(15);
    bst.insert(3);
    bst.insert(37);
    bst.insert(30);
    bst.insert(50);
    bst.insert(1);

    cout << bst.isEmpty() << endl;
    cout << "PREORDER: ";
    bst.print(PREORDER);
    cout << "INORDER: ";
    bst.print(INORDER);
    cout << "POSTORDER: ";
    bst.print(POSTORDER);

    cout<<endl;
    cout<<"Mirror: "<<endl;
    bst.mirror();
    cout << "PREORDER: ";
    bst.print(PREORDER);
    cout << "INORDER: ";
    bst.print(INORDER);
    cout << "POSTORDER: ";
    bst.print(POSTORDER);

    return 0;
}