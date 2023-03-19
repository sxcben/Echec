#ifndef ECHEC_H_INCLUDED
#define ECHEC_H_INCLUDED



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

    void print();

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

    void AfficherEchiquier(string nom_joueur1, string nom_joueur2);

    // Fonctions caracteristiques des cases

    bool caseVide(int i, int j) const {
        return echiquier_[i-1][j-1] == nullptr;
    }

    bool estAlliee(int i, int j, bool joueur);

    bool estAdverse(int i, int j, bool joueur);

    pair<int,int> PositionRoi(bool joueur);

    // Fonctions utiles au deplacement des pieces

    bool CoupValide(int i, int j, int m, int n, bool joueur);

    bool Echec(bool joueur);

    bool EchecApresDeplacement(int i, int j, int m, int n, bool joueur);

    bool DeplacerPiece(int i, int j, int m, int n, bool joueur);

    // Regles speciales

    bool Roque(bool joueur, bool petitRoque);

    void PionDame();

    // Fonctions caracterisant une fin de partie

    bool EchecMat(bool joueur);

    bool Victoire(bool joueur) {
        return EchecMat(!joueur);
    }

    bool Pat(bool joueur);

    bool Nul();

    // Fonctions utiles pour l'implementation du MinMax

    vector<pair<pair<int,int>,pair<int,int>>> CoupsPossibles(bool joueur);

    int Controle(bool joueur);

    float Evaluation();

};

void Jouer_echec();   // ordi vs humain
void Jouer_echec2();  // humain vs humain



#endif // ECHEC_H_INCLUDED
