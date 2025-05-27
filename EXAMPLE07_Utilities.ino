/*
 * FILENAME: EXAMPLE07_Utilities.ino
 * AUTHOR:   Enhanced by danel32 (based on Orlando S. Hoilett's structure)
 * VERSION:  1.2.0
 * 
 * DESCRIPTION
 * Demonstrates usage of utility functions in KickSort v1.2.0
 * Includes: indexOf, copy, reverse, isSorted
 * 
 * DISCLAIMER
 * Provided under MIT License.
 */

#include "KickSortPlus.h"

#if defined(ARDUINO_ARCH_SAMD)
  #define SerialDebugger SerialUSB
#else
  #define SerialDebugger Serial
#endif

const uint16_t samples = 10;
int original[samples] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int clone[samples];

void setup()
{
  SerialDebugger.begin(9600);
  while (!SerialDebugger);

  SerialDebugger.println("--- KickSort v1.2.0: Utility Functions Test ---\n");

  // 1. Copy test
  KickSort<int>::copy(original, clone, samples);
  SerialDebugger.println("1. Copied Array:");
  for (uint16_t i = 0; i < samples; i++) {
    SerialDebugger.print(clone[i]); SerialDebugger.print(" ");
  }
  SerialDebugger.println("\n");

  // 2. Reverse test
  KickSort<int>::reverse(clone, samples);
  SerialDebugger.println("2. Reversed Copy:");
  for (uint16_t i = 0; i < samples; i++) {
    SerialDebugger.print(clone[i]); SerialDebugger.print(" ");
  }
  SerialDebugger.println("\n");

  // 3. isSorted test
  SerialDebugger.print("3. Is Reversed Sorted Ascending? ");
  SerialDebugger.println(KickSort<int>::isSorted(clone, samples) ? "YES" : "NO");

  SerialDebugger.print("   Is Reversed Sorted Descending? ");
  SerialDebugger.println(KickSort<int>::isSorted(clone, samples, KickSort_Dir::DESCENDING) ? "YES" : "NO");

  // 4. indexOf test
  int target = 7;
  int16_t pos = KickSort<int>::indexOf(clone, samples, target);
  SerialDebugger.print("4. IndexOf value ");
  SerialDebugger.print(target);
  SerialDebugger.print(": ");
  SerialDebugger.println(pos >= 0 ? String(pos) : "Not Found");
}

void loop() {}
