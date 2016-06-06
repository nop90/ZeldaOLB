/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

#include "3ds/os_3ds.h"

#include "ZoneRect.h"
#include "Common.h"

class Personnage : public Listable {
    public :
        Personnage();
        ~Personnage();
        void saveEmpl();
        int getX();
        int getY();
        int getW();
        int getH();
        void setX(int i);
        void setY(int i);
        void setW(int i);
        void setH(int i);
        int getXDep();
        int getYDep();
        void setXDep(int i);
        void setYDep(int i);
        int getDirDep();
        void setDirDep(Direction d);
        ZoneRect* getZoneBase();
        void setDirection(Direction d);
        Direction getDirection();
        int getVie();
        int getVieMax();
        int getInvincible();
        void setInvincible(int i);
    protected :
        int x;
        int y;
        int xdep;
        int ydep;
        int vie;
        int viemax;
        int invincible;
        int type;
        Direction direction;
        int h;
        int w;
        int anim;
        int animmax;
        Direction dirdep;
        SDL_Surface* image;
        Uint32 lastAnimTime; // date de la derni�re anim
        ZoneRect* gpZoneBase; // zone � v�rifier pour les colisions
};

#endif  // Personnage.h
