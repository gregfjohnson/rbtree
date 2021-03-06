/* rbtree.h, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#ifndef RBTREE_H
#define RBTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <unistd.h>

typedef int (rbtree_cmp_t)(const void *, const void *);

typedef void *(rbtree_malloc_t)(size_t size);
typedef void  (rbtree_free_t)(void *ptr);

#include "rbtree_private.h"

/* initialize a red-black tree with user-provided comparison function */
void rbtree_init(rbtree_t *tree, rbtree_cmp_t *cmp);

/* set optional custom malloc and free functions for internals of rbtree implementation */ 
void rbtree_set_malloc_free(rbtree_t *tree, rbtree_malloc_t *malloc, rbtree_free_t *free);

/* binary search for a node equal to vsearch.  if not found, return NULL. */
void *rbtree_find(rbtree_t *tree, void *vsearch);

/* return smallest user data value in the tree, or NULL if tree is empty. */
void *rbtree_first(rbtree_t *tree);

/* delete node equal to z from the tree; return deleted value,
 * or NULL if nothing was deleted.
 */
void *rbtree_delete(rbtree_t *tree, void *z);

/* insert node x into the tree; on any failure (i.e., internal
 * malloc fails), return NULL.  otherwise, return inserted value.
 */
void *rbtree_insert(rbtree_t *tree, void *x);

/* return an iterator for the elements in the tree */
rbtree_iter_t rbtree_iter(rbtree_t *tree);

/* return the next node in the tree.
 * NULL return value signals traversal is complete.
 *
 * please don't insert or delete nodes while iteration is happening..
 */
void *rbtree_iter_next(rbtree_iter_t *iter);

#ifdef __cplusplus
}
#endif

#endif
