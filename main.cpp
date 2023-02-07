#include "tictactoe2.h"

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <array>
#include <ctime>
#include <cstdlib>

using namespace std;

// tictactoe2 humain vs ordi
int main()
{
    Grille grille;
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
        int ligne, colonne;
        cout << "Entrez votre coup (ligne colonne) : ";
        cin >> ligne >> colonne;
        while (!grille.PlacerCoup(ligne, colonne, symbole_joueur)) {
            cout << "Coup non valide, entrez de nouveau : ";
            cin >> ligne >> colonne;
        }
        if (grille.EstGagnant(symbole_joueur)) {
            grille.AfficherGrille();
            //cout << "Le joueur gagne !" << endl;
            cout << "Bravo " << nom_joueur << ", vous avez battu l'ordi !" << endl;
            break;
        }
        if (grille.EstPleine()) {
            grille.AfficherGrille();
            cout << "Match nul !" << endl;
            break;
        }

        // Tour de l'ordinateur
        ligne = rand() % 3;
        colonne = rand() % 3;
        while (!grille.PlacerCoup(ligne, colonne, symbole_ordi)) {
            ligne = rand() % 3;
            colonne = rand() % 3;
        }
        if (grille.EstGagnant(symbole_ordi)) {
            grille.AfficherGrille();
            cout << "L'ordinateur gagne !" << endl;
            break;
        }
    }

    return 0;
}
