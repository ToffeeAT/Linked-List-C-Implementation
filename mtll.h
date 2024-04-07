#ifndef MTLL_H
#define MTLL_H

#include <stddef.h>
#include <stdbool.h>

struct list {
    struct mtll *head_list; // start of the list [considered the data of the list]
    struct list *next_list; // used to iterate through the list
};

struct mtll {
    struct mtll_node *head_node; // the nodes of the list starting at the head
    int count; // provides what number list this is
};

struct mtll_node {
    void *data; // the value of the node
    char type[20]; // the type of the node
    struct mtll_node *next; // the next node in the list
    int indexNode;
};

extern struct list *head;
extern struct list *current;
extern int counter;
extern bool noList;
extern int indexNode;

// functions and implementations

extern struct mtll *mtll_create();

extern void InsertList(struct mtll* mtll);

extern void InsertNode(struct mtll *mtll, void *data, char *type, int indexNode);

extern void mtll_viewAll(struct list *list);

extern void mtll_new(int num);

extern void mtll_view(struct list *list, int num);

extern void mtll_remove(struct list **list_ptr, int num);

extern void mtll_type(struct list *list, int num);

extern bool isScientificNumber(const char *str);

extern void InsertNewNode(struct list *list, int listId, int index, void *value);

extern char *typeChecker(void *buffer);

extern void sortNodes(struct mtll *mtll);

extern void swapNodes(struct mtll_node *a, struct mtll_node *b);

extern void DeleteNode(struct list **list_ptr, int num, int index);


#endif
