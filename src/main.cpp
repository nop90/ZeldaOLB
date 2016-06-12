/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "3ds/os_3ds.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Keyboard.h"
#include "Generique.h"

SDL_Surface* init() {             // initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        exit(-1);
    }
    atexit(SDL_Quit);

    SDL_ShowCursor(SDL_DISABLE);
    
    return SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
}

int main(int argc, char** argv) {
    if (argc && argv); //pour �viter un warning.....
    
    std::srand(std::time(NULL));
    
    SDL_Surface* gpScreen = NULL;
    
    int mode = 2; //mode=0;
    
    gpScreen = init();
    
    Audio* gpAudio = new Audio();
    Jeu* gpJeu = new Jeu(gpAudio);
    Carte* gpCarte = new Carte(gpJeu);
    Encyclopedie* gpEncyclopedie = new Encyclopedie(gpJeu);
    Keyboard* gpKeyboard = new Keyboard(gpJeu, gpCarte, gpEncyclopedie, gpScreen, mode);
    gpJeu->setKeyboard(gpKeyboard);
    Generique* gpGenerique = new Generique(gpJeu);
    gpJeu->setGenerique(gpGenerique);
    gpGenerique->initLogo();
    
    //gpJeu->init(0);
    
    bool gLoop = true;
    
    Uint32 lastAnimTime = SDL_GetTicks();
    
    while (gLoop && aptMainLoop()) {
        
        if (gpKeyboard->gererClavier() == -1) {gLoop = false;}
        
        switch (gpKeyboard->getMode()) {
            case 12 : //carte
            case 22 : //carte t�l�portation
            case 13 : //encyclop�die des monstres
            case 17 : //menu d'aide 1
            case 18 : //menu d'aide 2
                gpJeu->draw(gpScreen);
				SDL_FillRect(gpScreen, NULL, RGBA8(0, 0, 0, 0x80));
				break;
            case 0 : //jeu normal
                gpJeu->draw(gpScreen);
				if (gpJeu->getMenu()) SDL_FillRect(gpScreen, NULL, RGBA8(0, 0, 0, 0x80));
				break;
            case 1 : //disclamer <-- Note by NOP90 - never used
            case 2 : //logo
                gpGenerique->draw(gpScreen); break;
            case 3 : //titre
            case 14 : //g�n�rique score
            case 4 : //selection
            case 6 : //options
            case 7 : //charger partie
            case 9 : //effacer partie
            case 15 : //records
            case 16 : //effacer record
            case 19 : //rang 100%
            case 20 : //rang ultime
            case 21 : //rang de rapidit�
                gpGenerique->drawTitre(gpScreen); break;
            case 8 : //g�n�rique intro
                gpGenerique->drawIntro(gpScreen, gpKeyboard->getIntro()); break;
            case 10 : //g�n�rique d�but chez link
                gpGenerique->drawDebut(gpScreen); break;
            case 11 : //g�n�rique fin
                gpGenerique->drawFin(gpScreen); break;
            default : break;
        }

        switch (gpKeyboard->getMode()) {
            case 4 : //selection
                gpGenerique->drawSelection((SDL_Surface*) 2, gpKeyboard->getLigne(),
                    gpKeyboard->getColonne()); break;
            case 6 : //options
                gpGenerique->drawOption((SDL_Surface*) 2, gpKeyboard->getLigneOption(),
                gpKeyboard->getVolume()/4, gpKeyboard->getVolson()/4); break;
            case 7 : //charger partie
                gpGenerique->drawCharger((SDL_Surface*) 2, gpKeyboard->getLigne(),
                    gpKeyboard->getLigneVal()); break;
            case 9 : //effacer partie
                gpGenerique->drawEffacerSave((SDL_Surface*) 2, gpKeyboard->getLigne(),
                    gpKeyboard->getLigneVal()); break;
            case 15 : //records
            case 19 : //rang 100%
            case 20 : //rang ultime
            case 21 : //rang de rapidit�
                gpGenerique->drawRecord((SDL_Surface*) 2, gpKeyboard->getLigneRecord(),
                    gpKeyboard->getColonneRecord()); break;
            case 16 : //effacer record
                gpGenerique->drawEffacer((SDL_Surface*) 2, gpKeyboard->getLigneVal()); break;
            case 12 : //carte
            case 22 : //carte t�l�portation
                gpCarte->draw((SDL_Surface*) 2); break;
				if (gpJeu->getMenuPtr()->getVal() == 200) gpJeu->getMenuPtr()->menuOut(); 
				gpJeu->drawMenu((SDL_Surface*) 2);
				break;
            case 13 : //encyclop�die des monstres
                gpEncyclopedie->draw((SDL_Surface*) 2); 
				if (gpJeu->getMenuPtr()->getVal() == 200) gpJeu->getMenuPtr()->menuOut(); 
				gpJeu->drawMenu((SDL_Surface*) 2);
				break;
            case 17 : //menu d'aide 1
            case 18 : //menu d'aide 2
                gpGenerique->draw((SDL_Surface*) 2); 
				if (gpJeu->getMenuPtr()->getVal() == 200) gpJeu->getMenuPtr()->menuOut(); 
				gpJeu->drawMenu((SDL_Surface*) 2);
				break;
            case 2 : //logo
            case 3 : //titre
            case 8 : //g�n�rique intro
            case 10 : //g�n�rique d�but chez link
            case 11 : //g�n�rique fin
				SDL_FillRect((SDL_Surface*) 2, NULL, SDL_MapRGB(0 , 0, 0, 0));
				break;
            default : 
				gpGenerique->drawBackground((SDL_Surface*) 2);
				if (gpJeu->getMenuPtr()->getVal() == 0) gpJeu->getMenuPtr()->menuIn(); 
				gpJeu->drawMenu((SDL_Surface*) 2);
				break;
        }

        SDL_Flip(gpScreen);
        
        if (SDL_GetTicks() < lastAnimTime + 20) SDL_Delay(lastAnimTime+20-SDL_GetTicks());
        lastAnimTime = SDL_GetTicks();
    
    }
    
    SDL_FreeSurface(gpScreen); //does nothing
    
    delete gpEncyclopedie;
    delete gpGenerique;
    delete gpKeyboard;
    delete gpCarte;
    delete gpJeu;
    delete gpAudio;
    
    SDL_ShowCursor(SDL_ENABLE);
    SDL_Quit();
    exit(0);
    
    return 0;
}
