# Use an official Ubuntu as a parent image
FROM ubuntu:latest

# Set the working directory inside the container
WORKDIR /app

# Install dependencies
RUN apt-get update && \
    apt-get install -y build-essential libsfml-dev libgtk-3-dev

# Copy the source code into the container
COPY . /app

# Build the project
RUN make clean && make

# Copy resources
RUN cp -r 6_colors/images build/

# Set the working directory to the build directory
WORKDIR /app/build

# Define the command to run the executable
CMD ["./project_release"]
