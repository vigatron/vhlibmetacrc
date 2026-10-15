/* ======================================================================================
 * Library       : vhlibmetacrc
 * Description   : PUSHK metablock hash calculation library
 * Revision      : 0.0.1
 * Source        : https://github.com/vigatron/vhlibmetacrc
 * Disclaimer    : Provided "AS IS", without warranty.
 * License       : MIT
 * File          : src/vhmetablock.cpp
 * Content size  : 2719
 * Date / Time   : 15-10-2026 15:55:09
 * MD5           : ab6be8e000d86564e9aff641b0d3e202
 * Notes         : MD5 = file content without header/footer
 * Encoding      : UTF-8
 * Author        : Viktor Glebov / V01G04A81
 * Copyright     : © 2026 Viktor Glebov
 * ========================[ BEGIN FILE CONTENT ]====================================== */
#include "vhmetablock.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>


extern std::string szhex16(uint16_t v);

/**
 * 
 */
BlockMeta::BlockMeta() : srcfile_size(0), srcfile_crc(0) {

}

/**
 * 
 */
BlockMeta::~BlockMeta() {

}

/**
 * 
 */
bool BlockMeta::empty() {
    return arrtbl.empty();
}

/**
 * 
 */
bool BlockMeta::Generate(uint16_t blksize, uint8_t *blkdat) {

    if (!blksize)
        return false;
    
    arrtbl.clear();

    srcfile_size = blksize;
    srcfile_crc = VHMetaBlockCRC16::calculate(blkdat, blksize);
    std::string fname = getfname();
    if (!isfileexist(fname))
        return GenerateFile(fname, blksize, blkdat);
    return InternalLoad(fname, blksize, blkdat);
}

/**
 * 
 */
uint16_t BlockMeta::crc(uint8_t ll, uint16_t pos, uint16_t blksize) const {
    int offs = ll * blksize + pos;
    return arrtbl[offs];
}

/**
 * 
 */
std::string BlockMeta::getfname() {
    return "metablock_" + szhex16(srcfile_size) + "_" + szhex16(srcfile_crc) + ".metacrc16";
}

/**
 * 
 */
int BlockMeta::calcfsize(uint16_t blksize) {
    return (64 + 1) * blksize * sizeof(uint16_t);
}

/**
 * 
 */
bool BlockMeta::isfileexist(std::string filename) {
    if (std::filesystem::exists(filename))
        if (std::filesystem::is_regular_file(filename))
            return true;
    return false;
}

/**
 * 
 */
bool BlockMeta::InternalLoad(std::string fname, uint16_t blksize, uint8_t *blkdat) {

    tbl_crc_size = calcfsize(blksize);
    if (std::filesystem::file_size(fname) != tbl_crc_size)
        return false;
    
    arrtbl.resize(tbl_crc_size);

    std::ifstream inFile(fname, std::ios::in | std::ios::binary);
    inFile.read((char *)arrtbl.data(), tbl_crc_size);
    bool status = inFile.good();
    inFile.close();
    return status;
}

/**
 * 
 */
bool BlockMeta::GenerateFile(std::string fname, uint16_t blksize, uint8_t *blkdat) {

    tbl_crc_size = calcfsize(blksize);
    arrtbl.resize(tbl_crc_size);
    arrtbl.assign(tbl_crc_size, 0);

    for (int d = 64; d > 4; d--)
        GenerateD(d, blksize, blkdat, arrtbl.data() + d * blksize);
    SaveResults(fname);
    return true;
}

/**
 * 
 */
bool BlockMeta::SaveResults(std::string fname) {
    std::ofstream outFile(fname, std::ios::out | std::ios::binary);
    if (!outFile.is_open())
        return false;
    outFile.write(reinterpret_cast<const char *>(arrtbl.data()), tbl_crc_size);
    outFile.close();
    std::cout << "File : " + fname + " created" << std::endl;
    return true;
}

/**
 * 
 */
void BlockMeta::GenerateD(int d, uint16_t blksize, uint8_t *blkdat, uint16_t *pdst) {
    for (int i = 0; i <= (srcfile_size - d); i++) {
        pdst[i] = VHMetaBlockCRC16::calculate(blkdat + i, d);
    }
}
/* ========================[  END FILE CONTENT  ]========================
 * Library          : vhlibmetacrc
 * File             : src/vhmetablock.cpp
 * Revision         : 0.0.1
 * Content size     : 2719
 * Date / Time      : 15-10-2026 15:55:09
 * MD5              : ab6be8e000d86564e9aff641b0d3e202
 * Copyright        : © 2026 Viktor Glebov
 * ====================================================================== */