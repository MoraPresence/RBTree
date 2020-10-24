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

void rbtree::searchUnit(int data, struct node *_node) {
    if (!_node || _node == NIL) return;
    if (_node->data == data) {
        deleteUnit(_node);
        return;
    }
    if (data > _node->data) searchUnit(data, _node->right);
    else searchUnit(data, _node->left);
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
        free(_node);
        if (p->color == BLACK)
            deleteFix(p);
        free(_node);
        return;
    }
    if ( _node->left != NIL && _node->right != NIL) {
        p = _node->left;
        p2 = _node->right;
        p2->parent = p;
        p->right = p2;
        if (_node->parent) {
            if (_node->parent->left == _node) {
                _node->parent->left = p;
                p->parent = _node->parent;
            } else {
                _node->parent->right = p;
                p->parent = _node->parent;
            }
        } else
            _root = p;
        if (_node->color == BLACK)
            deleteFix(p);
        free(_node);
        return;
    }
    if (!_node->left || _node->left == NIL) {
        p = _node->right;
    } else if (!_node->right || _node->right == NIL) {
        p = _node->left;
    }
    if (_node->parent) {
        if (_node->parent->left == _node) {
            _node->parent->left = p;
            p->parent = _node->parent;
        } else {
            _node->parent->right = p;
            p->parent = _node->parent;
        }
    } else
        _root = p;

    if (p->color == BLACK)
        deleteFix(p);
    free(_node);
}

void rbtree::deleteFix(node *_node) {
    while (_node != _root && _node->color == BLACK) {
        if (_node == _node->parent->left) {
            node *tmp = _node->parent->right;
            if (tmp->color == RED) {
                tmp->color = BLACK;
                _node->parent->color = RED;
                turnLeft (_node->parent);
                tmp = _node->parent->right;
            }
            if (tmp->left->color == BLACK && tmp->right->color == BLACK) {
                tmp->color = RED;
                _node = _node->parent;
            } else {
                if (tmp->right->color == BLACK) {
                    tmp->left->color = BLACK;
                    tmp->color = RED;
                    turnRight (tmp);
                    tmp = _node->parent->right;
                }
                tmp->color = _node->parent->color;
                _node->parent->color = BLACK;
                tmp->right->color = BLACK;
                turnLeft (_node->parent);
                _node = _root;
            }
        } else {
            node *tmp = _node->parent->left;
            if (tmp->color == RED) {
                tmp->color = BLACK;
                _node->parent->color = RED;
                turnRight (_node->parent);
                tmp = _node->parent->left;
            }
            if (tmp->right->color == BLACK && tmp->left->color == BLACK) {
                tmp->color = RED;
                _node = _node->parent;
            } else {
                if (tmp->left->color == BLACK) {
                    tmp->right->color = BLACK;
                    tmp->color = RED;
                    turnLeft (tmp);
                    tmp = _node->parent->left;
                }
                tmp->color = _node->parent->color;
                _node->parent->color = BLACK;
                tmp->left->color = BLACK;
                turnRight (_node->parent);
                _node = _root;
            }
        }
    }
    _node->color = BLACK;
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
//    a.insert(-1);
    a.insert(1);
    a.insert(4);
//    a.insert(5);
//    a._root = a.deleteUnit(4, a._root);
//    a.insert(4);
    a.searchUnit(2, a._root);
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
