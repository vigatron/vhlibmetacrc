/* ======================================================================================
 * Library       : vhlibmetacrc
 * Description   : PUSHK metablock hash calculation library
 * Revision      : 0.0.2
 * Source        : https://github.com/vigatron/vhlibmetacrc
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/vhmetablock_crc16.hpp
 * Content size  : 407
 * Date / Time   : 15-10-2026 16:39:28
 * MD5           : 99616a9e18be998463a7370f950d5553
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]====================================== */
#pragma once

#include <vector>
#include <cstdint>
#include <array>


class VHMetaBlockCRC16 {
public:
    //
    static constexpr uint16_t POLYNOMIAL = 0x1021;

    // Generates the lookup table at compile-time
    static constexpr std::array<uint16_t, 256> generate_table();

    // Fast table-based calculation
    static uint16_t calculate(const uint8_t* data, size_t len, uint16_t initial = 0xFFFF);
};
/* ========================[  END FILE CONTENT  ]========================
 * Library          : vhlibmetacrc
 * File             : src/vhmetablock_crc16.hpp
 * Revision         : 0.0.2
 * Content size     : 407
 * Date / Time      : 15-10-2026 16:39:28
 * MD5              : 99616a9e18be998463a7370f950d5553
 * Copyright        : © 2026 Viktor Glebov
 * ====================================================================== */