#ifndef __STRUCT__
#define __STRUCT__

// This file defines structs to be used in the project

struct data{
	//data to be read from *.csv file
	float timestamp;
	float accel_Y;
	float accel_Z;
	float rot_speed_x;
	int file_finish; //flag for end of file or  any file failure
};

#endif
