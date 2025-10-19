#pragma once

#include <array>
#include <string>

namespace rfmodel::engine {

/**
 * @brief Describes an RF transmitter capable of emitting energy into the scene.
 */
class ITransmitter {
public:
    virtual ~ITransmitter() = default;

    /**
     * @brief Returns a stable identifier for the transmitter instance.
     */
    [[nodiscard]] virtual std::string Id() const = 0;

    /**
     * @brief Provides the world-space position of the transmitter in meters.
     */
    [[nodiscard]] virtual std::array<double, 3> Position() const = 0;

    /**
     * @brief Updates the world-space position of the transmitter in meters.
     */
    virtual void SetPosition(const std::array<double, 3> &positionMeters) = 0;

    /**
     * @brief Provides the transmitter orientation as roll/pitch/yaw in radians.
     */
    [[nodiscard]] virtual std::array<double, 3> Orientation() const = 0;

    /**
     * @brief Updates the transmitter orientation using roll/pitch/yaw in radians.
     */
    virtual void SetOrientation(const std::array<double, 3> &orientationRadians) = 0;

    /**
     * @brief Returns the carrier frequency emitted by the transmitter in hertz.
     */
    [[nodiscard]] virtual double CarrierFrequency() const = 0;

    /**
     * @brief Adjusts the carrier frequency emitted by the transmitter in hertz.
     */
    virtual void SetCarrierFrequency(double frequencyHz) = 0;

    /**
     * @brief Returns the effective isotropic radiated power of the transmitter in dBm.
     */
    [[nodiscard]] virtual double Power() const = 0;

    /**
     * @brief Adjusts the effective isotropic radiated power of the transmitter in dBm.
     */
    virtual void SetPower(double powerDbm) = 0;
};

} // namespace rfmodel::engine

