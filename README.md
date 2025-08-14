# Concurrent Philosophers

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/aminekell/concurrent-philosophers)
[![C Standard](https://img.shields.io/badge/C-C99-blue.svg)](https://en.wikipedia.org/wiki/C99)
[![POSIX](https://img.shields.io/badge/POSIX-compliant-orange.svg)](https://pubs.opengroup.org/onlinepubs/9699919799/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

> A high-performance, thread-safe implementation of Dijkstra's classic Dining Philosophers problem, demonstrating advanced concurrency control and synchronization techniques.

## 🎯 Overview

This project implements a sophisticated solution to the **Dining Philosophers Problem**—a fundamental computer science challenge in concurrent programming. The solution addresses critical issues including deadlock prevention, race condition elimination, and resource starvation through advanced mutex synchronization and adaptive algorithms.

### Key Features

- 🔒 **Deadlock-Free Architecture**: Implements asymmetric fork acquisition to prevent circular wait conditions
- ⚡ **Adaptive Timing System**: Dynamic sleep intervals optimized for performance and precision
- 🛡️ **Thread-Safe Operations**: Comprehensive mutex protection with zero race conditions
- 📊 **Real-Time Monitoring**: Sub-10ms death detection with precise timestamp logging
- 🧠 **Memory Safe**: Zero memory leaks with comprehensive resource cleanup
- 🎯 **High Performance**: Optimized system calls and minimal CPU overhead

## 📋 Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Architecture](#architecture)
- [Algorithm Details](#algorithm-details)
- [Performance](#performance)
- [Testing](#testing)
- [Contributing](#contributing)
- [Technical Specifications](#technical-specifications)

## 🚀 Installation

### Prerequisites

- **Compiler**: GCC 4.8+ or Clang 3.4+
- **OS**: UNIX-like system (Linux, macOS, BSD)
- **Standards**: POSIX.1-2008 compliant system
- **Make**: GNU Make 3.81+

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/aminekell/concurrent-philosophers.git
cd concurrent-philosophers

# Compile with optimizations
make

# Install (optional)
sudo make install

# Clean build artifacts
make clean
```

### Compilation Flags

The project compiles with strict standards and comprehensive warnings:
```bash
gcc -Wall -Wextra -Werror -std=c99 -O2 -pthread
```

## 💻 Usage

### Basic Syntax

```bash
./philo number_of_philosophers die_time eat_time time_to_sleep [meal_number]
```

### Parameters

| Parameter | Type | Description | Range |
|-----------|------|-------------|-------|
| `number_of_philosophers` | int | Number of philosophers and forks | 1-200 |
| `die_time` | int | Maximum time (ms) without eating before death | ≥60 |
| `eat_time` | int | Duration (ms) of eating phase | ≥60 |
| `time_to_sleep` | int | Duration (ms) of sleeping phase | ≥60 |
| `meal_number` | int | Optional: meals required per philosopher | ≥1 |

### Example Usage

```bash
# Classic 5 philosophers with 800ms death timer
./philo 5 800 200 200

# Stress test: 3 philosophers, tight timing
./philo 3 310 100 100

# Meal limit: Stop after each philosopher eats 7 times
./philo 4 410 200 200 7

# Edge case: Single philosopher
./philo 1 800 200 200
```

### Output Format

```
timestamp_ms philosopher_id action
```

**Actions:**
- `has taken a fork` - Philosopher acquires a fork
- `is eating` - Philosopher begins eating
- `is sleeping` - Philosopher begins sleeping  
- `is thinking` - Philosopher begins thinking
- `died` - Philosopher dies from starvation

## 🏗️ Architecture

### System Design

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Philosopher   │    │   Fork Mutex    │    │  Monitor Thread │
│     Thread      │────│  Synchronization│────│   Death Watch   │
│                 │    │                 │    │                 │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         └───────────────────────┼───────────────────────┘
                                 │
                    ┌─────────────────┐
                    │  Shared State   │
                    │   (Protected)   │
                    └─────────────────┘
```

### Core Components

#### 1. Philosopher Structure
```c
typedef struct s_philo {
    int             id;              // Philosopher identifier
    long            meals;           // Meal counter
    long            last_meal;       // Timestamp of last meal
    pthread_t       thread;          // Thread handle
    pthread_mutex_t fork;            // Fork mutex
    pthread_mutex_t meal_mutex;      // Meal data protection
    pthread_mutex_t save_eat;        // Eating state protection
    int             is_eating;       // Current eating status
    struct s_philo  *next;          // Circular list pointer
    struct s_philo  *prev;          // Circular list pointer
    t_data          *info;
