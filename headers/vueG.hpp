#pragma once
#include <gtkmm.h>
#include "grille.hpp"

class VueG : public Gtk::Window {
protected:
	Grille g;
	Gtk::VBox box1{};
	Gtk::Button bClose;
public:
    VueG() : g(Grille(6, 4)), bClose(Gtk::StockID(Gtk::Stock::CLOSE)){
        set_title("Damier");
        box1.pack_start(g);
        box1.pack_start(bClose);
        add(box1);

        bClose.signal_clicked().connect([this] () {this->close(); });
        g.set_can_focus(true);
        g.set_focus_on_click(true);

        show_all_children();
    }

    virtual ~VueG() {}
};
