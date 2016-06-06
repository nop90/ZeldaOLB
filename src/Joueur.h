/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include "Personnage.h"
#include "Bouclier.h"

class Jeu;

class Joueur : public Personnage {
    public :
        Joueur(Jeu* jeu, int nmsv);
        ~Joueur();
        void saveSemiEmpl();
        void restoreSemiEmpl();
        void restoreEmpl();
        void draw(SDL_Surface* gpScreen);
        void draw2(int i, int j, SDL_Surface* gpScreen);
        void moveX(int i, int nbdir);
        void moveY(int i, int nbdir);
        void moveX(int i);
        void moveY(int i);
        void setTypeAnim(int t);
        int getTypeAnim();
        void setBouclier(int b);
        void setMagie(int b);
        void setMagieMax(int b);
        void setEpee(int e);
        void setTunique(int t);
        void setRubis(int i);
        void setFleche(int i);
        void setBombe(int i);
        void setRubisMax(int i);
        void setFlecheMax(int i);
        void setBombeMax(int i);
        void calculDef();
        void chargeSpin();
        void dechargeSpin();
        int getCharge();
        int nbQuarts();
        int nbCristaux();
        bool hasCristal(int i);
        void setCristal(int i);
        bool hasMedaillon(int i);
        void trouveMedaillon(int i);
        bool hasMelodie(int i);
        void setMelodie(int i, int v=1);
        int hasObjet(int i);
        int hasBouteille(int i);
        void setBouteille(int i, int v);
        int getMagie();
        int getMagieMax();
        int getMiMagie();
        int getForce();
        int getEpee();
        int getTunique();
        int getDefense();
        int getBouclier();
        int getRubis();
        int getFleche();
        int getBombe();
        int getRubisMax();
        int getFlecheMax();
        int getBombeMax();
        int getObjet();
        int getCle();
        void setObjet(int i);
        bool getOnilink();
        bool getOni();
        int getOnijauge();
        int getOnimax();
        void setOnilink(bool b);
        void setOni(bool b);
        void setOnijauge(int i);
        void setOnimax(int i);
        bool verifZone();
        bool isDauphin();
        void savePrec();
        void setVie(int i);
        void setVieMax(int i);
        void bigPlouf();
        void antiPlouf();
        void revie();
        int getBoostVie();
        void setBoostVie(int i);
        int getBoostMagie();
        void setBoostMagie(int i);
        int getBoostRubis();
        void setBoostRubis(int i);
        int getPousse();
        void setPousse(int i);
        void setTrouve(int i);
        int getCoeur(int i);
        void setCoeur(int i);
        int getCoffre(int i, int j);
        void setCoffre(int i, int j, int val=1);
        int getCle(int i, int j);
        void setCle(int i, int j, int val=1);
        int getAvancement();
        void setAvancement(int i);
        int getTemps(int i);
        void trouveObjet(int obj, int val=1);
        bool getExplore(int z, int i, int j);
        void setExplore(int z, int i, int j);
        void visible();
        void nonvisible();
        bool isLapin();
        void setLapin();
        void save();
        void load();
        void setImmo(bool b);
        bool getImmo();
        int nbEnnemis();
        void setEnnemi(int i);
        int getEnnemi(int i);
        bool getLoader();
        int getMort();
        int getTutoriel();
        void setTutoriel(int i);
        int getSolde();
        void paye();
        int getRaplaplat();
        void setRaplaplat();
        int getAsile();
        void setAsile(int v);
        void testTapis();
        void geler();
        void degeler();
        int getGel();
        void mortel();
    private :
        void tireFleche();
        void tireGrappin();
        void tireMagie();
        void tireLanterne();
        void poseBombe();
        void lance(int v);
        void boit();
        void glisser();
        void drawChute(SDL_Surface* gpScreen);
        void drawImmoMarche(SDL_Surface* gpScreen);
        void drawCharge(SDL_Surface* gpScreen);
        void drawEpee(SDL_Surface* gpScreen);
        void drawSpin(SDL_Surface* gpScreen);
        void drawArc(SDL_Surface* gpScreen);
        void drawGrappin(SDL_Surface* gpScreen);
        void drawBaguette(SDL_Surface* gpScreen);
        void drawFlotte(SDL_Surface* gpScreen);
        void drawSouleve(SDL_Surface* gpScreen);
        void drawBoire(SDL_Surface* gpScreen);
        void drawPousse(SDL_Surface* gpScreen);
        void drawTrouve(SDL_Surface* gpScreen);
        void drawTouche(SDL_Surface* gpScreen);
        void drawMort(SDL_Surface* gpScreen);
        void collisionEpee();
        void collisionSpin();
        
        int numSave;
        int temps; //temps depuis la sauvegarde charg�e
        int xdep2;
        int ydep2;
        Direction dirdep2;
        int magie;
        int magiemax;
        int typeanim;
        int minanim;
        int fleche;
        int bombe;
        int rubis;
        int objet;
        Bouclier* boucl;
        int bouclier;
        int tunique;
        int epee;
        Jeu* gpJeu;
        int charge;
        int flechemax;
        int bombemax;
        int rubismax;
        bool lapin;
        bool onilink;  //risque de transformation
        bool oni;      //transform�
        int onijauge; //jauge transformation
        int onimax;   //capacit� jauge
        int plouf;  //si entre dans l'eau
        int mort; //nombre de mort
        int porte; //objet port�
        int boostVie;
        int boostMagie;
        int boostRubis;
        int pousse;
        int trouve;
        int avancement;
        int tutoriel;
        bool invisible;
        int dirglisse;          //direction pour glisser
        int dirglace;           //direction dans laquel link a commencer � glisser
        int glace;
        int glisse;      // si sur surface glissante et � quel point
        int vitesse;
        int oldxg; //x pr�c�dent
        int oldyg; //y pr�c�dent
        bool immo;
        bool loader; //si les donn�es ont �t� charg�es depuis une sauvegarde
        int verse;   //d�j� vers�
        int raplaplat; // 1 si escalad�
        int asile;     // 1 si peur, 2 si fini
        int gel;
        int defense;
        int coeur[29]; //13 coeurs + 16 quarts de coeur
        int cristaux[5];
        int medaillon[3];
        int objets[15];
        int bouteille[3];
        int melodie[3];
        int ennemis[77]; //ennemis vaincus
        int cle[14][4]; // cl�s dans donjon i, 0 : carte, 1 : boussole, 2 : cl� boss, 3 : cl�s
        int coffre[15][35]; //14 donjons + coffres ext�rieurs
        bool explore[14][20][10]; //lieux explor�s dans les donjons
        int oldx[8]; //x pr�c�dents
        int oldy[8]; //y pr�c�dents
        SDL_Surface* imageTmp; //image servant pour des animations quelconques
        SDL_Surface* imageEpee;
        SDL_Surface* imageSpin;
        SDL_Surface* imageObjets;
        Uint32 TimeB; //temps de la derni�re sauvegarde charg�e
};

#endif  // Joueur.h
