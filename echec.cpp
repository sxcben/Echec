#include "echec.h"
#include "MinaMax2.h"

void Piece::print()
{
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
            cout  << piece ;

        } else {
            // On affiche les pieces noires sur un fond marron
            cout << piece ;

        }

//    string piece;
//    string color;
//    string reset = "\033[0m"; // Code pour réinitialiser la couleur
//
//    switch(type_){
//        case ROI :
//            piece = "R";
//            break;
//        case DAME :
//            piece = "D";
//            break;
//        case TOUR :
//            piece = "T";
//            break;
//        case FOU :
//            piece = "F";
//            break;
//        case CAVALIER :
//            piece = "C";
//            break;
//        case PION :
//            piece = "P";
//            break;
//        case VIDE :
//            piece = "  ";
//            break;
//        default :
//            cout << "PI" << endl;
//            return;
//    }
//
//    // Choix de la couleur en fonction de la couleur de la pièce
//    if(estBlanche_){
//        color = "\033[1;37m"; // Blanc
//    } else {
//        color = "\033[0;33m"; // Marron
//    }
//
//    if(type_ != VIDE){
//        if(estBlanche_){
//            piece.append("b");
//        }
//        else {
//            piece.append("n");
//        }
//    }
//
//    // Affichage de la pièce avec la couleur choisie
//    cout << color << piece << reset;

}



void Echiquier::AfficherEchiquier(string nom_joueur1, string nom_joueur2) {
    // En tete indiquant le nombre de tours realises
    cout << endl;
    cout << "      "  << " Tour numero " << nbTour_  << endl;
    cout << endl;
    // Score de chaque joueur
    cout << " Score de : " << Evaluation() << endl;
//    cout << " Score de " << nom_joueur2 << " : "  << Evaluation(false)  << endl;
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
                        cout  << "Rb" ;
                    } else {
                        cout << "Rn" ;
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


bool Echiquier::estAlliee(int i, int j, bool joueur) {
        Piece* p = getPiece(i,j);
        if(p != nullptr && p->getEstBlanche() == joueur) {
            return true;
        }
        return false;
    }


bool Echiquier::estAdverse(int i, int j, bool joueur) {
        Piece* p = getPiece(i,j);
        if(p != nullptr && p->getEstBlanche() != joueur) {
            return true;
        }
        return false;
    }


pair<int,int> Echiquier::PositionRoi(bool joueur) {
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


bool Echiquier::CoupValide(int i, int j, int m, int n, bool joueur) {
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



bool Echiquier::Echec(bool joueur) {
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



bool Echiquier::EchecApresDeplacement(int i, int j, int m, int n, bool joueur) {
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


bool Echiquier::DeplacerPiece(int i, int j, int m, int n, bool joueur) {
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




bool Echiquier::Roque(bool joueur, bool petitRoque) {
        // On recupere le roi et la tour
        int iRoi = joueur ? 8 : 1;
        int jRoi = 5;
        int iTour = joueur ? 8 : 1;
        int jTour = petitRoque ? 8 : 1;
        Piece* pRoi = getPiece(iRoi,jRoi);
        Piece* pTour = getPiece(iTour,jTour);
        // On regarde si les pieces sont � leurs places
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





void Echiquier::PionDame() {   //lorsqu'un pion arrive sur la ligne de l'ennemi
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




bool Echiquier::EchecMat(bool joueur) {
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




bool Echiquier::Pat(bool joueur) {
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




bool Echiquier::Nul() {
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


vector<pair<pair<int,int>,pair<int,int>>> Echiquier::CoupsPossibles(bool joueur) {
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




int Echiquier::Controle(bool joueur) {
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


float Echiquier::Evaluation() {
        float alpha = 1.0;
        float beta = 0.5;
        float score = 0.0;
        // Score de fin de partie
        if(Victoire(true)) {
            return INFINITY;
        }
        else if(Victoire(false)) {
            return -INFINITY;
        }
        else if(Nul()) {
            return 0.0;
        }
        else {
            float valJoueur = 0.0;
            float valAdversaire = 0.0;
            int contJoueur = Controle(true);
            int contAdversaire = Controle(false);
            for(int i=1; i<=8; i++) {
                for(int j=1; j<=8; j++) {
                    Piece* p = getPiece(i,j);
                    if(p != nullptr) {
                        float valPiece = p->getValeur();
                        if(p->getEstBlanche()) {
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

void Jouer_echec()   //ordi vs humain
{
    char rejouer = 'O';
    while (rejouer == 'O') {

        Echiquier* echiquier = new Echiquier();
        bool joueurBlanc = true;

        cout << endl;
        cout << "Bienvenue dans le jeu d'echecs : joueur (blancs) vs ordinateur (noirs) !" << endl;
        cout << endl;

        string nom_joueur;
        cout << "Entrez votre nom : ";
        cin >> nom_joueur;

        string nom_joueur2 = "ordinateur";

        while(!echiquier->Victoire(joueurBlanc) && !echiquier->Victoire(!joueurBlanc) && !echiquier->Nul()) {
            echiquier->AfficherEchiquier(nom_joueur,nom_joueur2);
            if(joueurBlanc) {
                cout << endl;
                cout << "A vous de jouer " << nom_joueur << "..." << endl;
                string position1, position2;
                cout << "Coordonnees de la piece a deplacer (ex: E2) : ";
                cin >> position1;
                int y1 = position1[0] - 'A' + 1;
                int x1 = '9' - position1[1];
                cout << "Coordonnees de la case de destination (ex: E4) : ";
                cin >> position2;
                int y2 = position2[0] - 'A' + 1;
                int x2 = '9' - position2[1];
                if(!echiquier->DeplacerPiece(x1, y1, x2, y2, joueurBlanc)) {
                    cout << endl;
                    cout << "Deplacement invalide..." << endl;
                    continue;
                }
            }
            else {
                cout << endl;
                cout << "Tour de l'ordinateur..." << endl;



                auto choix = meilleur_coup_alphabeta(echiquier, 5);
                int x1 = choix.first.first;
                int y1 = choix.first.second;
                int x2 = choix.second.first;
                int y2 = choix.second.second;

                char x1_char = 'A' + x1;
                char x2_char = 'A' + x2;
                int y1_int = y1 + 1;
                int y2_int = y2 + 1;

                cout << "piece deplacee de " << x1_char << y1_int << " a " << x2_char << y2_int << endl;

                echiquier->DeplacerPiece(x1, y1, x2, y2, false);

            }
            echiquier->PionDame();
            joueurBlanc = !joueurBlanc;
        }
        echiquier->AfficherEchiquier(nom_joueur,nom_joueur2);
        if(echiquier->Victoire(true)) {
            cout << endl;
            cout << "Felicitations " << nom_joueur << ", vous avez gagne !" << endl;
        }
        else if(echiquier->Victoire(false)) {
            cout << endl;
            cout << "L'ordinateur a gagne, desole " << nom_joueur << "..." << endl;
        }
        else {
            cout << endl;
            cout << "Partie nulle." << endl;
        }
        delete echiquier;

        cout << endl;
        cout << "Rejouer ? (O ou N) : ";
        cin >> rejouer;
        if(rejouer == 'O') {
            continue;
        }

    }
}
void Jouer_echec2()     // humain vs humain
{

    char rejouer = 'O';
    while (rejouer == 'O') {

        Echiquier* echiquier = new Echiquier();
        bool joueurBlanc = true;

        cout << endl;
        cout << "Bienvenue dans le jeu d'echecs : joueur 1 (blancs) vs joueur 2 (noirs) !" << endl;
        cout << endl;

        string nom_joueur1;
        cout << "Entrez votre nom (blancs) : ";
        cin >> nom_joueur1;
        cout << endl;

        string nom_joueur2;
        cout << "Entrez votre nom (noirs) : ";
        cin >> nom_joueur2;

        while(!echiquier->Victoire(joueurBlanc) && !echiquier->Victoire(!joueurBlanc) && !echiquier->Nul()) {
            echiquier->AfficherEchiquier(nom_joueur1,nom_joueur2);
            if(joueurBlanc) {
                cout << endl;
                cout << "A vous de jouer " << nom_joueur1 << "..." << endl;
                string position1B, position2B;
                cout << "Coordonnees de la piece a deplacer (ex: E2) : ";
                cin >> position1B;
                int y1B = position1B[0] - 'A' + 1;
                int x1B = '9' - position1B[1];
                cout << "Coordonnees de la case de destination (ex: E4) : ";
                cin >> position2B;
                int y2B = position2B[0] - 'A' + 1;
                int x2B = '9' - position2B[1];
                if(!echiquier->CoupValide(x1B, y1B, x2B, y2B, joueurBlanc) || !echiquier->DeplacerPiece(x1B, y1B, x2B, y2B, joueurBlanc)) {
                    cout << endl;
                    cout << "Deplacement invalide..." << endl;
                    continue;
                }
            }
            else {
                cout << endl;
                cout << "A vous de jouer " << nom_joueur2 << "..." << endl;
                string position1, position2;
                cout << "Coordonnees de la piece a deplacer (ex: E2) : ";
                cin >> position1;
                int y1 = position1[0] - 'A' + 1;
                int x1 = '9' - position1[1];
                cout << "Coordonnees de la case de destination (ex: E4) : ";
                cin >> position2;
                int y2 = position2[0] - 'A' + 1;
                int x2 = '9' - position2[1];
                if(!echiquier->CoupValide(x1, y1, x2, y2, joueurBlanc) || !echiquier->DeplacerPiece(x1, y1, x2, y2, joueurBlanc)) {
                    cout << endl;
                    cout << "Deplacement invalide..." << endl;
                    continue;
                }
            }
            echiquier->PionDame();
            joueurBlanc = !joueurBlanc;
        }
        echiquier->AfficherEchiquier(nom_joueur1,nom_joueur2);
        if(echiquier->Victoire(true)) {
            cout << endl;
            cout << "Felicitations " << nom_joueur1 << ", vous avez battu " << nom_joueur2 << " !" << endl;
        }
        else if(echiquier->Victoire(false)) {
            cout << endl;
            cout << "Felicitations " << nom_joueur2 << ", vous avez battu " << nom_joueur1 << " !" << endl;
        }
        else {
            cout << endl;
            cout << "Partie nulle." << endl;
        }
        delete echiquier;

        cout << endl;
        cout << "Rejouer ? (O ou N) : ";
        cin >> rejouer;
        if(rejouer == 'O') {
            continue;
        }

    }
};
