#include "hashes.hpp"

unsigned int math_tools::crc32(unsigned char *buf, unsigned long len) {
    unsigned long crc_table[256];
    unsigned long crc;
    for (int i = 0; i < 256; i++) {
        crc = i;
        for (int j = 0; j < 8; j++)
            crc = crc & 1 ? (crc >> 1) ^ 0xedb88320UL : crc >> 1;
        crc_table[i] = crc;
    };
    crc = 0xffffffffUL;
    while (len--) {
        crc = crc_table[(crc ^ *buf++) & 0xff] ^ (crc >> 8);
    }
    return crc ^ 0xffffffffUL;
}

unsigned int math_tools::crc32_fast(unsigned char *buf, unsigned long len) {
    static bool crc_computed = false;
    static unsigned long global_crc_table[256];
    unsigned long crc;
    if (!crc_computed) {
        for (int i = 0; i < 256; i++) {
            crc = i;
            for (int j = 0; j < 8; j++)
                crc = crc & 1 ? (crc >> 1) ^ 0xedb88320UL : crc >> 1;
            global_crc_table[i] = crc;
        }
    }
    crc = 0xffffffffUL;
    while (len--) {
        crc = global_crc_table[(crc ^ *buf++) & 0xff] ^ (crc >> 8);
    }
    return crc ^ 0xffffffffUL;
}