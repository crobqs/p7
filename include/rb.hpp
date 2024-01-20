#pragma once

#include <bits/stdc++.h>
#include "util.hpp"
#include "at.hpp"

class RB {
public:
    enum { RED,BLACK };

    typedef struct Tree {
        int val;
        struct Tree *left, *right;

        bool color;
        struct Tree *parent;
    } Tree;

    RB() {
    #ifdef BST
        this->root = NULL;
    #else
        this->nil = &BLACK_NODE;
        this->nil->color = BLACK;
        this->root = this->nil;
    #endif
    }

    ~RB() {
        clean();
    }

    void insert(int val) {
    #ifdef BST
        root = bst_insert(root, val);
    #else
        rb_insert(val);
    #endif
    }

    void clean() {
        clean__(root);
    }

    void print() {
        AT at;
        at.print_ascii_tree(root);
    }

private:
    Tree
    BLACK_NODE = { 0,NULL,NULL,BLACK,NULL },
    *nil,
    *root;

    Tree* newTree(int val) {
        Tree* n = (Tree*)calloc(1, sizeof(Tree));
        n->val = val;
        n->color = RED;
        n->left = n->right = n->parent = this->nil;
        return n;
    }

    void rl(Tree* a) {
        Tree* b = a->right;
        a->right = b->left;
        if (b->left != nil) b->left->parent = a;
        b->parent = a->parent;
        if (a->parent == nil) root = b;
        else if (a->parent->left) a->parent->left = b;
        else a->parent->right = b;
        b->left = a;
        a->parent = b;
    }

    void rr(Tree* a) {
        Tree* b = a->left;
        a->left = b->right;
        if (b->right != nil) b->right->parent = a;
        b->parent = a->parent;
        if (a->parent == nil) root = b;
        else if (a->parent->left) a->parent->left = b;
        else a->parent->right = b;
        b->right = a;
        a->parent = b;
    }

    void insertFix(Tree* n) {
        while (n != root && n->parent->color == RED) {
            Tree* pp = n->parent->parent;
            if (n->parent == pp->left) {
                Tree* uncle = pp->right;
                if (uncle->color == RED) {
                    n->parent->color = BLACK;
                    uncle->color = BLACK;
                    pp->color = RED;
                    n = pp;
                } else {
                    if (n == n->parent->right) {
                        n = n->parent;
                        rl(n);
                    }
                    n->parent->color = BLACK;
                    n->parent->parent->color = RED;
                    rr(n->parent->parent);
                }
            } else {
                Tree* uncle = pp->left;
                if (uncle->color == RED) {
                    n->parent->color = BLACK;
                    uncle->color = BLACK;
                    pp->color = RED;
                    n = pp;
                } else {
                    if (n == n->parent->left) {
                        n = n->parent;
                        rr(n);
                    }
                    n->parent->color = BLACK;
                    n->parent->parent->color = RED;
                    rl(n->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void rb_insert(int val) {
        Tree *n = newTree(val);
        Tree *cur = root;
        Tree *parent = nil;

        while (cur != nil) {
            parent = cur;
            if (n->val < cur->val) {
                cur = cur->left;
            } else if (n->val > cur->val) {
                cur = cur->right;
            } else {
                free(n);
                return;
            }
        }

        n->parent = parent;

        if (parent == nil) {
            root = n;
        } else if (n->val < parent->val) {
            parent->left = n;
        } else {
            parent->right = n;
        }

        insertFix(n);
    }

    Tree* bst_insert(Tree* root, int val) {
        if (!root) return newTree(val);
        else if (val < root->val) {
            Tree* lc = bst_insert(root->left, val);
            lc->parent = root;
            root->left = lc;
        } else if (val > root->val) {
            Tree* rc = bst_insert(root->right, val);
            rc->parent = root;
            root->right = rc;
        } else { return root; }
        return root;
    }

    void clean__(Tree* t) {
    #ifdef BST
        if (!t) return;
        clean__(t->left);
        clean__(t->right);
        free(t);
    #else
        if (t != nil) return;
        clean__(t->left);
        clean__(t->right);
        free(t);
    #endif
    }

};
