# Philosophers

A multithreaded C simulation of the Dining Philosophers problem that demonstrates synchronization, shared-state safety, and timing-sensitive concurrency control.

## Overview

This project implements the classic Dining Philosophers concurrency challenge using POSIX threads and mutexes.

It was built to practice writing thread-safe systems code, coordinate shared resources (forks), and handle real-time constraints (eat/sleep/die timing) without race conditions or deadlocks. The simulation also includes robust argument validation and controlled shutdown when a philosopher dies or all required meals are completed.

**42 Berlin project:** `philosophers`  
**Score:** `100/100`

<!-- ## Demo / Screenshots

Add your visuals here:

![Terminal Demo Placeholder](docs/demo-terminal.gif)
![Simulation Output Placeholder](docs/screenshot-output.png)

Example run command:

```bash
./philo 5 800 200 200 7
```-->

## Tech Stack

- C
- POSIX Threads (`pthread`)
- POSIX Mutexes
- GNU Make
- Linux/Unix system APIs (`gettimeofday`, `usleep`)

## Architecture / Implementation

Core design is split into small modules with clear responsibilities:

- `main.c`: Program flow, thread creation/join, simulation lifecycle.
- `init.c`: Initialization of shared data, philosophers, forks, and mutexes.
- `monitor.c`: Central monitoring loop that detects death/completion and stops simulation.
- `utils.c`: Time handling, precise sleep loop, and synchronized logging.
- `check.c`: CLI argument parsing and input validation.
- `destroy.c` / `error_exit.c`: Cleanup paths for normal exit and error handling.

Key technical decisions:

- Per-fork mutexes protect fork ownership.
- Per-philosopher mutexes protect mutable philosopher state (`last_meal`, `finished`).
- A dedicated monitor checks starvation based on elapsed milliseconds.
- Fork acquisition order alternates by philosopher ID (odd/even) to reduce circular wait pressure.
- A print mutex serializes logs to keep output readable and race-free.

## Features

- Configurable simulation via CLI arguments.
- Optional meal target to stop when all philosophers have eaten enough.
- Starvation detection with millisecond precision.
- Synchronized, timestamped state output.
- Input validation with clear error messages.
- Graceful resource cleanup (threads, mutexes, allocated memory).

## Getting Started

### Prerequisites

- GCC or Clang
- `make`
- POSIX-compatible environment (Linux/macOS)

### Build

```bash
cd philo
make
```

### Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200 5
```

### Clean

```bash
make clean
make fclean
```

## Project Structure

```text
philosophers/
├── README.md
└── philo/
    ├── Makefile
    ├── includes/
    │   └── philo.h
    └── src/
        ├── main.c
        ├── init.c
        ├── monitor.c
        ├── utils.c
        ├── check.c
        ├── destroy.c
        └── error_exit.c
```

## Future Improvements

- Add CI workflow for build, sanitizers, and thread checks.
- Add structured test scenarios and expected-output checks.
- Improve scheduler fairness and reduce busy-wait sections.
- Add optional logging modes (minimal vs verbose).
- Include benchmark notes for larger philosopher counts.

## References & Testing Tools

- Dining Philosophers background: [Wikipedia - Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- Threading fundamentals: [CodeVault Lesson](https://code-vault.net/course/07hdekibo8:1603733520293/lesson/18ec1942c2da46840693efe9b51d86a8)
- Helpful walkthrough: [YouTube - Jamshidbek Ergashev](https://www.youtube.com/watch?v=UGQsvVKwe90)
- Helpful walkthrough: [YouTube - Oceano](https://www.youtube.com/watch?v=zOpzGHwJ3MU)
- Reference implementation: [TommyJD93/Philosophers](https://github.com/TommyJD93/Philosophers)
- Tester: [nesvoboda/socrates](https://github.com/nesvoboda/socrates)
- Tester: [MichelleJiam/LazyPhilosophersTester](https://github.com/MichelleJiam/LazyPhilosophersTester)
- Visualizer: [philosophers-visualizer](https://nafuka11.github.io/philosophers-visualizer/)

## What I Learned

- Designing and debugging multithreaded C applications.
- Preventing race conditions with fine-grained mutex usage.
- Coordinating shared resources under timing constraints.
- Building reliable startup/shutdown flows for concurrent systems.
- Structuring low-level projects into maintainable modules.
