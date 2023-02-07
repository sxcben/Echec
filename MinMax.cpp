#include <iostream>
#include <limits>


int valeur_tictactoe(Board P)
{
    int v;
    if victoire(P) {v = std::numeric_limits<int>::max();}
    if match_nul(P) {v = 0;}
    if defaite(P) {v = std::numeric_limits<int>::min();}

    return v

}

int valeur(Board P, int alpha, int beta)
{
    int v;
    int val;
    int cont;

    if victoire(P) {v = std::numeric_limits<int>::max();}
    if match_nul(P) {v = 0;}
    if defaite(P) {v = std::numeric_limits<int>::min();}

    for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                    if (echiquier_[i][j] != nullptr && echiquier_[x][y].couleur ==  )

}

int MinMax(Board P, int profondeur)
{
    int m;
    int MinMax;
    if (partie_terminee(P)||profondeur==0)  {return valeur(P);}

    if (Position.joueur=="humain")
    {
        m = std::numeric_limits<int>::min();

        for  //parcourt tous les coups possibles
        {
            MinMax = MinMax(, profondeur-1);
            if (MinMax > m)

                {m=MinMax};
        }
        return m;
    }
    if (Position.joueur=="ordi")
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
int AlphaBeta(Board P, int profondeur, int alpha, int beta)
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
