# EC_hw1_SCH

This project implements binary GA and real-valued GA in C++17 with different operators to find the minimal solution of the Schwefel function (SCH), $N=10$:

$$ f_{SCH}(\vec{x}) = 418.98291N − \sum_{i=1}^{N} x_{i}\sin(\sqrt{| x_i |} ), \quad where -512 \leq x_{i} \leq 511\ $$ 
![](https://i.imgur.com/8ZlQxDA.png)

### Directory Structure

    .
    ├── Makefile 
    ├── README.md
    ├── build                   # Contains the compiled object files and executable
    │   ├── bga.o
    │   ├── global.o
    │   ├── main
    │   ├── main.o
    │   └── rga.o
    ├── data                    # Contains the data files generated by the program
    │   ├── fitness.csv
    │   └── fitness_plot.png
    ├── include                 # Contains the header files for the projec      
    │   ├── bga.h
    │   ├── global.h
    │   └── rga.h
    ├── plot                    # Contains the Python script to plot the fitness data          
    │   └── plot.py
    ├── spec
    │   └── EC22_prog1.pdf
    └── src                     # Contains the source files for the project
         ├── bga.cpp
         ├── global.cpp
         ├── main.cpp
         └── rga.cpp

### Prerequisites
- C++ compiler that supports C++17
- Python 3.x with Matplotlib and Pandas installed
    ```
    pip install pandas matplotlib
    ```
### Run this Project
#### Result 
To directly get the result of the compliation, run, plot directly, run the following code:
```
$ make result
```
This repository is already had the executable file(main) inside the build directory, so you can run the project using the following code directly.
```
$ make run
$ make plot
```

#### Compliation
To compile the project, run the following command in the project root directory:
```
$ make
```
This command will generate the main executable inside the build directory.

### Running the Program
To run the program, use the following command:

```
$ make run
```
This command will execute the main program and move the generated fitness.csv file to the data directory.

### Plotting the Fitness Data
To plot the fitness data, run the following command:

```
$ make plot
```
This command will execute the plot.py Python script inside the plot directory to generate a plot of the fitness data.

### Cleaning up
To clean up the build files, run the following command:

```
make clean
```
This command will remove the object files and the main executable from the build directory.
### 
