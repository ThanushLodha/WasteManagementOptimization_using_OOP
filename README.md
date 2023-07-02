## Waste Collection Point Optimization

This repository contains a C++ implementation for optimizing waste collection routes using a vehicle fleet. The code calculates optimized routes for waste collection points and assigns them to available vehicles based on their capacities.

### Features

- Calculation of optimized routes based on the distance between waste collection points using the nearest neighbor algorithm.
- Assignment of waste collection points to vehicles based on their capacities, aiming to maximize the utilization of each vehicle.
- Support for reading input data from a file in a specified format.
- Function overloading for calculating distances between generic points and waste collection points.

### Usage

1. Clone the repository and navigate to the project directory.
2. Compile the code using a C++ compiler (e.g., g++).
3. Prepare an input file with the following format:
   - The first line should contain the number of waste collection points.
   - Each subsequent line should contain the information for a waste collection point in the format: `<place_id> <x_coordinate> <y_coordinate> <capacity>`.
   - After the waste collection points, add a line with the number of vehicles.
   - Each line following that should contain the information for a vehicle in the format: `<vehicle_id> <vehicle_capacity>`.
   - Save the file with a .txt extension.
4. Run the compiled program and provide the path to the input file when prompted.
5. The program will output the optimized routes for each vehicle, indicating the sequence of waste collection points.

### Dependencies

The code is written in C++ and does not have any external dependencies.
