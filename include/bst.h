// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class BST {
    struct  Node {
        T value;
        int count;
        Node* left;
        Node* right;
    };

private:
    Node* root;
    Node* addNode(Node*, T);
    void printTree(Node*);
    int deepTree(Node*);
    int searchNode(Node*, T);
    Node* delNode(Node*, int);

public:
    BST();
    ~BST() {};
    void add(T);
    void print();
    int deep();
    int search(T);
    void clear();
    void remove(int);
};

template <typename T>
BST<T>::BST() :root(nullptr) {}

template <typename T>
typename BST<T>::Node* BST<T>::addNode(Node* root, T value) {
    if (root == nullptr) {
        root = new Node;
        root->value = value;
        root->count = 1;
        root->left = nullptr;
        root->right = nullptr;
    }
    else if (root->value > value) {
        root->left = addNode(root->left, value);
    }
    else if (root->value < value) {
        root->right = addNode(root->right, value);
    }
    else {
        root->count++;
    }
    return root;
}

template <typename T>
int BST<T>::deep() {
    return deepTree(root) - 1;
}

template<typename T>
int BST<T>::deepTree(Node* current) {
    int left = 0, right = 0;
    if (current != nullptr) {
        left = current->left != nullptr ? deepTree(current->left) : 0;
        right = current->right != nullptr ? deepTree(current->right) : 0;
    }
    return left > right ? left + 1 : right + 1;
}

template <typename T>
int BST<T>::search(T str) {
    return searchNode(root, str);
}

template<typename T>
int BST<T>::searchNode(Node* current, T str) {
    if (current->value == str) {
        return current->count;
    }
    return str < current->value ? searchNode(current->left, str) : searchNode(current->right, str);
}

template <typename T>
void BST<T>::add(T value) {
    root = addNode(root, value);
}

template <typename T>
void BST<T>::printTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    if (root->left != nullptr) {
        printTree(root->left);
    }
    for (int i = 0; i < root->count; i++) {
        std::cout << root->value << " ";
    }
    if (root->right != nullptr) {
        printTree(root->right);
    }
}

template <typename T>
void BST<T>::print() {
    printTree(root);
}

template <typename T>
void BST<T>::clear() {
    if (root) {
        delTree(root);
        root = nullptr;
    }
}

template <typename T>
typename BST<T>::Node* BST<T>::delNode(typename BST<T>::Node* root, int value) {
    if (root == nullptr) {
        return root;
    }
    Node* p, * v;
    if (value < root->value) {
        root->left = delNode(root->left, value);
    }
    else if (value > root->value) {
        root->right = delNode(root->right, value);
    }
    else {
        if (root->right == nullptr) {
            root = root->left;
        }
        else if (root->left == nullptr) {
            root = root->right;
        }
        else {
            v = root->left;
            if (v->right) {
                while (v->right->right) {
                    v = v->right;
                }
                root->value = v->right->value;
                root->count = v->right->count;
                p = v->right;
                v->right = v->right->left;
            }
            else {
                root->value = v->value;
                root->count = v->count;
                p = v;
                root->left = root->left->left;
            }
        }
        delete p;
    }
    return root;
}

template <typename T>
void BST<T>::remove(int value) {
    if (root) {
        root = delNode(root, value);
    }
}

#endif  // INCLUDE_BST_H_
