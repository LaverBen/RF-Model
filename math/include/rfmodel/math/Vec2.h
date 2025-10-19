#pragma once

#include <cmath>
#include <limits>
#include <ostream>
#include <type_traits>

namespace rfmodel::math {

template <typename T>
struct Vec2 {
    static_assert(std::is_arithmetic<T>::value, "Vec2 requires an arithmetic type");

    T x{0};
    T y{0};

    constexpr Vec2() = default;
    constexpr Vec2(T x_value, T y_value) : x(x_value), y(y_value) {}

    template <typename U>
    explicit constexpr Vec2(const Vec2<U>& other)
        : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

    static constexpr Vec2 zero() { return Vec2{}; }

    constexpr Vec2 operator+() const { return *this; }
    constexpr Vec2 operator-() const { return Vec2{-x, -y}; }

    constexpr Vec2& operator+=(const Vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    constexpr Vec2& operator-=(const Vec2& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    constexpr Vec2& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr Vec2& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr Vec2 operator+(const Vec2& rhs) const { return Vec2{x + rhs.x, y + rhs.y}; }
    constexpr Vec2 operator-(const Vec2& rhs) const { return Vec2{x - rhs.x, y - rhs.y}; }

    constexpr Vec2 operator*(T scalar) const { return Vec2{x * scalar, y * scalar}; }
    constexpr Vec2 operator/(T scalar) const { return Vec2{x / scalar, y / scalar}; }

    constexpr bool operator==(const Vec2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    constexpr bool operator!=(const Vec2& rhs) const { return !(*this == rhs); }

    static constexpr T dot(const Vec2& lhs, const Vec2& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    constexpr T dot(const Vec2& rhs) const { return dot(*this, rhs); }

    constexpr T lengthSquared() const { return dot(*this, *this); }

    double length() const {
        using std::sqrt;
        return sqrt(static_cast<double>(lengthSquared()));
    }

    Vec2 normalized() const {
        double len_sq = static_cast<double>(lengthSquared());
        if (len_sq <= std::numeric_limits<double>::epsilon()) {
            return Vec2{};
        }
        double inv_len = 1.0 / std::sqrt(len_sq);
        return Vec2{static_cast<T>(x * inv_len), static_cast<T>(y * inv_len)};
    }
};

template <typename T>
constexpr Vec2<T> operator*(T scalar, const Vec2<T>& value) {
    return value * scalar;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec2<T>& value) {
    return os << '(' << value.x << ", " << value.y << ')';
}

}  // namespace rfmodel::math
