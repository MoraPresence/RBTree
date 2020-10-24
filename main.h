//
// Created by mora on 10.10.2020.
//
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

#define BLACK false
#define RED true

#ifndef STATICREVERSE_MAIN_H
#define STATICREVERSE_MAIN_H


struct node {
    int data;
    node *left;
    node *right;
    node *parent;
    bool color;
};

#define NIL &sentinel
node sentinel = {0, NIL, NIL, nullptr, BLACK};

class rbtree {
public:
    node *insert(int data);

    void insertFix(node *x);

    void turnRight(node *x);

    void turnLeft(node *x);

    void show(struct node **_node, int count);

    node *searchUnit(int data, struct node *_node);

    void deleteUnit(struct node *_node);

    void deleteFix(node *x);

    int inorder(struct node *_node);

    int preorder(struct node *_node);

    int postorder(struct node *_node);


    node *_root = NIL;
};


#endif //STATICREVERSE_MAIN_H
