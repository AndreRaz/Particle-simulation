# Electrostatic Particle Simulation

A real-time 2D electrostatic particle simulation written in **C** using **Raylib**. Watch 50 charged particles interact through Coulomb's law — complete with live electric field visualization and a speed histogram.

---

## Demo

<video src="https://raw.githubusercontent.com/AndreRaz/Particle-simulation/main/video/simulation.webm" autoplay loop muted playsinline width="500"></video>

---

## Features

- **N-body electrostatic simulation** — O(n²) pairwise Coulomb force calculation per frame
- **Electric field visualization** — superposition of all particle fields rendered as a vector grid
- **Speed histogram** — real-time distribution of particle speeds (bottom left)
- **Newton's 3rd law** — equal and opposite force accumulation per pair
- **Elastic boundary collisions** — particles bounce off all four walls
- **60 FPS** target with frame-time integration

---

## Physics

### Coulomb's Law

The force between two charged particles is:

```
F = ke * q1 * q2 / r²
```

Where:
- `ke = 8000.0` — scaled Coulomb constant
- `q1`, `q2 ∈ {-1, +1}` — particle charges (randomly assigned)
- `r` — distance between particles

Same-sign charges **repel**, opposite-sign charges **attract**.

### Electric Field

The field at each grid point is the vector superposition of all particle contributions:

```
E = ke * q / r²   (direction: away from positive, toward negative)
```

### Integration

Each frame uses **semi-implicit Euler** integration:

```
a = F / m
v += a * dt
x += v * dt
```

Where `dt = GetFrameTime()` — the real elapsed time since the last frame.

### Particles

| Property | Value |
|----------|-------|
| Count | 50 |
| Mass | 1.0 |
| Charge | ±1 (random) |
| Radius | 5 px |
| Initial position | Random [50, 450] |
| Initial velocity | Random [-100, 100] |

---

## Requirements

- **GCC** (or any C99-compatible compiler)
- **Raylib** — [https://www.raylib.com](https://www.raylib.com)
- **Linux** with a display server (X11 or Wayland)
- `make`

---

## Installation

### 1. Install Raylib

**Ubuntu / Debian:**
```bash
sudo apt update
sudo apt install libraylib-dev
```

**Arch Linux:**
```bash
sudo pacman -S raylib
```

**Fedora / RHEL:**
```bash
sudo dnf install raylib-devel
```

**From source (any distro):**
```bash
git clone https://github.com/raysan5/raylib.git
cd raylib/src
make PLATFORM=PLATFORM_DESKTOP
sudo make install
```

---

### 2. Clone this repository

```bash
git clone https://github.com/YOUR_USERNAME/Particulas.git
cd Particulas
```

---

### 3. Build

```bash
make
```

---

### 4. Run

```bash
./simulation
```

---

### Clean build artifacts

```bash
make clean
```

---

## Project Structure

```
Particulas/
├── particles.h        # Particle struct definition and function prototypes
├── particles.c        # Physics simulation, rendering, and main loop
├── Makefile           # Build configuration
├── video/
│   └── simulation.webm  # Recorded simulation output
└── README.md
```

---

## How it Works

```
Each frame:
  1. apply_force()   → compute pairwise Coulomb forces (O(n²))
  2. update_particles() → integrate acceleration → velocity → position
  3. draw_field()    → render electric field vectors on a 25px grid
  4. draw_particles() → render circles (red = +, blue = -)
  5. draw_hist()     → render speed distribution histogram
```

---

## License

MIT — do whatever you want with it.
