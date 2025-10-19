#pragma once

#include <memory>
#include <string>
#include <vector>

namespace rfmodel::engine {

class ISimulationObject;

/**
 * @brief Container interface describing the contents and update mechanics of a scene.
 *
 * A scene bundles together the spatial layout, RF emitters, receivers, and other
 * simulation objects that interact during an engine step.
 */
class IScene {
public:
    virtual ~IScene() = default;

    /**
     * @brief Returns a human readable identifier for the scene.
     */
    [[nodiscard]] virtual std::string Name() const = 0;

    /**
     * @brief Loads scene-specific configuration data.
     *
     * Implementations may interpret the identifier as a path, asset key, or serialized
     * document depending on their storage model.
     */
    virtual void LoadConfiguration(const std::string &sourceIdentifier) = 0;

    /**
     * @brief Adds a simulation object to the scene.
     */
    virtual void AddObject(std::unique_ptr<ISimulationObject> object) = 0;

    /**
     * @brief Removes a simulation object by identifier, returning true when successful.
     */
    virtual bool RemoveObject(const std::string &objectId) = 0;

    /**
     * @brief Enumerates the objects currently hosted within the scene.
     */
    [[nodiscard]] virtual std::vector<ISimulationObject *> GetObjects() const = 0;

    /**
     * @brief Clears all objects and transient state from the scene.
     */
    virtual void Clear() = 0;

    /**
     * @brief Advances the scene-level simulation by the supplied time step in seconds.
     */
    virtual void Step(double deltaTimeSeconds) = 0;
};

} // namespace rfmodel::engine
