#include "rbtree.h"

void rbtree_init(rbtree_t *tree, rbtree_cmp_t *cmp) {
    tree->root   = NULL;
    tree->cmp    = cmp;
    tree->malloc = malloc;
    tree->free   = free;
}

void rbtree_set_malloc_free(rbtree_t *tree, rbtree_malloc_t *malloc, rbtree_free_t *free) {
    tree->malloc = malloc;
    tree->free   = free;
}

static rbtree_node_t *parent(rbtree_node_t *node) {
    return   node == NULL
           ? NULL
           : node->parent;
}

static rbtree_node_t *grandparent(rbtree_node_t *node) {
    return parent(parent(node));
}

static bool is_left_child(rbtree_node_t *node) {
    return   parent(node) == NULL
           ? false
           : parent(node)->lchild == node;
}

static rbtree_node_t *sibling(rbtree_node_t *node) {
    return   parent(node) == NULL
           ? NULL
           :   is_left_child(node)
             ? parent(node)->rchild
             : parent(node)->lchild;
}

static rbtree_node_t *inside_child(rbtree_node_t *node) {
    return   node == NULL
           ? NULL
           :   is_left_child(node)
             ? node->rchild
             : node->lchild;
}

static rbtree_node_t *outside_child(rbtree_node_t *node) {
    return   node == NULL
           ? NULL
           :   is_left_child(node)
             ? node->lchild
             : node->rchild;
}

static rbtree_node_t *ankle(rbtree_node_t *node) {
    return sibling(parent(node));
}

static rbtree_node_t *near_nieph(rbtree_node_t *node) {
    return inside_child(sibling(node));
}

static rbtree_node_t *far_nieph(rbtree_node_t *node) {
    return outside_child(sibling(node));
}

static bool is_red_node(rbtree_node_t *node) {
    return   node == NULL
           ? false
           : node->color == 'r';
}

static bool is_root_node(rbtree_node_t *node) {
    return node != NULL && parent(node) == NULL;
}

static bool is_inside_child(rbtree_node_t *node) {
    return is_left_child(node) ^ is_left_child(parent(node));
}

static rbtree_node_t *successor(rbtree_node_t *node) {
    rbtree_node_t *result;

    if (node == NULL) return NULL;

    if (node->rchild != NULL) {
        result = node->rchild;

        while (result->lchild != NULL)
            result = result->lchild;

    } else {
        result = node;
        while (result != NULL && !is_left_child(result))
            result = parent(result);

        result = parent(result);
    }
    return result;
}

