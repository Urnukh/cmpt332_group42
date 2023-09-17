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
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <stdbool.h>




/*
def:Sets the flag to false
args: List
return: none
pre-cond: must have struct ListInitFlag object, struct NodeMemory object, struct ListMemory object and declared
post-cond: allocate space for 1000 nodes, 10 lists and set the flag to true(Flag - is indicator that memory
is allocated for nodes and lists)
*/
void listInitFlag(struct ListInitFlag listInit, struct NodeMemory nodes, struct ListMemory lists){
    listInit.flag = true;
    nodes.currFree = 1000;
    nodes.currOcc = 0;
    nodes.idxCurrFree = 0;
    nodes.idxCurrOcc = 0;
    lists.currFree = 10;
    lists.currOcc = 0;
    lists.idxCurrFree = 0;
    if (listInit.flag){
        (void)listInit.flag;
        (void)nodes.currFree;
        (void)nodes.currOcc;
        (void)nodes.idxCurrFree;
        (void)nodes.idxCurrOcc;
        (void)lists.currFree;
        (void)lists.currOcc;
        (void)lists.idxCurrFree;
    }
}


/*
def: Create a list of limited number of elements/node
args: int number of max elements, struct ListInitFlag and struct ListMemory
return: pointer to the list on success if not NULL pointer
pre-cond: must have struct ListInitFlag, struct NodeMemory, struct ListMemory initiliazed
post-cond: a new list
*/
struct List *ListCreate(int maxEl,struct ListInitFlag listInit, struct ListMemory lists, struct NodeMemory nodes){
    struct List newList;
    struct List *listPtr;
    /* Check if it is the very first time list is created */
    if (listInit.flag == false){
        return NULL;
    }else{
        if(maxEl <= 0){
            return NULL;
        }else{
            /* Setting pointer to Pool of Nodes */
            newList.ptrNodePool = &nodes;
            /* Setting newList to its corresponding array location */
            lists.listPool[lists.idxCurrFree] = newList;
            /* Keeping track of free and occupied number of Lists*/
            lists.currFree -= 1;
            lists.currOcc += 1;
            lists.idxCurrOcc += 1;
            lists.idxCurrFree += 1;
            listPtr = &newList;
            /* Setting list parameters*/
            newList.maxEl = maxEl;
            newList.numEl = 0;
            newList.firstElement = NULL;
            newList.curEl = NULL;
            newList.nextEl = NULL;
            newList.prevEl = NULL;
            newList.lastElement = NULL;
            return listPtr;
        }
    }
}


/*
def:Gets number of elements in the list
args: struct List list
return: int numEl
pre-cond: must have a list
post-cond: none
*/
int ListCount(struct List list){
    return list.numEl;
}


/*
def: Adds a new item right after the current element and sets the new item as current element
args: struct List list, void* item,
return: 0 on success else return 1
pre-cond: The list must not be full
post-cond: The list will have one more item and new current element
*/
int ListAdd(struct List list,void* item) {
    if (list.numEl >= list.maxEl) {
        return -1;
    } else {
        /* Pointer to first available free spot in Pool of Nodes */
        struct Node* ptrNode = &list.ptrNodePool->nodePool[list.ptrNodePool->idxCurrFree];
        /* Setting a pointer to Pool of Nodes*/
        struct NodeMemory* memPtr = list.ptrNodePool;
        /* Setting Node parameter for it's corresponding idx in Pool of Nodes*/
        ptrNode->idxMemory = memPtr->idxCurrFree;
        /* Setting item to Node data*/
        ptrNode->data = item;
        /* NodeMemory tracking added node*/
        memPtr->idxCurrFree += 1;
        memPtr->currFree -= 1;
        memPtr->currOcc += 1;
        /* Setting previous and next nodes for the Node*/
        ptrNode->nextNode = list.nextEl;
        ptrNode->prevNode = list.curEl;
        /* Setting next, current nodes*/
        if(list.numEl == 0){
            list.curEl = ptrNode;
            list.firstElement = ptrNode;
            list.lastElement = ptrNode;
            ptrNode->nextNode = NULL;
            ptrNode->prevNode = NULL;
        }
        if(list.curEl->nextNode == NULL){
            list.lastElement = ptrNode;
        }
        list.curEl->nextNode = ptrNode;
        list.prevEl = list.curEl;
        list.curEl = ptrNode;
        list.idxCurEl += 1;
        list.numEl += 1;
        ListNext(list);
        return 0;
    }
}


/*
def: Inserts an item right before current item and sets added as current item
args: struct List list, struct Node item
return: 0 on successful insertion -1 otherwise
pre-cond: The list must not be full
post-cond: The list will have one more item and will point to the newly added element
*/
int ListInsert(struct List list, void* item) {
    if (list.numEl >= list.maxEl) {
        return -1;
    } else {
        struct Node* ptrNode = &list.ptrNodePool->nodePool[list.ptrNodePool->idxCurrFree];
        struct NodeMemory* memPtr = list.ptrNodePool;
        ptrNode->idxMemory = memPtr->idxCurrFree;
        ptrNode->data = item;
        ptrNode->idxMemory = memPtr->idxCurrFree;
        memPtr->idxCurrFree += 1;
        memPtr->currFree -= 1;
        memPtr->currOcc += 1;
        if(list.numEl == 0){
            ptrNode->nextNode = NULL;
            ptrNode->prevNode = NULL;
            list.curEl = ptrNode;
            list.firstElement = ptrNode;
            list.curEl = ptrNode;
            list.lastElement = ptrNode;
        }else{
            ptrNode->prevNode = list.prevEl;
            ptrNode->nextNode = list.curEl;
            list.curEl->prevNode = ptrNode;
            list.curEl = ptrNode;
        }
        list.numEl += 1;
        list.idxCurEl += 1;
        return 0;
    }
}

/*
def: Add an element to the end of list and make it current item
args: struct List list, struct Node item
return: 0 on successful insertion or -1 on failure
pre-cond: The list can NOT be full
post-cond: List will have one more item
*/
int ListAppend(struct List list, void* item){
    if(list.numEl >= list.maxEl){
        return -1;
    }else{
        struct Node* ptrNode = &list.ptrNodePool->nodePool[list.ptrNodePool->idxCurrFree];
        struct NodeMemory* memPtr = list.ptrNodePool;
        ptrNode->idxMemory = memPtr->idxCurrFree;
        ptrNode->data = item;
        memPtr->idxCurrFree += 1;
        memPtr->currFree -= 1;
        memPtr->currOcc += 1;
        if(list.numEl == 0){
            ptrNode->nextNode = NULL;
            ptrNode->prevNode = NULL;
            list.curEl = ptrNode;
            list.lastElement = ptrNode;
            list.firstElement = ptrNode;
        }else{
            list.lastElement->nextNode = ptrNode;
            ptrNode->prevNode = list.lastElement;
            ptrNode->nextNode = NULL;
            list.lastElement = ptrNode;
            list.curEl = ptrNode;
        }
        list.numEl += 1;
        list.idxCurEl = list.numEl;
        return 0;
    }
}

/*
def: Adds an element at the front of the element and sets this element to current element
args: struct LIST list, struct NODE list
return: 0 on success -1 on failure
pre-cond: The list cannot be full
post-cond: The list will have one more item and new current item
 */
int ListPrepend(struct List list, void* item){
    if(list.numEl >= list.maxEl){
        return -1;
    }else{
        struct Node* ptrNode = &list.ptrNodePool->nodePool[list.ptrNodePool->idxCurrFree];
        struct NodeMemory* memPtr = list.ptrNodePool;
        ptrNode->idxMemory = memPtr->idxCurrFree;
        ptrNode->data = item;
        ptrNode->prevNode = NULL;

        memPtr->idxCurrFree += 1;
        memPtr->currFree -= 1;
        memPtr->currOcc += 1;

        list.firstElement->prevNode = ptrNode;
        ptrNode->nextNode = list.firstElement;
        list.firstElement = ptrNode;
        list.curEl = ptrNode;
        list.numEl += 1;
        list.idxCurEl = 0;
        return 0;
    }
}

/*
def: List2 is added to the end of List1 and current pointer is set to current element of List1
args: struct LIST list1, struct LIST list2
return: none
        pre-cond: The two list must NOT be empty
        post-cond: list2 does not exist
*/
void ListConcat(struct List list1,struct List list2){
    /* combine two lists;*/
    /* list1.lastElement = list2.firstElement; */
    (void) list1;
    (void) list2;
}
