#ifndef TICTACTOE_H_INCLUDED
#define TICTACTOE_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

class TicTacToe {
    private:
        char plateau[3][3];
        char joueur;
    public:
        TicTacToe() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    plateau[i][j] = ' ';
                }
            }
            joueur = 'X';
        }

        void afficher_plateau() {
            cout << " " << endl;
            cout << "  -----------" << endl;
            cout << "  Tic Tac Toe" << endl;
            cout << "  -----------" << endl;
            for (int i = 0; i < 3; i++) {
                cout << " | ";
                for (int j = 0; j < 3; j++) {
                    cout << plateau[i][j] << " | ";
                }
                cout << endl;
            }
            cout << " " << endl;
        }

        void jouer() {
            while (!partie_terminee()) {
                afficher_plateau();
                int ligne, colonne;
                cout << "Entrez la ligne (0, 1, 2) pour votre prochain coup : ";
                cin >> ligne;
                cout << "Entrez la colonne (0, 1, 2) pour votre prochain coup : ";
                cin >> colonne;
                jouer_coup(ligne, colonne);
                joueur = (joueur == 'X') ? 'O' : 'X';
            }
            afficher_plateau();
            if (match_nul()) {
                cout << "Match nul :(" << endl;
            } else {
                cout << "Victoire du joueur " << joueur << endl;
            }
        }

        void jouer_coup(int ligne, int colonne) {
            if (plateau[ligne][colonne] != ' ') {
                cout << " " << endl ;
                cout << "COUP NON VALIDE !! VEUILLEZ RECOMMENCER" << endl;
                joueur = (joueur == 'X') ? 'O' : 'X';
            }
            plateau[ligne][colonne] = joueur;

        }

        bool partie_terminee() {
            return victoire() || match_nul();
        }

        bool victoire() {
            // vérifie les lignes
            for (int i = 0; i < 3; i++) {
                if (plateau[i][0] == joueur && plateau[i][1] == joueur && plateau[i][2] == joueur) {
                    return true;
                }
            }

            // vérifie les colonnes
            for (int i = 0; i < 3; i++) {
                if (plateau[0][i] == joueur && plateau[1][i] == joueur && plateau[2][i] == joueur) {
                    return true;
                }
            }

            // vérifie les diagonales
            if (plateau[0][0] == joueur && plateau[1][1] == joueur && plateau[2][2] == joueur) {
                return true;
            }
            if (plateau[0][2] == joueur && plateau[1][1] == joueur && plateau[2][0] == joueur) {
                return true;
            }

            return false;
        }

        bool match_nul() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (plateau[i][j] == ' ') {
                        return false;
                    }
                }
            }
            return true;
        }
};

//int main()
//{
//    TicTacToe jeu;
//    jeu.jouer();
//    return 0;
//}

#endif // TICTACTOE_H_INCLUDED
