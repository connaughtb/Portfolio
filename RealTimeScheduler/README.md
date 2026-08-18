# Partitioned Real-Time Task Scheduler

A C program that assigns periodic real-time tasks to CPU partitions, then verifies schedulability under fixed-priority scheduling.

Developed as part of a Carnegie Mellon real-time embedded systems team project.

## What it does

- Parses periodic tasks specified by name, execution time, and period
- Sorts tasks by decreasing utilization
- Supports first-fit decreasing (FFD), best-fit decreasing (BFD), and worst-fit decreasing (WFD) partitioning
- Rejects task sets that exceed per-CPU utilization capacity
- Recognizes harmonic task periods
- Applies iterative worst-case response-time analysis to non-harmonic partitions

## Build and run

```bash
make
make run
```

## Input format

```text
<cpu-count>,<FFD|BFD|WFD>
<task-count>
<task-name>,<execution-time>,<period>
```

Example:

```text
2,FFD
6
vision,9,20
logging,7,20
sensor,3,10
controller,3,12
telemetry,4,20
planning,3,20
```

## Example behavior

The example task set has a total utilization of 1.70, so it cannot fit on a
single CPU. With FFD, `vision`, `logging`, and `telemetry` fill the first
partition to 1.00, while `sensor`, `controller`, and `planning` are placed on
the second partition.

The periods are not all harmonic (`10`, `12`, and `20`), so the program uses
iterative fixed-priority response-time analysis to verify the partitions rather
than relying only on utilization. A successful run reports each CPU's assigned
tasks and aggregate utilization, for example:

```text
Schedulable task set using FFD:
CPU 0 (U=1.000): vision logging telemetry
CPU 1 (U=0.700): sensor controller planning
```

## Portfolio adaptation note

This is a standalone, adapted presentation of the scheduling and analysis approach used in the original project. Course infrastructure, Linux-kernel source, test harnesses, executables, and platform-specific runtime components are intentionally excluded.
