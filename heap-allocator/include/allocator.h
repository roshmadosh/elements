#ifndef _ALLOCATOR_H
#define _ALLOCATOR_H

#include <stddef.h>
#define ALIGNMENT (1 << 3)

#define MAX_REQ_SIZE (1 << 30)

/* Function: myinit
 * ----------------
 * Resets the heap to an empty state. Returns 1 if successful.
 */
int myinit(void *segment_start, size_t segment_size);

void *mymalloc(size_t size);

void *myrealloc(void *ptr, size_t new_size);

void myfree(void *ptr);

#endif
