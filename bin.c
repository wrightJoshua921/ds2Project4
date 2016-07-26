/* 
 * File:   bin.c
 * Author: Joshua Wright
 * Project Number: 4
 * Created on October 28, 2015, 9:51 AM
 */

#include "bin.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//creates a new item list
ItemsT *newItemList(int item)
{
    ItemsT *newList =(ItemsT *) malloc(sizeof(ItemsT));
    newList->anchor = newList->tail = NULL;
    newList->size = 0;
    
    add2End(newList, item);
    
    return newList;
}

//adds an item to the end of the list
BinsT *add2End(ItemsT *list, int item)
{
    BinsT *new = newBin(item);
    BinsT *temp = list->anchor;
    
    if(list->anchor == NULL)
    {
        list->anchor = list->tail = new;
    }
    else
    {
        while(temp->nextBin != NULL)
        {
            temp = temp->nextBin;
        }
        temp->nextBin = list->tail = new;
    }
    new->nextBin = NULL;
    list->size++;
    
    return new;
}

//prints out the item list
void printItemList(const ItemsT *list)
{
    BinsT *temp = list->anchor;
    int i = 0;
    
    printf("Bin List Size: %d\n", list->size);
    while(temp!= NULL)
    {
        printf("Bin #%d ", i);
        printBin(temp);
        printf("\n");
        i++;
        temp = temp->nextBin;
        
    }
}
//free the memory allocated from the item list
void freeItemList(ItemsT *list)
{
    if(list == NULL)
    {
        return;
    }
    
    BinsT *temp1 = list->anchor;
    BinsT *temp2;
    
    while(temp1 != NULL)
    {
        temp2 = temp1->nextBin;
        freeBin(temp1);
        temp1 = temp2;
    }
    free(list);
            
}
//creates a new bin from bins.txt
BinsT *newBin(int size)
{
    int i;
    
    BinsT *bin = (BinsT *) malloc(sizeof(BinsT));
    bin->currentSize = bin->capacity = size;
    bin->numberOfItems = 0;
    bin->nextBin = NULL;
    
    for(i = 0; i < MAX_ITEM; i++)
    {
        bin->items[i] = -10;
    }
    
    return bin;
}
//checks to see if there is enough space in the bin to fit the item
int spaceCheck(BinsT *bin, int item)
{
    if(bin == NULL)
        exit(1);
    
    if(bin->capacity >= item)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
//puts the item in the bin
void putBin(BinsT *bin, int item)
{
    if(bin == NULL)
        exit(1);
    
    if(bin->numberOfItems >= MAX_ITEM)
        exit(1);
    
    bin->items[bin->numberOfItems] = item;
    bin->numberOfItems++;
    bin->capacity -= item;
}
//sets the bin and points to the next bin
void setBin(BinsT *bin, BinsT *nextbin)
{
    if(bin == NULL)
        exit(1);
    
    bin->nextBin = nextbin;
}
//print out the contents of the used bins
void printBin(BinsT *bin)
{
    if(bin == NULL)
    {
        fprintf(stderr, "printBin: NULL\n");
        exit(1);
    }
    int i;
    
    printf("Size: %d, ", bin->currentSize);
    printf("Space remaining: %d, ", bin->capacity);
    printf("Items contained: %d, ", bin->numberOfItems);
    
    if(!bin->numberOfItems)
    {
        printf("[ EMPTY ]");
    }
    else
    {
        for(i = 0; i < bin->numberOfItems; i++)
        {
            printf("Contains: %d ", bin->items[i]);
        }
    }
    printf("\n");
}

//frees the bin list
void freeList(ItemsT *list)
{
    if(list == NULL)
    {
        return;
    }
    
    BinsT *temp1 = list->anchor;
    BinsT *temp2;
    
    while(temp1 != NULL)
    {
        temp2 = temp1->nextBin;
        freeBin(temp1);
        temp1 = temp2;
    }
    
    free(list);
}

//free the bins 
void freeBin(BinsT *bin)
{
    if(bin == NULL)
        exit(1);
    
    free(bin);
}