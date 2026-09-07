# TaskForge: Logistics Work Processing System (COS 214 Practical 4)

## Overview
TaskForge is an application for logistics and shipment management. The project make use of four design patterns: **Composite**, **Iterator**, **State**, and **Decorator**.

## Project Repository Structure
```text
├── docs/                     # UML diagrams
├── ConcreteDecorators.h      
├── ConcreteIterators.h       
├── ConcreteStates.h          
├── Delivery.h                
├── ShipmentComponent.h       
├── ShipmentDecorator.h       
├── ShipmentGroup.h           
├── ShipmentItem.h            
├── ShipmentIterator.h        
├── main.cpp                  # Application & demonstration scenarios
├── Makefile                  
├── Dockerfile                # Containerized development environment config
└── README.md                 # Project setup and command documentation
```

## Build and Execution Guide (Docker)

### 1. Build the Docker Image
```bash
docker build -t taskforge-app .
```

### 2. Run the Application Executable
```bash
docker run --rm taskforge-app ./taskforge
```

### 3. Run Valgrind Memory Investigation
```bash
docker run --rm taskforge-app valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

### 4. Debug with GDB
To launch GDB interactively inside the Docker environment:
```bash
docker run -it --rm taskforge-app gdb ./taskforge
```

## Local Build and Execution Guide (Host Machine)

### 1. Build the Executable
```bash
make
```

### 2. Run the Executable
```bash
./taskforge
```

### 3. Clean Build Artifacts
```bash
make clean
```
