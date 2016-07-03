/* rbtree.c, Copyright (C) 2016, Greg Johnson
 * Released under the terms of the GNU GPL v2.0.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rbtree.h"

typedef unsigned char byte;

/* return value for unit test main routine */
static int test_result_value = 0;

static void test_result(int test, char *title) {
    printf("%s %s\n", title, test ? "passed" : "failed");

    if (!test)
        { test_result_value = -1; }
}

static int byte_cmp(byte *i1, byte *i2) {
    return (int) *i1 - *i2;
}

static int countNodes(rbtree_node_t *subtree) {
    if (subtree == 0) return 0;
    return 1 + countNodes(subtree->lchild) + countNodes(subtree->rchild);
}

static void printTree(rbtree_node_t *subtree) {
    if (subtree == 0) return;

    printTree(subtree->lchild);

    printf("%d\n", *(byte *) subtree->data);

    printTree(subtree->rchild);
}

static void test1() {
    byte data[] =       {3,1,4,1,5,9,2,6};
    byte sortedData[] = {1,1,2,3,4,5,6,9};
    rbtree_t tree;
    rbtree_iter_t iter;
    int i;

    rbtree_init(&tree, (rbtree_cmp_t *) byte_cmp);

    for (i = 0; i < sizeof(data); ++i) {
        rbtree_insert(&tree, &data[i]);
        test_result(countNodes(tree.root) == i + 1, "insert");
    }
    printTree(tree.root);

    iter = rbtree_iter(&tree);
    for (i = 0; i < sizeof(data); ++i) {
        byte *bytePtr = rbtree_iter_next(&iter);
        test_result(*bytePtr == sortedData[i], "in order");
    }

    for (i = sizeof(data) - 1; i >= 0; --i) {
        rbtree_delete(&tree, &sortedData[sizeof(sortedData) - 1 - i]);
        test_result(countNodes(tree.root) == i, "delete");
    }
}

static void test2() {
    byte data[] = {3,1,4,1,5,9,2,6};
    byte *datum;
    rbtree_t tree;
    int i;

    rbtree_init(&tree, (rbtree_cmp_t *) byte_cmp);

    for (i = 0; i < sizeof(data); ++i) {
        rbtree_insert(&tree, &data[i]);
        test_result(countNodes(tree.root) == i + 1, "insert");
    }

    i = sizeof(data);

    while ((datum = rbtree_first(&tree)) != NULL) {
        rbtree_delete(&tree, datum);
        test_result(countNodes(tree.root) == --i, "delete");
    }
}

int main(int argc, char **argv) {
    test1();
    test2();

    return test_result_value;
}
