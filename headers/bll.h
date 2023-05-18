#ifndef BLL_H
#define BLL_H
#include "structs.h"

int BLL_length(boardLinkedList *BLL);
void BLL_item(boardLinkedList *BLL,int index, board out);
void print_BLL_item(boardLinkedList *BLL, int index);
void freeBLL(boardLinkedList *toFree);
boardLinkedList* appendToBLL(board toAppend,boardLinkedList *head);
void printBLL(boardLinkedList *root);

#endif