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
	const int sz = 50;
	struct data ar[sz];
	for (int i = 0; i < sz; i++){
		t = c.tokenize();
		c.write(t.timestamp, 0);
		ar[i] = t;
		//printS(t);
	
	}
	
	struct data m;
       	m = mean_d(ar, sz);
	struct data s;
       	s = stdev_d(m, ar, sz);
	cout << "mean: ";
	printS(m);
	cout << "stdev ";
	printS(s);
	
	return 0;
}

