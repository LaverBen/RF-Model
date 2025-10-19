#pragma once

#include <cmath>
#include <limits>
#include <ostream>

namespace rfmodel::math {

struct Complex {
    double real{0.0};
    double imag{0.0};

    constexpr Complex() = default;
    constexpr Complex(double real_part, double imag_part) : real(real_part), imag(imag_part) {}

    static Complex fromPolar(double magnitude, double phase_radians) {
        return Complex{magnitude * std::cos(phase_radians), magnitude * std::sin(phase_radians)};
    }

    constexpr Complex operator+() const { return *this; }
    constexpr Complex operator-() const { return Complex{-real, -imag}; }

    constexpr Complex& operator+=(const Complex& rhs) {
        real += rhs.real;
        imag += rhs.imag;
        return *this;
    }

    constexpr Complex& operator-=(const Complex& rhs) {
        real -= rhs.real;
        imag -= rhs.imag;
        return *this;
    }

    constexpr Complex& operator*=(const Complex& rhs) {
        double new_real = real * rhs.real - imag * rhs.imag;
        double new_imag = real * rhs.imag + imag * rhs.real;
        real = new_real;
        imag = new_imag;
        return *this;
    }

    constexpr Complex& operator/=(const Complex& rhs) {
        double denominator = rhs.real * rhs.real + rhs.imag * rhs.imag;
        if (denominator <= std::numeric_limits<double>::epsilon()) {
            real = 0.0;
            imag = 0.0;
            return *this;
        }
        double new_real = (real * rhs.real + imag * rhs.imag) / denominator;
        double new_imag = (imag * rhs.real - real * rhs.imag) / denominator;
        real = new_real;
        imag = new_imag;
        return *this;
    }

    constexpr Complex& operator*=(double scalar) {
        real *= scalar;
        imag *= scalar;
        return *this;
    }

    constexpr Complex& operator/=(double scalar) {
        real /= scalar;
        imag /= scalar;
        return *this;
    }

    constexpr Complex operator+(const Complex& rhs) const {
        return Complex{real + rhs.real, imag + rhs.imag};
    }

    constexpr Complex operator-(const Complex& rhs) const {
        return Complex{real - rhs.real, imag - rhs.imag};
    }

    constexpr Complex operator*(const Complex& rhs) const {
        return Complex{real * rhs.real - imag * rhs.imag, real * rhs.imag + imag * rhs.real};
    }

    constexpr Complex operator/(const Complex& rhs) const {
        double denominator = rhs.real * rhs.real + rhs.imag * rhs.imag;
        if (denominator <= std::numeric_limits<double>::epsilon()) {
            return Complex{};
        }
        return Complex{(real * rhs.real + imag * rhs.imag) / denominator,
                       (imag * rhs.real - real * rhs.imag) / denominator};
    }

    constexpr Complex operator*(double scalar) const { return Complex{real * scalar, imag * scalar}; }
    constexpr Complex operator/(double scalar) const { return Complex{real / scalar, imag / scalar}; }

    constexpr bool operator==(const Complex& rhs) const {
        return real == rhs.real && imag == rhs.imag;
    }

    constexpr bool operator!=(const Complex& rhs) const { return !(*this == rhs); }

    double magnitudeSquared() const { return real * real + imag * imag; }

    double magnitude() const { return std::sqrt(magnitudeSquared()); }

    double phase() const { return std::atan2(imag, real); }

    constexpr Complex conjugate() const { return Complex{real, -imag}; }

    Complex normalized() const {
        double mag = magnitude();
        if (mag == 0.0) {
            return Complex{};
        }
        return Complex{real / mag, imag / mag};
    }
};

inline Complex operator*(double scalar, const Complex& value) {
    return value * scalar;
}

inline std::ostream& operator<<(std::ostream& os, const Complex& value) {
    return os << '(' << value.real << ", " << value.imag << ')';
}

}  // namespace rfmodel::math
