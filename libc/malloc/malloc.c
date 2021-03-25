#include "malloc.h"
#include "../string.h"
#include "../../devices/screen/screen.h"

heap_t kernel_heap;

static void __heap_init(heap_t* heap, int size)
{
    heap->base_addr = HIGHER_HALF_KERNEL;
    heap->free_mem_addr = heap->base_addr;
    heap->size = size * FRAME_SIZE;
    heap->first = 0, heap->last = 0; // NULL
}

void heap_init(void)
{
    __heap_init(&kernel_heap, 1024 * 2);
}

void print_int(int num)
{
    char str[10] = "";
    int_to_ascii(num, str);
    kprint(str);
}

static inline void* insert(heap_t* heap, heap_chunk_t* chunk, unsigned int size)
{
    chunk->data_size = size;

    if(heap->first == 0)
    {
        chunk->next = 0;
        chunk->prev = 0;
        heap->first = chunk;
        heap->last = chunk;
        return (void*)((unsigned long)chunk + sizeof(chunk));
    }else
    {        
        chunk->prev = heap->last;
        heap->last->next = chunk;
        heap->last = chunk;
        return (void*)((unsigned long)chunk + sizeof(chunk));
    }
}

void* kmalloc(unsigned int size)
{
    int physic_sz = size + sizeof(heap_chunk_t);
    heap_chunk_t* chunk;

    chunk = (heap_chunk_t*)kernel_heap.free_mem_addr;

    // todo: check if the heap still has free memory

    void* pointer = insert(&kernel_heap, chunk, size);
    kernel_heap.free_mem_addr += physic_sz;
    return pointer;
}

static inline void remove(heap_t* heap)
{
    if(heap->last == heap->first)
    {
        heap->first, heap->last = 0;
    }else
    {
        heap->last = heap->last->prev;
        heap->last->next = 0;
    }
    
}

void kfree(void* addr)
{
    heap_chunk_t* chunk;
    chunk = (heap_chunk_t*)((unsigned long)addr - sizeof(heap_chunk_t));
    if(chunk == kernel_heap.last)
    {
        remove(&kernel_heap);
        kernel_heap.free_mem_addr = chunk;
    }
}