# KickSort 1.2.0

An enhanced Arduino library for sorting algorithms and statistical analysis, built upon the original KickSort library.

## Overview

KickSort extends the original KickSort library with comprehensive statistical functions while maintaining all original sorting capabilities. This library is optimized for microcontrollers with minimal memory footprint and maximum efficiency.

## Features

### Sorting Algorithms
- **Bubble Sort** - Simple comparison-based sorting
- **Quick Sort** - Efficient divide-and-conquer algorithm
- **Insertion Sort** - Efficient for small datasets
- **Shell Sort** - Improved insertion sort variant
- **Comb Sort** - Improved bubble sort variant

### Statistical Functions
- `minElement()` - Find the smallest value in an array
- `maxElement()` - Find the largest value in an array
- `mean()` - Calculate arithmetic average
- `median()` - Find the middle value (sorts array internally)
- `mode()` - Find the most frequently occurring value
- `stdDevPopulation()` - Population standard deviation
- `stdDevSample()` - Sample standard deviation (n-1 correction)

### Utility Functions
- `indexOf()` - Search for the index of a specific value
- `copy()` - Copy one array to another
- `swap()` - Swap two values
- `reverse()` - Reverse array order
- `isSorted()` - Check if array is sorted

## Installation

1. Download the `KickSortPlus.h` file
2. Place it in your Arduino libraries folder
3. Include it in your sketch: `#include "KickSortPlus.h"`

## Usage

This is a templated static class. Function calls must be preceded with the class name and scope resolution operator:

```cpp
#include "KickSort.h"

void setup() {
  Serial.begin(9600);
  
  // Example array
  int data[] = {64, 34, 25, 12, 22, 11, 90};
  int size = 7;
  
  // Sorting
  KickSort<int>::quickSort(data, size);
  
  // Statistics
  int minVal = KickSort<int>::minElement(data, size);
  int maxVal = KickSort<int>::maxElement(data, size);
  float average = KickSort<int>::mean(data, size);
  float stdDev = KickSort<int>::stdDevSample(data, size);
  
  Serial.print("Min: "); Serial.println(minVal);
  Serial.print("Max: "); Serial.println(maxVal);
  Serial.print("Mean: "); Serial.println(average);
  Serial.print("Std Dev: "); Serial.println(stdDev);
}

void loop() {
  // Your main code here
}
```

## API Reference

### Sorting Methods
```cpp
// Sort in ascending order (default)
KickSort<Type>::quickSort(array, size);
KickSort<Type>::bubbleSort(array, size);
KickSort<Type>::insertionSort(array, size);

// Sort with direction control
KickSort<Type>::quickSort(array, size, KickSort_Dir::DESCENDING);
```

### Statistical Methods
```cpp
Type minVal = KickSort<Type>::minElement(array, size);
Type maxVal = KickSort<Type>::maxElement(array, size);
float avg = KickSort<Type>::mean(array, size);
Type med = KickSort<Type>::median(array, size); // Note: modifies array
Type mod = KickSort<Type>::mode(array, size);   // Note: modifies array
float popStdDev = KickSort<Type>::stdDevPopulation(array, size);
float sampleStdDev = KickSort<Type>::stdDevSample(array, size);
```

### Utility Methods
```cpp
int16_t index = KickSort<Type>::indexOf(array, size, value);
KickSort<Type>::copy(source, destination, size);
KickSort<Type>::swap(a, b);
KickSort<Type>::reverse(array, size);
bool sorted = KickSort<Type>::isSorted(array, size, KickSort_Dir::ASCENDING);
```

## Performance Notes

- **Memory Efficient**: All functions are static, no object overhead
- **Template Based**: Works with any comparable data type
- **Optimized for MCUs**: Designed specifically for Arduino and similar platforms
- **Note**: `median()` and `mode()` functions modify the input array during sorting

## Version History

### Version 1.2.0 (Enhanced by danel32)
- Added comprehensive statistical functions
- Improved `mode()` algorithm efficiency (O(n log n) instead of O(n²))
- Added separate population and sample standard deviation functions
- Enhanced error handling for edge cases
- Optimized memory usage for microcontrollers

### Version 1.1.0 (Original KickSort)
- Updated comments and documentation

### Version 1.0.0 (Original KickSort)
- Initial release by Orlando S. Hoilett
- Basic sorting algorithms implementation

## Credits

**Original KickSort Library:**
- **Author**: Orlando S. Hoilett (orlandohoilett@gmail.com)
- **Organization**: Linnes Lab, Purdue University

**Enhanced Version (KickSortPlus):**
- **Enhanced by**: danel32
- **Additions**: Statistical functions, utility improvements, performance optimizations

**Special Thanks:**
Built from aggregating and modifying different sorting implementations from various GitHub users including: robtillaart, emilv, luisllamasbinaburo, and dndubins.

## License

Released under the MIT License. See the source code for full license details.

---

**Note**: This library is designed for Arduino and microcontroller environments. For larger datasets or desktop applications, consider using standard library implementations.
