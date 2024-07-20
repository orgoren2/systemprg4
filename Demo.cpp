#include <iostream>
#include "tree.hpp"
#include "complex.hpp"

using namespace std;
using namespace ariel;

int main()
{
    Tree<Complex,2> complexTree;
    Complex root(1, 2);
    Complex child1(2, 4);
    Complex child2(3, 6);
    Complex child3(4, 7);
    Complex child4(5, 6);
    Complex child5(6, 2);
    Complex child6(7, 6);
    TreeNode<Complex> rootNode (root);
    TreeNode<Complex> node1(child1);
    TreeNode<Complex> node2 (child2);
    TreeNode<Complex> node3(child3);
    TreeNode<Complex> node4 (child4);
    TreeNode<Complex> node5 (child5);
    TreeNode<Complex> node6 (child6);

    complexTree.add_root(rootNode);
    complexTree.add_sub_node(rootNode, node1);
    complexTree.add_sub_node(rootNode, node2);
    complexTree.add_sub_node(node1, node3);
    complexTree.add_sub_node(node1, node4);
    complexTree.add_sub_node(node2, node5);
    complexTree.add_sub_node(node2, node6);

    std::cout << "Pre-Order Traversal: ";
    for (auto it = complexTree.begin_pre_order(); it != complexTree.end_pre_order(); ++it)
    {
        std::cout << *it << ", ";
        
    }
    std::cout << std::endl;

    std::cout << "In-Order Traversal: ";
    for (auto it = complexTree.begin_in_order(); it != complexTree.end_in_order(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

    std::cout << "Post-Order Traversal: ";
    for (auto it = complexTree.begin_post_order(); it != complexTree.end_post_order(); ++it)
    {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;

      // Heap Traversal
    std::cout << "Heap traversal: ";
    for (auto it = complexTree.begin_heap(); it !=complexTree.end_heap(); ++it) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
   


    // Create a general k-ary tree with k = 3
    Tree<int, 3> tree;

    // Create nodes
    TreeNode<int> root1(1);
    TreeNode<int> child_1(2);
    TreeNode<int> child_2(3);
    TreeNode<int> child_3 (4);
    TreeNode<int> child_4 (5);

    // Add nodes to the tree
    tree.add_root(root1);
    tree.add_sub_node(root1,child_1);
    tree.add_sub_node(root1,child_2);
    tree.add_sub_node(child_1, child_3);
    tree.add_sub_node(child_1, child_4);

    /*
            1
           / \
          2   3
         / \
        4   5

*/
    // BFS Traversal
    cout << "BFS traversal: ";
    for (auto it = tree.begin_bfs_scan(); it != tree.end_bfs_scan(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;

    // DFS Traversal
    cout << "DFS traversal: ";
    for (auto it = tree.begin_dfs_scan(); it != tree.end_dfs_scan(); ++it) {
        cout << *it << ", ";
    }
    cout << endl;
    complexTree.displayTreeGUI();
    tree.displayTreeGUI();
   
}
