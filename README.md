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