#ifndef __STRUCT__
#define __STRUCT__

// This file defines structs to be used in the project

struct data{
	//data to be read from *.csv file
	float timestamp;
	float accel_X;
	float accel_Y;
	float accel_Z;
	float rot_speed_x;
	float rot_speed_y;
	float rot_speed_z;
	int file_finish; //flag for file end
};

#endif
