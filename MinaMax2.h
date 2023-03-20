#ifndef MINAMAX2_H_INCLUDED
#define MINAMAX2_H_INCLUDED

#include <iostream>
#include <limits>
#include "echec.h"
using namespace std;
#include <chrono>

// Définir le temps limite en millisecondes
int tempsMax = 800;

//Au debut, alpha=-inf, beta=+inf
int alpha1 = std::numeric_limits<int>::min();
int beta1 = std::numeric_limits<int>::max();
// Fonction de base

int MinMax(Echiquier* E, int profondeur, bool tour) {
    int Minmax;

    vector<pair<pair<int, int>,pair <int,int>>> moves = E->CoupsPossibles(tour); // vecteur des coups possibles
    int L = moves.size();

    if (E->Victoire(true) ||E->Victoire(false) ||E->Nul() || profondeur == 0) {
        return E->Evaluation();
    }

    if (tour) { // si c'est le tour du joueur humain
        Minmax = std::numeric_limits<int>::min();
        for (int i = 0; i < L; i++) {
            Echiquier *G = new Echiquier(*E);
            G->DeplacerPiece(moves[i].first.first,moves[i].first.second,moves[i].second.first, moves[i].second.second, tour);
            Minmax = std::max(Minmax, MinMax(G, profondeur - 1, !tour));
        }
        return Minmax;
    }
    else {
        Minmax = std::numeric_limits<int>::max();
        for (int i = 0; i < L; i++) {
            Echiquier *G = new Echiquier(*E);
            G->DeplacerPiece(moves[i].first.first,moves[i].first.second,moves[i].second.first, moves[i].second.second, tour);
            Minmax = std::min(Minmax, MinMax(G, profondeur - 1, !tour));
        }
        return Minmax;
    }
    return 0;
}

// Elagage alpha-beta

int AlphaBeta(Echiquier* E, int profondeur, bool tour, int alpha, int beta, int tempsMax) {
    int valeur;
    auto tdebut = chrono::high_resolution_clock::now();
    if (tempsMax<0)   // finir si le temps est dépassé
    {
        return E->Evaluation();
    }
    vector<pair<pair<int, int>,pair <int,int>>> moves = E->CoupsPossibles(tour); // vecteur des coups possibles
    int L = moves.size();

    if (E->Victoire(true) ||E->Victoire(false) ||E->Nul() || profondeur == 0) {
        return E->Evaluation();
    }

    if (tour) { // si c'est le tour du joueur humain
        valeur = std::numeric_limits<int>::min();
        for (int i = 0; i < L; i++) {
            Echiquier *G = new Echiquier(*E);
            G->DeplacerPiece(moves[i].first.first,moves[i].first.second,moves[i].second.first, moves[i].second.second, tour);
            auto tfin = chrono::high_resolution_clock::now();
            auto duree = chrono::duration_cast<chrono::milliseconds>(tfin - tdebut).count();
            tempsMax=tempsMax-duree;
            int eval = AlphaBeta(G, profondeur - 1, !tour, alpha, beta,tempsMax);
            valeur = std::max(valeur, eval);
            alpha = std::max(alpha,eval);
            if (beta<=alpha)
            {
                break;
            }

        }
        //return valeur;
    }
    else {
        valeur = std::numeric_limits<int>::max();
        for (int i = 0; i < L; i++) {
            Echiquier *G = new Echiquier(*E);
            G->DeplacerPiece(moves[i].first.first,moves[i].first.second,moves[i].second.first, moves[i].second.second, tour);
            auto tfin = chrono::high_resolution_clock::now();
            auto duree = chrono::duration_cast<chrono::milliseconds>(tfin - tdebut).count();
            tempsMax=tempsMax-duree;
            int eval = AlphaBeta(G, profondeur - 1, !tour, alpha, beta,tempsMax);
            valeur = std::min(valeur, eval);
            beta = std::min(beta,eval);
            if (beta<=alpha)
            {
                break;
            }
        }
        //return valeur;
    }

    return valeur;

}

// Choix du meilleur coup avec l'algorithme de base

pair<pair<int, int>,pair <int,int>> meilleur_coup(Echiquier* E, int profondeur) {
    int m = std::numeric_limits<int>::max();
    vector<pair<pair<int, int>,pair <int,int>>> moves = E->CoupsPossibles(false); // vecteur des coups possibles
    pair<pair<int, int>,pair <int,int>> choix = moves[0];
    int L = moves.size();

    for (int i=0;i<L;i++)
    {
        Echiquier *G = new Echiquier(*E);
        G->DeplacerPiece(moves[i].first.first,moves[i].first.second,moves[i].second.first, moves[i].second.second, false);
        if (MinMax(G,profondeur,true)<m)
        {
            m=MinMax(G,profondeur,true);
            choix=moves[i];
        }

    }
    return choix;


}

// Choix du meilleur coup avec la variante

pair<pair<int, int>,pair <int,int>> meilleur_coup_alphabeta(Echiquier* E,int profondeur) {
    int m = std::numeric_limits<int>::max();
    vector<pair<pair<int, int>,pair <int,int>>> moves = E->CoupsPossibles(false); // vecteur des coups possibles
    pair<pair<int, int>,pair <int,int>> choix = moves[0];
    int L = moves.size();

    for (int i=0;i<L;i++)
    {
        Echiquier *G = new Echiquier(*E);
        G->DeplacerPiece(moves[i].first.first,moves[i].first.second,moves[i].second.first, moves[i].second.second, false);
        if (AlphaBeta(G,profondeur,true,alpha1,beta1,tempsMax)<m)
        {
            m=AlphaBeta(G,profondeur,true,alpha1,beta1,tempsMax);
            choix=moves[i];
        }

    }
    return choix;
}

#endif // MINAMAX2_H_INCLUDED
