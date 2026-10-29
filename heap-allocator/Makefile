CC = gcc
CFLAGS = -g -Iinclude
objs = build/mmap.o 
exec = my_mmap 

${exec}: ${objs}
	${CC} ${CFLAGS} $^ -o $@

${objs}: build/%.o: src/%.c
	mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $^ -o $@

clean:
	rm -rf build/ ${exec} my_allocator

alloc:
	${CC} ${CFLAGS} main.c src/bump.c -o my_allocator

debug:
	gdb -q ./my_allocator
