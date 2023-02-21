#include "tictactoe.h"
#include "MinMax.h"

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
        vector <int> v = MinMax(grille,10,grille.getTour(),symbole_joueur,symbole_ordi);
        ligne = v[1];
        colonne = v[2];
        grille.PlacerCoup(ligne, colonne, symbole_ordi);

        if (grille.EstGagnant(symbole_ordi)) {
            grille.AfficherGrille();
            cout << "L'ordinateur gagne !" << endl;
            break;
        }
    }
}