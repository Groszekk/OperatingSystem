#ifndef MALLOC_H
#define MALLOC_H

#define HIGHER_HALF_KERNEL 0xc00000
#define FRAME_SIZE 0x1000 // 4kB

typedef struct heap_chunk
{
    struct heap_elem* next;
    struct heap_elem* prev;
    unsigned int data_size;
} heap_chunk_t;

typedef struct heap
{
    unsigned int base_addr;
    unsigned int size;
    unsigned int free_mem_addr;
    heap_chunk_t* first;
    heap_chunk_t* last;     
} heap_t;

void* kmalloc(unsigned int size);
void kfree(void* addr);
void heap_init(void);

#endif