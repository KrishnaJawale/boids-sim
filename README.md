# Boids Sim

2D boids flocking simulation in C++ with raylib. Each agent follows basic local steering rules, which produces flocking behavior. Includes a live tuning panel to adjust simulation parameters at runtime.

## Features

- **Flocking rules** - separation, alignment, cohesion (Reynolds boids)
- **500 agents** - using naive O(n²) neighbor search for now
- **Edge avoidance** - boids steer away from screen boundaries
- **Speed limits** - configurable min/max speed clamping
- **Live tuning UI** - sliders for all relevant simulation parameters

## Tunable parameters

| Parameter | Description |
|-----------|-------------|
| Max speed | Upper bound on boid velocity |
| Min speed | Lower bound on boid velocity |
| Perception | Radius for detecting neighbors |
| Separation | Radius for personal space avoidance |
| Avoid | Weight of the separation force |
| Alignment | Weight of the alignment force |
| Cohesion | Weight of the cohesion force |
| Edge margin | Distance from screen edge where turning begins |
| Turn factor | Strength of edge avoidance steering |

## Project structure

```
src/
  main.cpp      - simulation loop, flocking logic, rendering
  Boid.h        - boid state (position, velocity, acceleration)
  Vec2.h        - 2D vector math
  SimParams.h   - tunable simulation parameters
  Ui.h / Ui.cpp - live tuning panel with sliders
```

## Requirements

- C++17 compiler
- [CMake](https://cmake.org/) 3.14+
- [raylib](https://www.raylib.com/)

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/boids-sim
```
