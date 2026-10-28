# Goal

Understand how a heap allocator works, and how to implement one.

# Roadmap

## 1. Build a bump allocator

- [ ] Obtain a fixed region of memory and return successive aligned portions of it. Initially, don't support freeing individual blocks.

- [ ] Learn: alignment, pointer arithmetic, headers, overflow checks, and how an allocator manages its own metadata.

- [ ] Done when: every valid allocation lies within the arena and is correctly aligned.

## 2. Implement an implicit free list

- [ ] Add block headers containing size and allocation status. Implement first-fit search, block splitting, free(), and reuse of freed blocks.

- [ ] Learn: internal and external fragmentation, minimum block sizes, and how to traverse blocks safely.

- [ ] Done when: a freed block can be reused without requesting additional memory.

## 3. Add coalescing and an explicit free list

- [ ] Maintain links between free blocks, merge adjacent free blocks, and implement a strategy for removing and inserting blocks in the free list.

- [ ] Learn: boundary tags, doubly linked lists, invariants, and the trade-off between search speed and memory utilization.

- [ ] Done when: freeing neighboring blocks produces a reusable larger block, and the free list remains consistent.

## 4. Implement realloc() and harden the allocator

- [ ] Handle shrinking, expansion into adjacent free space, and moving a block when necessary. Add calloc() if you want to complete the standard allocation interface.

- [ ] Learn: preserving data, failure handling, and complex allocation lifetimes.

- [ ] Done when: tests verify that existing data is preserved according to the allocation interface's requirements.

## 5. Measure and experiment

- [ ] Compare first-fit with best-fit, different splitting thresholds, and alternative free-list designs. Record allocation throughput and peak utilization under repeatable workloads.

- [ ] Learn: how to distinguish a theoretically attractive design from one that performs well in practice.

# Resources

1. Textbook: CSAPP by Bryant, O'Hallaron

2. [Stanford CS107 Heap Allocator Assignment](https://web.stanford.edu/class/archive/cs/cs107/cs107.1222/assign6/)
3. [Illinois CS341 Malloc Tutorial](https://cs341.cs.illinois.edu/coursebook/Malloc?utm_source=chatgpt.com)
4. [ANU Lab: Building Dynamic Memory Allocators](https://comp.anu.edu.au/courses/comp2310/labs/05-malloc/?utm_source=chatgpt.com#outline)
5. malloc(3), mmap(2), munmap(2), mprotect(2), and getpagesize(2)

# Tools
- gcc or clang
- gdb
- [ASan](https://github.com/google/sanitizers/wiki/addresssanitizer), [UBSan](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html)
- [valgrind](https://valgrind.org/)
- [perf](https://perfwiki.github.io/main/)
- make

# Further Readings after Implementation

- [jemalloc docs and code](https://jemalloc.net/)
- [mimalloc code repo](https://github.com/microsoft/mimalloc)

# Recommendation and Cautionary Words from the GPT Chatz
 
_My strongest recommendation: start with the Stanford assignment and CS:APP §9.9. Implement each stage in your own C project, and write a heap-validation routine before attempting performance optimizations. Being able to prove your allocator's internal invariants and diagnose corruption is the most valuable skill you'll develop from this project._

