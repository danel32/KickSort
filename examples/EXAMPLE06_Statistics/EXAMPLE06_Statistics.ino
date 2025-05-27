/*
 * FILENAME: EXAMPLE06_Statistics.ino
 * AUTHOR:   Enhanced by danel32 (based on Orlando S. Hoilett's structure)
 * VERSION:  1.2.0
 * 
 * DESCRIPTION
 * Demonstrates usage of statistical functions provided in KickSort v1.2.0
 * Includes: mean, median, mode, standard deviation (population/sample), min/max, etc.
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

const uint16_t samples = 20;
int input[samples] = { 5, 1, 7, 3, 7, 8, 2, 5, 4, 3, 7, 9, 2, 4, 6, 5, 3, 8, 7, 5 };

void setup()
{
  SerialDebugger.begin(9600);
  while (!SerialDebugger);

  SerialDebugger.println("--- KickSort v1.2.0: Statistical Functions Test ---\n");

  SerialDebugger.println("Input Array:");
  for (uint16_t i = 0; i < samples; i++) {
    SerialDebugger.print(input[i]); SerialDebugger.print(" ");
  }
  SerialDebugger.println("\n");

  SerialDebugger.print("Mean: ");
  SerialDebugger.println(KickSort<int>::mean(input, samples));

  SerialDebugger.print("Median: ");
  SerialDebugger.println(KickSort<int>::median(input, samples));

  SerialDebugger.print("Mode: ");
  SerialDebugger.println(KickSort<int>::mode(input, samples));

  SerialDebugger.print("Population Std Dev: ");
  SerialDebugger.println(KickSort<int>::stdDevPopulation(input, samples));

  SerialDebugger.print("Sample Std Dev: ");
  SerialDebugger.println(KickSort<int>::stdDevSample(input, samples));

  SerialDebugger.print("Minimum: ");
  SerialDebugger.println(KickSort<int>::minElement(input, samples));

  SerialDebugger.print("Maximum: ");
  SerialDebugger.println(KickSort<int>::maxElement(input, samples));
}

void loop() {}
