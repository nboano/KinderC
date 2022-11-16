#pragma once
#include "kinderc.hpp"

extern "C" {
	unsigned long get_memory_size();
	void memory_grow(int q);

	void* memset(void* s, int c, unsigned long len);
	void* memcpy(void* dest, const void* src, unsigned long n);

	unsigned char __heap_base;
	unsigned char __data_end;
}

#define OFFSET_BASE 8192 + (unsigned long)&__heap_base

#define EMPTY_CELL 0
#define ALLOC_CELL 0x11
#define LAST_CELL 0x12
#define LAST_CELL_COUNT 4
#define SPACELEN 1

exported void* malloc(unsigned long size);
exported void free(void* ptr);

unsigned long memlen(char* pt);

void* getpos(unsigned long start, unsigned long size);
unsigned long checkmem(unsigned long start, unsigned long size);
int isendofmem(char* pt, int n);

int atoi(char* str);

class Memory {
public:
	static void* Allocate(unsigned long size);
	static void Free(void* ptr);
	static void Grow(int blocks);
	static unsigned long GetSize();
};

unsigned long memsz = 0;

#include "code/malloc.cpp"