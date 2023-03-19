#include "tictactoe.h"
#include "MinMax.h"



bool Grille::PlacerCoup(int ligne, int colonne, char symbole) {
        if (ligne >= 0 && ligne <= 2 && colonne >= 0 && colonne <= 2 && grille_[ligne][colonne] == '-') {
            grille_[ligne][colonne] = symbole;
            return true;
        } else {
            return false;
        }
    }


void Grille::AfficherGrille() const {
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


bool Grille::EstPleine() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grille_[i][j] == '-') {
                    return false;
                }
            }
        }
        return true;
    }

bool Grille::EstGagnant(char symbole) const {
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


vector<pair<int,int>> Grille::CoupsPossibles() {
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

bool Grille::game_over() const{
    char X = 'X';
    char O = 'O';
    if (this->EstPleine()||this->EstGagnant(X)||this->EstGagnant(O)){
        return true;}
    return false;
    }

int Grille::valeur_tictactoe(){
    char X='X';
    char O='O';
    int v;
    if (this->EstGagnant(X)) {v = std::numeric_limits<int>::max();}
    else if (this->EstGagnant(O)) {v = std::numeric_limits<int>::min();}

    else {v = 0;}
    return v;

    }


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
        int ligne, colonne;
        grille.AfficherGrille();
        // Tour du joueur
        grille.setTour(true);

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
        vector<pair<int, int>> moves=grille.CoupsPossibles();   // vecteur des coups possibles
        pair<int, int> coup;
        int L = moves.size();
        // pour faire des coups aléatoires
//        std::srand(std::time(0));
//        int randomIndex = std::rand() % grille.CoupsPossibles().size();
//        pair <int,int> v = grille.CoupsPossibles()[randomIndex];
//        ligne = v.first;
//        colonne = v.second;
        //cout << "ligne = " << ligne << endl;

        //pair <int,int> v = meilleur_coup(grille,20);
        pair <int,int> v = meilleur_coup_alphabeta(grille,20);
        ligne = v.first;
        colonne = v.second;
        cout << "Coup jouer : Ligne=" << ligne << "; colonne=" << colonne<< endl;
        grille.PlacerCoup(ligne, colonne, symbole_ordi);


        if (grille.EstGagnant(symbole_ordi)) {
            grille.AfficherGrille();
            cout << "L'ordinateur gagne !" << endl;
            break;
        }



    }
}


