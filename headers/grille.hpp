#pragma once
#include <gtkmm.h>
#include "../graph.cpp"

class Grille : public Gtk::DrawingArea {
private:
    int coteCase;

    int largeur;
    int hauteur;

    int largeurPixel = 600;
    int hauteurPixel = 600;

    Labyrinth lab;

    //Position du joueur
    int xCercle;
    int yCercle;

public:
    Grille(const int l, const int h, const bool algo, Labyrinth laby);

    virtual ~Grille() {}

   
protected:
    void finalScreen();

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    bool on_key_press_event(GdkEventKey* event) override;
   
};
