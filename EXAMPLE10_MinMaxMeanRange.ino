/*
 * FILENAME: EXAMPLE10_MinMaxMeanRange.ino
 * AUTHOR:   Enhanced by danel32
 * VERSION:  1.2.0
 * 
 * DESCRIPTION
 * Demonstrates core statistical tools in KickSort v1.2.0:
 * minElement, maxElement, mean, and calculated range (max - min).
 * Useful for understanding distribution boundaries and average.
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

const uint16_t samples = 12;
int data[samples] = { 17, 22, 14, 8, 19, 25, 30, 16, 21, 18, 20, 13 };

void setup()
{
  SerialDebugger.begin(9600);
  while (!SerialDebugger);

  SerialDebugger.println("--- KickSort v1.2.0: Min, Max, Mean, Range ---\n");

  SerialDebugger.println("Data:");
  for (uint16_t i = 0; i < samples; i++) {
    SerialDebugger.print(data[i]); SerialDebugger.print(" ");
  }
  SerialDebugger.println("\n");

  int minVal = KickSort<int>::minElement(data, samples);
  int maxVal = KickSort<int>::maxElement(data, samples);
  float avg = KickSort<int>::mean(data, samples);
  int range = maxVal - minVal;

  SerialDebugger.print("Minimum Value: ");
  SerialDebugger.println(minVal);

  SerialDebugger.print("Maximum Value: ");
  SerialDebugger.println(maxVal);

  SerialDebugger.print("Mean (Average): ");
  SerialDebugger.println(avg);

  SerialDebugger.print("Range (Max - Min): ");
  SerialDebugger.println(range);
}

void loop() {}
