# Revolux Phase 3.2 — Proof-of-Work Specification
# RevoluxHash (Design-Freeze Document)

**Status:** DESIGN FROZEN  
**Consensus Impact:** YES  
**Code Impact:** NO  
**Phase:** 3.2 Complete  

---

## 1. Formal RevoluxHash Specification (RULES ONLY)

RevoluxHash is the proof-of-work algorithm for the Revolux network. This specification defines the exact computational requirements and verification rules that constitute protocol consensus law.

### A. Exact PoW Inputs

The proof-of-work input consists of the following block header fields, concatenated in this exact order:

1. **block.major_version** (uint8_t) - Protocol version identifier
2. **block.minor_version** (uint8_t) - Protocol minor version
3. **block.timestamp** (uint64_t, little-endian) - Block timestamp in Unix epoch seconds
4. **block.prev_id** (32 bytes, little-endian) - Previous block hash
5. **block.nonce** (uint32_t, little-endian) - Proof-of-work nonce
6. **merkle_root** (32 bytes, little-endian) - Merkle root of all transactions in the block
7. **transaction_count** (uint64_t, little-endian) - Number of transactions in the block

No additional fields may be included. No fields may be omitted or reordered.

### B. Serialization Rules

**Input Preparation:**
- All multi-byte integers MUST be serialized in little-endian byte order
- No padding bytes are permitted between fields
- The concatenated input MUST be exactly 106 bytes in length
- Input buffer MUST be treated as immutable during computation

**Hash Output:**
- Final hash output MUST be 32 bytes (256 bits)
- Output MUST be in little-endian byte order
- Hash comparison for difficulty MUST use the first 32 bytes of output

**Determinism Requirements:**
- Same input bytes MUST always produce identical output bytes
- No random number generation permitted during computation
- No external state dependencies allowed
- Computation MUST be deterministic across all platforms and implementations

### C. Memory Model

**Memory Size:**
- Working memory allocation MUST be exactly 2,097,152 bytes (2 MiB)
- Memory MUST be allocated as a contiguous byte array
- No additional memory allocations permitted during computation

**Allocation Timing:**
- Memory MUST be allocated before computation begins
- Memory MUST remain allocated for the entire computation duration
- Memory MUST be zero-initialized before use

**Lifetime Rules:**
- Memory content MUST NOT persist between separate proof-of-work computations
- Memory MUST be treated as uninitialized on each computation start
- No precomputation or caching of memory content permitted

**Access Pattern:**
- Memory access MUST be data-dependent (not fixed-index)
- Read and write operations MUST interleave throughout computation
- Memory MUST be both read from and written to during computation
- Access pattern MUST prevent efficient parallelization

### D. Execution Model

**Sequential Dependency:**
- All operations MUST maintain sequential dependency on previous results
- No independent parallel execution paths permitted
- Computation MUST be fundamentally serial in nature

**Branching Expectations:**
- Control flow MUST depend on computed data values
- No predictable branching patterns allowed
- Conditional operations MUST be data-dependent

**Parallelism Limits:**
- Algorithm MUST resist efficient SIMD vectorization
- Memory access pattern MUST prevent coalesced memory operations
- Computation MUST require random-access memory patterns

**ASIC Resistance Characteristics:**
- Memory access MUST be irregular and data-dependent
- Computation MUST include operations that are inefficient in fixed-function hardware
- Algorithm MUST favor general-purpose processors over specialized hardware

---

## 2. Explicit Threat Model

### CPU Miner
**Capability:** Access to consumer-grade CPU hardware with multiple cores  
**Advantage:** Low power consumption, general-purpose computing flexibility  
**RevoluxHash Defense:** Memory-bound nature prevents efficient multi-core scaling. Data-dependent memory access patterns limit instruction-level parallelism that CPUs excel at.

### GPU Miner
**Capability:** Massive parallel processing with thousands of cores and high memory bandwidth  
**Advantage:** SIMD operations and parallel thread execution  
**RevoluxHash Defense:** Sequential dependency requirements prevent parallel execution. Irregular memory access patterns defeat GPU memory coalescing optimizations. Memory size exceeds efficient GPU cache capacity.

### ASIC Builder
**Capability:** Custom silicon design optimized for specific computational patterns  
**Advantage:** Extreme power efficiency and computational density  
**RevoluxHash Defense:** Data-dependent control flow prevents fixed-function optimization. Memory access patterns require flexible addressing that ASICs cannot efficiently implement. Algorithm evolution potential deters long-term investment in fixed hardware.

### Botnet Operator
**Capability:** Access to compromised systems across global networks  
**Advantage:** Effectively unlimited computational resources at near-zero marginal cost  
**RevoluxHash Defense:** Memory requirements limit deployment on resource-constrained systems. Data-dependent patterns prevent efficient distribution of work units. Economic resistance through computational intensity discourages casual participation.

---

## 3. Invariant List (NON-NEGOTIABLE)

The following invariants are consensus-critical and MUST NOT be violated under any circumstances. Violation of any invariant requires a hard fork.

**Input Structure:**
- Input field order MUST NOT change
- Input field count MUST remain exactly 7
- Input byte length MUST remain exactly 106 bytes
- No additional input fields MAY be added

**Serialization:**
- Little-endian byte order MUST NOT change
- No padding bytes MAY be introduced
- Field concatenation rules MUST NOT change

**Memory Model:**
- Memory size MUST remain exactly 2,097,152 bytes
- Memory MUST remain contiguous
- Memory MUST be zero-initialized
- Memory lifetime rules MUST NOT change

**Execution Model:**
- Sequential dependency MUST be maintained
- Data-dependent access patterns MUST be preserved
- Parallelism limits MUST NOT be relaxed
- Determinism requirements MUST be enforced

**Output Format:**
- Output size MUST remain 32 bytes
- Output byte order MUST remain little-endian
- Hash comparison method MUST NOT change

**Consensus Impact:**
- Difficulty calculation MUST use identical comparison logic
- Block validation MUST enforce all invariants
- No exceptions or special cases permitted

---

## 4. Implementation Boundary Declaration

### Allowed Future Changes (Difficulty Adjustment Only)
The following parameters MAY be adjusted through future soft forks:

**Difficulty Window:**
- Block count in difficulty calculation window
- Time weighting factors for timestamp variance
- Maximum adjustment factors for extreme hashrate changes

**Timestamp Validation:**
- Future timestamp tolerance
- Median timestamp weighting
- Clock drift compensation factors

### Forbidden Forever (Protocol Constants)
The following MUST NEVER change and require hard forks if modification is necessary:

**Algorithm Structure:**
- RevoluxHash computational model
- Memory size and allocation rules
- Input field definitions and ordering
- Serialization format and endianness

**Consensus Rules:**
- Proof-of-work verification logic
- Difficulty adjustment algorithm (beyond parameter tuning)
- Block header validation requirements

**Economic Parameters:**
- Block reward schedule
- Transaction fee structure
- Mining distribution rules

### Implementation Scope Declaration

**Permitted Implementation Directories:**
- `src/crypto/` - Core cryptographic primitives
- `src/cryptonote_core/` - Consensus rule implementation
- `src/blockchain_db/` - Block validation and storage
- `tests/` - Algorithm verification tests

**Protected Protocol Components:**
- `src/cryptonote_config.h` - Network constants (no PoW changes)
- `src/cryptonote_basic/` - Core data structures (no header modifications)
- `src/blockchain_utilities/` - Block utilities (validation only)

**Implementation Constraints:**
- No changes to block header structure
- No modifications to transaction format
- No alterations to consensus validation paths
- No introduction of new network messages

---

## Phase 3.2 Design Freeze Declaration

**RevoluxHash is now protocol law.**

The RevoluxHash proof-of-work specification is hereby frozen and constitutes binding consensus rules for the Revolux network. No further modifications to the proof-of-work algorithm, memory model, input structure, or execution requirements are permitted.

**Implementation may begin only in Phase 4 or later phases explicitly designated for implementation work.**

This document serves as the authoritative reference for all future Revolux protocol implementations, audits, and consensus enforcement.

**Design Freeze Date:** [Current Date]  
**Phase 3.2 Status:** COMPLETE  
**Next Phase:** Implementation preparation (Phase 4)

---

*This specification document is immutable consensus law. All implementations must conform exactly to these rules.*
