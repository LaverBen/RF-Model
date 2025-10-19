#pragma once

#include <cmath>
#include <limits>
#include <ostream>
#include <type_traits>

namespace rfmodel::math {

template <typename T>
struct Vec3 {
    static_assert(std::is_arithmetic<T>::value, "Vec3 requires an arithmetic type");

    T x{0};
    T y{0};
    T z{0};

    constexpr Vec3() = default;
    constexpr Vec3(T x_value, T y_value, T z_value)
        : x(x_value), y(y_value), z(z_value) {}

    template <typename U>
    explicit constexpr Vec3(const Vec3<U>& other)
        : x(static_cast<T>(other.x)),
          y(static_cast<T>(other.y)),
          z(static_cast<T>(other.z)) {}

    static constexpr Vec3 zero() { return Vec3{}; }

    constexpr Vec3 operator+() const { return *this; }
    constexpr Vec3 operator-() const { return Vec3{-x, -y, -z}; }

    constexpr Vec3& operator+=(const Vec3& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    constexpr Vec3& operator-=(const Vec3& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    constexpr Vec3& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    constexpr Vec3& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    constexpr Vec3 operator+(const Vec3& rhs) const {
        return Vec3{x + rhs.x, y + rhs.y, z + rhs.z};
    }

    constexpr Vec3 operator-(const Vec3& rhs) const {
        return Vec3{x - rhs.x, y - rhs.y, z - rhs.z};
    }

    constexpr Vec3 operator*(T scalar) const {
        return Vec3{x * scalar, y * scalar, z * scalar};
    }

    constexpr Vec3 operator/(T scalar) const {
        return Vec3{x / scalar, y / scalar, z / scalar};
    }

    constexpr bool operator==(const Vec3& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    constexpr bool operator!=(const Vec3& rhs) const { return !(*this == rhs); }

    static constexpr T dot(const Vec3& lhs, const Vec3& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    constexpr T dot(const Vec3& rhs) const { return dot(*this, rhs); }

    static constexpr Vec3 cross(const Vec3& lhs, const Vec3& rhs) {
        return Vec3{
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x,
        };
    }

    constexpr Vec3 cross(const Vec3& rhs) const { return cross(*this, rhs); }

    constexpr T lengthSquared() const { return dot(*this, *this); }

    double length() const {
        using std::sqrt;
        return sqrt(static_cast<double>(lengthSquared()));
    }

    Vec3 normalized() const {
        double len_sq = static_cast<double>(lengthSquared());
        if (len_sq <= std::numeric_limits<double>::epsilon()) {
            return Vec3{};
        }
        double inv_len = 1.0 / std::sqrt(len_sq);
        return Vec3{static_cast<T>(x * inv_len), static_cast<T>(y * inv_len), static_cast<T>(z * inv_len)};
    }
};

template <typename T>
constexpr Vec3<T> operator*(T scalar, const Vec3<T>& value) {
    return value * scalar;
}

template <typename T>
inline std::ostream& operator<<(std::ostream& os, const Vec3<T>& value) {
    return os << '(' << value.x << ", " << value.y << ", " << value.z << ')';
}

}  // namespace rfmodel::math
