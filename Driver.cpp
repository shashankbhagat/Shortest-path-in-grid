// File Name: Driver.cpp
// Author: Shashank Bhagat
// Date: 10/09/2017
// Compiler Used: VC++
// Notes: This is an driver file. Intended for the end user for running the program.

#include <iostream>
#include <fstream>
#include "ShortestPath.h"

using namespace std;

int main() {
	int rows, cols, startX, startY, endX, endY;
	int ** input;
	string filename = "input.txt";

	ShortestPath obj(filename);

	cout << "status:" << endl;
	for (int i = 0; i < obj.iterations; i++) {
		do {
			cout << obj;
		} while (!obj.DestinationReached());
		obj.Reset();
	}

	system("pause");
	return 0;
}