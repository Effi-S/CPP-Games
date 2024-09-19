    # Use the official Ubuntu base image
FROM ubuntu:latest

# Set the working directory
WORKDIR /app

# Install make, build-essential, and SFML
RUN apt-get update && \
    apt-get install -y build-essential libsfml-dev && \
    apt-get clean

# Copy the project files to the container
COPY . /app

# Run make to build the project
RUN make clean && make

# Copy resources to the build directory
RUN cp bomberman/*.txt  build
RUN cp  -r bomberman/menu_buttons/  bomberman/toolbar_buttons/ bomberman/images/  build

# Set the working directory to the build directory
WORKDIR /app/build

# Define the command to run the built executable
CMD ["./project_release"]
