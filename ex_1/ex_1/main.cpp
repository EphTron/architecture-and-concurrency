#include <iostream>
#include <math.h>
#include <Windows.h>
#include <fstream>

using namespace std;
// number of loops 
const int loopSize = 99999999; 
float x[loopSize], y[loopSize], g[loopSize];

void main(int argc, char** argv)
{ 
	// initialise data 
	for (int i = 0; i < loopSize; i++) {
		x[i] = float(i);
	}
	cout << "Running" << endl;

	// setup timer 
	LARGE_INTEGER li;
	double freq = 0.0;

	// get freqency of machine
	if (!QueryPerformanceFrequency(&li)) {
		cout << "QueryPerformanceFrequency failed!\n";
	}
	freq = double(li.QuadPart) / 1000.0;
	// freq = double(start_time.QuadPart)  // seconds;
	// freq = double(start_time.QuadPart) / 1000000.0  // microseconds;

	// start timer
	QueryPerformanceCounter(&li);
	__int64 start = li.QuadPart;

	// calculation of the square root results
	for (int i = 0; i < loopSize; i++) {
		y[i] = x[i] * x[i] + x[i] + 1.0f + sqrt(x[i]);
		g[i] = x[i] * x[i] + x[i] + 6.0f + sqrt(x[i]);
	}
	
	// stop timer
	QueryPerformanceCounter(&li);
	__int64 stop = li.QuadPart;

	// get elapsed time and write to file
	double ellapsedTime = double(stop - start) / freq;
	ofstream file;
	file.open("times.txt", ofstream::app);
	file << ellapsedTime << "\n";
	file.close();

	// display 'Finished' and pause
	cout << "Finished after " << ellapsedTime << " milliseconds" << endl;

	// make sure optimizer doesn't get rid of y
	double sum = 0.0;
	for (int i = 0; i < loopSize; ++i) {
		sum += y[i];
	}


	system("Pause");
}