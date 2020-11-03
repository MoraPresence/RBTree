//
// Created by mora on 10.10.2020.
//
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <debugapi.h>

#define BLACK false
#define RED true
#define NIL &sentinel

#ifndef STATICREVERSE_MAIN_H
#define STATICREVERSE_MAIN_H


struct node {
    int data;
    node *left;
    node *right;
    node *parent;
    bool color;
};


class rbtree {
public:
    rbtree() {
        sentinel = {0, NIL, NIL, nullptr, BLACK};
        _root = NIL;
    }

    ~rbtree();

    node *insert(int data);

    void show(struct node **_node, int count);

    void searchUnit(int data, struct node *_node);

    void deleteUnit(struct node *_node);


    int inorder(struct node *_node);

    int preorder(struct node *_node);

    int postorder(struct node *_node);

    node *_root;
private:
    void insertFix(node *x);

    void turnRight(node *x);

    void turnLeft(node *x);

    void deleteFix(node *x);

    node sentinel{};
};


#endif //STATICREVERSE_MAIN_H

