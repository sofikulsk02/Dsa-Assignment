#include <iostream>
using namespace std;

class AVLTree{
private:
    struct Node {
        int key;
        Node *left, *right;
        int height;
        int size;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1), size(1) {}
    };
          Node* root;
              int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }
         int size(Node* N) {
         if (N == nullptr)
            return 0;
             return N->size;
    }
        Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;
        y->height = max(height(y->left),height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->size = size(y->left) + size(y->right) + 1;
        x->size = size(x->left) + size(x->right) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->size = size(x->left) + size(x->right) + 1;
        y->size = size(y->left) + size(y->right) + 1;

        return y;
    }

          int getBalance(Node* N) {
               if (N == nullptr)
            return 0;
         return height(N->left) - height(N->right);
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        node->size = 1 + size(node->left) + size(node->right);

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }
    Node* remove(Node* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = remove(root->left, key);
        else if (key > root->key)
            root->right = remove(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = remove(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));
        root->size = size(root->left) + size(root->right) + 1;

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) 
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) 
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    bool find(Node* root, int key) {
        if (root == nullptr)
            return false;
        if (key == root->key)
            return true;
        if (key < root->key)
            return find(root->left, key);
        return find(root->right, key);
    }

    int order_of_key(Node* node, int key) {
        if (node == nullptr)
            return 0;

        if (key < node->key)
            return order_of_key(node->left, key);
        else if (key > node->key)
            return 1 + size(node->left) + order_of_key(node->right, key);
        else
            return size(node->left);
    }

    int get_by_order(Node* node, int k) {
        if (node == nullptr)
            return -1;

        int left_size = size(node->left);
        if (left_size > k)
            return get_by_order(node->left, k);
        else if (left_size < k)
            return get_by_order(node->right, k - left_size - 1);
        else
            return node->key;
    }

    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    bool find(int key) {
        return find(root, key);
    }

    void insert(int key) 
    {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    int order_of_key(int key) 
    {
        return order_of_key(root, key);
    }

    int get_by_order(int k) {
        return get_by_order(root, k);
    }

    void printInOrder() {
        inOrder(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "In-order traversal of the AVL tree is: ";
    tree.printInOrder();

    tree.remove(20);
    tree.printInOrder();

    tree.order_of_key(25);
    tree.get_by_order(2) ;

    return 0;
}
