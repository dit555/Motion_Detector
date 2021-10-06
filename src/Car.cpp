#include <iostream>
#include <string>
#include <fstream>

#include "../header/Car.hpp"
#include "../header/structs.hpp"
#include "../header/data_math.hpp"

using std::string;
using std::stof;

const int init_n = 50; //how many lines are read to be used of calc of mean and stdev

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
	//accel_Y
	if (!(m.accel_Y - s.accel_Y < d.accel_Y && d.accel_Y < m.accel_Y + s.accel_Y))
		speed_Y += (d.accel_Y - m.accel_Y) * accel_scale; 
	//accel_Z
	if (!(m.accel_Z - s.accel_Z < d.accel_Z && d.accel_Z < m.accel_Z + s.accel_Z))
		speed_Z += (d.accel_Z - m.accel_Z) * accel_scale;
	//rot_spd_X
	if (!(m.rot_speed_X - s.rot_speed_X < d.rot_speed_X && d.rot_speed_X < m.rot_speed_X + s.rot_speed_X))
		r_speed_X = (d.rot_speed_X - m.rot_speed_X);


}

void Car::write(float time, int flag){
	output_file << time << "," << flag << std::endl;
}

void Car::moving(){
	struct data cur; //curent data
	
	struct data ar[init_n]; //array be used for mean and stdev
	for (int i = 0; i < init_n; i++){
		ar[i] = tokenize();
		time_previous = ar[i].timestamp;
		write(ar[i].timestamp, 1);//vehicle is standing still during this time
	}
	m = mean_d(ar, init_n); //find mean
	s = stdev_d(m, ar, init_n); //find stdev
	
	//do the rest
	cur = tokenize();
	while (!cur.file_finish){
		//std::cout << "doing: " << cur.timestamp << std::endl;
		float spd = pyth(speed_Y, speed_Z);
		std::cout << "spd: " << spd << ", rot_sp: " << r_speed_X << std::endl;
		if (spd >= 0.25 || (r_speed_X >= 0.25 && r_speed_X <= -0.25)){ //check if moving
			write(cur.timestamp, 0); // moving
		}
		else
			write(cur.timestamp, 1); //not moving
		cur = tokenize();
	}
}

Car::~Car(){
	data_file.close();
	output_file.close();
}
