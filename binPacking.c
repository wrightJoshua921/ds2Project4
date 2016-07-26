/* 
 * File:   binPacking.c
 * Author: Joshua Wright
 * Project Number: 4
 * Created on October 28, 2015, 9:51 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bin.h"

/*
 * This Program takes the amount of bins and there sizes and puts those on 
 * a linked list. The program then takes the total number of runs, the items
 * per run and that runs items and puts them in bins that fit if that bin does not
 * fit, the program creates another bin, if the next bin doesn't fit, that item
 * is discarded and the next item is tried to fit, and so on.
 * 
 * 
 */


struct packingIcons{
    ItemsT *firstFitOnline;
    ItemsT *nextFitOnline;
    ItemsT *bestFitOnline;
    ItemsT *firstFitOffline;
    ItemsT *bestFitOffline;
};

/*
 * 
 */

void argC(int argc, char *argv[], int **bins, int ***items, int *numRuns, int **itemsPerRun);
void initLists(int firstBin, struct packingIcons *new);
void firstFit(ItemsT *list, const int *bins, const int *items, int itemsPerRun);
void nextFit(ItemsT *list, const int *bins, const int *items, int itempsPerRun);
void bestFit(ItemsT *list, const int *bins, const int *items, int itemsPerRun);
void printLists(struct packingIcons *new);
void freeLists(struct packingIcons *new);
void simpleSort(int *array, int left, int right);
int partition(int * array, int left, int right);


int main(int argc, char** argv) 
{
    //initializes my variables
    int i, numRuns, *bins = NULL, **items = NULL, *itemsPerRun = NULL;
    struct packingIcons PL;
    //gets the bins from bins.txt and items from binitems.txt
    argC(argc, argv, &bins, &items, &numRuns, &itemsPerRun);
    
   for(i = 0; i < numRuns; i++)
    {
       //creates the lists and performs the operations
        printf("Run #%d\n", i);
        initLists(bins[0], &PL);
        printf("Online First Fit\n");
        firstFit(PL.firstFitOnline, bins, items[i], itemsPerRun[i]);
        printf("Online Next Fit\n");
        nextFit(PL.nextFitOnline, bins, items[i], itemsPerRun[i]);
        printf("Online Best Fit\n");
        bestFit(PL.bestFitOnline, bins, items[i], itemsPerRun[i]);
        
        simpleSort(items[i], 0, itemsPerRun[i] - 1);
        printf("Offline First Fit\n");
        firstFit(PL.firstFitOffline, bins, items[i], itemsPerRun[i]);
        printf("Offline Best Fit\n");
        bestFit(PL.bestFitOffline, bins, items[i], itemsPerRun[i]);
        printf("\n");
        
        printLists(&PL);
        freeLists(&PL);
    }
 
   
    return (EXIT_SUCCESS);
}
//function to handle the .txt files and puts them into linked lists
 void argC(int argc, char *argv[], int **bins, int ***items, int *numRuns, int **itemsPerRun)
{
    FILE *fp;
    int i, j;
    
    fp = fopen("bins.txt", "r");
    if(fp == NULL)
    {
        fprintf(stderr, "Could not open FILE");
        exit(1);
    }
    
    *bins = (int *) malloc(1000 * sizeof(int));
    for(i = 0; i < 1000; i++)
    {
        fscanf(fp, "%d", &(*bins)[i]);
    }
    fclose(fp);
    
    fp = fopen("binItems.txt", "r");
    if(fp == NULL)
    {
        fprintf(stderr, "Could not open FILE");
        exit(1);
    }
    
    fscanf(fp, "%d", numRuns);
    *items = (int **) malloc(*numRuns * sizeof(int *));
    *itemsPerRun = (int *) malloc(*numRuns * sizeof(int));
    
    for(i = 0; i < *numRuns; i++)
    {
     fscanf(fp, "%d", &(*itemsPerRun)[i]);
     (*items)[i] = (int *) malloc((*itemsPerRun)[i] * sizeof(int));
     
     for(j = 0; j < (*itemsPerRun)[i]; j++)
     {
         fscanf(fp, "%d", &(*items)[i][j]);
     }
    }
    fclose(fp);
 }

//initialize the lists that holds the solutions
 void initLists(int firstBin, struct packingIcons *new)
{
    new->firstFitOnline = newItemList(firstBin);
    new->nextFitOnline = newItemList(firstBin);
    new->bestFitOnline = newItemList(firstBin);
    new->firstFitOffline = newItemList(firstBin);
    new->bestFitOffline = newItemList(firstBin);
}
 //performs the firstfit algorithm
void firstFit(ItemsT *list, const int *bins, const int *items, int itemsPerRun)
{
    int i;
    BinsT *temp;
    
    for(i = 0; i < itemsPerRun; i++)
    {
        temp = list->anchor;
    
        if(items[i] > 100)
        {
            printf("Throwing out item %d\n", items[i]);
            continue;
        }
        else if(items[i] < 0)
        {
            fprintf(stderr, "NEGATIVE ITEM");
            continue;
        }
    
        while(temp != NULL)
        {
            if(spaceCheck(temp, items[i]))
            {
                putBin(temp, items[i]);
                printf("Placing item %d in bin %d\n", items[i], temp->currentSize);
                break;
            }
            else
            {
                temp = temp->nextBin;
            }
        }
        
        if(temp == NULL)
        {
            temp = add2End(list, bins[list->size]);
            if(spaceCheck(temp, items[i]))
            {
                putBin(temp, items[i]);
                printf("Placing item %d in bin %d.\n", items[i], temp->currentSize);
            }
            else
            {
                printf("Throwing out item %d.\n", items[i]);
            }
        }
    }
    printf("\n\n");
}

//performs the nextFit algorithm
void nextFit(ItemsT *list, const int *bins, const int *items, int itemsPerRun)
{
   int i;
   BinsT *temp;
    
    for (i = 0; i < itemsPerRun; i++)
    {
        if (items[i] > 100) 
        { 
            printf("Throwing out item %d\n ", items[i]);
            
        }
        else if (items[i] < 0)
        {
            printf("Throwing out item %d\n ", items[i]);
            
        }
        
        if (spaceCheck(list->tail, items[i]))
        {
            putBin(list->tail, items[i]);
            printf("Placing item %d in bin %d\n ", items[i], list->tail->currentSize);
        } 
        else
        {
            temp = add2End(list, bins[list->size]);
            if (spaceCheck(temp, items[i]))
            { 
                putBin(temp, items[i]);
                printf("Placing item %d in bin %d\n", items[i], temp->currentSize);
            } 
            else
            {
                printf("Throwing out item %d\n", items[i]);
            
            }
        }
    }
   printf("\n\n");
} 
//performs the bestFit algorithm
void bestFit(ItemsT *list, const int *bins, const int *items, int itemsPerRun)
{
    int i; 
    BinsT *temp, *best;
    
    for(i = 0; i < itemsPerRun; i++)
    {
        temp = list->anchor, best = NULL;
        
        if(items[i] > 100)
        {
            printf("Throwing out item %d\n", items[i]);
            
        }
        else if(items[i] < 0)
        {
            printf("Throwing out item %d\n", items[i]);
            
        }
        
        while(temp != NULL)
        {
            if(best == NULL && spaceCheck(temp, items[i]))
            {
                best = temp;
            }
            else if(spaceCheck(temp, items[i]) && temp->capacity < best->capacity)
            {
                best = temp;
            }
             temp = temp->nextBin;
        }
        if(best != NULL && spaceCheck(best, items[i]))
        {
            putBin(best, items[i]);
            printf("Placing item %d in bin %d\n", items[i], best->currentSize);
        }
        else
        {
            temp = add2End(list, bins[list->size]);
            if(spaceCheck(temp, items[i]))
            {
                putBin(temp, items[i]);
                printf("Placing item %d in bin %d\n", items[i], temp->currentSize);
            }
            else
            {
                printf("Throwing out item %d\n", items[i]);
            
            }
            }
        }
    printf("\n\n");
    }

//print out the table of the bins used and the discards
void printLists(struct packingIcons *new) 
{
    printf("            Online algorithms\n");
    printf("First Fit: Bins Used:        %d\n", new->firstFitOnline->size);
    printf("Next Fit:  Bins Used:        %d\n", new->nextFitOnline->size);
    printf("Best Fit:  Bins Used:        %d\n", new->bestFitOnline->size);
    printf("            Offline algorithms\n");
    printf("First Fit: Bins Used:        %d\n", new->firstFitOffline->size);
    printf("Best Fit:  Bins Used:        %d\n", new->bestFitOffline->size);
    printf("\n");
}

//frees the solutions lists
void freeLists(struct packingIcons *new)
{
    freeItemList(new->firstFitOnline);
    freeItemList(new->nextFitOnline);
    freeItemList(new->bestFitOnline);
    freeItemList(new->firstFitOffline);
    freeItemList(new->bestFitOffline);
}
//conducts a simpleSort for the offline performance
void simpleSort(int *array, int left, int right)
{
    int index = partition(array, left, right);
    if(left < index - 1) simpleSort(array, left, index - 1);
    if(index < right) simpleSort(array, index, right);
}
int partition(int * array, int left, int right)
{
    int i = left, j = right;
    int temp;
    int pivot = (left + right) / 2;
    
    while( i <= j)
    {
        while(array[i] > array[pivot]) i++;
        while(array[pivot] > array[j]) j--;
        if(i <= j)
        {
            temp = array[i];
            array[i] = array[j];
            array[j] = array[i];
	    array[j] = temp;
            i++; j--;
        }
    }
    return i;
}


