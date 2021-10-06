#ifndef __CAR__
#define __CAR__

#include <iostream>
#include <string>
#include <fstream>

#include "structs.hpp"

using std::string;


class Car{
public:
	Car(string file_path); //constructor input filepath name
	struct data tokenize(); //read next line from file and separate data into data struct
	void update(struct data d); //updates speed of car
	void write(float time, int flag); //writes data to new csv
	void moving(); //checks if moving and writes to the file
	~Car(); //closes the files

private:
	std::ifstream data_file; //stores opened file
	std::ofstream output_file; //stores new csv file
	
	//current car data
	float time_previous;
	float speed_Y;
	float speed_Z;
	float r_speed_X;

	//zeroing data
	struct data mean; // holds the mean of the data
	struct data stdev; // holds the stdev of the data
};

#endif
