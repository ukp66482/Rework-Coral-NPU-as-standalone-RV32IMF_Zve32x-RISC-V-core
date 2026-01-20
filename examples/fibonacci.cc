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
 * Fibonacci Example for CoralNPU
 * 
 * This program calculates Fibonacci numbers and outputs the result
 * via the mailbox interface.
 */

#include <cstdint>

// Mailbox address (for communicating results to host)
volatile uint32_t* mailbox = reinterpret_cast<volatile uint32_t*>(0x20000000L);

// Recursive Fibonacci
int fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// Iterative Fibonacci (faster)
int fib_iterative(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main() {
    // Calculate Fibonacci(10) using both methods
    int result_recursive = fib_recursive(10);  // Should be 55
    int result_iterative = fib_iterative(20);  // Should be 6765
    
    // Output results via mailbox (only 4 entries available)
    mailbox[0] = result_recursive;  // fib(10) = 55
    mailbox[1] = result_iterative;  // fib(20) = 6765
    mailbox[2] = 0xF1B0ACC1;        // Magic: "FIB" marker (32-bit)
    mailbox[3] = fib_iterative(15); // fib(15) = 610
    
    // Signal completion
    asm("wfi");
    return 0;
}
