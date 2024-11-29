# Use an official GCC image as a parent image
FROM gcc:11

# Set the working directory in the container
WORKDIR /app

# Copy only necessary files into the container
COPY Makefile .
COPY src/ src/
COPY include/ include/
COPY tests/ tests/

# Install any required dependencies (optional step)
RUN apt-get update && apt-get install -y \
    make \
    && rm -rf /var/lib/apt/lists/*

# Build the project using the Makefile
RUN make

# Set the default command to run the test binary
CMD ["./test_atm"]
