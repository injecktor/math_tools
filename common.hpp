namespace math_tools {

    enum endianness_t {
        unknown,
        little,
        big
    };

    extern inline endianness_t get_host_endian();
    extern inline short htobe16(short data);
    extern inline short htole16(short data);
    extern inline int htobe32(int data);
    extern inline int htole32(int data);

    template<class T>
    T border(T value, T min, T max) {
        return value > max ? max : (value < min ? min : value);
    }

    template<class T>
    void swap(T* left, T* right) {
        T tmp = *left;
        *left = *right;
        *right = tmp;
    }

}