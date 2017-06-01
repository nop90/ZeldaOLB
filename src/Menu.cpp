/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <iostream>
#include <string>

#include "3ds/gfx_3ds.h"

#include "Menu.h"
#include "Texte.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"

Menu::Menu(Jeu* jeu) : gpJeu(jeu), sens(0), val(0), anim(0) {
    lastAnimTime = SDL_GetTicks();
    
    imageCadre = IMG_Load("romfs:/images/menu/bord.png");
    imageCoeur = IMG_Load("romfs:/images/menu/coeur.png");
    imageObjets = IMG_Load("romfs:/images/statut/objets.png");
    imageInventaire = IMG_Load("romfs:/images/statut/inventaire.png");
    
    SDL_SetColorKey(imageCadre,SDL_SRCCOLORKEY,SDL_MapRGB(imageCadre->format,0,0,255));
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
}

Menu::~Menu() {
    SDL_FreeSurface(imageCadre);
    SDL_FreeSurface(imageCoeur);
    SDL_FreeSurface(imageObjets);
    SDL_FreeSurface(imageInventaire);
}

void Menu::draw(SDL_Surface* gpScreen) {
    
 //   if (!gpJeu->getStop()) gpJeu->setStop(true);
    
    drawCadres(gpScreen);
    
    drawCoeur(gpScreen);
    drawCristaux(gpScreen);
    drawStatut(gpScreen);
    drawInventaire(gpScreen);
    drawCurseur(gpScreen);
    
    if(SDL_GetTicks() > lastAnimTime + 240) {
        lastAnimTime = SDL_GetTicks();
        anim++;            
        if (anim > 1) anim = 0;
    }
    
    if(sens==1 && val<200)val+=25;
    if(sens==0 && val > 0) {
        val-=25;
        if (val<=0) gpJeu->setStop(false);
    }
}

void Menu::drawCurseur(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    SDL_Rect src;
    SDL_Rect dst;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    src.w=32; src.h=32; src.y=0;
    //curseur
    if (anim==1) {
        if ((gpJoueur->getTypeAnim()<4 || gpJoueur->getTypeAnim()>20) && !gpJoueur->getOni()) 
            src.x=48; else src.x=80;
        dst.x=24+32*(gpJoueur->getObjet()%3)-dec; 
        dst.y=24+32*(gpJoueur->getObjet()/3);
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
}

void Menu::drawCadres(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=16; src.h=16;
    
    //cadre inventaire
    src.x = 0; src.y = 0; dst.x = 16-dec; dst.y = 16;
    if (dst.x > -15) {
        if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
    }
    src.x = 16;
    for (int i = 0; i < 5; i++) {
        dst.x += 16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    src.x = 32; dst.x+=16;
    if (dst.x > -15) {
        if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
    }
    src.y=16;
    for (int j = 0; j < 7; j++) {
        src.x=0; dst.x=16-dec; dst.y+=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
        src.x=16;
        for (int i = 0; i < 5; i++) {
            dst.x+=16;
            if (dst.x > -15) {
                if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
                SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
                if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
            }
        }
        src.x=32; dst.x+=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    src.y=32;
    src.x=0; dst.x=16-dec; dst.y+=16;
    if (dst.x > -15) {
        if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
    }
    src.x=16;
    for (int i = 0; i < 5; i++) {
        dst.x+=16;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    src.x=32; dst.x+=16;
    if (dst.x > -15) {
        if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
    }
    
    
    
    
    //cadre statut
    src.x = 0; src.y = 0; dst.x = 144; dst.y = 16 - dec;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    src.x = 16;
    for (int i = 0; i < 8; i++) {
        dst.x += 16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    src.x = 32; dst.x+=16;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    src.y=16;
    for (int j = 0; j < 7; j++) {
        src.x=0; dst.x=144; dst.y+=16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
        src.x=16;
        for (int i = 0; i < 8; i++) {
            dst.x+=16;
            if (dst.y > -15) {
                if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
                SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
                if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
            }
        }
        src.x=32; dst.x+=16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    src.y=32; src.x=0; dst.x=144; dst.y+=16;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    src.x=16;
    for (int i = 0; i < 8; i++) {
        dst.x+=16;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    src.x=32; dst.x+=16;
    if (dst.y > -15) {
        if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
        if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
    }
    
    
    
    
    //cadre cristaux
    src.x = 0; src.y = 0; dst.x = 80; dst.y = 176+dec;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.x = 16;
    for (int i = 0; i < 8; i++) {
        dst.x += 16;
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    }
    src.x = 32; dst.x+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.y=16; src.x=0; dst.x=80; dst.y+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.x=16;
    for (int i = 0; i < 8; i++) {
        dst.x+=16;
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    }
    src.x=32; dst.x+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.y=32; src.x=0; dst.x=80; dst.y+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    src.x=16;
    for (int i = 0; i < 8; i++) {
        dst.x+=16;
        SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    }
    src.x=32; dst.x+=16;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    
    //cadre link
    src.w=48; src.h=48;
    src.x = 0; src.y = 0; dst.x = 16; dst.y = 176+dec;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    gpJeu->getJoueur()->draw2(32,186+dec,gpScreen);
    
    //cadre coeur
    src.w=48; src.h=48;
    src.x = 0; src.y = 0; dst.x = 256+dec; dst.y = 176;
    SDL_BlitSurface(imageCadre, &src, gpScreen, &dst);
    
}

void Menu::drawInventaire(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    gpJeu->affiche(gpScreen, "Y", 20-dec,20);

    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=16; src.h=17;
    
    //arc
    if (gpJoueur->hasObjet(O_ARC)) {
        src.x=0; dst.x=32-dec; dst.y=32;
        if (gpJoueur->hasObjet(O_ARC)==5)src.y=0; else {src.x=16; src.y=102;}
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //grappin
    if (gpJoueur->hasObjet(O_GRAPPIN)) {
        src.x=16; src.y=0; dst.x=64-dec; dst.y=32;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //bombes
    if (gpJoueur->hasObjet(O_SAC_BOMBES) && gpJoueur->getBombe()>0) {
        src.x=32; src.y=0; dst.x=96-dec; dst.y=32;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //baguette de feu
    if (gpJoueur->hasObjet(O_BFEU)) {
        src.x=0; src.y=17; dst.x=32-dec; dst.y=64;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //baguette de glace
    if (gpJoueur->hasObjet(O_BGLACE)) {
        src.x=16; src.y=17; dst.x=64-dec; dst.y=64;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //lanterne
    if (gpJoueur->hasObjet(O_LANTERNE)) {
        src.x=32; src.y=17; dst.x=96-dec; dst.y=64;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //marteau
    if (gpJoueur->hasObjet(O_MARTEAU)) {
        src.x=0; src.y=34; dst.x=32-dec; dst.y=96;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //flute
    if (gpJoueur->hasObjet(O_OCARINA)) {
        src.x=0; src.y=85; dst.x=64-dec; dst.y=96;
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //masque
    if (gpJoueur->hasObjet(O_MASQUE)) {
        src.x=0; src.y=102; dst.x=96-dec; dst.y=96;
        if (gpJoueur->hasObjet(O_MASQUE)==2) {src.x=16;src.y=85;}
        if (dst.x > -15) {
            if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
        }
    }
    
    //bouteilles
    for (int i = 0; i < 3; i++) {
        if (gpJoueur->hasBouteille(i)) {
            dst.x=32*(i+1)-dec; dst.y=128;
            switch (gpJoueur->hasBouteille(i)) {
                case 1 : src.x=0; src.y=68; break;
                case 2 : src.x=0; src.y=51; break;
                case 3 : src.x=16; src.y=51; break;
                case 4 : src.x=32; src.y=51; break;
            }    
            if (dst.x > -15) {
                if (dst.x < 0) {src.x -= dst.x; src.w+= dst.x; dst.x = 0;}
                SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
                if (src.w < 16) {src.x -= (16-src.w); dst.x-= (16-src.w); src.w = 16;}
            }
        }
    }
    
}

void Menu::drawStatut(SDL_Surface* gpScreen) {
    int dec = 200-val;
    std::ostringstream oss;
    
    Joueur* gpJoueur = gpJeu->getJoueur();
    
    int i = 36;
    if (!gpJoueur->hasObjet(O_LANTERNE) || !gpJoueur->getOnilink()) i+=8;
    
switch(getLanguage()) {
case 2: // French
    gpJeu->affiche(gpScreen, "STATUT:", 148,20-dec);
break;

case 4: // Italian
    gpJeu->affiche(gpScreen, "STATO:", 148,20-dec);
break;

case 5: // Spanish
    gpJeu->affiche(gpScreen, "ESTATUTO:", 148,20-dec);
break;

default:
    gpJeu->affiche(gpScreen, "STATUS:", 148,20-dec);
break;	
}

    int v = gpJoueur->getVie();
    int vm = gpJoueur->getVieMax();
    if (v < 10) oss<<"0"; oss << v << "/";
    if (vm < 10) oss<<"0"; oss << vm;
switch(getLanguage()) {
case 2: // French
    gpJeu->affiche(gpScreen, "VIE       : " + oss.str(), 148,36-dec+8);
break;

case 4: // Italian
    gpJeu->affiche(gpScreen, "VITA      : " + oss.str(), 148,36-dec+8);
break;

case 5: // Spanish
    gpJeu->affiche(gpScreen, "VIDA      : " + oss.str(), 148,36-dec+8);
break;

default:
    gpJeu->affiche(gpScreen, "LIFE      : " + oss.str(), 148,36-dec+8);
break;	
}
    i+=16;
    
    
    if (gpJoueur->hasObjet(O_LANTERNE)) {
        oss.str("");
        int m = gpJoueur->getMagie();
        int mm = gpJoueur->getMagieMax();
        if (m < 10) oss<<"0"; oss << m << "/";
        if (mm < 10) oss<<"0"; oss << mm;
switch(getLanguage()) {
case 2: // French
        gpJeu->affiche(gpScreen, "MAGIE     : " + oss.str(), 148,i-dec);
break;

case 4: // Italian
        gpJeu->affiche(gpScreen, "MAGIA     : " + oss.str(), 148,i-dec);
break;

case 5: // Spanish
        gpJeu->affiche(gpScreen, "MAGIA     : " + oss.str(), 148,i-dec);
break;

default:
        gpJeu->affiche(gpScreen, "MAGIC     : " + oss.str(), 148,i-dec);
break;	
}
        i+=16;
    }
    
    if (gpJoueur->getOnilink()) {
        oss.str("");
        int o = gpJoueur->getOnijauge();
        int oo = gpJoueur->getOnimax();
        if (o < 10) oss<<"0"; oss << o << "/";
        if (oo < 10) oss<<"0"; oss << oo;
        gpJeu->affiche(gpScreen, "ONI LINK  : " + oss.str(), 148,i-dec);
        i+=16;
    }
    
    oss.str("");
    oss << gpJoueur->getForce();
switch(getLanguage()) {
case 2: // French
    gpJeu->affiche(gpScreen, "FORCE     : " + oss.str(), 148,i-dec);
break;

case 4: // Italian
    gpJeu->affiche(gpScreen, "FORZA     : " + oss.str(), 148,i-dec);
break;

case 5: // Spanish
    gpJeu->affiche(gpScreen, "STRENGTH  : " + oss.str(), 148,i-dec);
break;

default:
    gpJeu->affiche(gpScreen, "STRENGTH  : " + oss.str(), 148,i-dec);
break;	
}
    i+=16;
    oss.str("");
    oss << gpJoueur->getDefense();
switch(getLanguage()) {
case 2: // French
    gpJeu->affiche(gpScreen, "DEFENSE   : " + oss.str(), 148,i-dec);
break;


case 4: // Italian
    gpJeu->affiche(gpScreen, "DIFESA    : " + oss.str(), 148,i-dec);
break;

case 5: // Spanish
    gpJeu->affiche(gpScreen, "DEFENSA   : " + oss.str(), 148,i-dec);
break;

default:
    gpJeu->affiche(gpScreen, "DEFENSE   : " + oss.str(), 148,i-dec);
break;	
}
    i+=16;
    oss.str("");
    int h = gpJoueur->getTemps(2);
    int m = gpJoueur->getTemps(1);
    int s = gpJoueur->getTemps(0);
    if (h < 10) oss<<"0"; oss << h << ":";
    if (m < 10) oss<<"0"; oss << m << ":";
    if (s < 10) oss<<"0"; oss << s;
switch(getLanguage()) {
case 2: // French
    gpJeu->affiche(gpScreen, "TEMPS     : " + oss.str(), 148,i-dec);
break;

case 4: // Italian
    gpJeu->affiche(gpScreen, "TEMPO     : " + oss.str(), 148,i-dec);
break;

case 5: // Spanish
    gpJeu->affiche(gpScreen, "TIEMPO    : " + oss.str(), 148,i-dec);
break;

default:
    gpJeu->affiche(gpScreen, "TIME      : " + oss.str(), 148,i-dec);
break;	
}

    SDL_Rect src;
    SDL_Rect dst;
    
    src.y=0; src.w=16; src.h=16; dst.y=136-dec;
    
    //�p�e
    if (gpJoueur->getEpee()) {
        src.x = 16 * (gpJoueur->getEpee()-1); dst.x=156;
        if (gpJoueur->getOni()) {
            if (gpJoueur->hasObjet(O_MASQUE)==2) src.x=162;
            else src.x=112;
        }
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    //bouclier
    if (gpJoueur->getBouclier()) {
        src.x = 16 * (gpJoueur->getBouclier()-1); src.y=16; dst.x=176;
        if (gpJoueur->getOni()) {
            if (gpJoueur->hasObjet(O_MASQUE)==2) src.x=162;
            else {src.x=96; src.y=0;}
        }
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    //tunique
    if (gpJoueur->getTunique()) {
        src.x = 48 + 16 * (gpJoueur->getTunique()-1); src.y=16; dst.x=196;
        if (gpJoueur->getOni()) src.x=96;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    //bottes
    if (gpJoueur->hasObjet(O_BOTTES)) {
        src.x = 80; src.y=0; dst.x=216;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    //gants
    if (gpJoueur->hasObjet(O_GANTS)) {
        src.x=32; dst.x=236;
        if (gpJoueur->hasObjet(O_GANTS)==2)src.y=34; else src.y=85;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    //palmes
    if (gpJoueur->hasObjet(O_PALMES)) {
        src.x=16; src.y=34; dst.x=256;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
    //sac de bombes
    if (gpJoueur->hasObjet(O_SAC_BOMBES)) {
        src.x = 112; src.y = 16; dst.x=276;
        if (dst.y > -15) {
            if (dst.y < 0) {src.y -= dst.y; src.h+= dst.y; dst.y = 0;}
            SDL_BlitSurface(imageObjets, &src, gpScreen, &dst);
            if (src.h < 16) {src.y -= (16-src.h); dst.y-= (16-src.h); src.h = 16;}
        }
    }
}

void Menu::drawCristaux(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    gpJeu->affiche(gpScreen, "GRAAL :", 84,180+dec);
    
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=16; src.h=16; src.y=68;
    dst.x=94; dst.y=198+dec;
    
    for (int i = 0; i < 5; i++) {
        if (gpJeu->getJoueur()->hasCristal(i)) src.x=16;
        else src.x=32;
        SDL_BlitSurface(imageInventaire, &src, gpScreen, &dst);
        dst.x+=32-3;
    }
}

void Menu::drawCoeur(SDL_Surface* gpScreen) {
    int dec = 200-val;
    
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=16; src.h=16; src.y=0; src.x = 16*(gpJeu->getJoueur()->nbQuarts()%4);
    dst.x = 272+dec; dst.y = 192;
    SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
}

void Menu::menuIn() {
    sens = 1; val = 0;
    gpJeu->getAudio()->playSound(1);
}

void Menu::menuOut() {
    sens = 0;
    gpJeu->getAudio()->playSound(2);
}

int Menu::getVal() { return val;}
