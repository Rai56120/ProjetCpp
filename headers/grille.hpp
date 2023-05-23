#pragma once
#include <gtkmm.h>

class Grille : public Gtk::DrawingArea {
private:
    const int coteCase = 60;

    int largeur;
    int hauteur;

    int largeurPixel;
    int hauteurPixel;

    int xCaseCercle;
    int yCaseCercle;

public:
    Grille(const int l, const int h) : largeur(l), hauteur(h), xCaseCercle(0), yCaseCercle(0) {
        this->largeurPixel = largeur*coteCase;
        this->hauteurPixel = hauteur*coteCase;
        this->set_size_request(this->largeurPixel, this->hauteurPixel);
        

        //Clic de la souris
        this->add_events(Gdk::BUTTON_PRESS_MASK);
        this->signal_button_press_event().connect(sigc::mem_fun(*this, &Grille::on_button_press_event));


        //Clavier
        this->add_events(Gdk::KEY_PRESS_MASK);
        this->signal_key_press_event().connect(sigc::mem_fun(*this, &Grille::on_key_press_event));

        this->signal_draw().connect(sigc::mem_fun(*this, &Grille::on_draw));
    }

    virtual ~Grille() {}

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
        // tracer le background
        cr->set_source_rgb(1, 1, 1);
        cr->rectangle(0, 0, this->largeurPixel, this->hauteurPixel);
        cr->fill();

        //trace les lignes horizontales
        cr->set_source_rgb(0, 0, 0);
        for(int i = 0; i <= this->hauteur; i++) {
            cr->move_to(0, i*this->coteCase);
            cr->line_to(this->largeurPixel, i*this->coteCase);
            cr->stroke();
        }
        //trace les lignes verticales
        for(int i = 0; i <= this->largeur; i++) {
            cr->move_to(i*this->coteCase, 0);
            cr->line_to(i*this->coteCase, this->hauteurPixel);
            cr->stroke();
        }

        if(this->xCaseCercle != 0 && this->yCaseCercle != 0) {
            int xCercle, yCercle;
            
            xCercle = (i-1)*this->coteCase - this->coteCase/2;
            yCercle = (j-1)*this->coteCase - this->coteCase/2;

            //Tracer un cercle bleu de rayon 15 pixels sur la case ou on clique
            cr->set_source_rgb(0, 0, 1);
            cr->arc(xCercle, yCercle, 15, 0.0, 2 * M_PI);
            cr->fill();
        }

        return true;
    }

    bool on_button_press_event(GdkEventButton *event) override {
        //Si clic gauche
        if(event->button = GDK_BUTTON_PRIMARY) {
            this->xCaseCercle = event->x;
            this->yCaseCercle = event->y;

            cout << this->xCaseCercle << endl;

            DrawingArea::queue_draw();
        }
        return true;
    }
};