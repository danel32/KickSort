/*
 * FILENAME: EXAMPLE08_Swap.ino
 * AUTHOR:   Enhanced by danel32 (based on Orlando S. Hoilett's structure)
 * VERSION:  1.2.0
 * 
 * DESCRIPTION
 * Demonstrates usage of KickSort::swap() utility function.
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

void setup()
{
  SerialDebugger.begin(9600);
  while (!SerialDebugger);

  SerialDebugger.println("--- KickSort v1.2.0: swap() Function Test ---\n");

  int a = 42;
  int b = 77;

  SerialDebugger.print("Before Swap -> a: ");
  SerialDebugger.print(a);
  SerialDebugger.print(" | b: ");
  SerialDebugger.println(b);

  KickSort<int>::swap(a, b);

  SerialDebugger.print("After Swap  -> a: ");
  SerialDebugger.print(a);
  SerialDebugger.print(" | b: ");
  SerialDebugger.println(b);
}

void loop() {}
