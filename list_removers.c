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
#include <list.h>

/*
def: Remove current item from the list and make next item as current item
args: struct List list, struct Node item
return: struct Node item
pre-cond:the list must NOT be empty
post-cond: the list is one item shorter
*/
void *ListRemove(struct List list){
    struct Node* remItem;
     if(list.numEl == 0){
         return NULL;
     }else{
        remItem = list.curEl;
        list.nextEl = list.curEl->nextNode->nextNode;
        list.prevEl->nextNode = list.curEl->nextNode;
        list.curEl->nextNode->prevNode = list.prevEl;
        list.curEl = list.nextEl;
        remItem->prevNode = NULL;
        remItem->nextNode= NULL;
        list.numEl -= 1;
        return remItem;
     }

}
/*
def: Deletes list
args: struct List list, *itemFree
return: none
pre-cond: the list must NOT be empty
post-cond: the items of the list freed and list deleted
 */
void ListFree(struct List list, void(* itemFree)(void* )){
    list.curEl = list.firstElement;
    while(list.curEl->nextNode != NULL){
        (*itemFree)(list.curEl->data);
        list.curEl = list.nextEl;
        list.nextEl = list.nextEl->nextNode;
    }
}


/*
def:Return last item in the list and remove it from the list.
    Set current pointer to new last element.
args: struct List list
return: struct Node item
pre-cond:List must NOT empty
post-cond: List is one item shorter and new current element
 */
void *ListTrim(struct  List list){
     if(list.numEl == 0){
         return NULL;
     }else{
         struct Node* remItem;
          remItem = list.lastElement;
          list.lastElement->prevNode->nextNode = NULL;
          list.curEl = list.lastElement->prevNode;
          list.lastElement = list.curEl;
          list.numEl -= 1;
          list.idxCurEl = list.numEl -1;
          remItem->prevNode = NULL;
         return  remItem;
     }
}


/*
def:Search for an item in the list starting at current item , if found return a pointer
    to the item and current item is set at this location.
    If not found return a NULL pointer and current item is at the last item of the list.
args: struct List list, void* comparator, void* comparisonArg
return: pointer to item
pre-cond:none
post-cond: Current item is at the item or at the end of the list
 */
void *ListSearch(struct List list, int(* comparator)(void*,void*),void* comparisonArg){
    while(list.curEl != NULL){
        if((*comparator)(list.curEl->data,comparisonArg) == 0){
            ListNext((list));
        }if(comparator(list.curEl->data,comparisonArg) == 1){
            return list.curEl->data;
        }
    }
    return NULL;
}
