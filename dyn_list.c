#include "dyn_list.h"
#include <stdio.h>

struct dyn_list {
	struct element *first;
	struct element *last;
	size_t length;
};

struct element {
	int value;
	struct element *next;
};

static struct element *newElement(int value, struct element *next);
static struct element *findElement(struct element *to_find, size_t length);
static struct element *fillList(Array a, size_t index);
static int searchIndexOf(struct element *cur, size_t offset, size_t length, int value);



/*** PUBLIC ***/

/*++++++++++++++++++++++++++++++*/
/* Array creation / destruction */
/*++++++++++++++++++++++++++++++*/

/*allocates new array struct, allocates length elements*/
Array newArray(int starting_values[], size_t length)
{
	Array a = malloc(sizeof(struct dyn_list));
	*a = (struct dyn_list) {.first = NULL, .last = NULL, .length = length};

	if(length) {
		a->first = newElement(starting_values[0], NULL);	//create first element
		a->last = a->first;

		for(size_t i = 1; i < length; i++) {		//add rest of elements
			a->last->next = newElement(starting_values[i], NULL);
			a->last = a->last->next;
		}
	} 

	return a;
}

/*frees all element allocs of the given array struct, frees array struct itself afterwards*/
void freeArray(Array a)
{
	clear(a);						//free elements
	free(a);						//free array struct itself
}


/*+++++++++++++++++++++++++++*/
/* 	 	Basic indexing	 	 */
/*+++++++++++++++++++++++++++*/

/*returns element value at given index, or 0 if index is out of bounds*/
int valueAt(Array a, size_t index)
{
	return index < a->length ? findElement(a->first, index)->value : 0;
}

/*sets the value of the element at the given position. fills up array if needed*/
/*returns new array length*/
size_t setValue(Array a, size_t index, int value)
{
	if(index < a->length) {								//element exists: change value
		findElement(a->first, index)->value = value;
	} else {											//set element over index boundary:
		a->last = fillList(a, index);					//fill array until index
		a->last->value = value;							//set value of new last
	}

	return a->length;
}



/*+++++++++++++++++++++++++++*/
/* 	 Insertion / deletion	 */
/*+++++++++++++++++++++++++++*/

/*Inserts element at given position and moves following elements up one position*/
/*Fills up array if needed. Returns new array length.*/
size_t insert(Array a, size_t index, int value)
{
	if(index == 0) {									//insertion at beginning
		a->first = newElement(value, a->first);
		if(!a->last)									//if array was empty:
			a->last = a->first;							//set new last
		a->length++;

	} else if(index < a->length) {						//insertion in the middle
		struct element *el_before_index = findElement(a->first, index-1);
		struct element *new_el = newElement(value, el_before_index->next);
		el_before_index->next = new_el;
		a->length++;

	} else {											//insertion over array boundary
		a->last = fillList(a, index);					//fill array until index
		a->last->value = value;							//set the value of new last
	}

	return a->length;
}

/*deletes the element at given index and returns the deleted elements' value*/
/*returns 0 if index is out of array bounds*/
int delete(Array a, size_t index)
{
	if(index >= a->length) return 0;

	struct element *to_delete;
	int to_return;

	if(index == 0) {									//deletion of first element
		to_delete = a->first;
		a->first = to_delete->next;						//set new first
		if(a->length == 1)								//if deletion of only element in array
			a->last = NULL;								//set last NULL

	} else if(index == a->length-1) {					//deletion of last element
		to_delete = a->last;
		a->last = findElement(a->first, index-1);		//set new last
		a->last->next = NULL;							//let new last point to NULL

	} else {											//deletion in middle
		struct element *el_before_index = findElement(a->first, index-1);
		to_delete = el_before_index->next;				//element before deleted element
		el_before_index->next = to_delete->next;		//has to point to el. after del. el.
	}

	a->length--;

	to_return = to_delete->value;
	free(to_delete);
	return to_return;
}


/*+++++++++++++++++++++++++++*/
/* 	 	Stack operations 	 */
/*+++++++++++++++++++++++++++*/

/*adds element to end of array, returns new array length*/
size_t push(Array a, int value)
{
	return insert(a, a->length, value);
}

/*removes last element in the array and returns its value, or 0 if array is empty*/
int pop(Array a)
{
	return delete(a, a->length-1);
}

/*returns value of last element, or 0 if list is empty*/
int peek(Array a)
{
	return a->last ? a->last->value : 0;
}


/*+++++++++++++++++++++++*/
/* 	 	Array info		 */
/*+++++++++++++++++++++++*/

/*returns length of given array*/
size_t length(Array a)
{
	return a->length;
}

/*returns true if array has element with value, false otherwise*/
bool contains(Array a, int value)
{
	for(struct element *cur = a->first; cur; cur = cur->next)
		if(cur->value == value) return true;

	return false;
}

/*returns true if array is empty, false otherwise*/
bool isEmpty(Array a)
{
	return !a->length;
}

/*returns first index of element with value, -1 if not found*/
int indexOf(Array a, int value)
{
	return a->length ? searchIndexOf(a->first, 0, a->length, value) : -1;
}

/*returns first index of element with value, starting from offset, -1 if not found*/
int indexOfFromOffset(Array a, size_t offset, int value)
{
	if(offset >= a->length) return -1;

	return searchIndexOf(findElement(a->first, offset), offset, a->length, value);
}


/*+++++++++++++++++++++++++++++++*/
/* 	 	Array transformation	 */
/*+++++++++++++++++++++++++++++++*/

/*transforms dynamic array to static array or correct size*/
int *toStaticArray(Array a)
{
	int *static_array = malloc(a->length * sizeof(int));

	struct element *cur = a->first;
	for(size_t i = 0; i < a->length; i++) {
		static_array[i] = cur->value;
		cur = cur->next;
	}

	return static_array;
}

/*clears the array of all elements*/
void clear(Array a)
{
	while(!isEmpty(a))
		pop(a);
}



/*** PRIVATE ***/

/*creates new element for the list with given values, returns pointer to it*/
static struct element *newElement(int value, struct element *next)
{
	struct element *new_el = malloc(sizeof(struct element));
	*new_el = (struct element) {.value = value, .next = next};
	return new_el;
}

/*returns element at index position of linked list*/
/*to_find must be non-NULL when calling this function!*/
static struct element *findElement(struct element *to_find, size_t index)
{
	for(size_t i = 0; i < index; i++)
		to_find = to_find->next;

	return to_find;
}

/*fills array up to index, returns pointer to new last element*/
static struct element *fillList(Array a, size_t index)
{
	if(a->length == 0) {							//if empty array:
		a->first = a->last = newElement(0, NULL);	//make initial element
		a->length++;
	}
	for(size_t i = a->length; i <= index; i++) {	//fill up array until index
		a->last->next = newElement(0, NULL);
		a->last = a->last->next;
		a->length++;
	}
	return a->last;
}

/*searches array for first element with value, starting from offset*/
/*returns the first index, or -1 if value not found*/
static int searchIndexOf(struct element *cur, size_t offset, size_t length, int value)
{
	for(size_t i = offset; i < length; i++) {
		if(cur->value == value)
			return i;
		cur = cur->next;
	}
	return -1;
}
