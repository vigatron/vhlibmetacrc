/* ======================================================================================
 * Library       : vhlibmetacrc
 * Description   : PUSHK metablock hash calculation library
 * Revision      : 0.0.2
 * Source        : https://github.com/vigatron/vhlibmetacrc
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/vhmetablock.hpp
 * Content size  : 1005
 * Date / Time   : 15-10-2026 16:39:28
 * MD5           : fcc684ce08b55ae793f1a2b746414db5
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

    static const char *_szhex;

    std::string strhex16(size_t v);

};
/* ========================[  END FILE CONTENT  ]========================
 * Library          : vhlibmetacrc
 * File             : src/vhmetablock.hpp
 * Revision         : 0.0.2
 * Content size     : 1005
 * Date / Time      : 15-10-2026 16:39:28
 * MD5              : fcc684ce08b55ae793f1a2b746414db5
 * Copyright        : © 2026 Viktor Glebov
 * ====================================================================== */