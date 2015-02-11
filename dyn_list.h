#ifndef _DYN_ARRAY_H_
#define _DYN_ARRAY_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct dyn_list *Array;

/*initialize array*/
Array newArray(int starting_values[], size_t length);

/*destruct array*/
void freeArray(Array a);


/*BASIC INDEXING*/
//returns element value at given index, or 0 if index is not set with an element
int valueAt(Array a, size_t index);

//updates the element value at the given index and returns the array length
//will fill up the array if needed
size_t setValue(Array a, size_t index, int value);


/*STACK OPERATIONS*/
//adds element to the end of the list and returns the new array length
size_t push(Array a, int value);

//removes element from the end of the list and returns the removed element value
int pop(Array a);

//inspects last element
int peek(Array a);


/*INSERTION & DELETION*/
//inserts element at given position and moves the following elements one index further
//will fill up the array if needed
//returns the new array length
size_t insert(Array a, size_t index, int value);

//deletes the element at the given position and returns the deleted element value
//if there if no element at that index, 0 will be returned
int delete(Array a, size_t index);


/*INFO ON ARRAY*/
//get length of array
size_t length(Array a);

//ask if array has element with given value
bool contains(Array a, int value);

//info if array is empty
bool isEmpty(Array a);

//get index of first element with value
int indexOf(Array a, int value);

//returns first index of element with value, starting from offset, -1 if not found
int indexOfFromOffset(Array a, size_t offset, int value);


/*ARRAY TRANSFORMATION*/
//transform to dynamic to static array
int *toStaticArray(Array a);

/*clears array of all elements*/
void clear(Array a);
#endif
