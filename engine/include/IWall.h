#pragma once

#include <array>
#include <string>

namespace rfmodel::engine {

/**
 * @brief Defines boundary characteristics impacting RF propagation.
 */
class IWall {
public:
    virtual ~IWall() = default;

    /**
     * @brief Returns a stable identifier for the wall segment.
     */
    [[nodiscard]] virtual std::string Id() const = 0;

    /**
     * @brief Provides the centroid position of the wall in meters.
     */
    [[nodiscard]] virtual std::array<double, 3> Position() const = 0;

    /**
     * @brief Returns the outward-facing normal vector of the wall.
     */
    [[nodiscard]] virtual std::array<double, 3> Normal() const = 0;

    /**
     * @brief Returns the wall thickness in meters.
     */
    [[nodiscard]] virtual double Thickness() const = 0;

    /**
     * @brief Returns the relative permittivity of the wall material.
     */
    [[nodiscard]] virtual double RelativePermittivity() const = 0;

    /**
     * @brief Returns the conductivity of the wall material in siemens per meter.
     */
    [[nodiscard]] virtual double Conductivity() const = 0;
};

} // namespace rfmodel::engine

