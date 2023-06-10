#include <gtkmm/application.h>
#include "headers/vue.hpp"

int main(int argc, char *argv[]) {
	//Taille du labyrinthe
	int w = 5;
	//False = Aldous-Broder			True = Fusion
	bool selectedAlgorithm = false;
	Labyrinth lab(w);
	
	auto app = Gtk::Application::create(argc, argv);
	
	Vue vue(w, selectedAlgorithm, lab);

	return app->run(vue);
}