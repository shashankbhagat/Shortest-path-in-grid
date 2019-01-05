// File Name: ShortestPath.h
// Author: Shashank Bhagat
// Date: 10/09/2017
// Compiler Used: VC++
// Notes: This is a header file. Includes all the declaration of the variables and member functions in private and public section.

#pragma once
#ifndef SHORTESTPATH
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class ShortestPath {
private:
	int inRows, inCols, startPointx, startPointy, endPointx, endPointy, obstaclesX, obstaclesY;
	int loopctr, currentX, currentY, nextX, nextY;
	int minX, minY, maxX, maxY, vector_counter;
	int path;
	bool top, down, left, right, win;
	string fin;
	char** input;
	int* visited;
	vector<string> fileinput;
	void TracePath();
	int Checkvisited(const int&, const int&);
	int GetLoopCounter(const int&, const int&);
	void LoadData(string filename = "default.txt");
	void PopulateTrack();
	void TraceAlternatePath(int&, int&);

public:
	int iterations;
	ShortestPath(string);
	void operator=(const ShortestPath&);
	const friend ostream& operator<<(ostream&, ShortestPath&);
	void Reset();
	~ShortestPath();
	bool DestinationReached();
};
#endif // !SHORTESTPATH