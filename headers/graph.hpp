#pragma once
#include <cstdlib>
#include <map>
#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

class Point {
protected:
	vector<int> adj;
public:
	Point() {}
	void addAdj(int a);
	vector<int> getAdj() const;
};

class Labyrinth {
private:
	map<int, Point> pointList;
	int width;

	int startingPoint;
	int endingPoint;
	
public:
	Labyrinth(const int w);

	Point getPoint(const int id);
	int getWidth() const;
	vector<int> getAdjacent(const int id);

	void setPath(const int p1, const int p2);
	int isPath(const int p1, const int p2);
	int chooseRand(const int *id);
	
	void generateFusion();
	void generateAldousBroder();

	void print() const;
	void prettyPrint();
	void testGeneration();
};