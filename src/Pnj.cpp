/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Texte.h"
#include "Projectile.h"
#include "Ennemi.h"
#include "Pnj.h"
#include "Jeu.h"

Pnj::Pnj(Jeu* jeu, int type, int i, int j, int msg) : Personnage(), gpJeu(jeu), 
id(type), message(msg), typePnj(P_SIMPLE), immo(false), typeIA(IA_RANDOM) {
    if (id) {
        ostringstream im;
        im << id;
        image = IMG_Load(("romfs:/images/personnage/personnage" + im.str() + ".png").c_str());
        SDL_SetColorKey(image,SDL_SRCCOLORKEY,SDL_MapRGB(image->format,0,0,255));
        x=i; y=j; saveEmpl(); animmax=1;
        init();
    }
}

Pnj::~Pnj() {}

void Pnj::draw(SDL_Surface* gpScreen) {
    if (id && vie) {
        
        int phg[2];
        phg[0] = gpJeu->getPhg(0);
        phg[1] = gpJeu->getPhg(1);
    
        if (!gpJeu->getStop()) IA();
        
        SDL_Rect src;
        SDL_Rect dst;
        
        switch (typePnj) {
            case P_SIMPLE : src.x=direction*w; src.y=h*anim; break;
            case P_MONO_DIR : src.x=0; src.y=h*anim; break;
            case P_PROFIL : src.x=(direction%2)*w; src.y=h*anim; break;
        }
        dst.x=x-phg[0]; dst.y=y-phg[1]; src.w=w; src.h=h;
        
        if (id == 46 && gpJeu->getJoueur()->getAvancement()!=14) src.y=h*2;
        
        SDL_BlitSurface(image, &src, gpScreen, &dst);
        
        if(animmax){    
            if(SDL_GetTicks() > lastAnimTime + 240 && !gpJeu->getStop()) {
            lastAnimTime = SDL_GetTicks();
                anim++;
                if (anim > animmax) anim = 0;
            }
        }
    }
    if (suivant != NULL) ((Pnj*)suivant)->draw(gpScreen);
}

void Pnj::moveX(int i) {
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (gpJeu->isEnnemi(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (gpJeu->isPnj(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, getListId())) return;
    if (!gpJeu->isNotFull(x + gpZoneBase->getZone()->x + i, y + gpZoneBase->getZone()->y, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, 0, 0, 0)) return;
    x+=i;
}

void Pnj::moveY(int i) {
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (gpJeu->isEnnemi(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h)) return;
    if (gpJeu->isPnj(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, getListId())) return;
    if (!gpJeu->isNotFull(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y + i, 
        gpZoneBase->getZone()->w, gpZoneBase->getZone()->h, 0, 0, 0)) return;
    y+=i;
}

Pnj* Pnj::getSuivant() {return (Pnj*)suivant;}

int Pnj::getMessage() {return message;}

void Pnj::setMessage(int i) {message=i;}

void Pnj::setTypeIA(int i) {typeIA=i;}

void Pnj::setImmo(bool b) {immo=b;}

void Pnj::revie() {
    if (gpJeu->getZone()==20) return;
    vie = 1;
    x = xdep;
    y = ydep;
    if (suivant != NULL) getSuivant()->revie();
}

void Pnj::IA() {
    if (id == 47 && gpJeu->getJoueur()->getAvancement()==1 && gpJeu->getZone()==1) {
        if (x<40*16+8) {direction=E; x++;}
        else {vie=0;gpJeu->getJoueur()->setImmo(false);}
    }
    
    if (id == 33 && gpJeu->getJoueur()->getAvancement()==9) {
        if (y<16*16+8 && x>69*16+8 && y>15*16+8) {direction=S; moveY(1);}
        else if (x>69*16+8) {direction=O; moveX(-1);}
        else if (y>15*16+8) {direction=N; moveY(-1);}
        else {direction=S; gpJeu->getJoueur()->setAvancement(10);}
    }
    
    if (id == 46 && gpJeu->getJoueur()->getAvancement()==14) {
        if (y<12*16+8) moveY(1);
        else if (x>13*16+8) moveX(-1);
        else {direction=S; gpJeu->getJoueur()->setAvancement(15);}
    }
    
    if (id == 49 && !immo) {
        if (x<13*16) moveX(1);
        else if (y>4*16) moveY(-1);
        else immo=true;
    }
    if (id == 50 && !immo) {
        if (x>6*16) moveX(-1);
        else if (y>4*16) moveY(-1);
        else immo=true;
    }
    
    if (immo) return;
    if (parle()) return;
    if (typeIA==IA_SUIT) suit();
    if (typeIA==IA_RANDOM) bouge();
}

void Pnj::bouge() {
    int randomValue = (int)((float)rand() / RAND_MAX * (100));    
    switch (randomValue) {
        case 1 : moveX(-1);direction=O; break;
        case 2 : moveX(1); direction=E; break;
        case 3 : moveY(-1);direction=N; break;
        case 4 : moveY(1); direction=S; break;
        case 5 :
        case 6 :
        case 7 :
        case 8 : break;
        default :
            switch (direction) {
                case N : moveY(-1); break;
                case S : moveY(1); break;
                case O : moveX(-1); break;
                case E : moveX(1); break;
            }
            break;    
    }
}

void Pnj::suit() {
    Joueur* gpJoueur = gpJeu->getJoueur();
    int pnjCX = x + gpZoneBase->getZone()->x + (gpZoneBase->getZone()->w/2);
    int pnjCY = y + gpZoneBase->getZone()->y + (gpZoneBase->getZone()->h);
    int linkCX = gpJoueur->getX() + 8;
    int linkCY = gpJoueur->getY() + 24;
    int difx = pnjCX - linkCX;
    int dify = pnjCY - linkCY;
    
    //test port�e
    
    
    if ( max(abs(difx),abs(dify))>128) {
        if (gpJoueur->getAvancement()==6) gpJoueur->setAvancement(5);
        return;
    }
//    if (max(abs(difx),abs(dify))<16) return;
    if (gpJoueur->getAvancement()==5) gpJoueur->setAvancement(6);
    
    if (abs(difx) > abs(dify)) {
        if (difx>0) direction=O;
        else direction=E;
    }
    else {
        if (dify>0) direction=N;
        else direction=S;
    }
    
    if (gpJeu->getJoueur()->getX() < x) moveX(-1);
    if (gpJeu->getJoueur()->getX() > x) moveX(1);
    if (gpJeu->getJoueur()->getY() < y) moveY(-1);
    if (gpJeu->getJoueur()->getY() > y) moveY(1);
}

bool Pnj::parle() {
    Joueur* gpJoueur = gpJeu->getJoueur();
    int difx = (gpJoueur->getX()+8)-(x+(w/2));
    int dify = (gpJoueur->getY()+16)-(y+(h/2));
    
    if (abs(difx) < 24 && abs(dify) < 24) {
        if (abs(difx) < abs(dify)) {
            if (dify < 0) direction = N;
            else direction = S;
        }
        else {
            if (difx < 0) direction = O;
            else direction = E;
        }
        return true;
    }
    return false;
    
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x-8, 
    y + gpZoneBase->getZone()->y+gpZoneBase->getZone()->h-8, 1, 1)) {
        direction = O;
        return true;
    }
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x+gpZoneBase->getZone()->w+7, 
    y + gpZoneBase->getZone()->y+gpZoneBase->getZone()->h-8, 1, 1)) {
        direction = E;
        return true;
    }
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x, y + gpZoneBase->getZone()->y-8, 1, 1)) {
        direction = N;
        return true;
    }
    if (gpJeu->isLink(x + gpZoneBase->getZone()->x, 
    y + gpZoneBase->getZone()->y+gpZoneBase->getZone()->h+7, 1, 1)) {
        direction = S;
        return true;
    }
    return false;
}

void Pnj::init() {
    switch(id){
        case 1: case 13: case 14: case 23: case 33: w=16; h=25; break;
        case 2: case 18: case 43: case 45: w=16; h=24; typePnj = P_MONO_DIR; immo = true; break;
        case 3: w=16; h=23; typePnj = P_PROFIL; break;
        case 4: w=16; h=17; animmax=3; typePnj = P_MONO_DIR; break;
        case 5: w=13; h=16; break;
        case 6: w=15; h=16; typePnj = P_PROFIL; break;
        case 7: case 12: case 19: case 25: case 34: w=16; h=25; typePnj = P_MONO_DIR; immo = true; break;
        case 8: case 40: case 41: case 42: w=16; h=23; typePnj = P_MONO_DIR; immo = true; break;
        case 9: w=16; h=27; typePnj = P_MONO_DIR; immo = true; break;
        case 10: case 20: w=16; h=26; animmax=3; typePnj = P_MONO_DIR; immo = true; break;
        case 11: case 36: case 47: case 52: w=16; h=24; break;
        case 15: w=16; h=23; immo = true; break;
        case 16: case 48: w=32; h=48; typePnj = P_MONO_DIR; immo = true; break;
        case 17: w=18; h=25; typePnj = P_MONO_DIR; immo = true; break;
        case 21: case 55: w=17; h=25; typePnj = P_MONO_DIR; immo = true; break;
        case 22: w=16; h=29; animmax=3; typePnj = P_MONO_DIR; immo = true; break;
        case 24: w=16; h=21; typePnj = P_MONO_DIR; immo = true; break;
        case 26: w=39; h=30; animmax=3; typePnj = P_MONO_DIR; immo = true; break;
        case 27: case 30: case 31: w=16; h=17; typePnj = P_MONO_DIR; immo = true; break;
        case 28: w=25; h=35; animmax=4; typePnj = P_MONO_DIR; immo = true; break;
        case 29: w=21; h=27; animmax=4; typePnj = P_MONO_DIR; immo = true; break;
        case 32: case 54: w=16; h=23; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 35: w=16; h=22; animmax=3; typePnj = P_MONO_DIR; immo = true; break;
        case 37: w=19; h=22; break;
        case 38: w=16; h=16; break;
        case 39: w=24; h=16; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 44: w=28; h=28; animmax=0; typePnj = P_MONO_DIR; immo = true; break;
        case 46: w=22; h=27; animmax=1; typePnj = P_MONO_DIR; immo = true; break;
        case 49: case 50: w=16; h=16; animmax=1; typePnj = P_MONO_DIR; immo = true; 
            typeIA=IA_RIEN; break;
        case 51: w=16; h=27; typePnj = P_PROFIL; break;
        case 53: w=16; h=17; typePnj = P_MONO_DIR; immo = true; break;
    }
    gpZoneBase->getZone()->w=w; gpZoneBase->getZone()->h=h;
    gpZoneBase->getZone()->x=0; gpZoneBase->getZone()->y=0; 
    
    if (id == 15) {gpZoneBase->getZone()->y=7; gpZoneBase->getZone()->h=16;}
    if (id == 16) {gpZoneBase->getZone()->h+=4;}
    if (id == 33) {gpZoneBase->getZone()->y=9; gpZoneBase->getZone()->h=16; immo = true;}
    if (id == 46) {gpZoneBase->getZone()->y=11; gpZoneBase->getZone()->h=16;}
    if (id == 47) {immo = true;if(gpJeu->getZone()==1)direction=N;}
}
