#pragma once

#include <string>

namespace rfmodel::engine {

class IReceiver;
class ITransmitter;
class IWall;

/**
 * @brief Captures propagation characteristics between transmitters and receivers.
 */
class IChannel {
public:
    virtual ~IChannel() = default;

    /**
     * @brief Returns a stable identifier for the channel model instance.
     */
    [[nodiscard]] virtual std::string Id() const = 0;

    /**
     * @brief Registers a wall or obstacle affecting channel propagation.
     */
    virtual void AddObstacle(const IWall &wall) = 0;

    /**
     * @brief Clears all currently registered obstacles.
     */
    virtual void ClearObstacles() = 0;

    /**
     * @brief Computes the path loss in decibels between the given endpoints.
     */
    [[nodiscard]] virtual double PathLoss(const ITransmitter &transmitter, const IReceiver &receiver) const = 0;

    /**
     * @brief Computes the propagation delay in seconds between the given endpoints.
     */
    [[nodiscard]] virtual double PropagationDelay(const ITransmitter &transmitter, const IReceiver &receiver) const = 0;

    /**
     * @brief Returns a complex fading coefficient magnitude squared for the given link.
     */
    [[nodiscard]] virtual double FadingPower(const ITransmitter &transmitter, const IReceiver &receiver) const = 0;
};

} // namespace rfmodel::engine

