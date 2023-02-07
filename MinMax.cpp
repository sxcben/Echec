#include <iostream>
#include <limits>
#include "titactoe.h"


int valeur_tictactoe(Grille P,char s='O')
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

int MinMax(Grille P, int profondeur,char X='X',char O='O')
{
    int m;
    int MinMax;
    if (P.EstPleine()||P.EstGagnant(X)||P.EstGagnant(O)||profondeur==0)  {return valeur_tictactoe(P,O);}

    if (P.getturn())  // si c'est le tour du jour humain
    {
        m = std::numeric_limits<int>::min();
        vector<pair<int, int>> moves=P.getPossibleMoves();   // vecteur des coups possibles
        pair<int, int> coup;
        int L = moves.size();
        for (int i=0;i<L;i++)
        {
            coup = moves[i];

            MinMax = MinMax(, profondeur-1);
            if (MinMax > m)

                {m=MinMax};
        }
        return m;
    }
    if (!P.getturn())
    {
        m = std::numeric_limits<int>::max();
        for
        {
            MinMax = MinMax(, profondeur-1);
            if (MinMax < m)

            {m=MinMax;}

        }
        return m;
    }

}

//Au début, alpha=-inf, beta=+inf
int AlphaBeta(Grille P, int profondeur, int alpha, int beta)
{
    int score;
    if (terminale(P)||profondeur==0)  {return valeur(P);}

    if (Position.joueur=="humain")
    {
        for
        {
            score = AlphaBeta(, profondeur-1, alpha, beta);
            if (score > alpha) {alpha = score;} //on a trouvé un meilleur coup
            if (alpha >= beta) {return alpha;} // on coupe le noeud
        }
        return alpha; //meilleur coup

    }

        if (Position.joueur=="ordi")
    {
        for
        {
            score = AlphaBeta(, profondeur-1, alpha, beta);
            if (score < beta) {beta = score;} //l'ordi a trouvé un "pire" coup
            if (alpha >= beta) {return alpha;} // on coupe le noeud
        }
        return beta; //meilleur coup pour l'ordi

    }

}
