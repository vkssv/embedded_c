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
 * @file data.h
 * @brief Some very basic data manipulation
 *
 * This header file provides some functions to convert a 32-bit signed
 * int to a character ASCII string and vice versa.
 *
 * @author Valentina Krasnobaeva
 * @date July 14 2020
 *
 */
#ifndef __DATA_H__
#define __DATA_H__

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include "data.h"
#include "platform.h"
#include "memory.h"

#define BASE_2 (2)
#define BASE_8 (8)
#define BASE_10 (10)
#define BASE_16 (16)

// we need to hold int32, so 32 positions + one char for adding '/0' at
// the end
#define MAX_LEN ((32+1) * sizeof(uint8_t))

/**
 * @brief Convert data from a 32-bit signed int into an ASCII string
 *
 * Converts data from a 32-bit signed int into an ASCII string. Supports
 * bases: 2, 10, 16, positive and negative data.
 *
 * @param data 32-bit signed int in decimal format
 * @param ptr Address to an ASCII string in dynamic memory
 * @param base Integer base, supported values: 2, 10, 16
 *
 * @return The length of the converted data (including a negative sign
 * '-' and '\0').
 */
uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base);

/**
 * @brief Convert data back from an ASCII represented string into
 * a signed 32-bit int
 *
 * Converts an ASCII string into a 32-bit signed integer in decimal
 * format. Supports bases: 2, 10, 16, also supports strings, which
 * starts with negative sign '-' or '1' for binary represented numbers.
 *
 * @param str Pointer to an ASCII string in dynamic memory
 * @param digits The number of digits in a given character set
 * (including '-' and '\0')
 * @param base Integer base, supported values: 2, 10, 16
 *
 * @return The converted 32-bit signed integer in a decimal format.
 */
int32_t my_atoi(uint8_t * str, uint8_t digits, uint32_t base);

#endif /* __DATA_H__ */
