# FiberLib – A User-Level Thread Library

## 1. Project Overview

FiberLib is a lightweight user-level thread library implemented in C for Linux.

It provides a mechanism to create and manage lightweight execution units called fibers.
Fibers share the same process address space but have their own execution contexts and stacks.

The project demonstrates important Operating System concepts such as:

- Concurrency
- User-level threads
- Context switching
- CPU scheduling
- Synchronization
- Mutual exclusion
- Process and resource management

---

## 2. Objectives

The main objectives of FiberLib are:

1. Create user-level fibers.
2. Allocate an independent stack for each fiber.
3. Perform context switching between fibers.
4. Implement cooperative scheduling.
5. Implement Round-Robin scheduling.
6. Implement Priority scheduling.
7. Implement fiber termination.
8. Implement fiber joining.
9. Provide mutex-based synchronization.
10. Provide automated testing.

---

## 3. Features

### Fiber Management

FiberLib supports:

- `fiber_init()`
- `fiber_create()`
- `fiber_yield()`
- `fiber_exit()`
- `fiber_join()`

### Scheduling

Two scheduling policies are supported:

#### Round-Robin

Each READY fiber gets an opportunity to execute in sequence.

```text
Fiber 0
   ↓
Fiber 1
   ↓
Fiber 2
   ↓
Fiber 0
   ↓
...
