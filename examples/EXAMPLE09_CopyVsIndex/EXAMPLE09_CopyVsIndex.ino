/*
 * FILENAME: EXAMPLE09_CopyVsIndex.ino
 * AUTHOR:   Enhanced by danel32
 * VERSION:  1.2.0
 * 
 * DESCRIPTION
 * Demonstrates use of KickSort::copy() and KickSort::indexOf().
 * Compares two arrays and uses indexOf() to locate mismatches.
 * Also shows how indexOf() behaves with repeated values.
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
int original[samples] = { 3, 5, 2, 7, 5, 9, 5, 1, 6, 4 };
int clone[samples];

void setup()
{
  SerialDebugger.begin(9600);
  while (!SerialDebugger);

  SerialDebugger.println("--- KickSort v1.2.0: Copy and IndexOf Comparison ---\n");

  // Step 1: Copy original[] to clone[]
  KickSort<int>::copy(original, clone, samples);

  // Step 2: Introduce a small difference
  clone[4] = 99;

  SerialDebugger.println("Original Array:");
  for (uint16_t i = 0; i < samples; i++) {
    SerialDebugger.print(original[i]); SerialDebugger.print(" ");
  }
  SerialDebugger.println("\n");

  SerialDebugger.println("Modified Copy:");
  for (uint16_t i = 0; i < samples; i++) {
    SerialDebugger.print(clone[i]); SerialDebugger.print(" ");
  }
  SerialDebugger.println("\n");

  // Step 3: Detect mismatches
  SerialDebugger.println("Mismatched values:");
  for (uint16_t i = 0; i < samples; i++) {
    if (original[i] != clone[i]) {
      SerialDebugger.print("Mismatch at index ");
      SerialDebugger.print(i);
      SerialDebugger.print(": original=");
      SerialDebugger.print(original[i]);
      SerialDebugger.print(", clone=");
      SerialDebugger.println(clone[i]);
    }
  }
  SerialDebugger.println();

  // Step 4: Demonstrate indexOf with repeated values
  int target = 5;
  int index = KickSort<int>::indexOf(original, samples, target);

  SerialDebugger.print("First occurrence of value ");
  SerialDebugger.print(target);
  SerialDebugger.print(" is at index: ");
  SerialDebugger.println(index);
}

void loop() {}
