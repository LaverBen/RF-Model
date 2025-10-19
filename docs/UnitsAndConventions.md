# Units and Coordinate Conventions

This document captures the shared assumptions RF-Model makes about dimensional units, angle handling, and orientation. All new
code, UI, and documentation should adopt these defaults unless explicitly stated otherwise.

## Frequency, Distance, and Power Units

| Quantity   | Default Unit | Notes |
| ---------- | ------------ | ----- |
| Frequency  | **Hertz (Hz)** | Configuration values in the UI accept Hz, kHz, MHz, or GHz. Internally, numeric values are stored in Hz. |
| Wavelength | **Meters (m)** | Any derived distance (path length, antenna spacing) must be expressed in meters. |
| Position   | **Meters (m)** | Scene coordinates, obstacle dimensions, and offsets use meters. |
| Power      | **Watts (W)** | User input may also support dBm; convert to watts immediately when ingesting values. |
| Gain/Loss  | **Decibels (dB)** | Store gain/loss factors as dimensionless linear multipliers internally, but expose dB in the UI. |

*Provide conversion helpers whenever a module needs to expose alternative units (e.g., MHz or dBm) so that data at module
boundaries remains in the canonical units above.*

## Angular Conventions

* **User interface:** Present all angles (bearing, wall orientation, antenna rotation) in **degrees**. Accept input in degrees
  with clockwise-positive controls when applicable.
* **Internal representation:** Store all angles in **radians** with mathematical (counter-clockwise) positive direction.
* **Conversions:** Utilities converting between degrees and radians must preserve precision by using `double` and should live in a
  shared helper (e.g., `math/AngleUtils`).
* **Normalization:** Normalize angles internally to the range \([-\pi, \pi)\) unless a module documents an alternate interval.

## Right-Handed Coordinate System

RF-Model uses a right-handed coordinate frame aligned with the on-screen view.

* **Axes:**
  * **+X** points to the **right** of the canvas.
  * **+Y** points **up** on the canvas.
  * **+Z** emerges **out of the screen toward the viewer** (useful for cross-product reasoning even in 2D simulations).
* **Orientation:** The default "zero" heading (0° / 0 rad) aligns with the +X axis. Positive rotation follows the right-hand rule
  (counter-clockwise when looking down the +Z axis).
* **Polar coordinates:** When converting from polar to Cartesian, treat the angle as measured from +X toward +Y.

## Reference Values and Defaults

* Unless otherwise specified, transmitter center frequency defaults to **2.4 GHz** (2.4 × 10⁹ Hz).
* Default transmit power is **1 W** (0 dBW / 30 dBm) before path loss.
* Receiver and obstacle positions should be defined relative to the origin at the lower-left corner of the canvas.
* Document any deviations (alternate origins, axis flips, unit changes) in the module README or header comments.

Keeping these conventions explicit avoids hidden unit conversions and prevents misinterpretation when combining contributions from
different team members.
