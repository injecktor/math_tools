#include "common.hpp"

using namespace math_tools;

endianness_t host = endianness_t::unknown;

endianness_t math_tools::get_host_endian() {
    if (host == endianness_t::unknown) {
        endianness_t tmp;
        int a = 1;
        if (*reinterpret_cast<unsigned char*>(&a) == 1) {
            tmp = endianness_t::little;
        } else {
            tmp = endianness_t::big;
        }
        host = tmp;
    }
    return host;
}

short math_tools::htob16(short data) {
    short result = data;
    if (host == endianness_t::unknown) {
        get_host_endian();
    }
    if (host != endianness_t::big) {
        result = static_cast<unsigned short>(data) << 8 | data >> 8;
    }
    return result;
}

short math_tools::htol16(short data) {
    short result = data;
    if (host == endianness_t::unknown) {
        get_host_endian();
    }
    if (host != endianness_t::little) {
        result = static_cast<unsigned short>(data) << 8 | data >> 8;
    }
    return result;
}

int math_tools::htob32(int data) {
    int result = data;
    if (host == endianness_t::unknown) {
        get_host_endian();
    }
    if (host != endianness_t::big) {
        auto ptr = reinterpret_cast<unsigned char*>(&data);
        result = ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3];
    }
    return result;
}

int math_tools::htol32(int data) {
    int result = data;
    if (host == endianness_t::unknown) {
        get_host_endian();
    }
    if (host != endianness_t::little) {
        auto ptr = reinterpret_cast<unsigned char*>(&data);
        result = ptr[3] << 24 | ptr[2] << 16 | ptr[1] << 8 | ptr[0];
    }
    return result;
}