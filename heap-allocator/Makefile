CC = gcc
CFLAGS = -g -Iinclude 
malloc_trace = ./malloc_trace
malloc_dbg_so = /usr/lib64/libc_malloc_debug.so.0
exec=my_allocator

alloc:
	mkdir bin
	${CC} ${CFLAGS} ${exec}.c src/bump.c -o bin/${exec}
	MALLOC_TRACE=${malloc_trace} LD_PRELOAD=${malloc_dbg_so} ./bin/${exec}

clean:
	rm -rf build/ bin/ ${malloc_trace}

debug:
	gdb -q ./bin/${exec}


