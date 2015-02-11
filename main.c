#include "dyn_list.h"
#include <stdio.h>

int main()
{
	Array myArray;

	puts("\n**** PUSH POP TESTS ****");
	puts("Initializing array with values 3, 6, 9");
	myArray = newArray((int []){3,6,9}, 3);
	printf("Length of array after initialization: %lu\n", length(myArray));

	puts("Pushing value 1");
	printf("Length of array after push: %lu\n", push(myArray, 1));

	puts("Performing 4 pops...");
	printf("First popped value: %d\n", pop(myArray));
	printf("Second popped value: %d\n", pop(myArray));
	printf("Third popped value: %d\n", pop(myArray));
	printf("Fourth popped value: %d\n", pop(myArray));

	puts("Pushing value 9 on empty array");
	printf("Length of array after push: %lu\n", push(myArray, 9));
	printf("Peeking top value: %d\n", peek(myArray));

	printf("Popping top value: %d\n", pop(myArray));
	printf("Peeking top value of empty array: %d\n", peek(myArray));
	printf("Popping top value of empty array: %d\n", pop(myArray));
	printf("Length of array: %lu\n", length(myArray));
	
	freeArray(myArray);


	puts("\n**** BASIC INDEXING TESTS ****");
	puts("Initializing empty array");
	myArray = newArray(NULL, 0);
	printf("Length of array after setting value 123 at index 0: %lu\n", setValue(myArray, 0, 123));
	printf("Length of array after setting value 22 at index 6: %lu\n", setValue(myArray, 6, 22));
	printf("Peeking top value: %d\n", peek(myArray));
	printf("Popping value: %d\n", pop(myArray));
	printf("Length of array: %lu\n", length(myArray));

	puts("Setting value 99 at index 2");
	setValue(myArray, 2, 99);
	printf("Value of element with index 2: %d\n", valueAt(myArray, 2));
	printf("Value of element with out of bounds index %d: %d\n", 10, valueAt(myArray, 10));

	freeArray(myArray);


	puts("\n**** INSERTION / DELETION TESTS ****");
	puts("Initializing empty array");
	myArray = newArray(NULL, 0);
	printf("Value of deleted element at index 0: %d\n", delete(myArray, 0));
	printf("Length of array after inserting value 33 at index 0: %lu\n", insert(myArray, 0, 33));
	printf("Value of deleted element at index 0: %d\n", delete(myArray, 0));
	printf("Length of array: %lu\n", length(myArray));
	printf("Length of array after inserting value 44 at index 5: %lu\n", insert(myArray, 5, 44));
	printf("Value of deleted element at index 5: %d\n", delete(myArray, 5));
	printf("Length of array: %lu\n", length(myArray));
	printf("Length of array after inserting value 55 at index 3: %lu\n", insert(myArray, 3, 55));
	printf("Value of deleted element at index 3: %d\n", delete(myArray, 3));
	printf("Length of array: %lu\n", length(myArray));

	freeArray(myArray);



	puts("\n**** MIXED TESTS ****");
	puts("Initializing empty array");
	myArray = newArray(NULL, 0);
	printf("Starting length: %lu\n", length(myArray));
	printf("Peeking empty array: %d\n", peek(myArray));
	printf("Popping empty array: %d\n", pop(myArray));
	printf("Length after inserting value 5 at index 5: %lu\n", insert(myArray, 5, 5));
	printf("Value at index 5: %d\n", valueAt(myArray, 5));
	printf("Value at index 6 (out of bounds): %d\n", valueAt(myArray, 6));
	printf("Deleted value at index 6: %d\n", delete(myArray, 6));
	printf("Deleted value at index 5: %d\n", delete(myArray, 5));
	printf("Length after deletion: %lu\n", length(myArray));
	printf("Length after setting value 1 at index 0: %lu\n", setValue(myArray, 0, 1));
	printf("Length after inserting value 2 at index 0: %lu\n", insert(myArray, 0, 2));
	printf("Deleted value at index 0: %d\n", delete(myArray, 0));

	freeArray(myArray);

	puts("\n**** MORE MIXED TESTS ****");
	puts("Initializing empty with value 1");
	myArray = newArray((int[]){1}, 1);
	printf("Popping array of 1 element: %d\n", pop(myArray));
	printf("Length after popping: %lu\n", length(myArray));
	printf("Length after pushing value 22 on empty array: %lu\n", push(myArray, 22));
	printf("Deleting array of 1 element: %d\n", delete(myArray, 0));
	printf("Length after deletion: %lu\n", length(myArray));
	printf("Length after setting value 33 at index 0 of empty array: %lu\n", setValue(myArray, 0, 33));
	printf("Popping this val...\n");
	pop(myArray);
	printf("Length after inserting value 44 at index 0 of empty array: %lu\n", insert(myArray, 0, 44));
	if(contains(myArray, 44))
		puts("Array contains value 44!");
	if(contains(myArray, 55))
		puts("Array contains value 55!");

	freeArray(myArray);


	puts("\n**** ARRAY INFO / TRANSFORMATION TESTS ****");
	puts("Initializing array with values: 0,1,2,3,4,5,6,7,8,9");
	myArray = newArray((int[]){0,1,2,3,4,5,6,7,8,9}, 10);
	puts("Transforming to static array and printing out values of static array:");
	int *sa = toStaticArray(myArray);
	for(int i = 0; i < 10; i++)
		printf("%d ", sa[i]);
	putchar('\n');

	puts("Clearing dynamic array");
	clear(myArray);
	printf("Length after clear: %lu\n", length(myArray));
	if(isEmpty(myArray))
		puts("Array is Empty!");

	puts("Reallocating dynamic array with static array");
	freeArray(myArray);
	myArray = newArray(sa, 10);
	if(!isEmpty(myArray))
		puts("Array not empty!");

	printf("Value at index 5: %d\n", valueAt(myArray, 5));
	printf("First index with value 6: %d\n", indexOf(myArray, 6));

	puts("Setting value 2 at index 8");
	setValue(myArray, 8, 2);
	printf("First index of value 2, starting from index 2: %d\n", indexOfFromOffset(myArray, 2, 2));
	printf("First index of value 2, starting from index 3: %d\n", indexOfFromOffset(myArray, 3, 2));

	freeArray(myArray);
	free(sa);

	exit(EXIT_SUCCESS);
}
