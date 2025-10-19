#include <cassert>
#include <cmath>

#include "rfmodel/math/Complex.h"
#include "rfmodel/math/Decibel.h"
#include "rfmodel/math/Vec2.h"
#include "rfmodel/math/Vec3.h"

namespace {

constexpr double kTolerance = 1e-9;

void testVec2() {
    using Vec2d = rfmodel::math::Vec2<double>;

    constexpr Vec2d a{1.0, 2.0};
    constexpr Vec2d b{3.0, -4.0};

    constexpr auto sum = a + b;
    static_assert(sum.x == 4.0 && sum.y == -2.0, "Vec2 addition failed");

    constexpr auto diff = a - b;
    static_assert(diff.x == -2.0 && diff.y == 6.0, "Vec2 subtraction failed");

    constexpr auto scaled = a * 2.0;
    static_assert(scaled.x == 2.0 && scaled.y == 4.0, "Vec2 scaling failed");

    constexpr double dot = Vec2d::dot(a, b);
    static_assert(dot == -5.0, "Vec2 dot product failed");

    Vec2d normalized = a.normalized();
    double length = normalized.length();
    assert(std::abs(length - 1.0) < kTolerance);
}

void testVec3() {
    using Vec3d = rfmodel::math::Vec3<double>;

    constexpr Vec3d a{1.0, 0.0, 0.0};
    constexpr Vec3d b{0.0, 1.0, 0.0};

    constexpr auto cross = Vec3d::cross(a, b);
    static_assert(cross.x == 0.0 && cross.y == 0.0 && cross.z == 1.0, "Vec3 cross product failed");

    constexpr double dot = Vec3d::dot(a, b);
    static_assert(dot == 0.0, "Vec3 dot product orthogonality failed");

    Vec3d normalized = Vec3d{2.0, -2.0, 1.0}.normalized();
    double length = normalized.length();
    assert(std::abs(length - 1.0) < kTolerance);
}

void testComplex() {
    using rfmodel::math::Complex;

    Complex a{1.0, 2.0};
    Complex b{3.0, -4.0};

    Complex sum = a + b;
    assert(sum.real == 4.0);
    assert(sum.imag == -2.0);

    Complex diff = a - b;
    assert(diff.real == -2.0);
    assert(diff.imag == 6.0);

    Complex product = a * b;
    assert(std::abs(product.real - 11.0) < kTolerance);
    assert(std::abs(product.imag - 2.0) < kTolerance);

    Complex quotient = a / b;
    assert(std::abs(quotient.real - (-0.2)) < kTolerance);
    assert(std::abs(quotient.imag - (0.4)) < kTolerance);

    Complex polar = Complex::fromPolar(2.0, std::atan2(1.0, 1.0));
    assert(std::abs(polar.magnitude() - 2.0) < kTolerance);
}

void testDecibelConversions() {
    using namespace rfmodel::math;

    double amplitude = 2.0;
    double db = amplitudeToDecibels(amplitude);
    double recovered_amplitude = decibelsToAmplitude(db);
    assert(std::abs(recovered_amplitude - amplitude) < kTolerance);

    double power = 5.0;
    double power_db = powerToDecibels(power);
    double recovered_power = decibelsToPower(power_db);
    assert(std::abs(recovered_power - power) < kTolerance);
}

}  // namespace

int main() {
    testVec2();
    testVec3();
    testComplex();
    testDecibelConversions();
    return 0;
}
