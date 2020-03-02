#ifndef AVLTREE_H
#define AVLTREE_H

#include <memory>

/*
 * AVL Tree Template Container
 * https://en.wikipedia.org/wiki/AVL_tree
 */

template <typename T>
class AvlTree
{
public:
    //Container interface
    AvlTree()
    {
        m_Root = nullptr;
    }

    int size() const
    {
        return _size(m_Root);
    }

    T at(int index)
    {
        if(index >= _size(m_Root))
            throw std::out_of_range("Out of bounds exception");

        int searchIndex = index;
        auto it = m_Root;
        while(true)
        {
            int leftTreeAndNodeSize = _size(it) - _size(it->right) - 1;
            if(searchIndex == leftTreeAndNodeSize)
                return it->key;
            if(searchIndex < leftTreeAndNodeSize && it->left != nullptr){
                it = it->left;
                continue;
            }
            if(searchIndex > leftTreeAndNodeSize && it->right != nullptr)
            {
                searchIndex -= leftTreeAndNodeSize + 1;
                it = it->right;
                continue;
            }
        }
    }

    int find(T&& obj) const
    {
        int foundIndex = 0;
        auto it = m_Root;

        while(it != nullptr)
        {
            if(!(obj < it->key) && !(it->key < obj))
                return foundIndex + _size(it->left);
            if(obj < it->key)
            {
                it = it->left;
            }
            else
            {
                foundIndex += _size(it->left) + 1;
                it = it->right;
            }
        }
        return -1;
    }

    AvlTree<T> split(int index)
    {
        AvlTree<T> splitContainer;
        for(int i = 0; i < index; ++i)
            splitContainer.insert(at(i));

        return splitContainer;
    }

    void insert(T obj)
   {
        m_Root = _insert(m_Root, obj);
   }

    template <class... Args>
    void emplace(Args...args)
    {
        T t(args...);
        insert(t);
    }

private:
    struct Node
    {
        T key;
        std::shared_ptr<Node> left, right;
        int height;
        int size;
        explicit Node(T& t)
        {
            key = t;
            left = right = nullptr;
            height = 1;
            size = 1;
        }
        static std::shared_ptr<Node> make_node(T& key)
        {
            return std::make_shared<Node>(key);
        }
    };

    std::shared_ptr<Node> m_Root;

    //Null-safe getters
    int _height(std::shared_ptr<Node> node) const
    {
        return node == nullptr ? 0 : node->height;
    }

    int _size(std::shared_ptr<Node> node) const
    {
        return node == nullptr ? 0 : node->size;
    }

    int _getBalance(std::shared_ptr<Node> node) const
    {
        return node != nullptr ? _height(node->left) - _height(node->right) : 0;
    }

    //Tree Operations
    std::shared_ptr<Node> _insert(std::shared_ptr<Node> node, T& key) {
        if(node == nullptr)
            return Node::make_node(key);

        if(!(key < node->key) && !(node->key < key)) // key == node->key
            return node;

        if(key < node->key)
            node->left = _insert(node->left, key);
        else
            node->right = _insert(node->right, key);

        node->height = std::max(_height(node->left), _height(node->right)) + 1;
        node->size = _size(node->left) + _size(node->right) + 1;

        int balance = _getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return _rightRotate(node);

        // Right Right Case
        if (balance < -1 && node->right->key < key) // key > node->right->key
            return _leftRotate(node);

        // Left Right Case
        if (balance > 1 && node->left->key < key) // key > node->left->key
        {
            node->left = _leftRotate(node->left);
            return _rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key)
        {
            node->right = _rightRotate(node->right);
            return _leftRotate(node);
        }

        // Return the (unchanged) node pointer
        return node;
    }

    std::shared_ptr<Node> _leftRotate(std::shared_ptr<Node>& node)
    {
        auto y = node->right;
        auto T2 = y->left;

        // Perform rotation
        y->left = node;
        node->right = T2;

        // Update node values
        node->height = std::max(_height(node->left), _height(node->right)) + 1;
        node->size = _size(node->left) + _size(node->right) + 1;

        y->height = std::max(_height(y->left), _height(y->right)) + 1;
        y->size = _size(y->left) + _size(y->right) + 1;

        // Return new root
        return y;
    }

    std::shared_ptr<Node> _rightRotate(std::shared_ptr<Node>& node)
    {
        auto x = node->left;
        auto T2 = x->right;

        // Perform rotation
        x->right = node;
        node->left = T2;

        // Update node values
        node->height = std::max(_height(node->left), _height(node->right)) + 1;
        node->size = _size(node->left) + _size(node->right) + 1;

        x->height = std::max(_height(x->left), _height(x->right)) + 1;
        x->size = _size(x->left) + _size(x->right) + 1;

        // Return new root
        return x;
    }

};


#endif //AVLTREE_H
