#include "headers/graph.hpp"

/***************************************************************************
 *************************		Class Point			************************
 ***************************************************************************/
void Point::addAdj(int a) {
	this->adj.push_back(a);
}
vector<int> Point::getAdj() const {
	return this->adj;
}

/***************************************************************************
 *************************		Class Labyrinth		************************
 ***************************************************************************/
Labyrinth::Labyrinth(const int w) : width(w){
	for(int i = 0; i < w*w; i++) {
		Point p;
		this->pointList[i] = p;
	}

	srand(time(NULL));
}

Point Labyrinth::getPoint(const int id) {	
	Point p;
	if(this->pointList.find(id) != this->pointList.end()) {
		p =  this->pointList[id];
	} else {
		cout << "Index error ! Unavailable id" << endl;
		p.addAdj(-1);
	}
	return p;
}

int Labyrinth::getWidth() const {
	return this->width;
}
vector<int> Labyrinth::getAdjacent(const int id){
	vector<int> adj;
	if(this->pointList.find(id) != this->pointList.end()) {
		adj = this->pointList[id].getAdj();
	} else {
		adj.push_back(-1);
	}
	return adj;
}

void Labyrinth::setPath(const int p1, const int p2) {
	this->pointList[p1].addAdj(p2);
	this->pointList[p2].addAdj(p1);
}

int Labyrinth::isPath(const int p1, const int p2) {
	int ret = 0;
	
	for(auto p: this->getAdjacent(p1)) {
		if(p == p2) { ret = 1; }
	}
	return ret;
}

int Labyrinth::chooseRand(const int &id) {
	/*	orientation:
			0
		1 - + - 3
			2
	*/
	int orientation = rand()%4;
	int nextElement = id;

	if(orientation == 0 && id >= this->width) {
		nextElement = id-this->width;
	}

	else if(orientation == 1 && id % this->width != 0) {
		nextElement = id-1;
	}

	else if(orientation == 2 && id < this->width*this->width - this->width) {
		nextElement = id+this->width;
	}

	else if(orientation == 3 && (id+1) % this->width != 0) {
		nextElement = id+1;
	}

	return nextElement;
}

void Labyrinth::generateFusion() {
    const int tot = this->width*this->width;

    //On crée un tableau avec les Id des cases
    int idTab[tot];

    for(int i = 0; i < tot; i++) { idTab[i] = i; }

    int element;
	int neighborElement = element;
	bool finishFlag = false;
	
	while(!finishFlag) {
		
		element = rand()%tot;

		//On vérifie que l'on a bin tout les id identiques
		int sum = 0;
		for(int i = 1; i < tot; i++) {
			if(idTab[i-1] == idTab[i]) {
				sum += 1;
			}
		}
		if(sum == tot-1) { finishFlag = true; }
		
		neighborElement = this->chooseRand(element);

		if(idTab[neighborElement] != idTab[element]) {
			this->setPath(element, neighborElement);
			idTab[neighborElement] = idTab[element];
		}
	}
}

void Labyrinth::generateAldousBroder() {
	int tot = this->width*this->width;

	vector<int> visited, vect;
	int lastElement = rand()%tot;
	int nextElement = lastElement;

	visited.push_back(lastElement);
	
	vect.push_back(lastElement);

	while(visited.size() < (unsigned long) tot) {		
		lastElement = vect.back();

		nextElement = this->chooseRand(lastElement);
		
		if(lastElement != nextElement) {
			bool visitedFlag = 0;
			
			for(auto v: visited) {
				if(v == nextElement) {
					visitedFlag = 1;
					break;
				}
			}
			if(!visitedFlag && !isPath(lastElement, nextElement)) { 
				this->setPath(lastElement, nextElement);
				visited.push_back(nextElement);

				//cout << "Nb de pts visites : " << visited.size() << "				Dernier visite : " << visited.back() << endl;
			}
			vect.push_back(nextElement);
		}
	}
}

/*
void Labyrinth::print() const {
	int tot = (this->width)*(this->width);
	for(int i = 0; i < tot; i++) {
		cout << i << "	";
		if((i+1)%width == 0) { cout << endl; }
	}
}

void Labyrinth::prettyPrint() {
	int tot = (this->width)*(this->width);
	
	//Mise en forme
	cout << endl << "Pretty print :" << endl;

	for(int i = 0;i < this->width; i++) { cout << " _"; }
	cout << endl << "|";

	//On parcourt les cases
	for(int i = 0; i < tot; i++) {
		//S'il y a un un chemin quelconque
		if((this->isPath(i, i+1)) || 
			(this->isPath(i, i+this->width))) {
			
			//Cas où il y a un angle
			if((this->isPath(i, i+1)) && 
				(this->isPath(i, i+this->width))) {
				cout << "  ";
			}

			//Cas où c'est en ligne
			else if(this->isPath(i, i+1)) {
				if(this->isPath(i, i+1)) { cout << "_ "; }
				else { cout << "|_ "; }
			}

			//Cas où c'est en colonne
			else if(this->isPath(i, i+this->width)) { cout << " |"; }
		}

		//S'il n'y a pas de chemin
		else { cout << "_|"; }

		//Lorsque l'on arrive en fin de ligne
		if((i+1)%this->width == 0 && 
			i+1 != this->width*this->width) { 
			cout << endl << "|"; 
		}
	}
	cout << endl;
}

void Labyrinth::testGeneration(){
	cout << "Liste des relations :" << endl;

	for(int i = 0; i < this->width*this->width; i++) {
		for(int j = i+1; j < this->width*this->width; j++) {
			if(this->isPath(i, j)) {
				cout << "(" << i << " , " << j << ")" << endl;
			}
		}
	}
}
*/