# Motion_Detector
## Contents  
1. Task Description
2. Thought Process
3. Description of files
 

## Task Description
The IMU installed on a regular car. The attached file contains IMU measurements  in a csv format. Columns are following:    
Timestamp, acceleration X, acceleration Y, acceleration Z, rotation speed X, rotation speed Y, rotation speed Z, and status.  
Timestamps are seconds, acceleration is in meters/seconds^2, rotation speed is in radians/second.  
Create another csv file, with same timestamps and with “motion indication flag”: 0 when vehicle is moving, and “1” when it is standing still.

## Thought Process


## Description of files  
### imu.csv:   
* contains the data from the imu

### output.csv
* csv with columns: timestamp, motion flag
* timestamp is the timestamp form imu.csv
* motion flag is 0 when car is moving, 1 when it is not moving

### Makefile
* `make` or `make run`: compiles the project as normal
* `make test`: compiles using test/test.cpp instead of src/detector.cpp
* `make clean`: removes \*.out files

### header/structs.hpp:
* contains a row of data read from the csv file
* contains a flag that signifies end of file

### header/data_math.hpp and src/data_math.cpp:
* `struct data mean_d(struct data* d, const int size)`: takes an array of the data struct and then returns a new data struct with the mean value for each.
* `struct data stdev_d(struct data m, struct data* d, const int size)`: takes the mean from about as well as the same array as above and returns a data struct with standard deviation
* `float pyth(float a, float b)`: calculates the hypotneus of a triangle given two sides
* `void printS(struct data d)`: prints all values of the data stuck in a comma separted list

### header/Car.hpp and src/Car.cpp:
* `Car(string file_path)`: constructor for car class, takes the file path for the input csv, and open the input and output files
* `struct data tokenize()`: reads a line from the csv and sparates the values into a data struct
* `void update(struct data d)`:
  * converts m/s^2 into ~m/cs^2 
  * checks if the data from a line of the input csv is within one standard deviation of the median. If it is not within one standard deviation then it modifies the parameters of the car (`speed_Y`, `speed_Z`, and `rot_speed_X`)
* `void write(float time, int flag)`: writes to the output csv
* `void moving()`: 
  * read first 10 lines to get the mean and standard deviation of those lines
  * reads each line of the csv one by one and decides if the car is moving or not
* `~Car`: the destructor for car class, closes both files.

### src/detector.cpp:
* contains the main that runs the program

### test/test.cpp:
* contains the main the runs tests for the program.
