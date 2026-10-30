#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <mcheck.h>
#include "allocator.h"

#define HEAP_START_HINT (void *)0x107000000L
#define HEAP_SIZE_HINT 401

int main() {
	printf("Testing allocator...\n");
  // malloc tracer
	mtrace();

	void *start_seg = mmap(HEAP_START_HINT, HEAP_SIZE_HINT, PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	if (start_seg == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	size_t asize = sizeof(char) * 21;
	myinit(start_seg, HEAP_SIZE_HINT);
	char *ptr = (char *)mymalloc(asize); // intentionally unaligning
																						 //
	char *mallocptr = (char *)malloc(asize);
	strcpy(ptr, "cat");
	void *newptr = myrealloc(ptr, 32);

	free(mallocptr);

  // closes tracer
	muntrace();
	return 0;
}

