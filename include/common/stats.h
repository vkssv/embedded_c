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
 * @file: stats.h
 * @brief: Function declarations to analyze an array of unsigned char
 *		   data items.
 *
 * Functions declarations to analyze an array of unsigned char data:
 * to find the maximum, minimum, mean, and median, to reorder data set
 * from large to small, to print it in a nicely format to the screen
 * and to report analytics.
 *
 * @author: Krasnobaeva Valentina
 * @date: 09/02/2020
 *
 */
#ifndef __STATS_H__
#define __STATS_H__

#include <stddef.h>
#include <stdint.h>
#include "platform.h"

/**
 * @brief: Prints the given one-dimentional array.
 *
 * Prints the given one-dimentional array of unsigned char
 * data items in a nicely format. The number of columns to show is
 * defined by COLUMNS macros.
 *
 * @param: unsigned char * array The pointer to the first element of
 *								 unsigned char array to print
 * @param: int size The number of elements in the given array
 * @return: void
 *
 */
void print_array(uint8_t * array, size_t size);

/**
 * @brief: Reorders the given one-dimentional array from large to small. 
 *
 * Reorders the given one-dimentional array of unsigned char elements
 * from large to small. Uses selection sort (Θ(n2)), because the given
 * array is not too large and its size is predefined. Inspite of
 * quadratic time efficiency, which is not effective for large arrays,
 * selection sort is simple and has a good space efficiency
 * (O(1) auxiliary), which is important for embedded apps.
 *
 * @param: unsigned char * array The pointer to the first element of
 *								 unsigned char array to reorder
 * @param: int size The number of elements in the given array
 * @return: void
 *
 */
void sort_array(uint8_t * array, size_t size);

/**
 * @brief: Finds the biggest element in the given array.
 *
 * Finds the biggest unsigned char data item in the given
 * one-dimentional array.
 *
 * @param: unsigned char * array The pointer to the first element of
 *								 unsigned char array to analyze
 * @param: int size The number of elements in the given array
 * @return: unsigned char The biggest unsigned char element
 *
 */
uint8_t find_maximum(uint8_t * array, size_t size);

/**
 * @brief: Finds the smallest element in the given array.
 *
 * Finds the smallest unsigned char data item in the given
 * one-dimentional array.
 *
 * @param: unsigned char * array The pointer to the first element of
 *								 unsigned char array to analyze
 * @param: int size The number of elements in the given array
 * @return: unsigned char The smallest unsigned char element
 *
 */
uint8_t find_minimum(uint8_t * array, size_t size);

/**
 * @brief: Calculates the median of the given array.
 *
 * Calculates the median of the given one-dimentional array of unsigned
 * char data items.
 *
 * @param: unsigned char * array The pointer to the first element of
 *								 unsigned char array to analyze
 * @param: int size The number of elements in the array
 * @return: unsigned short The median value, which can be stored in
 *						   unsigned short type.
 *
 */
uint8_t find_median(uint8_t * array, size_t size);

/**
 * @brief: Calculates the mean of the given array.
 *
 * Calculates the mean of the given one-dimentional array of unsigned
 * char data items.
 *
 * @param: unsigned char * array The pointer to the first element of
 *								 unsigned char array to analyze
 * @param: int size The number of elements in the array
 * @return: unsigned char The mean value
 *
 */
uint8_t find_mean(uint8_t * array, size_t size);

/**
 * @brief: Print statistics in a nicely format.
 *
 * Aggregates and prints statistics of the given unsigned char data
 * items array in a nicely format to the screen.
 *
 * @param: unsigned char * array The pointer to the first element of
 *								 unsigned char array to analyze
 * @param: int size The number of elements in the array
 * @return: void
 *
 */
void print_statistics(uint8_t * array, size_t size);

/**
 * @brief: Print statistics in a nicely format.
 *
 * Aggregates and prints statistics of the given unsigned char data
 * items array in a nicely format to the screen.
 *
 * @param: unsigned char * array The pointer to the first element of
 *								 unsigned char array to analyze
 * @param: int size The number of elements in the array
 * @return: void
 *
 */
void show_stats();

/**
 * @brief: Show input data and calculated statistics.
 *
 * Top level function, that calls others to print input data,
 * to sort it out and to output statistics.
 *
 * @return: void
 *
 */
 

#endif /* __STATS_H__ */
