#include "headers/grille.hpp"

Grille::Grille(const int l, const int h, const bool algo, Labyrinth laby) : largeur(l), hauteur(h), lab(laby){
    this->coteCase = this->largeurPixel/l;

    this->xCercle = this->coteCase/2;
    this->yCercle = this->coteCase/2;

    this->set_size_request(this->largeurPixel, this->hauteurPixel);
    
    //Construction du labyrinthe
    if(algo) { this->lab.generateFusion(); }
    else { this->lab.generateAldousBroder(); }

    //Clavier
    this->add_events(Gdk::KEY_PRESS_MASK);
    this->signal_key_press_event().connect(sigc::mem_fun(*this, &Grille::on_key_press_event));

    this->signal_draw().connect(sigc::mem_fun(*this, &Grille::on_draw));

}

void Grille::finalScreen() { 
    //Création d'une fenêtre popup
    Gtk::Window* newWindow = new Gtk::Window();
    newWindow->set_default_size(300, 50);
    newWindow->set_title("Fin");

    // Create a vertical box container to hold the widgets
    Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    newWindow->add(*vbox);

    // Create a label widget to display a message
    Gtk::Label* message = Gtk::manage(new Gtk::Label("Bravo ! \n Tu as gagné, relance une partie quand tu le veux !"));
    vbox->pack_start(*message, Gtk::PACK_SHRINK);

    //Button pour quitter le jeu
    Gtk::Button* close = Gtk::manage(new Gtk::Button("Fermer"));
    close->signal_clicked().connect([] {Gtk::Main::quit();});
    vbox->pack_start(*close, Gtk::PACK_SHRINK);

    // Show the new window
    newWindow->show_all();
}

bool Grille::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // tracer le background
    cr->set_source_rgb(1, 1, 1);
    cr->rectangle(0, 0, this->largeurPixel, this->hauteurPixel);
    cr->fill();

    //Dessiner l'arrivée
    cr->set_source_rgb(0, 1, 0);
    cr->rectangle(this->largeurPixel-this->coteCase, this->hauteurPixel-this->coteCase, this->largeurPixel, this->hauteurPixel);
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

    //Dessin du labyrinthe
    cr->set_source_rgb(1, 1, 1);
    for(int j = 0; j < this->largeur; j++) {
        for(int i = 0; i < this->largeur; i++) {
            int actualCase = this->largeur*j + i;
            //Effacement des traits verticaux
            if(this->lab.isPath(actualCase, actualCase+1)) {
                cr->move_to((i+1)*this->coteCase, j*this->coteCase);
                cr->line_to((i+1)*this->coteCase, (j+1)*this->coteCase);
                cr->stroke();
            } //Effacement des traits horizontaux
            if(this->lab.isPath(actualCase, actualCase+this->largeur)) {
                cr->move_to(i*this->coteCase, (j+1)*this->coteCase);
                cr->line_to((i+1)*this->coteCase, (j+1)*this->coteCase);
                cr->stroke();
            }
        }
    }

    //Tracer un cercle bleu de rayon 15 pixels sur la case ou on clique
    cr->set_source_rgb(0, 0, 1);
    cr->arc(this->xCercle, this->yCercle, this->coteCase*0.4, 0.0, 2 * M_PI);
    cr->fill();

    int actCase = this->largeur * ((int) (this->yCercle / this->coteCase)) + 
                    ((int)(this->xCercle / this->coteCase));
    //Sur la dernière case (fin du jeu)
    if (actCase == this->largeur*this->hauteur -1) {
        finalScreen();
    }

    return true;
}

bool Grille::on_key_press_event(GdkEventKey* event) {
	guint keyvalue = event->keyval;

    int actualCase = this->largeur * ((int) (this->yCercle / this->coteCase)) + 
                    ((int)(this->xCercle / this->coteCase));
    
    switch (keyvalue) {
        case GDK_KEY_Up:
            //Pas sur la 1ere ligne et chemin
            if (this->yCercle > this->coteCase && this->lab.isPath(actualCase, actualCase-this->largeur)) { 
                this->yCercle -= this->coteCase;
            }
            break;

        case GDK_KEY_Down:
            //Pas sur la dernière ligne et chemin
            if (this->yCercle < (this->hauteur-1)*this->coteCase && this->lab.isPath(actualCase, actualCase+this->largeur)) {
                this->yCercle += this->coteCase;
            }
            break;

        case GDK_KEY_Left:
            //Pas sur la colonne de gauche et chemin
            if (actualCase%this->largeur != 0 && this->lab.isPath(actualCase, actualCase-1)) {
                this->xCercle -= this->coteCase;
            }
            break;

        case GDK_KEY_Right:
            //Pas sur la colonne de droite et chemin
            if ((actualCase+1)%this->largeur != 0 && this->lab.isPath(actualCase, actualCase+1)) {
                this->xCercle += this->coteCase;
            }
            break;
        default:
            break;
    }

    DrawingArea::queue_draw();
    
    return true;
}
