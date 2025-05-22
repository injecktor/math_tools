#pragma once

namespace math_tools {

    /*
    CRC-32/ISO-HDLC
    CRC-32
    CRC-32/ADCCP
    CRC-32/V-42
    CRC-32/XZ
    */
    extern unsigned int crc32(unsigned char *buf, unsigned long len);
    extern unsigned int crc32_fast(unsigned char *buf, unsigned long len, unsigned long start_crc);

}