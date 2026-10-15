/* ======================================================================================
 * Library       : vhlibmetacrc
 * Description   : PUSHK metablock hash calculation library
 * Revision      : 0.0.1
 * Source        : https://github.com/vigatron/vhlibmetacrc
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/vhmetablock_cache.cpp
 * Content size  : 934
 * Date / Time   : 15-10-2026 15:55:09
 * MD5           : cab83f6a01f74953d3b09f82335db992
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]====================================== */
#include "vhmetablock_cache.hpp"


/**
 * 
 */
BlockMetaCache::BlockMetaCache() {
}

/**
 * 
 */
BlockMetaCache::~BlockMetaCache() {
}

/**
 * 
 */
bool BlockMetaCache::empty() {
    return blkmeta.empty();
}

/**
 * 
 */
void BlockMetaCache::cleanmarks() {
    sidx.fill(0);
}

/**
 * 
 */
uint16_t BlockMetaCache::val(uint16_t srclen, uint16_t offs, uint8_t ll) {
    return blkmeta.crc(ll, offs, srclen);
}

/**
 * 
 */
bool BlockMetaCache::init(uint16_t blen, uint8_t *bsrc) {
    cleanmarks();
    return blkmeta.Generate(blen, bsrc);
}

/**
 * 
 */
bool BlockMetaCache::check(uint16_t srclen, uint16_t offs, uint8_t ll) const {

#if CFG_DISABLE_CRC_CACHE != 0
    return 1;
#else
    uint16_t crcval = blkmeta.crc(ll, offs, srclen);
    return sidx[crcval];
#endif
}

/**
 * 
 */
void BlockMetaCache::mark(uint16_t srclen, uint16_t offs, uint8_t ll) {
    uint16_t crcval = blkmeta.crc(ll, offs, srclen);
    sidx[crcval] = 1;
}
/* ========================[  END FILE CONTENT  ]========================
 * Library          : vhlibmetacrc
 * File             : src/vhmetablock_cache.cpp
 * Revision         : 0.0.1
 * Content size     : 934
 * Date / Time      : 15-10-2026 15:55:09
 * MD5              : cab83f6a01f74953d3b09f82335db992
 * Copyright        : © 2026 Viktor Glebov
 * ====================================================================== */