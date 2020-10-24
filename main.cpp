#include "main.h"

node *rbtree::insert(int data) {
    node *current, *parent, *x;
    current = _root;
    parent = nullptr;
    while (current != NIL) {
        if (data == current->data) return current;
        parent = current;
        current = (data < current->data) ? current->left : current->right;
    }

    x = new struct node;
    x->data = data;
    x->left = x->right = NIL;
    x->parent = parent;
    x->color = RED;

    if (parent) {
        if (data < parent->data)
            parent->left = x;
        else
            parent->right = x;
    } else {
        _root = x;
    }
    insertFix(x);
    return x;
}

void rbtree::insertFix(node *x) {
    while (x != _root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            node *tmp = x->parent->parent->right;
            if (tmp->color == RED) {
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                tmp->color = BLACK;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    turnLeft(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                turnRight(x->parent->parent);
            }
        } else {
            node *tmp = x->parent->parent->left;
            if (tmp->color == RED) {
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                tmp->color = BLACK;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    turnRight(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                turnLeft(x->parent->parent);
            }
        }
    }
    _root->color = BLACK;
}

void rbtree::show(struct node **_node, int count) {
    if ((*_node) == NIL) {
        std::cout << "<Is Empty>" << std::endl << std::endl;
        return;
    }

    if ((*_node)->right != NIL) {
        show(&(*_node)->right, count + 4);
    }

    for (int i = 0; i < count; ++i) fputs(" ", stdout);
    std::cout << (*_node)->data << std::endl;

    if ((*_node)->left != NIL) {
        show(&(*_node)->left, count + 4);
    }
}

node *rbtree::searchUnit(int data, struct node *_node) {
    if (!_node || _node == NIL) return _node;
    if (_node->data == data) {
        deleteUnit(_node);
    }
    if (data > _node->data) _node->right = searchUnit(data, _node->right);
    else _node->left = searchUnit(data, _node->left);
}

void rbtree::deleteUnit(struct node *_node) {
    struct node *p = NIL;
    struct node *p2 = NIL;
    if (!_node || _node == NIL) return;

    if (!_node->left || _node->left == NIL && !_node->right || _node->right == NIL) {
        if (_node->parent->left == _node) {
            _node->parent->left = NIL;
        } else {
            _node->parent->right = NIL;
        }
    }

    if (!_node->left || _node->left == NIL) {
        p = _node->right;
    } else {
        p = _node->left;
    }

    p->parent = _node->parent;
    if (_node->parent)
        if (_node == _node->parent->left)
            _node->parent->left = p;
        else
            _node->parent->right = p;
    else
        _root = p;

    if (_node != p2) p2->data = _node->data;

    if (p2->color == BLACK)
        deleteFix(p);
    free(_node);
}

int rbtree::inorder(struct node *_node) {
    struct node *tmp;
    int result = 0;
    if (!_node || _node == NIL) return -1;
    for (tmp = _node; tmp->parent != nullptr || tmp == _root; tmp = tmp->right) {
        inorder(tmp->left);
        result = printf("%d -> ", tmp->data);
    }
    return result;
}

int rbtree::preorder(struct node *_node) {
    struct node *tmp;
    int result = 0;
    if (!_node || _node == NIL) return printf("Is empty");
    for (tmp = _node; tmp->parent != nullptr || tmp == _root; tmp = tmp->right) {
        printf("%d -> ", tmp->data);
        result = preorder(tmp->left);
    }
    return result;
}

int rbtree::postorder(struct node *_node) {
    int result = 0;
    if (!_node || _node == NIL) return printf("Is empty");
    postorder(_node->left);
    postorder(_node->right);
    result = printf("%d -> ", _node->data);
    return result;
}

void rbtree::turnRight(node *x) {
    node *y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;

    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        _root = y;
    }
    y->right = x;
    if (x != NIL) x->parent = y;
}

void rbtree::turnLeft(node *x) {
    node *y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    } else {
        _root = y;
    }

    y->left = x;
    if (x != NIL) x->parent = y;
}

int main() {
    rbtree a;
    a.insert(2);
    a.insert(3);
    a.insert(1);
    a.insert(4);
    a.insert(5);
//    a._root = a.deleteUnit(4, a._root);
//    a.insert(4);
    a.insert(7);
    a.insert(8);
    a.searchUnit(8, a._root);
    a.insertFix(a._root->right);
    a.show(&a._root, 0);
    //show(&BinWood, 0);
//    a.inorder(a._root);
//    std::cout << std::endl;
//     a.preorder(a._root);
//    std::cout << std::endl;
////    std::cout << std::endl;
////    preorder(BinWood);
////    std::cout << std::endl;
//    a.postorder(a._root);
//
//    postorder(BinWood->right);

    return 0;
}
