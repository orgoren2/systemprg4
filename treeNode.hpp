// treeNode.hpp
#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <iostream>
#include <vector>

namespace ariel
{
    template <typename T>
    class TreeNode
    {
    private:
        T key;
        std::vector<TreeNode<T> *> children;

    public:
        TreeNode(const T &key) : key(key) {}
   
        T getKey() const
        {
            return key;
        }

        const std::vector<TreeNode<T> *> &getChildren() const
        {
            return children;
        }

        void addChild(TreeNode<T> &child)
        {
            children.push_back(&child);
        }
    };
}
#endif // TREENODE_HPP
