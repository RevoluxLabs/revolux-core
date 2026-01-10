/*
 * RevoluxHash — Proof-of-Work Function
 *
 * STATUS: IMPLEMENTED, NOT ACTIVATED
 *
 * This file contains the RevoluxHash PoW implementation
 * as defined in docs/POW_REVOLUXHASH_SPEC.md.
 *
 * ⚠️ CONSENSUS NOTICE:
 * - This function MUST NOT be called from block validation.
 * - Network activation is governed strictly by Phase 3.4.
 * - Any activation requires explicit consensus upgrade.
 *
 * Do NOT modify behavior without protocol approval.
 */

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

#pragma once

#include <stdint.h>
#include <stddef.h>

#define REVOLUX_HASH_MEMORY_SIZE 2097152  // 2 MiB exactly as per spec
#define REVOLUX_HASH_INPUT_SIZE 106       // 106 bytes input as per spec
#define REVOLUX_HASH_OUTPUT_SIZE 32       // 32 bytes output as per spec

#ifdef __cplusplus
extern "C" {
#endif

/**
 * RevoluxHash proof-of-work function
 *
 * Computes RevoluxHash according to the frozen specification.
 *
 * @param input - 106 bytes of concatenated block header fields (immutable)
 * @param output - 32 bytes output buffer
 */
void revolux_hash(const uint8_t* input, uint8_t* output);

#ifdef __cplusplus
}
#endif
