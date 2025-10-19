# RF-Model

**RF-Model** is a simulation and visualization tool designed to explore how a receiver interacts with radio frequency (RF) waves in a 2D environment. The project aims to model RF propagation effects such as reflections, attenuation, and channel fading in a configurable virtual space.

> ⚠️ *Note: RF-Model is currently in early development. The initial focus is on setting up the simulation environment and building the core logic in C++ using Qt for the user interface.*

---

## 🎯 Project Overview

RF-Model is intended to help visualize how an RF receiver experiences incoming signals from different directions and under various propagation conditions.
The eventual goal is to allow users to:

* Move and position a **receiver** within a 2D simulation area.
* Create **transmitters** representing distant RF sources from the top, bottom, left, or right of the scene.
* Add **walls** or obstacles that can affect RF signals through reflection and attenuation.
* Adjust **material properties** of walls (e.g., reflectivity, thickness).
* Apply **channel effects**, such as fading or multipath interference, to simulate real-world conditions.
* Modify **RF properties** of the transmitted signals (e.g., frequency, phase, amplitude).
* Observe **receiver metrics** like average received power, phase characteristics, and more.

---

## 🧠 Motivation

Understanding RF propagation behavior can be complex — particularly when trying to visualize how environmental factors impact signal strength and phase.
RF-Model aims to provide a more **intuitive and interactive** way to explore these effects for educational, experimental, or research purposes.

---

## 🏗️ Current Status

| Component        | Status     | Notes                                                                  |
| ---------------- | ---------- | ---------------------------------------------------------------------- |
| Core C++ logic   | 🚧 Planned | Will handle wave modeling, reflection logic, and receiver calculations |
| Qt GUI           | 🚧 Planned | Will visualize transmitters, receivers, and walls                      |
| Channel modeling | 🚧 Planned | To simulate fading, multipath, and other real-world effects            |
| RF visualization | 🚧 Planned | Power maps, phase displays, and animation of wave interactions         |

---

## 🧩 Planned Architecture

* **Language:** C++
* **Framework:** Qt (for GUI and event handling)
* **Structure:**

  * `Core/` – signal and environment simulation logic
  * `UI/` – Qt-based visualization and user interaction
  * `Models/` – definitions for transmitters, receivers, and walls
  * `Channel/` – fading and channel effect models

---

## 📏 Units, Angles, and Coordinate Conventions

RF-Model standardizes on SI units, degree-based UI controls, radian-based internals, and a right-handed coordinate frame. See
[docs/UnitsAndConventions.md](docs/UnitsAndConventions.md) for the full reference covering axis directions, default RF
parameters, and angle conversion guidance.

---

## 🚀 Roadmap (High-Level)

1. **Environment Setup**

   * Initialize Qt project and basic GUI window
   * Create a base simulation canvas

2. **Receiver & Transmitter Models**

   * Implement movable receiver
   * Add basic directional transmitter sources

3. **Walls & Reflection Modeling**

   * Introduce walls with adjustable properties
   * Compute basic signal reflection/attenuation

4. **RF Properties & Channels**

   * Add configurable RF parameters
   * Simulate channel effects (fading, delay spread, etc.)

5. **Visualization Tools**

   * Display received power and phase metrics
   * Develop real-time visualization and logging

---

## 🧰 Development Setup

> Detailed build and dependency setup instructions will be added once the project has a working prototype.

For now, expect to use:

* **Qt 6+** for GUI and visualization
* **CMake** for building
* **C++17 or later** for core logic

### Build configuration options

The top-level `CMakeLists.txt` exposes a couple of toggles to help keep your local build lean:

| Option | Default | Description |
| ------ | ------- | ----------- |
| `RFMODEL_BUILD_TESTS` | `ON` | Enables the optional test suite (requires the `tests/` subdirectory). Disable with `-DRFMODEL_BUILD_TESTS=OFF` when you want a faster build or do not need the tests. |
| `RFMODEL_BUILD_BENCH` | `OFF` | Enables the optional benchmarks (requires the `bench/` subdirectory). Turn on with `-DRFMODEL_BUILD_BENCH=ON` when you intend to build the benchmarks. |

Both options automatically guard their respective subdirectories, so CMake will skip them when the directories are missing or the options are turned off.

---

## 🧪 Continuous Integration

Automated builds run on GitHub Actions (`.github/workflows/ci.yml`) across **Ubuntu**, **Windows**, and **macOS**. Each job installs Qt 6 via `install-qt-action`, configures CMake in Release mode with `RFMODEL_BUILD_TESTS=ON`, and then compiles the project. When tests are enabled, the workflow executes `ctest` so failures surface directly in the job log. The Linux leg also invokes `run-clang-tidy` against the generated `compile_commands.json` compilation database to keep static-analysis findings visible in CI. Every job publishes the resulting build output (binaries, bundles, and `compile_commands.json`) as artifacts, giving contributors easy access to build products or logs when diagnosing failures.

To verify changes locally before opening a pull request, mirror the CI pipeline:

1. Install Qt 6 and generate a build directory with `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DRFMODEL_BUILD_TESTS=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON`.
2. Build with `cmake --build build` (or `cmake --build build --config Release` on multi-config generators such as Visual Studio).
3. Run the test suite via `ctest --test-dir build --output-on-failure`.
4. Execute `run-clang-tidy -p build` to reproduce the static-analysis checks performed in CI.

---

### Logging

RF-Model configures Qt logging categories for both the UI and engine layers at startup. Control the minimum severity that is printed without rebuilding the application by using either of the following mechanisms:

* **Command line:** pass `--log-level <level>` when launching the binary, for example `./RF-Model --log-level debug`.
* **Environment variable:** set `RF_MODEL_LOG_LEVEL` before starting the process, for example `RF_MODEL_LOG_LEVEL=warning ./RF-Model`.

Valid levels are `debug`, `info`, `warning` (or `warn`), and `error` (alias `critical`). When no value is provided the logger defaults to `info` messages and above.

---

## 🧹 Code Style & Quality Tooling

The repository includes shared configuration files to ensure consistent formatting and linting across the codebase:

* `.clang-format` &ndash; C++ formatting rules derived from LLVM with Qt-friendly include ordering.
* `.clang-tidy` &ndash; Static-analysis checks tailored for modern C++ while automatically skipping Qt-generated sources such as `moc_`, `qrc_`, and `ui_` files.
* `.editorconfig` &ndash; Editor defaults for indentation, line endings, and whitespace across C++, CMake, and Markdown files.

### Formatting C++ code

Run `clang-format` locally before committing changes:

```bash
clang-format -i path/to/file.cpp path/to/header.h
```

Most IDEs (including Qt Creator and VS Code) can be configured to apply the project style automatically by pointing them to the repository root.

### Running clang-tidy checks

Invoke `clang-tidy` with the project configuration by passing the source file and build directory:

```bash
clang-tidy path/to/file.cpp \
  -p /path/to/build/directory
```

Ensure your build directory is generated with CMake (e.g., `cmake -S . -B build`). The tidy configuration filters out auto-generated Qt files, so you only need to run the tool on manually authored sources.

---