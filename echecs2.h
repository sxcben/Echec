#ifndef ECHECS2_H_INCLUDED
#define ECHECS2_H_INCLUDED
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
//#include <pair>
#include <map>

using namespace std;

class TypePiece
{
public:
    enum PieceType {
        ROI,
        REINE,
        TOUR,
        FOU,
        CAVALIER,
        PION
    };

    TypePiece(PieceType type, std::vector<std::pair<int, int>> deplacement, int valeur)
        : type_(type), deplacement_(deplacement), valeur_(valeur) {}

    PieceType getType() const { return type_; }
    std::vector<std::pair<int, int>> getDeplacement() const { return deplacement_; }
    int getValeur() const { return valeur_; }
    void setValeur(int valeur) { valeur_ = valeur; }

    // les fonctions getType, getDeplacement et getValeur permettent
    // de récupérer la valeur des différents attributs de la classe

private:
    PieceType type_;
    std::vector<std::pair<int, int>> deplacement_;
    int valeur_;
};

inline void initTypePiece(TypePiece &tp) {
  switch (tp.getType()) {
    case TypePiece::ROI:
      tp.setValeur(0);
      break;
    case TypePiece::REINE:
      tp.setValeur(9);
      break;
    case TypePiece::TOUR:
      tp.setValeur(5);
      break;
    case TypePiece::FOU:
    case TypePiece::CAVALIER:
      tp.setValeur(3);
      break;
    case TypePiece::PION:
      tp.setValeur(1);
      break;
  }
  tp.setValeur(tp.getValeur() * tp.getValeur());
}

class Piece
{
public:
    enum Couleur {
        NOIR,
        BLANC
    };

    Piece(TypePiece type, Couleur couleur, std::pair<int, int> position)
        : type_(type), couleur_(couleur), position_(position) {}

    TypePiece getType() const { return type_; }
    Couleur getCouleur() const { return couleur_; }
    std::pair<int, int> getPosition() const { return position_; }

    void setType(TypePiece type) { type_ = type; }
    void setCouleur(Couleur couleur) { couleur_ = couleur; }
    void setPosition(std::pair<int, int> position) { position_ = position; }

private:
    TypePiece type_;
    Couleur couleur_;
    std::pair<int, int> position_;
};

class Echiquier
{
public:
    Echiquier() {
        // Initialisation de l'échiquier avec des pointeurs nuls
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                echiquier_[i][j] = nullptr;
            }
        }
    }

    // Affiche l'échiquier à l'écran ou dans un fichier
    void print(std::ostream& out = std::cout) const {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece *p = echiquier_[i][j];
                if (p) {
                    out << p->getType().getType() << " " << p->getCouleur() << " " << p->getPosition().first << " " << p->getPosition().second << " ";
                } else {
                    out << "NULL" << " ";
                }
            }
            out << std::endl;
        }
    }

    // Place une pièce sur l'échiquier
    void placePiece(Piece *p, int x, int y) {
        echiquier_[x][y] = p;
    }

    // Supprime une pièce de l'échiquier
    void removePiece(int x, int y) {
        echiquier_[x][y] = nullptr;
    }

private:
    Piece *echiquier_[8][8];
};

#endif // ECHECS2_H_INCLUDED
