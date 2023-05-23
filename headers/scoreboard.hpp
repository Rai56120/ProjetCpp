#pragma once
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "player.hpp"

using namespace std;

class Scoreboard {
private:
	vector<Player> scores;
	int difficulty;
public:
	Scoreboard(const int d);

	void print();
	bool isTop10(Player newP);
	int getRank(Player newP);

	void insertP(Player newP);
	void save(const string filename);
};