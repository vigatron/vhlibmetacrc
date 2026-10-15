/* ======================================================================================
 * Library       : vhlibmetacrc
 * Description   : PUSHK metablock hash calculation library
 * Revision      : 0.0.1
 * Source        : https://github.com/vigatron/vhlibmetacrc
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/vhmetablock_cache.hpp
 * Content size  : 591
 * Date / Time   : 15-10-2026 15:55:09
 * MD5           : a0a4cb9943735b53d9e688ecb0960ae0
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]====================================== */
#pragma once

#include "vhmetablock.hpp"

class BlockMetaCache {

  public:
    explicit BlockMetaCache();

    ~BlockMetaCache();

    bool empty();

    void cleanmarks();

    uint16_t val(uint16_t srclen, uint16_t offs, uint8_t ll);

    bool init(uint16_t blen, uint8_t *bsrc);

    bool check(uint16_t srclen, uint16_t offs, uint8_t ll) const;

    void mark(uint16_t srclen, uint16_t offs, uint8_t ll);

  private:
    //
    static const int POS_COUNT_MAX = 65536;

    //
    std::array<uint8_t, POS_COUNT_MAX> sidx;

    // CRC-16 blocks for 64 for tables
    BlockMeta blkmeta;
};
/* ========================[  END FILE CONTENT  ]========================
 * Library          : vhlibmetacrc
 * File             : src/vhmetablock_cache.hpp
 * Revision         : 0.0.1
 * Content size     : 591
 * Date / Time      : 15-10-2026 15:55:09
 * MD5              : a0a4cb9943735b53d9e688ecb0960ae0
 * Copyright        : © 2026 Viktor Glebov
 * ====================================================================== */