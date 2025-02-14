#include <iostream>

enum Color {
    RED,
    BLACK
};

template <typename T>
class RedBlackTree {
   private:
    struct Node {
        T data;
        Color color;
        Node *parent;
        Node *left;
        Node *right;

        // Consturctor of node
        Node(T value)
            : data(value), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    Node *root;  // Root of the Red-Black Tree

    void rotateLeft(Node *node) {
        Node *child = node->right;  // child node is z node
        // child's left become parent's right
        node->right = child->left;
        if (node->right != nullptr)
            node->right->parent = node;  // complet bi-directional link
        // child takeplace its parent
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;  // z node become the root
        else if (node->parent->left == node)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->left = node;
        node->parent = child;
    }

    void rotateRight(Node *node) {
        Node *child = node->left;  // child node is z node
        // child's right become parent's left
        node->left = child->right;
        if (node->left != nullptr)
            node->left->parent = node;  // complet bi-directional link
        // child takeplace its parent
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;  // z node become the root
        else if (node->parent->left == node)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->right = node;
        node->parent = child;
    }

    void fixInsert(Node *node) {
        Node *uncle = nullptr;
        std::cout << "Current node is " << node->data << std::endl;
        while (node != root && node->parent->parent != nullptr && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    // Case 1: node's uncle is red, recolor its parent, grandparent and uncle
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else if (node == node->parent->right) {
                    // Case 2: node's uncle is black (triangle)
                    node = node->parent;
                    rotateLeft(node);
                } else {
                    // Case 3: node's uncle is black (line)
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    // Case 1: node's uncle is red, recolor its parent, grandparent and uncle
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else if (node == node->parent->left) {
                    // Case 2: node's uncle is black (triangle)
                    node = node->parent;
                    rotateRight(node);
                } else {
                    // Case 3: node's uncle is black (line)
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        // Case 0: node is root, recolor it
        root->color = BLACK;
    }

    void printHelper(Node *root, std::string indent, bool last) {
        if (root != nullptr) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "    ";
            } else {
                std::cout << "L----";
                indent += "|   ";
            }
            std::string sColor = (root->color == RED) ? "R" : "B";
            std::cout << root->data << "(" << sColor << ")" << std::endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

   public:
    RedBlackTree()
        : root(nullptr) {}
    ~RedBlackTree() { std::cout << "Destory the tree..." << std::endl; }

    void insert(T key) {
        Node *node = new Node(key);
        Node *parent = nullptr;
        Node *current = root;
        // Move down to leave
        while (current != nullptr) {
            parent = current;
            if (node->data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        // Connect to the tree
        node->parent = parent;
        if (parent == nullptr) {
            root = node;
        } else if (node->data < parent->data) {
            parent->left = node;
        } else {
            parent->right = node;
        }
        fixInsert(node);
    }

    void printTree() {
        if (root == nullptr) {
            std::cout << "Tree is empty" << std::endl;
        } else {
            printHelper(root, "", true);
        }
    }
};

int main() {
    RedBlackTree<int> rbTree;
    std::cout << "Start..." << std::endl;
    rbTree.insert(8);
    rbTree.insert(5);
    rbTree.insert(15);
    rbTree.insert(12);
    rbTree.insert(19);
    rbTree.insert(9);
    rbTree.insert(13);
    rbTree.insert(23);
    rbTree.insert(10);
    rbTree.printTree();
    return 0;
}