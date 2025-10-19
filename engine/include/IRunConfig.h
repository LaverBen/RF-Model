#pragma once

#include <chrono>
#include <cstddef>
#include <string>

namespace rfmodel::engine {

/**
 * @brief Provides metadata and timing for a simulation run.
 */
class IRunConfig {
public:
    using Duration = std::chrono::duration<double>;

    virtual ~IRunConfig() = default;

    /**
     * @brief Returns a human readable name for the run configuration.
     */
    [[nodiscard]] virtual std::string Name() const = 0;

    /**
     * @brief Returns the fixed simulation time step.
     */
    [[nodiscard]] virtual Duration TimeStep() const = 0;

    /**
     * @brief Adjusts the fixed simulation time step.
     */
    virtual void SetTimeStep(Duration timeStep) = 0;

    /**
     * @brief Returns the total simulated duration desired.
     */
    [[nodiscard]] virtual Duration TotalDuration() const = 0;

    /**
     * @brief Adjusts the total simulated duration.
     */
    virtual void SetTotalDuration(Duration duration) = 0;

    /**
     * @brief Returns an upper bound on discrete simulation steps.
     */
    [[nodiscard]] virtual std::size_t MaxIterations() const = 0;

    /**
     * @brief Sets an upper bound on discrete simulation steps.
     */
    virtual void SetMaxIterations(std::size_t iterations) = 0;
};

} // namespace rfmodel::engine

