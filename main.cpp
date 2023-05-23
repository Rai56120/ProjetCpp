#include "graph.cpp"
#include "scoreboard.cpp"

#include <gtkmm/application.h>
#include "headers/vue.hpp"

int main(int argc, char *argv[]) {
	int w = 5;

	auto app = Gtk::Application::create(argc, argv);
	
	Vue vue(w);

	return app->run(vue);
}

/*
int main() {
	int w = 5;

	Scoreboard sb(w);
	Labyrinth lab(w);
	
	//Affichage du labyrinthe
	cout << "Labyrinthe :" << endl;
	lab.print();
	
	lab.generateFusion();
	//lab.generateAldousBroder();
	lab.prettyPrint();
	

	
	sb.print();

	Player p("nouveau", 150.25);
	
	cout << "is in top 10 ?" << sb.isTop10(p) << endl;
	cout << "rank:" << sb.getRank(p) << endl;

	sb.insertP(p);

	sb.print();
	string filename = "scores/scoreboardd" + to_string(w) + ".txt";
	sb.save(filename);
	
}
*/