#include "allocator.h"
#include <stdio.h>
#include <string.h>

static void *segment_start;
static size_t segment_size;
static size_t nused;

/* function: roundup
 * -----------------
 * Rounds _val_ up to the smallest multiple of _mult_ greater than 
 * or equal to _val_.
 */
size_t roundup(size_t val, size_t mult) {
	return (val + mult - 1) & ~(mult - 1);
}

int myinit(void *start, size_t size) {
	segment_start = start;
	segment_size = size;
	nused = 0;
	return 1;
};

void *mymalloc(size_t size) {
	size_t needed = roundup(size, ALIGNMENT);
	if (nused + needed > segment_size)
		return NULL;

	void *ptr = (char *)segment_start + nused;
	nused += needed;
	return ptr;
};

void *myrealloc(void *oldptr, size_t new_size) {
	void *newptr = mymalloc(new_size);
	memcpy(newptr, oldptr, new_size);
	myfree(oldptr);
	return newptr;
};

void myfree(void *ptr) {
}

/* function: dump_heap
 * -------------------
 * Helper function for that dumps heap contents.
 */
void dump_heap() {
	printf("Heap segment starts at addres %p, ends at %p. %lu bytes currently used.", segment_start, segment_start + segment_size, nused); 
	for (int i = 0; i < nused; i++) {
		unsigned char *cur = (unsigned char *)segment_start + i;
		if (i % 32 == 0)
			printf("\n%p", cur);

		printf("%02x ", *cur);
	}
	printf("\n");
}
