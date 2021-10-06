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

	//TODO
}

void Car::moving(){
	//TODO
}

Car::~Car(){
	data_file.close();
	output_file.close();
}
