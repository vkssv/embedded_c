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
 * @file: stats.c
 * @brief: Analyze an array of unsigned char data items and report
 *	    analytics
 *
 * Analyze an array of unsigned char data items and report analytics
 * on the maximum, minimum, mean, and median of the data set. Before
 * analasys the given data set is reordered from large to small.
 *
 * @author: Valentina Krasnobaeva
 * @date: 09/02/2020
 *
 */
#include <stddef.h>
#include <stdint.h>
#include "platform.h"
#include "stats.h"

/* Size of the Data Set */
#define SIZE (40)
#define COLUMNS (4)

void show_stats() {

	uint8_t test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
							114, 88,   45,  76, 123,  87,  25,  23,
							200, 122, 150, 90,   92,  87, 177, 244,
							201,   6,  12,  60,   8,   2,   5,  67,
							7,  87, 250, 230,  99,   3, 100,  90 };

	print_array(test, SIZE);
	sort_array(test, SIZE);
	print_statistics(test, SIZE);
}

void print_array(uint8_t * array, size_t size) {

#ifdef VERBOSE
	uint8_t i = 0;
	PRINTF("=============\n");
	while (i < size) {
		if ((i+1)%COLUMNS)
			PRINTF("\ttest[%d] = %d\t", i, array[i]);
		else
			PRINTF("\ttest[%d] = %d\n", i, array[i]);
		i++;
	}
#endif

}

void sort_array(uint8_t * array, size_t size) {
	uint8_t i, j;
	uint8_t tmp;
	for (i = 0; i < size; ++i) {
		for (j = i + 1; j < size; ++j) {
			if (array[i] < array[j]) {
				tmp= array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}

}

uint8_t find_maximum(uint8_t * array, size_t size) {
	return array[0];
};

uint8_t find_minimum(uint8_t * array, size_t size) {
	return array[size-1];
};

uint8_t find_median(uint8_t * array, size_t size) {
	return (array[size/2-1] + array[size/2])/2;
};

uint8_t find_mean(uint8_t * array, size_t size) {
	uint8_t i = 0;
	uint8_t sum = 0;
	while( i < size ) {
		sum += array[i];
		i++;
	}
	return sum/size;
};

void print_statistics(uint8_t * array, size_t size) {
	PRINTF("======================\n");
	PRINTF("  Maximum value = %d\n", find_maximum(array, size));
	PRINTF("  Minimum value = %d\n", find_minimum(array, size));
	PRINTF("  Median = %d\n", find_median(array, size));
	if (size == 0)
		PRINTF("  ERROR: Mean: cannot divide by zero, please check array len\n");
	else
		PRINTF("  Mean = %d\n", find_mean(array, size));
	PRINTF("======================\n");

}
