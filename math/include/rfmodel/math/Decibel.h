#pragma once

#include <algorithm>
#include <cmath>
#include <limits>

namespace rfmodel::math {

inline double clampToPositive(double value) {
    const double minimum = std::numeric_limits<double>::min();
    return std::max(std::abs(value), minimum);
}

inline double amplitudeToDecibels(double amplitude) {
    return 20.0 * std::log10(clampToPositive(amplitude));
}

inline double decibelsToAmplitude(double decibels) {
    return std::pow(10.0, decibels / 20.0);
}

inline double powerToDecibels(double power) {
    return 10.0 * std::log10(clampToPositive(power));
}

inline double decibelsToPower(double decibels) {
    return std::pow(10.0, decibels / 10.0);
}

inline double ratioToDecibels(double ratio) {
    return powerToDecibels(ratio);
}

inline double decibelsToRatio(double decibels) {
    return decibelsToPower(decibels);
}

}  // namespace rfmodel::math
