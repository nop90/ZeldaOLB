/*

    Zelda Oni Link Begins

    Copyright (C) 2006-2008  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "os_3ds.h"

#include "Texte.h"
#include "Menu.h"
#include "Joueur.h"
#include "Monde.h"
#include "Projectile.h"
#include "Jeu.h"

Texte::Texte(Jeu* jeu) : gpJeu(jeu), vitesse(40), av(0), x(0), y(0), w(0), h(0),
id(0), idsuiv(0), def(false), cadre(false), texte(""), buffer("") {
    lastAnimTime = SDL_GetTicks();
    imageFont = IMG_Load("romfs:/images/texte/font.png");
    SDL_SetColorKey(imageFont,SDL_SRCCOLORKEY,SDL_MapRGB(imageFont->format,0,0,255));
    imageCoeur = IMG_Load("romfs:/images/menu/coeur.png");
    SDL_SetColorKey(imageCoeur,SDL_SRCCOLORKEY,SDL_MapRGB(imageCoeur->format,0,0,255));
}

Texte::~Texte() {
    SDL_FreeSurface(imageFont);
    SDL_FreeSurface(imageCoeur);
}

void Texte::chercheText() {
    ostringstream os;
    int tmp;
    switch (id) {
        case 3  : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = "You find a piece of heart!!!";
            if (tmp<4) buffer = "Again "+os.str()+" before having a new heart!!!";
            else buffer = "Your heart count just increases!!!";
            break;
        case 5 : texte = "Sealed portal cave.**No Entry."; break;
        case 6 : texte = "Faron Temple**Save the trees, eat beaver!!!"; break;
        case 7 : texte = "You find Pegasus Boots!!! *Shift hold or Caps lock to run."; break;
        case 8 : texte = "N : East Field"; break;
        case 9 : texte = "W : Lanayru Lake"; break;
        case 10 : texte = "S : Forbidden Forest"; break;
        case 11 : texte = "S : Lanayru Lake"; break;
        case 12 : texte = "N : To Ordona Temple"; break;
        case 13 : texte = "N : Ruto Village"; break;
        case 14 : texte = "-Super Anti Monsters Ultimate Society- (S.A.M.U.S.)**Come in if you don't like monsters."; break;
        case 15 : texte = "W : Rauru City"; break;
        case 16 : texte = "You still didn't learn any song.";
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=17; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=26; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=28; chercheText();break;}
            break;
        case 17 : texte = "- SONG OF SOARING*- Don't play";
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=19; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=30; chercheText();break;}
            break;
        case 18 : texte = "- Song of Soaring*- DON'T PLAY"; break;
        case 19 : texte = "- SONG OF SOARING*- Elegy of Emptiness*- Don't play";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=22; chercheText();break;}
            break;
        case 20 : texte = "- Song of Soaring*- ELEGY OF EMPTINESS*- Don't play"; break;
        case 21 : texte = "- Song of Soaring*- Elegy of Emptiness*- DON'T PLAY"; break;
        case 22 : texte = "- SONG OF SOARING*- Elegy of Emptiness*- Song of Spirit*- Don't play"; break;
        case 23 : texte = "- Song of Soaring*- ELEGY OF EMPTINESS*- Song of Spirit*- Don't play"; break;
        case 24 : texte = "- Song of Soaring*- Elegy of Emptiness*- SONG OF SPIRIT*- Don't play"; break;
        case 25 : texte = "- Song of Soaring*- Elegy of Emptiness*- Song of Spirit*- DON'T PLAY"; break;
        case 26 : texte = "- ELEGY OF EMPTINESS*- Don't play";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=33; chercheText();break;}
            break;
        case 27 : texte = "- Elegy of Emptiness*- DON'T PLAY"; break;
        case 28 : texte = "- SONG OF SPIRIT*- Don't play"; break;
        case 29 : texte = "- Song of Spirit*- DON'T PLAY"; break;
        case 30 : texte = "- SONG OF SOARING*- Song of Spirit*- Don't play"; break;
        case 31 : texte = "- Song of Soaring*- SONG OF SPIRIT*- Don't play"; break;
        case 32 : texte = "- Song of Soaring*- Song of Spirit*- DON'T PLAY"; break;
        case 33 : texte = "- ELEGY OF EMPTINESS*- Song of Spirit*- Don't play"; break;
        case 34 : texte = "- Elegy of Emptiness*- SONG OF SPIRIT*- Don't play"; break;
        case 35 : texte = "- Elegy of Emptiness*- Song of Spirit*- DON'T PLAY"; break;
        case 36 : texte = "N : Ruto Village*S : East Field"; break;
        case 37 : texte = "S : Ruto Village*E : To the desert"; break;
        case 38 : texte = "Mine entrance"; break;
        case 39 : texte = "W : To Ordona Temple*E : Ruto Village"; break;
        case 40 : texte = "Sorry, that was my only bottle."; break;
        case 41 : texte = "I am selling a bottle for 100 rupees, are you interested?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->hasBouteille(0)) {id=40; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) idsuiv=44;
            else idsuiv=45;
            break;
        case 42 : texte = "I am selling a bottle for 100 rupees, are you interested?*              yes              NO ?"; idsuiv=43; break;
        case 43 : texte = "Come again if you change your mind."; break;
        case 44 : texte = "You don't have enough rupees!"; break;
        case 45 : texte = "Thanks!"; break;
        case 46 : texte = "You find an empty bottle!!!**It will help you stock potions."; break;
        case 47 : texte = "There is a secret passage to the west of the village which leads to Ordona Temple, but you will need bombs to take it."; break;
        case 49 :
            if (gpJeu->getJoueur()->getAvancement()>3 && !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) 
                texte = "If you are looking for a bomb bag, you should go to see the man working in the mine, he uses a lot of bombs.";
            else texte = "Get out of my way!"; break;
        case 50 : 
            if (gpJeu->getJoueur()->getAvancement()==5 || gpJeu->getJoueur()->getAvancement()==6)
                texte = "The mayor strictly forbade the access to the mine because monsters go out.";
            else if (gpJeu->getJoueur()->getAvancement()==7)
                texte = "You are saying that maybe someone is locked in the mine? So what?";
            else if (gpJeu->getJoueur()->getAvancement()==8 || gpJeu->getJoueur()->getAvancement()==9)
                texte = "The mayor allowed you to pass? So move along!";
            else texte = "..."; break;
        case 54 : texte = "Welcome to the Ruto village.**And just between us, don't trust anyone here..."; break;
        case 55 : texte = "Even if this village seems to be wealthy at first sight, it's actually the poorest in Termina... And we cannot rely on the mayor to change that..."; break;
        case 56 : texte = "Tourists who come here used to be either lost, or totally mad.**For my part, I always have a map with me."; break;
        case 57 : texte = "S : To East Field*W : To Ordona Temple*E : Ruto Village"; break;
        case 58 : texte = "S : East Field"; break;
        case 59 : texte = "Ordona Temple"; break;
        case 60 : texte = "E : Forgotten Land"; break;
        case 61 : texte = "S : Ruto Village*W : Sure Death"; break;
        case 62 : texte = "Enchanting Oasis"; break;
        case 63 : texte = "Fairy Cave"; break;
        case 64 : texte = "Din Temple**Fairies' power will reward bravery!"; break;
        case 65 : texte = "                     ???"; break;
        case 66 : texte = "Lanayru Temple"; break;
        case 67 : texte = "W : Witch's Swamp"; break;
        case 68 : texte = "E : Forbidden Forest"; break;
        case 69 : texte = "N : East Field*W : To Rauru City"; break;
        case 70 : texte = "N : Rauru City"; break;
        case 71 : texte = "O : West Field"; break;
        case 72 : texte = "N : Forgotten Land*S : Rauru City"; break;
        case 73 : texte = "N : Rauru City*S : Lanayru Lake*W : West Field*E : East Field"; break;
        case 74 : texte = "E : East Field"; break;
        case 75 :  texte = "Sorry, I have nothing in stock anymore."; break;
        case 76 : texte = "I am selling a better shield for 250 rupees, are you interested?*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getBouclier()>1) {id=75; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<250) idsuiv=44;
            else idsuiv=45;
            break;
        case 77 : texte = "I am selling a better shield for 250 rupees, are you interested?*              yes              NO ?"; idsuiv=43; break;
        case 78 : texte = "You find a new shield!!!*Your defense rises by one point, your resistance is stronger against the enemies' attacks !!!"; break;
        case 79 : texte = "But why do I have to care for these hens again???"; break;
        case 80 : texte = "I like to sweep!"; break;
        case 81 : texte = "Rauru is the most beautiful city of the country, a lot of visitors come every day to visit it."; break;
        case 82 : texte = "A magical instrument is said to be somewhere in Termina. *I wonder if I might see it some day..."; break;
        case 83 : texte = "You found the magical instrument???**I hoped that was a saxo..."; break;
        case 84 : texte = "My parents are lost."; break;
        case 85 : texte = "I like to wander!"; break;
        case 86 : texte = "S : Rauru City*E : Haunted House"; break;
        case 87 : texte = "Haunted House**Come to enrich our soul collection!"; break;
        case 88 : texte = "E : To Ordona Temple"; break;
        case 89 : texte = "Farore Temple**Fairies' power will reward bravery!"; break;
        case 90 : texte = "W : Mido Village"; break;
        case 91 : texte = "N : Destiny Mountains"; break;
        case 92 : texte = "Zelda Temple"; break;
        case 93 : texte = "W : Graveyard"; break;
        case 94 : texte = "Desert's secret :*Lift the bird's stones clockwise ending by the eye to open the way."; break;
        case 95 : texte = "S : Witch's Swamp"; break;
        case 96 : texte = "E : Rauru City"; break;
        case 97 : texte = "N : West Field*S : Witch's Hut"; break;
        case 98 : texte = "W : Kasuto Village*E : Witch's Hut"; break;
        case 99 : texte = "Potions Hut**Come trade your rupees for the most powerful potions of the country!!!"; break;
        case 100 : texte = "E : Lanayru Lake"; break;
        case 101 : texte = "N : Graveyard*S : Kasuto Village"; break;
        case 102 : texte = "Kasuto Village**   -- Not for humans (alive) --"; break;
        case 103 : texte = "Tip : Hold Ctrl to look around with the keyboard arrows."; break;
        case 104 : texte = "N : Kasuto Village*E : Witch's Swamp"; break;
        case 105 : texte = "Monsters' Colosseum**Come all!"; break;
        case 106 : texte = "You look pretty strong, you should train in the arena at the South of the village. A very useful object is said to be hidden inside..."; break;
        case 107 : texte = "Uh?*A new species?**Do you know how to speak?"; break;
        case 108 : texte = "This village is the last rampart against humanity."; break;
        case 109 : texte = "Hello, I am a dummy monster."; break;
        case 110 : texte = "Stuck?***Though the solution is not so far."; break;
        case 111 : texte = "S : Kasuto Village"; break;
        case 112 : texte = "Xanto Temple**""Dead men tell no tales..."; break;
        case 113 : texte = "Did you ever try the hammer on skulls?"; break;
        case 114 : texte = "E : West Field"; break;
        case 115 : texte = "Mido Village"; break;
        case 116 : texte = "Do all teenagers have no fashion sense as you do?"; break;
        case 117 : texte = "Welcome in the Mido village, but don't feel obliged to stay here."; break;
        case 118 : texte = "Grrr... I thought I would be alone here..."; break;
        case 119 : texte = "Only the immeasurable emptiness can remove this stone."; break;
        case 120 : texte = "Nayru Temple**Fairies' power will reward bravery!"; break;
        case 121 : texte = "Destiny Way**Only an ally of Good and Evil will get over this cave."; break;
        case 122 : texte = "S : Mido Village"; break;
        case 123 : texte = "Eldin Temple"; break;
        case 124 : texte = "S : West Field"; break;
        case 125 : texte = "Titans' strength will go to the legendary hero..."; break;
        case 126 : texte = "Destiny Tower*Hero of Hyrule watch out, vile Ganon now sits here enthroned, the future of the world will be at stake here."; break;
        case 127 : texte = "Congratulations!**You succeeded in climbing the Flatty Mountain!"; break;
        case 128 : texte = "You must not transform yourself here!!!"; break;
        case 129 : texte = "You cannot go in this village with this appearance !!!"; break;
        case 130 : texte = "Link, it's Pit. I am talking with you by telepathy. You must under no circumstances transform yourself in a village!*I will teleport you outside."; break;
        case 131 : texte = "You find a sword!!!**Press Z (or W) to attack or hold Z (or W) to charg a spin attack."; break;
        case 132 : texte = "You find the Map!!!*Press P to see the map of the Dungeon."; break;
        case 133 : texte = "You find the Compass!!!**The Boss and chests are now indicated on the map."; break;
        case 134 : texte = "You find the Boss Key.**Use it to reach his haunt."; break;
        case 135 : texte = "You find a small key.**Use it to unlock a door."; break;
        case 136 : texte = "You find a New Heart!!!**Your maximal energy rises by one heart!!!"; break;
        case 137 : texte = "You find a Graal!!!"; break;
        case 138 : texte = "You came to save me?*Thank you very much!"; 
            if (gpJeu->getMonde()->regionValue(0)==160*16) {
                if (gpJeu->getJoueur()->getCoffre(1,25)) {id=50; chercheText();break;}
                else idsuiv = 139;}
            if (gpJeu->getMonde()->regionValue(0)==180*16 
                && gpJeu->getMonde()->regionValue(1)==15*16) {
                if (gpJeu->getJoueur()->getCoffre(1,26)) {id=50; chercheText();break;}
                else idsuiv = 140;}
            if (gpJeu->getMonde()->regionValue(0)==180*16 
                && gpJeu->getMonde()->regionValue(1)==45*16) {
                if (gpJeu->getJoueur()->getCoffre(1,27)) {id=50; chercheText();break;}
                else idsuiv = 141;}
            break;
        case 139 : texte = "Digging in these galleries we discovered this hang-out of monsters..."; idsuiv=142; break;
        case 140 : texte = "We all have been captured by the monsters living in these caverns."; idsuiv=142; break;
        case 141 : texte = "Our chief is on the floor downstairs, go quickly to save him!"; idsuiv=142; break;
        case 142 : texte = "I found that in the mine, take it, it could help you!"; break;
        case 143 : 
            if (gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=50; chercheText();break;}
            texte = "You defeated the monster of the mine???*Congratulations!!!"; idsuiv=144; break;
        case 144 : texte = "I am the chief of the workers, you say you were looking for me?"; idsuiv=145; break;
        case 145 : texte = "Take this bag full of bomb, it may help you."; break;
        case 146 : texte = "You find the Bomb Bag!!!*And it's full!!!*Press ENTER to set them up, and X to put one down."; break;
        case 147 : texte = "You find the Gloves!!!**Now you can lift light stones by pressing C."; break;
        case 148 : 
            if (gpJeu->getJoueur()->hasObjet(O_ARC)) {id=50; chercheText();break;}
            texte = "I am the right hand man of the mayor, he sent me to save his daughter...*But I've been had, there is nothing to do against these ghosts..."; idsuiv=149; break;
        case 149 : texte = "Don't stay here, you can't do anything with your actual weapons..."; idsuiv=150; break;
        case 150 : texte = "To continue your quest, follow the road at the west of the City. This bow will allow you to reach the sphere and open the way..."; break;
        case 151 : texte = "You find the Bow!!!*You can now attack from a distance and reach distant targets!!!"; break;
        case 152 : 
            if (gpJeu->getJoueur()->getAvancement()>64) {id=153; chercheText();break;}
            texte = "You defeated the vampire and came to save me? Thank you so much! My father is the mayor of the City, go and see him, I'm sure he will reward you."; break;
        case 153 : texte = "Don't worry about me, I can go back home by myself now that the vampire is dead."; break;
        case 154 : 
            if (gpJeu->getJoueur()->getAvancement()==13)
                texte = "You received the mayor's authorization?*So be careful, those who venture over there never come back...";
            else if (gpJeu->getJoueur()->getAvancement()<13)
                texte = "Under orders by the mayor, access to this area is strictly forbidden.";
            else texte = "..."; break;
        case 155 : texte = "You cannot run away now!"; break;
        case 156 : texte = "You find the Hammer!!!**Now you can squash impeding obstacles!!!"; break;
        case 157 : texte = "You find the Hookshot!!!**Now you can cross over precipices!!!"; break;
        case 158 : texte = "Colosseum Hall"; break;
        case 159 : texte = "Arena 1"; break;
        case 160 : texte = "Arena 2"; break;
        case 161 : texte = "Arena 3"; break;
        case 162 : texte = "Arena 4"; break;
        case 163 : texte = "Prize giving"; break;
        case 164 : texte = "Special Arena**Come and try the special prize!!!"; break;
        case 165 : texte = "You find the Flippers!!!**You can now cross the spans of water!!!"; break;
        case 166 : texte = "You find a Coat of Mail!!!**Your defense rises by one point!!!"; break;
        case 167 : texte = "You find a better Coat of Mail!!!   *Your defense rises by one point!!!"; break;
        case 168 : texte = "Hehehehehe!!!*Congratulation Link! You succeeded in getting rid of your curse. And in the same way you released me!!!"; idsuiv=169; break;
        case 169 : texte = "In reward for your efforts I won't kill you today, I have a more important mission."; idsuiv=170; break;
        case 170 : texte = "If you really want to stop me, meet me in the dead temple if you are brave enough.*Farewell! Hihihihihi!!!"; break;
        case 171 : texte = "Link, it's Zelda, I am talking with you by telepathy. I am with Pit, rejoin us quickly, the situation is serious."; break;
        case 172 : texte = "Good morning Link, I was waiting for you.**My name is Pit, I have been charged by Princess Zelda to watch on this cave."; idsuiv=173; break;
        case 173 : texte = "She warned me you were coming and asked me to help you.*My house is just here, we'll be more comfortable to talk, follow me."; break;
        case 174 : texte = "Pit told you not to go out of the forest."; break;
        case 175 : texte = "You find the Fire Rod!!!**You can now throw powerful fireball!!!"; break;
        case 176 : 
            if ((gpJeu->getZone() == 23 && gpJeu->getJoueur()->getCoffre(8,19))
            || (gpJeu->getZone() == 24 && gpJeu->getJoueur()->getCoffre(9,24))
            || (gpJeu->getZone() == 25 && gpJeu->getJoueur()->getCoffre(10,21))) {
                id=50; chercheText();break;}
            texte = "I was waiting for you Link.*I hand the power of the Goddness over to your sword to restore the strenght of the Master Sword."; break;
        case 177 : 
            if (gpJeu->getJoueur()->getEpee()==5) {id=178; chercheText();break;}
            texte = "The power of the Master Sword rises ! **Go quickly to the next temple!"; break;
        case 178 : texte = "The Master Sword reach its maximal power!!!  *Even Oni-Link could not stand up to its blade!!!"; break;
        case 179 : texte = "You find the Ice Rod!!!**Now you can freeze what ever you want!!!"; break;
        case 180 : texte = "You find a new shield!!!*Your defense rises, now your resistance is stronger against the enemies' attacks!!!"; break;
        case 181 : texte = "Link, it's Zelda, I am talking to you by telepathy. Do not go in this dungeon if you are not perfectly prepared, it's probably a trap by Oni-Link."; break;
        case 182 : texte = "So you've come?*You probably want to die, it will be a pleasure to grant your wish.*Hehehehehe!!!"; break;
        case 183 : texte = "The substance of Oni-Link have been locked in the Spirit Mask!!!*You succeed!!!"; break;
        case 184 : texte = "Grrrr!!! I can't believe you defeated Oni-Link??? Impressive...*I suppose you didn't expect to see me, though we are in the dead world."; idsuiv=185; break;
        case 185 : texte = "Oni-Link gave me the energy I needed to rematerialize, so I am back earlier than I expected.*Gwahahahahaha !!!"; idsuiv=186; break;
        case 186 : texte = "By the way, maybe you wonder where Oni-Link is from? It's very easy, last time I wanted to be sure you would never disturb me again, so I used"; idsuiv=187; break;
        case 187 : texte = "the Triforce to change you into a monster in my legion. But there was not enough darkness in your heart, so this transformation was not dazzling..."; idsuiv=188; break;
        case 188 : texte = "Enough said, I have a lot of plans...*It would be a great pleasure to eliminate you, but I don't think it would be useful..."; idsuiv=189; break;
        case 189 : texte = "For your information, only creatures of the dark can get out of here.*So farewell! Gwahahahahaha !!!"; break;
        case 190 : 
            if (!gpJeu->getJoueur()->getOni()) {id=184; chercheText();break;}
            texte = "Onily? So where is my coffee???*What??? It's you Link???"; idsuiv=184; break;
        case 191 : texte = "                   Dead World"; break;
        case 192 : texte = "Link, it's Zelda, I am talking to you by telepathy. It's terrible, Ganon is back!!!"; idsuiv=193; break;
        case 193 : texte = "He has recreated his army, which is getting ready to attack Rauru!*You still can stop them, go quickly to the West Field and intercept this army!"; break;
        case 194 : texte = "You find the Great Fairy Bow!!!**Now you can shoot arrows with an incredible power!!!"; break;
        case 195 : texte = "You find the Triforce !!!"; break;
        
        case 197 : texte = "Tutorial : Press SPACE to talk, read or open a chest, and ENTER to pass the texts on the screen on."; break;
        case 198 : texte = "Press C to lift a light object."; break;
        case 199 : texte = "Do you want to save your game?**                    ? YES ?*                      no  "; break;
        case 200 : texte = "Do you want to save your game?**                      yes  *                    ? NO ?"; break;
        case 201 : texte = "                    Level 1 :                                                                                   Faron Temple"; break;
        case 202 : texte = "                    Level 2 :                                                                                     Ruto Mine"; break;
        case 203 : texte = "                    Level 3 :                                                                                   Ordona Temple"; break;
        case 204 : 
            if (gpJeu->getJoueur()->getEpee()>=2) 
                   texte = "                    Level 9 :                                                                                  Haunted Mansion";
            else   texte = "                    Level 4 :                                                                                  Haunted Mansion"; break;
        case 205 : texte = "                    Level 5 :                                                                                   Eldin Temple"; break;
        case 206 : texte = "                    Level 6 :                                                                                Monsters' Colosseum"; break;
        case 207 : texte = "                    Level 7 :                                                                                  Lanayru Temple"; break;
        case 208 : texte = "                    Level 8 :                                                                                   Zelda Temple"; break;
        case 209 : texte = "                   Level 10 :                                                                                    Din Temple"; break;
        case 210 : texte = "                   Level 11 :                                                                                   Nayru Temple"; break;
        case 211 : texte = "                   Level 12 :                                                                                   Farore Temple"; break;
        case 212 : 
            if (gpJeu->getJoueur()->getX()>14*320) {id=191; chercheText();break;}
                   texte = "                   Level 13 :                                                                                   Xanto Temple"; break;
        case 213 : texte = "                    Level ? :                                                                                   Secret Temple"; break;
        case 214 : texte = "                  Level Final :                                                                                 Destiny Tower"; break;
        case 215 : texte = "                 Already tired?                  ?                 CONTINUE                 ?                   Save and quit                               Quit without saving            "; break;
        case 216 : texte = "                 Already tired?                                    Continue                     ?               SAVE AND QUIT              ?                Quit without saving            "; break;
        case 217 : texte = "                 Already tired?                                    Continue                                     Save and quit                  ?            QUIT WITHOUT SAVING           ?"; break;
        case 218 : texte = "After Ganon's defeat and Triforce's disappearing, the legend lets us believe that peace has lasted...*But beneath each legend, a darker reality is often hidden..."; idsuiv=402; break;
        case 220 : texte = "Yes... It's this way... *We are very near..."; idsuiv=221; break;
        case 221 : texte = "I'm sorry you can't have weapons with you... But you see... You might transform yourself whenever...*It's too dangerous..."; idsuiv=222; break;
        case 222 : texte = "Here we are! That's it!*Don't move anymore, I set the portal...**Are you ready?"; break;
        case 223 : texte = "Got rid of Ganon's curse, Link could return in Hyrule safely.**The Triforce, the Master Sword, and the Ocarina were handed over to the Royal Family of Hyrule, while Oni-Link Mask was entrusted to the Fairies to be hidden over space and time...**The portal leading to Termina was sealed by Princess Zelda and by Pit, so that it could never be opened again, and this terrible chapter was erased from the legend..."; idsuiv=224; break;
        case 224 : texte = "People of Hyrule never knew what happened in the mysterious land of Termina, neither did they know that formidable Ganon was already preparing his return...**But what everybody knew, was the return in Hyrule of its hero, who will always be there to protect the Realm against the darkness."; break;
        case 225 : texte = "You find a shield!!!*Your defense rises by one point, now your resistance is stronger against the enemies' attacks!!!"; break;
        case 226 : texte = "Pit is waiting for you in the house just right here."; break;
        case 227 : 
            if (gpJeu->getJoueur()->getMagieMax()>32) texte = "...";
            else texte = "Congratulations Link, for finding me. I will raise the busload of your magic container to reward you."; break;
        case 228 : texte = "The busload of your magic container doubles !!!"; break;
        case 229 : texte = "You find the Ocarina of Time!!!**He has such a power that he can stop the time when you blow in!"; break;
        case 230 : texte = "You find the Lantern!!!**Now you can shoot up flames!!!"; break;
        case 231 : texte = "You find the Spirit Mask!!!**A strange aura shroud around it..."; break;
        case 232 : 
            if (gpJeu->getJoueur()->getTutoriel()==3) {id=233; chercheText();break;}
            gpJeu->getJoueur()->setTutoriel(3);
            texte = "Congratulations, you found me!!!**I am the desert Big Fairy, I organize rupees collections!"; idsuiv=233; break;
        case 233 : texte = "Give me 100 rupees quickly!!!**              YES ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) {idsuiv=236; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70 && gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=239; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70) {idsuiv=237; break;}
            if (gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=238; break;}
            idsuiv = 237 + (rand()%2); break;
        case 234 : texte = "Give me 100 rupees quickly!!!**              yes              NO ?"; idsuiv=235; break;
        case 235 : texte = "You make me lose my time, off you go!"; break;
        case 236 : texte = "You don't have enough rupees!!!*You make me lose my time, off you go!"; break;
        case 237 : texte = "I raise the maximum amount of bombs you can carry on, thanks to who???"; break;
        case 238 : texte = "I raise the maximum amount of arrows you can carry on, thanks to who???"; break;
        case 239 : texte = "I have enough rupees, disappear!"; break;
        case 240 : texte = "You find the Golden Gloves!!!**Now you can lift heavy stones pressing C."; break;
        case 241 : texte = "I let go through only maleficious creatures."; 
            if (gpJeu->getJoueur()->getOni()) idsuiv=243; break;
        case 242 : texte = "I let go through only beneficent creatures."; 
            if (!gpJeu->getJoueur()->getOni()) idsuiv=244; break;
        case 243 : texte = "You look maleficious...*Ok you can go!"; break;
        case 244 : texte = "You look beneficent...*Ok you can go!"; break;
        case 245 : 
            if (gpJeu->getJoueur()->getAvancement()==2) {id=250; chercheText();break;}
            texte = "You must wonder where you are.*This is Termina, and you don't need to know more than that..."; idsuiv=246; break;
        case 246 : texte = "It's a secret land which should remain secret, Princess Zelda should have never sent you here..."; idsuiv=247;  break;
        case 247 : texte = "More precisely you are in the Termina Forest. In this forest there is a temple, and in this temple there is a sacred object able to conjure any evil spell..."; idsuiv=248; break;
        case 248 : texte = "Find this object, and come back to see me.*I will open the portal again for your departure."; idsuiv=249; break;
        case 249 : texte = "A last thing, do not go out of the forest under no circumstances! Your presence here is secret, and besides, in your state you are a threat for all people you come cross..."; idsuiv=250; break;
        case 250 : texte = "Good Luck Link!"; break;
        case 251 : 
            if (gpJeu->getJoueur()->getAvancement()==3) {id=250; chercheText();break;}
            texte = "What ??? The graal didn't succeed in getting rid of the curse??? That's... unthinkable..."; idsuiv=252; break;
        case 252 : texte = "This curse must be frightfully powerful... But on closer examination, all hope is not lost..."; idsuiv=253; break;
        case 253 : texte = "The graal had an efect on you, you probably noticed it.*From now on you take less time to transform yourself."; idsuiv=254; break;
        case 254 : texte = "But it's double-edged... When you are transformed, you stay that way for a longer time..."; idsuiv=255; break;
        case 255 : texte = "Listen to me carefully Link, there are again 4 other graals in the temples of Termina...*It is said that the 5 combined have as much power as the Triforce itself."; idsuiv=256; break;
        case 256 : texte = "Thanks to the graal you found, you are a bit less dangerous, so I authorize you to explore Termina freely."; idsuiv=257; break;
        case 257 : texte = "Venture out of this forest, search and find these graals, and you will be saved.*But you must not go in a village if you are transformed."; idsuiv=258; break;
        case 258 : texte = "Take this map with you, it will probably be useful...*Good Luck!"; break;
        case 259 : 
            if (gpJeu->getJoueur()->getEpee()>=2) {id=271; chercheText();break;}
            texte = "I'm happy to see you safe and sound! Now that you don't risk being transformed anymore, I thought you would appreciate to have this..."; break;
        case 260 : texte = "You find the Master Sword!!!**Its amazing power seems to be palpable !!!"; break;
        case 261 : texte = "Unfortunately you will need it...*Oni-Link has been liberated...*We could have seen it before..."; idsuiv=262; break;
        case 262 : texte = "Each time you found a new graal, the frequency of your transformations dampenned, but the lenght of Oni-Link's life has risen..."; idsuiv=263; break;
        case 263 : texte = "Besides, Oni-Link's behavior is strange...*With his destructive temperament he should have attacked a village..."; idsuiv=264; break;
        case 264 : texte = "I should wallow, but I'm afraid that he has more important projects which is absolutely not good news..."; idsuiv=265; break;
        case 265 : texte = "However, we have drawn up a plan to vanquish him. Listen to me carefully..."; idsuiv=266; break;
        case 266 : texte = "The Master Sword is a formidable weapon, but it won't be useful to face Oni-Link...*...for the moment..."; idsuiv=267; break;
        case 267 : texte = "There are 3 secret temples hidden in Termina. In these temples are fairies whose powers will raise the strenght of your sword. Find them all!"; idsuiv=268; break;
        case 268 : texte = "Then you will be on equal footing with Oni-Link.*However, Oni-Link is only energy so he can't be killed..."; idsuiv=269; break;
        case 269 : texte = "The Spirit Mask will allow you to lock him inside forever. To do this, you will have to find this mask, find the magical Ocarina and find the melody which may lock him..."; idsuiv=270; break;
        case 270 : texte = "Your quest is just beginning..."; break;
        case 271 : texte = "Find the 3 fairies, the mask, the Ocarina, and the song of spirit, and then go to face Oni-Link!"; break;
        case 272 : 
            if (gpJeu->getJoueur()->getEpee()<2) {id=50; chercheText();break;}
            texte = "As you know, the Master Sword can defeat ghosts, reflect magical attacks back, and destroy magical fences...*Put it to good use..."; break;
        case 273 : texte = "There is not ime to loose!*Go immediately to the West Field to intercept Ganon's army!"; break;
        case 274 : texte = "Hurry up Link, what are you waiting for?*Christmas ???"; idsuiv=275; break;
        case 275 : texte = "Er... What about me ?*I... er... ...protect the princess, that's it! Who do you think has kept her from being kidnapped this time ? Huh ?"; break;
        case 276 : 
            if (gpJeu->getJoueur()->getAvancement()==69) {id=282; chercheText();break;}
            texte = "Link... there is a thing I should have told you since the beginning...*This world, Termina..."; idsuiv=277; break;
        case 277 : texte = "This world is very new, it's a creation of the Triforce through a wish... People, their memories and their stories have also been created..."; idsuiv=278; break;
        case 278 : texte = "Yes... as you guessed, it's me who asked the Triforce to create this world... It's a world built to contain all we might need."; idsuiv=279; break;
        case 279 : texte = "You found there the graals, Oni-Link found his master, and Ganon found...*...the Triforce..."; idsuiv=280; break;
        case 280 : texte = "I created this world to be used as a hideaway for the Triforce, but Ganon found it..."; idsuiv=281; break;
        case 281 : texte = "Link! This land and these people have been created, but they are truly real now! If we don't do anything, this land will soon look like the ancient Dark World!"; idsuiv=282; break;
        case 282 : texte = "I leave it to you again, Link, save this world!"; break;
        case 283 : 
            texte = "Welcome to the study house of all kind of monsters!"; 
            if (gpJeu->getJoueur()->getOni()) {idsuiv=290; break;}
            if (gpJeu->getJoueur()->hasObjet(O_ENCYCL)) {
                if (gpJeu->getJoueur()->getEpee()>1 
                && gpJeu->getJoueur()->hasObjet(O_ENCYCL)==1) {
                    gpJeu->getJoueur()->trouveObjet(O_ENCYCL,2);
                    idsuiv=294; break;
                }
                if (gpJeu->getJoueur()->getEnnemi(19)
                && gpJeu->getJoueur()->getEnnemi(24)
                && gpJeu->getJoueur()->getEnnemi(35)
                && gpJeu->getJoueur()->hasObjet(O_ENCYCL)!=3) {
                    gpJeu->getJoueur()->trouveObjet(O_ENCYCL,3);
                    idsuiv=296; break;
                }
                if (gpJeu->getJoueur()->nbEnnemis()==62) {idsuiv=297; break;}
                if (gpJeu->getJoueur()->getSolde()>0) {idsuiv=291; break;}
            }
            else {idsuiv=284; gpJeu->getJoueur()->trouveObjet(O_ENCYCL);}
            break;
        case 284 : texte = "You probably remember me, you helped me a lot in Hyrule.*Uh... You wonder how I came in Termina? Uh... doesn't matter!"; idsuiv=285; break;
        case 285 : texte = "This vast world has an abundance of monsters, so I had to be on the trip!"; idsuiv=286; break;
        case 286 : texte = "I will list all monsters in a new encyclopedia!**With your help, of course."; idsuiv=287; break;
        case 287 : texte = "Unfortunately I don't have pieces of heart anymore, but currency is my new currency. *I will pay you a good price for each new monster added in the encyclopedia."; idsuiv=288; break;
        case 288 : texte = "Come here regularly to get your winnings. If you can't carry all, I will keep the surplus for your next visit."; idsuiv=289; break;
        case 289 : texte = "You just have to beat a new enemy to add him in the encyclopedia.*You can see it by pressing M!"; break;
        case 290 : 
            texte = "Mmm... you are a curious specimen...";
            if (gpJeu->getJoueur()->getEnnemi(75) 
            || !gpJeu->getJoueur()->hasObjet(O_ENCYCL)) break;
            texte += "*I will add you in the encyclopedia!!!"; break;
        case 291 : 
            os << gpJeu->getJoueur()->getSolde();
            texte = "I owe you " + os.str() + " rupees.";
            idsuiv=292; break;
        case 292 : texte = "Do you want to be paid now?**              YES ?            no  "; break;
        case 293 : texte = "Do you want to be paid now?**              yes              NO ?"; break;
        case 294 : texte = "I have a scoop for you, monsters you defeated in Hyrule have been mysteriously brought to the life! They are supposed to wander in Termina..."; idsuiv=295; break;
        case 295 : texte = "They are said to be three.*If you beat them all, I will give you a... special prize..."; break;
        case 296 : texte = "You defeated the 3 rare monsters???*...*You reward is waiting for you downstairs..."; break;
        case 297 : texte = "You defeated all monsters...*It's incredible..."; break;
        case 298 : texte = "Hello Link, how are your bombs?"; break;
        case 299 : texte = "I don't have anymore prizes to bring into play, sorry."; break;
        case 300 : texte = "One of these chests contains a piece of heart, do you want to try for 10 rupees?*You will be allowed to open just one chest, ok?               YES ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 301 : texte = "One of these chests contains a piece of heart, do you want to try for 10 rupees?*You will be allowed to open just one chest, ok?               yes              NO ?"; break;
        case 302 : texte = "Choose a chest."; break;
        case 303 : texte = "Hey! You have to pay to open one of my chests!!!"; break;
        case 304 : texte = "You lose! This chest is empty. Try again!"; break;
        case 305 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=342; chercheText(); break;}
            texte = "What would you like to drink?"; break;
        case 306 : texte = "You are looking for the man who works in the mine? Nobody has seen him since they locked the mine... Maybe he is trapped inside..."; break;
        case 307 : texte = "This saloon was very popular...*...before..."; break;
        case 308 : texte = "I AM the mayor of this village, and I do NOT want to talk with you!"; break;
        case 309 : texte = "You say that someone is perhaps locked in the mine?**... ... ..."; 
            if (gpJeu->getJoueur()->getAvancement()==8) {id=308; chercheText();} 
            else idsuiv=310; break;
        case 310 : texte = "Very well, give me 10 rupees and I will allow you to go into the mine. Ok?*              YES ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; 
            else idsuiv=312; break;
        case 311 : texte = "Very well, give me 10 rupees and I will allow you to go into the mine. Ok?*              yes              NO ?"; break;
        case 312 : texte = "That's a deal, go and talk to the guard, he will let you pass..."; break;
        case 313 : texte = "One heart for 5 rupees, ok?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getVie() == gpJeu->getJoueur()->getVieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=44; break;
        case 314 : texte = "One heart for 5 rupees, ok?**              yes              NO ?"; break;
        case 315 : texte = "You don't need this right now."; break;
        case 316 : texte = "A little vial of magic for 15 rupees, ok?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=44; break;
        case 317 : texte = "A little vial of magic for 15 rupees, ok?**              yes              NO ?"; break;
        case 318 : texte = "A big vial of magic for 25 rupees, ok?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<25) idsuiv=44; break;
        case 319 : texte = "A big vial of magic for 25 rupees, ok?**              yes              NO ?"; break;
        case 320 : texte = "Choose what you want."; break;
        case 321 : texte = "10 arrows for 20 rupees?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()
            || !gpJeu->getJoueur()->hasObjet(O_ARC)) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=44; break;
        case 322 : texte = "10 arrows for 20 rupees?**              yes              NO ?"; break;
        case 323 : texte = "5 bombs for 30 rupees?**              YES ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=325; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=44; break;
        case 324 : texte = "5 bombs for 30 rupees?**              yes              NO ?"; break;
        case 325 : texte = "You need a bomb bag to buy this."; break;
        case 326 : texte = "Come back when you have an empty bottle and I will sell you some potions."; break;
        case 327 : texte = "Red potions restore energy and green potions restore magic."; 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            idsuiv=328; break;
        case 328 : texte = "What do you want?*                ?  RED POTION  ?*                ? green potion ?*                ?   nothing    ?"; idsuiv=331; break;
        case 329 : texte = "What do you want?*                ?  red potion  ?*                ? GREEN POTION ?*                ?   nothing    ?"; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=315;
            idsuiv=333; break;
        case 330 : texte = "What do you want?*                ?  red potion  ?*                ? green potion ?*                ?   NOTHING    ?"; break;
        case 331 : texte = "A red potion for 60 rupees?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=44; break;
        case 332 : texte = "A red potion for 60 rupees?**              yes              NO ?"; break;
        case 333 : texte = "A green potion for 40 rupees?**              YES ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=44; break;
        case 334 : texte = "A green potion for 40 rupees?**              yes              NO ?"; break;
        case 335 : texte = "You find a red potion!!!**Drink it to restore all your energy!!!"; break;
        case 336 : texte = "You find a green potion!!!**Drink it to restore all your magic!!!"; break;
        case 337 : texte = "You find a blue potion!!!**Drink it to restore all your energy and all your magic!!!"; break;
        case 338 : texte = "SANCTUARYYY!!!!!!!!"; break;
        case 339 : texte = "Oh, you too... the hens? -hiccup- !*Terrible those beasties... -hiccup-!"; break;
        case 340 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=339; chercheText(); break;}
            if (gpJeu->getJoueur()->hasCristal(3)) {id=341; chercheText(); break;}
            texte = "I used to be a fisherman a long time ago... -hiccup-! But since I saw IT... -hiccup-!*This terrible beast... -hiccup-!*In the lake... -hiccup-!"; break;
        case 341 : texte = "You defeated the monster in the lake???*... ... ...*Anyway I fear water... -hiccup-!*(I prefer wine) -hiccup-!"; break;
        case 342 : texte = "He-He-He!"; break;
        case 343 : 
            if (gpJeu->getJoueur()->getAvancement()==11) {id=344; chercheText(); break;}
            if (gpJeu->getJoueur()->getAsile()==3) {id=347; chercheText(); break;}
            if (gpJeu->getJoueur()->getRaplaplat()) {id=348; chercheText(); break;}
            texte = "Hello! I know everything about all what is said in the city, come to see me if you need information."; break;
        case 344 : 
            if (gpJeu->getJoueur()->getAvancement()!=11) {id=343; chercheText(); break;}
            texte = "You want to know why the mayor is so silent?*Okay, but I didn't say anything, huh?"; idsuiv=345; break;
        case 345 : texte = "This city has a terrible secret...*During the night, young girls are captured, we never see them again... I don't dare even to go out..."; idsuiv=346; break;
        case 346 : texte = "Last night, according to the rumours, the mayor's daughter would have disapeared..."; break;
        case 347 : 
            if (gpJeu->getJoueur()->getRaplaplat()) idsuiv=348;
            texte = "Hello! Mister-who-fears-the-hens,*He! He! He!"; break;
        case 348 : texte = "You are said to have climbed the Flatty Mountain? Congratulations! He! He! He!"; break;
        case 349 : 
            if (gpJeu->getJoueur()->getAvancement()==13) {id=50; chercheText(); break;}
            texte = "You... you know about my daughter?*It's terrible... My dear daughter..."; idsuiv=350;break;
        case 350 : texte = "According to the inquiry I conducted since the beginning of these events, the captured young girls seem to be brought into the mansion at the north village..."; idsuiv=351; break;
        case 351 : texte = "I already sent the guards there, but no one came back..."; idsuiv=352; break;
        case 352 : texte = "So this morning, when I discovered my own daughter was not here anymore, I beg my hired hand to bring her back... He is a perfect combatant, but he is abnormally slow..."; idsuiv=353; break;
        case 353 : texte = "You look to be a combatant too, do you want to see what happened there?*You will have a great reward if you rescue my daughter."; idsuiv=354; break;
        case 354 : texte = "Go to see the guard at the north-west of the city, he will let you pass."; break;
        case 355 : 
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=358; chercheText(); break;}
            texte = "My daughter told me everything, I owe you so much!!!"; idsuiv=356; break;
        case 356 : texte = "Listen carefully, I will teach you a song, it is an heirloom handed down from generation to generation:*The Elegy of Emptiness!"; break;
        case 357 : texte = "You learn the Elegy of Emptiness!!!**Use the Ocarina to play it!"; break;
        case 358 : texte = "The Elegy of Emptiness has mysterious powers...*...I think."; break;
        case 359 : texte = "Hello mister-my-rescuer!"; break;
        case 360 : 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            texte = "One blue potion for 160 rupees?*You won't be deceived...*              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=44; break;
        case 361 : texte = "One blue potion for 160 rupees?*You won't be deceived...*              yes              NO ?"; break;
        case 362 : 
            if (gpJeu->getJoueur()->hasObjet(O_GRAPPIN)) {id=364; chercheText(); break;}
            texte = "Good morning, we can't see such a powerful monster every day, it's a honour..."; idsuiv=363; break;
        case 363 : texte = "You should go to play in the Colosseum at the south-east village, there is an interesting prize to win..."; break;
        case 364 : texte = "You won the prize of the Colosseum?*Impressive..."; break;
        case 365 : texte = "If you think you are the most terrifying monster of Termina, that mean you believe your dreams are reality my poor friend..."; idsuiv=366; break;
        case 366 : texte = "Take my word, the monster of the lake is by far the most terrifying of all monsters. Most of all avoid fighting him, that's my advice."; break;
        case 367 : texte = "The colosseum south of here is the principal entertainment of the village.*The goal is to go as far as possible before being killed."; idsuiv=368; break;
        case 368 : texte = "But it's always very difficult to find volunteers, so the chief was obligated to put a very hight valued object inside."; break;
        case 369 : 
            texte = "Do you want to listen to my story for 10 rupees?**              YES ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 370 : texte = "Do you want to listen to my story for 10 rupees?**              yes              NO ?"; break;
        case 371 : texte = "According to the chief, north of here there is the Xanto temple, also known as the dead temple..."; idsuiv=372; break;
        case 372 : texte = "This temple is said to be a way from the world of living to the world of the deads... But to reach the world of the deads, you would have to go trough an impassable labyrinth..."; idsuiv=373; break;
        case 373 : texte = "Pay me again if you want me to repeat."; break;
        case 374 : 
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==1) {id=376; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==2) {id=380; chercheText(); break;}
            texte = "You are looking for the Spirit Mask?*... Fancy that..."; idsuiv=375; break;
        case 375 : texte = "No, I don't know where it is, but I know how to use it.*Come back if you find it and I will help you."; break;
        case 376 : 
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=379; chercheText(); break;}
            texte = "You find the Spirit Mask??? *...*Okay, listen carefully, I will teach you how to use it."; idsuiv=377; break;
        case 377 : texte = "In the presence of a weakened spirit, you will have to play the Song of Spirit with your ocarina.*Listen the Song of Spirit!"; break;
        case 378 : texte = "You learn the Song of Spirit!!!**Use the Ocarina to play it!"; break;
        case 379 : texte = "The Spirit Mask can be used only one time, put it to good use..."; break;
        case 380 : texte = "You locked a terribly powerful spirit...*Make sure that he never falls into bad hands..."; break;
        case 381 : texte = "Our village rarely receives visitors...*It's maybe related to the fact we blocked the entry..."; break;
        case 382 : 
            if (gpJeu->getJoueur()->hasObjet(O_BFEU)) {id=386; chercheText(); break;}
            if (gpJeu->getJoueur()->getAvancement()==66) {id=385; chercheText(); break;}
            texte = "You are the only visitor I have seen since I live here*I am an ancient adventurer, I was very talented as a treasure hunter..."; idsuiv=383;break;
        case 383 : texte = "One day I heard the story of the pyramid's treasure, a magical object...*But this desert caused my ruin, I could never cross over it. It is really too dangerous..."; idsuiv=384; break;
        case 384 : texte = "You look as determined as I was in my youth... That's a deal, if you bring me the pyramid's treasure, I will give you my most precious treasure."; break;
        case 386 : 
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=389; chercheText(); break;}
            texte = "You found the treasure???*A fire rod, huh?*...*..."; idsuiv=387; break;
        case 387 : texte = "This rod will help you more than me...*You can keep it...*"; idsuiv=388; break;
        case 388 : texte = "Accept this reward to show an old man the treasure he searched for all his life...*The Song of Soaring!!!"; break;
        case 389 : texte = "Played with a magical instrument, this song will teleport you. I had hoped I could cross over the desert with this, but I never found the good instrument..."; break;
        case 390 : texte = "You learn the Song of Soaring!!!**Use the Ocarina to play it!"; break;
        case 391 : texte = "Link! It's Pit!!!*What are you doing???*Get a move on to the West Field!!!"; break;
        case 392 : texte = "Link, it's Zelda, congratulations!!!*Rauru is safe, for the moment...*Go to the Destiny Tower at the peak of the mountain and stop Ganon!"; break;
        case 393 : texte = "Tutorial : when the gauge of anger is full, you are transformed into Oni-Link.*Your weapon is extended and your strenght increases while your defense reduces."; idsuiv=394; break;
        case 394 : texte = "As Oni-Link, you cannot use objects, but you can teleport yourself to the entry when you are in a dungeon by pressing T."; idsuiv=395; break;
        case 395 : texte = "Each time Oni-Link defeats an enemy, your gauge decreases. When it's empty, Link regain his normal form."; break;
        case 396 : texte = "Team leader, creator and programmer :                                                                         Vincent Jouillat"; break;
        case 397 : texte = "Scriptwriter and translator:                                                                                      Lobalùz"; break;
        case 398 : texte = "Help to the Graphics :                                                                                          Harvestland"; break;
        case 399 : texte = "Help to the Graphics :                                                                                        Solène Jouillat"; break;
        case 400 : texte = "Illustrator :                                                                                                      Raiden"; break;
        case 401 : texte = "You find the Termina map!!!**Press P when you are outside to see it."; break;
        case 402 : texte = "The legend forgets that after these events, the hero was brought down by a terrible curse..."; idsuiv=403; break;
        case 403 : texte = "Day by day, Link was transforming into an incontrollable and destructive powered monster named Oni-Link..."; idsuiv=404; break;
        case 404 : texte = "Banished from Hyrule, Link asked for advice from Princess Zelda."; idsuiv=405; break;
        case 405 : texte = "She indicated to him his last hope : a portal to a secret world..."; break;
        case 406 : texte = "Game saved."; break;
        case 407 : texte = "You don't need to drink this potion now."; break;
        case 408 : texte = "HELP : Press F1 to see the help."; break;
        case 409 : texte = "Grrrr... But how could you escape from the world of the deads and arrive here???"; idsuiv=410; break;
        case 410 : texte = "Why do you persist to challenge me? *Even if you strike me down I will always return to life."; idsuiv=411; break;
        case 411 : texte = "Your quest is vain, abandon all hope! **Let's rock, baby!"; break;
    }
    
    
}

void Texte::affiche(SDL_Surface* gpScreen, std::string s, int a, int b) {
    for (int i = 0; i < (int)s.length(); i++) {
        afficheLettre(gpScreen, s.at(i),a,b);
        a+=6;
    }
}

void Texte::draw(SDL_Surface* gpScreen) {
    
    if (cadre) drawCadre(gpScreen);
    
    if (id==3 && texte == "You find a piece of heart!!!") {
        SDL_Rect src; SDL_Rect dst;
        src.x=16*(gpJeu->getJoueur()->nbQuarts()%4);
        if(src.x==0)src.x=16*4;
        src.y=0; src.w=16; src.h=16; dst.x=160-8; dst.y=120-8+16*5;
        SDL_BlitSurface(imageCoeur, &src, gpScreen, &dst);
    }
    
    int a = x+8; int b = y+8;
    for (int i = 0; i < av; i++) {
        afficheLettre(gpScreen, texte.at(i),a,b);
        a+=6;
        if (a > x+w-16) {a=x+8; b+=16;}
    }
    
    if(SDL_GetTicks() > lastAnimTime + vitesse && def && av < (int)texte.length()) {
        lastAnimTime = SDL_GetTicks();
        do av++;
        while (av < (int)texte.length() && texte.at(av-1) == ' ');
        if (texte.at(av-1) != ' ') gpJeu->getAudio()->playSound(0,1);
    }
}

bool Texte::isFinished() {return (av==(int)texte.length());}

int Texte::getId() {return id;}

void Texte::changeId(int i) {
    id=i; idsuiv=0; buffer="";
    chercheText();
    decoupeText();
    if (av>(int)texte.length()) av=(int)texte.length();
}

void Texte::drawCadre(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    
    src.w=8; src.h=8; src.x = 103; src.y = 100; dst.x = x; dst.y = y;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.y = 109; src.w=8;
    for (int j = 8; j < h-8; j+=16) {
        dst.y = y + j;
        src.x = 103; dst.x = x; src.h=16;
        while (dst.y + src.h > y+h && src.h>0) src.h--;
        if (src.h>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
        src.x = 129; dst.x = x+w-8;
        if (src.h>0)SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.h=8; src.x = 103; src.y = 126; dst.x = x; dst.y = y+h-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    
    src.x = 112;
    for (int i = 8; i < w-8; i+=16) {
        dst.x = x+i; src.w=16;
        while (dst.x + src.w > x+w && src.w>0) src.w--;
        if (src.w>0) SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
    }
    
    src.w=8; src.x = 129; dst.x = x+w-8;
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

void Texte::setTexte(int idTxt, int vx, int vy, int vw, int vh, bool cadr, bool defil, int vit) {
    if (idTxt == 0) return;
    id = idTxt; 
    idsuiv = 0;
    buffer = "";
    chercheText();
    
    x = vx; y = vy; w = vw; h = vh;
    decoupeText();
        
    def=defil;
    if (def) av = 0;
    else av = texte.length();
    
    cadre = cadr;
    
    vitesse = vit;
}

void Texte::decoupeText() {
    //compte le nombre de caractères possibles et largeur et en hauteur
    int nbcol = (w-16)/6 -1;
    int nblig = (h-16)/16;
    int tailleMax = nbcol * nblig;
    int taille;
    
    //parcours du texte à afficher; à chaque début de mot, 
    //vérifie que le mot peut tenir sur la ligne
    for (int i = 0; i < (int)texte.length(); i++) {
        
        //supprime les espaces isolés en début de ligne
        if (texte.at(i)==' ' && texte.at(i+1)!=' ' && i%nbcol == 0) texte.erase(i,1);
        //recherche du début du prochain mot
        while(texte.at(i)==' ' && i < (int)texte.length()-1) i++;
        
        //saute une ligne si trouve une étoile
        if (texte.at(i)=='*') {
            texte.erase(i,1);//replace(i, 1, " ");
            int nb = (nbcol)-(i%(nbcol));
            for (int j = 0; j < nb; j++) texte.insert(i," ");
            continue;
        }
        
        //si le mot dépasse
        taille = tailleMot(i);
        if ((i%nbcol)+taille>nbcol) {
            if  (i < tailleMax) {
                //si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille>nbcol) {
                    texte.insert(((i/nbcol)+1)*nbcol-1,"--");
                    i = 1+((i/nbcol)+1)*nbcol;
                }
                //sinon, on ajoute des espaces pour faire commencer le mot à la ligne
                else while((i%nbcol) != 0) {texte.insert(i," "); i++;}
            }
        }
        
    }
    
    // si le texte est trop grand, on le coupe en deux
    if ((int)texte.length() > tailleMax) {
        buffer = texte.substr(tailleMax);
        texte = texte.substr(0, tailleMax);
    }
}

int Texte::tailleMot(int deb) {
    int i = deb;
    int total = 0;
    while (texte.at(i)!=' ') {total++; i++; if (i >= (int)texte.length()) return total;}
    return total;
}

void Texte::afficheLettre(SDL_Surface* gpScreen, char c, int vx, int vy) {
    SDL_Rect src;
    SDL_Rect dst;
    
    int val = (int)c;
    
    dst.x=vx; dst.y=vy;
    src.h=16;src.w=8;
    
    if(val==32) return;

    // es
    // ñ
    if(val=='ñ') {src.x=164;src.y=68;}
    // ó
    if(val=='ó') {src.x=164;src.y=103;}
    // í
    if(val=='í') {src.x=164;src.y=52;}
    // á
    if(val=='á') {src.x=164;src.y=84;}
    // á
    if(val=='á') {src.x=164;src.y=151;}
    
	// de
    // ß
    if(val=='ß') {src.x=6+16*3; src.y=167;}
    
    // Ä
    if(val=='Ä') {src.x=6; src.y=167;}
    
    // Ö
    if(val=='Ö') {src.x=6+16; src.y=167;}
    
    // Ü
    if(val=='Ü') {src.x=6+16*2; src.y=167;}
    

    // it
    // ì
    if(val=='ì') {src.x=164;src.y=36;}
    // ò
    if(val=='ò') {src.x=164;src.y=119;}
 

    // /
    if(val==47) {src.x=52;src.y=151;}
    
    // @ hylien
    if(val==64) {src.x=4;src.y=151;}
            
    // + hylien
    if(val==43) {src.x=20;src.y=151;}
            
    // = hylien
    if(val==61) {src.x=36;src.y=151;}
            
    //minuscules a-z
    if(val>=97 && val<=122) {src.x=4+16*((val-97)%10); src.y=52+16*((val-97)/10);}
            
    //majuscules A-Z
    if(val>=65 && val<=90) {src.x=6+16*((val-65)%10); src.y=2+16*((val-65)/10);}   
    // ç
    if(val=='ç') {src.x=148;src.y=34;}
    // é
    if(val=='é') {src.x=100;src.y=84;}
    // ê
    if(val=='ê') {src.x=116;src.y=84;}
    // è
    if(val=='è') {src.x=132;src.y=84;}
    // ë
    if(val=='ë') {src.x=132;src.y=151;}
    // à
    if(val=='à') {src.x=148;src.y=84;}
    // â
    if(val=='â') {src.x=148;src.y=103;}
    // ä
    if(val=='ä') {src.x=148;src.y=135;}
    // î
    if(val=='î') {src.x=84;src.y=119;}
    // ï
    if(val=='ï') {src.x=116;src.y=151;}
    // û
    if(val=='û') {src.x=84;src.y=103;}
    // ù
    if(val==-'ù') {src.x=148;src.y=151;}
    // ü
    if(val=='ü') {src.x=116;src.y=135;}
    // ö
    if(val=='ö') {src.x=132;src.y=135;}
    // ô
    if(val=='ô') {src.x=148;src.y=119;}
            
    //ponctuation
    // -
    if(val==45) {src.x=102;src.y=34;}
    // .
    if(val==46) {src.x=118;src.y=34;}
    // ,
    if(val==44) {src.x=134;src.y=34;}
    // !
    if(val==33) {src.x=3;src.y=135;}
    // ?
    if(val==63) {src.x=19;src.y=135;}
    // (
    if(val==40) {src.x=35;src.y=135;}
    // )
    if(val==41) {src.x=51;src.y=135;}            
    // ' ( avec @ )
    if(val==39) {src.x=67;src.y=135;}
    // :
    if(val==58) {src.x=83;src.y=135;}
    // ... ( avec % )
    if(val==37) {src.x=101;src.y=135;}
    // >
    if(val==62) {src.x=100;src.y=151;}
    // <
    if(val==60) {src.x=84;src.y=151;}
            
    //chiffres            
    if(val>=48 && val<=57) {src.x=3+16*((val-48)%5); src.y=103+16*((val-48)/5);}
    
    SDL_BlitSurface(imageFont, &src, gpScreen, &dst);
}

bool Texte::hasNext() {
    return (buffer != "" || idsuiv > 0);
}

bool Texte::suite() {
    if (av < (int)texte.length()) {
        av = texte.length();
        return true;
    }
    if (!hasNext()) {
        gpJeu->getAudio()->playSound(18);
        return gpJeu->finTexte(id);
    }
    if (buffer != "") {
        texte = buffer;
        buffer = "";
    }
    else {
        id = idsuiv;
        idsuiv = 0;
        chercheText();
    }
    decoupeText();
    if (def) av = 0;
    else av = texte.length();
    gpJeu->getAudio()->playSound(17);
    return true;
}
