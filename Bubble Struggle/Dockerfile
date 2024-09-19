# Use an official Ubuntu as a parent image
FROM ubuntu:latest

# Set the working directory
WORKDIR /app

# Update and install make and SFML
RUN apt-get update && \
    apt-get install -y build-essential libsfml-dev

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Build the project
RUN make clean && make

# Copy resources
RUN cp -r bubble-struggle/resources/ build

# Set the working directory to the build directory
WORKDIR /app/build

# Run the built executable
CMD ["./project_release"]
