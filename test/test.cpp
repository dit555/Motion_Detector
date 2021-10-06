#include <iostream>
#include <string>

#include "../header/Car.hpp"
#include "../header/structs.hpp"

//std::string
using std::string;

//std:iostream
using std::cout;
using std::endl;

int main(){	//don't need any args
	string csv_file_path = "imu.csv";
	cout << "reading file: " << csv_file_path << endl;
	struct data test;
	Car c(csv_file_path);
	for (int i = 0; i < 10; i++){
		test = c.tokenize();
		c.write(test.timestamp, 0);
		//cout << test.timestamp << "," << test.accel_Y << "," << test.accel_Z << "," << test.rot_speed_X << endl;
	
	}	
	return 0;
}

