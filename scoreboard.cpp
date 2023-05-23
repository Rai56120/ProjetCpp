#include "headers/scoreboard.hpp"

Scoreboard::Scoreboard(int d) {
	this->difficulty = d;
	string filename = "scores/scoreboardd" + to_string(d) + ".txt";
	ifstream file(filename);

	if(!file) { cerr << "Failed to open the file: " << filename << endl; }

	int rank = 1;

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name;
        unsigned long time;
        int diff;

        getline(iss, name, ',');
        iss >> time;
        iss.ignore();
        iss >> diff;

        if(diff == d) {
        	this->scores.emplace_back(rank, name, time);
        	rank++;
        }
        
    }
    file.close();
}

void Scoreboard::print() {
	cout << "+-------------------------------------------------------+" << endl;
	cout << "| rank	|	name	|	time	| difficulty	|" << endl;
	cout << "+-------------------------------------------------------+" << endl;
	for(auto p: this->scores) {
		cout << "| " << p.getRank() << "	|	" << p.getName() << "	|	" << p.getTime() << "	|	" << this->difficulty << " 	|" << endl;
	}
	cout << "+-------------------------------------------------------+" << endl;
}

bool Scoreboard::isTop10(Player newP) {
	vector<Player>::iterator i;

	for(i = this->scores.begin(); i < this->scores.begin()+10; i++){
		if(newP.getTime() < (*i).getTime()) {
			return true;
		}
	}
	return false;
}

int Scoreboard::getRank(Player newP) {
	vector<Player>::iterator i;

	for(i = this->scores.begin(); i < this->scores.end(); i++){
		if(newP.getTime() < (*i).getTime()) {
			return (*i).getRank();
		}
	}
	return -1;
}

void Scoreboard::insertP(Player newP) {
	this->scores.insert(this->scores.begin() + this->getRank(newP) -1, newP);
	int r = 1;
	vector<Player>::iterator i;
	for(i = this->scores.begin(); i < this->scores.end(); i++, r++) {
		(*i).setRank(r);
	}
}

void Scoreboard::save(const string filename) {
	ofstream file(filename);

    for (auto p : this->scores) {
        file << p.getName() << "," << p.getTime() << "," << this->difficulty << ";\n";
    }

    file.close();
}