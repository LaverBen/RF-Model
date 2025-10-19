#pragma once

#include <memory>
#include <string>
#include <vector>

namespace rfmodel::engine {

class IScene;

/**
 * @brief Core interface describing the RF simulation engine lifecycle.
 *
 * Implementations are responsible for loading configuration data, managing scenes,
 * and advancing the global simulation state in response to the host application's
 * timing signals.
 */
class IRfEngine {
public:
    virtual ~IRfEngine() = default;

    /**
     * @brief Loads engine-level configuration data from a file or serialized payload.
     *
     * The provided identifier may reference a filesystem path, resource handle, or any
     * other implementation-defined source.
     */
    virtual void LoadConfiguration(const std::string &sourceIdentifier) = 0;

    /**
     * @brief Registers a scene instance that can be activated later.
     *
     * Ownership of the scene reference is shared so the caller can retain access while
     * the engine manages activation and updates.
     */
    virtual void RegisterScene(std::shared_ptr<IScene> scene) = 0;

    /**
     * @brief Selects the active scene used when stepping the simulation.
     */
    virtual void SetActiveScene(const std::shared_ptr<IScene> &scene) = 0;

    /**
     * @brief Returns the currently active scene, or nullptr when no scene is active.
     */
    [[nodiscard]] virtual std::shared_ptr<IScene> GetActiveScene() const = 0;

    /**
     * @brief Provides visibility into all scenes that have been registered with the engine.
     */
    [[nodiscard]] virtual std::vector<std::shared_ptr<IScene>> GetRegisteredScenes() const = 0;

    /**
     * @brief Advances the simulation by the supplied time step in seconds.
     */
    virtual void StepSimulation(double deltaTimeSeconds) = 0;

    /**
     * @brief Resets the engine to a known baseline state, clearing transient data.
     */
    virtual void Reset() = 0;
};

} // namespace rfmodel::engine
