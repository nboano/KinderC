#pragma once

#define OFFSET_BASE 8192 + (unsigned long)&__heap_base

#define EMPTY_CELL 0
#define ALLOC_CELL 0x11
#define LAST_CELL 0x12
#define LAST_CELL_COUNT 4
#define SPACELEN 1

unsigned long memsz = 0;

unsigned long checkmem(unsigned long start, unsigned long size) {
	while ((unsigned long)start + size > Memory::GetSize())
		Memory::Grow(1);
	char* s = (char*)start;
	for (int i = 0; i < size; i++) {
		if (s[i] != EMPTY_CELL)
			return (start + i + 1);
	}
	return start;
}
void* getpos(unsigned long start, unsigned long size) {
	size += SPACELEN;
	unsigned long s = start;
	do
	{
		s = checkmem(s, size);
	} while (s != checkmem(s, size));
	return (void*)(s + SPACELEN);
}
int isendofmem(char* pt, int n) {
	for (int i = 0; i < LAST_CELL_COUNT - 1; i++)
	{
		if (pt[i + n] != LAST_CELL)
			return 0;
	}
	return 1;
}
void* malloc(unsigned long size) {
	char* pt = (char*)getpos(OFFSET_BASE, size + LAST_CELL_COUNT);
	for (int i = 0; i < size; i++)
	{
		pt[i] = ALLOC_CELL;
	}
	for (int i = 0; i < LAST_CELL_COUNT; i++)
	{
		pt[i + size] = LAST_CELL;
	}
	return pt;
}
void free(void* ptr) {
	int i = 0;
	char* p = (char*)ptr;
	while (isendofmem(p, i) == 0) {
		p[i] = EMPTY_CELL;
		i++;
	}
	for (int j = i; j < LAST_CELL_COUNT + i; j++)
	{
		p[j] = EMPTY_CELL;
	}
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
unsigned long memlen(char* pt) {
	char* s;
	for (s = pt; isendofmem(s, 0) == 0; s++);
	return(s - pt);
}
void* Memory::Allocate(unsigned long size) {
	return malloc(size);
}
void Memory::Free(void* ptr) {
	free(ptr);
}
void Memory::Grow(int blocks) {
	memory_grow(blocks);
	memsz += 65536;
}
unsigned long Memory::GetSize() {
	if (memsz == 0) memsz = get_memory_size();
	return memsz;
}