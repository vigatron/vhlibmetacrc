/* ======================================================================================
 * Library       : vhlibmetacrc
 * Description   : PUSHK metablock hash calculation library
 * Revision      : 0.0.1
 * Source        : https://github.com/vigatron/vhlibmetacrc
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/vhmetablock.hpp
 * Content size  : 966
 * Date / Time   : 15-10-2026 15:55:09
 * MD5           : ea3539b50db9d7f6697d4f0bed76078b
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]====================================== */
#pragma once

#include <array>
#include <cstdint>
#include <string>

#include "vhmetablock_crc16.hpp"

class BlockMeta {

  public:
    //
    BlockMeta();

    //
    ~BlockMeta();

    //
    bool empty();

    //
    bool Generate(uint16_t blksize, uint8_t *blkdat);

    //
    uint16_t crc(uint8_t ll, uint16_t pos, uint16_t blksize) const;

private:
    //
    uint16_t srcfile_size;
    //
    uint16_t srcfile_crc;

    //
    std::vector<uint16_t> arrtbl;

    //
    int tbl_crc_size;

    //
    // void dealloc();

    //
    std::string getfname();

    //
    int calcfsize(uint16_t blksize);

    //
    bool isfileexist(std::string filename);

    //
    bool InternalLoad(std::string fname, uint16_t blksize, uint8_t *blkdat);

    //
    bool GenerateFile(std::string fname, uint16_t blksize, uint8_t *blkdat);

    //
    bool SaveResults(std::string fname);

    //
    void GenerateD(int d, uint16_t blksize, uint8_t *blkdat, uint16_t *pdst);
};
/* ========================[  END FILE CONTENT  ]========================
 * Library          : vhlibmetacrc
 * File             : src/vhmetablock.hpp
 * Revision         : 0.0.1
 * Content size     : 966
 * Date / Time      : 15-10-2026 15:55:09
 * MD5              : ea3539b50db9d7f6697d4f0bed76078b
 * Copyright        : © 2026 Viktor Glebov
 * ====================================================================== */