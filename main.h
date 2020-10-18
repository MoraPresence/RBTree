//
// Created by mora on 10.10.2020.
//
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#ifndef STATICREVERSE_MAIN_H
#define STATICREVERSE_MAIN_H
struct node {
    int data;
    node *left, *right;
};

void insert(int in, struct node **_node) {
    if ((*_node) == nullptr) {
        (*_node) = new struct node;
        (*_node)->data = in;
        (*_node)->left = (*_node)->right = nullptr;
        return;
    }
    if (in > (*_node)->data) insert(in, &(*_node)->right);
    else insert(in, &(*_node)->left);
}

void show(struct node **_node, int count) {
    if ((*_node) == nullptr) {
        std::cout << "<Is Empty>" << std::endl << std::endl;
        return;
    }

    if ((*_node)->right != nullptr) {
        show(&(*_node)->right, count + 4);
    }

    for (int i = 0; i < count; ++i) fputs(" ", stdout);
    std::cout << (*_node)->data << std::endl;

    if ((*_node)->left != nullptr) {
        show(&(*_node)->left, count + 4);
    }
}

struct node *deleteUnit(int in, struct node *_node) {
    if (!_node) return _node;
    struct node *p, *p2;
    if (_node->data == in) {
        if (_node->left == nullptr) {
            p = _node->right;
            free(_node);
            return p;
        } else if (_node->right == nullptr) {
            p = _node->left;
            free(_node);
            return p;
        } else {
            p2 = _node->right;
            p = _node->right;
            while (p->left) p = p->left;
            p->left = _node->left;
            free(_node);
            return p2;
        }
    }
    if (in > _node->data) _node->right = deleteUnit(in, _node->right);
    else _node->left = deleteUnit(in, _node->left);
}

int inorder(struct node *_node) {
    struct node *tmp;
    int result = 0;
    if (!_node) return -1;
    for (tmp = _node; tmp; tmp = tmp->right) {
        inorder(tmp->left);
        result = printf("%d -> ", tmp->data);
    }
    return result;
}

int preorder(struct node *_node) {
    struct node *tmp;
    int result = 0;
    if (!_node) return printf("Is empty");;
    for (tmp = _node; tmp; tmp = tmp->right) {
        printf("%d -> ", tmp->data);
        result = preorder(tmp->left);
    }
    return result;
}

int postorder(struct node *_node) {
    struct node *tmp;
    int result = 0;
    if (!_node) return printf("Is empty");
    if(_node != nullptr) {
        postorder(_node->left);
        postorder(_node->right);
    }
    result = printf("%d -> ", _node->data);
    return result;
}

#endif //STATICREVERSE_MAIN_H
