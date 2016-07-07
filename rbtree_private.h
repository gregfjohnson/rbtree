/* rbtree_private.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef RBTREE_PRIVATE_H
#define RBTREE_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _rbtree_node_t {
    void *data;
    struct _rbtree_node_t *parent;
    struct _rbtree_node_t *lchild, *rchild;
    char color;
} rbtree_node_t;

typedef struct {
    rbtree_node_t *root;
    rbtree_cmp_t  *cmp;

    rbtree_malloc_t *malloc;
    rbtree_free_t *free;
} rbtree_t;

typedef struct {
    rbtree_node_t *next_node;
    rbtree_t *tree;
} rbtree_iter_t;

#ifdef __cplusplus
}
#endif

#endif
