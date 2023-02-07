#ifndef TITACTOE_H_INCLUDED
#define TITACTOE_H_INCLUDED

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
    bool human_turn;    // bool qui est True si c'est le tour du joueur humain et false sinon
    bool getturn() const { return human_turn;}
    void setturn(bool human_turn2) {human_turn=human_turn2;}

    // Place un coup sur la grille
    bool PlacerCoup(int ligne, int colonne, char symbole) {
        if (ligne >= 0 && ligne <= 2 && colonne >= 0 && colonne <= 2 && grille_[ligne][colonne] == '-') {
            grille_[ligne][colonne] = symbole;
            return true;
        } else {
            return false;
        }
    }

    // Affiche l'�tat actuel de la grille
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
        // V�rifie les lignes
        for (int i = 0; i < 3; i++) {
            if (grille_[i][0] == symbole && grille_[i][1] == symbole && grille_[i][2] == symbole) {
                return true;
            }
        }

        // V�rifie les colonnes
        for (int i = 0; i < 3; i++) {
            if (grille_[0][i] == symbole && grille_[1][i] == symbole && grille_[2][i] == symbole) {
                return true;
            }
        }

        // V�rifie les diagonales
        if (grille_[0][0] == symbole && grille_[1][1] == symbole && grille_[2][2] == symbole) {
            return true;
        }
        if (grille_[0][2] == symbole && grille_[1][1] == symbole && grille_[2][0] == symbole) {
            return true;
        }

        return false;}

        // Retourne les coups possibles pour un joueur donné
        vector<pair<int, int>> getPossibleMoves() {
            vector<pair<int, int>> moves;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (grille_[i][j] == '-') {
                        moves.push_back({i, j});
                        }
                    }
                }

            return moves;
        }


private:
    char grille_[3][3];
};





//class Coup
//{
//public:
//    int ligne;
//    int colonne;
//    Coup(int ligne, int colonne) {
//        this->ligne = ligne;
//        this->colonne = colonne;
//    }
//};


// Cette classe est utilis�e pour stocker les coups jou�s par les joueurs ou les ordinateurs.
// Elle contient deux variables membres ligne et colonne qui repr�sentent la position o� le coup a �t� jou� sur la grille.
// La classe dispose d'un constructeur qui permet d'initialiser les variables membres.


#endif // TITACTOE_H_INCLUDED
