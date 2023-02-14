#ifndef MINMAX_H_INCLUDED
#define MINMAX_H_INCLUDED


#include <iostream>
#include <limits>
#include "morpion.h"
int profondeur_max=10;

int valeur_tictactoe(Grille P,char s='X')
{
    int v;
    if (P.EstGagnant(s)) {v = std::numeric_limits<int>::max();}
    if (P.EstPleine()) {v = 0;}
    else {v = std::numeric_limits<int>::min();}
    return v;
}

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

vector<int> MinMax(Grille P, int profondeur, bool tour, char X='X',char O='O')
{
    int m;
    vector <int> v = {m,0,0};
    pair<int,int> choix;
    int Minmax;
    if (P.EstPleine()||P.EstGagnant(X)||P.EstGagnant(O)||profondeur==0)  {
        v = {valeur_tictactoe(P,X),0,0};
        return v;}

    if (tour)  // si c'est le tour du joueur humain
    {
        m = std::numeric_limits<int>::min();
        vector<pair<int, int>> moves=P.CoupsPossibles();   // vecteur des coups possibles
        pair<int, int> coup;
        int L = moves.size();
        for (int i=0;i<L;i++)
        {
            Grille G = P;
            coup = moves[i];
            G.PlacerCoup(coup.first,coup.second,'X');

            Minmax = MinMax(G, profondeur-1, !tour, X,O)[0];
            if (Minmax > m)

                {m=Minmax;}
            }

        return v;
    }
    if (!tour)
    {
        m = std::numeric_limits<int>::max();
        vector<pair<int, int>> moves=P.CoupsPossibles();   // vecteur des coups possibles
        pair<int, int> coup;
        int L = moves.size();
        for (int i=0;i<L;i++)
        {
            Grille G = P;
            coup = moves[i];
            G.PlacerCoup(coup.first,coup.second,'O');
            Minmax = MinMax(G, profondeur-1, !tour,X,O)[0];
            if (Minmax < m)

            {m=Minmax;

            if (profondeur==profondeur_max){
                    choix=coup;
                    v = {m,choix.first,choix.second};
                    }

        }
        return v;
    }

}

//Au début, alpha=-inf, beta=+inf
//int AlphaBeta(Grille P, int profondeur, bool tour, int alpha, int beta, char X='X',char O='O')
//{
//    int score;
//     if (P.EstPleine()||P.EstGagnant(X)||P.EstGagnant(O)||profondeur==0)  {return valeur_tictactoe(P,O);}
//
//    if (tour) // si c'est au joueur humain de jouer
//    {
//        vector<pair<int, int>> moves=P.CoupsPossibles();   // vecteur des coups possibles
//        pair<int, int> coup;
//        int L = moves.size();
//        for (int i=0;i<L;i++)
//        {
//            Grille G = P;
//            coup = moves[i];
//            G.PlacerCoup(coup.first,coup.second,'X');
//            score = AlphaBeta(G, profondeur-1, !tour, alpha, beta);
//            if (score > alpha) {alpha = score;} //on a trouvé un meilleur coup
//            if (alpha >= beta) {return alpha;} // on coupe le noeud
//        }
//        return alpha; //meilleur coup
//
//    }
//
//        if (!tour)
//    {
//        vector<pair<int, int>> moves=P.CoupsPossibles();   // vecteur des coups possibles
//        pair<int, int> coup;
//        int L = moves.size();
//        for (int i=0;i<L;i++)
//        {
//            Grille G = P;
//            coup = moves[i];
//            G.PlacerCoup(coup.first,coup.second,'X');
//            score = AlphaBeta(G, profondeur-1, !tour, alpha, beta);
//            if (score < beta) {beta = score;} //l'ordi a trouvé un "pire" coup
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
