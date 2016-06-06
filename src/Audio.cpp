/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>

//#include <SDL/SDL.h>
#include <3ds.h>
#include "Audio.h"

#include "3ds/os_3ds.h"
#include "3ds/sound_3ds.h"

Audio::Audio() : volume(0), musiqueId(0), specialId(0) {
    SOUND = FSOUND_Init(44100, 32, 0);
    music = NULL;
    
    if (SOUND) {
        previous_volume = -1;
        previous_volson = FSOUND_GetSFXMasterVolume();
        loadSounds();
    }
}

Audio::~Audio() {
    if (SOUND) {
        freeSounds();
        FMUSIC_StopSong(music);
        FMUSIC_SetMasterVolume(music, previous_volume);
        FMUSIC_FreeSong(music);
        FSOUND_SetSFXMasterVolume(previous_volson);
        FSOUND_Close();
    }
}

void Audio::setVolume(int vol) {volume=vol*4;
    if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
    FMUSIC_SetMasterVolume(music, volume);}
void Audio::setVolson(int volson) {FSOUND_SetSFXMasterVolume(volson*4);}

void Audio::loadSounds() {
    sons = new FSOUND_SAMPLE*[44];
    
    sons[0] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/text.ogg",0,0,0); // lettres
    sons[1] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/menu1.ogg",0,0,0); // menu 1
    sons[2] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/menu2.ogg",0,0,0); // menu 2
    sons[3] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/menu3.ogg",0,0,0); // menu 3
    sons[4] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/menu4.ogg",0,0,0); // menu 4
    sons[5] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/timewarp.ogg",0,0,0); // time retour
    sons[6] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/tombe.ogg",0,0,0); // tombe (ennemi)
    sons[7] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/hitenemy.ogg",0,0,0); //shot 1
    sons[8] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/killenemy.ogg",0,0,0); // shot 2
    sons[9] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/surprise.ogg",0,0,0); // surprise
    sons[10] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/monte.ogg",0,0,0); // monte
    sons[11] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/descend.ogg",0,0,0); // descend
    sons[12] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/chute.ogg",0,0,0); // chute
    sons[13] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/item.ogg",0,0,0); // item
    sons[14] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/rupee.ogg",0,0,0); // rubis
    sons[15] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/heart.ogg",0,0,0); // coeur
    sons[16] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/bomb.ogg",0,0,0); // bombe
    sons[17] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/textnext.ogg",0,0,0); // suite texte
    sons[18] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/textend.ogg",0,0,0); // fin texte
    sons[19] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/happy.ogg",0,0,0); // trouve objet
    sons[20] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/door.ogg",0,0,0); // ouvre porte
    sons[21] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/pics.ogg",0,0,0); // pics contre mur
    sons[22] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/sword.ogg",0,0,0); // �p�e
    sons[23] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/SwordCharging.ogg",0,0,0); // charg�e
    sons[24] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/Sword360.ogg",0,0,0); // spin
    sons[25] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/shoot.ogg",0,0,0); // fl�che
    sons[26] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/hookshot.ogg",0,0,0); // grappin
    sons[27] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/stamp.ogg",0,0,0); // pose bombe
    sons[28] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/magic.ogg",0,0,0); // magie
    sons[29] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/burn.ogg",0,0,0); // br�le
    sons[30] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/hammer.ogg",0,0,0); // marteau
    sons[31] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/plouf.ogg",0,0,0); // plouf
    sons[32] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/danger.ogg",0,0,0); // danger
    sons[33] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/hurt.ogg",0,0,0); // link se blesse
    sons[34] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/porte.ogg",0,0,0); // porte objet
    sons[35] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/lance.ogg",0,0,0); // lance objet
    sons[36] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/casse.ogg",0,0,0); // casse objet
    sons[37] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/charge.ogg",0,0,0); // charge magie
    sons[38] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/buisson.ogg",0,0,0); // coupe buisson
    sons[39] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/pousse.ogg",0,0,0); // pousse caisse
    sons[40] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/envol.ogg",0,0,0); // chant envol
    sons[41] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/vide.ogg",0,0,0); // hymne vide
    sons[42] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/masque.ogg",0,0,0); // chant esprit
    sons[43] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/splash.ogg",0,0,0); // ...
    
}

void Audio::freeSounds() {
    if (SOUND) {
        for (int i = 0; i < 44; i++) FSOUND_Sample_Free(sons[i]);
        delete[] sons;
    }
}

void Audio::playSound(int id, int chl) {
    if (SOUND) //Mix_PlayChannel(chl,sons[id],0);
        FSOUND_PlaySound(chl, sons[id]);
}

void Audio::playMusic(int id) {
    if (SOUND) {
        if (musiqueId != id) {
            musiqueId = id;            
            if (specialId == 0) {
                FMUSIC_StopSong(music);
                FMUSIC_FreeSong(music);
                music = choixMusique(id);
                if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
                FMUSIC_SetMasterVolume(music, volume);
                FMUSIC_SetLooping(music, 1);
                FMUSIC_PlaySong(music);
                specialId = 0;
            }
		}
    }
}

bool Audio::isSpecial() {return (specialId>0);}

void Audio::stopMusic() {
    if (SOUND) FMUSIC_StopSong(music);
}

void Audio::replayMusic() {
    if (SOUND) FMUSIC_PlaySong(music);
}

FMUSIC_MODULE* Audio::choixMusique(int id) {
    switch (id) {
        case 1 : return FMUSIC_LoadSong("data/music/Foret.mid");
        case 2 : return FMUSIC_LoadSong("data/music/Plaine.mid");
        case 3 : return FMUSIC_LoadSong("data/music/Villageest.mid");
        case 4 : return FMUSIC_LoadSong("data/music/Vallee.mid");
        case 5 : return FMUSIC_LoadSong("data/music/Desert.mid");
        case 6 : return FMUSIC_LoadSong("data/music/Lac.mid");
        case 7 : return FMUSIC_LoadSong("data/music/Rauru.mid");
        case 8 : return FMUSIC_LoadSong("data/music/Chateau.mid");
        case 9 : return FMUSIC_LoadSong("data/music/PlaineO.mid");
        case 10 : return FMUSIC_LoadSong("data/music/Marais.mid");
        case 11 : return FMUSIC_LoadSong("data/music/Ombre.mid");
        case 12 : return FMUSIC_LoadSong("data/music/Secret.mid");
        case 13 : return FMUSIC_LoadSong("data/music/Mido.mid");
        case 14 : return FMUSIC_LoadSong("data/music/Mont.mid");
        case 15 : case 17 : return FMUSIC_LoadSong("data/music/Donjon1.mid");
        case 18 : return FMUSIC_LoadSong("data/music/Manoir.mid");
        case 19 : return FMUSIC_LoadSong("data/music/Ordinn.mid");
        case 20 : return FMUSIC_LoadSong("data/music/Colisee.mid");
        case 21 : return FMUSIC_LoadSong("data/music/Lanelle.mid");
        case 22 : return FMUSIC_LoadSong("data/music/DFinal.mid");
        case 23 : return FMUSIC_LoadSong("data/music/DDesert.mid");
        case 24 : return FMUSIC_LoadSong("data/music/Glace.mid");
        case 25 : return FMUSIC_LoadSong("data/music/Farore.mid");
        case 26 : return FMUSIC_LoadSong("data/music/Xanto.mid");
        case 27 : return FMUSIC_LoadSong("data/music/DSecret.mid");
        case 28 : return FMUSIC_LoadSong("data/music/TourD.mid");
        case 16 : case 29 : case 31 : case 32 : case 33 : case 34 : case 35 :
        case 36 : case 37 : case 38 : case 40 : case 41 : case 42 : case 43 :
            return FMUSIC_LoadSong("data/music/Cave.mid");
        case 30 : case 39 : return FMUSIC_LoadSong("data/music/Fee.mid");
        case 44 : return FMUSIC_LoadSong("data/music/Pit.mid");
        case 45 : case 46 : case 54 : case 57 : case 58 : case 63 : case 64 :
        case 66 : case 67 : case 71 : return FMUSIC_LoadSong("data/music/Maison.mid");
        case 52 : case 56 : case 61 : case 70 :
            return FMUSIC_LoadSong("data/music/Potion.mid");
        case 48 : case 53 : return FMUSIC_LoadSong("data/music/Bar.mid");
        case 49 : case 62 : case 68 : case 79 : return FMUSIC_LoadSong("data/music/Maire.mid");
        case 50 : case 51 : case 59 : case 60 : case 65 : case 69 :
            return FMUSIC_LoadSong("data/music/Magasin.mid");
        case 47 : return FMUSIC_LoadSong("data/music/Jeu.mid");
        case 55 : return FMUSIC_LoadSong("data/music/Triste.mid");
        case 80 : return FMUSIC_LoadSong("data/music/Titre.mid");
        case 90 : return FMUSIC_LoadSong("data/music/Selection.mid");
        case 100 : return FMUSIC_LoadSong("data/music/Debut.mid");
        default : return FMUSIC_LoadSong("data/music/Maison.mid");
    }
}

void Audio::playSpecial(int id) {
    if (SOUND) {
        if (specialId != id) {
            FMUSIC_StopSong(music);
            FMUSIC_FreeSong(music);
            music = choixSpecial(id);
            if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
            FMUSIC_SetMasterVolume(music, volume);
            FMUSIC_SetLooping(music, 1);
            FMUSIC_PlaySong(music);
            specialId=id;
        }    
    }
}

void Audio::stopSpecial() {
    if (!specialId) return;
    int tmp = musiqueId;
    musiqueId = 0;
    specialId = 0;
    playMusic(tmp);
}

FMUSIC_MODULE* Audio::choixSpecial(int id) {
    switch (id) {
        case 1 : return FMUSIC_LoadSong("data/music/Boss.mid");
        case 2 : return FMUSIC_LoadSong("data/music/Mort.mid");
        case 3 : return FMUSIC_LoadSong("data/music/Epee.mid");
        case 4 : return FMUSIC_LoadSong("data/music/BossF.mid");
        case 5 : return FMUSIC_LoadSong("data/music/Fin.mid");
        case 6 : return FMUSIC_LoadSong("data/music/BossM.mid");
        case 7 : return FMUSIC_LoadSong("data/music/Area81.mid");
        case 8 : return FMUSIC_LoadSong("data/music/OniLink.mid");
        default : return FMUSIC_LoadSong("data/music/Boss.mid");
    }
}
