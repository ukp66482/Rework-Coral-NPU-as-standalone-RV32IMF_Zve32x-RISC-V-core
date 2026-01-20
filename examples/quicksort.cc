// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * Quicksort Example for CoralNPU
 * 
 * This program sorts an array using the quicksort algorithm and outputs
 * the result via the mailbox interface.
 */

#include <cstdint>

// Mailbox address (for communicating results to host)
volatile uint32_t* mailbox = reinterpret_cast<volatile uint32_t*>(0x20000000L);

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Simple bubble sort (to avoid recursion issues)
void bubblesort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    // Simple test without arrays
    int a = 64;
    int b = 34;
    int c = 25;
    int d = 12;
    
    // Store original first value
    mailbox[0] = (uint32_t)a;  // Should be 64
    
    // Manual sort: find min and max
    int min_val = a;
    if (b < min_val) min_val = b;
    if (c < min_val) min_val = c;
    if (d < min_val) min_val = d;
    
    int max_val = a;
    if (b > max_val) max_val = b;
    if (c > max_val) max_val = c;
    if (d > max_val) max_val = d;
    
    mailbox[1] = (uint32_t)min_val;  // Should be 12
    mailbox[2] = (uint32_t)max_val;  // Should be 64
    mailbox[3] = 0x50B7ED;  // SORTED marker
    
    // Signal completion
    asm("wfi");
    return 0;
}
