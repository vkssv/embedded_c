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
 * @file memory.c
 * @brief Abstraction of memory read and write operations
 *
 * This implementation file provides an abstraction of reading and
 * writing to memory via function calls. There is also a globally
 * allocated buffer array used for manipulation.
 *
 * @author Alex Fosdick
 * @date April 1 2017
 *
 */
#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "platform.h"


/***********************************************************
 Function Definitions
***********************************************************/
void set_value(uint8_t * ptr, uint8_t index, uint8_t value){
	ptr[index] = value;
}

void clear_value(uint8_t * ptr, uint8_t index){
	set_value(ptr, index, 0);
}

uint8_t get_value(uint8_t * ptr, uint8_t index){
	return ptr[index];
}

void set_all(uint8_t * ptr, uint8_t value, uint8_t size){
	uint8_t i;

	for(i = 0; i < size; i++) {
		set_value(ptr, i, value);
	}
}

void clear_all(uint8_t * ptr, uint8_t size){
	set_all(ptr, 0, size);
}

uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length){
	if(src == dst) {
		PRINTF("WARN: src and dst are the same !\n");

		return dst;
	} else if(src < dst && dst < src + length) { 
		/* if overlap then copy from end*/
		src += length;
		dst += length;
		while(length--) {
			dst--;
			src--;
			*dst = *src;
		}
	} else {
		while(length--){
			*dst = *src;
			dst++;
			src++;
		}
	}

	return dst;
	
}

uint8_t * my_memcopy(uint8_t * src, uint8_t * dst, size_t length) {
	const uint8_t * source = (const uint8_t * )src;
	uint8_t * p = dst;

	while(length--) {
		*p = *source;
		p++;
		source++;
	}

	return dst;
}

uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value) {
	while(length--){
		*src = value;
		src++;
	}

	return src;
}

uint8_t * my_memzero(uint8_t * src, size_t length) {

	return my_memset(src, length, 0);
}

uint8_t * my_reverse(uint8_t * src, size_t length) {
	size_t lim = length/2;
	uint8_t tmp;
	uint8_t * source = src;

	for (uint8_t i=0; i < lim; i++) {
		length--;
		tmp = *source;
		*source = *(src+length*sizeof(uint8_t));
		*(src+length*sizeof(uint8_t)) = tmp;
		source++;
	}

	return src;
}

int32_t * reserve_words(size_t length) {
	int32_t * src = calloc(length, sizeof(int32_t));

	if (src == NULL) {
		PRINTF("FATAL: Memory not allocated.\n");
		return NULL;
	}

	return src;
}

void free_words(int32_t * src) {
	free(src);
}
