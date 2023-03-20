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
    Piece(TypePiece tp, bool estBlanche);

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

public:
    // Fonctions caracteristiques de l'echiquier et de la partie
    Echiquier();
    ~Echiquier();
    Piece* getPiece(int i, int j) const;
    void setPiece(int i, int j, Piece* piece);
    bool getTour() const;
    void setTour(bool Tour);
    void AfficherEchiquier(string nom_joueur1, string nom_joueur2);

    // Fonctions caracteristiques des cases
    bool caseVide(int i, int j) const;
    bool estAlliee(int i, int j, bool joueur);
    bool estAdverse(int i, int j, bool joueur);
    pair<int,int> PositionRoi(bool joueur);

    // Fonctions utiles au deplacement des pieces
    bool CoupValide(int i, int j, int m, int n, bool joueur);
    bool Echec(bool joueur);
    bool EchecApresDeplacement(int i, int j, int m, int n, bool joueur);
    bool DeplacerPiece(int i, int j, int m, int n, bool joueur);

    // Nombre de tours
    int nbTour_ = 1;

    // Regles speciales
    bool Roque(bool joueur, bool petitRoque);
    void Promotion();

    // Fonctions caracterisant une fin de partie
    bool EchecMat(bool joueur);
    bool Victoire(bool joueur);
    bool Pat(bool joueur);
    bool Nul();

    // Fonctions utiles pour l'implementation du MinMax
    vector<pair<pair<int,int>,pair<int,int>>> CoupsPossibles(bool joueur);
    int Controle(bool joueur);
    float Evaluation();
};

// Creation de partie
void JouerUnJoueur();
void JouerDeuxJoueurs();

#endif // ECHEC_H_INCLUDED
