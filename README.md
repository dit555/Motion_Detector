# Motion_Detector
## Contents  
- [How to Use](#How-to-Use)
- [Task Description](#Task-Description)
- [Though Process](#Though-Process)
- [Description of Files](#Description-of-Files)

## How to Use
clone this project with: `git clone https://github.com/dit555/Motion_Detector.git`  
run `make` to compile the project  
to run the project: `./detector.out <input.csv name> <output.csv name>`

## Task Description
The IMU installed on a regular car which stats with 0 speed. The input file contains IMU measurements in a csv format. Columns are the following: Timestamp, acceleration X, acceleration Y, acceleration Z, rotation speed X, rotation speed Y, rotation speed Z, and status. Timestamps are seconds, acceleration is in meters/seconds^2, rotation speed is in radians/second. Create another csv file, with same timestamps and with “motion indication flag”: 0 when vehicle is moving, and “1” when it is standing still.

## Thought Process
When first looking at the data, we noticed that the row for acceleration X had an average of 9.8 m/s^2. This acceleration value is the acceleration of gravity. Knowing this we can orient the 3d axis like this:  

<img src="https://user-images.githubusercontent.com/56750709/136298021-540b37be-66ba-4dff-874f-9436eba99a13.JPG" width=500>
  
Where -X is pointing upwards away from the road and +X is pointing to the ground. The road is the plane on the Y and Z axis. As a result, we know the car is moving when it has speed in the Y or Z direction. In addition, the only way the car could turn in this case is if it is rotating along the X axis. Therefore, the only data values we can use to determine if the car is moving are: acceleration Y, acceleration Z, and rotation speed X.  

Looking in other columns of the imu csv we notice that even when the car has no speed, some of the values are far off what they would be normally. For example, the average value for acceleration Y is -1.4 m/s^2. This is clearly incorrect as it should be 0 when the car is standing still. As a result, we choose to normalize the data (shift it by subtracting the mean). To do this, we read the first 10 lines of the input csv (~0.1 s from the first timestamp) and use those to get the mean and standard deviation of the data. This is a really safe amount of time because, it is very unlikely that anyone would start accelerating the car after starting it within that timeframe.  

After reading the first ten lines and using them to calculate the mean and standard deviation, we start reading the input csv line by line. We only store the contents of one line as we go because doing so saves a lot of memory as opposed to loading them all at once. We then see if the values are outside of one standard deviation from the mean. If they are outside then they are accepted.  
![number line](https://user-images.githubusercontent.com/56750709/136300763-2f9f805e-3f27-42ca-a074-7dc256ff6b30.png)  

We do this to ignore values that are both: too small to make a notable difference of the car, or values that are noise caused by tolerances in the imu. Values that are accepted are then used to update the car_speed_X, car_speed_Y, and car_rotation_speed_X of the car. For the speed values, the respective acceleration value is added to the current speed of the car. Rotation speed is set directly equal to the normalized data.  

Finally, we calculate the diagonal velocity of the car using car_speed_X and car_speed_Y. This way we get a one directional velocity vector. This along with rotation speed allows us to determine if the car is moving. To further remove noise, we choose to say the car is moving only when it is faster than 0.25 m/s or is rotating faster than 0.25 rad/s. We choose 0.25 m/s because that is equivalent to 0.5 mph which cars can accelerate to almost instantaneously. We also choose 0.25 rad/s because when a car is making wide turns, it is not necessarily moving fast, but it is moving considerably to the side. Using this we write 1 to the file if the car is not moving and 0 to the file if the car is moving.

## Description of files  
### imu.csv:   
* contains the data from the imu

### output.csv
* csv with columns: timestamp, motion flag
* timestamp is the timestamp form imu.csv
* motion flag is 0 when car is moving, 1 when it is not moving

### Makefile
* `make` or `make run`: compiles the project as normal
* `make clean`: removes \*.out files

### header/structs.hpp:
* contains a row of data read from the csv file
* contains a flag that signifies end of file

### header/data_math.hpp and src/data_math.cpp:
* `struct data mean_data(struct data* d, const int size)`: takes an array of the data struct and then returns a new data struct with the mean value for each.
* `struct data standard_deviation_data(struct data m, struct data* d, const int size)`: takes the mean from about as well as the same array as above and returns a data struct with standard deviation
* `float get_speed(float a, float b)`: calculates the hypotneus of a triangle given two sides
* `void print_data(struct data d)`: prints all values of the data stuck in a comma separted list

### header/Car.hpp and src/Car.cpp:
* `Carstd::string input_file_path, std::string output_file_path)`: constructor for car class, takes the file path for the input csv, and open the input and output files
* `struct data tokenize_line()`: reads a line from the csv and sparates the values into a data struct
* `void update_car_speed(struct data d)`:
  * converts m/s^2 into ~m/cs^2 
  * checks if the data from a line of the input csv is within one standard deviation of the median. If it is not within one standard deviation then it modifies the parameters of the car (`car_speed_Y`, `car_speed_Z`, and `car_rotation_speed_X`)
* `void write_to_output(float time, int flag)`: writes to the output csv
* `void run_moving()`: 
  * read first 10 lines to get the mean and standard deviation of those lines
  * reads each line of the csv one by one and decides if the car is moving or not
* `~Car`: the destructor for car class, closes both files.

### src/detector.cpp:
* contains the main that runs the program
