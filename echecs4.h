#ifndef ECHECS4_H_INCLUDED
#define ECHECS4_H_INCLUDED

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>

using namespace std;

enum TypePiece {ROI, DAME, TOUR, FOU, CAVALIER, PION, VIDE};

class Piece
{
public:
    TypePiece type_;
    vector<pair<int,int>> deplacements_;
    int valeur_;
    bool blanche_;
    pair<int,int> position_;

    Piece(TypePiece tp, bool blanche) : type_(tp), blanche_(blanche) {
        pair<int,int> coup;
        if(tp == ROI){
            valeur_ = 0;
            coup.first = -1;
            coup.second = -1;
            deplacements_.push_back(coup);
            coup.first = -1;
            coup.second = -0;
            deplacements_.push_back(coup);
            coup.first = -1;
            coup.second = 1;
            deplacements_.push_back(coup);
            coup.first = 0;
            coup.second = -1;
            deplacements_.push_back(coup);
            coup.first = 0;
            coup.second = 1;
            deplacements_.push_back(coup);
            coup.first = 1;
            coup.second = -1;
            deplacements_.push_back(coup);
            coup.first = 1;
            coup.second = 0;
            deplacements_.push_back(coup);
            coup.first = 1;
            coup.second = 1;
            deplacements_.push_back(coup);
        }
        if(tp == DAME || tp == TOUR){
            valeur_=5;
            for(int i=1;i<8;i++){
                coup.first = -i;
                coup.second = 0;
                deplacements_.push_back(coup);
                coup.first = 0;
                coup.second = -i;
                deplacements_.push_back(coup);
                coup.first = 0;
                coup.second = i;
                deplacements_.push_back(coup);
                coup.first = i;
                coup.second = 0;
                deplacements_.push_back(coup);
            }
        }
        if(tp == DAME || tp == FOU){
            valeur_=3;
            for(int i=1;i<8;i++){
                coup.first = -i;
                coup.second = -i;
                deplacements_.push_back(coup);
                coup.first = -i;
                coup.second = i;
                deplacements_.push_back(coup);
                coup.first = i;
                coup.second = -i;
                deplacements_.push_back(coup);
                coup.first = i;
                coup.second = i;
                deplacements_.push_back(coup);
            }
        }
        if(tp == DAME){
            valeur_ = 9;
        }
        if(tp == CAVALIER){
            valeur_ = 3;
            coup.first = -2;
            coup.second = -1;
            deplacements_.push_back(coup);
            coup.first = -2;
            coup.second = 1;
            deplacements_.push_back(coup);
            coup.first = -1;
            coup.second = -2;
            deplacements_.push_back(coup);
            coup.first = -1;
            coup.second = 2;
            deplacements_.push_back(coup);
            coup.first = 1;
            coup.second = -2;
            deplacements_.push_back(coup);
            coup.first = 1;
            coup.second = 2;
            deplacements_.push_back(coup);
            coup.first = 2;
            coup.second = -1;
            deplacements_.push_back(coup);
            coup.first = 2;
            coup.second = 1;
            deplacements_.push_back(coup);
        }
        if(tp == PION){
            valeur_ = 1;
            if(blanche_){
                coup.first = -2;
                coup.second = 0;
                deplacements_.push_back(coup);
                coup.first = -1;
                coup.second = -1;
                deplacements_.push_back(coup);
                coup.first = -1;
                coup.second = 0;
                deplacements_.push_back(coup);
                coup.first = -1;
                coup.second = 1;
                deplacements_.push_back(coup);
            }
            else {
                coup.first = 1;
                coup.second = -1;
                deplacements_.push_back(coup);
                coup.first = 1;
                coup.second = 0;
                deplacements_.push_back(coup);
                coup.first = 1;
                coup.second = 1;
                deplacements_.push_back(coup);
                coup.first = 2;
                coup.second = 0;
                deplacements_.push_back(coup);
            }
        }
        if(tp == VIDE){
            valeur_ = 0;
            coup.first = 0;
            coup.second = 0;
            deplacements_.assign(1,coup);
            blanche_ = false;
        }
    }

    TypePiece getType() const {return type_;}
    vector<pair<int,int>> getDeplacements() const {return deplacements_;}
    int getValeur() {return valeur_;}
    pair<int,int> getPosition() const {return position_;}

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
            piece = " ";
            break;
        }
        if(type_ != VIDE){
            if(blanche_){
                piece.append("b");
            }
            else {
                piece.append("n");
            }
        }
        cout << piece;
    }


};

class Echiquier
{
public:
    Piece echiquier_[8][8];

//    Echiquier() {
//
//    }

    void AfficherEchiquier() const {
        cout << endl;
        cout << "Etat de l'echiquier : " << endl;
        cout << endl;
        for (int i=0;i<8;i++) {
            cout << i+1;
            for (int j=0;j<8;j++) {
                echiquier_[i][j].print();
                cout << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

};

#endif // ECHECS4_H_INCLUDED
