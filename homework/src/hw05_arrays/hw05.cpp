#include "hw05.h"
#include <cstddef>

// Pre-conditions: none
// Post-conditions: none
// Returns: the pointer to where the first instance of 0 is found.
//          if no instance of a 0 exists within the valid size, return nullptr
const int *find_first_zero(const int *src, size_t size) {
        if (src == nullptr) {
                return nullptr;
        }
        for (int i = 0; i < size; i++) {
                if (*(src + i) == 0) {
                        return src + i;
                }
        }
        return nullptr;
}

// Pre-conditions: none
// Post-conditions: none
// Returns: the pointer to where the last instance of 0 is found.
//          if no instance of a 0 exists within the valid size, return nullptr
const int *find_last_zero(const int *src, size_t size) {
        if (src == nullptr) {
                return nullptr;
        }
        for (int i = size - 1; i >= 0; i--) {
                if (*(src + i) == 0)
                {
                        return src + i;
                }
        }
        return nullptr;
}

// Pre-conditions: none
// Post-conditions: none
// Returns: the number of times the key passed in exists in the array passed in
size_t find_num_keys(const int *src, size_t size, int key) {
        int counter = 0;
        if (src == nullptr) {
                return 0;
        }
        for (int i = 0; i < size; i++) {
                if (*(src + i) == key) {
                        counter++;
                }
        }
        return counter;
}

// Pre-conditions: none
// Post-conditions: result will contain the mean value of src
// Returns: true when there exists a valid value for result
//          false for when there are no items, or nullptr is passed in
bool mean_of_array(const double *src, size_t size, double &result) {
        if (src == nullptr || size == 0) {
                return false;
        }
        double sum = 0;
        for (int i = 0; i < size; i++) {
                sum += *(src + i);
        }
        result = sum / size;
        return true;
}

// Pre-conditions: dst array size would be at least the size of src
// Post-conditions: contents of src copied into dst for size elements
// Returns: number of items that were copied
//
// Note: dst or src could be nullptr, and if so, do not attempt any copy
size_t copy_array(int *dst, const int *src, size_t size) {
        size_t counter = 0;
        if (dst == nullptr || src == nullptr) {
                return 0;
        }
        for (int i = 0; i < size; i++) {
                *(dst + i) = *(src + i);
                counter++;
        }
        return counter;
}

// Pre-conditions: dst array size would be at least the size of src
// Post-conditions: contents of dst will be the reverse of what is contained in
//                  src
// Returns: nothing, but dst will be changed
//
// if either dst or src is nullptr, do nothing
//
// e.g.: if src: [0,1,2,3,4,5] -> dst: [5,4,3,2,1,0]
void reverse_array(int *dst, const int *src, size_t size) {
        int j = 0;
        if (dst == nullptr || src == nullptr) {
                return;
        }
        for (int i = size - 1; i >= 0; i--) {
                *(dst + j) = *(src + i);
                j++;
        }
        return;
}

// Pre-conditions: none
// Post-conditions: contents of array will be the reverse of what was originally
//                  passed in
// Returns: nothing, but array is reversed
//
// e.g.: if array: [0,1,2,3,4,5] -> array: [5,4,3,2,1,0]
void reverse_in_place(int *array, size_t size) {
        if (array == nullptr) {
                return;
        }
        for (int i = 0; i < size / 2; i++) {
                int tmp = *(array + i);
                *(array + i) = *(array + size - 1 - i);
                *(array + size - 1 - i) = tmp;
        }
        return;
}
