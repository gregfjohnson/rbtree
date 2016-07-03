# rbtree
An implementation of the classic red black tree algorithm for balanced binary trees in C

This is an implementation of red-black trees:  ordered binary trees
that maintain balance in the presence of arbitrary sequences
of inserts and deletes.

Don't believe what they tell you in algorithms textbooks ;-).  The red-black
tree algorithms are somewhat tricky and hard to understand.

This implementation is based on a re-design of the fundamental red-black
tree algorithms intended to be helpful in making the opaque magic easier
to grok.

Each node is given a color (red or black), and the tree satisfies
the following two properties:

    black property:  sibling nodes have the same black-height.
    red property:    no red node has a red parent.

These two properties together guarantee that no two leaf nodes will
differ by more than a factor of two in depth.

Usage:

    rbtree_t tree;
    rbtree_init(&tree, my_data_comparison_function);

    my_data_t my_data = {...};
    rbtree_insert(&tree, &my_data);

    my_data_t search, *found;
    search.key = key;
    found = rbtree_find(&tree, &search);

    found = rbtree_delete(&tree, &search);

    found = rbtree_first(&tree) 

    rb_tree_t iter = rb_iter(&tree);
    while ((found = rbtree_iter_next(&iter)) != NULL) {
        ...
    }

A common usage pattern is for the client to malloc() instances of their
data type, populate them, and insert them into a red black tree.  Then,
at clean-up time, delete each data value from the tree and free() it.

Here are a few thoughts on the approach that guided this implementation.

We define a single rotateUp() operation that applies to a child
node instead of defining distinct left and right rotate() operations
that apply to a parent node.

We use direction-agnostic naming of relative node positions.  Together
with rotateUp(), this allows us to avoid mentions of left or right
anywhere in the algorithms except in a couple of low-level utility
routines.

Moreover, this obviates the need to have large chunks of
redundant code that handle "to the left" and "to the right" separately.

We introduce no notion of artificial NIL leaf nodes.  We make no
assumption in the definitions or the code that all non-leaf nodes have
two children.

We make no requirement that the root node be red.

We make use of a generalization of the usual notion of black height.
In the standard definition, the black height of a node is only considered
well defined if all simple paths from the node to leaf nodes have the
same number of black nodes.  We prefer to define the black height of
a node as the maximum number of black nodes in any simple path starting
from the node and descending into its subtree.  With that definition,
black height is well-defined for all nodes in all trees, even ones that
violate the black property.

We give an alternative formulation of the Black property in terms
of sibling nodes.  This fits well with the pre-conditions of the
restoreBlackProperty() algorithm.  The exact location of a violation
of the Black property becomes well-defined.  If a node has
children with different black heights, the node's black height is defined in
terms of the larger child black height.  This fits well with the deletion
algorithm, because all nodes outside the subtree that is the lighter of
the unequal sibling pair retain their original black heights.  However,
this new definition creates the need for a proof that the standard black
property is equivalent.  The latter is of course essential to ensure that
red-black trees have the desired O(log(N)) algorithms.

We define restoreRedProperty() and restoreBlackProperty() recursively
instead of iteratively.  The entry conditions of these routines are
carefully stated and serve the same function as loop invariants in the
iterative versions.

In the delete operation we leave the node to be deleted in the tree while
the Black property is being restored.  It is helpful in the algorithm to
start at that node and work upward in the tree.  To create the initial
violation of the Black property, we assign this node a third color.

More details are available at gregfjohnson.com.

Please let me know if you see any errors or problems.  Thanks!
