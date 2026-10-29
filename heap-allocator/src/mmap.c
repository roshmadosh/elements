#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

/**
 * Just checking I get how mmap(2) works. Most of this is from the example given in the man page.
 */
int main(int argc, char **argv) {
	int fd;
	char *addr;
	off_t offset, page_offset; // signed int, cuz offsets can be negative
	size_t length; // size_t is for byte counts
	ssize_t bytes_written; // signed because error code of write(2) returns -1
	struct stat sb; // file status buffer

	if (argc < 3 || argc > 4) {
		fprintf(stderr, "%s file offset [length]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDONLY);

	if (fd == -1)
		handle_error("open");

	if (fstat(fd, &sb) == -1)
		handle_error("fstat");

	offset = atoi(argv[2]);

	if (offset >= sb.st_size) {
		fprintf(stderr, "offset is greater than total size of file. File size: %zu bytes\n", sb.st_size);
		exit(EXIT_FAILURE);
	}

	/* 
	 * I can only offset by a multiple of the page size, so we want the largest multiple of page size that's less than the offset (e.g. if offset is 4200 bytes, page offset is 4096 bytes).
	 * Page size minus 1 is 4095, which in bits is zero for the first 21 bits and 1's for the remaining 11. ~ flips the bits, & makes the RHS a bitmask so that everything before the 12th bit on the LHS is zeroed out, which guarantees page_offset is a multiple of the 2^12 = 4096, less than or equal to offset. 
	 * */
	page_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);

	// default length reads til end of file
	length = sb.st_size - offset;

	if (argc == 4) {
		size_t a = atoi(argv[3]);

		if (a < length) 
			length = a;	
	}

	/* The second arg has to include the bytes that come before the offset up until the page boundary, otherwise some bytes at the end won't be included */
	addr = mmap(NULL, length + offset - page_offset, PROT_READ, MAP_PRIVATE, fd, page_offset);

	if (addr == MAP_FAILED)
		handle_error("mmap");

	bytes_written = write(STDOUT_FILENO, addr + offset - page_offset, length);

	if (bytes_written != length) {
		if (bytes_written == -1) 
			handle_error("write");

		fprintf(stderr, "partial write\n");
		exit(EXIT_FAILURE);
	}

	munmap(addr, length + offset - page_offset);

	close(fd);

	exit(EXIT_SUCCESS);
}
