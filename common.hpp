namespace math_tools {

    enum endianness_t {
        unknown,
        little,
        big
    };

    extern endianness_t get_host_endian();
    extern short htob16(short data);
    extern short htol16(short data);
    extern int htob32(int data);
    extern int htol32(int data);

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