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
 * @file course1.c
 * @brief This file is to be used to course 1 final assessment.
 *
 * @author Valentina Krasnobaeva
 * @date July 14, 2020
 *
 */

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

/* we need to hold int32, so 32 positions + one char for adding '/0' at
 * the end
 */
#define MAX_LEN ((32+1) * sizeof(uint8_t))

static void print_str(uint8_t * str, uint8_t len) {

#ifdef VERBOSE
	PRINTF("\t>>>'");
	while(len) {
		PRINTF("%c", *str);
		str++;
		len--;
	}
	PRINTF("'<<<\n");
#endif

}

static uint8_t * int_to_str(int32_t data, uint8_t * start, uint32_t base) {
	uint8_t * str = start;
	uint8_t i;

	while (data) {
		i = data % base;
		data /= base;
		if (i < 10) {
			*str = '0'+ i;
			str++;
		} else {
			*str = 'a' - 10 + i;
			str++;
		}
	}

	return str;
}

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base) {
	uint8_t start_str[MAX_LEN];
	uint8_t negative;
	uint8_t len;
	uint8_t * str;

	/* check base */
	if ((base < BASE_2 || base > BASE_16) || (base == BASE_8)) {
		PRINTF("ERROR: Invalid base! Supported bases are: %d, %d, %d\n",
			BASE_2, BASE_10, BASE_16);
		return EINVAL;
	}

	negative = data < 0 ? 1 : 0;
	if (negative) {
		data *= -1;
		if (base != BASE_10) {
			/* need to perform a two's complement to store it as
			 * a negative:
			 * 'UINT_MAX - data' - for flipping bits (this will be
			 * one's complement), then '+ 1' as we need two's
			 * complement
			 */
			data = UINT_MAX - data + 1;
		}
	}

#ifdef VERBOSE
	PRINTF("\t%s: data=%d, radix=%d\n", __func__, data, base);
#endif

	str = int_to_str(data, start_str, base);
	len = str - start_str;

#ifdef VERBOSE
	PRINTF("\t%s: len=%d\n", __func__, len);
#endif

	if (base == BASE_10 && negative) {
		*str++ = '-';
		len++;
	}
	my_reverse(start_str, len);
	*str++ = '\0';
	my_memcopy(start_str, ptr, len++);

#ifdef VERBOSE
	PRINTF("\t%s: converted str:\n", __func__);
	print_str(ptr, len);
	PRINTF("\t%s: len=%d\n", __func__, len);
#endif

	return len;
}

int32_t my_atoi(uint8_t * str, uint8_t digits, uint32_t base) {
	int32_t num = 0;
	size_t len;
	uint8_t data;
	uint8_t i = 0;
	uint8_t negative = 0;

	/* check base */
	if ((base < BASE_2 || base > BASE_16) || (base == BASE_8)) {
		PRINTF("ERROR: Invalid base! Supported bases are: %d, %d, %d\n",
			BASE_2, BASE_10, BASE_16);
		return EINVAL;
	}
	digits--; /* skip str termination '\0' */
	len = digits;

#ifdef VERBOSE
	PRINTF("\t%s: given str from end to start:\n", __func__);
#endif
	print_str(str, digits);

	if (*str == '-' ) {
		negative = 1;
		len--;
		str++;
	}

	if (base == BASE_10 || base == BASE_2)
		my_reverse(str, len);

	while (digits--) {
		if(*(str + digits) >= '0' && *(str + digits) <= '9') {
			data = *(str + digits) - '0';
		} else if((*(str + digits) >= 'A' && *(str + digits) <= 'F') || \
			(*(str + digits) >= 'a' && *(str + digits) <= 'f')) {
			switch(*(str + digits)) {
				case 'A': case 'a': data=10; break;
				case 'B': case 'b': data=11; break;
				case 'C': case 'c': data=12; break;
				case 'D': case 'd': data=13; break;
				case 'E': case 'e': data=14; break;
				case 'F': case 'f': data=15; break;
			}
		}
		if (base == BASE_10 || base == BASE_2) {
			num = base * num + data;
		} else {
			/* 1 << (4 * i) - avoid to use pow(16,i) which leads
			 * to computations in FPU and linking with libm
			 */
			num += data * (1 << (4 * i));
			i++;
		}
	}

	if (base == BASE_10 && negative )
		num *= -1;

	return num;
}
