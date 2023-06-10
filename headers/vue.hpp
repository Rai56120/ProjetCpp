#pragma once
#include <gtkmm.h>
#include "grille.hpp"

class Vue : public Gtk::Window {
protected:
	Grille g;
	Gtk::VBox box1{};
	Gtk::Button bClose;

public:
    Vue(const int w, const bool algo, const Labyrinth &l) : bClose(Gtk::StockID(Gtk::Stock::CLOSE)), g(Grille(w, w, algo, l)){        
        set_title("Labyrinthe");
        box1.pack_start(g);
        box1.pack_start(bClose);
        add(box1);

        bClose.signal_clicked().connect([this] () {this->close(); });
        g.set_can_focus(true);
        g.set_focus_on_click(true);

        show_all_children(); 
    }

    virtual ~Vue() {}
};
