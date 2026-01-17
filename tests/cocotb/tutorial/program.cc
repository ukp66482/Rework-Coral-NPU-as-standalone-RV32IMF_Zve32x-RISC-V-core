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

#include <stdint.h>

// Addresses start at 0x10100 to avoid CRT magic number at 0x10000
#define INPUT1_ADDR 0x10100
#define INPUT2_ADDR 0x10120
#define OUTPUT_ADDR 0x10140
#define COUNT 8

int main(int argc, char** argv) {
  volatile uint32_t* input1 = (volatile uint32_t*)INPUT1_ADDR;
  volatile uint32_t* input2 = (volatile uint32_t*)INPUT2_ADDR;
  volatile uint32_t* output = (volatile uint32_t*)OUTPUT_ADDR;

  for (int i = 0; i < COUNT; i++) {
    output[i] = input1[i] + input2[i];
  }
  return 0;
}

