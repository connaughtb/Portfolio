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
3
sensor,1,5
control,1,10
logging,2,20
```

## Portfolio adaptation note

This is a standalone, adapted presentation of the scheduling and analysis approach used in the original project. Course infrastructure, Linux-kernel source, test harnesses, executables, and platform-specific runtime components are intentionally excluded.
