/*
 FILENAME:      KickSort.h
 AUTHOR:        Orlando S. Hoilett (original KickSort)
 EMAIL:         orlandohoilett@gmail.com
 ENHANCED BY:   danel32
 VERSION:       1.2.0
 
 
 DESCRIPTION
 An enhanced Arduino library for sorting algorithms and statistical analysis,
 built upon the original KickSort library. Provides comprehensive sorting
 capabilities with added statistical functions optimized for microcontrollers.
 
 The class is templated allowing for ease of use across different data types.
 This is a static class. Function calls must be preceded with the class name and
 scope resolution operator as follows "KickSort<variable_type>::" where
 variable_type should be replaced with int16_t, int, float, etc.
 
 Original KickSort library is built from aggregating and modifying different
 sorting implementations from various other GitHub users including: robtillaart
 (especially), emilv, luisllamasbinaburo, and dndubins. Thanks!
 
 Enhanced with statistical functions and utilities by danel32.
 
 
 UPDATES
 Version 1.0.0
 2020/08/22:2000> (UTC-5)
             - Initial release by Orlando S. Hoilett.
 Version 1.1.0
 2020/08/26:2335> (UTC-5)
             - Updated comments.
 Version 1.2.0 (Enhanced by danel32)
 2024/XX/XX:
             - Added comprehensive statistical functions
             - Added utility functions (indexOf, copy, swap, reverse)
             - Improved mode() algorithm efficiency (O(n log n) instead of O(n²))
             - Added separate population and sample standard deviation functions
             - Enhanced error handling for edge cases
             - Optimized memory usage for microcontrollers
 
 
 DISCLAIMER
 Linnes Lab code, firmware, and software is released under the
 MIT License (http://opensource.org/licenses/MIT).
 
 The MIT License (MIT)
 
 Copyright (c) 2020 Linnes Lab, Purdue University
 Enhancements Copyright (c) 2024 danel32
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 */

#ifndef KickSort_h
#define KickSort_h

#include <Arduino.h>
#include <math.h>

// Sort direction enum
enum class KickSort_Dir {
    ASCENDING = 0,
    DESCENDING = 1
};

template<typename Type>
class KickSort {
public:
    // === SORTING ALGORITHMS ===
    static void bubbleSort(Type input[], const uint16_t samples);
    static void bubbleSort(Type input[], const uint16_t samples, KickSort_Dir d);
    
    static void quickSort(Type input[], const uint16_t samples);
    static void quickSort(Type input[], const uint16_t samples, KickSort_Dir d);
    
    static void insertionSort(Type input[], const uint16_t samples);
    static void insertionSort(Type input[], const uint16_t samples, KickSort_Dir d);
    
    static void combSort(Type input[], const uint16_t samples);
    static void combSort(Type input[], const uint16_t samples, KickSort_Dir d);
    
    static void shellSort(Type input[], const uint16_t samples);
    static void shellSort(Type input[], const uint16_t samples, KickSort_Dir d);

    // === UTILITY FUNCTIONS ===
    static bool isSorted(const Type input[], const uint16_t samples, KickSort_Dir d = KickSort_Dir::ASCENDING);
    static void reverse(Type input[], const uint16_t samples);
    static int16_t indexOf(const Type input[], uint16_t samples, Type value);
    static void copy(const Type source[], Type destination[], uint16_t samples);
    static void swap(Type& a, Type& b);

    // === STATISTICAL FUNCTIONS ===
    static Type minElement(const Type input[], uint16_t samples);
    static Type maxElement(const Type input[], uint16_t samples);
    static float mean(const Type input[], uint16_t samples);
    static Type median(Type input[], uint16_t samples);
    static Type mode(Type input[], uint16_t samples);
    static float stdDevPopulation(const Type input[], uint16_t samples);
    static float stdDevSample(const Type input[], uint16_t samples);

private:
    // Helper functions for quickSort
    static void quickSortRecursive(Type input[], int16_t low, int16_t high);
    static void quickSortRecursive(Type input[], int16_t low, int16_t high, KickSort_Dir d);
    static int16_t partition(Type input[], int16_t low, int16_t high);
    static int16_t partitionDesc(Type input[], int16_t low, int16_t high);
};

// ============================================================================
// IMPLEMENTATION
// ============================================================================

// === BUBBLE SORT ===
template<typename Type>
void KickSort<Type>::bubbleSort(Type input[], const uint16_t samples) {
    if (samples < 2) return;
    
    uint32_t newn = 0, n = samples;
    Type temp;
    do {
        newn = 1;
        for(uint16_t p = 1; p < samples; p++) {
            if(input[p-1] > input[p]) {
                temp = input[p];
                input[p] = input[p-1];
                input[p-1] = temp;
                newn = p;
            }
        }
        n = newn;
    } while(n > 1);
}

template<typename Type>
void KickSort<Type>::bubbleSort(Type input[], const uint16_t samples, KickSort_Dir d) {
    if (samples < 2) return;
    
    if(d == KickSort_Dir::ASCENDING) {
        bubbleSort(input, samples);
    } else {
        uint32_t newn = 0, n = samples;
        Type temp;
        do {
            newn = 1;
            for(uint16_t p = 1; p < samples; p++) {
                if(input[p-1] < input[p]) {
                    temp = input[p];
                    input[p] = input[p-1];
                    input[p-1] = temp;
                    newn = p;
                }
            }
            n = newn;
        } while(n > 1);
    }
}

// === QUICK SORT ===
template<typename Type>
void KickSort<Type>::quickSort(Type input[], const uint16_t samples) {
    if (samples < 2) return;
    quickSortRecursive(input, 0, samples - 1);
}

template<typename Type>
void KickSort<Type>::quickSort(Type input[], const uint16_t samples, KickSort_Dir d) {
    if (samples < 2) return;
    quickSortRecursive(input, 0, samples - 1, d);
}

template<typename Type>
void KickSort<Type>::quickSortRecursive(Type input[], int16_t low, int16_t high) {
    if (low < high) {
        int16_t pi = partition(input, low, high);
        quickSortRecursive(input, low, pi - 1);
        quickSortRecursive(input, pi + 1, high);
    }
}

template<typename Type>
void KickSort<Type>::quickSortRecursive(Type input[], int16_t low, int16_t high, KickSort_Dir d) {
    if (low < high) {
        int16_t pi = (d == KickSort_Dir::ASCENDING) ? 
                     partition(input, low, high) : 
                     partitionDesc(input, low, high);
        quickSortRecursive(input, low, pi - 1, d);
        quickSortRecursive(input, pi + 1, high, d);
    }
}

template<typename Type>
int16_t KickSort<Type>::partition(Type input[], int16_t low, int16_t high) {
    Type pivot = input[high];
    int16_t i = (low - 1);
    
    for (int16_t j = low; j <= high - 1; j++) {
        if (input[j] < pivot) {
            i++;
            swap(input[i], input[j]);
        }
    }
    swap(input[i + 1], input[high]);
    return (i + 1);
}

template<typename Type>
int16_t KickSort<Type>::partitionDesc(Type input[], int16_t low, int16_t high) {
    Type pivot = input[high];
    int16_t i = (low - 1);
    
    for (int16_t j = low; j <= high - 1; j++) {
        if (input[j] > pivot) {
            i++;
            swap(input[i], input[j]);
        }
    }
    swap(input[i + 1], input[high]);
    return (i + 1);
}

// === INSERTION SORT ===
template<typename Type>
void KickSort<Type>::insertionSort(Type input[], const uint16_t samples) {
    if (samples < 2) return;
    
    for (uint16_t i = 1; i < samples; i++) {
        Type key = input[i];
        int16_t j = i - 1;
        while (j >= 0 && input[j] > key) {
            input[j + 1] = input[j];
            j--;
        }
        input[j + 1] = key;
    }
}

template<typename Type>
void KickSort<Type>::insertionSort(Type input[], const uint16_t samples, KickSort_Dir d) {
    if (samples < 2) return;
    
    if (d == KickSort_Dir::ASCENDING) {
        insertionSort(input, samples);
    } else {
        for (uint16_t i = 1; i < samples; i++) {
            Type key = input[i];
            int16_t j = i - 1;
            while (j >= 0 && input[j] < key) {
                input[j + 1] = input[j];
                j--;
            }
            input[j + 1] = key;
        }
    }
}

// === COMB SORT ===
template<typename Type>
void KickSort<Type>::combSort(Type input[], const uint16_t samples) {
    if (samples < 2) return;
    
    uint16_t gap = samples;
    bool swapped = true;
    
    while (gap != 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        
        swapped = false;
        for (uint16_t i = 0; i < samples - gap; i++) {
            if (input[i] > input[i + gap]) {
                swap(input[i], input[i + gap]);
                swapped = true;
            }
        }
    }
}

template<typename Type>
void KickSort<Type>::combSort(Type input[], const uint16_t samples, KickSort_Dir d) {
    if (samples < 2) return;
    
    if (d == KickSort_Dir::ASCENDING) {
        combSort(input, samples);
    } else {
        uint16_t gap = samples;
        bool swapped = true;
        
        while (gap != 1 || swapped) {
            gap = (gap * 10) / 13;
            if (gap < 1) gap = 1;
            
            swapped = false;
            for (uint16_t i = 0; i < samples - gap; i++) {
                if (input[i] < input[i + gap]) {
                    swap(input[i], input[i + gap]);
                    swapped = true;
                }
            }
        }
    }
}

// === SHELL SORT ===
template<typename Type>
void KickSort<Type>::shellSort(Type input[], const uint16_t samples) {
    if (samples < 2) return;
    
    for (uint16_t gap = samples / 2; gap > 0; gap /= 2) {
        for (uint16_t i = gap; i < samples; i++) {
            Type temp = input[i];
            uint16_t j;
            for (j = i; j >= gap && input[j - gap] > temp; j -= gap) {
                input[j] = input[j - gap];
            }
            input[j] = temp;
        }
    }
}

template<typename Type>
void KickSort<Type>::shellSort(Type input[], const uint16_t samples, KickSort_Dir d) {
    if (samples < 2) return;
    
    if (d == KickSort_Dir::ASCENDING) {
        shellSort(input, samples);
    } else {
        for (uint16_t gap = samples / 2; gap > 0; gap /= 2) {
            for (uint16_t i = gap; i < samples; i++) {
                Type temp = input[i];
                uint16_t j;
                for (j = i; j >= gap && input[j - gap] < temp; j -= gap) {
                    input[j] = input[j - gap];
                }
                input[j] = temp;
            }
        }
    }
}

// === UTILITY FUNCTIONS ===
template<typename Type>
void KickSort<Type>::reverse(Type input[], const uint16_t samples) {
    for (uint16_t i = 0; i < samples / 2; ++i) {
        swap(input[i], input[samples - 1 - i]);
    }
}

template<typename Type>
bool KickSort<Type>::isSorted(const Type input[], const uint16_t samples, KickSort_Dir d) {
    if (samples < 2) return true;
    
    for (uint16_t i = 1; i < samples; ++i) {
        if (d == KickSort_Dir::ASCENDING && input[i - 1] > input[i]) return false;
        if (d == KickSort_Dir::DESCENDING && input[i - 1] < input[i]) return false;
    }
    return true;
}

template<typename Type>
int16_t KickSort<Type>::indexOf(const Type input[], uint16_t samples, Type value) {
    for (uint16_t i = 0; i < samples; i++) {
        if (input[i] == value) return i;
    }
    return -1;
}

template<typename Type>
void KickSort<Type>::copy(const Type source[], Type destination[], uint16_t samples) {
    for (uint16_t i = 0; i < samples; i++) {
        destination[i] = source[i];
    }
}

template<typename Type>
void KickSort<Type>::swap(Type& a, Type& b) {
    Type temp = a;
    a = b;
    b = temp;
}

// === STATISTICAL FUNCTIONS ===
template<typename Type>
Type KickSort<Type>::minElement(const Type input[], uint16_t samples) {
    if (samples == 0) return Type();
    
    Type minVal = input[0];
    for (uint16_t i = 1; i < samples; i++) {
        if (input[i] < minVal) minVal = input[i];
    }
    return minVal;
}

template<typename Type>
Type KickSort<Type>::maxElement(const Type input[], uint16_t samples) {
    if (samples == 0) return Type();
    
    Type maxVal = input[0];
    for (uint16_t i = 1; i < samples; i++) {
        if (input[i] > maxVal) maxVal = input[i];
    }
    return maxVal;
}

template<typename Type>
float KickSort<Type>::mean(const Type input[], uint16_t samples) {
    if (samples == 0) return 0.0f;
    
    float sum = 0;
    for (uint16_t i = 0; i < samples; i++) {
        sum += input[i];
    }
    return sum / samples;
}

template<typename Type>
Type KickSort<Type>::median(Type input[], uint16_t samples) {
    if (samples == 0) return Type();
    
    // Sort the array to find median
    quickSort(input, samples);
    
    if (samples % 2 == 0) {
        return (input[samples/2 - 1] + input[samples/2]) / 2;
    } else {
        return input[samples/2];
    }
}

template<typename Type>
Type KickSort<Type>::mode(Type input[], uint16_t samples) {
    if (samples == 0) return Type();
    if (samples == 1) return input[0];
    
    // Sort the array first for efficient mode calculation
    quickSort(input, samples);
    
    uint16_t maxCount = 1, currentCount = 1;
    Type modeVal = input[0];
    
    for (uint16_t i = 1; i < samples; ++i) {
        if (input[i] == input[i - 1]) {
            currentCount++;
            if (currentCount > maxCount) {
                maxCount = currentCount;
                modeVal = input[i];
            }
        } else {
            currentCount = 1;
        }
    }
    return modeVal;
}

template<typename Type>
float KickSort<Type>::stdDevPopulation(const Type input[], uint16_t samples) {
    if (samples == 0) return 0.0f;
    
    float m = mean(input, samples);
    float accum = 0.0;
    
    for (uint16_t i = 0; i < samples; i++) {
        accum += (input[i] - m) * (input[i] - m);
    }
    
    return sqrt(accum / samples);
}

template<typename Type>
float KickSort<Type>::stdDevSample(const Type input[], uint16_t samples) {
    if (samples < 2) return 0.0f;
    
    float m = mean(input, samples);
    float accum = 0.0;
    
    for (uint16_t i = 0; i < samples; i++) {
        accum += (input[i] - m) * (input[i] - m);
    }
    
    return sqrt(accum / (samples - 1));
}

#endif /* KickSort_h */
