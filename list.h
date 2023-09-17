/*
# Urnukh Tsogt
# URT633
# 11267557
#
# Mitchell Risling
# MJR810
# 11221612
#
# CMPT332
# a01-phase03
*/

#include <stdbool.h>
#define NODE_SIZE 1000
#define LIST_SIZE 10

/*
    Definition of structs
*/
#ifndef NODE_HEADER_GUARD_WITH_UNIQUE_NAME
#define NODE_HEADER_GUARD_WITH_UNIQUE_NAME
struct ListInitFlag{
    bool flag;
};

struct Node{
    void* data;
    int idxMemory;
    struct NodeMemory* nodePool;
    struct Node* nextNode;
    struct Node* prevNode;
};


struct NodeMemory{
    int currFree;
    int currOcc;
    int idxCurrFree;
    int idxCurrOcc;
    struct Node nodePool[NODE_SIZE];
};

struct List{
    struct Node* firstElement;
    struct Node* lastElement;
    struct NodeMemory* ptrNodePool;
    int idxMemory;
    int numEl;
    int maxEl;
    int idxCurEl;
    struct Node* prevEl;
    struct Node* nextEl;
    struct Node* curEl;
};

struct ListMemory{
    int currOcc;
    int currFree;
    int idxCurrFree;
    int idxCurrOcc;
    struct List listPool[LIST_SIZE];
};


/* Method signature */
void listInitFlag(struct ListInitFlag listInit, struct NodeMemory nodes, struct ListMemory lists);
struct Node* nodeMemoryInit();
struct List* listMemoryInit();
struct List *ListCreate(int maxEl,struct ListInitFlag listInit, struct ListMemory lists, struct NodeMemory nodes);
int ListCount(struct List list);
void *ListFirst(struct List list);
void *ListLast(struct List list);
void *ListNext(struct List list);
void *ListPrev(struct List list);
void *ListCurr(struct List list);
int ListAdd(struct List list,void* item);
int ListInsert(struct List list,void* item);
int ListAppend(struct List list,void* item);
int ListPrepend(struct List list, void* item);
void *ListRemove(struct List list);
void ListConcat(struct List list1, struct List list2);
void ListFree(struct List list, void(* itemFree)(void* ));
void *ListTrim(struct List list);
void *ListSearch(struct List list, int(* comparator)(void*,void*),void* comparisonArg);

#endif
