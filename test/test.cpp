#include <iostream>
#include <string>

#include "../header/Car.hpp"
#include "../header/structs.hpp"
#include "../header/data_math.hpp"

//std::string
using std::string;

//std:iostream
using std::cout;
using std::endl;

int main(){	//don't need any args
	string csv_file_path = "imu.csv";
	cout << "reading file: " << csv_file_path << endl;
	struct data t;
	Car c(csv_file_path);
	c.moving();
	
	return 0;
}

