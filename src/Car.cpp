#include <iostream>
#include <string>
#include <fstream>

#include "../header/Car.hpp"
#include "../header/structs.hpp"

using std::string;
using std::stof;

Car::Car(string file_path){
	data_file.open(file_path, std::ifstream::in);
	output_file.open("output.csv", std::ofstream::out | std::ofstream::trunc);
}

struct data Car::tokenize(){
	struct data temp; //data struct to be returned 
	string::size_type sz; //starting inde of stof
	float value_temp; //variable that holds the float temporarely
	string line;
	if (data_file.is_open()){
		if(std::getline(data_file, line)){
			temp.timestamp = stof(line, &sz); //timestamp
			sz++;
			line = line.substr(sz);
			value_temp = stof(line,&sz); //accel_X
			sz++;
			line = line.substr(sz);
			temp.accel_Y = stof(line, &sz); //accel_Y
			sz++;
			line = line.substr(sz);
			temp.accel_Z = stof(line, &sz); //accel_Z
			sz++;
			line = line.substr(sz);
			temp.rot_speed_X = stof(line, &sz); //rot_spd_X
			sz++;
			line = line.substr(sz);
		}
		else
			temp.file_finish = 1; //file is fully read
	}
	else 
		temp.file_finish = 1; //make sure file is open

	return temp;
}

void Car::update(struct data){
	//convert m/s^2 into m/time_dif^2
	float accel_scale; //acceleration m/s^2 scaled to 
	float time_dif = data.timestamp - time_previous; //find time ellapsed in between calculations
	accel_scale = time_dif / 1.0; 
	accel_scale *= accel_scale; // accel_scale ^ 2

	//apply
	speed_Y += (data.accel_Y - zero_accel_Y) * accel_scale; 
	speed_X += (data.accel_Z - zero_accel_Z) * accel_scale;
}

void Car::moving(){
	struct data zero; //will be used to calc zeroing data

}

Car::~Car(){
	data_file.close();
	output_file.close();
}
