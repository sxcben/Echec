#ifndef MINMAX_H_INCLUDED
#define MINMAX_H_INCLUDED

#include <iostream>
#include <limits>
#include "tictactoe.h"
using namespace std;



//int valeur(Grille P, int alpha, int beta)
//{
//    int v;
//    int val;
//    int cont;
//
//    if victoire(P) {v = std::numeric_limits<int>::max();}
//    if match_nul(P) {v = 0;}
//    if defaite(P) {v = std::numeric_limits<int>::min();}
//
//    for (int i = 0; i < 8; ++i) {
//            for (int j = 0; j < 8; ++j) {
//                    if (echiquier_[i][j] != nullptr && echiquier_[x][y].couleur ==  )
//
//}




int MinMax(Grille P, int profondeur, bool tour, char X='X', char O='O') {
    int Minmax;

    vector<pair<int, int>> moves = P.CoupsPossibles(); // vecteur des coups possibles
    int L = moves.size();

    if (P.game_over() || profondeur == 0) {
        return P.valeur_tictactoe();
    }

    if (tour) { // si c'est le tour du joueur humain
        Minmax = std::numeric_limits<int>::min();
        for (int i = 0; i < L; i++) {
            Grille G = P;
            G.PlacerCoup(moves[i].first, moves[i].second, 'X');
            Minmax = std::max(Minmax, MinMax(G, profondeur - 1, !tour, X, O));
        }
        return Minmax;
    }
    else {
        Minmax = std::numeric_limits<int>::max();
        for (int i = 0; i < L; i++) {
            Grille G = P;
            G.PlacerCoup(moves[i].first, moves[i].second, 'O');
            Minmax = std::min(Minmax, MinMax(G, profondeur - 1, !tour, X, O));
        }
        return Minmax;
    }
    return 0;
}


pair<int,int> meilleur_coup(Grille P,int profondeur)
{
    int m = std::numeric_limits<int>::max();
    vector<pair<int, int>> moves=P.CoupsPossibles();   // vecteur des coups possibles
    pair<int, int> choix;
    int L = moves.size();
    char X='X';
    char O='O';
    for (int i=0;i<L;i++)
    {
        Grille G = P;
        G.PlacerCoup(moves[i].first,moves[i].second,'O');
        cout << "ligne=" << moves[i].first << "; colonne" << moves[i].second << "; valeur= " << MinMax(G,profondeur,1,X,O) << endl;
        if (MinMax(G,profondeur,1,X,O)<m)
        {
            m=MinMax(G,profondeur,1,X,O);
            choix=moves[i];
        }

    }
    return choix;


}







//Au debut, alpha=-inf, beta=+inf
//int AlphaBeta(Grille P, int profondeur, bool tour, int alpha, int beta, char X='X',char O='O')
//{
//    int score;
//    vector<pair<int, int>> moves = P.CoupsPossibles(); // vecteur des coups possibles
//    int L = moves.size();
//
//    if (P.game_over() || profondeur == 0) {
    //    return P.valeur_tictactoe();
//   }
//
//    if (tour) // si c'est au joueur humain de jouer
//    {
//        score = std::numeric_limits<int>::min();
//
//
//        for (int i=0;i<L;i++)
//        {
//            Grille G = P;
//            G.PlacerCoup(moves[i].first, moves[i].second, 'X');
//            score = std::max(score, AlphaBeta(G, profondeur - 1, !tour, alpha, beta, X, O));
//
//            if (score > alpha) {alpha = score;} //on a trouve un meilleur coup
//            if (alpha >= beta) {return alpha;} // on coupe le noeud
//        }
//        return alpha; //meilleur coup
//
//    }
//
//        if (!tour)
//    {
//        score = std::numeric_limits<int>::min();
//
//
//        for (int i=0;i<L;i++)
//        {
//            Grille G = P;
//            G.PlacerCoup(moves[i].first, moves[i].second, 'X');
//            score = std::max(score, AlphaBeta(G, profondeur - 1, !tour, alpha, beta, X, O));
//
//            if (score < beta) {beta = score;} //l'ordi a trouve un "pire" coup
//            if (alpha >= beta) {return alpha;} // on coupe le noeud
//        }
//        return beta; //meilleur coup pour l'ordi
//
//    }
//
//}
//
//
#endif // MINMAX_H_INCLUDED
