// Id-9115
// Email address- orgoren3146@gmail.com

#include "doctest.h"
#include <string>
#include "tree.hpp"
#include "complex.hpp"
#include <iostream>

using namespace std;
using namespace ariel;
using namespace doctest;

TEST_CASE("Tree add and get root test with complex numbers")
{

    Tree<Complex, 3> tree;
    Complex c1(1, 2);
    TreeNode<Complex> node1 = (c1);
    tree.add_root(node1);
    CHECK((tree.getRoot()->getKey() == c1) == true);

    SUBCASE("Tree add and get root tests with double")
    {
        Tree<double, 3> tree;
        double num = 1.5;
        TreeNode<double> node1 (num);
        tree.add_root(node1);
        CHECK((tree.getRoot()->getKey() == num) == true);
    }
}

TEST_CASE("Tree add and sub root test with complex numbers")
{

    Tree<Complex, 3> tree;
    Complex c1(1, 2);
    TreeNode<Complex> node1 (c1);
    tree.add_root(node1);
    Complex c2(2, 4);
    TreeNode<Complex> node2 (c2);
    tree.add_sub_node(node1, node2);
    CHECK((tree.getRoot()->getChildren()[0]->getKey() == c2) == true);
    CHECK((tree.getRoot()->getChildren()[0]->getKey() == c2) == true);

    SUBCASE("Add sub root when the root has alredy k children")
    {
        Complex c3(2, 3);
        TreeNode<Complex> node3 (c3);
        Complex c4(21, 4);
        TreeNode<Complex> node4 (c4);
        Complex c5(22, 4);
        TreeNode<Complex> node5 (c5);
        tree.add_sub_node(node1, node3);
        tree.add_sub_node(node1, node4);
        // We defined this tree as a tree with 3 children for each node, when we try to add more than 3 children,
        // the function shoudl throw an error
        CHECK_THROWS(tree.add_sub_node(node1, node5));
    }
}

TEST_CASE("Tree add and sub root test with int")
{

    Tree<int, 3> tree;
    int c1 = 1;
    TreeNode<int> node1(c1);
    tree.add_root(node1);
    int c2 = 2;
    TreeNode<int> node2(c2);
    tree.add_sub_node(node1, node2);
    CHECK((tree.getRoot()->getChildren()[0]->getKey() == c2) == true);

    SUBCASE("Add sub root when the root has alredy k children")
    {
        int c3 = 3;
        TreeNode<int> node3 (c3);
        int c4 = 4;
        TreeNode<int> node4(c4);
        int c5 = 5;
        TreeNode<int> node5(c5);
        tree.add_sub_node(node1, node3);
        tree.add_sub_node(node1, node4);
        // We defined this tree as a tree with 3 children for each node, when we try to add more than 3 children,
        // the function shoudl throw an error
        CHECK_THROWS(tree.add_sub_node(node1, node5));
    }
}

TEST_CASE("Tree node getters and setters with complex variable tests")
{
    
    // Get key test
    Complex c1(1, 2);
    TreeNode<Complex> root(c1);
    CHECK((root.getKey().getReal() == 1) == true);
    CHECK((root.getKey().getImaginary() == 2) == true);

    SUBCASE("Get and add child")
    {
       
        Complex c2(2, 6);
        TreeNode<Complex> child(c2);
        root.addChild(child);
        CHECK((root.getChildren()[0]->getKey().getReal() == c2.getReal()) == true);
        CHECK((root.getChildren()[0]->getKey().getImaginary() == c2.getImaginary()) == true);
    }
}

TEST_CASE("Tree node getters and setters with string variable tests")
{
    // Get key test
    string s = "Hello";
    TreeNode<string> root(s);
    CHECK((root.getKey() == "Hello") == true);

    SUBCASE("Get and add child")
    {
        string name = "Or";
        TreeNode<string> child(name);
        root.addChild(child);
        CHECK((root.getChildren()[0]->getKey() == "Or") == true);
    }
}

TEST_CASE("Tree iterators test")
{
    
    Tree<int, 3> tree;
    TreeNode<int> root (1);
    TreeNode<int> child1 (2);
    TreeNode<int> child2(3);
    TreeNode<int> child3 (4);
    TreeNode<int> child4 (5);
    TreeNode<int> child5 (6);
    TreeNode<int> child6(7);
    TreeNode<int> child7 (8);
    TreeNode<int> child8(9);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(root, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child1, child5);
    tree.add_sub_node(child2, child6);
    tree.add_sub_node(child3, child7);
    tree.add_sub_node(child3, child8);

    /* The tree should look that way:

                        1
                     /  |  \
                    /   |   \
                   2    3    4
                 /  \   |   / \
                5    6  7  8   9


    */

    // Bfs iterator test
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }

    SUBCASE("Dfs iterator test")
    {
     
        int expected[] = {1, 2, 5, 6, 3, 7, 4, 8, 9};
        int i = 0;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            // cout<<*node<<endl;
            i++;
        }
    }

    SUBCASE("in order iterator test on regular tree")
    {
    int expected[] = {1, 2, 5, 6, 3, 7, 4, 8, 9};
    int i = 0;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
    
        CHECK((*node == expected[i]) == true);
        i++;
    }
    
    }

    SUBCASE("pre order iterator test on regular tree")
    {

    int expected[] = {1, 2, 5, 6, 3, 7, 4, 8, 9};
    int i = 0;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }
    }
    SUBCASE("post order iterator test on regular tree")
    {

    int expected[] = {1, 2, 5, 6, 3, 7, 4, 8, 9};
    int i = 0;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }
    }
}

TEST_CASE("Tree iterators test")
{
    Tree<int, 4> tree;
    TreeNode<int> root (1);
    TreeNode<int> child1 (2);
    TreeNode<int> child2 (3);
    TreeNode<int> child3 (4);
    TreeNode<int> child4 (5);
    TreeNode<int> child5 (6);
    TreeNode<int> child6 (7);
    TreeNode<int> child7 (8);
    TreeNode<int> child8 (9);
    tree.add_root(root);
    tree.add_sub_node(root, child1);
    tree.add_sub_node(root, child2);
    tree.add_sub_node(root, child3);
    tree.add_sub_node(child1, child4);
    tree.add_sub_node(child2, child5);
    tree.add_sub_node(child2, child6);
    tree.add_sub_node(child3, child7);
    tree.add_sub_node(child7, child8);

    /* The tree should look that way:

                        1
                     /  |  \
                    /   |   \
                   2    3    4
                   |   / \    \
                   5  6   7    8
                                \
                                 9


    */

    // Bfs iterator test
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }

    SUBCASE("Dfs iterator test")
    {

        int expected[] = {1, 2, 5, 3, 6, 7, 4, 8, 9};
        int i = 0;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            // cout<<*node<<endl;
            i++;
        }
    }
}

TEST_CASE("Binary Tree add and get root test with complex numbers")
{

    Tree<Complex,2> tree;
    Complex c1(1, 2);
    TreeNode<Complex> node1(c1);
    tree.add_root(node1);
    CHECK((tree.getRoot()->getKey().getReal() == c1.getReal()) == true);
    CHECK((tree.getRoot()->getKey().getImaginary() == c1.getImaginary()) == true);

    SUBCASE("Tree add and get root tests with double")
    {
        Tree<double,2> tree;
        double num = 1.5;
        TreeNode<double> node1 (num);
        tree.add_root(node1);
        CHECK((tree.getRoot()->getKey() == num) == true);
    }
}

TEST_CASE("Binary tree add sub root test with complex numbers")
{

    Tree<Complex,2> tree;
    Complex c1(1, 2);
    TreeNode<Complex> node1 (c1);
    tree.add_root(node1);
    Complex c2(2, 4);
    TreeNode<Complex> node2 (c2);
    Complex c3(2, 3);
    TreeNode<Complex> node3 (c3);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node1, node3);
    CHECK((tree.getRoot()->getChildren()[0]->getKey().getReal() == c2.getReal()) == true);
    CHECK((tree.getRoot()->getChildren()[0]->getKey().getImaginary() == c2.getImaginary()) == true);
    CHECK((tree.getRoot()->getChildren()[1]->getKey().getReal() == c3.getReal()) == true);
    CHECK((tree.getRoot()->getChildren()[1]->getKey().getImaginary() == c3.getImaginary()) == true);

    SUBCASE("Add sub root when the root has alredy 2 children")
    {

        Complex c4(21, 4);
        TreeNode<Complex> node4 (c4);
        // Binary tree can have at most two children, if we try to add more than two children,
        // the function will throw an exception
        CHECK_THROWS(tree.add_sub_node(node1, node4));
    }
}

TEST_CASE("Binary tree add and sub root test with int")
{

    Tree<int,2> tree;
    int c1 = 1;
    TreeNode<int> node1 (c1);
    tree.add_root(node1);
    int c2 = 2;
    TreeNode<int> node2(c2);
    int c3 = 3;
    TreeNode<int> node3(c3);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node1, node3);
    CHECK((tree.getRoot()->getChildren()[0]->getKey() == c2) == true);
    CHECK((tree.getRoot()->getChildren()[1]->getKey() == c3) == true);

    SUBCASE("Add sub root when the root has alredy 2 children")
    {
        int c4 = 4;
        TreeNode<int> node4 (c4);
        // Binary tree can have at most two children, if we try to add more than two children,
        // the function will throw an exception
        CHECK_THROWS(tree.add_sub_node(node1, node4));
    }
}

TEST_CASE("Binary tree itrerators tests")
{
    // Pre order test
    Tree<int,2> tree;
    int c1 = 1;
    TreeNode<int> node1 (c1);
    tree.add_root(node1);
    int c2 = 2;
    TreeNode<int> node2 (c2);
    int c3 = 3;
    TreeNode<int> node3 (c3);
    tree.add_root(node1);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node1, node3);

    /* The tree should look that way:
                1
               /  \
              2    3
    */

    int expected[] = {1, 2, 3};
    int i = 0;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }

    SUBCASE("In order test")
    {
        int expected[] = {2, 1, 3};
        int i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("Post order test")
    {
        int expected[] = {2, 3, 1};
        int i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Binary tree itrerators tests")
{
    // Pre order test
    Tree<int,2> tree;
    int c1 = 1;
    TreeNode<int> node1 (c1);
    tree.add_root(node1);
    int c2 = 2;
    TreeNode<int> node2 (c2);
    int c3 = 3;
    TreeNode<int> node3 (c3);
    int c4 = 4;
    TreeNode<int> node4 (c4);
    int c5 = 5;
    TreeNode<int> node5 (c5);
    tree.add_root(node1);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node1, node3);
    tree.add_sub_node(node2, node4);
    tree.add_sub_node(node2, node5);

    /* The tree should look that way:
                1
               /  \
              2    3
             / \
            4   5
    */

    int expected[] = {1, 2, 4, 5, 3};
    int i = 0;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }

    SUBCASE("In order test")
    {
        int expected[] = {4, 2, 5, 1, 3};
        int i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("Post order test")
    {
        int expected[] = {4, 5, 2, 3, 1};
        int i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Binary tree itrerators tests")
{
    // Pre order test
    Tree<int,2> tree;
    int c1 = 1;
    TreeNode<int> node1 (c1);
    tree.add_root(node1);
    int c2 = 2;
    TreeNode<int> node2 (c2);
    int c3 = 3;
    TreeNode<int> node3 (c3);
    int c4 = 4;
    TreeNode<int> node4(c4);
    int c5 = 5;
    TreeNode<int> node5 (c5);
    tree.add_root(node1);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node1, node3);
    tree.add_sub_node(node3, node4);
    tree.add_sub_node(node3, node5);

    /* The tree should look that way:
                1
               /  \
              2    3
                  / \
                 4   5
    */
    int expected[] = {1, 2, 3, 4, 5};
    int i = 0;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }

    SUBCASE("In order test")
    {
        int expected[] = {2, 1, 4, 3, 5};
        int i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("Post order test")
    {
        int expected[] = {2, 4, 5, 3, 1};
        int i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Binary tree itrerators tests")
{
    // Pre order test
    Tree<int,2> tree;
    int c1 = 1;
    TreeNode<int> node1 (c1);
    tree.add_root(node1);
    int c2 = 2;
    TreeNode<int> node2 (c2);
    int c3 = 3;
    TreeNode<int> node3 (c3);
    int c4 = 4;
    TreeNode<int> node4 (c4);
    int c5 = 5;
    TreeNode<int> node5 (c5);
    tree.add_root(node1);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node2, node3);
    tree.add_sub_node(node2, node4);
    tree.add_sub_node(node4, node5);

    /* The tree should look that way:
                1
               /  \
                   2
                  / \
                 3   4
                      \
                       5
    */
    int expected[] = {1, 2, 3, 4, 5};
    int i = 0;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }

    SUBCASE("In order test")
    {
        int expected[] = {3, 2, 5, 4, 1};
        int i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("Post order test")
    {
        int expected[] = {3, 5, 4, 2, 1};
        int i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Binary tree itrerators tests")
{
    // Pre order test
    Tree<int,2> tree;
    int c1 = 1;
    TreeNode<int> node1 (c1);
    tree.add_root(node1);
    int c2 = 2;
    TreeNode<int> node2 (c2);
    int c3 = 3;
    TreeNode<int> node3 (c3);
    int c4 = 4;
    TreeNode<int> node4 (c4);
    int c5 = 5;
    TreeNode<int> node5(c5);
    tree.add_root(node1);
    tree.add_sub_node(node1, node2);
    tree.add_sub_node(node2, node3);
    tree.add_sub_node(node3, node4);
    tree.add_sub_node(node3, node5);

    /* The tree should look that way:
                1
               /  \
              2
             / \
            3
           / \
          4   5
    */
    int expected[] = {1, 2, 3, 4, 5};
    int i = 0;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }

    SUBCASE("In order test")
    {
        int expected[] = {4, 3, 5, 2, 1};
        int i = 0;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }

    SUBCASE("Post order test")
    {
        int expected[] = {4, 5, 3, 2, 1};
        int i = 0;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}

TEST_CASE("Binary tree heap iterator tests")
{
    Tree<int,2> intTree;
    int root = 55;
    int leftChild = 0;
    int rightChild = -7;
    TreeNode<int> rootNode (root);
    TreeNode<int> leftNode (leftChild);
    TreeNode<int> rightNode(rightChild);

    intTree.add_root(rootNode);
    intTree.add_sub_node(rootNode, leftNode);
    intTree.add_sub_node(rootNode, rightNode);

    /* The tree should look that way:
              55
             /  \
            0    -7

*/
    int expected[] = {-7, 0, 55};
    int i = 0;
    // Heap Traversal
    for (auto node = intTree.begin_heap(); node != intTree.end_heap(); ++node)
    {
        CHECK((*node == expected[i]) == true);
        i++;
    }

    SUBCASE("Binary tree heap iterator tests")
    {
        Tree<int,2> intTree;
        int root = 100;
        int leftChild = 2;
        int rightChild = -9;
        int leftChild1 = 17;
        int rightChild1 = 87;
        int leftChild2 = 0;
        int rightChild2 = -3;
        TreeNode<int> rootNode (root);
        TreeNode<int> leftNode (leftChild);
        TreeNode<int> rightNode (rightChild);
        TreeNode<int> leftNode1 = (leftChild1);
        TreeNode<int> rightNode1 = (rightChild1);
        TreeNode<int> leftNode2 = (leftChild2);
        TreeNode<int> rightNode2 =(rightChild2);

        intTree.add_root(rootNode);
        intTree.add_sub_node(rootNode, leftNode);
        intTree.add_sub_node(rootNode, rightNode);
        intTree.add_sub_node(leftNode, leftNode1);
        intTree.add_sub_node(leftNode, rightNode1);
        intTree.add_sub_node(rightNode, leftNode2);
        intTree.add_sub_node(rightNode, rightNode2);

        /* The tree should look that way:
                  100
                 /   \
                2     -9
               / \    / \
              17  87 0   -3
  */
        int expected[] = {-9, -3, 0, 2, 17, 87, 100};
        int i = 0;
        // Heap Traversal
        for (auto node = intTree.begin_heap(); node != intTree.end_heap(); ++node)
        {
            CHECK((*node == expected[i]) == true);
            i++;
        }
    }
}


TEST_CASE("Complex getters tests")
{
    Complex c1(1, 2);
    CHECK((c1.getReal() == 1) == true);
    CHECK((c1.getImaginary() == 2) == true);
}

TEST_CASE("Complex operators tests"){
    //== and != operators
    Complex c(1,2);
    Complex c1(1,2);
    Complex c2(2,2);
    Complex c3(2,3);
    CHECK((c==c1)==true);
    CHECK((c1!=c2)==true);

    SUBCASE(" '>' operator test"){
        CHECK((c>c1)==false);
        CHECK((c1>c2)==false);
        CHECK((c2>c1)==true);
        CHECK((c3>c2)==true);

    }
}