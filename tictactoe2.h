#ifndef TICTACTOE2_H_INCLUDED
#define TICTACTOE2_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include <vector>

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

    // Affiche l'état actuel de la grille
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
        // Vérifie les lignes
        for (int i = 0; i < 3; i++) {
            if (grille_[i][0] == symbole && grille_[i][1] == symbole && grille_[i][2] == symbole) {
                return true;
            }
        }

        // Vérifie les colonnes
        for (int i = 0; i < 3; i++) {
            if (grille_[0][i] == symbole && grille_[1][i] == symbole && grille_[2][i] == symbole) {
                return true;
            }
        }

        // Vérifie les diagonales
        if (grille_[0][0] == symbole && grille_[1][1] == symbole && grille_[2][2] == symbole) {
            return true;
        }
        if (grille_[0][2] == symbole && grille_[1][1] == symbole && grille_[2][0] == symbole) {
            return true;
        }

        return false;
    }

private:
    char grille_[3][3];
};


class Coup
{
public:
    int ligne;
    int colonne;
    Coup(int ligne, int colonne) {
        this->ligne = ligne;
        this->colonne = colonne;
    }
};

// Cette classe est utilisée pour stocker les coups joués par les joueurs ou les ordinateurs.
// Elle contient deux variables membres ligne et colonne qui représentent la position où le coup a été joué sur la grille.
// La classe dispose d'un constructeur qui permet d'initialiser les variables membres.



#endif // TICTACTOE2_H_INCLUDED
