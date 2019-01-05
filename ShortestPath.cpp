// File Name: ShortestPath.cpp
// Author: Shashank Bhagat
// Date: 10/09/2017
// Compiler Used: VC++
// Notes: This is an implementation file. All the member & non-member functions are implemented.

#include "ShortestPath.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/* constructor for initialising the data members and also loading the data for the track. */
ShortestPath::ShortestPath(string filename) {
	iterations = 0;
	LoadData(filename);
	vector_counter = 0;

	ofstream outputToFile;
	outputToFile.open("output.txt");
	outputToFile.close();

	minX = 0; minY = 0;
	maxX = inRows;
	maxY = inCols;
	loopctr = 0;
	top = false;
	down = false;
	left = false;
	right = false;
	win = false;
	path = -1;
}

/* Overloading the = operator. */
void ShortestPath::operator=(const ShortestPath& Rhs) {
	iterations = 0;
	vector_counter = 0;
	minX = 0; minY = 0;
	maxX = inRows;
	maxY = inCols;
	loopctr = 0;
	top = false;
	down = false;
	left = false;
	right = false;
	win = false;
	path = -1;
}

/* Reset method for resetting the values and also calling the destructor manually. */
void ShortestPath::Reset()
{
	loopctr = 0;
	top = false;
	down = false;
	left = false;
	right = false;
	win = false;
	path = -1;
	this->~ShortestPath();
}

/* Overloading the Destructor. */
ShortestPath::~ShortestPath() {
	delete visited;
	for (int i = 0; i < inRows; i++) {
		delete[] input[i];
	}
	delete[] input;
	fileinput.clear();
}

/* Operator overloading the << operator. Would also call the TracePath and PopulateTrack methods. */
const ostream& operator<<(ostream& out, ShortestPath& obj) {
	string str;
	if (obj.path >= 0) {
		obj.TracePath();
		str = "**********Step " + to_string(obj.path) + "***********";
	}
	else {
		obj.PopulateTrack();
		str = "************Start Configuration ************";
	}

	ofstream outputToFile;
	outputToFile.open("output.txt", ios::app);
	out << str << endl;
	outputToFile << str << endl;

	for (int i = 1; i < obj.inRows; i++) {
		for (int j = 1; j < obj.inCols; j++) {
			out << obj.input[i][j];
			outputToFile << obj.input[i][j] << "\t";
		}
		out << endl;
		outputToFile << endl;
	}
	out << endl << endl;
	outputToFile << endl << endl;
	obj.top = false;
	obj.down = false;
	obj.left = false;
	obj.right = false;
	outputToFile.close();
	return out;
}

/* Method to check the vivisted array whether a specific cell has been previously visited or not. */
int ShortestPath::Checkvisited(const int& currentX, const int& currentY)
{
	visited[((startPointx - 1)*(inCols - 1)) + (startPointy - 1)] = 1;
	if (visited[((currentX - 1)*(inCols - 1)) + (currentY - 1)])
		return 1;
	else
		return 0;
}

/* This method returns the accessible cells from a given cell neglecting the obstacles. */
int ShortestPath::GetLoopCounter(const int& currentX, const int& currentY)
{
	loopctr = 0;
	if (currentX - 1 > minX && (Checkvisited(currentX - 1, currentY) == 0)) {
		loopctr++;
		top = true;
	}

	if (currentY - 1 > minY && (Checkvisited(currentX, currentY - 1) == 0)) {
		loopctr++;
		left = true;
	}

	if (currentX + 1 < maxX && (Checkvisited(currentX + 1, currentY) == 0)) {
		loopctr++;
		down = true;
	}

	if (currentY + 1 < maxY && (Checkvisited(currentX, currentY + 1) == 0)) {
		loopctr++;
		right = true;
	}
	return loopctr;
}

/* This method would trace the path as per the logic designed. */
void ShortestPath::TracePath() {
	GetLoopCounter(currentX, currentY);

	visited[((currentX - 1)*(inCols - 1)) + (currentY - 1)] = 1;
	for (int i = 0; i < loopctr; i++) {
		if (top == true) {
			nextX = currentX - 1;
			nextY = currentY;
			top = false;
		}
		else if (right == true) {
			nextX = currentX;
			nextY = currentY + 1;
			right = false;
		}
		else if (down == true) {
			nextX = currentX + 1;
			nextY = currentY;
			down = false;
		}
		else if (left == true) {
			nextX = currentX;
			nextY = currentY - 1;
			left = false;
		}

		if (input[nextX][nextY] == 'O') {
			nextX = currentX;
			nextY = currentY;
		}
		if (input[nextX][nextY] == '=') {
			path++;
			break;
		}
		if (input[nextX][nextY] == 'E') {
			path++;
			win = true;
			break;
		}
	}

	if ((nextX == currentX && nextY == currentY) || loopctr == 0) {
		TraceAlternatePath(currentX, currentY);
	}

	input[nextX][nextY] = 'C';
	input[currentX][currentY] = '=';
	currentX = nextX;
	currentY = nextY;
}

/* This method is for deadlock situations. It would trace an alternate path neglecting the visited array. Working is similar to recursive function. */
void ShortestPath::TraceAlternatePath(int& currentX, int& currentY) {
	loopctr = 0;
	if (currentX - 1 > minX) {
		loopctr++;
		top = true;
	}

	if (currentY - 1 > minY) {
		loopctr++;
		left = true;
	}

	if (currentX + 1 < maxX) {
		loopctr++;
		down = true;
	}

	if (currentY + 1 < maxY) {
		loopctr++;
		right = true;
	}

	visited[((currentX - 1)*(inCols - 1)) + (currentY - 1)] = 1;

	for (int i = 0; i < loopctr; i++) {
		if (top == true) {
			nextX = currentX - 1;
			nextY = currentY;
			top = false;
		}
		else if (right == true) {
			nextX = currentX;
			nextY = currentY + 1;
			right = false;
		}
		else if (down == true) {
			nextX = currentX + 1;
			nextY = currentY;
			down = false;
		}
		else if (left == true) {
			nextX = currentX;
			nextY = currentY - 1;
			left = false;
		}

		if (input[nextX][nextY] == 'O') {
			nextX = currentX;
			nextY = currentY;
		}
		if (input[nextX][nextY] == '=') {
			path++;
			break;
		}
		if (input[nextX][nextY] == 'E') {
			path++;
			win = true;
			break;
		}
	}
}

/* Checks whether the trace is complete or not. */
bool ShortestPath::DestinationReached() {
	if (win) {
		ofstream outputToFile;
		cout << "Destination Reached!!" << endl << "Path:" << path << endl << endl;
		outputToFile.open("output.txt", ios::app);
		outputToFile << "Destination Reached!!" << endl << "Path:" << path << endl << endl;
		outputToFile.close();
		return true;
	}
	else
		return false;
}

/* this method loads all the data in a vector from a file. Avoids repeated access to file. */
void ShortestPath::LoadData(string filename) {
	string tempFileData;
	ifstream fname(filename);
	while (!fname.eof()) {
		getline(fname, tempFileData);
		fileinput.push_back(tempFileData);
		if (tempFileData == "-1")
			iterations++;
	}
	iterations++;
	fname.close();
}

/* This method would populate the initial track i.e. start and end points and also the obstacles. */
void ShortestPath::PopulateTrack() {
	if (fileinput.size() == 0)
	{
		fileinput.clear();
		iterations = 0;
		LoadData("input.txt");
	}

	string test = fileinput[vector_counter++];
	inRows = stoi(test.substr(1, test.find(','))) + 1;
	inCols = stoi(test.substr(test.find(',') + 1, test.length() - test.find(','))) + 1;
	maxX = inRows;
	maxY = inCols;

	test = fileinput[vector_counter++];
	startPointx = stoi(test.substr(1, test.find(',')));
	startPointy = stoi(test.substr(test.find(',') + 1, test.length() - test.find(',')));

	test = fileinput[vector_counter++];
	endPointx = stoi(test.substr(1, test.find(',')));
	endPointy = stoi(test.substr(test.find(',') + 1, test.length() - test.find(',')));

	currentX = startPointx;
	currentY = startPointy;

	visited = new int[(inRows - 1)*(inCols - 1)]();
	input = new char*[inRows];
	for (int i = 0; i < inRows; i++) {
		input[i] = new char[inCols];
	}

	for (int i = 1; i < inRows; i++) {
		for (int j = 1; j < inCols; j++) {
			input[i][j] = '=';
		}
	}

	input[startPointx][startPointy] = 'C';
	input[endPointx][endPointy] = 'E';

	do {
		test = fileinput[vector_counter%fileinput.size()];
		if (test == "-1") {
			vector_counter++;
			break;
		}

		obstaclesX = stoi(test.substr(1, test.find(',')));
		obstaclesY = stoi(test.substr(test.find(',') + 1, test.length() - test.find(',')));
		input[obstaclesX][obstaclesY] = 'O';
		vector_counter++;
	} while (vector_counter < fileinput.size());
	path = 0;
}