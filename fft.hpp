#include <complex>
#include <vector>

// Wasn't tested

namespace math_tools {

template<class T, class V>
std::vector<std::complex<V>>& dft(const std::vector<T>& input) {
    size_t n = input.size();
    std::vector<std::complex<V>> result;
    result.resize(n);
    std::vector<std::complex<T>> input_complex;
    input_complex.reserve(n);
    for (const auto&& elem : input) {
        input_complex.emplace_back(elem, 0);
    }
    double step = 6.28318530718 / n;
    std::complex<double> w(cos(step), sin(-step));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            result[i] += std::pow(w, i * j) * input_complex[j];
        }
    }
    return result;
}

template<class T, class V>
std::vector<V>& idft(const std::vector<std::complex<T>>& input) {
    size_t n = input.size();
    std::vector<std::complex<V>> result_complex;
    result_complex.resize(n);
    std::vector<V> result;
    result.resize(n / 2);
    double step = 6.28318530718 / n;
    std::complex<double> w(cos(step), sin(step));

    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            result_complex[i] += std::pow(w, i * j) * input[j];
        }
        result_complex[i] /= n;
        result[i] = result_complex[i].real;
    }
    return result;
}

template<class T, class V>
std::vector<std::complex<V>>& fft(const std::vector<T>& input) {
    std::vector<std::complex<T>> input_complex;
    for (const auto&& elem : input) {
        input_complex.emplace_back(elem, 0);
    }
    for (const auto&& elem : input) {
        input_complex.emplace_back(elem, 0);
    }
    
    fft_alg(&input_complex);
    return input_complex;
}

template<class T, class V>
std::vector<V>& ifft(const std::vector<std::complex<T>>& input) {
    size_t n = input.size();
    auto tmp = const_cast<std::vector<std::complex<T>>&>(input);
    fft_alg(&tmp, true);

    std::vector<V> result;
    result.reserve(n / 2);
    for (int i = 0; i < n / 2; ++i) {
        result.push_back(tmp[i].real);
    }
    return result;
}

template<class T>
static void fft_alg(std::vector<std::complex<T>>* input, bool is_invert) {
    int n = input->size();
    if (n <= 1) {
        return;
    }

    std::vector<std::complex<T>> odd;
    std::vector<std::complex<T>> even;
    odd.resize(n / 2);
    even.resize(n / 2);
    for (int i = 0; i < n / 2; i++) {
        even[i] = (*input)[2*i];
        odd[i] = (*input)[2*i+1];
    }

    fft_alg(&even);
    fft_alg(&odd);

    std::complex<double> w;
    double step = 6.28318530718 / n;

    w.real = cos(step);
    if (is_invert) {
        w.imag = sin(step);
    } else {
        w.imag = sin(-step);
    }

    for (int i = 0; i < n / 2; i++) {
        std::complex<T> t = std::pow(w, i) * odd[i];
        (*input)[i] = even[i] + t;
        (*input)[n / 2 + i] = even[i] - t;
        if (is_invert) {
            (*input)[i] = (*input)[i] / n * (-1);
            (*input)[n / 2 + i] = (*input)[n / 2 + i] / n * (-1);
        }
    }
}

}
