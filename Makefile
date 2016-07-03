CFLAGS += -g -Wall

all:  rbtree_test1

rbtree.o: rbtree.h rbtree.c
	$(CC) $(CFLAGS) -c rbtree.c

rbtree_test1:  rbtree_test1.c rbtree.o
	$(CC) $(CFLAGS) -o rbtree_test1 rbtree_test1.c rbtree.o

clean:
	$(RM) -rf *.o rbtree_test1
