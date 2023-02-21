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
    bool PlacerCoup(int ligne, int colonne, char symbole) {
        if (ligne >= 0 && ligne <= 2 && colonne >= 0 && colonne <= 2 && grille_[ligne][colonne] == '-') {
            grille_[ligne][colonne] = symbole;
            return true;
        } else {
            return false;
        }
    }

    // Affiche l'etat actuel de la grille
    void AfficherGrille() const {
        cout << endl;
        cout << "Etat de la grille : " << endl;
        cout << endl;
        for (int i = 0; i < 3; i++) {
            cout << "       " ;
            for (int j = 0; j < 3; j++) {
                cout << grille_[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Retourne true si une grille est remplie et false sinon
    bool EstPleine() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grille_[i][j] == '-') {
                    return false;
                }
            }
        }
        return true;
    }

    // Retourne true si une grille est gagnante et false sinon
    bool EstGagnant(char symbole) const {
        // Verifie les lignes
        for (int i = 0; i < 3; i++) {
            if (grille_[i][0] == symbole && grille_[i][1] == symbole && grille_[i][2] == symbole) {
                return true;
            }
        }

        // Verifie les colonnes
        for (int i = 0; i < 3; i++) {
            if (grille_[0][i] == symbole && grille_[1][i] == symbole && grille_[2][i] == symbole) {
                return true;
            }
        }

        // Verifie les diagonales
        if (grille_[0][0] == symbole && grille_[1][1] == symbole && grille_[2][2] == symbole) {
            return true;
        }
        if (grille_[0][2] == symbole && grille_[1][1] == symbole && grille_[2][0] == symbole) {
            return true;
        }

        return false;
    }

    // A qui le tour
    bool TourHumain;
    bool getTour() const {return TourHumain;}
    void setTour(bool Tour) {TourHumain=Tour;}

    // Coups possibles
    vector<pair<int,int>> CoupsPossibles() {
        vector<pair<int,int>> Coups;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grille_[i][j] == '-') {
                    Coups.push_back({i,j});
                }
            }
        }
        return Coups;
    }

private:
    char grille_[3][3];
};

void Jouer(Grille grille);

#endif // TICTACTOE_H_INCLUDED
