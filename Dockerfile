FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install required build tools, debuggers, and utilities
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    gdb \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# Set working directory inside the container
WORKDIR /usr/src/taskforge

# Copy project files into the container
COPY . .

# Build the project executable
RUN make clean && make

# Default command to run the application
CMD ["./taskforge"]