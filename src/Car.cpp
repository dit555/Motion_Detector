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

void Car::update(struct data d){
	//convert m/s^2 into m/time_dif^2
	float accel_scale; //acceleration m/s^2 scaled to 
	float time_dif = d.timestamp - time_previous; //find time ellapsed in between calculations
	accel_scale = time_dif / 1.0; 
	accel_scale *= accel_scale; // accel_scale ^ 2

	//apply
	//also make sure that new data is far enough way from the zero +/- stev margine
	if (mean.accel_Y + stdev.accel_Y < d.accel_Y && mean.accel_Y - stdev.accel_Y > d.accel_Y )
		speed_Y += (d.accel_Y - mean.accel_Y) * accel_scale; 
	if (mean.accel_Z + stdev.accel_Z < d.accel_Z && mean.accel_Z - stdev.accel_Z > d.accel_Z )
		speed_Z += (d.accel_Z - mean.accel_Z) * accel_scale;
}

void Car::write(float time, int flag){
	output_file << time << "," << flag << std::endl;
}

void Car::moving(){
	struct data zero; //will be used to calc zeroing data
	struct data cur; //curent data
	for (int i = 0; i < 10; i++){
		
	}

}

Car::~Car(){
	data_file.close();
	output_file.close();
}
