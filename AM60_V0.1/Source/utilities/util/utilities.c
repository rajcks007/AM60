/**
*@file utilities.c
*/
#include "utilities.h"
#include <stdio.h>
#include "common.h"
static void swapU16(uint16_t* const xp, uint16_t* const yp);

static void swapU16(uint16_t* const xp, uint16_t* const yp) {
    uint16_t temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform Selection Sort
void selectionSortAscU16(uint16_t* arr, const uint16_t n) {
    uint16_t min_idx;

    // One by one move boundary of unsorted subarray
    for (uint16_t i = 0; i < n - 1; i++) {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (uint16_t j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        // Swap the found minimum element
        // with the first element
        swapU16(&arr[min_idx], &arr[i]);
    }
}

int combine(int a, int b) {
    int times = 1;
    while (times <= b)
        times *= 10;
    return a * times + b;
}

