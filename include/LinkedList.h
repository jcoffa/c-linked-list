/*
 * @file LinkedListAPI.h
 * @author CIS*2750 S18 (based on the ListADT from CIS*2520, S17)
 * @date May 2018
 * @brief File containing the function definitions of a doubly linked list
 */

#ifndef _LIST_API_
#define _LIST_API_

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**************
 * STRUCTURES *
 **************/

/*
 * Node of a linked list. This list is doubly linked, meaning that it has points to both the node immediately in front 
 * of it, as well as the node immediately behind it.
 */
typedef struct listNode{
    void *data;
    struct listNode *previous;
    struct listNode *next;
} ListNode;


/*
 * Metadata head of the list. 
 * Contains no actual data but contains
 * information about the list (head and tail) as well as the function pointers
 * for working with the abstracted list data.
 */
typedef struct listHead{
    ListNode *head;
    ListNode *tail;
    int length;
    void (*deleteData)(void* toBeDeleted);
    int (*compare)(const void* first,const void* second);
    char *(*printData)(void* toBePrinted);
} List;


/*
 * List iterator structure.
 * It represents an abstract object for iterating through the list.
 * The list implemntation is hidden from the user
 */
typedef struct iter{
    ListNode *current;
} ListIterator;


/*************
 * FUNCTIONS *
 *************/

/**
 * Function to initialize the list metadata head to the appropriate function pointers.
 * Allocates memory to the struct.
 * 
 * @param printFunction function pointer to print a single node of the list
 * @param deleteFunction function pointer to delete a single piece of data from the list
 * @param compareFunction function pointer to compare two nodes of the list in order to test for equality or order
 * @return pointer to the list head
 */
List *initializeList(char *(*printFunction)(void *toBePrinted), void (*deleteFunction)(void *toBeDeleted), int (*compareFunction)(const void *first, const void *second));


/**
 * Deletes the entire linked list, freeing all memory.
 * Uses the supplied function pointer to release allocated memory for the data.
 *
 * @pre 'List' type must exist and be used in order to keep track of the linked list.
 * @param list pointer to the List-type dummy node
 * @return  on success: NULL, on failure: head of list
 */
void freeList(List *list);


/**
 * Clears the list: frees the contents of the list - ListNode structs and data stored in them - 
 * without deleting the List struct. Uses the supplied function pointer to release allocated memory for the data.
 *
 * @pre 'List' type must exist and be used in order to keep track of the linked list.
 * @post List struct still exists, list head = list tail = NULL, list length = 0
 * @param list pointer to the List-type dummy node
 */
void clearList(List *list);


/**
 * Function for creating a node for the linked list. 
 * This node contains abstracted (void *) data as well as previous and next
 * pointers to connect to other nodes in the list
 *
 * @pre data should be of same size of void pointer on the users machine to avoid size conflicts.
 *      data must be valid. data must be cast to void pointer before being added.
 * @post data is valid to be added to a linked list
 * @return On success returns a node that can be added to a linked list. On failure, returns NULL.
 * @param data a void * pointer to any data type.  Data must be allocated on the heap.
 */
ListNode *initializeListNode(void *data);


/**
 * Inserts a ListNode at the front of a linked list. List metadata is updated
 * so that head and tail pointers are correct.
 *
 * @pre 'List' type must exist and be used in order to keep track of the linked list.
 * @param list pointer to the dummy head of the list
 * @param toBeAdded a pointer to data that is to be added to the linked list
 */
void insertBack(List *list, void *toBeAdded);


/**
 * Inserts a ListNode at the front of a linked list.  List metadata is updated
 * so that head and tail pointers are correct.
 *
 * @pre 'List' type must exist and be used in order to keep track of the linked list.
 * @param list pointer to the dummy head of the list
 * @param toBeAdded a pointer to data that is to be added to the linked list
 */
void insertFront(List *list, void *toBeAdded);


/**
 * Returns a pointer to the data at the front of the list. Does not alter list structure.
 *
 * @pre The list exists and has memory allocated to it
 * @param the list struct
 * @return pointer to the data located at the head of the list
 */
void *getFromFront(List *list);


/**
 * Returns a pointer to the data at the back of the list. Does not alter list structure.
 *
 * @pre The list exists and has memory allocated to it
 * @param the list struct
 * @return pointer to the data located at the tail of the list
 */
void *getFromBack(List *list);


void *deleteDataFromList(List *list, void *toBeDeleted);


/**
 * Uses the comparison function pointer to place the element in the 
 * appropriate position in the list.
 *
 * Should be used as the only insert function if a sorted list is required.  
 *
 * @pre List exists and has memory allocated to it. ListNode to be added is valid.
 * @post The node to be added will be placed immediately before or after the first occurrence of a related node
 * @param list a pointer to the dummy head of the list containing function pointers for delete and compare, as well 
 *        as a pointer to the first and last element of the list.
 * @param toBeAdded a pointer to data that is to be added to the linked list
 */
void insertSorted(List *list, void *toBeAdded);


/**
 * Returns a string that contains a string representation of the list traversed from head to tail. 
 * Utilize an iterator and the list's printData function pointer to create the string.
 * returned string must be freed by the calling function.
 *
 * @pre List must exist, but does not have to have elements.
 * @param list Pointer to linked list dummy head.
 * @return On success: char * to string representation of list (must be freed after use).
 *         On failure: NULL
 */
char *toString(List *list);


ListIterator createIterator(List *list);


void *nextElement(ListIterator *iter);


int getLength(List *list);


void *findElement(List *list, bool (*customCompare)(const void *first,const void *second), const void *searchRecord);

#endif

