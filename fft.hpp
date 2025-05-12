#include <complex>
#include <vector>

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

// QVector<double> idft() {
//     QVector<ComplexNum> comRes;
//     QVector<double> res;

//     comRes.resize(N);

//     ComplexNum w(cos(2 * PI / N), sin(2 * PI / N));

//     for (int k = 0; k < N / 2; k++) {
//         for (int j = 0; j < N; j++) {
//             comRes[k] = comRes[k] + w.power(k * j) * complexfft[j];
//         }
//         comRes[k] = comRes[k] / N;
//         res.push_back(comRes[k].real);
//     }

//     return res;
// }

// void fft(QVector<double> signal) {
//     for (int i = 0; i < signal.size(); i++) {
//         complexfft.push_back(ComplexNum(signal[i], 0));
//         // x_out[i] *= 1; // Window
//     }

//     for (int i = 0; i < signal.size(); i++) {
//         complexfft.push_back(ComplexNum(signal[i], 0));
//         // x_out[i] *= 1; // Window
//     }

//     //fft algorithm
//     fft_alg(&complexfft);

//     for (int var = 0; var < N / 2; ++var) {
//         ComplexNum tmp = complexfft[var];
//         doublefft.push_back(sqrt(tmp.real * tmp.real + tmp.imag * tmp.imag));
//     }
// }

// QVector<double> ifft() {
//     QVector<ComplexNum> tmp;
//     tmp = complexfft;

//     fft_alg(&tmp, true);

//     QVector<double> res;
//     for (int var = 0; var < N / 2; ++var) {
//         res.push_back(tmp.at(var).real);
//     }
//     return res;
// }

// static void fft_alg(QVector<ComplexNum>* signal, bool isInvert) {
//     //check if it's splitted enough
//     int n = signal->size();
//     if (n <= 1) {
//         return;
//     }

//     //split even and odd
//     QVector<ComplexNum> odd;
//     QVector<ComplexNum> even;
//     odd.resize(n / 2);
//     even.resize(n / 2);
//     for (int i = 0; i < n / 2; i++) {
//         even[i] = signal->at(2*i);
//         odd[i] = signal->at(2*i+1);
//     }

//     fft_alg(&even);
//     fft_alg(&odd);

//     ComplexNum w;

//     //calculate FFT
//     if (isInvert)
//         w = ComplexNum(cos(2 * PI / n), sin(2 * PI / n));
//     else
//         w = ComplexNum(cos(2 * PI / n), sin(-2 * PI / n));

//     for (int k = 0; k < n / 2; k++) {
//         ComplexNum t = w.power(k) * odd[k];
//         (*signal)[k] = even.at(k) + t;
//         (*signal)[n / 2 + k] = even.at(k) - t;
//         if (isInvert) {
//             (*signal)[k] = (*signal)[k] / N * (-1);
//             (*signal)[n / 2 + k] = (*signal)[n / 2 + k] / N * (-1);
//         }
//     }
// }
