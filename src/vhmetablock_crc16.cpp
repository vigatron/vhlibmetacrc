/* ======================================================================================
 * Library       : vhlibmetacrc
 * Description   : PUSHK metablock hash calculation library
 * Revision      : 0.0.1
 * Source        : https://github.com/vigatron/vhlibmetacrc
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/vhmetablock_crc16.cpp
 * Content size  : 813
 * Date / Time   : 15-10-2026 15:55:09
 * MD5           : 27a1527ea1ae7e2b48f3b27c77ee313e
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]====================================== */
#include "vhmetablock_crc16.hpp"

/**
 * @brief Generates the lookup table at compile-time
 */
constexpr std::array<uint16_t, 256> VHMetaBlockCRC16::generate_table() {
    std::array<uint16_t, 256> table{};
    for (int i = 0; i < 256; ++i) {
        uint16_t crc = static_cast<uint16_t>(i << 8);
        for (int j = 0; j < 8; ++j) {
            crc = (crc & 0x8000) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
        }
        table[i] = crc;
    }
    return table;
}

/**
 * @brief Fast table-based calculation
 */
uint16_t VHMetaBlockCRC16::calculate(const uint8_t *data, size_t len, uint16_t initial) {
    static constexpr auto table = generate_table();
    uint16_t crc = initial;
    for (size_t i = 0; i < len; ++i) {
        crc = (crc << 8) ^ table[((crc >> 8) ^ data[i]) & 0xFF];
    }
    return crc;
}
/* ========================[  END FILE CONTENT  ]========================
 * Library          : vhlibmetacrc
 * File             : src/vhmetablock_crc16.cpp
 * Revision         : 0.0.1
 * Content size     : 813
 * Date / Time      : 15-10-2026 15:55:09
 * MD5              : 27a1527ea1ae7e2b48f3b27c77ee313e
 * Copyright        : © 2026 Viktor Glebov
 * ====================================================================== */