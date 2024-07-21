#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "TreeNode.hpp"
#include "TreeGUI.hpp"

namespace ariel
{
    // The Tree class template represents a generic k-ary tree
    template <typename T, size_t K>
    class Tree
    {
    private:
        TreeNode<T> *root;

    public:
        Tree() : root(nullptr) {}

        // Set the root of the tree
        void add_root(TreeNode<T> &root)
        {
            this->root = &root;
        }

        // Get the root of the tree
        TreeNode<T> *getRoot() const
        {
            return this->root;
        }

        // Add a child to a parent node
        void add_sub_node(TreeNode<T> &parent, TreeNode<T> &child)
        {
            // If the parent has already K children, throw an exception
            if (parent.getChildren().size() >= K)
            {
                throw std::invalid_argument("This node has already " + std::to_string(K) + " children");
            }
            else
            {
                parent.addChild(child);
            }
        }

        void displayTreeGUI()
        {
            // Display the tree using GUI
            TreeGUI<T> treeGUI(root);
            treeGUI.display();
        }

        // BFS Iterator class for traversing the tree using BFS
        class BFSIterator
        {
        private:
            std::queue<TreeNode<T> *> queue;

        public:
            BFSIterator(TreeNode<T> *root)
            {
                if (root)
                {
                    queue.push(root);
                }
            }

            // * operator to access the key of the current node
            T operator*() const
            {
                // Return the value of the current node
                return queue.front()->getKey();
            }

            // Increment operator to move to the next node in BFS
            BFSIterator &operator++()
            {
                TreeNode<T> *node = queue.front();
                queue.pop();
                // Insert all the children of the current node to the queue
                for (auto child : node->getChildren())
                {
                    queue.push(child);
                }
                // Return the updated iterator
                return *this;
            }

            // Inequality operator to compare iterators
            bool operator!=(const BFSIterator &other) const
            {
                return !queue.empty() || !other.queue.empty();
            }
        };

        BFSIterator begin_bfs_scan()
        {
            return BFSIterator(root);
        }

        BFSIterator end_bfs_scan()
        {
            return BFSIterator(nullptr);
        }

        // DFS Iterator class for traversing the tree using DFS
        class DFSIterator
        {
        private:
            std::stack<TreeNode<T> *> stack;

        public:
            DFSIterator(TreeNode<T> *root)
            {
                if (root)
                {
                    stack.push(root);
                }
            }

            // * operator to access the key of the current node
            T operator*() const
            {
                return stack.top()->getKey();
            }

            // Increment operator to move to the next node in DFS
            DFSIterator &operator++()
            {
                // Get the top node from the stack
                TreeNode<T> *node = stack.top();
                // Remove the top node from the stack
                stack.pop();
                // Push all children of the current node onto the stack in reverse order
                for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it)
                {
                    stack.push(*it);
                }
                // Return the updated iterator
                return *this;
            }

            // Inequality operator to compare iterators
            bool operator!=(const DFSIterator &other) const
            {
                return !stack.empty() || !other.stack.empty();
            }
        };

        DFSIterator begin_dfs_scan()
        {
            return DFSIterator(root);
        }

        DFSIterator end_dfs_scan()
        {
            return DFSIterator(nullptr);
        }

        // Pre-Order Iterator class
        class PreOrderIterator
        {
        private:
            std::stack<TreeNode<T> *> stack;

        public:
            PreOrderIterator(TreeNode<T> *root)
            {
                if (root)
                {
                    stack.push(root);
                }
            }

            // * operator to access the key of the current node
            T operator*() const
            {
                return stack.top()->getKey();
            }

            // Increment operator to move to the next node in pre-order(root,left,right)
            PreOrderIterator &operator++()
            {
                if (K == 2)
                {
                    TreeNode<T> *node = stack.top();
                    stack.pop();
                    auto children = node->getChildren();
                    for (auto it = children.rbegin(); it != children.rend(); ++it)
                    {
                        stack.push(*it);
                    }
                }
                // Else if the tree is not binary tree, return dfs iterator
                else
                {
                    // Get the top node from the stack
                    TreeNode<T> *node = stack.top();
                    // Remove the top node from the stack
                    stack.pop();
                    // Push all children of the current node onto the stack in reverse order
                    for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it)
                    {
                        stack.push(*it);
                    }
                    // Return the updated iterator
                }
                return *this;
            }

            // Inequality operator to compare iterators
            bool operator!=(const PreOrderIterator &other) const
            {
                return !stack.empty() || !other.stack.empty();
            }
        };

        PreOrderIterator begin_pre_order()
        {

            return PreOrderIterator(root);
        }

        PreOrderIterator end_pre_order()
        {
            return PreOrderIterator(nullptr);
        }

        // In-Order Iterator class
        class InOrderIterator
        {
        private:
            std::stack<TreeNode<T> *> stack;

            // Helper function to push all left children of a node onto the stack
            void pushLeft(TreeNode<T> *node)
            {
                while (node)
                {
                    stack.push(node); // Push current node onto stack
                    if (!node->getChildren().empty())
                    {
                        node = node->getChildren()[0]; // Move to the left child
                    }
                    else
                    {
                        node = nullptr; // No left child, stop
                    }
                }
            }

        public:
            // Constructor initializes the iterator with the root
            InOrderIterator(TreeNode<T> *root)
            {
                if (K == 2)
                {
                    pushLeft(root);
                }

                else if (root)
                {
                    stack.push(root);
                }
            }

            // * operator to access the key of the current node
            T operator*() const
            {
                return stack.top()->getKey();
            }

            // Increment operator to move to the next node in in-order (left, root, right)
            InOrderIterator &operator++()
            {
                if (K == 2)
                {
                    TreeNode<T> *node = stack.top();
                    stack.pop(); // Remove the top node
                    // If the node has a right child, call push left on the right child node
                    if (node->getChildren().size() > 1)
                    {
                        pushLeft(node->getChildren()[1]); // Push all left children of the right child
                    }
                }
                else
                {
                    TreeNode<T> *node = stack.top();
                    stack.pop(); // Remove the top node
                    for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it)
                    {
                        stack.push(*it); // Push all children in reverse order
                    }
                }
                return *this;
            }

            // Inequality operator to compare iterators
            bool operator!=(const InOrderIterator &other) const
            {
                return !stack.empty() || !other.stack.empty(); // Check if either stack is not empty
            }
        };

        // Begin and end methods for in-order traversal
        InOrderIterator begin_in_order()
        {
            return InOrderIterator(root); // Create an iterator starting from the root
        }

        InOrderIterator end_in_order()
        {
            return InOrderIterator(nullptr); // Create an iterator representing the end
        }
// Post-Order Iterator class
class PostOrderIterator {
private:
    std::stack<TreeNode<T>*> stack1, stack2; // Two stacks used for post-order traversal

public:
    // Constructor initializes the iterator with the root
    PostOrderIterator(TreeNode<T>* root) {
        if (root) {
            if (K != 2) {
                // For non-binary trees, initialize stack2 with root
                stack2.push(root);
            } else {
                // For binary trees, use two stacks to simulate post-order traversal
                stack1.push(root);
                while (!stack1.empty()) {
                    TreeNode<T>* node = stack1.top();
                    stack1.pop();
                    stack2.push(node);
                    // Push left and right children to stack1
                    if (node->getChildren().size() > 0 && node->getChildren()[0]) {
                        stack1.push(node->getChildren()[0]);
                    }
                    if (node->getChildren().size() > 1 && node->getChildren()[1]) {
                        stack1.push(node->getChildren()[1]);
                    }
                }
            }
        }
    }

    // * operator to access the key of the current node
    T operator*() const {
        return stack2.top()->getKey(); // Return the key of the top node in stack2
    }

    // Increment operator to move to the next node in post-order (left, right, root)
    PostOrderIterator& operator++() {
        if (K == 2) {
            // For binary trees, simply pop the top node from stack2
            stack2.pop();
            return *this;
        }

        // For non-binary trees
        // Get the top node from the stack
        TreeNode<T>* node = stack2.top();
        // Remove the top node from the stack
        stack2.pop();
        // Push all children of the current node onto the stack in reverse order
        for (auto it = node->getChildren().rbegin(); it != node->getChildren().rend(); ++it) {
            stack2.push(*it);
        }
        // Return the updated iterator
        return *this;
    }

    // Inequality operator to compare iterators
    bool operator!=(const PostOrderIterator& other) const {
        return !stack2.empty() || !other.stack2.empty(); // Iterators are different if either stack is non-empty
    }
};

// Begin and end methods for post-order traversal
PostOrderIterator begin_post_order() {
    return PostOrderIterator(root); // Return iterator starting at root
}

PostOrderIterator end_post_order() {
    return PostOrderIterator(nullptr); // Return iterator representing the end
}


        // Heap Iterator class (min-heap)
class HeapIterator {
private:
    std::vector<TreeNode<T>*> heap; // Vector to store the heap elements

public:
    // Constructor initializes the iterator with the root
    HeapIterator(TreeNode<T>* root) {
        if (root) {
            createHeap(root); // Create a min-heap from the binary tree starting at root
        }
    }

    // Method to create a min-heap from the binary tree
    void createHeap(TreeNode<T>* root) {
        std::queue<TreeNode<T>*> q; // Queue for level-order traversal
        q.push(root);
        while (!q.empty()) {
            TreeNode<T>* node = q.front();
            q.pop();
            heap.push_back(node); // Add node to the heap vector
            // Push left and right children to the queue
            if (node->getChildren().size() > 0 && node->getChildren()[0]) {
                q.push(node->getChildren()[0]);
            }
            if (node->getChildren().size() > 1 && node->getChildren()[1]) {
                q.push(node->getChildren()[1]);
            }
        }
        // Convert the vector into a min-heap
        std::make_heap(heap.begin(), heap.end(), [](TreeNode<T>* a, TreeNode<T>* b) {
            return a->getKey() > b->getKey(); // Comparison function for min-heap
        });
    }

    // * operator to access the key of the current node
    T operator*() const {
        return heap.front()->getKey(); // Return the key of the root of the heap
    }

    // Increment operator to move to the next node in the heap
    HeapIterator& operator++() {
        // Remove the root of the heap
        std::pop_heap(heap.begin(), heap.end(), [](TreeNode<T>* a, TreeNode<T>* b) {
            return a->getKey() > b->getKey(); // Comparison function for min-heap
        });
        heap.pop_back(); // Remove the last element (new root after pop_heap)
        return *this;
    }

    // Inequality operator to compare iterators
    bool operator!=(const HeapIterator& other) const {
        // Iterators are different if either heap is non-empty
        return !heap.empty() || !other.heap.empty();
    }
};

// Begin and end methods for heap traversal
HeapIterator begin_heap() {
    return HeapIterator(root); // Return iterator starting at root
}

HeapIterator end_heap() {
    return HeapIterator(nullptr); // Return iterator representing the end
}
};

} // namespace ariel

#endif // TREE_HPP
