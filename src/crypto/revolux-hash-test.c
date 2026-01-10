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

#include "revolux-hash.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Test vectors for RevoluxHash - must produce identical results across platforms
int main() {
    printf("RevoluxHash Test Vectors\n");
    printf("=======================\n\n");

    // Test vector 1: All zeros input
    uint8_t input1[REVOLUX_HASH_INPUT_SIZE] = {0};
    uint8_t output1[REVOLUX_HASH_OUTPUT_SIZE];

    revolux_hash(input1, output1);

    printf("Test Vector 1 (all zeros):\n");
    printf("Input:  ");
    for (size_t i = 0; i < REVOLUX_HASH_INPUT_SIZE; ++i) {
        printf("%02x", input1[i]);
    }
    printf("\nOutput: ");
    for (size_t i = 0; i < REVOLUX_HASH_OUTPUT_SIZE; ++i) {
        printf("%02x", output1[i]);
    }
    printf("\n\n");

    // Test vector 2: Known pattern
    uint8_t input2[REVOLUX_HASH_INPUT_SIZE];
    for (size_t i = 0; i < REVOLUX_HASH_INPUT_SIZE; ++i) {
        input2[i] = (uint8_t)(i * 17 + 42);
    }
    uint8_t output2[REVOLUX_HASH_OUTPUT_SIZE];

    revolux_hash(input2, output2);

    printf("Test Vector 2 (patterned input):\n");
    printf("Input:  ");
    for (size_t i = 0; i < REVOLUX_HASH_INPUT_SIZE; ++i) {
        printf("%02x", input2[i]);
    }
    printf("\nOutput: ");
    for (size_t i = 0; i < REVOLUX_HASH_OUTPUT_SIZE; ++i) {
        printf("%02x", output2[i]);
    }
    printf("\n\n");

    // Test vector 3: Genesis-like input (version 20, timestamp 0, etc.)
    uint8_t input3[REVOLUX_HASH_INPUT_SIZE] = {
        // major_version (uint8_t) = 20
        0x14,
        // minor_version (uint8_t) = 0
        0x00,
        // timestamp (uint64_t, little-endian) = 0
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // prev_id (32 bytes, little-endian) = null_hash
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // nonce (uint32_t, little-endian) = 0
        0x00, 0x00, 0x00, 0x00,
        // merkle_root (32 bytes, little-endian) = null_hash
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        // transaction_count (uint64_t, little-endian) = 1
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    uint8_t output3[REVOLUX_HASH_OUTPUT_SIZE];

    revolux_hash(input3, output3);

    printf("Test Vector 3 (genesis-like input):\n");
    printf("Input:  ");
    for (size_t i = 0; i < REVOLUX_HASH_INPUT_SIZE; ++i) {
        printf("%02x", input3[i]);
    }
    printf("\nOutput: ");
    for (size_t i = 0; i < REVOLUX_HASH_OUTPUT_SIZE; ++i) {
        printf("%02x", output3[i]);
    }
    printf("\n\n");

    // Verify determinism by running the same input twice
    uint8_t output3_verify[REVOLUX_HASH_OUTPUT_SIZE];
    revolux_hash(input3, output3_verify);

    printf("Determinism check: ");
    if (memcmp(output3, output3_verify, REVOLUX_HASH_OUTPUT_SIZE) == 0) {
        printf("PASS - Same input produces identical output\n");
    } else {
        printf("FAIL - Non-deterministic behavior detected\n");
        return 1;
    }

    printf("\nRevoluxHash test vectors complete.\n");
    return 0;
}
