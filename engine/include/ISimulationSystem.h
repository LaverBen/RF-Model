#pragma once

#include <string>

namespace rfmodel::engine {

class IScene;

/**
 * @brief Interface for subsystems that perform domain-specific simulation work.
 *
 * Systems encapsulate algorithms such as RF propagation, collision handling, or metrics
 * collection and are orchestrated by the engine during each simulation step.
 */
class ISimulationSystem {
public:
    virtual ~ISimulationSystem() = default;

    /**
     * @brief Descriptive name used for logging or diagnostics.
     */
    [[nodiscard]] virtual std::string Name() const = 0;

    /**
     * @brief Called when the system is attached to a scene to perform any required setup.
     */
    virtual void Initialize(IScene &scene) = 0;

    /**
     * @brief Advances the system using the active scene as context.
     */
    virtual void Step(IScene &scene, double deltaTimeSeconds) = 0;

    /**
     * @brief Signals that configuration inputs have changed and cached data should refresh.
     */
    virtual void OnConfigurationReload(const std::string &sourceIdentifier) = 0;
};

} // namespace rfmodel::engine
