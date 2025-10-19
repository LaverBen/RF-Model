#pragma once

#include <array>
#include <string>

namespace rfmodel::engine {

/**
 * @brief Represents a simulation receiver capable of capturing RF energy.
 */
class IReceiver {
public:
    virtual ~IReceiver() = default;

    /**
     * @brief Returns a stable identifier for the receiver instance.
     */
    [[nodiscard]] virtual std::string Id() const = 0;

    /**
     * @brief Provides the world-space position of the receiver in meters.
     */
    [[nodiscard]] virtual std::array<double, 3> Position() const = 0;

    /**
     * @brief Updates the world-space position of the receiver in meters.
     */
    virtual void SetPosition(const std::array<double, 3> &positionMeters) = 0;

    /**
     * @brief Provides the receiver orientation as roll/pitch/yaw in radians.
     */
    [[nodiscard]] virtual std::array<double, 3> Orientation() const = 0;

    /**
     * @brief Updates the receiver orientation using roll/pitch/yaw in radians.
     */
    virtual void SetOrientation(const std::array<double, 3> &orientationRadians) = 0;

    /**
     * @brief Returns the effective isotropic sensitivity of the receiver in dBm.
     */
    [[nodiscard]] virtual double Sensitivity() const = 0;

    /**
     * @brief Adjusts the effective isotropic sensitivity of the receiver in dBm.
     */
    virtual void SetSensitivity(double sensitivityDbm) = 0;
};

} // namespace rfmodel::engine

