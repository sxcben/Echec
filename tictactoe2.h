#ifndef TICTACTOE2_H_INCLUDED
#define TICTACTOE2_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>


using namespace std;
int profondeur_max=10;
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

void Jouer(Grille grille) {
    char symbole_joueur = 'X';
    char symbole_ordi = 'O';

    srand(time(NULL));

    cout << endl;
    cout << "Bienvenue dans le jeu TicTacToe : joueur (X) vs ordinateur (O) !" << endl;
    cout << endl;

    string nom_joueur;
    cout << "Entrez votre nom : ";
    cin >> nom_joueur;

    while (!grille.EstPleine() && !grille.EstGagnant(symbole_joueur) && !grille.EstGagnant(symbole_ordi)) {
        grille.AfficherGrille();
        // Tour du joueur
        grille.setTour(true);
        int ligne, colonne;
        cout << "Entrez votre coup (ligne colonne) : ";
        cin >> ligne >> colonne;
        while (!grille.PlacerCoup(ligne, colonne, symbole_joueur)) {
            cout << "Coup non valide, entrez de nouveau : ";
            cin >> ligne >> colonne;
        }
        if (grille.EstGagnant(symbole_joueur)) {
            grille.AfficherGrille();
            cout << "Bravo " << nom_joueur << ", vous avez battu l'ordi !" << endl;
            break;
        }
        if (grille.EstPleine()) {
            grille.AfficherGrille();
            cout << "Match nul !" << endl;
            break;
        }

        // Tour de l'ordinateur
        grille.setTour(false);
        vector <int> v = MinMax(grille,profondeur_max,grille.getTour,symbole_joueur,symbole_ordi);
        ligne = v[1];
        colonne = v[2]
        grille.PlacerCoup(ligne, colonne, symbole_ordi)

        if (grille.EstGagnant(symbole_ordi)) {
            grille.AfficherGrille();
            cout << "L'ordinateur gagne !" << endl;
            break;
        }
    }
}
