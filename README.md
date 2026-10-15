# vhlibmetacrc — PUSHK Metablock Hash Calculation Library

**vhlibmetacrc** is a lightweight C++ library designed for fast and efficient hash (CRC-16) calculation and validation of data metablocks. It features compile-time lookup table generation, automated disk-based caching of precomputed hash tables, and O(1) metadata validation.

---

## Library Metadata

* **Repository:** https://github.com/vigatron/vhlibmetacrc
* **Revision:** `0.0.1`
* **Main Headers:** `src/vhmetablock.hpp`, `src/vhmetablock_cache.hpp`
* **Author:** Viktor Glebov (`V01G04A81`)
* **Copyright:** © 2026 Viktor Glebov
* **License:** MIT

---

## Key Features

* **Compile-Time CRC-16 Table:** The `VHMetaBlockCRC16` class generates its 256-entry lookup table at compile-time using `constexpr`, ensuring zero initialization overhead and maximum runtime performance.
* **Automated Hash Caching:** The `BlockMeta` class automatically generates and saves precomputed CRC-16 tables for various block lengths (from 64 down to 5 bytes) to disk (`.metacrc16` files), eliminating redundant calculations on subsequent runs.
* **O(1) Validation:** The `BlockMetaCache` class provides ultra-fast validation checks using a fixed-size index array (`sidx`), allowing instant verification of whether a specific metablock segment has been processed.
* **Configurable:** Cache behavior can be completely bypassed at compile-time using the `CFG_DISABLE_CRC_CACHE` macro.

---

## Core Components

The library is divided into three main logical units:

* **VHMetaBlockCRC16:** The foundational CRC-16 engine. Provides fast, table-based calculation for arbitrary byte arrays.
* **BlockMeta:** Manages the lifecycle of metablock metadata. It calculates the source block CRC, determines the cache file path, and handles loading/generating the multi-length CRC table.
* **BlockMetaCache:** A high-level caching facade. It wraps `BlockMeta` and provides `check()` and `mark()` methods to track the validation state of specific block segments (defined by length, offset, and level).

---

## API Reference

### VHMetaBlockCRC16
| Method | Description |
|--------|-------------|
| `generate_table()` | `constexpr` function that generates the 256-element CRC-16 lookup table at compile time. |
| `calculate(const uint8_t* data, size_t len, uint16_t initial)` | Fast table-based CRC-16 calculation for a given data buffer. |

### BlockMeta
| Method | Description |
|--------|-------------|
| `Generate(uint16_t blksize, uint8_t *blkdat)` | Initializes metadata, calculates source CRC, and either loads or generates the cache file. |
| `crc(uint8_t ll, uint16_t pos, uint16_t blksize) const` | Retrieves the precomputed CRC-16 value for a specific level (`ll`), position, and block size. |

### BlockMetaCache
| Method | Description |
|--------|-------------|
| `init(uint16_t blen, uint8_t *bsrc)` | Initializes the cache and generates/loads metadata for the source block. |
| `check(uint16_t srclen, uint16_t offs, uint8_t ll) const` | Returns `true` if the specific segment CRC has been previously marked as valid. |
| `mark(uint16_t srclen, uint16_t offs, uint8_t ll)` | Marks the specific segment CRC as valid in the internal `sidx` array. |
| `cleanmarks()` | Resets all validation marks in the `sidx` array. |

---

## Basic Usage Examples

### Initialization and Validation

```cpp
#include "vhmetablock_cache.hpp"
#include <iostream>
#include <vector>

int main() {
    // Sample data block
    std::vector<uint8_t> data = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint16_t blksize = static_cast<uint16_t>(data.size());

    // Initialize the cache
    BlockMetaCache cache;
    if (!cache.init(blksize, data.data())) {
        std::cerr << "Failed to initialize BlockMetaCache" << std::endl;
        return 1;
    }

    uint16_t srclen = 4;
    uint16_t offs = 0;
    uint8_t ll = 1; // level/length descriptor

    // Check if this specific metablock segment was already processed
    if (cache.check(srclen, offs, ll)) {
        std::cout << "Segment already validated (cached)." << std::endl;
    } else {
        std::cout << "Segment not cached. Processing and marking..." << std::endl;
        // ... perform actual processing ...
        cache.mark(srclen, offs, ll);
    }

    return 0;
}
```



---

## Data Format Specification

### Cache File Naming
The library automatically generates a unique filename for the precomputed hash table based on the source block's size and its overall CRC-16:
`metablock_<srcfile_size_hex>_<srcfile_crc_hex>.metacrc16`

### Cache File Structure
* **Size:** `(64 + 1) * blksize * sizeof(uint16_t)` bytes.
* **Content:** A flat binary array of `uint16_t` values. It stores precomputed CRC-16 hashes for block lengths `d` ranging from 64 down to 5, for every possible offset in the source block. This allows O(1) lookup during validation.

---

## Integration & Requirements

### Requirements
* C++17 or higher (required for `constexpr` std::array and `<filesystem>`).
* Standard C++ Library (STL) with `<filesystem>` support.
* Linking with the standard filesystem library may be required on some compilers (e.g., `-lstdc++fs` on older GCC versions).

### Configuration
* **CFG_DISABLE_CRC_CACHE:** Define this macro to `1` to bypass all cache checks and force `check()` to always return `true`. Useful for debugging or environments without filesystem access.

```cpp
#define CFG_DISABLE_CRC_CACHE 1
#include "vhmetablock_cache.hpp"
```

### License
This project is licensed under the MIT License — see the source headers or the LICENSE file for details.

Copyright (c) 2026 Viktor Glebov / V01G04A81
