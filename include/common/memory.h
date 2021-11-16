/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file memory.h
 * @brief Abstraction of memory read and write operations
 *
 * This header file provides an abstraction of reading and
 * writing to memory via function calls. 
 *
 * @author Alex Fosdick
 * @date April 1 2017
 *
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include <stdlib.h>
#include <platform.h>

/**
 * @brief Sets a value of a data array 
 *
 * Given a pointer to a char data set, this will set a provided
 * index into that data set to the value provided.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 * @param value value to write the the locaiton
 *
 * @return void.
 */
void set_value(uint8_t *ptr, uint8_t index, uint8_t value);

/**
 * @brief Clear a value of a data array 
 *
 * Given a pointer to a char data set, this will clear a provided
 * index into that data set to the value zero.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 *
 * @return void.
 */
void clear_value(uint8_t *ptr, uint8_t index);

/**
 * @brief Returns a value of a data array 
 *
 * Given a pointer to a char data set, this will read the provided
 * index into that data set and return the value.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 *
 * @return Value to be read.
 */
uint8_t get_value(uint8_t *ptr, uint8_t index);

/**
 * @brief Sets data array elements to a value
 *
 * Given a pointer to a char data set, this will set a number of elements
 * from a provided data array to the given value. The length is determined
 * by the provided size parameter.
 *
 * @param ptr Pointer to data array
 * @param value value to write the the locaiton
 * @param size Number of elements to set to value
 *
 * @return void.
 */
void set_all(uint8_t *ptr, uint8_t value, uint8_t size);

/**
 * @brief Clears elements in a data array
 *
 * Given a pointer to a char data set, this will set a clear a number
 * of elements given the size provided. Clear means to set to zero. 
 *
 * @param ptr Pointer to data array
 * @param size Number of elements to set to zero
 *
 * @return void.
 */
void clear_all(uint8_t *ptr, uint8_t size);

/**
 * @brief Moves a given number of bytes from source memory location to
 * destination
 *
 * Takes two byte pointers (src and dst) and a length of bytes to move
 * from source memory location to destination. It handles overlap of
 * source and destination addresses. If overlap happens, moves bytes
 * from right to left.
 *
 * @param src Pointer to address to move from, source
 * @param dst Pointer to address to move to, destination
 * @param length Number of bytes to move
 *
 * @return Pointer to a destination memory location.
 */
uint8_t *my_memmove(uint8_t *src, uint8_t *dst, size_t length);

/**
 * @brief Copies a given number of bytes from source memory location to
 * destination
 *
 * Takes two byte pointers (src and dst) and a length of bytes to copy
 * from source memory location to destination. The behavior is
 * undefined, if there is overlap of source and destination. Copy still
 * occurs, but will likely corrupt your data.
 * 
 * @param src Pointer to address to copy from, source
 * @param dst Pointer to address to copy to, destination
 * @param length Number of bytes to copy
 *
 * @return Pointer to a destination memory location.
 */
uint8_t *my_memcopy(uint8_t *src, uint8_t *dst, size_t length);

/**
 * @brief Set to a given value a length of bytes starting from a source
 * memory location 
 *
 * Takes a pointer to a source memory location, a length of bytes and
 * set all memory locations from source to length to a given value.
 *
 * @param src Pointer to source memory location
 * @param length Number of bytes to set to a given value
 * @param value Given value to set to
 *
 * @return Pointer to a source memory location.
 */
uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value);

/**
 * @brief Zero out a length of bytes starting from a source memory
 * location
 *
 * Takes a pointer to a memory location, a length in bytes and zeros out
 * all of the memory from source to length.
 * 
 * @param src Pointer to a source memory location
 * @param length Number of bytes to set to zero
 *
 * @return Pointer to a source memory location.
 */
uint8_t *my_memzero(uint8_t *src, size_t length);

/**
 * @brief Reverse the order of all of the bytes from source to length
 *
 * Takes a pointer to a source memory location and a length in bytes
 * and reverses the order of all of the bytes from source to length.
 *
 * @param src Pointer to a source memory location
 * @param length Number of bytes to reverse
 *
 * @return Pointer to a source memory location.
 */
uint8_t *my_reverse(uint8_t *src, size_t length);

/**
 * @brief Allocate in dynamic memory a given length of bytes
 *
 * Takes a length of bytes to allocate in dynamic memory.
 *
 * @param length Number of bytes to allocate
 *
 * @return Pointer to allocated dynamic memory if successful, or NULL
 * if failed.
 */
int32_t *reserve_words(size_t length);

/**
 * @brief Free a dynamic memory allocation 
 *
 * Free a dynamic memory allocation at the given source address by
 * handling a call to free() stdlib function.
 *
 * @param src Pointer to dynamic memory location to free
 * 
 * @return void.
 */
extern void free_words(int32_t *src);

#endif /* __MEMORY_H__ */
