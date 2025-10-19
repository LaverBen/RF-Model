#pragma once

#include <string>

namespace rfmodel::engine {

/**
 * @brief Base interface for entities that participate in an RF scene.
 *
 * Simulation objects represent transmitters, receivers, obstacles, or helper constructs
 * that contribute to propagation modeling during a scene update.
 */
class ISimulationObject {
public:
    virtual ~ISimulationObject() = default;

    /**
     * @brief Unique identifier used to reference the object within a scene.
     */
    [[nodiscard]] virtual std::string Id() const = 0;

    /**
     * @brief Human readable classification (e.g. "transmitter" or "wall").
     */
    [[nodiscard]] virtual std::string Type() const = 0;

    /**
     * @brief Applies configuration data encoded as JSON, YAML, or another serialized form.
     */
    virtual void ApplyConfiguration(const std::string &serializedConfiguration) = 0;

    /**
     * @brief Integrates the object's internal state forward by the provided time step.
     */
    virtual void Step(double deltaTimeSeconds) = 0;

    /**
     * @brief Resets transient state so the object can be reused in a fresh simulation run.
     */
    virtual void Reset() = 0;
};

} // namespace rfmodel::engine
