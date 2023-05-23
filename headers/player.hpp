#pragma once
#include <cstdlib>
#include <string>

class Player {
private:
	int rank;
	string name;
	unsigned long time;
public:
	Player(const string n, const unsigned long t) : name(n), time(t) {}
	Player(const int r, const string n, const unsigned long t) : rank(r), name(n), time(t) {}
	
	int getRank() { return this->rank;}
	void setRank(const int r) {this->rank = r; }

	string getName() { return this->name; }
	unsigned long getTime() { return this->time; }
};