#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "echecs.hpp"

using namespace std;

//int main() {
//
//    char rejouer = 'O';
//    while (rejouer == 'O') {
//
//        Echiquier* echiquier = new Echiquier();
//        bool joueurBlanc = true;
//
//        cout << endl;
//        cout << "Bienvenue dans le jeu d'echecs : joueur (blancs) vs ordinateur (noirs) !" << endl;
//        cout << endl;
//
//        string nom_joueur;
//        cout << "Entrez votre nom : ";
//        cin >> nom_joueur;
//
//        string nom_joueur2 = "ordinateur";
//
//        while(!echiquier->Victoire(joueurBlanc) && !echiquier->Victoire(!joueurBlanc) && !echiquier->Nul()) {
//            echiquier->AfficherEchiquier(nom_joueur,nom_joueur2);
//            if(joueurBlanc) {
//                cout << endl;
//                cout << "A vous de jouer " << nom_joueur << "..." << endl;
//                string position1, position2;
//                cout << "Coordonnees de la piece a deplacer (ex: E2) : ";
//                cin >> position1;
//                int y1 = position1[0] - 'A' + 1;
//                int x1 = '9' - position1[1];
//                cout << "Coordonnees de la case de destination (ex: E4) : ";
//                cin >> position2;
//                int y2 = position2[0] - 'A' + 1;
//                int x2 = '9' - position2[1];
//                if(!echiquier->DeplacerPiece(x1, y1, x2, y2, joueurBlanc)) {
//                    cout << endl;
//                    cout << "Deplacement invalide..." << endl;
//                    continue;
//                }
//            }
//            else {
//                cout << endl;
//                cout << "Tour de l'ordinateur..." << endl;
//
////                vector<pair<pair<int,int>,pair<int,int>>> cp = echiquier->CoupsPossibles(false);
////                srand(time(nullptr));
////                int ind = rand() % cp.size();
////                pair<pair<int,int>,pair<int,int>> coup = cp[ind];
////                int x1 = coup.first.first;
////                int y1 = coup.first.second;
////                int x2 = coup.second.first;
////                int y2 = coup.second.second;
////                if(!echiquier->DeplacerPiece(x1, y1, x2, y2, joueurBlanc)) {
////                    cout << "Deplacement invalide." << endl;
////                    continue;
////                }
//
//                auto meilleurCoup = MeilleurCoup(echiquier, 3, false);
//                int x1 = meilleurCoup.first.first;
//                int y1 = meilleurCoup.first.second;
//                int x2 = meilleurCoup.second.first;
//                int y2 = meilleurCoup.second.second;
//                echiquier->DeplacerPiece(x1, y1, x2, y2, false);
//
//            }
//            echiquier->PionDame();
//            joueurBlanc = !joueurBlanc;
//        }
//        echiquier->AfficherEchiquier(nom_joueur,nom_joueur2);
//        if(echiquier->Victoire(true)) {
//            cout << endl;
//            cout << "Felicitations " << nom_joueur << ", vous avez gagne !" << endl;
//        }
//        else if(echiquier->Victoire(false)) {
//            cout << endl;
//            cout << "L'ordinateur a gagne, desole " << nom_joueur << "..." << endl;
//        }
//        else {
//            cout << endl;
//            cout << "Partie nulle." << endl;
//        }
//        delete echiquier;
//
//        cout << endl;
//        cout << "Rejouer ? (O ou N) : ";
//        cin >> rejouer;
//        if(rejouer == 'O') {
//            continue;
//        }
//
//    }
//    return 0;
//}

int main() {

    char rejouer = 'O';
    while (rejouer == 'O') {

        Echiquier* echiquier = new Echiquier();
        bool joueurBlanc = true;

        cout << endl;
        cout << "Bienvenue dans le jeu d'echecs : joueur 1 (blancs) vs joueur 2 (noirs) !" << endl;
        cout << endl;

        string nom_joueur1;
        cout << "Entrez votre nom (blancs) : ";
        cin >> nom_joueur1;
        cout << endl;

        string nom_joueur2;
        cout << "Entrez votre nom (noirs) : ";
        cin >> nom_joueur2;

        while(!echiquier->Victoire(joueurBlanc) && !echiquier->Victoire(!joueurBlanc) && !echiquier->Nul()) {
            echiquier->AfficherEchiquier(nom_joueur1,nom_joueur2);
            if(joueurBlanc) {
                cout << endl;
                cout << "A vous de jouer " << nom_joueur1 << "..." << endl;
                string position1B, position2B;
                cout << "Coordonnees de la piece a deplacer (ex: E2) : ";
                cin >> position1B;
                int y1B = position1B[0] - 'A' + 1;
                int x1B = '9' - position1B[1];
                cout << "Coordonnees de la case de destination (ex: E4) : ";
                cin >> position2B;
                int y2B = position2B[0] - 'A' + 1;
                int x2B = '9' - position2B[1];
                if(!echiquier->CoupValide(x1B, y1B, x2B, y2B, joueurBlanc) || !echiquier->DeplacerPiece(x1B, y1B, x2B, y2B, joueurBlanc)) {
                    cout << endl;
                    cout << "Deplacement invalide..." << endl;
                    continue;
                }
            }
            else {
                cout << endl;
                cout << "A vous de jouer " << nom_joueur2 << "..." << endl;
                string position1, position2;
                cout << "Coordonnees de la piece a deplacer (ex: E2) : ";
                cin >> position1;
                int y1 = position1[0] - 'A' + 1;
                int x1 = '9' - position1[1];
                cout << "Coordonnees de la case de destination (ex: E4) : ";
                cin >> position2;
                int y2 = position2[0] - 'A' + 1;
                int x2 = '9' - position2[1];
                if(!echiquier->CoupValide(x1, y1, x2, y2, joueurBlanc) || !echiquier->DeplacerPiece(x1, y1, x2, y2, joueurBlanc)) {
                    cout << endl;
                    cout << "Deplacement invalide..." << endl;
                    continue;
                }
            }
            echiquier->PionDame();
            joueurBlanc = !joueurBlanc;
        }
        echiquier->AfficherEchiquier(nom_joueur1,nom_joueur2);
        if(echiquier->Victoire(true)) {
            cout << endl;
            cout << "Felicitations " << nom_joueur1 << ", vous avez battu " << nom_joueur2 << " !" << endl;
        }
        else if(echiquier->Victoire(false)) {
            cout << endl;
            cout << "Felicitations " << nom_joueur2 << ", vous avez battu " << nom_joueur1 << " !" << endl;
        }
        else {
            cout << endl;
            cout << "Partie nulle." << endl;
        }
        delete echiquier;

        cout << endl;
        cout << "Rejouer ? (O ou N) : ";
        cin >> rejouer;
        if(rejouer == 'O') {
            continue;
        }

    }
    return 0;
}
