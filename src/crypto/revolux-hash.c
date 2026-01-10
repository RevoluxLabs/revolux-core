// Copyright (c) 2014-2024, The Monero Project
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef REVOLUX_POW_ACTIVATION
#warning "RevoluxHash compiled but NOT activated in consensus"
#endif

#define REVOLUX_POW_ACTIVATION 1

#include "revolux-hash.h"
#include <string.h>
#include <stdlib.h>

// RevoluxHash implementation conforming to the frozen specification
// This implementation is consensus-critical and must not be modified

void revolux_hash(const uint8_t* input, uint8_t* output) {
    // Allocate working memory exactly as specified: 2,097,152 bytes (2 MiB)
    uint8_t* memory = (uint8_t*)malloc(REVOLUX_HASH_MEMORY_SIZE);
    if (!memory) {
        // Memory allocation failure - this should not happen in normal operation
        memset(output, 0, REVOLUX_HASH_OUTPUT_SIZE);
        return;
    }

    // Initialize memory to zero as per specification
    memset(memory, 0, REVOLUX_HASH_MEMORY_SIZE);

    // State variables for sequential computation
    uint64_t a = 0, b = 0, c = 0, d = 0;

    // Initialize state from input (first 32 bytes)
    memcpy(&a, input, 8);
    memcpy(&b, input + 8, 8);
    memcpy(&c, input + 16, 8);
    memcpy(&d, input + 24, 8);

    // Main computation loop - exactly 1024 iterations for memory coverage
    for (uint32_t i = 0; i < 1024; ++i) {
        // Data-dependent memory indices
        uint32_t idx1 = (uint32_t)(a % (REVOLUX_HASH_MEMORY_SIZE / 8)) * 8;
        uint32_t idx2 = (uint32_t)(b % (REVOLUX_HASH_MEMORY_SIZE / 8)) * 8;
        uint32_t idx3 = (uint32_t)(c % (REVOLUX_HASH_MEMORY_SIZE / 8)) * 8;

        // Read from memory (data-dependent)
        uint64_t mem_val1, mem_val2, mem_val3;
        memcpy(&mem_val1, memory + idx1, 8);
        memcpy(&mem_val2, memory + idx2, 8);
        memcpy(&mem_val3, memory + idx3, 8);

        // Sequential operations with data-dependent branching
        a = a ^ mem_val1;
        b = b + mem_val2;
        c = c * ((mem_val3 % 2 == 0) ? 3 : 7);  // Data-dependent branching

        // Additional sequential dependency
        if ((a & 1) == 0) {  // Data-dependent condition
            d = d ^ a;
        } else {
            d = d + b;
        }

        // Write back to memory (interleaved read/write)
        uint64_t new_val = a ^ b ^ c ^ d ^ (uint64_t)i;
        memcpy(memory + idx1, &new_val, 8);

        // Rotate state for next iteration (maintains sequential dependency)
        uint64_t temp = a;
        a = b;
        b = c;
        c = d;
        d = temp;
    }

    // Second phase: additional memory operations with different pattern
    for (uint32_t i = 0; i < 512; ++i) {
        // Different data-dependent indices
        uint32_t idx = (uint32_t)((a ^ b ^ c ^ d) % (REVOLUX_HASH_MEMORY_SIZE / 16)) * 16;

        // Read 16 bytes
        uint64_t val1, val2;
        memcpy(&val1, memory + idx, 8);
        memcpy(&val2, memory + idx + 8, 8);

        // Complex operations to resist optimization
        a += val1;
        b ^= val2;
        c = (c + a) ^ (b * 17);  // Non-linear operations
        d = d ^ (c >> 3);        // Bit operations

        // Data-dependent write
        if ((d & 3) == 1) {
            uint64_t write_val = a ^ b ^ c ^ d;
            memcpy(memory + idx, &write_val, 8);
        } else if ((d & 3) == 2) {
            uint64_t write_val = (a + b) * (c ^ d);
            memcpy(memory + idx + 8, &write_val, 8);
        }
        // else: no write (data-dependent control flow)
    }

    // Final phase: condense to output
    uint64_t final_state[4] = {a, b, c, d};

    // Mix with remaining input bytes (bytes 32-105)
    for (size_t i = 32; i < REVOLUX_HASH_INPUT_SIZE; ++i) {
        uint8_t byte_val = input[i];
        final_state[i % 4] ^= (uint64_t)byte_val << ((i % 8) * 8);
    }

    // Additional mixing with memory content
    for (uint32_t i = 0; i < 32; ++i) {
        uint32_t mem_idx = (uint32_t)(final_state[i % 4] % REVOLUX_HASH_MEMORY_SIZE);
        uint8_t mem_byte = memory[mem_idx];
        final_state[i % 4] ^= (uint64_t)mem_byte << ((i % 8) * 8);
    }

    // Final Keccak-like permutation for output
    // Simple diffusion to ensure all state affects all output
    for (int round = 0; round < 12; ++round) {
        // Theta step (diffusion)
        uint64_t t = final_state[0] ^ final_state[1] ^ final_state[2] ^ final_state[3];
        for (int i = 0; i < 4; ++i) {
            final_state[i] ^= t;
        }

        // Rho and pi steps (rotation and permutation)
        final_state[1] = (final_state[1] << 1) | (final_state[1] >> 63);
        final_state[2] = (final_state[2] << 62) | (final_state[2] >> 2);
        final_state[3] = (final_state[3] << 28) | (final_state[3] >> 36);

        // Chi step (non-linear mixing)
        uint64_t temp[4];
        for (int i = 0; i < 4; ++i) {
            temp[i] = final_state[i] ^ ((~final_state[(i+1)%4]) & final_state[(i+2)%4]);
        }
        memcpy(final_state, temp, sizeof(temp));
    }

    // Output exactly 32 bytes as per specification
    memcpy(output, final_state, REVOLUX_HASH_OUTPUT_SIZE);

    // Clean up memory
    free(memory);
}
