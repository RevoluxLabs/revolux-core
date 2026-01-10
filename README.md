# Revolux (RVLX)

Revolux is an independent Layer-1 cryptocurrency implementing the CryptoNote protocol with enhanced privacy and a zero-premine fair launch.

## Overview

Revolux is a new cryptocurrency protocol with the following key characteristics:

- **Fair Launch:** Zero-premine genesis block - all coins must be earned through mining
- **Privacy by Default:** Ring signatures, stealth addresses, and unlinkable transactions
- **Immutable Genesis:** Cryptographically locked genesis block prevents chain splits
- **Network Separation:** Distinct mainnet and testnet with enforced isolation

This repository contains the reference implementation: node (revoluxd), wallet software, and development tools.

## Project Status

**Phase:** 3.3 (Proof-of-Work Implementation) - Complete ✅
**Genesis:** Finalized and cryptographically locked
**Testnet:** Operational
**Mainnet:** Ready for launch

RevoluxHash is implemented but not active. Network activation will occur in Phase 3.4 via an explicit consensus upgrade.

### Completed Phases
- **Phase 1:** Core implementation and testing
- **Phase 2:** Network identity and protocol hardening
- **Phase 3.1:** Genesis block finalization and network enforcement
- **Phase 3.2:** RevoluxHash proof-of-work specification (design-frozen)
- **Phase 3.3:** RevoluxHash implementation (no activation)

### Upcoming Phases
- **Phase 3.4:** RevoluxHash consensus activation
- **Phase 4:** Ecosystem development

## Fair Launch Guarantee

Revolux implements a true fair launch with no premine or pre-allocations:

- **Zero Genesis Outputs:** The genesis block coinbase transaction has zero outputs
- **No Developer Allocation:** No coins are pre-assigned to founders or developers
- **Mining-Only Distribution:** All RVLX coins must be earned through proof-of-work mining
- **Immutable Genesis:** The genesis block identity is cryptographically enforced and cannot be changed

## Network Configuration

### Mainnet
- **Ports:** P2P 18880, RPC 18881, ZMQ 18882
- **Data Directory:** `~/.revolux/`
- **Address Prefix:** 42 (public), 43 (integrated), 44 (subaddress)
- **Genesis Hash:** 24df5db85351f6ec613826082afcd07075ef0ffc1582bfdbf91d1e3274ecf9bb

### Testnet
- **Ports:** P2P 28080, RPC 28081, ZMQ 28082
- **Data Directory:** `~/.revolux/testnet/`
- **Address Prefix:** 63 (public), 64 (integrated), 65 (subaddress)
- **Genesis Hash:** 5f854609368bcf7307c7f52d6b58ae181c12066e9a715f08b5a9017f2d7f3527

## Building

The Revolux daemon must be built before it can be run. After building, binaries will be located in `build/bin/`.

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt update && sudo apt install build-essential cmake pkg-config libssl-dev libzmq3-dev libsodium-dev libunbound-dev libminiupnpc-dev libunwind8-dev liblzma-dev libreadline6-dev libexpat1-dev libgtest-dev libboost-all-dev libhidapi-dev libusb-1.0-0-dev libprotobuf-dev protobuf-compiler libudev-dev
```

### Build Steps
```bash
# Clone the repository
git clone <repository-url>
cd revolux-core

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ../monero -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF

# Build
make -j$(nproc)
```

### Binaries Produced
After building, the following binaries will be available in `build/bin/`:
- `revoluxd` - Main daemon/node
- `revolux-wallet` - CLI wallet
- `revolux-wallet-rpc` - RPC wallet interface
- `revolux-genesis-hash` - Genesis hash computation tool

## Usage

### Start Testnet Node
```bash
./build/bin/revoluxd --testnet --detach
```

### Create Wallet
```bash
./build/bin/revolux-wallet --testnet --generate-new-wallet wallet.bin
```

### Check Balance
```bash
./build/bin/revolux-wallet --testnet --wallet-file wallet.bin --balance
```

## Documentation

- [Build Guide](BUILD.md) - Detailed build instructions
- [Contributing Guide](docs/CONTRIBUTING.md) - Development guidelines
- Whitepaper v2.0 - Released soon

## Attribution

Revolux is derived from the CryptoNote protocol and inherits its cryptographic foundations. Revolux is an independent project and is not affiliated with, endorsed by, or connected to the Monero Project or any other cryptocurrency project.

## License

See [LICENSE](LICENSE) file for details. This project inherits the BSD 3-Clause license from its CryptoNote heritage.
