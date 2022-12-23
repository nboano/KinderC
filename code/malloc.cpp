#include "../kinderc.hpp"
#pragma once

#define OFFSET_BASE ((unsigned long)&__heap_base)

#define MALLOC_SPACE 1

unsigned long memsz = 0;


bool malloc_initialized = false;
void* heap_start;
void* heap_end;

void malloc_init() {
	heap_start = (void*)OFFSET_BASE;
	heap_end = (void*)OFFSET_BASE;

	malloc_initialized = true;
}

typedef struct s_memblock {
	bool available;
	unsigned long size;
} memblock;

void free(void* ptr) {
	memblock* mcb = (memblock*)((unsigned long)ptr - sizeof(memblock));
	mcb->available = true;
}

void* malloc(unsigned long size) {
	while((unsigned long)heap_end + size > Memory::GetSize()) Memory::Grow(1);

	memblock* loc_mcb;
	void* returned_location = 0;

	if(!malloc_initialized) malloc_init();

	void* loc = heap_start;

	size += sizeof(memblock) + MALLOC_SPACE;

	while(loc != heap_end) {
		loc_mcb = (memblock*)loc;
		if(loc_mcb->available && loc_mcb->size >= size) {
			loc_mcb->available = false;
			returned_location = loc;
			break;
		}
		loc = (void*)((unsigned long)loc + loc_mcb->size);
	}

	if(returned_location == 0) {
		returned_location = heap_end;
		heap_end = (void*)((unsigned long)heap_end + size);
		loc_mcb = (memblock*)returned_location;
		loc_mcb->available = false;
		loc_mcb->size = size;
	}

	returned_location = (void*)((unsigned long)returned_location + sizeof(memblock));

	return returned_location;
}


void* memset(void* s, int c, unsigned long len)
{
	unsigned char* p = (unsigned char*)s;
	while (len--)
	{
		*p++ = (unsigned char)c;
	}
	return s;
}
void* memcpy(void* dest, const void* src, unsigned long n)
{
	char* csrc = (char*)src;
	char* cdest = (char*)dest;
	for (int i = 0; i < n; i++)
		cdest[i] = csrc[i];
	return 0;
}

void* operator new(unsigned long size) {
	return malloc(size);
}
void* operator new[](unsigned long size){
	return malloc(size);
}
void operator delete(void* ptr) noexcept {
	free(ptr);
}
void operator delete[](void* ptr) noexcept {
	free(ptr);
}

void* Memory::Allocate(unsigned long size) {
	return malloc(size);
}
void Memory::Free(void* ptr) {
	free(ptr);
}
void Memory::Grow(int blocks) {
	memory_grow(blocks);
	memsz += 65536*blocks;
}
unsigned long Memory::GetSize() {
	if (memsz == 0) memsz = get_memory_size();
	return memsz;
}