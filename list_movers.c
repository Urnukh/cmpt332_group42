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
# a01-phase01

*/
#include <stdio.h>
#include <stdlib.h>
#include <list.h>

/*
def: Returns a pointer to the first element of the list and sets current item to first element
args: struct List list
return:  *firstElement
pre-cond: must have a list
post-cond: curEl is set to firstElement
*/
void *ListFirst(struct List list){
  list.curEl = list.firstElement;
  list.idxCurEl = 0;
  return list.curEl->data;
}

/*
def: Returns a pointer to the last element of the list and sets current element to the last
args: struct List list
return: *lastElement
pre-cond: must have a list
post-cond: curEl points to lastElement
 */
void *ListLast(struct List list){
   list.prevEl = list.lastElement->prevNode;
   list.nextEl = NULL;
   list.curEl = list.lastElement;
   list.idxCurEl = list.numEl -1;
   return list.curEl->data;

}

/*
def: Advances current element by one in the list
args: struct List list
return: pointer to new current element
pre-cond: list must have an element
post-cond: curEl points to next element(element prior to method call)
*/
void *ListNext(struct List list){
   if(list.idxCurEl == list.maxEl -1){
     return NULL;
   }else{
     list.idxCurEl += 1;
     list.prevEl = list.curEl;
     list.nextEl = list.curEl->nextNode->nextNode;
     list.curEl = list.curEl->nextNode;
     return list.curEl->data;
   }
}

/*
def: Set current element moving backwards by one and return a pointer to new current element
args: struct List list
return: pointer to new current element
pre-cond: list must have at least one item
post-cond: current element points to previous element(element prior to method call)
 */
void *ListPrev(struct List list){
   if(list.idxCurEl == 0){
     return NULL;
   }else{
     list.prevEl = list.prevEl->prevNode;
     list.nextEl = list.curEl;
     list.idxCurEl -= 1;
     list.curEl = list.curEl->prevNode;
     return list.curEl->data;
   }

}



/*
def: Returns pointer to current element of the list
args: struct List list
return: pointer to current element
pre-cond: List must have at least one item
post-cond: none
 */
void *ListCurr(struct List list) {
    if (list.numEl == 0) {
        return NULL;
    } else {
        return list.curEl->data;
    }
}
