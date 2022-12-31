#pragma once
#include "../kinderc.hpp"

/// @brief Retrieves the current memory size.
/// @return The memory size, in bytes.
imported unsigned long get_memory_size();

/// @brief Expands the memory of q units. One unit is 65536 bytes long.
/// @param q The number of units
imported void memory_grow(int q);

/// @brief Sets all the bytes of a memory area to the same value.
/// @param s Memory area pointer.
/// @param c Value to set.
/// @param len Memory area lenght (in bytes).
/// @return Memory area pointer.
imported void* memset(void* s, int c, unsigned long len);

/// @brief Copies all the bytes of a memory area from one place to another.
/// @param dest The destination memory area.
/// @param src The source memory area.
/// @param n The areas byte lenght.
/// @return The destination memory area.
imported void* memcpy(void* dest, const void* src, unsigned long n);

/// @brief Heap pointer. All the pointers created using malloc point to this area.
imported unsigned char __heap_base;

/// @brief End of the stack data pointer.
imported unsigned char __data_end;

/// @brief Given a size (in bytes), allocates enough space in the heap memory. This function is accessible from JavaScript.
/// @param size The allocated block size
/// @return A pointer to the allocated space.
/// @exception OutOfMemory
/// @example char* myString = (char*)malloc(25); strcpy(myString, "Hello World");
exported void* malloc(unsigned long size);

/// @brief Given a pointer returned by a malloc, clears the data associated.
/// @param ptr The pointer.
/// @example char* myString = (char*)malloc(25); strcpy(myString, "Hello World"); free(myString);
exported void free(void* ptr);

/// @brief Class that manages the program memory.
class Memory {
public:

    /// @brief Alias for malloc(). Given a size (in bytes), allocates enough space in the heap memory. This function is accessible from JavaScript.
    /// @param size The allocated block size
    /// @return A pointer to the allocated space.
    /// @exception OutOfMemory
    /// @example char* myString = (char*)malloc(25); strcpy(myString, "Hello World");
    static void* Allocate(unsigned long size);

    /// @brief Alias for free(). Given a pointer returned by a malloc, clears the data associated.
    /// @param ptr The pointer.
    /// @example char* myString = (char*)malloc(25); strcpy(myString, "Hello World"); free(myString);
    static void Free(void* ptr);

    /// @brief Expands the memory of a number of units. One unit is 65536 bytes long.
    /// @param blocks The number of units.
    static void Grow(int blocks);

    /// @brief Retrieves the current memory size.
    /// @return The memory size, in bytes.
    static unsigned long GetSize();

};