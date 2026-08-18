# Belle Connaught – Software & Embedded Systems Portfolio

This repository highlights selected projects from my work at Carnegie Mellon University and personal work. I earned a B.S. in Electrical & Computer Engineering in May 2025 and an M.S. in Electrical & Computer Engineering in May 2026.

Each project includes focused source code and documentation intended to demonstrate the underlying engineering work. Course-provided infrastructure, external dependencies, and full assignment repositories are omitted where appropriate.  

---

## Projects
### [Embedded Navigation Stack](EmbeddedNavigation/README.md)
*C++, Eigen, CMake, Extended Kalman Filter, LQR, A* path planning*

- Built a simulated autonomous-navigation pipeline for a differential-drive robot operating in occupancy-grid environments
- Implemented and tuned the discrete-time LQR trajectory controller and Extended Kalman Filter for noisy pose estimation
- Evaluated closed-loop tracking under injected process and measurement noise; EKF position-estimation error remained below approximately 0.05 m
- Developed with Ethan Crook, who implemented the occupancy-grid processing, obstacle inflation, and A* path-planning components

### [Partitioned Real-Time Task Scheduler](RealTimeScheduler/README.md)
*C, real-time scheduling, bin packing, response-time analysis*

- Allocates up to 10,000 periodic tasks across up to 100 CPU partitions using FFD, BFD, or WFD
- Validates utilization and applies harmonic-period checks plus fixed-priority response-time analysis
- Reports per-CPU assignments for schedulable task sets

### [Embedded FreeRTOS Motor Controller](MotorController/README.md)
*STM32, C, FreeRTOS, PID control, PWM, quadrature encoder*

- Built a closed-loop DC motor position controller using quadrature-encoder feedback
- Implemented PID control, PWM-based motor-speed control, direction control, and braking behavior
- Achieved under 2% steady-state error during testing

### [DrumLite — Portable Electronic Drum System](DrumLite/README.md)
*ESP32, MPU-6050, Bluetooth, OpenCV, Python/C++*

- Built an interactive virtual drumming system using IMU-based hit detection and camera-based stick tracking
- Achieved approximately 52 ms end-to-end latency for real-time drum-hit detection
- Developed a Flask-based interface for the system

### [Fault-Tolerant Distributed Compute System](DistributedMiner/README.md)
*Go, UDP networking, goroutines, concurrency, fault tolerance*

- Implemented client-server job distribution and concurrent worker coordination
- Built reliable communication and failure-handling behavior on top of a custom Live Sequence Protocol implementation
- Applied distributed-systems concepts including timeouts, retries, and fault recovery

---

## Technical Skills

- **Programming Languages:** Python, C, C++, Go, Rust, Java
- **Embedded Systems:** FreeRTOS, STM32/ESP32, real-time scheduling, device drivers, interrupts, Bluetooth, Linux
- **Distributed Systems:** Concurrency, goroutines, client-server systems, fault tolerance, UDP/TCP networking
- **Computer Vision & ML:** OpenCV, PyTorch, TensorFlow, model training pipelines
- **Libraries & Build Tools:** Eigen, CMake, Docker
- **Tools:** Git

---

## Contact

- Email: [connaughtb@gmail.com](mailto:connaughtb@gmail.com)
- LinkedIn: [linkedin.com/in/belle-connaught](https://linkedin.com/in/belle-connaught)
- GitHub: [github.com/connaughtb](https://github.com/connaughtb)
 
