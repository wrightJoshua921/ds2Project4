/* 
 * File:   bin.h
 * Author: Joshua Wright
 * Project Number: 4
 * Created on October 28, 2015, 9:51 AM
 */

#ifndef BIN_H
#define	BIN_H
#define MAX_ITEM 100


typedef struct Bins{
    int capacity;
    int currentSize;
    int items[100];
    int numberOfItems;
    struct Bins * nextBin;
}BinsT;

typedef struct Items{
    int size;
    BinsT *anchor, *tail;
}ItemsT;

BinsT *newBin(int size);

ItemsT *newItemList(int item);

BinsT *add2End(ItemsT *list, int item);

void printItemList(const ItemsT *list);

void freeItemList(ItemsT *list);

int spaceCheck(BinsT *bin, int item);

void putBin(BinsT *bin, int item);

void setBin(BinsT *bin, BinsT *nextbin);

void printBin(BinsT *bin);

void freeBin(BinsT *bin);

#endif	/* BIN_H */

