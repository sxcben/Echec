#ifndef TICTACTOE_H_INCLUDED
#define TICTACTOE_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>

using namespace std;

class Grille
{
public:
    Grille() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                grille_[i][j] = '-';
            }
        }
    }

    // Place un coup sur la grille
    bool PlacerCoup(int ligne, int colonne, char symbole);

    // Affiche l'etat actuel de la grille
    void AfficherGrille() const ;

    // Retourne true si une grille est remplie et false sinon
    bool EstPleine() const ;

    // Retourne true si une grille est gagnante et false sinon
    bool EstGagnant(char symbole) const ;

    // A qui le tour
    bool TourHumain;
    bool getTour() const {return TourHumain;}
    void setTour(bool Tour) {TourHumain=Tour;}

    // Coups possibles
    vector<pair<int,int>> CoupsPossibles() ;

    //vaut 1 si la partie est terminée et 0 sinon
    bool game_over() const;
    int valeur_tictactoe(); //penser à rajouter la profondeur en paramètre pour échec

private:
    char grille_[3][3];
};

void Jouer(Grille grille);

#endif // TICTACTOE_H_INCLUDED
