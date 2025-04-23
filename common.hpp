namespace math_tools {

template<class T>
T border(T value, T min, T max) {
    return value > max ? max : (value < min ? min : value);
}

}