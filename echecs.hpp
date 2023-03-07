#ifndef ECHECS_HPP_INCLUDED
#define ECHECS_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <chrono>

using namespace std;

enum TypePiece {ROI, DAME, TOUR, FOU, CAVALIER, PION, VIDE};

class Piece {
private:
    // Type de la piece
    TypePiece type_;
    // Booleen indiquant la couleur de la piece
    bool estBlanche_;
    // Valeur de la piece (entre 0 et 9)
    int valeur_;
    // Vecteur des deplacements possibles de la piece
    vector<pair<int,int>> deplacements_;
    // Position de la piece sur l'echiquier
    pair<int,int> position_;
    // Nombre de deplacements realises par la piece
    int nbDeplacements_;

public:

    // Constructeur de piece

    Piece(TypePiece tp, bool estBlanche) : type_(tp), estBlanche_(estBlanche) {
        if(tp == ROI){
            valeur_ = 0;
            // Le roi ne peut bouger que d'une case autour de lui, sauf s'il veut roque
            deplacements_ = {{-1,-1},{-1,0},{-1,1},{0,-2},{0,-1},{0,1},{0,2},{1,-1},{1,0},{1,1}};
        }
        if(tp == DAME || tp == TOUR){
            valeur_ = 5;
            // Le fou ne peut bouger qu'en diagonale, la dame peut
            for(int i=1;i<8;i++){
                deplacements_.push_back({-i,0});
                deplacements_.push_back({0,-i});
                deplacements_.push_back({0,i});
                deplacements_.push_back({i,0});
            }
        }
        if(tp == DAME || tp == FOU){
            valeur_ = 3;
            // La tour ne peut bouger que verticalement ou horizontalement, la dame peut
            for(int i=1;i<8;i++){
                deplacements_.push_back({-i,-i});
                deplacements_.push_back({-i,i});
                deplacements_.push_back({i,-i});
                deplacements_.push_back({i,i});
            }
        }
        if(tp == DAME){
            valeur_ = 9;
        }
        if(tp == CAVALIER){
            valeur_ = 3;
            // Le cavalier ne peut bouger que d'un coin a un autre d'un rectangle 2x3
            deplacements_ = {{-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1}};
        }
        if(tp == PION){
            valeur_ = 1;
            // Le pion ne peut avancer que d'une case en verticalement, ou en diagonale s'il veut manger, sauf au depart ou il peut avancer de deux cases verticalement
            if(estBlanche){
                deplacements_ = {{-2,0},{-1,-1},{-1,0},{-1,1}};
            } else {
                deplacements_ = {{1,-1},{1,0},{1,1},{2,0}};
            }
        }
        if(tp == VIDE){
            valeur_ = 0;
            deplacements_ = {{0,0}};
            estBlanche_ = false;
        }
    }

    // Fonctions d'acces aux variables privees

    TypePiece getType() const {return type_;}
    vector<pair<int,int>> getDeplacements() const {return deplacements_;}
    int getValeur() const {return valeur_;}
    bool getEstBlanche() const {return estBlanche_;}
    pair<int,int> getPosition() const {return position_;}
    int getNbDeplacements() const {return nbDeplacements_;}

    // Fonctions modifiant les variables privees

    void setPosition(pair<int,int> position) {position_ = position;}
    void incrementNbDeplacements() {nbDeplacements_++;}

    // Affichage d'une piece

    void print() {
        string piece;
        switch(type_){
        case ROI :
            piece = "R";
            break;
        case DAME :
            piece = "D";
            break;
        case TOUR :
            piece = "T";
            break;
        case FOU :
            piece = "F";
            break;
        case CAVALIER :
            piece = "C";
            break;
        case PION :
            piece = "P";
            break;
        case VIDE :
            piece = "  ";
            break;
        default :
            cout << "PI" << endl;
            return;
        }
        if(type_ != VIDE){
            if(estBlanche_){
                piece.append("b");
            }
            else {
                piece.append("n");
            }
        }
        if(estBlanche_){
            // On affiche les pieces blaches sur un fond blanc
            cout << "\033[1;30;47m" << piece << "\033[0m";

        } else {
            // On affiche les pieces noires sur un fond marron
            cout << "\033[1;97;43m" << piece << "\033[0m";

        }
    }

};

class Echiquier {
private:
    // Plateau
    vector<vector<Piece*>> echiquier_;
    // Booleen indiquant qui joue
    bool tourHumain_;
    // Vecteurs stockant les pieces mangees
    vector<Piece*> prisesBlanches_;
    vector<Piece*> prisesNoires_;
    // Nombre de tours
    int nbTour_ = 1;

public:

    // Fonctions caracteristiques de l'echiquier et de la partie

    Echiquier() : echiquier_(8, vector<Piece*>(8, nullptr)), tourHumain_(true) {
        // Placement des pieces noires
        setPiece(1, 1, new Piece(TOUR, false));
        setPiece(1, 2, new Piece(CAVALIER, false));
        setPiece(1, 3, new Piece(FOU, false));
        setPiece(1, 4, new Piece(DAME, false));
        setPiece(1, 5, new Piece(ROI, false));
        setPiece(1, 6, new Piece(FOU, false));
        setPiece(1, 7, new Piece(CAVALIER, false));
        setPiece(1, 8, new Piece(TOUR, false));
        for(int j = 1; j <= 8; j++) {
            setPiece(2, j, new Piece(PION, false));
        }
        // Placement des pieces blanches
        setPiece(8, 1, new Piece(TOUR, true));
        setPiece(8, 2, new Piece(CAVALIER, true));
        setPiece(8, 3, new Piece(FOU, true));
        setPiece(8, 4, new Piece(DAME, true));
        setPiece(8, 5, new Piece(ROI, true));
        setPiece(8, 6, new Piece(FOU, true));
        setPiece(8, 7, new Piece(CAVALIER, true));
        setPiece(8, 8, new Piece(TOUR, true));
        for(int j = 1; j <= 8; j++) {
            setPiece(7, j, new Piece(PION, true));
        }
    }

    ~Echiquier() {
        for(int i=0; i<8; i++) {
            for(int j=0; j<8; j++) {
                delete echiquier_[i][j];
            }
        }
    }

    Piece* getPiece(int i, int j) const {
        return echiquier_[i-1][j-1];
    }

    void setPiece(int i, int j, Piece* piece) {
        echiquier_[i-1][j-1] = piece;
    }

    bool getTour() const {
        return tourHumain_;
    }

    void setTour(bool Tour) {
        tourHumain_ = Tour;
    }

    void AfficherEchiquier(string nom_joueur1, string nom_joueur2) {
        // En tete indiquant le nombre de tours realises
        cout << endl;
        cout << "      " << "\033[1;37;46m" << " Tour numero " << nbTour_ << " " << "\033[0m" << endl;
        cout << endl;
        // Score de chaque joueur
        cout << " Score de " << nom_joueur1 << " : " << "\033[1;30;47m" << Evaluation(true) << "\033[0m" << endl;
        cout << " Score de " << nom_joueur2 << " : " << "\033[1;97;43m" << Evaluation(false) << "\033[0m" << endl;
        cout << endl;
        // Plateau
        cout << "   A  B  C  D  E  F  G  H" << endl;
        for(int i = 1; i <= 8; i++) {
            cout << 9-i << " |";
            for(int j = 1; j <= 8; j++) {
                Piece* p = getPiece(i, j);
                if(p != nullptr) {
                    if(p->getType() == ROI && Echec(p->getEstBlanche())) {
                        // On affiche le roi en rouge s'il est en echec
                        if(p->getEstBlanche()) {
                            cout << "\033[1;30;41m" << "Rb" << "\033[0m";
                        } else {
                            cout << "\033[1;97;41m" << "Rn" << "\033[0m";
                        }
                    } else {
                        p->print();
                    }
                } else {
                    cout << "  ";
                }
                cout << "|";
            }
            cout << " " << 9-i << endl;
        }
        cout << "   A  B  C  D  E  F  G  H" << endl;
        // Pieces mangees
        cout << endl << "Pieces blanches prises : ";
        sort(prisesBlanches_.begin(),prisesBlanches_.end(),[](Piece* pb1, Piece* pb2){return pb1->getValeur() > pb2->getValeur();});
        for(Piece* pb : prisesBlanches_) {
            pb->print();
            cout << " ";
        }
        cout << endl << "Pieces noires prises : ";
        sort(prisesNoires_.begin(),prisesNoires_.end(),[](Piece* pn1, Piece* pn2){return pn1->getValeur() > pn2->getValeur();});
        for(Piece* pn : prisesNoires_) {
            pn->print();
            cout << " ";
        }
        cout << endl;
    }

    // Fonctions caracteristiques des cases

    bool caseVide(int i, int j) const {
        return echiquier_[i-1][j-1] == nullptr;
    }

    bool estAlliee(int i, int j, bool joueur) {
        Piece* p = getPiece(i,j);
        if(p != nullptr && p->getEstBlanche() == joueur) {
            return true;
        }
        return false;
    }

    bool estAdverse(int i, int j, bool joueur) {
        Piece* p = getPiece(i,j);
        if(p != nullptr && p->getEstBlanche() != joueur) {
            return true;
        }
        return false;
    }

    pair<int,int> PositionRoi(bool joueur) {
        for(int i=1; i<=8; i++) {
            for(int j=1; j<=8; j++) {
                Piece* p = getPiece(i,j);
                // On recupere la position du roi allie
                if(p != nullptr && p->getType() == ROI && p->getEstBlanche() == joueur) {
                    return make_pair(i,j);
                }
            }
        }
        // Au cas ou on ne trouve pas de roi (impossible en pratique)
        return make_pair(-1,-1);
    }

    // Fonctions utiles au deplacement des pieces

    bool CoupValide(int i, int j, int m, int n, bool joueur) {
        // On verifie que les coordonnees sont reelles
        if(i<1 || i>8 || j<1 || j>8 || m<1 || m>8 || n<1 || n>8) {
            return false;
        }
        // On stocke les pieces
        Piece* pd = getPiece(i,j);
        Piece* pa = getPiece(m,n);
        // On verifie que la case de depart contient une piece alliee
        if(!estAlliee(i,j,joueur)) {
            return false;
        }
        // On verifie que la case d'arrivee est libre ou contient une piece adverse
        if(pa != nullptr && !estAdverse(m,n,joueur)) {
            return false;
        }
        // On verifie que le coup est un deplacement de la piece
        vector<pair<int,int>> deplacements = pd->getDeplacements();
        bool dv = false;
        for(auto const& deplacement : deplacements) {
            if(i+deplacement.first == m && j+deplacement.second == n) {
                dv = true;
                break;
            }
        }
        if(!dv) {
            return false;
        }
        // Cas particulier du pion
        if(pd->getType() == PION) {
            // S'il veut avancer de deux cases
            if(abs(m-i) == 2) {
                // On verifie qu'il ne bouge pas horizontalement
                if(j != n) {
                    return false;
                }
                // On verifie qu'il est bien sur la ligne de depart
                if(i != 2 && i != 7) {
                    return false;
                }
                // On verifie que la case d'arrivee est libre
                if(!caseVide(m,n)) {
                    return false;
                }
                // On verifie que personne ne bloque le passage
                int dir = (joueur == true) ? -1 : 1;
                if(getPiece(i+dir,j) != nullptr) {
                    return false;
                }
            }
            // S'il veut avancer d'une case
            else if(abs(m-i) == 1) {
                // On verifie qu'il peut manger s'il veut
                if(abs(j-n) == 1) {
                    if(!estAdverse(m,n,joueur)) {
                        return false;
                    }
                }
                // On verifie que c'est vide devant
                int direction = (joueur == true) ? -1 : 1;
                if(j == n) {
                    if(!caseVide(i+direction,j)) {
                        return false;
                    }
                }
            }
            else {
                return false;
            }

        }
        // Le cavalier peut sauter les pieces
        else if(pd->getType() == CAVALIER) {
            return true;
        }
        else {
            // On verifie que personne ne bloque le passage
            int i_direction = (i < m) ? 1 : ((i == m) ? 0 : -1);
            int j_direction = (j < n) ? 1 : ((j == n) ? 0 : -1);
            int distance = max(abs(i-m), abs(j-n));
            for(int k=1; k<distance; k++) {
                if(!caseVide(i+k*i_direction,j+k*j_direction)) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Echec(bool joueur) {
        // On recupere la position du roi
        int m = PositionRoi(joueur).first;
        int n = PositionRoi(joueur).second;
        // On regarde si une piece adverse peut attaquer le roi
        for(int i=1; i<=8; i++) {
            for(int j=1; j<=8; j++) {
                if(estAdverse(i,j,joueur) && CoupValide(i,j,m,n,!joueur)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool EchecApresDeplacement(int i, int j, int m, int n, bool joueur) {
        // On verifie que le coup est valide
        if(!CoupValide(i,j,m,n,joueur)) {
            return false;
        }
        // On effectue le deplacement fictif
        Piece* pd = getPiece(i,j);
        Piece* pa = getPiece(m,n);
        setPiece(m,n,pd);
        setPiece(i,j,nullptr);
        // On verifie si le roi est en echec
        bool echec = Echec(joueur);
        // On annule le deplacement fictif
        setPiece(i,j,pd);
        setPiece(m,n,pa);
        return echec;
    }

    bool DeplacerPiece(int i, int j, int m, int n, bool joueur) {
        if(!joueur) {
            nbTour_++;
        }
        Piece* p = getPiece(i,j);
        // Si c'est un roi qui veut roque
        if(p->getType() == ROI && abs(n-j) == 2) {
            // S'il va a droite c'est un petit roque, sinon un grand
            bool petitRoque = (m-j > 0) ? true : false;
            // S'il fait un petit
            if(Roque(joueur,petitRoque)) {
                Piece* tourP = getPiece(i,8);
                setPiece(i,j,nullptr);
                setPiece(i,8,nullptr);
                setPiece(m,n,p);
                setPiece(m,n-1,tourP);
                p->incrementNbDeplacements();
                tourP->incrementNbDeplacements();
                return true;
            }
            // S'il fait un grand
            else if(Roque(joueur,!petitRoque)) {
                Piece* tourG = getPiece(i,1);
                setPiece(i,j,nullptr);
                setPiece(i,1,nullptr);
                setPiece(m,n,p);
                setPiece(m,n+1,tourG);
                p->incrementNbDeplacements();
                tourG->incrementNbDeplacements();
                return true;
            } else {
                return false;
            }
        } else {
            // On verifie que le deplacement est completement valide
            if(CoupValide(i,j,m,n,joueur) && !EchecApresDeplacement(i,j,m,n,joueur)) {
                // On place l'eventuelle piece prise dans son vecteur
                Piece* q = getPiece(m,n);
                if(estAdverse(m,n,joueur)) {
                    if(joueur) {
                        prisesNoires_.push_back(q);
                    } else {
                        prisesBlanches_.push_back(q);
                    }
                }
                // On deplace la piece
                setPiece(i,j,nullptr);
                setPiece(m,n,p);
                p->incrementNbDeplacements();
                return true;
            } else {
                return false;
            }
        }
    }

    // Regles speciales

    bool Roque(bool joueur, bool petitRoque) {
        // On recupere le roi et la tour
        int iRoi = joueur ? 8 : 1;
        int jRoi = 5;
        int iTour = joueur ? 8 : 1;
        int jTour = petitRoque ? 8 : 1;
        Piece* pRoi = getPiece(iRoi,jRoi);
        Piece* pTour = getPiece(iTour,jTour);
        // On regarde si les pieces sont à leurs places
        if(pRoi == nullptr || pTour == nullptr) {
            return false;
        }
        // On regarde si elles n'ont pas bouge
        if(pRoi->getNbDeplacements() != 0 || pTour->getNbDeplacements() != 0) {
            return false;
        }
        // On regarde si les cases separant les pieces sont vides
        if(petitRoque) {
            if(!caseVide(iRoi,jRoi+1) || !caseVide(iRoi,jRoi+2)) {
                return false;
            }
        } else {
            if(!caseVide(iRoi,jRoi-1) || !caseVide(iRoi,jRoi-2) || !caseVide(iRoi,jRoi-3)) {
                return false;
            }
        }
        // On regarde si le roi est en echec
        if(Echec(joueur)) {
            return false;
        }
        // On regarde si les cases traversees par le roi sont attaquees
        int dir = petitRoque ? 1 : -1;
        for(int n = jRoi; n != jRoi + 3*dir; n += dir) {
            for(int i=1; i<=8; i++) {
                for(int j=1; j<=8; j++) {
                    if(estAdverse(i,j,joueur) && CoupValide(i,j,iRoi,n,!joueur)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void PionDame() {
        for(int j=1; j<=8; j++) {
            Piece* pB = getPiece(1,j);
            Piece* pN = getPiece(8,j);
            // Si un pion blanc atteint la ligne du haut, il devient une dame blanche
            if(pB != nullptr && pB->getType() == PION && pB->getEstBlanche()) {
                delete pB;
                setPiece(1, j, new Piece(DAME, true));
            }
            // Si un pion noir atteint la ligne du bas, il devient une dame noire
            if(pN != nullptr && pN->getType() == PION && !pN->getEstBlanche()) {
                delete pN;
                setPiece(8, j, new Piece(DAME, false));
            }
        }
    }

    // Fonctions caracterisant une fin de partie

    bool EchecMat(bool joueur) {
        // On verifie que le joueur est bien en echec
        if(!Echec(joueur)) {
            return false;
        }
        // On parcourt les pieces alliees
        for(int i=1; i<=8; i++) {
            for(int j=1; j<=8; j++) {
                if(estAlliee(i,j,joueur)) {
                    // On regarde si elle peut faire sortir de l'echec
                    for(int m=1; m<=8; m++) {
                        for(int n=1; n<=8; n++) {
                            if(CoupValide(i,j,m,n,joueur) && !EchecApresDeplacement(i,j,m,n,joueur)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        // Si le roi ne peut pas etre sauve
        return true;
    }

    bool Victoire(bool joueur) {
        return EchecMat(!joueur);
    }

    bool Pat(bool joueur) {
        // On verifie que le joueur n'est pas en echec
        if(Echec(joueur)) {
            return false;
        }
        // On verifie qu'aucun coup n'est possible
        for(int i=1; i<=8; i++) {
            for(int j=1; j<=8; j++) {
                if(estAlliee(i,j,joueur)) {
                    for(int m=1; m<=8; m++) {
                        for(int n=1; n<=8; n++) {
                            if(CoupValide(i,j,m,n,joueur) && !EchecApresDeplacement(i,j,m,n,joueur)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        // Si on ne peut rien faire
        return true;
    }

    bool Nul() {
        // On verifie s'il y a un pat
        if(Pat(true) || Pat(false)) {
            return true;
        }
        // On verifie s'il ne reste que deux pieces (forcement les deux rois)
        int nbPieces = 0;
        for(int i=1; i<=8; i++) {
            for(int j=1; j<=8; j++) {
                if(getPiece(i,j) != nullptr) {
                    nbPieces++;
                }
            }
        }
        if(nbPieces == 2 && !Echec(true) && !Echec(false)) {
            return true;
        }
        return false;
    }

    // Fonctions utiles pour l'implementation du MinMax

    vector<pair<pair<int,int>,pair<int,int>>> CoupsPossibles(bool joueur) {
        vector<pair<pair<int,int>,pair<int,int>>> coups;
        for(int i=1; i<=8; i++) {
            for(int j=1; j<=8; j++) {
                if(estAlliee(i,j,joueur)) {
                    for(int m=1; m<=8; m++) {
                        for(int n=1; n<=8; n++) {
                            if(CoupValide(i,j,m,n,joueur) && !EchecApresDeplacement(i,j,m,n,joueur)) {
                                coups.push_back(make_pair(make_pair(i,j),make_pair(m,n)));
                            }
                        }
                    }
                }
            }
        }
        return coups;
    }

    int Controle(bool joueur) {
        int score = 0;
        for(int i=1; i<=8; i++) {
            for(int j=1; j<=8; j++) {
                if(estAlliee(i,j,joueur)) {
                    Piece* p = getPiece(i,j);
                    vector<pair<int,int>> dep = p->getDeplacements();
                    for(auto const& d : dep) {
                        int m = i + d.first;
                        int n = j + d.second;
                        // Chaque case controlee vaut 1 point
                        if(CoupValide(i,j,m,n,joueur) && !EchecApresDeplacement(i,j,m,n,joueur)) {
                            score++;
                            // On rajoute la valeur de la piece adverse attaquee
                            if(estAdverse(m,n,joueur)) {
                                score += getPiece(m,n)->getValeur();
                            }
                        }
                    }
                }
            }
        }
        return score;
    }

    float Evaluation(bool joueur) {
        float alpha = 1.0;
        float beta = 0.5;
        float score = 0.0;
        // Score de fin de partie
        if(Victoire(joueur)) {
            return INFINITY;
        }
        else if(Victoire(!joueur)) {
            return -INFINITY;
        }
        else if(Nul()) {
            return 0.0;
        }
        else {
            float valJoueur = 0.0;
            float valAdversaire = 0.0;
            int contJoueur = Controle(joueur);
            int contAdversaire = Controle(!joueur);
            for(int i=1; i<=8; i++) {
                for(int j=1; j<=8; j++) {
                    Piece* p = getPiece(i,j);
                    if(p != nullptr) {
                        float valPiece = p->getValeur();
                        if(p->getEstBlanche() == joueur) {
                            valJoueur += valPiece;
                        } else {
                            valAdversaire += valPiece;
                        }
                    }
                }
            }
            score = alpha*(valJoueur-valAdversaire) + beta*(contJoueur-contAdversaire);
            return score;
        }
    }

};

// Fonctions du MinMax

float MinMax(Echiquier* etat, int profondeur, float alpha, float beta, bool joueurMax) {
    if (profondeur == 0 || etat->Victoire(true) || etat->Victoire(false) || etat->Nul()) {
        return etat->Evaluation(joueurMax);
    }

    if (joueurMax) {
        float maxEval = -INFINITY;
        for (auto const& coup : etat->CoupsPossibles(true)) {
            Echiquier* copieEtat = new Echiquier(*etat);
            copieEtat->DeplacerPiece(coup.first.first, coup.first.second, coup.second.first, coup.second.second,true);
            float eval = MinMax(copieEtat, profondeur - 1, alpha, beta, false);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            delete copieEtat;
            if (beta <= alpha) break; // élagage alpha-bêta
        }
        return maxEval;
    } else {
        float minEval = INFINITY;
        for (auto const& coup : etat->CoupsPossibles(false)) {
            Echiquier* copieEtat = new Echiquier(*etat);
            copieEtat->DeplacerPiece(coup.first.first, coup.first.second, coup.second.first, coup.second.second, false);
            float eval = MinMax(copieEtat, profondeur - 1, alpha, beta, true);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            delete copieEtat;
            if (beta <= alpha) break; // élagage alpha-bêta
        }
        return minEval;
    }
}

pair<pair<int, int>, pair<int, int>> MinMaxWithID(Echiquier* etat, int profondeurMax, bool joueurMax, float alpha, float beta, int tempsMax) {
    pair<pair<int, int>, pair<int, int>> meilleurCoup;
    float eval;
    float maxEval = -INFINITY;
    float minEval = INFINITY;
    int profondeur = 1;
    auto tDebut = chrono::high_resolution_clock::now();
    while(profondeur <= profondeurMax) {
        if(joueurMax) {
            maxEval = -INFINITY;
            for(auto const& coup : etat->CoupsPossibles(true)) {
                Echiquier* copieEtat = new Echiquier(*etat);
                copieEtat->DeplacerPiece(coup.first.first, coup.first.second, coup.second.first, coup.second.second, true);
                eval = MinMax(copieEtat, profondeur-1, alpha, beta, false);
                if(eval > maxEval) {
                    maxEval = eval;
                    meilleurCoup = coup;
                }
                alpha = max(alpha, eval);
                delete copieEtat;
                if(beta <= alpha) break; // élagage alpha-bêta
            }
        } else {
            minEval = INFINITY;
            for(auto const& coup : etat->CoupsPossibles(false)) {
                Echiquier* copieEtat = new Echiquier(*etat);
                copieEtat->DeplacerPiece(coup.first.first, coup.first.second, coup.second.first, coup.second.second, false);
                eval = MinMax(copieEtat, profondeur-1, alpha, beta, true);
                if(eval < minEval) {
                    minEval = eval;
                    meilleurCoup = coup;
                }
                beta = min(beta, eval);
                delete copieEtat;
                if(beta <= alpha) break; // élagage alpha-bêta
            }
        }
        auto tFin = chrono::high_resolution_clock::now();
        auto duree = chrono::duration_cast<chrono::milliseconds>(tFin - tDebut).count();
        if (duree > tempsMax) break; // finir si le temps est dépassé
        profondeur++;
    }
    return meilleurCoup;
}

#endif // ECHECS_HPP_INCLUDED
