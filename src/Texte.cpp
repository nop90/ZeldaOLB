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
	
switch(getLanguage()) {

case 2: // French
    switch (id) {
        case 3  : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = "Tu as trouv� un quart de coeur !!!";
            if (tmp<4) buffer = "Encore "+os.str()+" et tu gagneras un coeur suppl�mentaire !!!";
            else buffer = "Ton nombre de coeurs vient d'augmenter !!!";
            break;
        case 5 : texte = "Grotte du portail scell�.**Entr�e interdite."; break;
        case 6 : texte = "Temple de Firone**Sauvez les arbres, mangez du castor!"; break;
        case 7 : texte = "Tu as trouv� les bottes de P�gases !!! *Maintiens R pour courir."; break;
        case 8 : texte = "N : Plaine Est"; break;
        case 9 : texte = "O : Lac de Lanelle"; break;
        case 10 : texte = "S : For�t interdite"; break;
        case 11 : texte = "S : Lac de Lanelle"; break;
        case 12 : texte = "N : Vers le Temple Latouane"; break;
        case 13 : texte = "N : Village de Ruto"; break;
        case 14 : texte = "-Service Anti Monstres Urluberlus et Sauvages- (S.A.M.U.S.)**Entrez si vous n'aimez pas les monstres."; break;
        case 15 : texte = "O : Ville de Rauru"; break;
        case 16 : texte = "Vous n'avez appris aucun th�me.";
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=17; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=26; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=28; chercheText();break;}
            break;
        case 17 : texte = "- CHANT DE L'ENVOL*- Ne rien jouer";
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=19; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=30; chercheText();break;}
            break;
        case 18 : texte = "- Chant de l'envol*- NE RIEN JOUER"; break;
        case 19 : texte = "- CHANT DE L'ENVOL*- Hymne du vide*- Ne rien jouer";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=22; chercheText();break;}
            break;
        case 20 : texte = "- Chant de l'envol*- HYMNE DU VIDE*- Ne rien jouer"; break;
        case 21 : texte = "- Chant de l'envol*- Hymne du vide*- NE RIEN JOUER"; break;
        case 22 : texte = "- CHANT DE L'ENVOL*- Hymne du vide*- Chant de l'esprit*- Ne rien jouer"; break;
        case 23 : texte = "- Chant de l'envol*- HYMNE DU VIDE*- Chant de l'esprit*- Ne rien jouer"; break;
        case 24 : texte = "- Chant de l'envol*- Hymne du vide*- CHANT DE L'ESPRIT*- Ne rien jouer"; break;
        case 25 : texte = "- Chant de l'envol*- Hymne du vide*- Chant de l'esprit*- NE RIEN JOUER"; break;
        case 26 : texte = "- HYMNE DU VIDE*- Ne rien jouer";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=33; chercheText();break;}
            break;
        case 27 : texte = "- Hymne du vide*- NE RIEN JOUER"; break;
        case 28 : texte = "- CHANT DE L'ESPRIT*- Ne rien jouer"; break;
        case 29 : texte = "- Chant de l'esprit*- NE RIEN JOUER"; break;
        case 30 : texte = "- CHANT DE L'ENVOL*- Chant de l'esprit*- Ne rien jouer"; break;
        case 31 : texte = "- Chant de l'envol*- CHANT DE L'ESPRIT*- Ne rien jouer"; break;
        case 32 : texte = "- Chant de l'envol*- Chant de l'esprit*- NE RIEN JOUER"; break;
        case 33 : texte = "- HYMNE DU VIDE*- Chant de l'esprit*- Ne rien jouer"; break;
        case 34 : texte = "- Hymne du vide*- CHANT DE L'ESPRIT*- Ne rien jouer"; break;
        case 35 : texte = "- Hymne du vide*- Chant de l'esprit*- NE RIEN JOUER"; break;
        case 36 : texte = "N : Village de Ruto*S : Plaine Est"; break;
        case 37 : texte = "S : Village de Ruto*E : Vers le d�sert"; break;
        case 38 : texte = "Entr�e de la mine"; break;
        case 39 : texte = "O : Vers le Temple Latouane*E : Village de Ruto"; break;
        case 40 : texte = "D�sol�, je n'avais qu'un seul flacon."; break;
        case 41 : texte = "Je vends un flacon pour 100 rubis, �a t'int�resse ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->hasBouteille(0)) {id=40; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) idsuiv=44;
            else idsuiv=45;
            break;
        case 42 : texte = "Je vends un flacon pour 100 rubis, �a t'int�resse ?*              oui              NON ?"; idsuiv=43; break;
        case 43 : texte = "Reviens me voir si tu changes d'avis."; break;
        case 44 : texte = "Tu n'as pas assez !"; break;
        case 45 : texte = "Merci !"; break;
        case 46 : texte = "Tu as trouv� un flacon vide !!!**Tu vas pouvoir stocker des potions dedans."; break;
        case 47 : texte = "Il y a un passage secret � l'Ouest du village qui m�ne au temple de Latouane, mais tu auras besoin de bombes pour l'emprunter."; break;
        case 49 :
            if (gpJeu->getJoueur()->getAvancement()>3 && !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) 
                texte = "Si tu cherches un sac de bombes, tu devrais aller voir l'homme qui travaille � la mine, il en utilise beaucoup.";
            else texte = "Ne tra�ne pas dans mes pattes !"; break;
        case 50 : 
            if (gpJeu->getJoueur()->getAvancement()==5 || gpJeu->getJoueur()->getAvancement()==6)
                texte = "L'acc�s � la mine est strictement interdit sur ordre du maire depuis que des monstres en sortent.";
            else if (gpJeu->getJoueur()->getAvancement()==7)
                texte = "Tu dis que quelqu'un est peut-�tre bloqu� dans la mine ? Et alors ?";
            else if (gpJeu->getJoueur()->getAvancement()==8 || gpJeu->getJoueur()->getAvancement()==9)
                texte = "Le maire t'a autoris� � passer ? Alors �carte-toi !";
            else texte = "..."; break;
        case 54 : texte = "Bienvenue au village de Ruto.**Et tout � fait entre nous, m�fie-toi de tout le monde ici..."; break;
        case 55 : texte = "Ce village � la fa�ade prosp�re est en v�rit� le plus pauvre de Termina...*Et il ne faut pas compter sur le maire pour que �a change..."; break;
        case 56 : texte = "Les touristes qui viennent dans ce village sont soit perdus, soit compl�tement fous.**Pour ma part j'ai toujours une carte sur moi."; break;
        case 57 : texte = "S : Vers la Plaine Est*O : Vers le temple de Latouane*E : Village de Ruto"; break;
        case 58 : texte = "S : Plaine Est"; break;
        case 59 : texte = "Temple de Latouane"; break;
        case 60 : texte = "E : Terres oubli�es"; break;
        case 61 : texte = "S : Village de Ruto*O : Mort certaine"; break;
        case 62 : texte = "Oasis f��rique"; break;
        case 63 : texte = "Grotte de la F�e"; break;
        case 64 : texte = "Temple de Din**La puissance des f�es r�compensera les braves !"; break;
        case 65 : texte = "                     ???"; break;
        case 66 : texte = "Temple de Lanelle"; break;
        case 67 : texte = "O : Marais de la sorci�re"; break;
        case 68 : texte = "E : For�t interdite"; break;
        case 69 : texte = "N : Plaine Est*O : Vers la ville de Rauru"; break;
        case 70 : texte = "N : Ville de Rauru"; break;
        case 71 : texte = "O : Plaine Ouest"; break;
        case 72 : texte = "N : Terres oubli�es*S : Ville de Rauru"; break;
        case 73 : texte = "N : Ville de Rauru*S : Lac de Lanelle*O : Plaine Ouest*E : Plaine Est"; break;
        case 74 : texte = "E : Plaine Est"; break;
        case 75 :  texte = "D�sol�, je n'ai plus rien en stock."; break;
        case 76 : texte = "Je vends un meilleur bouclier pour 250 rubis, �a t'int�resse ?*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getBouclier()>1) {id=75; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<250) idsuiv=44;
            else idsuiv=45;
            break;
        case 77 : texte = "Je vends un meilleur bouclier pour 250 rubis, �a t'int�resse ?*              oui              NON ?"; idsuiv=43; break;
        case 78 : texte = "Tu as trouv� un nouveau bouclier !!!**Ta d�fense augmente d'un point, tu r�sistes mieux aux attaques ennemies !!!"; break;
        case 79 : texte = "Pourquoi est-ce encore � moi de m'occuper de ces poules ???"; break;
        case 80 : texte = "J'aime balayer !"; break;
        case 81 : texte = "Rauru est la plus belle ville du pays, de nombreux visiteurs arrivent chaque jour pour la contempler."; break;
        case 82 : texte = "On dit qu'un instrument magique se trouve quelque part sur les terres de Termina. *Je me demande si je le verrai un jour..."; break;
        case 83 : texte = "Tu as trouv� l'instrument magique ???**Et moi qui esp�rais que ce soit un saxo..."; break;
        case 84 : texte = "Mes parents se sont perdus."; break;
        case 85 : texte = "J'aime me promener !"; break;
        case 86 : texte = "S : Ville de Rauru*E : Maison hant�e"; break;
        case 87 : texte = "Maison hant�e**Venez enrichir notre collection d'�mes !"; break;
        case 88 : texte = "E : Vers le Temple Latouane"; break;
        case 89 : texte = "Temple de Farore**La puissance des f�es r�compensera les braves !"; break;
        case 90 : texte = "O : Village de Mido"; break;
        case 91 : texte = "N : Montagnes du destin"; break;
        case 92 : texte = "Temple de Zelda"; break;
        case 93 : texte = "O : Cimeti�re"; break;
        case 94 : texte = "Secret du d�sert :*Soul�ve les pierres de l'oiseau dans le sens des aiguilles d'une montre en finissant par l'oeil pour ouvrir le chemin."; break;
        case 95 : texte = "S : Marais de la sorci�re"; break;
        case 96 : texte = "E : Ville de Rauru"; break;
        case 97 : texte = "N : Plaine Ouest*S : Hutte de la sorci�re"; break;
        case 98 : texte = "O : Village de Kasuto*E : Hutte de la sorci�re"; break;
        case 99 : texte = "Hutte aux potions**Venez �changer vos rubis contre les potions les plus puissantes du pays !!!"; break;
        case 100 : texte = "E : Lac de Lanelle"; break;
        case 101 : texte = "N : Cimeti�re*S : Village de Kasuto"; break;
        case 102 : texte = "Village de Kasuto**   -- Interdit aux humains (vivants) --"; break;
        case 103 : texte = "Astuce : Maintient L pour regarder autour de toi avec les fl�ches de directions."; break;
        case 104 : texte = "N : Village de Kasuto*E : Marais de la sorci�re"; break;
        case 105 : texte = "Colis�e des monstres**Venez nombreux !"; break;
        case 106 : texte = "T'as l'air plut�t fort, tu devrais aller t'entra�ner dans l'ar�ne au Sud du village. On dit qu'un objet tr�s utile y est cach�..."; break;
        case 107 : texte = "Tiens ?*Une nouvelle esp�ce ?**Est-ce que tu sais parler ?"; break;
        case 108 : texte = "Ce village est le dernier rempart contre l'humanit�."; break;
        case 109 : texte = "Bonjour, je suis un monstre d�bile."; break;
        case 110 : texte = "Bloqu� ?***La solution n'est pourtant pas loin."; break;
        case 111 : texte = "S : Village de Kasuto"; break;
        case 112 : texte = "Temple de Xanto**Les morts ne racontent pas d'histoires..."; break;
        case 113 : texte = "Avez-vous d�j� essay� le marteau sur les cr�nes ?"; break;
        case 114 : texte = "E : Plaine Ouest"; break;
        case 115 : texte = "Village de Mido"; break;
        case 116 : texte = "Est-ce que tous les jeunes de ton �ge ont d'aussi mauvais go�ts vestimentaires ?"; break;
        case 117 : texte = "Bienvenue au village de Mido, mais ne te sens pas oblig� de rester."; break;
        case 118 : texte = "Grrr... je pensais �tre enfin tranquille ici..."; break;
        case 119 : texte = "Seul le vide infini pourra �ter cette pierre."; break;
        case 120 : texte = "Temple de Nayru**La puissance des f�es r�compensera les braves !"; break;
        case 121 : texte = "Passe du destin**Seul l'alli� du bien et du mal franchira cette grotte."; break;
        case 122 : texte = "S : Village de Mido"; break;
        case 123 : texte = "Temple d'Ordinn"; break;
        case 124 : texte = "S : Plaine Ouest"; break;
        case 125 : texte = "La force des titans reviendra au h�ros l�gendaire..."; break;
        case 126 : texte = "Tour du Destin**H�ros d'Hyrule prends garde, ici tr�ne d�sormais le vil Ganon, ici se jouera l'avenir du monde."; break;
        case 127 : texte = "F�licitation !**Tu as r�ussi � atteindre le sommet du mont Raplaplat !"; break;
        case 128 : texte = "Tu ne dois pas te transformer ici !!!"; break;
        case 129 : texte = "Tu ne peux pas entrer dans ce village sous cette apparence !!!"; break;
        case 130 : texte = "Link, c'est Pit. Je te parle par t�l�pathie. Tu ne dois en aucun cas te transformer dans un village !*Je te t�l�porte � l'ext�rieur."; break;
        case 131 : texte = "Tu as trouv� une �p�e !!!**Appuie sur B pour attaquer ou maintiens B pour charger une super attaque."; break;
        case 132 : texte = "Tu as trouv� la carte !!!**Appuie sur START pour voir le plan du donjon."; break;
        case 133 : texte = "Tu as trouv� la boussole !!!**Les coffres et le boss du donjon sont d�sormais indiqu�s sur la carte."; break;
        case 134 : texte = "Tu as trouv� la cl� du boss !!!**Sers-t'en pour acc�der � son repaire."; break;
        case 135 : texte = "Tu as trouv� une petite cl�.**Sers-t'en pour d�verrouiller une porte."; break;
        case 136 : texte = "Tu as trouv� un nouveau coeur !!!**Ta vie maximale augmente d'un coeur !!!"; break;
        case 137 : texte = "Tu as trouv� un Graal !!!"; break;
        case 138 : texte = "Tu es venu me sauver ?*Merci beaucoup !"; 
            if (gpJeu->getMonde()->regionValue(0)==160*16) {
                if (gpJeu->getJoueur()->getCoffre(1,25)) {id=50; chercheText();break;}
                else idsuiv = 139;}
            if (gpJeu->getMonde()->regionValue(0)==180*16 
                && gpJeu->getMonde()->regionValue(1)==15*16) {
                if (gpJeu->getJoueur()->getCoffre(1,26)) {id=50; chercheText();break;}
                else idsuiv = 140;}
            if (gpJeu->getMonde()->regionValue(0)==180*16 
                && gpJeu->getMonde()->regionValue(1)==45*16)  {
                if (gpJeu->getJoueur()->getCoffre(1,27)) {id=50; chercheText();break;}
                else idsuiv = 141;}
            break;
        case 139 : texte = "En creusant des galeries nous avons d�couvert ce repaire de monstres..."; idsuiv=142; break;
        case 140 : texte = "Nous avons tous �t� captur�s par les monstres vivants dans ces cavernes."; idsuiv=142; break;
        case 141 : texte = "Notre chef est � l'�tage en dessous, va vite le sauver!"; idsuiv=142; break;
        case 142 : texte = "J'ai trouv� �a dans la mine, prends-la, �a devrait t'aider!"; break;
        case 143 : 
            if (gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=50; chercheText();break;}
            texte = "Tu as vaincu le monstre de cette mine ???*F�licitation!!!"; idsuiv=144; break;
        case 144 : texte = "Je suis le chef des ouvriers, tu dis que tu me cherchais ?"; idsuiv=145; break;
        case 145 : texte = "Prends ce sac rempli de bombes, �a devrait t'aider."; break;
        case 146 : texte = "Tu as trouv� le Sac de Bombes !!!*Il est rempli en plus !!!*Appuie sur Y pour en poser."; break;
        case 147 : texte = "Tu as trouv� les Gants !!!**Tu peux d�sormais soulever les pierres l�g�res en appuyant sur C."; break;
        case 148 : 
            if (gpJeu->getJoueur()->hasObjet(O_ARC)) {id=50; chercheText();break;}
            texte = "Je suis le bras droit du maire, il m'a envoy� sauver sa fille...*Mais je me suis fait avoir, il n'y a rien � faire contre ces fant�mes..."; idsuiv=149; break;
        case 149 : texte = "Ne reste pas ici, tu ne pourras rien faire avec tes armes actuelles..."; idsuiv=150; break;
        case 150 : texte = "Pour continuer ta qu�te, suis le chemin � l'Ouest de la ville. Cet arc te permettra d'atteindre la sph�re et d'ouvrir le chemin..."; break;
        case 151 : texte = "Tu as trouv� l'Arc !!!*Tu peux d�sormais attaquer � distance et atteindre des cibles �loign�es !!!"; break;
        case 152 : 
            if (gpJeu->getJoueur()->getAvancement()>64) {id=153; chercheText();break;}
            texte = "Tu as vaincu le vampire et es venu me sauver ? Merci infiniment ! Mon p�re est le maire de la ville, va le voir, je suis s�re qu'il te r�compensera."; break;
        case 153 : texte = "Ne t'en fais pas pour moi, je peux rentrer sans aide maintenant que le vampire n'est plus."; break;
        case 154 : 
            if (gpJeu->getJoueur()->getAvancement()==13)
                texte = "Tu as re�u l'autorisation du maire ?*Sois prudent dans ce cas, ceux qui s'aventurent l�-bas ne reviennent jamais...";
            else if (gpJeu->getJoueur()->getAvancement()<13)
                texte = "Sur ordre du maire, l'acc�s � cette r�gion est strictement interdit.";
            else texte = "..."; break;
        case 155 : texte = "Tu ne peux pas fuir maintenant!"; break;
        case 156 : texte = "Tu as trouv� le Marteau !!!**Tu peux d�sormais �craser les obstacles g�nants !!!"; break;
        case 157 : texte = "Tu as trouv� le Grappin !!!**Tu peux d�sormais franchir les pr�cipices !!!"; break;
        case 158 : texte = "Hall du Colis�e"; break;
        case 159 : texte = "Ar�ne 1"; break;
        case 160 : texte = "Ar�ne 2"; break;
        case 161 : texte = "Ar�ne 3"; break;
        case 162 : texte = "Ar�ne 4"; break;
        case 163 : texte = "Remise des prix"; break;
        case 164 : texte = "Ar�ne sp�ciale**Venez tenter le prix sp�cial !!!"; break;
        case 165 : texte = "Tu as trouv� les Palmes !!!**Tu peux d�sormais traverser les �tendues d'eau !!!"; break;
        case 166 : texte = "Tu as trouv� une Cotte de Maille !!!**Ta d�fense augmente d'un point !!!"; break;
        case 167 : texte = "Tu as trouv� une meilleure Cotte de Maille !!!   *Ta d�fense augmente d'un point !!!"; break;
        case 168 : texte = "Hihihihihi !!!*F�licitation Link ! Tu as r�ussi � te d�barrasser de ta mal�diction. Et par la m�me occasion tu m'as enfin lib�r� !!!"; idsuiv=169; break;
        case 169 : texte = "Pour te r�compenser de tes efforts je ne te tuerai pas aujourd'hui, j'ai une mission plus importante."; idsuiv=170; break;
        case 170 : texte = "Si tu tiens � m'arr�ter, rejoins-moi au temple des morts si tu en as le courage.*Adieu ! Hihihihihi !!!"; break;
        case 171 : texte = "Link, c'est Zelda, je te parle par t�l�pathie. Je suis avec Pit, rejoins-nous vite, l'heure est grave."; break;
        case 172 : texte = "Bonjour Link, je t'attendais.**Je m'appelle Pit, j'ai �t� charg� de surveiller cette grotte par la princesse Zelda."; idsuiv=173; break;
        case 173 : texte = "Elle m'a pr�venu de ton arriv�e et m'a demand� de t'aider.*Ma maison est juste � c�t�, nous serons mieux pour parler, suis-moi."; break;
        case 174 : texte = "Pit t'a demand� de ne pas sortir de la for�t."; break;
        case 175 : texte = "Tu as trouv� la Baguette de Feu !!!**Tu peux d�sormais envoyer de puissantes boules de feu !!!"; break;
        case 176 : 
            if ((gpJeu->getZone() == 23 && gpJeu->getJoueur()->getCoffre(8,19))
            || (gpJeu->getZone() == 24 && gpJeu->getJoueur()->getCoffre(9,24))
            || (gpJeu->getZone() == 25 && gpJeu->getJoueur()->getCoffre(10,21))) {
                id=50; chercheText();break;}
            texte = "Je t'attendais Link.*Je transmets la puissance de la d�esse � ton �p�e pour restituer le pouvoir d'Excalibur."; break;
        case 177 : 
            if (gpJeu->getJoueur()->getEpee()==5) {id=178; chercheText();break;}
            texte = "La puissance d'Excalibur a augment� ! **Va vite au prochain temple !"; break;
        case 178 : texte = "Excalibur a atteint sa puissance maximale !!!  *M�me Oni-Link ne devrait pas r�sister � sa lame !!!"; break;
        case 179 : texte = "Tu as trouv� la Baguette de Glace !!!**Tu peux d�sormais geler ce que tu veux !!!"; break;
        case 180 : texte = "Tu as trouv� un nouveau bouclier !!!**Ta d�fense a augment�, tu r�sistes d�sormais mieux aux attaques ennemies !!!"; break;
        case 181 : texte = "Link, c'est Zelda, je te parle par t�l�pathie. N'entre surtout pas dans ce donjon sans �tre parfaitement pr�par�, c'est sans doute un pi�ge d'Oni-Link."; break;
        case 182 : texte = "Ainsi tu es venu ?*Tu dois sans doute vouloir mourir, je vais me faire un plaisir de t'exaucer.*Hihihihihi !!!"; break;
        case 183 : texte = "L'essence d'Oni-Link a �t� enferm�e dans le masque de l'Esprit !!!*Tu as r�ussi !!!"; break;
        case 184 : texte = "Grrrr !!! Tu n'as tout de m�me pas battu Oni-Link ??? Impressionnant...*J'imagine que tu ne t'attendais pas � me voir, nous sommes pourtant dans le monde des morts."; idsuiv=185; break;
        case 185 : texte = "Oni-Link m'a donn� l'�nergie dont j'avais besoin pour me re-mat�rialiser, je suis donc de retour plus t�t que pr�vu.*Gwahahahahaha !!!"; idsuiv=186; break;
        case 186 : texte = "Au fait, tu te demandes peut-�tre d'ou vient Oni-Link ? C'est tr�s simple, la derni�re fois je voulais m'assurer que tu ne te mettrais plus en travers de mon chemin, je me suis donc servi"; idsuiv=187; break;
        case 187 : texte = "de la Triforce pour te changer en monstre � ma solde. H�las il n'y avait pas assez de t�n�bres en toi, cette transformation n'a donc pas �t� fulgurante..."; idsuiv=188; break;
        case 188 : texte = "Assez parl�, j'ai de nombreux projets...*Je me ferais une joie de t'�liminer, mais je n'en vois pas l'utilit�..."; idsuiv=189; break;
        case 189 : texte = "Pour ton information, seules les cr�atures des t�n�bres peuvent s'�chapper d'ici.*Alors adieu! Gwahahahahaha !!!"; break;
        case 190 : 
            if (!gpJeu->getJoueur()->getOni()) {id=184; chercheText();break;}
            texte = "Onily ? Alors il vient ce caf� ???*Quoi ??? C'est toi Link ???"; idsuiv=184; break;
        case 191 : texte = "                Monde des Morts"; break;
        case 192 : texte = "Link, c'est Zelda, je te parle par t�l�pathie. C'est terrible, Ganon est de retour !!!"; idsuiv=193; break;
        case 193 : texte = "Il a recr�� son arm�e, qui s'appr�te � attaquer Rauru!*Tu peux encore les arr�ter, va vite les intercepter sur la plaine Ouest!"; break;
        case 194 : texte = "Tu as trouv� le grand Arc des F�es!!!**Tu tires d�sormais des fl�ches d'une puissance extraordinaire !!!"; break;
        case 195 : texte = "Tu as trouv� la Triforce !!!"; break;
        
        case 197 : texte = "Tutoriel : appuie sur ESPACE pour parler, lire ou ouvrir un coffre, et sur ENTREE pour passer les textes � l'�cran."; break;
        case 198 : texte = "Appuie sur X pour soulever un objet l�ger."; break;
        case 199 : texte = "Souhaites-tu sauvegarder ta partie ?**                    ? OUI ?*                      non  "; break;
        case 200 : texte = "Souhaites-tu sauvegarder ta partie ?**                      oui  *                    ? NON ?"; break;
        case 201 : texte = "                   Niveau 1 :                                                                                 Temple de Firone"; break;
        case 202 : texte = "                   Niveau 2 :                                                                                   Mine de Ruto"; break;
        case 203 : texte = "                   Niveau 3 :                                                                                Temple de Latouane"; break;
        case 204 : 
            if (gpJeu->getJoueur()->getEpee()>=2) 
                texte = "                   Niveau 9 :                                                                                   Manoir hant�";
            else texte = "                   Niveau 4 :                                                                                   Manoir hant�"; break;
        case 205 : texte = "                   Niveau 5 :                                                                                 Temple d'Ordinn"; break;
        case 206 : texte = "                   Niveau 6 :                                                                               Colis�e des Monstres"; break;
        case 207 : texte = "                   Niveau 7 :                                                                                Temple de Lanelle"; break;
        case 208 : texte = "                   Niveau 8 :                                                                                 Temple de Zelda"; break;
        case 209 : texte = "                   Niveau 10 :                                                                                 Temple de Din"; break;
        case 210 : texte = "                   Niveau 11 :                                                                                Temple de Nayru"; break;
        case 211 : texte = "                   Niveau 12 :                                                                                Temple de Farore"; break;
        case 212 : 
            if (gpJeu->getJoueur()->getX()>14*320) {id=191; chercheText();break;}
            texte = "                   Niveau 13 :                                                                                Temple de Xanto"; break;
        case 213 : texte = "                   Niveau ? :                                                                                  Temple secret"; break;
        case 214 : texte = "                 Niveau Final :                                                                                Tour du Destin"; break;
        case 215 : texte = "                D�j� fatigu� ?                  ?                CONTINUER                  ?             Sauvegarder et quitter                        Quitter sans sauvegarder           "; break;
        case 216 : texte = "                D�j� fatigu� ?                                   Continuer                     ?          SAUVEGARDER ET QUITTER           ?            Quitter sans sauvegarder           "; break;
        case 217 : texte = "                D�j� fatigu� ?                                   Continuer                                Sauvegarder et quitter              ?         QUITTER SANS SAUVEGARDER          ?"; break;
        case 218 : texte = "Apr�s la d�faite de Ganon et la disparition de la Triforce, la l�gende laisse croire que la paix dura...*Mais derri�re chaque l�gende se cache souvent une plus sombre r�alit�..."; idsuiv=402; break;
        case 220 : texte = "Oui... C'est par ici... *Nous y sommes presque..."; idsuiv=221; break;
        case 221 : texte = "Je suis d�sol�e que tu ne puisses pas emmener d'armes... Mais tu comprends... Tu risques de te transformer � tout moment...*Ce serait trop dangereux..."; idsuiv=222; break;
        case 222 : texte = "Ca y est! C'est ici!*Ne bouge plus, j'active le portail...**Est-ce que tu es pr�t ?"; break;
        case 223 : texte = "D�barrass� de la mal�diction de Ganon, Link put retourner � Hyrule sans risque.**La Triforce, Excalibur, ainsi que l'Ocarina furent remis � la famille royale d'Hyrule, tandis que le masque d'Oni-Link fut confi� aux f�es pour �tre cach� par del� le temps et l'espace...**Le portail menant � Termina fut scell� par la princesse Zelda et par Pit, pour ne jamais plus �tre ouvert, et ce terrible chapitre fut effac� de la l�gende..."; idsuiv=224; break;
        case 224 : texte = "Le peuple d'Hyrule ne sut jamais ce qui se joua dans les myst�rieuses contr�es de Termina, ni que le redoutable Ganon pr�parait d�j� son retour...**Mais ce que personne n'ignorait, fut le retour � Hyrule de son h�ros, qui sera toujours l� pour d�fendre le Royaume face aux t�n�bres."; break;
        case 225 : texte = "Tu as trouv� un bouclier !!!**Ta d�fense augmente d'un point, tu r�sistes mieux aux attaques ennemies !!!"; break;
        case 226 : texte = "Pit t'attend dans la maison juste � c�t�."; break;
        case 227 : 
            if (gpJeu->getJoueur()->getMagieMax()>32) texte = "...";
            else texte = "F�licitation Link, tu as r�ussi � me trouver. Je vais augmenter la capacit� de ta r�serve de magie pour te r�compenser."; break;
        case 228 : texte = "La capacit� de ta jauge de magie a doubl� !!!"; break;
        case 229 : texte = "Tu as trouv� l'Ocarina du Temps !!!**Sa puissance est telle qu'il stoppe le temps lorsque tu souffles dedans !"; break;
        case 230 : texte = "Tu as trouv� la Lanterne !!!**Tu peux d�sormais faire jaillir des flammes!!!"; break;
        case 231 : texte = "Tu as trouv� le Masque des Esprits !!!**Une �trange aura s'en d�gage..."; break;
        case 232 : 
            if (gpJeu->getJoueur()->getTutoriel()==3) {id=233; chercheText();break;}
            gpJeu->getJoueur()->setTutoriel(3);
            texte = "F�licitation, tu m'as trouv�e !!!**Je suis la grosse f�e du d�sert, j'organise des collectes de rubis !"; idsuiv=233; break;
        case 233 : texte = "Donne-moi vite 100 rubis !!!**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) {idsuiv=236; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70 && gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=239; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70) {idsuiv=237; break;}
            if (gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=238; break;}
            idsuiv = 237 + (rand()%2); break;
        case 234 : texte = "Donne-moi vite 100 rubis !!!**              oui              NON ?"; idsuiv=235; break;
        case 235 : texte = "Tu me fais perdre mon temps, oust!"; break;
        case 236 : texte = "Tu n'as m�me pas assez!!!*Tu me fais perdre mon temps, oust!"; break;
        case 237 : texte = "J'augmente le nombre maximal de bombes que tu peux transporter, merci qui ???"; break;
        case 238 : texte = "J'augmente le nombre maximal de fl�ches que tu peux transporter, merci qui ???"; break;
        case 239 : texte = "J'ai assez de rubis, disparait!"; break;
        case 240 : texte = "Tu as trouv� les Gants d'Or !!!**Tu peux d�sormais soulever les pierres lourdes en appuyant sur X."; break;
        case 241 : texte = "Je ne laisserai passer que les cr�atures malfaisantes."; 
            if (gpJeu->getJoueur()->getOni()) idsuiv=243; break;
        case 242 : texte = "Je ne laisserai passer que les cr�atures bienfaisantes."; 
            if (!gpJeu->getJoueur()->getOni()) idsuiv=244; break;
        case 243 : texte = "Tu as l'air malfaisant...*Ok tu peux passer!"; break;
        case 244 : texte = "Tu as l'air bienfaisant...*Ok tu peux passer!"; break;
        case 245 : 
            if (gpJeu->getJoueur()->getAvancement()==2) {id=250; chercheText();break;}
            texte = "Tu dois te demander ou tu es.*Ici c'est Termina, et tu n'as pas besoin d'en savoir plus � ce sujet..."; idsuiv=246; break;
        case 246 : texte = "C'est une terre secr�te qui aurait d� le rester, la princesse Zelda n'aurait jamais d� t'envoyer ici..."; idsuiv=247;  break;
        case 247 : texte = "Plus pr�cis�ment tu te trouves dans la for�t de Termina. Dans cette for�t se trouve un temple, et dans ce temple se trouve un objet sacr� capable de conjurer n'importe quel mal�fice..."; idsuiv=248; break;
        case 248 : texte = "Trouve cet objet, puis reviens me voir.*J'ouvrirai le portail � nouveau pour que tu puisses repartir."; idsuiv=249; break;
        case 249 : texte = "Une derni�re chose, ne quitte la for�t � aucun prix! Ta pr�sence ici est secr�te, et de plus, dans ton �tat tu constitues une menace pour tous ceux que tu croises..."; idsuiv=250; break;
        case 250 : texte = "Bonne chance Link!"; break;
        case 251 : 
            if (gpJeu->getJoueur()->getAvancement()==3) {id=250; chercheText();break;}
            texte = "Quoi ??? Le graal n'a pas r�ussi � te d�barrasser de la mal�diction ??? C'est... impensable..."; idsuiv=252; break;
        case 252 : texte = "Cette mal�diction doit �tre terriblement puissante... Mais si tu y regardes de plus pr�s tout espoir n'est pas perdu..."; idsuiv=253; break;
        case 253 : texte = "Le graal a eu un effet sur toi, tu as d� le remarquer.*D�sormais tu mets plus de temps � te transformer."; idsuiv=254; break;
        case 254 : texte = "Mais c'est � double tranchant... Car une fois  transform�, tu le restes plus longtemps..."; idsuiv=255; break;
        case 255 : texte = "Ecoute-moi bien Link, il reste encore 4 autres graals dans les temples de Termina...*Il est dit que les 5 r�unis ont autant de pouvoir que la Triforce elle-m�me."; idsuiv=256; break;
        case 256 : texte = "Gr�ce au graal que tu as trouv�, tu es d�j� un peu moins dangereux, je t'autorise donc � explorer librement Termina."; idsuiv=257; break;
        case 257 : texte = "Aventure-toi hors de cette for�t, cherche et trouve ces graals, et tu seras sauv�.*Mais tu ne dois en aucun cas t'aventurer dans un village en �tant m�tamorphos�."; idsuiv=258; break;
        case 258 : texte = "Prends cette carte avec toi, elle te sera certainement utile...*Bonne chance!"; break;
        case 259 : 
            if (gpJeu->getJoueur()->getEpee()>=2) {id=271; chercheText();break;}
            texte = "Heureuse de te voir sain et sauf Link ! Maintenant que tu ne risques plus de te transformer, j'ai pens� que tu appr�cierais d'avoir ceci..."; break;
        case 260 : texte = "Tu as trouv� Excalibur!!!**Sa puissance extraordinaire semble palpable !!!"; break;
        case 261 : texte = "Tu vas h�las en avoir grand besoin...*Oni-Link a �t� lib�r�...*Nous aurions d� le voir plus t�t..."; idsuiv=262; break;
        case 262 : texte = "A chaque nouveau graal trouv�, la fr�quence de tes transformations diminuait, mais la dur�e d'existence d'Oni-Link augmentait..."; idsuiv=263; break;
        case 263 : texte = "De plus, le comportement d'Oni-Link me semble �trange...*Sa nature destructrice aurait d� le pousser � attaquer un village..."; idsuiv=264; break;
        case 264 : texte = "Je devrais me r�jouir, mais j'ai peur que de savoir qu'il a des desseins plus importants n'ait rien d'une bonne nouvelle..."; idsuiv=265; break;
        case 265 : texte = "Nous avons toutefois �tabli un plan pour le vaincre. Ecoute-moi attentivement..."; idsuiv=266; break;
        case 266 : texte = "Excalibur est une arme redoutable, mais elle ne fera pas le poids contre Oni-Link...*...pour l'instant..."; idsuiv=267; break;
        case 267 : texte = "Il y a 3 temples secrets cach�s � Termina. Dans ces temples se trouvent des f�es dont les pouvoirs augmenteront la puissance de ton �p�e. Trouve-les toutes!"; idsuiv=268; break;
        case 268 : texte = "Tu seras alors en mesure de faire jeu �gal avec Oni-Link.*Cependant, Oni-Link n'est qu'�nergie et ne peut donc pas �tre vaincu..."; idsuiv=269; break;
        case 269 : texte = "Le Masque des Esprits te permettra de l'enfermer � jamais. Pour ce faire, tu devras trouver ce masque, trouver l'Ocarina magique et trouver la m�lodie qui l'enfermera..."; idsuiv=270; break;
        case 270 : texte = "Ta qu�te ne fait que commencer..."; break;
        case 271 : texte = "Trouve les 3 f�es, le masque, l'Ocarina, et le chant de l'esprit, puis va affronter Oni-Link!"; break;
        case 272 : 
            if (gpJeu->getJoueur()->getEpee()<2) {id=50; chercheText();break;}
            texte = "Comme tu le sais, Excalibur peut vaincre les fant�mes, renvoyer les attaques magiques, et d�truire les barri�res magiques...*Fais-en bon usage..."; break;
        case 273 : texte = "Il n'y a pas de temps � perdre!*Va imm�diatement � la plaine Ouest intercepter l'arm�e de Ganon!"; break;
        case 274 : texte = "Vite Link, t'attends quoi ?*No�l ???"; idsuiv=275; break;
        case 275 : texte = "Euh... Comment �a et moi ?*Je... euh... ...prot�ge la princesse, voil�!*Tu crois que c'est gr�ce � qui si elle n'a pas �t� enlev�e cette fois ? Hein ?"; break;
        case 276 : 
            if (gpJeu->getJoueur()->getAvancement()==69) {id=282; chercheText();break;}
            texte = "Link... il y a une chose que j'aurais d� te dire depuis le d�but...*Sur ce monde, Termina..."; idsuiv=277; break;
        case 277 : texte = "Ce monde est tr�s r�cent, il a �t� fabriqu� de toute pi�ce par la Triforce et par un voeu... Les gens, leurs souvenirs et leurs histoires ont ainsi �t� fabriqu�s..."; idsuiv=278; break;
        case 278 : texte = "Oui... Tu as bien devin�, c'est moi qui ai demand� � la Triforce de cr�er ce monde... C'est un monde con�u pour contenir tout ce dont on peut avoir besoin."; idsuiv=279; break;
        case 279 : texte = "Tu y as trouv� les graals, Oni-Link a retrouv� son ma�tre, et Ganon a retrouv�...*...la Triforce..."; idsuiv=280; break;
        case 280 : texte = "J'ai cr�� ce monde pour servir de cachette � la Triforce, mais Ganon l'a retrouv�e..."; idsuiv=281; break;
        case 281 : texte = "Link! Ce pays et ces gens ont �t� cr��s, mais ils sont bien r�els maintenant! Si on ne fait rien, ce monde ressemblera bient�t � l'ex-monde des t�n�bres!"; idsuiv=282; break;
        case 282 : texte = "Je m'en remets une fois de plus � toi, Link, sauve ce monde!"; break;
        case 283 : 
            texte = "Bienvenue � la maison d'�tudes des monstres en tout genre!"; 
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
        case 284 : texte = "Tu te souviens sans doute de moi, tu m'as �t� d'une grande aide � Hyrule.*Euh... Tu te demandes comment je suis arriv� � Termina ? Euh... peu importe!"; idsuiv=285; break;
        case 285 : texte = "Ce vaste monde regorge de monstres, alors je ne pouvais pas ne pas �tre du voyage!"; idsuiv=286; break;
        case 286 : texte = "Je vais donc r�pertorier chaque monstre dans une nouvelle encyclop�die!**Avec ton aide, cela va de soit."; idsuiv=287; break;
        case 287 : texte = "Je n'ai h�las plus de quarts de coeurs, mais les devises sont ma nouvelle devise.*Je te paierai un bon prix chaque nouveau monstre ajout� � l'encyclop�die."; idsuiv=288; break;
        case 288 : texte = "Passe me voir r�guli�rement pour obtenir tes gains. Si tu ne peux pas tout transporter, je garderais l'exc�dent pour ta prochaine venue."; idsuiv=289; break;
        case 289 : texte = "Il suffit de battre de nouveaux monstres pour qu'ils soient ajout�s.*Tu peux consulter l'encyclop�die en appuyant sur L et B!"; break;
        case 290 : 
            texte = "Mmm... tu es un dr�le de sp�cimen...";
            if (gpJeu->getJoueur()->getEnnemi(75) 
            || !gpJeu->getJoueur()->hasObjet(O_ENCYCL)) break;
            texte += "*Je t'ajoute � l'encyclop�die!!!"; break;
        case 291 : 
            os << gpJeu->getJoueur()->getSolde();
            texte = "Je te dois " + os.str() + " rubis.";
            idsuiv=292; break;
        case 292 : texte = "Veux-tu �tre pay� maintenant ?**              OUI ?            non  "; break;
        case 293 : texte = "Veux-tu �tre pay� maintenant ?**              oui              NON ?"; break;
        case 294 : texte = "J'ai un scoop pour toi, des monstres que tu avais vaincu � Hyrule ont myst�rieusement �t� ramen�s � la vie! Ils se baladeraient dans les contr�es de Termina..."; idsuiv=295; break;
        case 295 : texte = "Il y en aurait 3.*Si tu les bats, je t'offrirais un prix... sp�cial..."; break;
        case 296 : texte = "Tu as vaincu les 3 monstres rares ???*...*Ta r�compense t'attends au sous-sol..."; break;
        case 297 : texte = "Tu as vaincu chaque monstre...*C'est incroyable..."; break;
        case 298 : texte = "Bonjour Link, comment vont tes bombes ?"; break;
        case 299 : texte = "Je n'ai plus de prix � mettre en jeu, d�sol�."; break;
        case 300 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?              OUI ?            non  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 301 : texte = "Un de ces coffres contient un quart de coeur, tu veux tenter ta chance pour 10 rubis ?*Tu ne pourras ouvrir qu'un seul coffre, ok ?              oui              NON ?"; break;
        case 302 : texte = "Choisis un coffre."; break;
        case 303 : texte = "Hey! Il faut payer pour ouvrir un de mes coffres!!!"; break;
        case 304 : texte = "Perdu! Ce coffre est vide."; break;
        case 305 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=342; chercheText(); break;}
            texte = "Qu'est-ce que je vous sers ?"; break;
        case 306 : texte = "Tu cherches l'homme qui travaille � la mine ? Personne ne l'a revu depuis qu'ils ont condamn� la mine... Il est peut-�tre encore coinc� dedans..."; break;
        case 307 : texte = "Ce saloon �tait tr�s fr�quent�...*...autrefois..."; break;
        case 308 : texte = "JE suis le maire de ce village, et JE n'ai pas envie de te parler!"; break;
        case 309 : texte = "Tu dis que quelqu'un est peut-�tre bloqu� dans la mine ?**... ... ..."; 
            if (gpJeu->getJoueur()->getAvancement()==8) {id=308; chercheText();} 
            else idsuiv=310; break;
        case 310 : texte = "Tr�s bien, donne-moi 10 rubis et je t'autorise � acc�der � la mine. Ok ?*              OUI ?            non  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; 
            else idsuiv=312; break;
        case 311 : texte = "Tr�s bien, donne-moi 10 rubis et je t'autorise � acc�der � la mine. Ok ?*              oui              NON ?"; break;
        case 312 : texte = "March� conclu, va parler au garde, il te laissera passer..."; break;
        case 313 : texte = "Un petit coeur pour 5 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getVie() == gpJeu->getJoueur()->getVieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=44; break;
        case 314 : texte = "Un petit coeur pour 5 rubis ?**              oui              NON ?"; break;
        case 315 : texte = "Tu n'as pas besoin de �a."; break;
        case 316 : texte = "Une petite fiole de magie pour 15 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=44; break;
        case 317 : texte = "Une petite fiole de magie pour 15 rubis ?**              oui              NON ?"; break;
        case 318 : texte = "Une grande fiole de magie pour 25 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<25) idsuiv=44; break;
        case 319 : texte = "Une grande fiole de magie pour 25 rubis ?**              oui              NON ?"; break;
        case 320 : texte = "Choisis ce que tu veux.*"; break;
        case 321 : texte = "10 fl�ches pour 20 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()
            || !gpJeu->getJoueur()->hasObjet(O_ARC)) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=44; break;
        case 322 : texte = "10 fl�ches pour 20 rubis ?**              oui              NON ?"; break;
        case 323 : texte = "5 bombes pour 30 rubis ?**              OUI ?            non  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=325; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=44; break;
        case 324 : texte = "5 bombes pour 30 rubis ?**              oui              NON ?"; break;
        case 325 : texte = "Il te faut un sac de bombes pour acheter ceci."; break;
        case 326 : texte = "Reviens me voir lorsque tu auras un flacon vide et je te vendrais des potions."; break;
        case 327 : texte = "Les potions rouges redonnent de l'�nergie alors que les potions vertes redonnent de la magie."; 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            idsuiv=328; break;
        case 328 : texte = "Que d�sires-tu ?*                ? POTION ROUGE ?*                ? potion verte ?*                ?     rien     ?"; idsuiv=331; break;
        case 329 : texte = "Que d�sires-tu ?*                ? potion rouge ?*                ? POTION VERTE ?*                ?     rien     ?"; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=315;
            idsuiv=333; break;
        case 330 : texte = "Que d�sires-tu ?*                ? potion rouge ?*                ? potion verte ?*                ?     RIEN     ?"; break;
        case 331 : texte = "Une potion rouge pour 60 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=44; break;
        case 332 : texte = "Une potion rouge pour 60 rubis ?**              oui              NON ?"; break;
        case 333 : texte = "Une potion verte pour 40 rubis ?**              OUI ?            non  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=44; break;
        case 334 : texte = "Une potion verte pour 40 rubis ?**              oui              NON ?"; break;
        case 335 : texte = "Tu as trouv� une potion rouge !!!**Bois-la pour restaurer toute ton �nergie!!!"; break;
        case 336 : texte = "Tu as trouv� une potion verte !!!**Bois-la pour restaurer toute ta magie!!!"; break;
        case 337 : texte = "Tu as trouv� une potion bleue !!!**Bois-la pour restaurer ton �nergie et ta magie!!!"; break;
        case 338 : texte = "DROIT   D'ASIIIIIILE !!!!!!!!"; break;
        case 339 : texte = "Ah vous aussi... les poules ? Hic!*Terribles aussi ces bestioles... Hic!"; break;
        case 340 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=339; chercheText(); break;}
            if (gpJeu->getJoueur()->hasCristal(3)) {id=341; chercheText(); break;}
            texte = "J'�tais un p�cheur dans le temps... Hic!*Mais depuis que je L'ai vu... Hic!*Cette terrible b�te... Hic!*Dans le lac... Hic!"; break;
        case 341 : texte = "Tu as vaincu le monstre du lac tu dis ???*... ... ...*De toute fa�on j'ai peur de l'eau... Hic!*(je pr�f�re le vin) Hic!"; break;
        case 342 : texte = "H�! H�! H�!"; break;
        case 343 : 
            if (gpJeu->getJoueur()->getAvancement()==11) {id=344; chercheText(); break;}
            if (gpJeu->getJoueur()->getAsile()==3) {id=347; chercheText(); break;}
            if (gpJeu->getJoueur()->getRaplaplat()) {id=348; chercheText(); break;}
            texte = "Bonjour! Je sais tout sur tout de ce qui se dit en ville, viens me voir si tu as besoin d'infos."; break;
        case 344 : 
            if (gpJeu->getJoueur()->getAvancement()!=11) {id=343; chercheText(); break;}
            texte = "Tu veux savoir pourquoi le maire est si silencieux ?*D'accord, mais je ne t'ai rien dit, ok ?"; idsuiv=345; break;
        case 345 : texte = "Cette ville a un terrible secret...*La nuit, des jeunes filles se font enlever, on ne les retrouve jamais... Je n'ose m�me plus sortir..."; idsuiv=346; break;
        case 346 : texte = "La nuit derni�re, d'apr�s les rumeurs, ce serait la fille du maire qui aurait disparu..."; break;
        case 347 : 
            if (gpJeu->getJoueur()->getRaplaplat()) idsuiv=348;
            texte = "Bonjour! Monsieur-qui-a-peur-des-poules,*Hi! Hi! Hi!"; break;
        case 348 : texte = "On raconte que tu aurais escalad� le mont Raplaplat ? F�licitation! Hi! Hi! Hi!"; break;
        case 349 : 
            if (gpJeu->getJoueur()->getAvancement()==13) {id=50; chercheText(); break;}
            texte = "Tu... tu es au courant pour ma fille ?*C'est affreux... Ma ch�re fille..."; idsuiv=350;break;
        case 350 : texte = "D'apr�s l'enqu�te que je m�ne depuis le d�but de ces �v�nements, les jeunes filles enlev�es seraient emmen�es au manoir au Nord du village..."; idsuiv=351; break;
        case 351 : texte = "J'ai d�j� envoy� la garde l� bas, mais personne n'en est revenu..."; idsuiv=352; break;
        case 352 : texte = "Alors ce matin, en d�couvrant que ma fille n'�tait plus l�, j'ai suppli� mon homme de main de me la ramener... C'est un combattant hors pair, mais il est anormalement long..."; idsuiv=353; break;
        case 353 : texte = "Tu as l'air d'�tre un combattant, veux-tu aller voir ce qui s'y passe ?*Tu seras grandement r�compens� si tu sauves ma fille."; idsuiv=354; break;
        case 354 : texte = "Va voir le garde au Nord-Ouest du village, il te laissera passer."; break;
        case 355 : 
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=358; chercheText(); break;}
            texte = "Ma fille m'a tout racont�, je te dois �norm�ment!!!"; idsuiv=356; break;
        case 356 : texte = "Ecoute attentivement, je vais t'apprendre un chant qui se transmet dans ma famille de g�n�ration en g�n�ration :*L'Hymne du Vide!"; break;
        case 357 : texte = "Tu as appris l'Hymne du Vide!!!**Utilise l'Ocarina pour le jouer!"; break;
        case 358 : texte = "L'Hymne du Vide a de myst�rieux pouvoirs...*...Je crois."; break;
        case 359 : texte = "Bonjour monsieur-mon-sauveur!"; break;
        case 360 : 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            texte = "Une potion bleue pour 160 rubis ?*Tu ne seras pas d��u...*              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=44; break;
        case 361 : texte = "Une potion bleue pour 160 rubis ?*Tu ne seras pas d��u...*              oui              NON ?"; break;
        case 362 : 
            if (gpJeu->getJoueur()->hasObjet(O_GRAPPIN)) {id=364; chercheText(); break;}
            texte = "Bonjour, ce n'est pas tous les jours qu'un monstre aussi puissant nous fait l'honneur de sa visite..."; idsuiv=363; break;
        case 363 : texte = "Tu devrais aller t'amuser dans le colis�e au Sud-Ouest du village, il y a un prix int�ressant � gagner..."; break;
        case 364 : texte = "Tu as gagn� le prix du colis�e ?*Impressionnant..."; break;
        case 365 : texte = "Si tu crois �tre le monstre le plus effrayant de Termina, c'est que tu prends tes r�ves pour la r�alit� mon pauvre ami..."; idsuiv=366; break;
        case 366 : texte = "Crois-moi sur parole, le monstre du lac est de loin le plus terrifiant des monstres, je te conseille d'�viter par dessus tout de l'affronter."; break;
        case 367 : texte = "Le colis�e au Sud d'ici est le principal divertissement de ce village.*Le but est d'aller le plus loin possible avant de se faire tuer."; idsuiv=368; break;
        case 368 : texte = "Mais on a toujours beaucoup de mal � trouver des volontaires, alors le chef a �t� contraint d'y placer des items de grande valeur."; break;
        case 369 : 
            texte = "Veux-tu entendre mon histoire pour 10 rubis ?**              OUI ?            non  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 370 : texte = "Veux-tu entendre mon histoire pour 10 rubis ?**              oui              NON ?"; break;
        case 371 : texte = "D'apr�s le chef, au Nord d'ici se trouve le temple de Xanto, �galement connu sous le nom de temple des morts..."; idsuiv=372; break;
        case 372 : texte = "Ce temple serait un passage du monde des vivants au monde des morts... Mais pour acc�der au monde des morts, il faudrait traverser un labyrinthe infranchissable..."; idsuiv=373; break;
        case 373 : texte = "Paie-moi � nouveau si tu veux que je r�p�te."; break;
        case 374 : 
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==1) {id=376; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==2) {id=380; chercheText(); break;}
            texte = "Tu cherches le Masque des Esprits ?*... Tiens donc..."; idsuiv=375; break;
        case 375 : texte = "Non, je ne sais pas ou il se trouve, mais je sais comment l'utiliser.*Reviens me voir si tu le trouves et je pourrais t'aider."; break;
        case 376 : 
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=379; chercheText(); break;}
            texte = "Tu as trouv� le Masque des Esprits ??? *...*Alors �coute-moi bien, je vais t'apprendre � l'utiliser."; idsuiv=377; break;
        case 377 : texte = "En pr�sence d'un esprit affaiblit, tu devras jouer le chant des esprits � l'aide de ton ocarina.*Ecoute le chant des esprits!"; break;
        case 378 : texte = "Tu as appris le chant des esprits!!!**Utilise l'Ocarina pour le jouer!"; break;
        case 379 : texte = "Le Masque des Esprits ne sert qu'une fois, fais-en bon usage..."; break;
        case 380 : texte = "Tu as enferm� un esprit terriblement puissant...*Veille � ce qu'il ne tombe pas en de mauvaises mains..."; break;
        case 381 : texte = "Notre village accueille rarement des visiteurs...*Cela vient peut-�tre du fait que nous avons bloqu� l'entr�e..."; break;
        case 382 : 
            if (gpJeu->getJoueur()->hasObjet(O_BFEU)) {id=386; chercheText(); break;}
            if (gpJeu->getJoueur()->getAvancement()==66) {id=385; chercheText(); break;}
            texte = "Tu es le seul visiteur que j'ai eu depuis que je vis ici...*Je suis un ancien aventurier, j'�tais tr�s dou� comme chasseur de tr�sor..."; idsuiv=383;break;
        case 383 : texte = "Un jour j'ai entendu l'histoire du tr�sor de la pyramide, un objet magique...*Mais ce d�sert causa ma perte, je n'ai jamais pu le traverser, il est bien trop dangereux..."; idsuiv=384; break;
        case 384 : texte = "Tu sembles aussi d�termin� que je l'�tais dans mon jeune temps... Je te propose un march�..."; idsuiv=385; break;
        case 385 : texte = "Ram�ne-moi le tr�sor de la pyramide, et je t'offrirais mon plus pr�cieux tr�sor."; break;
        case 386 : 
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=389; chercheText(); break;}
            texte = "Tu as trouv� le tr�sor ???*Une baguette de feu, hein ?*...*..."; idsuiv=387; break;
        case 387 : texte = "Cette baguette te servira plus qu'� moi...*Tu peux la garder...*"; idsuiv=388; break;
        case 388 : texte = "Accepte cette r�compense pour avoir montr� � un vieillard le tr�sor qu'il a cherch� toute sa vie...*Le chant de l'envol!!!"; break;
        case 389 : texte = "Jou� avec un instrument magique, ce chant permet de se t�l�porter. J'esp�rais pouvoir traverser le d�sert avec, mais je n'ai jamais trouv� l'instrument ad�quat..."; break;
        case 390 : texte = "Tu as appris le chant de l'envol!!!**Utilise l'Ocarina pour le jouer!"; break;
        case 391 : texte = "Link! C'est Pit!!!*Qu'est ce que tu fabriques???*Fonce � la plaine ouest!!!"; break;
        case 392 : texte = "Link, c'est Zelda, f�licitation!!!*Rauru est en s�curit�, pour le moment...*Va � la tour du destin au sommet de la montagne et stoppe Ganon!"; break;
        case 393 : texte = "Tutoriel : lorsque la jauge de col�re est pleine, tu te transformes en Oni-Link.*Ton allonge et ta force augmentent alors que ta d�fense diminue."; idsuiv=394; break;
        case 394 : texte = "En Oni-Link, tu ne peux plus utiliser les objets �quipables, mais tu peux te t�l�porter � l'entr�e lorsque tu es dans un donjon en appuyant sur L et R."; idsuiv=395; break;
        case 395 : texte = "A chaque ennemi vaincu par Oni-Link, ta jauge diminue. Une fois vide, Link reprend sa forme normale."; break;
        case 396 : texte = "Chef de projet, concepteur et programmeur :                                                                  Vincent Jouillat"; break;
        case 397 : texte = "Sc�nariste :                                                                                                      Lobaluz"; break;
        case 398 : texte = "Aide aux Graphismes :                                                                                           Harvestland"; break;
        case 399 : texte = "Aide aux Graphismes :                                                                                         Sol�ne Jouillat"; break;
        case 400 : texte = "Illustrateur :                                                                                             Adrien Batis (Raiden)"; break;
        case 401 : texte = "Tu as trouv� la carte de Termina !!!**Appuie sur START lorsque tu es � l'ext�rieur pour la visualiser."; break;
        case 402 : texte = "La l�gende oublie qu'� la suite de ces �v�nements son h�ros fut frapp� par une terrible mal�diction..."; idsuiv=403; break;
        case 403 : texte = "Jour apr�s jour, Link se transformait en un monstre au pouvoir destructeur incontr�lable surnomm� Oni-Link..."; idsuiv=404; break;
        case 404 : texte = "Banni d'Hyrule, Link demanda conseil � la Princesse Zelda."; idsuiv=405; break;
        case 405 : texte = "Cette derni�re lui indiqua son tout dernier espoir : un portail vers un monde secret..."; break;
        case 406 : texte = "Partie sauvegard�e."; break;
        case 407 : texte = "Tu n'as pas besoin de boire cette potion maintenant."; break;
        case 408 : texte = "AIDE : Appuie L et Y pour consulter l'aide."; break;
        case 409 : texte = "Grrrr... Comment as-tu pu t'�chapper du monde des morts et arriver jusqu'ici ???"; idsuiv=410; break;
        case 410 : texte = "Pourquoi t'ent�tes-tu � venir m'affronter ? *M�me si tu me terrasses je reviendrais toujours � la vie."; idsuiv=411; break;
        case 411 : texte = "Ta qu�te est vaine, abandonne tout espoir! **Let's rock, baby!"; break;
    }
	break; //French

case 4: //Italian	
    switch (id) {
        case 3  : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = "Hai trovato una parte di cuore!!!";
            if (tmp<4) buffer = "Ancora "+os.str()+" prima di avere un nuovo cuore!!!";
            else buffer = "Il tuo numero di cuori � aumentato!!!";
            break;
        case 5 : texte = "Entrata della grotta sigillata.**Non Entrare."; break;
        case 6 : texte = "Tempio del Faraone**Salva gli alberi, mangia i castori!!!"; break;
        case 7 : texte = "Hai trovato gli Stivali di Pegaso!!! *Premi R per correre."; break;
        case 8 : texte = "N : Campo Est"; break;
        case 9 : texte = "O : Lago Lanayru"; break;
        case 10 : texte = "S : Foresta Proibita"; break;
        case 11 : texte = "S : Lago Lanayru"; break;
        case 12 : texte = "N : Al Tempio di Ordona"; break;
        case 13 : texte = "N : Villaggio Ruto"; break;
        case 14 : texte = "-Super Anti Mostri Ultimate Society- (S.A.M.U.S.)**Entra se non ami i mostri."; break;
        case 15 : texte = "W : Citt� di Rauru"; break;
        case 16 : texte = "Non hai ancora imparato nessuna canzone.";
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=17; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=26; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=28; chercheText();break;}
            break;
        case 17 : texte = "- MELODIA DEL VOLO*- Non suonare";
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=19; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=30; chercheText();break;}
            break;
        case 18 : texte = "- Melodia del Volo*- NON SUONARE"; break;
        case 19 : texte = "- MELODIA DEL VOLO*- Elegia del Vuoto*- Non suonare";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=22; chercheText();break;}
            break;
        case 20 : texte = "- Melodia del Volo*- ELEGIA DEL VUOTO*- Non suonare"; break;
        case 21 : texte = "- Melodia del Volo*- Elegia del Vuoto*- NON SUONARE"; break;
        case 22 : texte = "- MELODIA DEL VOLO*- Elegia del Vuoto*- Canzone dello Spirito*- Non suonare"; break;
        case 23 : texte = "- Melodia del Volo*- ELEGIA DEL VUOTO*- Canzone dello Spirito*- Non suonare"; break;
        case 24 : texte = "- Melodia del Volo*- Elegia del Vuoto*- CANZONE DELLO SPIRITO*- Non suonare"; break;
        case 25 : texte = "- Melodia del Volo*- Elegia del Vuoto*- Canzone dello Spirito*- NON SUONARE"; break;
        case 26 : texte = "- ELEGIA DEL VUOTO*- non suonare";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=33; chercheText();break;}
            break;
        case 27 : texte = "- Elegia del Vuoto*- NON SUONARE"; break;
        case 28 : texte = "- CANZONE DELLO SPIRITO*- Non suonare"; break;
        case 29 : texte = "- Song of Spirit*- NON SUONARE"; break;
        case 30 : texte = "- MELODIA DEL VOLO*- Canzone dello Spirito*- Non suonare"; break;
        case 31 : texte = "- Melodia del Volo*- CANZONE DELLO SPIRITO*- Non suonare"; break;
        case 32 : texte = "- Melodia del Volo*- Canzone dello Spirito*- NON SUONARE"; break;
        case 33 : texte = "- ELEGIA DEL VUOTO*- Canzone dello Spirito*- Non suonare"; break;
        case 34 : texte = "- Elegia del Vuoto*- CANZONE DELLO SPIRITO*- Non suonare"; break;
        case 35 : texte = "- Elegia del Vuoto*- Canzone dello Spirito*- NON SUONARE"; break;
        case 36 : texte = "N : Villaggio Ruto*S : Campo Est"; break;
        case 37 : texte = "S : Villaggio Ruto*E : Deserto"; break;
        case 38 : texte = "Entrata delle Miniera"; break;
        case 39 : texte = "O : Tempio di Ordona*E : Villaggio Ruto"; break;
        case 40 : texte = "Spiacente, era la mia unica bottiglia."; break;
        case 41 : texte = "Vendo una bottiglia per 100 rupie, sei interessato?*              SI' ?            no  "; 
            if (gpJeu->getJoueur()->hasBouteille(0)) {id=40; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) idsuiv=44;
            else idsuiv=45;
            break;
        case 42 : texte = "Vendo una bottiglia per 100 rupie, sei interessato?*              s�               NO ?"; idsuiv=43; break;
        case 43 : texte = "Torna ancora se cambi idea."; break;
        case 44 : texte = "Non hai abbastanza rupie!"; break;
        case 45 : texte = "Grazie!"; break;
        case 46 : texte = "Hai trovayo una bottiglia vuota!!!**Ti servir� per conservare le pozioni."; break;
        case 47 : texte = "C'� un passaggio segreto ad ovest del villaggio che conduce al Tempio di Ordona, ma avrai bisogno delle bombe per entrare."; break;
        case 49 :
            if (gpJeu->getJoueur()->getAvancement()>3 && !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) 
                texte = "Se cerchi una borsa per le bombe, dovresti ad andare a trovare l'uomo che lavora nella miniera, lui usa molte bombe.";
            else texte = "Gira al largo da me!"; break;
        case 50 : 
            if (gpJeu->getJoueur()->getAvancement()==5 || gpJeu->getJoueur()->getAvancement()==6)
                texte = "Il sindaco ha vietato a tutti l'accesso alla miniera per evitare che i mostri escano fuori.";
            else if (gpJeu->getJoueur()->getAvancement()==7)
                texte = "Stai dicendo che qualcuno potrebbe essere bloccato nella miniera? Cosa proponi di fare?";
            else if (gpJeu->getJoueur()->getAvancement()==8 || gpJeu->getJoueur()->getAvancement()==9)
                texte = "Il sindaco ti ha dato il permesso di passare? Allora datti una mossa!";
            else texte = "..."; break;
        case 54 : texte = "Benvenuto al Villaggio Ruto.**E detto tra noi, non fidarti di nessuno qui..."; break;
        case 55 : texte = "Anche se questo villaggio sembra in salute ad una prima occhiata, � il piu povero di Termina... E non possiamo contare sul sindaco per un cambiamento..."; break;
        case 56 : texte = "I turisti che arrivano qui o si sono persi, o sono completamente matti.**Per quanto mi riguarda, io tengo sempre una mappa con me."; break;
        case 57 : texte = "S : Al Campo Est*O : Al Tempio di Ordona*E : Villaggio Ruto"; break;
        case 58 : texte = "S : Campo Est"; break;
        case 59 : texte = "Tempio Ordona"; break;
        case 60 : texte = "E : Terra Dimenticata"; break;
        case 61 : texte = "S : Villaggio Ruto*O : Morte Certa"; break;
        case 62 : texte = "Oasi Incantata"; break;
        case 63 : texte = "Grotta Fatata"; break;
        case 64 : texte = "Tempio Din**Il potere delle Fate ricompenser� il coraggio!"; break;
        case 65 : texte = "                     ???"; break;
        case 66 : texte = "Tempio Lanayru"; break;
        case 67 : texte = "O : Palude della STrega"; break;
        case 68 : texte = "E : Foresta Proibita"; break;
        case 69 : texte = "N : Campo Est*O : A Citt� di Rauru"; break;
        case 70 : texte = "N : Citt� di Rauru"; break;
        case 71 : texte = "O : Campo Ovest"; break;
        case 72 : texte = "N : Terra Dimenticata*S : Citt� di Rauru"; break;
        case 73 : texte = "N : Citt� di Rauru*S : Lago Lanayru*O : Campo Ovest*E : Campo Est"; break;
        case 74 : texte = "E : Campo Est"; break;
        case 75 :  texte = "Spiacente, non ho piu nulla in magazzino."; break;
        case 76 : texte = "Vendo un'armatura migliore per 250 rupie, sei interessato?*              SI' ?            no  "; 
            if (gpJeu->getJoueur()->getBouclier()>1) {id=75; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<250) idsuiv=44;
            else idsuiv=45;
            break;
        case 77 : texte = "Vendo un'armatura migliore per 250 rupie, sei interessato?*              si               NO ?"; idsuiv=43; break;
        case 78 : texte = "Hai trovato uno scudo nuovo!!!*La tua difesa aumenta di un punto, la tua resistenza contro gli attacchi nemici aumenta !!!"; break;
        case 79 : texte = "Ma perch� devo occuparmi di nuovo di queste galline???"; break;
        case 80 : texte = "Mi piace spazzare!"; break;
        case 81 : texte = "Rauru � la piu bella citt� del posto, ogni giorno arrivano frotte di visitatori."; break;
        case 82 : texte = "Si dice che uno strumento magico sia nascosto in Termina. *Mi domando se lo vedr� un giorno..."; break;
        case 83 : texte = "Hai trovato lo strumento magico???**Speravo fosse un sax..."; break;
        case 84 : texte = "I miei genitori si sono persi."; break;
        case 85 : texte = "Mi piace girovagare!"; break;
        case 86 : texte = "S : Citt� di Rauru*E : Casa Stregata"; break;
        case 87 : texte = "Casa Stregata**Vieni ad arricchire la nostra collezione di anime!"; break;
        case 88 : texte = "E : Per il Tempio di Ordona"; break;
        case 89 : texte = "Tempio di Farore**Il potere delle fate ricompenser� il coraggio!"; break;
        case 90 : texte = "O : Villaggio di Mido"; break;
        case 91 : texte = "N : Montagne del Destino"; break;
        case 92 : texte = "Tempio di Zelda"; break;
        case 93 : texte = "O : Cimitero"; break;
        case 94 : texte = "Segreto del Deserto :*Sollevare le pietre dell'uccello in senso orario per finire con l'occhio per aprire la strada."; break;
        case 95 : texte = "S : Palude della Strega"; break;
        case 96 : texte = "E : Citt� di Rauru"; break;
        case 97 : texte = "N : Terra dell'Ovest*S : Capanna della Strega"; break;
        case 98 : texte = "O : Villaggio di Kasuto*E : Capanna della Strega"; break;
        case 99 : texte = "Capanna delle Pozioni**Vieni a scambiare le tue rupie per le pozioni migliori del paese!!!"; break;
        case 100 : texte = "E : Lago Lanayru"; break;
        case 101 : texte = "N : Cimitero*S : Villaggio di Kasuto"; break;
        case 102 : texte = "Villaggio di Kasuto**   -- Non per umani (vivi) --"; break;
        case 103 : texte = "Consiglio : Mantieni premuto L per guardarti attorno con le frecce direzionali."; break;
        case 104 : texte = "N : Villaggio di Kasuto*E : Palude della Strega"; break;
        case 105 : texte = "Colosseo del Mostro**Venite tutti!"; break;
        case 106 : texte = "Sembri forte, dovresti allenarti nell'arena a sud del villaggio. Si dice che un oggetto estremamente utile sia nascosto l�..."; break;
        case 107 : texte = "Uh?*Una nuova specie?**Sai parlare?"; break;
        case 108 : texte = "Questo villaggio � l'ultima fortezza contro l'umanit�."; break;
        case 109 : texte = "Ciao, sono un finto mostro."; break;
        case 110 : texte = "Bloccato?***Ma la soluzione non � cos� lontana."; break;
        case 111 : texte = "S : Villaggio di Kasuto"; break;
        case 112 : texte = "Tempio di Xanto**""I morti non raccontano storie..."; break;
        case 113 : texte = "Hai mai provato il martello sugli scheletri?"; break;
        case 114 : texte = "E : Terra dell'Ovest"; break;
        case 115 : texte = "Villaggio di Mido"; break;
        case 116 : texte = "Tutti i teenager non hanno senso del gusto come te?"; break;
        case 117 : texte = "Benvenuto al villaggio di Mido, ma non sentirti obbligato a rimanere."; break;
        case 118 : texte = "Grrr... Pensavo di essere solo qui..."; break;
        case 119 : texte = "Solo la vuotezza incommensurabile pu� rimuovere questa pietra."; break;
        case 120 : texte = "Tempio di Nayru**Il potere delle fate ricompenser� il coraggio!"; break;
        case 121 : texte = "Via del Destino**Solo un alleato del Bene e del Male uscir� da questa caverna."; break;
        case 122 : texte = "S : Villaggio di Mido"; break;
        case 123 : texte = "Tempio di Eldin"; break;
        case 124 : texte = "S : Terra dell'Ovest"; break;
        case 125 : texte = "La forza dei Titani andr� all'eroe leggendario..."; break;
        case 126 : texte = "Torre del Destino*Attento Eroe di Hyrule, il vile Ganon troneggia qui, il futuro del mondo si gioca qui."; break;
        case 127 : texte = "Congratulazioni!**Sei riuscito a scalare le Montagne Piatte!"; break;
        case 128 : texte = "Non devi trasformarti qui!!!"; break;
        case 129 : texte = "Non puoi andare in questo villaggio con quell'aspetto !!!"; break;
        case 130 : texte = "Link, sono Pit. Ti sto parlando telepaticamente. Non devi trasformarti per nessun motivo in un villaggio!*Ti teletrasporter� fuori."; break;
        case 131 : texte = "Hai trovato una Spada!!!**Premi B per attaccare o mantienilo premuto per caricare un attacco roteante."; break;
        case 132 : texte = "Hai trovato la Mappa!!!*Premi Start per vedere la mappa del Dungeon."; break;
        case 133 : texte = "Hai trovato la Bussola!!!**Il Boss e i forzieri sono ora visibili sulla mappa."; break;
        case 134 : texte = "Hai trovato la Chiave del Boss.**Usala per raggiungere la sua tana."; break;
        case 135 : texte = "Hai trovato una Chiave Piccola.**Usala per sbloccare una porta."; break;
        case 136 : texte = "Hai trovato un Cuore Nuovo!!!**La tua vita massima aumenta di uno!!!"; break;
        case 137 : texte = "Hai trovato un Graal!!!"; break;
        case 138 : texte = "Sei venuto a salvarmi?*Grazie mille!"; 
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
        case 139 : texte = "Scavando in queste gallerie abbiamo scoperto questo mucchio di mostri..."; idsuiv=142; break;
        case 140 : texte = "Siamo stati tutti catturati dai mostri che vivono in queste caverne."; idsuiv=142; break;
        case 141 : texte = "Il nostro capo � al piano inferiore, vai a salvarlo al piu presto!"; idsuiv=142; break;
        case 142 : texte = "Ho trovato questo nella miniera, prendilo, potrebbe esserti d'aiuto!"; break;
        case 143 : 
            if (gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=50; chercheText();break;}
            texte = "Hai sconfitto il mostro nella miniera???*Congratulazioni!!!"; idsuiv=144; break;
        case 144 : texte = "Sono il capo dei lavoratori, mi stavi cercando?"; idsuiv=145; break;
        case 145 : texte = "Prendi questo sacco pieno di bombe, potrebbe esserti d'aiuto."; break;
        case 146 : texte = "Hai trovato il Sacco di Bombe!!!*Ed � pieno!!!*Premi Y per posarle."; break;
        case 147 : texte = "Hai trovato i Guanti!!!**Ora puoi sollevare pietre leggere con X."; break;
        case 148 : 
            if (gpJeu->getJoueur()->hasObjet(O_ARC)) {id=50; chercheText();break;}
            texte = "Sono il braccio destro del sindaco, mi ha inviato a salvare sua figlia...*Ma ci ho rinunciato, non c'� niente da fare contro questi fantasmi..."; idsuiv=149; break;
        case 149 : texte = "Non rimanere qui, non puoi fare nulla con le armi che possiedi..."; idsuiv=150; break;
        case 150 : texte = "Per continuare la tua missione, segui la strada ad ovest della citt�. Quest'arco ti permetter� di raggiungere la sfera e aprire la strada..."; break;
        case 151 : texte = "Hai trovato l'Arco!!!*Ora puoi attaccare a distanza e raggiungere bersagli lontani!!!"; break;
        case 152 : 
            if (gpJeu->getJoueur()->getAvancement()>64) {id=153; chercheText();break;}
            texte = "Hai ucciso il vampiro e sei venuto a salvarmi? Grazie mille! Mio padre � il sindaco della citt�, vai a trovarlo, sono sicuro che ti ricompenser�."; break;
        case 153 : texte = "Non preoccuparti per me, posso tornare a casa da sola ora che il vampiro � morto."; break;
        case 154 : 
            if (gpJeu->getJoueur()->getAvancement()==13)
                texte = "Hai ricevuto l'autorizzazione del sindaco?*Allora fai attenzione, quelli che si avventurano qui non fanno mai ritorno...";
            else if (gpJeu->getJoueur()->getAvancement()<13)
                texte = "Per volere del sindaco, l'accesso a quest'area � severamente proibito.";
            else texte = "..."; break;
        case 155 : texte = "Non puoi scappare ora!"; break;
        case 156 : texte = "Hai trovato il Martello!!!**Ora puoi schiacciare ostacoli impedenti!!!"; break;
        case 157 : texte = "Hai trovato il Gancio da Tiro!!!**Ora puoi attraversare i precipizi!!!"; break;
        case 158 : texte = "Sala del Colosseo"; break;
        case 159 : texte = "Arena 1"; break;
        case 160 : texte = "Arena 2"; break;
        case 161 : texte = "Arena 3"; break;
        case 162 : texte = "Arena 4"; break;
        case 163 : texte = "Sala dei Premi"; break;
        case 164 : texte = "Arena Speciale**Vieni e prova a vincere il premio speciale!!!"; break;
        case 165 : texte = "Hai trovato le Pinne!!!**Ora puoi attraversare i banchi d'acqua!!!"; break;
        case 166 : texte = "Hai trovato una Cotta di Maglia!!!**La tua difesa aumenta di un punto!!!"; break;
        case 167 : texte = "Hai trovato una Cotta di Maglia migliore!!!   *La tua difesa aumenta di un punto!!!"; break;
        case 168 : texte = "Hehehehehe!!!*Congratulazioni Link! Sei riuscito a liberarti dalla tua maledizione. E allo stesso tempo mi hai liberato!!!"; idsuiv=169; break;
        case 169 : texte = "Come ringraziamento per i tuoi sforzi, non ti uccider� oggi, ho una missione piu importante da compiere."; idsuiv=170; break;
        case 170 : texte = "Se vuoi veramente fermarmi, raggiungimi nel tempio della morte se sei abbastanza coraggioso.*Addio! Hihihihihi!!!"; break;
        case 171 : texte = "Link, sono Zelda, ti sto parlando telepaticamente. Sono con Pit, raggiungici immediatamente, la situazione � seria."; break;
        case 172 : texte = "Buongiorno Link, ti stavo aspettando.**Il mio nome � Pit, la Principessa Zelda mi ha chiesto di guardare in questa caverna."; idsuiv=173; break;
        case 173 : texte = "Mi ha detto che stavi arrivando e mi ha chiesto di aiutarti.*La mia casa � qui vicino, potremo parlare piu tranquillamente, seguimi."; break;
        case 174 : texte = "Pit ti ha detto di non abbandonare la foresta."; break;
        case 175 : texte = "Hai trovato l'Asta di Fuoco!!!**Ora puoi lanciare potenti palle di fuoco!!!"; break;
        case 176 : 
            if ((gpJeu->getZone() == 23 && gpJeu->getJoueur()->getCoffre(8,19))
            || (gpJeu->getZone() == 24 && gpJeu->getJoueur()->getCoffre(9,24))
            || (gpJeu->getZone() == 25 && gpJeu->getJoueur()->getCoffre(10,21))) {
                id=50; chercheText();break;}
            texte = "Ti stavo aspettando, Link.*Rilascer� il potere della Dea sulla tua spada per restaurare la Spada Maestra."; break;
        case 177 : 
            if (gpJeu->getJoueur()->getEpee()==5) {id=178; chercheText();break;}
            texte = "Il potere della Spada Maestra cresce! **Vai velocemente al prossimo tempio!"; break;
        case 178 : texte = "La Spada Maestra raggiunge il suo potere massimo!!!  *Anche Oni-Link non pu� resistere a questa spada!!!"; break;
        case 179 : texte = "Hai trovato l'Asta di Ghiaccio!!!**Ora puoi congelare qualsiasi cosa!!!"; break;
        case 180 : texte = "Hai trovato uno scudo nuovo!!!*La tua difesa aumenta, la tua resistenza agli attacchi nemici aumenta!!!"; break;
        case 181 : texte = "Link, sono Zelda, ti sto parlando telepaticamente. Non andare in questo dungeon se non sei pronto, probabilmente � una trappola di Oni-Link."; break;
        case 182 : texte = "Quindi sei venuto?*Probabilmente vuoi morire, sar� un piacere accontentarti.*Hehehehehe!!!"; break;
        case 183 : texte = "La sostanza di Oni-Link � stata imprigionata nella Maschera Sprituale!!!*Ce l'hai fatta!!!"; break;
        case 184 : texte = "Grrrr!!! Non posso crederci, hai sconfitto Oni-Link??? Impressionante...*Suppongo che non ti aspettavi di vedermi, d'altronde siamo nel mondo dei morti."; idsuiv=185; break;
        case 185 : texte = "Oni-Link mi ha dato l'energia necessaria per materializzarmi, perci� sono tornato prima del previsto.*Gwahahahahaha !!!"; idsuiv=186; break;
        case 186 : texte = "Comunque, magari ti starai domandando da dove viene Oni-Link? E' semplice, l'ultima volta ho fatto in modo da non essere piu disturbato, perci� ho usato"; idsuiv=187; break;
        case 187 : texte = "il Triforce per renderti un mostro della mia legione. Ma il tuo cuore era troppo puro, perci� la trasformazione non si � completata..."; idsuiv=188; break;
        case 188 : texte = "Ma sto divagando, ho un mucchio di piani...*Sarebbe un piacere eliminarti, ma non credo sia necessario..."; idsuiv=189; break;
        case 189 : texte = "Per tua informazione, solo le creature dell'oscurit� possono uscire da qui.*Quindi, addio! Gwahahahahaha !!!"; break;
        case 190 : 
            if (!gpJeu->getJoueur()->getOni()) {id=184; chercheText();break;}
            texte = "Onily? Allora, dov'� il mio caff�???*Cosa??? Sei tu, Link???"; idsuiv=184; break;
        case 191 : texte = "                   Mondo della Morte"; break;
        case 192 : texte = "Link, sono Zelda, ti sto parlando telepaticamente. E' terribile, Ganon � tornato!!!"; idsuiv=193; break;
        case 193 : texte = "Ha ricostituito la sua armata, e si preparano ad attaccare Rauru!*Puoi ancora fermarli, vai velocemente alla Terra dell'Ovest ed intercetta l'armata!"; break;
        case 194 : texte = "Hai trovato l'Arco della Grande Fata!!!**Ora puoi scoccare frecce dall'altissimo potenziale!!!"; break;
        case 195 : texte = "Hai trovato il Triforce !!!"; break;
        
        case 197 : texte = "Guida : Premi A per parlare, leggere, aprire forzieri o per proseguire nei dialoghi su schermo."; break;
        case 198 : texte = "Premi X per sollevare oggetti leggeri."; break;
        case 199 : texte = "Vuoi salvare il gioco?**                    ? SI ?*                      no  "; break;
        case 200 : texte = "Vuoi salvare il gioco?**                      si  *                    ? NO ?"; break;
        case 201 : texte = "                   Livello 1 :                                                                                Tempio di Faron"; break;
        case 202 : texte = "                   Livello 2 :                                                                                Miniera di Ruto"; break;
        case 203 : texte = "                   Livello 3 :                                                                                Tempio di Ordona"; break;
        case 204 : 
            if (gpJeu->getJoueur()->getEpee()>=2) 
                   texte = "                   Livello 9 :                                                                                  Casa Stregata";
            else   texte = "                   Livello 4 :                                                                                  Casa Stregata"; break;
        case 205 : texte = "                   Livello 5 :                                                                                 Tempio di Eldin"; break;
        case 206 : texte = "                   Livello 6 :                                                                               Colosseo dei Mostri"; break;
        case 207 : texte = "                   Livello 7 :                                                                                Tempio di Lanayru"; break;
        case 208 : texte = "                   Livello 8 :                                                                                 Tempio di Zelda"; break;
        case 209 : texte = "                  Livello 10 :                                                                                  Tempio di Din"; break;
        case 210 : texte = "                  Livello 11 :                                                                                 Tempio di Nayru"; break;
        case 211 : texte = "                  Livello 12 :                                                                                 Tempio di Farore"; break;
        case 212 : 
            if (gpJeu->getJoueur()->getX()>14*320) {id=191; chercheText();break;}
                   texte = "                  Livello 13 :                                                                                  Tempio di Xanto"; break;
        case 213 : texte = "                   Livello ? :                                                                                  Tempio Segreto"; break;
        case 214 : texte = "                Livello Finale :                                                                               Torre del Destino"; break;
        case 215 : texte = "                  Gi� stanco?                                     CONTINUA                                     Salva ed esci                               Esci senza salvare            "; break;
        case 216 : texte = "                  Gi� stanco?                                     Continua                                     SALVA ED ESCI                               Esci senza salvare            "; break;
        case 217 : texte = "                  Gi� stanco?                                     Continua                                     Salva ed esci                               ESCI SENZA SALVARE            "; break;
        case 218 : texte = "Dopo la sconfitta di Ganon e la scomparsa del Triforce, la leggenda ci fece credere che fosse giunta la pace...*Ma dietro ogni leggenda, c'� sempre una realt� ancora piu oscura..."; idsuiv=402; break;
        case 220 : texte = "S�... Per di qua... *Siamo quasi arrivati..."; idsuiv=221; break;
        case 221 : texte = "Mi dispiace che non puoi portare con te armi... Ma vedi... Potresti trasformarti in qualsiasi istante...*E' troppo pericoloso..."; idsuiv=222; break;
        case 222 : texte = "Siamo arrivati! Eccoci!*Non muoverti, preparo il portale...**Sei pronto?"; break;
        case 223 : texte = "Liberato dalla maledizione di Ganon, Link pot� ritornare in tranquillit� ad Hyrule.**Il Triforce, la Spada Maestra e l'Ocarina furono portati alla Famiglia Reale di Hyrule, mentre la Maschera di Oni-Link fu data alle Fate per essere nascosta tra lo spazio ed il tempo...**Il portale per Termina fu sigillato dalla Principessa Zelda e da Pit, cos� che non potesse essere mai piu percorso, e questo terribile capitolo fu cancellato dalla legenda..."; idsuiv=224; break;
        case 224 : texte = "Il popolo di Hyrule non venne mai a conoscenza di cosa accadde nelle misteriose terre di Termina, tantomeno seppero che il temibile Ganon stava gi� preprando il suo ritorno...**Ma ci� che tutti ricordano � il ritorno dell'eroe ad Hyrule che sar� sempre pronto a proteggere il Regno dall'oscurit�."; break;
        case 225 : texte = "Hai trovato uno scudo!!!*La tua difesa aumenta di un punto, la tua resistenza agli attacchi nemici aumenta!!!"; break;
        case 226 : texte = "Pit ti sta aspettando nella casa alla tua destra."; break;
        case 227 : 
            if (gpJeu->getJoueur()->getMagieMax()>32) texte = "...";
            else texte = "Congratulazioni Link per avermi trovato. Aumenter� la carica del tuo contenitore magico come ricompensa."; break;
        case 228 : texte = "La carica del tuo contenitore magico raddoppia !!!"; break;
        case 229 : texte = "Hai trovato l'Ocarina del Tempo!!!**Ha un potere cos� elevato da fermare il tempo quando suonata!"; break;
        case 230 : texte = "Hai trovato la Lanterna!!!**Ora puoi sparare fiamme!!!"; break;
        case 231 : texte = "Hai trovato la Maschera Spirituale!!!**Una strana aura risiede in lei..."; break;
        case 232 : 
            if (gpJeu->getJoueur()->getTutoriel()==3) {id=233; chercheText();break;}
            gpJeu->getJoueur()->setTutoriel(3);
            texte = "Congratulazioni, mi hai trovato!!!**Sono la Fata Maggiore del deserto, colleziono rupie!"; idsuiv=233; break;
        case 233 : texte = "Dammi 100 rupie, svelto!!!**              SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) {idsuiv=236; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70 && gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=239; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70) {idsuiv=237; break;}
            if (gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=238; break;}
            idsuiv = 237 + (rand()%2); break;
        case 234 : texte = "Dammi 100 rupie, svelto!!!**              si              NO ?"; idsuiv=235; break;
        case 235 : texte = "Mi hai fatto perdere tempo, vattene!"; break;
        case 236 : texte = "Non hai abbastanza rupie!!!*Mi hai fatto perdere tempo, vattene!"; break;
        case 237 : texte = "Alzer� il numero massimo di bombe che puoi trasportare, grazie a chi???"; break;
        case 238 : texte = "Alzer� il numero massimo di frecce che puoi trasportare, grazie a chi???"; break;
        case 239 : texte = "Ho abbastanza rupie, sparisci!"; break;
        case 240 : texte = "Hai trovato il Guanto d'Oro!!!**Ora puoi sollevare pietre pesanti premendo X."; break;
        case 241 : texte = "Lascio passare solo creature malefiche."; 
            if (gpJeu->getJoueur()->getOni()) idsuiv=243; break;
        case 242 : texte = "Lascio passare solo creature buone."; 
            if (!gpJeu->getJoueur()->getOni()) idsuiv=244; break;
        case 243 : texte = "Sembri cattivo...*Ok, puoi passare!"; break;
        case 244 : texte = "Sembri buono...*Ok, puoi passare!"; break;
        case 245 : 
            if (gpJeu->getJoueur()->getAvancement()==2) {id=250; chercheText();break;}
            texte = "Ti starai chiedendo dove ti trovi.*Questa � Termina, e non ti serve sapere molto a riguardo..."; idsuiv=246; break;
        case 246 : texte = "E' una terra segreta, e deve rimanere tale. La Principessa Zelda non avrebbe mai dovuto portarti qui..."; idsuiv=247;  break;
        case 247 : texte = "Nello specifico, ti trovi nella Foresta di Termina. C'� un tempio in questa foresta, ed in questo tempio vi � un oggetto sacro capace di spezzare qualsiasi magia demoniaca..."; idsuiv=248; break;
        case 248 : texte = "Trova quest'oggetto e poi torna qui.*Aprir� di nuovo il portale per il tuo ritorno."; idsuiv=249; break;
        case 249 : texte = "Ah, un ultima cosa, non abbandonare per nessun motivo la Foresta! La tua presenza qui � segreta e, nelle tue condizioni, sei un pericolo per qualsiasi persona che incontreresti..."; idsuiv=250; break;
        case 250 : texte = "Buona fortuna, Link!"; break;
        case 251 : 
            if (gpJeu->getJoueur()->getAvancement()==3) {id=250; chercheText();break;}
            texte = "Cosa ??? Il Graal non ha spezzato la maledizione??? E'... incredibile..."; idsuiv=252; break;
        case 252 : texte = "Questa maledizione deve essere tremendamente potente... Ma ad un'attento esame, non tutto � perduto..."; idsuiv=253; break;
        case 253 : texte = "Il Graal ti ha fatto qualcosa, probabilmente lo hai notato.*Ora impieghi meno tempo per trasformarti."; idsuiv=254; break;
        case 254 : texte = "Ma ha anche un contro-effetto... Quando sei trasformato, rimani tale per un tempo maggiore..."; idsuiv=255; break;
        case 255 : texte = "Ascoltami attentamente, Link. Ci sono altri 4 graal nei tempi di Termina...*Si pensa che una volta combinati, diventino potenti tanto quanto il Triforce."; idsuiv=256; break;
        case 256 : texte = "Grazie al graal che hai trovato, sei leggermente meno pericoloso, perci� ti autorizzo ad esplorare Termina liberamente."; idsuiv=257; break;
        case 257 : texte = "Avventurati oltre la foresta, cerca e trova i graal e sarai salvo.*Ma non devi entrare in un villaggio se sei trasformato."; idsuiv=258; break;
        case 258 : texte = "Prendi questa mappa, ti torner� sicuramente utile...*Buona fortuna!"; break;
        case 259 : 
            if (gpJeu->getJoueur()->getEpee()>=2) {id=271; chercheText();break;}
            texte = "Sono felice di vederti sano e salvo! Ora che non rischi piu di essere trasformato, ho pensato che ti avrebbe fatto piacere avere questo..."; break;
        case 260 : texte = "Hai trovato la Spada Maestra!!!**Il suo incredibile potere sembra palpabile !!!"; break;
        case 261 : texte = "Sfortunatamente ne avrai bisogno...*Oni-Link � stato libreato...*Potevamo accorgercene prima..."; idsuiv=262; break;
        case 262 : texte = "Ogni volta che trovavi un nuovo graal, la frequenza delle tue trasformazioni diminuiva, ma la durata vitale di Oni-Link cresceva..."; idsuiv=263; break;
        case 263 : texte = "Comunque, il comportamento di Oni-Link � strano...*Con il suo temperamento distruttivo avrebbe dovuto attaccare un villagio..."; idsuiv=264; break;
        case 264 : texte = "Dovrei esserne felice, ma temo che abbia progetti ben piu tremendi..."; idsuiv=265; break;
        case 265 : texte = "Comunque, abbiamo ideato un piano per eliminarlo. Ascoltami attentamente..."; idsuiv=266; break;
        case 266 : texte = "La Spada Maestra � un'arma formidabile, ma non avr� effetto su di Oni-Link...*...per ora..."; idsuiv=267; break;
        case 267 : texte = "Ci sono 3 templi segreti nascosti a Termina. In questi templi vi sono fate che potranno potenziare la tua spada. Trovali tutti!"; idsuiv=268; break;
        case 268 : texte = "Una volta fatto, potrai fronteggiare Oni-Link ad armi pari.*Comunque, Oni-Link � energia pura, perci� non pu� essere ucciso..."; idsuiv=269; break;
        case 269 : texte = "La Maschera Spirituale ti permetter� di imprigionarlo per sempre. Per farlo, dovrai trovare questa maschera, l'Ocarina magica e la melodia per intrappolarlo..."; idsuiv=270; break;
        case 270 : texte = "Il tuo viaggio � solo agli inizi..."; break;
        case 271 : texte = "Trova le 3 fate, la maschera, l'Ocarina e la canzone dello spirito, infine affronta Oni-Link!"; break;
        case 272 : 
            if (gpJeu->getJoueur()->getEpee()<2) {id=50; chercheText();break;}
            texte = "Come ben saprai, la Spada Maestra pu� sconfiggere i fantasmi, riflettere attacchi magici, e distruggere barriere magiche...*Fanne buon uso..."; break;
        case 273 : texte = "Non c'� tempo da perdere!*Vai immediatamente alla Terra dell'Ovest per intercettare l'armata di Ganon!"; break;
        case 274 : texte = "Corri Link, che cosa stai aspettando?*Natale ???"; idsuiv=275; break;
        case 275 : texte = "Ehm... Che c'� ?*Io... ehm... ...proteggo la principessa, questo � quanto! Chi pensi che abbia fatto in modo che non venisse rapita questa volta ? Huh ?"; break;
        case 276 : 
            if (gpJeu->getJoueur()->getAvancement()==69) {id=282; chercheText();break;}
            texte = "Link... c'� una cosa che avrei dovuto dirti fin dall'inizio...*Questo mondo, Termina..."; idsuiv=277; break;
        case 277 : texte = "Questo mondo � giovane, � una creazione del Triforce per via di un desiderio... Le persone, le loro memorie e le loro storie sono anche loro creazioni..."; idsuiv=278; break;
        case 278 : texte = "S�... come immaginavi, ho chiesto io al Triforce di creare questo mondo... E' un mondo creato per contenere tutto quello di cui potremmo aver bisogno."; idsuiv=279; break;
        case 279 : texte = "Tu hai trovato i graal, Oni-Link ha trovato il suo maestro e Ganon ha trovato...*...il Triforce..."; idsuiv=280; break;
        case 280 : texte = "Ho creato questo mondo per usarlo come nascondiglio per il Triforce, ma Ganon lo ha trovato..."; idsuiv=281; break;
        case 281 : texte = "Link! Questa terra e i loro abitanti son stati creati, ma sono reali ora! Se non facciamo nulla, questa terra diventer� presto come il vecchio Mondo Oscuro!"; idsuiv=282; break;
        case 282 : texte = "Mi affido a te, Link, salva questo mondo!"; break;
        case 283 : 
            texte = "Benvenuto alla casa degli studi dei Mostri!"; 
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
        case 284 : texte = "Probabilmente ti ricordi di me, mi hai aiutato ad Hyrule.*Uh... Ti chiedi perche son venuto a Termina? Uh... non importa!"; idsuiv=285; break;
        case 285 : texte = "Questo mondo � ricolmo di mostri, perci� fa proprio al caso mio!"; idsuiv=286; break;
        case 286 : texte = "Raccoglier� informazioni sui mostri su di una nuova Enciclopedia!**Con il tuo aiuto, ovviamente."; idsuiv=287; break;
        case 287 : texte = "Sfortunatamente non ho piu pezzi di cuore, per� ora pago in monete. *Ti pagher� profumatamente per ogni mostro aggiunto all'Enciclopedia."; idsuiv=288; break;
        case 288 : texte = "Torna qui regolarmente per ricevere le tue ricompense. Se non hai spazio a sufficienza, terr� il resto per la tua prossima visita."; idsuiv=289; break;
        case 289 : texte = "Devi solo sconfiggere un mostro nuovo per aggiungerlo all'Enciclopedia.*Puoi consultarla premendo L e B!"; break;
        case 290 : 
            texte = "Mmm... sei un esemplare curioso...";
            if (gpJeu->getJoueur()->getEnnemi(75) 
            || !gpJeu->getJoueur()->hasObjet(O_ENCYCL)) break;
            texte += "*Ti aggiunger� all'Enciclopedia!!!"; break;
        case 291 : 
            os << gpJeu->getJoueur()->getSolde();
            texte = "Ti devo " + os.str() + " rupie.";
            idsuiv=292; break;
        case 292 : texte = "Vuoi essere pagato ora?**              SI ?            no  "; break;
        case 293 : texte = "Vuoi essere pagato ora?**              si              NO ?"; break;
        case 294 : texte = "Ho uno scoop per te, i mostri che hai sconfitto in passato ad Hyrule sono tornati! Ora vagano per Termina..."; idsuiv=295; break;
        case 295 : texte = "Si dice siano tre.*Se li sconfiggi tutti, ri dar� un... premio speciale..."; break;
        case 296 : texte = "Hai sconfitto i tre mostri rari???*...*La tua ricompensa ti aspetta al piano di sotto..."; break;
        case 297 : texte = "Hai sconfitto tutti i mostri...*E' incredibile..."; break;
        case 298 : texte = "Ciao Link, come sei messo con le bombe?"; break;
        case 299 : texte = "Non ho piu ricompense per te, mi dispiace."; break;
        case 300 : texte = "Uno di questi forzieri contiene un pezzo di cuore, vuoi tentare la sorte per 10 rupie?*Potrai aprire solo un forziere, ok?               SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 301 : texte = "Uno di questi forzieri contiene un pezzo di cuore, vuoi tentare la sorte per 10 rupie?*Potrai aprire solo un forziere, ok?               si              NO ?"; break;
        case 302 : texte = "Scegli un forziere."; break;
        case 303 : texte = "Ehi! Devi pagare per aprire uno dei miei forzieri!!!"; break;
        case 304 : texte = "Hai perso! Questo forziere � vuoto. Riprova!"; break;
        case 305 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=342; chercheText(); break;}
            texte = "Cosa vorresti bere?"; break;
        case 306 : texte = "Stai cercando l'uomo che lavora nella miniera? Nessuno l'ha piu visto dal giorno che han sigillato la miniera... Forse � intrappolato all'interno..."; break;
        case 307 : texte = "Questo saloon era veramente in voga...*...prima..."; break;
        case 308 : texte = "Io SONO il sindaco di questo villaggio, e NON voglio parlarti!"; break;
        case 309 : texte = "Dici che qualcuno potrebbe essere intrappolato nella miniera?**... ... ..."; 
            if (gpJeu->getJoueur()->getAvancement()==8) {id=308; chercheText();} 
            else idsuiv=310; break;
        case 310 : texte = "Va bene, dammi 10 rupie e ti lascer� entrare nella miniera. Ok?*              SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; 
            else idsuiv=312; break;
        case 311 : texte = "Va bene, dammi 10 rupie e ti lascer� entrare nella miniera. Ok?*              si              NO ?"; break;
        case 312 : texte = "D'accordo, vai a parlare con la guardia, ti lascer� passare..."; break;
        case 313 : texte = "Un cuore per 5 rupie, ok?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getVie() == gpJeu->getJoueur()->getVieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=44; break;
        case 314 : texte = "Un cuore per 5 rupie, ok?**              si              NO ?"; break;
        case 315 : texte = "Al momento, non ne hai bisogno."; break;
        case 316 : texte = "Una fiala di magia per 15 rupie, ok?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=44; break;
        case 317 : texte = "Una fiala di magia per 15 rupie, ok?**              si              NO ?"; break;
        case 318 : texte = "Una fiala grande di magia per 25 rupie, ok?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<25) idsuiv=44; break;
        case 319 : texte = "Una fiala grande di magia per 25 rupie, ok?**              si              NO ?"; break;
        case 320 : texte = "Scegli cosa vuoi."; break;
        case 321 : texte = "10 frecce per 20 rupie?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()
            || !gpJeu->getJoueur()->hasObjet(O_ARC)) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=44; break;
        case 322 : texte = "10 frecce per 20 rupie?**              si              NO ?"; break;
        case 323 : texte = "5 bombe per 30 rupie?**              SI ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=325; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=44; break;
        case 324 : texte = "5 bombe per 30 rupie?**              si              NO ?"; break;
        case 325 : texte = "Ti serve un Sacco di Bombe per comprarle."; break;
        case 326 : texte = "Torna quando avrai una bottiglia vuota e ti vender� delle pozioni."; break;
        case 327 : texte = "Le pozioni rosse ripristinano la vita, quelle verdi ripristinano la magia."; 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            idsuiv=328; break;
        case 328 : texte = "Cosa vuoi?*                ?  POZIONE ROSSA  ?*                ? pozione verde ?*                ?   niente    ?"; idsuiv=331; break;
        case 329 : texte = "Cosa vuoi?*                ?  pozione ROSSA  ?*                ? POZIONE VERDE ?*                ?   niente    ?"; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=315;
            idsuiv=333; break;
        case 330 : texte = "Cosa vuoi?*                ?  pozione rossa  ?*                ? pozione verde ?*                ?   NIENTE    ?"; break;
        case 331 : texte = "Una pozione rossa per 60 rupie?**              SI ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=44; break;
        case 332 : texte = "Una pozione rossa per 60 rupie?**              si              NO ?"; break;
        case 333 : texte = "Una pozione verde per 40 rupie?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=44; break;
        case 334 : texte = "Una pozione rossa per 40 rupie?**              si              NO ?"; break;
        case 335 : texte = "Hai trovato una pozione rossa!!!**Bevila per recuperare tutta la tua vita!!!"; break;
        case 336 : texte = "Hai trovato una pozione verde!!!**Bevila per recuperare tutta la tua magia!!!"; break;
        case 337 : texte = "Hai trovato una pozione blue!!!**Bevila per recuperare tutta la tua vita e magia!!!"; break;
        case 338 : texte = "SANTUARIOOOO!!!!!!!!"; break;
        case 339 : texte = "Oh, anche tu... le galline? -hic- !*Terribili queste bestie... -hic-!"; break;
        case 340 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=339; chercheText(); break;}
            if (gpJeu->getJoueur()->hasCristal(3)) {id=341; chercheText(); break;}
            texte = "Ero un pescatore tanto tempo fa... -hic-! Ma quando L'HO vista... -hic-!*Questa terribile bestia... -hic-!*Nel lago... -hic-!"; break;
        case 341 : texte = "Hai sconfitto il mostro nel lago???*... ... ...*Comunque ho paura dell'acqua... -hic-!*(Preferisco il vino) -hic-!"; break;
        case 342 : texte = "Eh-Eh-Eh!"; break;
        case 343 : 
            if (gpJeu->getJoueur()->getAvancement()==11) {id=344; chercheText(); break;}
            if (gpJeu->getJoueur()->getAsile()==3) {id=347; chercheText(); break;}
            if (gpJeu->getJoueur()->getRaplaplat()) {id=348; chercheText(); break;}
            texte = "Ciao! Sono a conoscenza di tutto quello che si dice in citt�, vieni a trovarmi se ti servono informazioni."; break;
        case 344 : 
            if (gpJeu->getJoueur()->getAvancement()!=11) {id=343; chercheText(); break;}
            texte = "Vuoi sapere perch� il sindaco � cos� silenzioso?*Ok, ma non ti ho detto nulla, huh?"; idsuiv=345; break;
        case 345 : texte = "Questa citt� nasconde un temibile segreto...*Durante la notte, le ragazze spariscono e non fanno piu ritorno... Non vorrei nemmeno uscire..."; idsuiv=346; break;
        case 346 : texte = "La notte scorsa, stando alle dicerie, la figlia del sindaco sembra essere sparita..."; break;
        case 347 : 
            if (gpJeu->getJoueur()->getRaplaplat()) idsuiv=348;
            texte = "Ciao! Signore-che-teme-le-galline,*He! He! He!"; break;
        case 348 : texte = "Si dice che hai scalato le Montagne Piatte? Congratulazioni! He! He! He!"; break;
        case 349 : 
            if (gpJeu->getJoueur()->getAvancement()==13) {id=50; chercheText(); break;}
            texte = "Tu... tu sai di mia figlia?*E' terribile... La mia povera bambina..."; idsuiv=350;break;
        case 350 : texte = "Stando alle indagini che ho condotto dal partire di questi eventi, le ragazze catturate sembran essere portate nella casa a nord del villaggio..."; idsuiv=351; break;
        case 351 : texte = "Ho gia inviato le guardie l� ma nessuno ha mai fatto ritorno..."; idsuiv=352; break;
        case 352 : texte = "Cos� questa mattina, quando ho scoperto che mia figlia era sparita, ho giurato che l'avrei riportata a casa... Lui � un perfetto guerriero, ma � lento..."; idsuiv=353; break;
        case 353 : texte = "Sembri essere un guerriero anche tu, puoi scoprire cosa � successo qui?*Avrai una grande ricompensa se salverai mia figlia."; idsuiv=354; break;
        case 354 : texte = "Incontra le guardie a nord-ovest della citt�, ti far� passare."; break;
        case 355 : 
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=358; chercheText(); break;}
            texte = "Mia figlia mi ha raccontato tutto, ti ringrazio di cuore!!!"; idsuiv=356; break;
        case 356 : texte = "Ascolta attentamente, ti insegner� una canzone, � un cimelo di famiglia tramandato da generazioni:*L'Elegia della Vuotezza!"; break;
        case 357 : texte = "Hai imparato l'Elegia della Vuotezza!!!**Usa l'Ocarina per suonarla!"; break;
        case 358 : texte = "L'Elegia della Vuotezza ha poteri misteriosi...*...credo."; break;
        case 359 : texte = "Ciao signor-mio-salvatore!"; break;
        case 360 : 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            texte = "Una pozione blu per 160 rupie?*Non sarai imbrogliato...*              SI ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=44; break;
        case 361 : texte = "Una pozione blu per 160 rupie?*Non sarai imbrogliato...*              si              NO ?"; break;
        case 362 : 
            if (gpJeu->getJoueur()->hasObjet(O_GRAPPIN)) {id=364; chercheText(); break;}
            texte = "Buongiorno, non possiamo vedere un mostro cos� potente tutti i giorni, � un onore..."; idsuiv=363; break;
        case 363 : texte = "Dovresti andare a partecipare nel Colosseo a sud-est del villaggio, c'� un premio interessante in palio..."; break;
        case 364 : texte = "Hai vinto il premio del Coloseeo?*Impressionante..."; break;
        case 365 : texte = "Se pensi di essere il mostro piu terrificante di Termina, allora credi che i tuoi sogni siano realt� mio povero amico..."; idsuiv=366; break;
        case 366 : texte = "Dammi retta, il mostro del lago � in assoluto il piu terrificante esistente. Tutti evitano di affrontarlo."; break;
        case 367 : texte = "Il Colosseo a sud di qui � l'attrazione principale nei dintorni.*Lo scopo � andare avanti il piu possibile prima di morire."; idsuiv=368; break;
        case 368 : texte = "Ma � sempre difficile trovare volontari, cos� il proprietario ha deciso di mettere in palio un premio estremamente prezioso."; break;
        case 369 : 
            texte = "Vuoi ascoltare la mia storia per 10 rupie?**              SI ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 370 : texte = "Vuoi ascoltare la mia storia per 10 rupie?**              si              NO ?"; break;
        case 371 : texte = "Stando a quanto dice il capo, a nord c'� il tempio di Xanto, conosciuto come il tempio della morte..."; idsuiv=372; break;
        case 372 : texte = "Si dice che quel tempio sia un passaggio per il mondo dei morti... Ma per raggiungere il mondo dei morti dovrai affrontare un intricato labirinto..."; idsuiv=373; break;
        case 373 : texte = "Pagami di nuovo se vuoi ascoltarmi ancora."; break;
        case 374 : 
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==1) {id=376; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==2) {id=380; chercheText(); break;}
            texte = "Stai cercando la Maschera Spirituale?*... chi l'avrebbe mai detto..."; idsuiv=375; break;
        case 375 : texte = "No, non so dove sia, ma so come usarla.*Torna da me se la trovi e te lo dir�."; break;
        case 376 : 
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=379; chercheText(); break;}
            texte = "Hai trovato la Maschera Sprituale??? *...*Ok, ascoltami attentamente, ti insegner� ad usarla."; idsuiv=377; break;
        case 377 : texte = "In presenza di uno spirito indebolito, dovrai suonare la Canzone dello Spirito con la tua Ocarina.*Ascolta la Canzone dello Spirito!"; break;
        case 378 : texte = "Hai imparato la Canzone dello Spirito!!!**Usa l'Ocarina per suonarla!"; break;
        case 379 : texte = "La Maschera Spirituale pu� essere utilizzata solo una volta, fanne buon uso..."; break;
        case 380 : texte = "Hai imprigionato uno spirito estremamente potente...*Fai in modo che non cada mai nelle mani sbagliate..."; break;
        case 381 : texte = "Il nostro villaggio raramente riceve visite...*Forse � dovuto al fatto che abbiamo sigillato le entrate..."; break;
        case 382 : 
            if (gpJeu->getJoueur()->hasObjet(O_BFEU)) {id=386; chercheText(); break;}
            if (gpJeu->getJoueur()->getAvancement()==66) {id=385; chercheText(); break;}
            texte = "Sei il primo visitatore che incontro da quando vivo qui.*Sono un anziano avventuriero, ero bravo come cercatore di testori..."; idsuiv=383;break;
        case 383 : texte = "Un giorno venni a conoscenza del tesoro della piramide, un oggetto magico...*Ma questo deserto ha segnato la mia rovina, non riesco ad attraversarlo. E' veramente troppo pericoloso..."; idsuiv=384; break;
        case 384 : texte = "Sembri determinato come lo ero in gioventu... D'accordo, se mi porti il tesoro della piramide, ti dar� il mio tesoro piu prezioso."; break;
        case 386 : 
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=389; chercheText(); break;}
            texte = "Hai trovato il tesoro???*Un'asta di fuoco, uh?*...*..."; idsuiv=387; break;
        case 387 : texte = "Quest'asta sar� piu utile a te che a me...*Puoi tenertela...*"; idsuiv=388; break;
        case 388 : texte = "Accetta questa ricompensa per mostrare il tesoro che un anziano ha cercato per tutta la vita...*La Canzone della Levitazione!!!"; break;
        case 389 : texte = "Suonata con uno strumento magico, questa canzone ti teletrasporter�. Ho sperato di abbandonare questo deserto grazie a lei, ma non ho mai trovato lo strumento adatto..."; break;
        case 390 : texte = "Hai imparato la Canzone della Levitazione!!!**Usa l'Ocarina per suonarla!"; break;
        case 391 : texte = "Link! Sono Pit!!!*Cosa stai facendo???*Raggiungi la Terra dell'Ovest!!!"; break;
        case 392 : texte = "Link, Sono Zelda, congratulazioni!!!*Rauru � al sicuro, per ora...*Raggiungi la Torre del Destino in cima alla montagna e ferma Ganon!"; break;
        case 393 : texte = "Guida : quando il misuratore di rabbia � pieno, ti trasformi in Oni-Link.*La tua arma si estende e la tua forza aumenta a discapito della difesa."; idsuiv=394; break;
        case 394 : texte = "Nei panni di Oni-Link, non puoi usare oggetti, ma puoi teletrasportarti all'entrata di un dungeon premendo L ed R."; idsuiv=395; break;
        case 395 : texte = "Ogni volta che Oni-Link sconfigge un nemico, il misuratore si svuota un po'. Quando � vuoto, Link riacquista la sua forma originale."; break;
        case 396 : texte = "Team leader, creatore e programmatore :                                                                  Vincent Jouillat"; break;
        case 397 : texte = "Scrittore e traduttore:                                                                                      Lobaluz"; break;
        case 398 : texte = "Aiuto nella Grafica :                                                                                      Harvestland"; break;
        case 399 : texte = "Aiuto nella Grafica :                                                                                    Sol�ne Jouillat"; break;
        case 400 : texte = "Illustratore :                                                                                                Raiden"; break;
        case 401 : texte = "Hai trovato la mappa di Termina!!!**Premi Start all'esterno per consultarla."; break;
        case 402 : texte = "La leggenda non accenna al fatto che dopo questi eventi, l'eroe fu colpito da una terribile maledizione..."; idsuiv=403; break;
        case 403 : texte = "Giorno dopo giorno, Link si stava trasformando in un mostro spietato ed incontrollabile di nome Oni-Link..."; idsuiv=404; break;
        case 404 : texte = "Bandito da Hyrule, Link chiese consiglio alla Principessa Zelda."; idsuiv=405; break;
        case 405 : texte = "Lei le indico la sua ultima speranza : un portale per un mondo segreto..."; break;
        case 406 : texte = "Partita salvata."; break;
        case 407 : texte = "Non c'� bisogno di bere questa pozione ora."; break;
        case 408 : texte = "AIUTO : Premi L e Y per consultare gli Aiuti."; break;
        case 409 : texte = "Grrrr... Come hai fatto a scappare dal mondo dei morti e a raggiungermi???"; idsuiv=410; break;
        case 410 : texte = "Perch� insisti nell'affrontarmi? *Anche se mi batterai, torner� in vita."; idsuiv=411; break;
        case 411 : texte = "La tua missione � inutile, abbadona ogni speranza! **Divertiamoci!"; break;
    }
	break; // Italian

case 5: // Spanish
    switch (id) {
        case 3  : 
            tmp = 4-(gpJeu->getJoueur()->nbQuarts()%4);
            os << tmp;
            texte = "Has encontrado un cuarto de coraz�n !!!";
            if (tmp<4) buffer = "Con "+os.str()+" mas obtendras un coraz�n adicional !!!";
            else buffer = "Tu numero de coraz�nes acaba de aumentar !!!";
            break;
        case 5 : texte = "Cueva del portal sellado.**Entrada prohibida."; break;
        case 6 : texte = "Templo de Farone**Salve los �rboles, coma castor!!!"; break;
        case 7 : texte = "Has encontrado las botas Pegasus !!! *Manten Shift o pulsa R para correr."; break;
        case 8 : texte = "N : Finca Este"; break;
        case 9 : texte = "O : Lago de Lanayru"; break;
        case 10 : texte = "S : Bosque Prohibido"; break;
        case 11 : texte = "S : Lago de Lanayru"; break;
        case 12 : texte = "N : Hasta el Templo Latoan"; break;
        case 13 : texte = "N : Pueblo de Ruto"; break;
        case 14 : texte = "-Servicio Anti Monstruos hUra�os y Salvajes- (S.A.M.U.S.)**Entrad si no os gustan los monstruos."; break;
        case 15 : texte = "O : Ciudad de Rauru"; break;
        case 16 : texte = "No has aprendido ning�n tema.";
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=17; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=26; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=28; chercheText();break;}
            break;
        case 17 : texte = "- CANCION DE VUELO*- No tocar";
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=19; chercheText();break;}
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=30; chercheText();break;}
            break;
        case 18 : texte = "- Canci�n de Vuelo*- NO TOCAR"; break;
        case 19 : texte = "- CANCION DE VUELO*- Eleg�a al Vac�o*- No tocar";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=22; chercheText();break;}
            break;
        case 20 : texte = "- Canci�n de Vuelo*- ELEGIA AL VACIO*- No tocar"; break;
        case 21 : texte = "- Canci�n de Vuelo*- Eleg�a al Vac�o*- NO TOCAR"; break;
        case 22 : texte = "- CANCION DE VUELO*- Eleg�a al Vac�o*- Canci�n del Esp�ritu*- No tocar"; break;
        case 23 : texte = "- Canci�n de Vuelo*- ELEGIA AL VACIO*- Canci�n del Esp�ritu*- No tocar"; break;
        case 24 : texte = "- Canci�n de Vuelo*- Eleg�a al Vac�o*- CANCION DEL ESPIRITU*- No tocar"; break;
        case 25 : texte = "- Canci�n de Vuelo*- Eleg�a al Vac�o*- Canci�n del Esp�ritu*- NO TOCAR"; break;
        case 26 : texte = "- ELEGIA AL VACIO*- No tocar";
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=33; chercheText();break;}
            break;
        case 27 : texte = "- Eleg�a al Vac�o*- NO TOCAR"; break;
        case 28 : texte = "- CANCION DEL ESPIRITU*- No tocar"; break;
        case 29 : texte = "- Canci�n del Esp�ritu*- NO TOCAR"; break;
        case 30 : texte = "- CANCION DE VUELO*- Canci�n del Esp�ritu*- No tocar"; break;
        case 31 : texte = "- Canci�n de Vuelo*- CANCION DEL ESPIRITU*- No tocar"; break;
        case 32 : texte = "- Canci�n de Vuelo*- Canci�n del Esp�ritu*- NO TOCAR"; break;
        case 33 : texte = "- ELEGIA AL VACIO*- Canci�n del Esp�ritu*- No tocar"; break;
        case 34 : texte = "- Eleg�a al Vac�o*- CANCION DEL ESPIRITU*- No tocar"; break;
        case 35 : texte = "- Eleg�a al Vac�o*- Canci�n del Esp�ritu*- NO TOCAR"; break;
        case 36 : texte = "N : Pueblo de Ruto*S : Finca Este"; break;
        case 37 : texte = "S : Pueblo de Ruto*E : Hasta el desierto"; break;
        case 38 : texte = "Entrada de la mina"; break;
        case 39 : texte = "O : Hasta el Templo Latoan*E : Pueblo de Ruto"; break;
        case 40 : texte = "Lo siento, ten�a solo una botella."; break;
        case 41 : texte = "Vendo una botella por 100 rupias, quieres?**               SI ?            no  "; 
            if (gpJeu->getJoueur()->hasBouteille(0)) {id=40; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) idsuiv=44;
            else idsuiv=45;
            break;
        case 42 : texte = "Vendo una botella por 100 rupias, quieres?**               si              NO ?"; idsuiv=43; break;
        case 43 : texte = "Vuelve si cambias de opini�n."; break;
        case 44 : texte = "No tienes bastante!"; break;
        case 45 : texte = "Gracias!"; break;
        case 46 : texte = "Has encontrado una botella vac�a !!!**Podr�s utilizarla para almacenar p�cimas."; break;
        case 47 : texte = "Hay un paso secreto al Oeste del pueblo que lleva al Templo Latoan, pero necesitar�s bombas para cogerlo."; break;
        case 49 :
            if (gpJeu->getJoueur()->getAvancement()>3 && !gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) 
                texte = "Si buscas un balso de bombas, deber�as ir a ver el hombre quien trabaja en la mina, utiliza un mot�n.";
            else texte = "Fuera de aqu� !"; break;
        case 50 : 
            if (gpJeu->getJoueur()->getAvancement()==5 || gpJeu->getJoueur()->getAvancement()==6)
                texte = "El alcalde prohib� el acceso a la mina desde que monstruos salgan de aqu�.";
            else if (gpJeu->getJoueur()->getAvancement()==7)
                texte = "Dices que quiz�s alguien esta bloqueado en la mina? Y que?";
            else if (gpJeu->getJoueur()->getAvancement()==8 || gpJeu->getJoueur()->getAvancement()==9)
                texte = "El alcalde te autoriz� a pasar? Entonces ap�rtate!";
            else texte = "..."; break;
        case 54 : texte = "Bienvenido al pueblo de Ruto.**Y que queda entre nosotros, desconf�a de todo el mundo por aqu�..."; break;
        case 55 : texte = "Este pueblo de fachada pr�spera es en realidad lo m�s pobre de Termina...*Y no podemos contar con el alcalde para que cambia eso..."; break;
        case 56 : texte = "Las turistas que vienen en este pueblo son o perdidos, o totalmente locos.*En lo que me concierne siempre tengo una mapa conmigo."; break;
        case 57 : texte = "S : Hasta la Finca Este*O : Hasta el Templo Latoan*E : Pueblo de Ruto"; break;
        case 58 : texte = "S : Finca Este"; break;
        case 59 : texte = "Templo Latoan"; break;
        case 60 : texte = "E : Tierras olvidadas"; break;
        case 61 : texte = "S : Pueblo de Ruto*O : Muerta segura"; break;
        case 62 : texte = "Oasis m�gico"; break;
        case 63 : texte = "Cueva de la Hada"; break;
        case 64 : texte = "Templo de Din**El poder de las hadas recompensar� a los valientes !"; break;
        case 65 : texte = "                     ???"; break;
        case 66 : texte = "Templo de Lanayru"; break;
        case 67 : texte = "O : Pantano de la bruja"; break;
        case 68 : texte = "E : Bosque prohibido"; break;
        case 69 : texte = "N : Finca Este*O : Hasta la ciudad de Rauru"; break;
        case 70 : texte = "N : Ciudad de Rauru"; break;
        case 71 : texte = "O : Finca Oeste"; break;
        case 72 : texte = "N : Tierras olvidadas*S : Ciudad de Rauru"; break;
        case 73 : texte = "N : Ciudad de Rauru*S : Lago de Lanayru*O : Finca Oeste*E : Finca Este"; break;
        case 74 : texte = "E : Finca Este"; break;
        case 75 : texte = "Lo siento, no tengo nada m�s en dep�sito."; break;
        case 76 : texte = "Vendo un mejor escudo por 250 rupias, quieres? *               SI ?            no  "; 
            if (gpJeu->getJoueur()->getBouclier()>1) {id=75; chercheText();break;}
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<250) idsuiv=44;
            else idsuiv=45;
            break;
        case 77 : texte = "Vendo un mejor escudo por 250 rupias, quieres? *               si              NO ?"; idsuiv=43; break;
        case 78 : texte = "Has encontrado un nuevo escudo !!!**Tu defensa aumenta de un punto, resistes mejor a los ataques enemigos !!!"; break;
        case 79 : texte = "Porque soy otra vez yo quien tengo que cuidar estas gallinas ???"; break;
        case 80 : texte = "Me gusta barrer !"; break;
        case 81 : texte = "Rauru es la ciudad la m�s graciosa del pa�s, muchos visitantes llegan cada d�a para admirarla."; break;
        case 82 : texte = "Se dice que un instrumento m�gico se encuentra en alg�n sitio de las tierras de Termina. *Me pregunto si lo ver� un d�a..."; break;
        case 83 : texte = "Has encontrado el instrumento m�gico ??? **Esperaba que ser�a un saxo..."; break;
        case 84 : texte = "Mis padres se han perdido."; break;
        case 85 : texte = "Me gusta pasear !"; break;
        case 86 : texte = "S : Ciudad de Rauru*E : Casa encantada"; break;
        case 87 : texte = "Casa encantada**Vengan a enriquecer nuestra colecci�n de almas!"; break;
        case 88 : texte = "E : Hasta el Templo Latoan"; break;
        case 89 : texte = "Templo de Farore**El poder de las hadas recompensar� a los valientes !"; break;
        case 90 : texte = "O : Pueblo de Mido"; break;
        case 91 : texte = "N : Monta�as del destino"; break;
        case 92 : texte = "Templo de Zelda"; break;
        case 93 : texte = "O : Cementerio"; break;
        case 94 : texte = "Secreto del desierto :*Levanta las piedras del p�jaro en el sentido de las agujas del reloj acabando por el ojo para abrir el camino."; break;
        case 95 : texte = "S : Pantano de la bruja"; break;
        case 96 : texte = "E : Ciudad de Rauru"; break;
        case 97 : texte = "N : Finca Oeste*S : Choza de la bruja"; break;
        case 98 : texte = "O : Pueblo de Kasuto*E : Choza de la bruja"; break;
        case 99 : texte = "Choza de las p�cimas**Venid cambiar vuestras rupias por las p�cimas las m�s poderosas del pa�s !!!"; break;
        case 100 : texte = "E : Lago de Lanayru"; break;
        case 101 : texte = "N : Cementerio*S : Pueblo de Kasuto"; break;
        case 102 : texte = "Pueblo de Kasuto**   -- Prihibido a los humanos (vivos) --"; break;
        case 103 : texte = "Truco : Manten L para mirar alrededor con las flechas del teclado."; break;
        case 104 : texte = "N : Pueblo de Kasuto*E : Pantano de la bruja"; break;
        case 105 : texte = "Coliseo de los monstruos**Venid numerosos !"; break;
        case 106 : texte = "Pareces bastante fuerte, deber�as ir entrenarte en la arena al Sur del pueblo. Dicen que hay un objeto muy �til escondido dentro..."; break;
        case 107 : texte = "Vaya.*Una nueva especie ?**Sabes hablar ?"; break;
        case 108 : texte = "Este pueblo es el ultimo amparo contra la humanidad."; break;
        case 109 : texte = "Hola, soy un monstruo d�bil."; break;
        case 110 : texte = "Atorado ?***Sin embargo la soluci�n no est� tan lejos."; break;
        case 111 : texte = "S : Pueblo de Kasuto"; break;
        case 112 : texte = "Templo de Xanto**Los muertos no hablan..."; break;
        case 113 : texte = "Han probado ya ustedes el martillo sobre los cr�neos?"; break;
        case 114 : texte = "E : Finca Oeste"; break;
        case 115 : texte = "Pueblo de Mido"; break;
        case 116 : texte = "Tienen todos los j�venes de tu edad tan mal gusto para la ropa?"; break;
        case 117 : texte = "Bienvenido al pueblo de Mido, pero no te sientas obligado de quedarte."; break;
        case 118 : texte = "Grrr... pensaba estar por fin en paz aqu�..."; break;
        case 119 : texte = "Solo el vac�o total podr� quitar la piedra."; break;
        case 120 : texte = "Templo de Nayru**El poder de las hadas recompensar� a los valientes !"; break;
        case 121 : texte = "Pesa del destino**Solo el aliado del bueno y del malo atravesar� esta cueva."; break;
        case 122 : texte = "S : Pueblo de Mido"; break;
        case 123 : texte = "Templo de Eldin"; break;
        case 124 : texte = "S : Finca Oeste"; break;
        case 125 : texte = "La fuerza de los titanes recaer� sobre el h�roe legendario..."; break;
        case 126 : texte = "Torre del Destino*H�roe de Hyrule ten cuidado, aqu� reina ahora el vil Ganon, aqu� se jugar� el porvenir del mundo."; break;
        case 127 : texte = "Felicitaciones !**Has conseguido alcanzar la cumbre del monte Planito !"; break;
        case 128 : texte = "No puedes transformarte aqu� !!!"; break;
        case 129 : texte = "No puedes entrar en un pueblo con esta apariencia !!!"; break;
        case 130 : texte = "Link, soy Pit. Te hablo por telepat�a. No debes en ning�n caso transformarte en un pueblo !*Te teletransporto fuera."; break;
        case 131 : texte = "Has encontrado una espada !!!**Pulsa B para atacar o manten B para cargar un ataque genial."; break;
        case 132 : texte = "Has encontrado el mapa !!!**Pulsa START para ver el mapa del calabozo."; break;
        case 133 : texte = "Has encontrado la br�jula !!!**Las arcas y el jefe del calabozo se ven ahora sobre el mapa."; break;
        case 134 : texte = "Has encontrado la llave del jefe !!!**Util�zala para llevar a su antro."; break;
        case 135 : texte = "Has encontrado una llave peque�a.**Util�zala para abrir una puerta."; break;
        case 136 : texte = "Has encontrado un nuevo coraz�n !!!**Tu vida m�xima aumenta de un coraz�n !!!"; break;
        case 137 : texte = "Has encontrado un Graal !!!"; break;
        case 138 : texte = "Vine para salvarme ?*Muchas gracias !"; 
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
        case 139 : texte = "Cavando galer�as descubrimos esto antro de monstruos..."; idsuiv=142; break;
        case 140 : texte = "Fuimos capturados todos por los monstruos viviendo en estas cavernas."; idsuiv=142; break;
        case 141 : texte = "Nuestro jefe est� abajo, ve a salvarle de prisa!"; idsuiv=142; break;
        case 142 : texte = "Encontr� esto en la mina, toma, podr�a ayudarte!"; break;
        case 143 : 
            if (gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=50; chercheText();break;}
            texte = "Venciste el monstruo de la mina ??? *Felicitaciones!!!"; idsuiv=144; break;
        case 144 : texte = "Soy el jefe de los obreros, dices que estabas busc�ndome?"; idsuiv=145; break;
        case 145 : texte = "Toma esta bolsa llena de bombas, deber�a ayudarte."; break;
        case 146 : texte = "Has encontrado la Bolsa de Bombas !!!*Y est� llena !!!*Pulsa Y para poner una."; break;
        case 147 : texte = "Has encontrado los Guantes !!!**Ahora puedes levantar las piedras ligeras pulsando X."; break;
        case 148 : 
            if (gpJeu->getJoueur()->hasObjet(O_ARC)) {id=50; chercheText();break;}
            texte = "Soy el brazo derecho del alcalde, me mand� salvar a su hija...*Pero no pude hacer nada, estos fantasmas son invencibles..."; idsuiv=149; break;
        case 149 : texte = "No te quedes aqu�, no podr�s hacer nada con tus armas actuales..."; idsuiv=150; break;
        case 150 : texte = "Para continuar tu b�squeda, sigue el camino al Oeste de la ciudad. Con este arco podr�s alcanzar la esfera y abrir el camino..."; break;
        case 151 : texte = "Has encontrado el Arco !!!*Ahora puedes atacar a distancia y alcanzar objetos alejados !!!"; break;
        case 152 : 
            if (gpJeu->getJoueur()->getAvancement()>64) {id=153; chercheText();break;}
            texte = "Venciste el vampiro y viniste para salvarme? Muchas gracias! Mi padre es el alcalde de la ciudad, ve a verlo, estoy segura que te recompensar�."; break;
        case 153 : texte = "No te preocupes por mi, puedo volver a casa sin ayuda ahora que el vampiro est� vencido."; break;
        case 154 : 
            if (gpJeu->getJoueur()->getAvancement()==13)
                texte = "Has recibido la autorizaci�n del alcalde ?*Se prudente, los que se aventuran por ah� nunca vuelven...";
            else if (gpJeu->getJoueur()->getAvancement()<13)
                texte = "Orden del alcalde : el acceso a esta regi�n est� prohibido.";
            else texte = "..."; break;
        case 155 : texte = "No puedes huir ahora!"; break;
        case 156 : texte = "Has encontrado el martillo !!!**Ahora puedes aplastar los obst�culos molestos !"; break;
        case 157 : texte = "Has encontrado el lanzagarfios !!!**Ahora puedes atravesar los precipicios !"; break;
        case 158 : texte = "Hall del Coliseo"; break;
        case 159 : texte = "Arena 1"; break;
        case 160 : texte = "Arena 2"; break;
        case 161 : texte = "Arena 3"; break;
        case 162 : texte = "Arena 4"; break;
        case 163 : texte = "Entrega de premios"; break;
        case 164 : texte = "Arena especial**Venid a probar el premio especial !!!"; break;
        case 165 : texte = "Has encontrado las Aletas !!!**Ahora puedes nadar y atravesar superficies de agua !!!"; break;
        case 166 : texte = "Has encontrado una Loriga !!!**Tu defensa aumenta de un punto !!!"; break;
        case 167 : texte = "Has encontrado una mejor Loriga !!!   *Tu defensa aumenta de un punto !!!"; break;
        case 168 : texte = "Jijijijiji !!!*Felicitaciones Link ! Has conseguido deshacerte de la maldici�n. Y al mismo tiempo me has liberado !!!"; idsuiv=169; break;
        case 169 : texte = "Para recompensarte de tus esfuerzos no te matar� hoy, tengo una misi�n m�s importante."; idsuiv=170; break;
        case 170 : texte = "Si quieres pararme, une te a mi en el templo de los muertos si tienes la valor de hacerlo.*Adi�s ! Jijijijiji !!!"; break;
        case 171 : texte = "Link, soy Zelda, te hablo por telepat�a. Estoy con Pit, �nete a nosotros de prisa, tenemos un gran problema."; break;
        case 172 : texte = "Buenos d�as Link, te esperaba.**Me llamo Pit, fui encargado de la vigilancia de esta cueva por la princesa Zelda."; idsuiv=173; break;
        case 173 : texte = "Me avis� de tu llegada y me pidi� que te ayude.*Mi casa est� justo aqu�, estaremos mejor para hablar, s�gueme."; break;
        case 174 : texte = "Pit te pidi� que no salgas del bosque."; break;
        case 175 : texte = "Has encontrado la Varilla de Fuego !!!**Ahora puedes lanzar potentes bolas de fuego !!!"; break;
        case 176 : 
            if ((gpJeu->getZone() == 23 && gpJeu->getJoueur()->getCoffre(8,19))
            || (gpJeu->getZone() == 24 && gpJeu->getJoueur()->getCoffre(9,24))
            || (gpJeu->getZone() == 25 && gpJeu->getJoueur()->getCoffre(10,21))) {
                id=50; chercheText();break;}
            texte = "Te esperaba Link.*Transmito la potencia de la diosa a tu espada para restituir el poder de la Espada Maestra."; break;
        case 177 : 
            if (gpJeu->getJoueur()->getEpee()==5) {id=178; chercheText();break;}
            texte = "La potencia de la Espada Maestra aumenta ! **Ve de prisa al pr�ximo templo !"; break;
        case 178 : texte = "La Espada Maestra ha alcanzado su potencia m�xima !!!  *Incluso Oni-Link no deber�a resistir a su hoja!"; break;
        case 179 : texte = "Has encontrado la Varilla de Hielo !!!**Ahora puedes helar lo que quieras !!!"; break;
        case 180 : texte = "Has encontrado un nuevo escudo !!!**Tu defensa aumenta, resistes ahora mejor a los ataques !!!"; break;
        case 181 : texte = "Link, soy Zelda, te hablo por telepat�a. No entres en este calabozo si no estas perfectamente preparado, es sin duda una trampa de Oni-Link."; break;
        case 182 : texte = "As� has venido ?*Quiz�s quieres morir, va a ser un placer ayudarte.*Jijijijiji !!!"; break;
        case 183 : texte = "La esencia de Oni-Link fue encerrada en la M�scara del Esp�ritu !!!*Lo has hecho !!!"; break;
        case 184 : texte = "Grrrr !!! No lo puedo creer, has vencido a Oni-Link ??? Impresionante...*Me imagino que no contabas con verme, sin embargo estamos en el mundo de los muertos."; idsuiv=185; break;
        case 185 : texte = "Oni-Link me ha dado la energ�a que necesitaba para resucitarme, entonces estoy de vuelta m�s pronto que lo pensaba.*Gwajajajajaja !!!"; idsuiv=186; break;
        case 186 : texte = "A prop�sito, quiz�s te preguntas de donde viene Oni-Link ? Es muy simple, la ultima vez quer�a estar seguro que nunca m�s vendr�as a molestar mis planos, entonces utilic�"; idsuiv=187; break;
        case 187 : texte = "la Trifuerza para cambiarte en un monstruo de los m�os. Pero no hab�a bastantes tinieblas en tu coraz�n, y esta transformaci�n no fue fulgurante..."; idsuiv=188; break;
        case 188 : texte = "Basta ya, tengo muchos proyectos...*Ser�a un gran placer acabar contigo, pero no veo la utilidad..."; idsuiv=189; break;
        case 189 : texte = "Para que lo sepas : solo las criaturas de las tinieblas pueden escaparse de aqu�.*Entonces adi�s! Gwajajajajaja !!!"; break;
        case 190 : 
            if (!gpJeu->getJoueur()->getOni()) {id=184; chercheText();break;}
            texte = "Onilito ? Cuando viene este caf� ???*Que ??? Eres tu Link ???"; idsuiv=184; break;
        case 191 : texte = "              Mundo de los Muertos"; break;
        case 192 : texte = "Link, soy Zelda, te hablo por telepat�a. Es horrible, Ganon est� de vuelta !!!"; idsuiv=193; break;
        case 193 : texte = "Ha restaurado su ej�rcito, que se est� preparando a atacar Rauru!*Todav�a puedes pararlos, corre a interceptarlos en la finca Oeste!"; break;
        case 194 : texte = "Has encontrado el gran Arco de las Hadas !!! **Ahora tiras flechas de una potencia extraordinaria !!!"; break;
        case 195 : texte = "Has encontrado la Trifuerza !!!"; break;
        
        case 197 : texte = "Tutorial : pulsa A para hablar, leer o abrir una arca, y A para pasar los textos en la pantalla."; break;
        case 198 : texte = "Pulsa X para levantar un objeto ligero."; break;
        case 199 : texte = "Quieres gravar tu juego ?**                     ? SI ?*                       no  "; break;
        case 200 : texte = "Quieres gravar tu juego ?**                       si  *                     ? NO ?"; break;
        case 201 : texte = "                    Nivel 1 :                                                                                 Templo de Farone"; break;
        case 202 : texte = "                    Nivel 2 :                                                                                   Mina de Ruto"; break;
        case 203 : texte = "                    Nivel 3 :                                                                                 Templo de Latoan"; break;
        case 204 : 
            if (gpJeu->getJoueur()->getEpee()>=2) 
                texte = "                    Nivel 9 :                                                                                  Casa embrujada";
            else texte = "                    Nivel 4 :                                                                                  Casa embrujada"; break;
        case 205 : texte = "                    Nivel 5 :                                                                                 Templo de Eldin"; break;
        case 206 : texte = "                    Nivel 6 :                                                                             Coliseo de los Monstruos"; break;
        case 207 : texte = "                    Nivel 7 :                                                                                Templo de Lanayru"; break;
        case 208 : texte = "                    Nivel 8 :                                                                                 Templo de Zelda"; break;
        case 209 : texte = "                   Nivel 10 :                                                                                 Templo de Din"; break;
        case 210 : texte = "                   Nivel 11 :                                                                                 Templo de Nayru"; break;
        case 211 : texte = "                   Nivel 12 :                                                                                 Templo de Farore"; break;
        case 212 : 
            if (gpJeu->getJoueur()->getX()>14*320) {id=191; chercheText();break;}
            texte = "                   Nivel 13 :                                                                                 Templo de Xanto"; break;
        case 213 : texte = "                   Nivel ? :                                                                                  Templo secreto"; break;
        case 214 : texte = "                 Nivel Final :                                                                                Torre del Destino"; break;
        case 215 :texte = "               Ya estas cansado ?               ?                   SEGUIR                  ?                  Grabar y dejar                                Dejar sin grabar              "; break;
        case 216 :texte = "               Ya estas cansado ?                                   Seguir                     ?               GRABAR Y DEJAR              ?                 Dejar sin grabar              "; break;
        case 217 :texte = "               Ya estas cansado ?                                   Seguir                                     Grabar y dejar                 ?              DEJAR SIN GRABAR             ?"; break;
        case 218 : texte = "Despu�s de la derrota de Ganon y la desaparici�n de la Trifuerza, la leyenda deja creer que la paz dur�... *Pero cada leyenda oculta una oscura realidad..."; idsuiv=402; break;
        case 220 : texte = "Si... Es por ah�... *Casi estamos..."; idsuiv=221; break;
        case 221 : texte = "Lo siento mucho que no puedas llevar armas... Pero entiendes... Corres peligro de transformarte en cada momento...*Seria demasiado peligroso..."; idsuiv=222; break;
        case 222 : texte = "Ya estamos! Es aqu�!*No te muevas, activo el portal...**Estas listo ?"; break;
        case 223 : texte = "Liberado de la maldici�n de Ganon, Link pudo volver a Hyrule sin riesgo.**La Trifuerza, la Espada Maestra, as� como el Ocarina fueron entregados a la familia real de Hyrule, mientras que la M�scara de Oni-Link fue confiada a las hadas para ser escondida m�s all� del tiempo y del espacio...**El portal que conduc�a a Termina fue sellado por la princesa Zelda y por Pit, para nunca m�s ser abierto, y este horrible cap�tulo fue borrado de la leyenda..."; idsuiv=224; break;
        case 224 : texte = "El pueblo de Hyrule nunca supo lo que ocurro en las misteriosas comarcas de Termina, tampoco que el temible Ganon ya preparaba su regreso...**Pero lo que nadie ignoraba, fue el regreso en Hyrule de su h�roe, qui�n estar�a siempre all� para defender el Reino frente a la tinieblas."; break;
        case 225 : texte = "Has encontrado un escudo !!!**Tu defensa aumenta de un punto, te resistes mejor a los ataques enemigos !!!"; break;
        case 226 : texte = "Pit est� esper�ndote en la casa aqu� al lado."; break;
        case 227 : 
            if (gpJeu->getJoueur()->getMagieMax()>32) texte = "...";
            else texte = "Felicitaciones Link, has conseguido encontrarme. Para recompensarte, voy a doblar la capacidad de tu reserva de magia."; break;
        case 228 : texte = "La capacidad de tu reserva de magia acaba de doblar !!!"; break;
        case 229 : texte = "Has encontrado el Ocarina del Tiempo !!!**Su potencia es tal que para el tiempo cuando soplas dentro !"; break;
        case 230 : texte = "Has encontrado la L�mpara !!!**Ahora puedes hacer surgir llamas!!!"; break;
        case 231 : texte = "Has encontrado la M�scara del Esp�ritu !!!**Una extra�a aura se desprende de el..."; break;
        case 232 : 
            if (gpJeu->getJoueur()->getTutoriel()==3) {id=233; chercheText();break;}
            gpJeu->getJoueur()->setTutoriel(3);
            texte = "Felicitaciones, me has encontrado !!!**Soy la gorda hada del desierto, organizo colectas de rupias !"; idsuiv=233; break;
        case 233 : texte = "Dame 100 rupias ahora !!!**               SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<100) {idsuiv=236; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70 && gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=239; break;}
            if (gpJeu->getJoueur()->getFlecheMax()==70) {idsuiv=237; break;}
            if (gpJeu->getJoueur()->getBombeMax()==30) {idsuiv=238; break;}
            idsuiv = 237 + (rand()%2); break;
        case 234 : texte = "Dame 100 rupias ahora !!!**               si              NO ?"; idsuiv=235; break;
        case 235 : texte = "Me haces perder el tiempo, fuera !"; break;
        case 236 : texte = "No tienes bastante!!!*Me haces perder el tiempo, fuera !"; break;
        case 237 : texte = "Aumento la cantidad m�xima de bombas que puedes transportar, gracias a qui�n ???"; break;
        case 238 : texte = "Aumento la cantidad m�xima de flechas que puedes transportar, gracias a qui�n ???"; break;
        case 239 : texte = "Tengo bastante rupias, desaparece !"; break;
        case 240 : texte = "Has encontrado los Guantes de Oro !!!**Ahora puedes levantar las piedras pesadas pulsando X."; break;
        case 241 : texte = "Solo dejar� pasar a las criaturas mal�ficas."; 
            if (gpJeu->getJoueur()->getOni()) idsuiv=243; break;
        case 242 : texte = "Solo dejar� pasar a las criaturas beneficiosas."; 
            if (!gpJeu->getJoueur()->getOni()) idsuiv=244; break;
        case 243 : texte = "Pareces mal�fico...*Vale puedes pasar!"; break;
        case 244 : texte = "Pareces beneficioso...*Vale puedes pasar!"; break;
        case 245 : 
            if (gpJeu->getJoueur()->getAvancement()==2) {id=250; chercheText();break;}
            texte = "Debe de preguntarte donde estas.*Aqu� est� Termina, y no necesitas saber m�s al respecto..."; idsuiv=246; break;
        case 246 : texte = "Es una tierra secreta que habr�a tenido que quedarlo, la princesa Zelda nunca habr�a tenido que enviarte aqu�..."; idsuiv=247;  break;
        case 247 : texte = "M�s precisamente estas en el bosque de Termina. En este bosque hay un templo, y en este templo hay un objeto sagrado capaz de conjurar cualquier maleficio..."; idsuiv=248; break;
        case 248 : texte = "Encuentra este objeto, luego vuelve a verme.*Abrir� el portal una ultima vez para tu regreso."; idsuiv=249; break;
        case 249 : texte = "Ultima cosa, no salgas del bosque para nada del mundo ! Tu presencia aqu� es secreta, adem�s, en tu estado eres una amenaza para todos los que te cruzas con..."; idsuiv=250; break;
        case 250 : texte = "Buena suerte Link!"; break;
        case 251 : 
            if (gpJeu->getJoueur()->getAvancement()==3) {id=250; chercheText();break;}
            texte = "Que ??? El graal no ha conseguido librarte de la maldici�n ??? Es... impensable..."; idsuiv=252; break;
        case 252 : texte = "Esta maldici�n debe de ser poderos�sima... Pero si miras bien queda esperanza..."; idsuiv=253; break;
        case 253 : texte = "El graal te surti� efecto, lo has notado.*De ahora en adelante tardas m�s para transformarte."; idsuiv=254; break;
        case 254 : texte = "Pero es de doble filo... Porque cuando estas transformado, lo quedas m�s tiempo..."; idsuiv=255; break;
        case 255 : texte = "Esc�chame Link, quedan aun 4 otros graals en los templos de Termina...*Se dice que los 5 juntos tienen tanto poder como la Trifuerza ella misma."; idsuiv=256; break;
        case 256 : texte = "Gracias al graal que has encontrado, eres ya un poco menos peligroso, entonces te autorizo a explorar Termina libremente."; idsuiv=257; break;
        case 257 : texte = "Avent�rate fuera del bosque, busca y encuentra los graals, y ser�s salvado.*Pero no deber�s en ning�n caso ir en un pueblo si estas transformado."; idsuiv=258; break;
        case 258 : texte = "Toma esta mapa, seguro que te ayudar�...*Buena suerte!"; break;
        case 259 : 
            if (gpJeu->getJoueur()->getEpee()>=2) {id=271; chercheText();break;}
            texte = "Encantada de verte sano y salvo Link ! Ahora que no corres el riesgo de transformarte, pens� que apreciar�as de tener esto..."; break;
        case 260 : texte = "Has encontrado la Espada Maestra!!!**Su incre�ble potencia parece palpable !!!"; break;
        case 261 : texte = "Por desgracia la necesitar�s...*Oni-Link fue liberado...*Lo pod�amos ver antes..."; idsuiv=262; break;
        case 262 : texte = "Por cada nuevo graal encontrado, la frecuencia de tus transformaciones disminu�a, pero la duraci�n de vida de Oni-Link aumentaba..."; idsuiv=263; break;
        case 263 : texte = "Adem�s, el comportamiento de Oni-Link me extra�a...*Con su naturaleza destructiva hubiera tenido que atacar un pueblo..."; idsuiv=264; break;
        case 264 : texte = "Deber�a alegrarme, pero tengo miedo de saber que el tiene intereses m�s importantes no es por nada una buena noticia..."; idsuiv=265; break;
        case 265 : texte = "Sin embargo, hemos establecido un plan de acci�n para vencerlo. Esc�chame con mucha atenci�n..."; idsuiv=266; break;
        case 266 : texte = "La Espada Maestra es una arma temible, pero no ser� suficiente contra Oni-Link...*...de momento..."; idsuiv=267; break;
        case 267 : texte = "Hay 3 templos secretos escondidos en Termina. En estos templos se encuentran hadas cuyos poderes aumentaran el poder de tu espada. Encu�ntralas todas."; idsuiv=268; break;
        case 268 : texte = "Entonces estar�s en pie de igualdad con Oni-Link.*Sin embargo, Oni-Link es solo energ�a y no puede ser vencido..."; idsuiv=269; break;
        case 269 : texte = "La M�scara del Esp�ritu te permitir� de encerarlo para siempre. Para eso, tendr�s que encontrar esta m�scara, encontrar el Ocarina m�gico y encontrar la melod�a que lo recluir�."; idsuiv=270; break;
        case 270 : texte = "Tu b�squeda solo empieza..."; break;
        case 271 : texte = "Encuentra las 3 hadas, la m�scara, el Ocarina, y la canci�n del esp�ritu, y luego ve a enfrentarte a Oni-Link!"; break;
        case 272 : 
            if (gpJeu->getJoueur()->getEpee()<2) {id=50; chercheText();break;}
            texte = "Como lo sabes, la Espada Maestra puede vencer a los fantasmas, reflejar los ataques m�gicos, y destruir las barreras m�gicas...*Util�zala bien..."; break;
        case 273 : texte = "No hay tiempo que perder!*Ve ahora mismo a la finca Oeste para interceptar el ej�rcito de Ganon!"; break;
        case 274 : texte = "Date prisa Link, que esperas ?*Navidad ???"; idsuiv=275; break;
        case 275 : texte = "Eh... Porque me hablas de mi ?*Estoy... pues... protegiendo a la princesa! *Gracias a quien te crees que no fue raptada esta vez ? D�melo ?"; break;
        case 276 : 
            if (gpJeu->getJoueur()->getAvancement()==69) {id=282; chercheText();break;}
            texte = "Link... hay una cosa que tendr�a que decirte desde el principio...*Este mundo, Termina..."; idsuiv=277; break;
        case 277 : texte = "Este mundo es muy reciente, fue fabricado en su totalidad por la Trifuerza y por un deseo... La gente, sus recuerdos y sus historias as� fueron fabricados..."; idsuiv=278; break;
        case 278 : texte = "Si... Lo adivin�, soy yo quien ped� a la Trifuerza crear este mundo... Es un mundo pensado para contener todo lo que podr�amos necesitar."; idsuiv=279; break;
        case 279 : texte = "Encontraste los graals, Oni-Link encontr� su amo, y Ganon encontr�...*...la Trifuerza..."; idsuiv=280; break;
        case 280 : texte = "Cre� este mundo para servir de escondite para la Trifuerza, pero Ganon la encontr� una vez m�s..."; idsuiv=281; break;
        case 281 : texte = "Link! Ese pa�s y esa gente fueron creados, pero ahora son reales de verdad! Si no hacemos nada, este mundo se parecer� pronto al ex-mundo de las tinieblas!"; idsuiv=282; break;
        case 282 : texte = "Lo dejo por tu cuenta una vez m�s, Link, salva este mundo!"; break;
        case 283 : 
            texte = "Bienvenida en la casa de estudio de monstruos de todo estilo!"; 
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
        case 284 : texte = "Te acuerdas de mi ? Me ayudaste un mont�n en Hyrule.*Eh... Te preguntas como he llegado a Termina ? Eh... no importa!"; idsuiv=285; break;
        case 285 : texte = "Este inmenso mundo est� lleno de monstruos, no pod�a perderme el viaje!"; idsuiv=286; break;
        case 286 : texte = "Entonces voy a catalogar cada monstruo en una nueva enciclopedia!**Con tu ayuda, por supuesto."; idsuiv=287; break;
        case 287 : texte = "No tengo m�s cuartos de coraz�n, ahora el dinero es mi moneda m�s cotizada.*Te pagar� un buen precio por cada nuevo monstruo a�adido en la enciclopedia."; idsuiv=288; break;
        case 288 : texte = "Pasa a verme cuando quieras para recibir tus beneficios. Si no puedes transportar todo, conservar� el excedente para ti."; idsuiv=289; break;
        case 289 : texte = "Basta con matar a los monstruos para que sean a�adidos.*Puedes consultar la enciclopedia pulsando L y B!"; break;
        case 290 : 
            texte = "Vaya... que raro eres...";
            if (gpJeu->getJoueur()->getEnnemi(75) 
            || !gpJeu->getJoueur()->hasObjet(O_ENCYCL)) break;
            texte += "*Te a�ado en la enciclopedia!!!"; break;
        case 291 : 
            os << gpJeu->getJoueur()->getSolde();
            texte = "Te debo " + os.str() + " rupias.";
            idsuiv=292; break;
        case 292 : texte = "Quieres tu dinero ahora ?**              SI ?            no  "; break;
        case 293 : texte = "Quieres tu dinero ahora ?**              si              NO ?"; break;
        case 294 : texte = "Tengo una noticia para ti ! Parece que los monstruos que hab�as vencido en Hyrule han sido misteriosamente resucitados ! Se dice que pasean en las comarcas de Termina..."; idsuiv=295; break;
        case 295 : texte = "Son 3.*Si los matas, te ofrecer� un precio... especial..."; break;
        case 296 : texte = "Has vencido a los 3 monstruos raros ???*...*Tu recompensa te espera abajo..."; break;
        case 297 : texte = "Has vencido todos los monstruos...*Es incre�ble..."; break;
        case 298 : texte = "Hola Link, como est�n tus bombas ?"; break;
        case 299 : texte = "No tengo m�s precio que poner en juego, lo siento."; break;
        case 300 : texte = "Una de estas arcas contiene un cuarto de coraz�n, quieres probar tu fortuna por 10 rupias? Podr�s abrir solo uno, vale ?*              SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 301 : texte = "Una de estas arcas contiene un cuarto de coraz�n, quieres probar tu fortuna por 10 rupias? Podr�s abrir solo uno, vale ?*              si              NO ?"; break;
        case 302 : texte = "Elige un arca."; break;
        case 303 : texte = "Hey! Hay que pagar para abrir una de mis arcas!!!"; break;
        case 304 : texte = "Has perdido! Este arca est� vac�a."; break;
        case 305 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=342; chercheText(); break;}
            texte = "Que quiere de beber ?"; break;
        case 306 : texte = "Estas buscando al hombre que trabaja en la mina? Nadie le ha visto desde que han cerrado la mina... Quiz�s todav�a est� dentro..."; break;
        case 307 : texte = "Este saloon era muy frecuentado...*...anta�o..."; break;
        case 308 : texte = "YO soy el alcalde de este pueblo y NO quiero hablar contigo!"; break;
        case 309 : texte = "Dices que quiz�s alguien est� encerrado en la mina ?**... ... ..."; 
            if (gpJeu->getJoueur()->getAvancement()==8) {id=308; chercheText();} 
            else idsuiv=310; break;
        case 310 : texte = "Vale, dame 10 rupias y te autorizo el acceso a la mina. Ok ?*              SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; 
            else idsuiv=312; break;
        case 311 : texte = "Vale, dame 10 rupias y te autorizo el acceso a la mina. Ok ?*              si              NO ?"; break;
        case 312 : texte = "Trato hecho, ve a hablar al guardia, te dejar� pasar..."; break;
        case 313 : texte = "Un coraz�n por 5 rupias, vale ?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getVie() == gpJeu->getJoueur()->getVieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<5) idsuiv=44; break;
        case 314 : texte = "Un coraz�n por 5 rupias, vale ?**             si              NO ?"; break;
        case 315 : texte = "No necesitas esto ahora."; break;
        case 316 : texte = "Un peque�o frasco de magia por 15 rupias, vale?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<15) idsuiv=44; break;
        case 317 : texte = "Un peque�o frasco de magia por 15 rupias, vale?**              si              NO ?"; break;
        case 318 : texte = "Un grande frasco de magia por 25 rupias, vale?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getMagie() == gpJeu->getJoueur()->getMagieMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<25) idsuiv=44; break;
        case 319 : texte = "Un grande frasco de magia por 25 rupias, vale?**              si              NO ?"; break;
        case 320 : texte = "Elige lo que quieras.*"; break;
        case 321 : texte = "10 flechas por 20 rupias, vale ?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getFleche() == gpJeu->getJoueur()->getFlecheMax()
            || !gpJeu->getJoueur()->hasObjet(O_ARC)) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<20) idsuiv=44; break;
        case 322 : texte = "10 flechas por 20 rupias, vale ?**              si             NO ?"; break;
        case 323 : texte = "5 bombas por 30 rupias, vale ?**              SI ?            no  ";
            if (!gpJeu->getJoueur()->hasObjet(O_SAC_BOMBES)) {id=325; chercheText(); break;}
            else if (gpJeu->getJoueur()->getBombe() == gpJeu->getJoueur()->getBombeMax()) {id=315; chercheText(); break;}
            else if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<30) idsuiv=44; break;
        case 324 : texte = "5 bombas por 30 rupias, vale ?**              si              NO ?"; break;
        case 325 : texte = "Necesitas un bolso de bombas para comprar esto."; break;
        case 326 : texte = "Vuelve cuando tengas una botella vac�a y te vender� p�cimas."; break;
        case 327 : texte = "Las p�cimas rojas devuelven energ�a mientras que las p�cimas verdes rellenan magia."; 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            idsuiv=328; break;
        case 328 : texte = "Que quieres ?*                ? POCIMA ROJA  ?*                ? p�cima verde ?*                ?     nada     ?"; idsuiv=331; break;
        case 329 : texte = "Que quieres ?*                ? p�cima roja  ?*                ? POCIMA VERDE ?*                ?     nada     ?"; 
            if (!gpJeu->getJoueur()->hasObjet(O_LANTERNE)) idsuiv=315;
            idsuiv=333; break;
        case 330 : texte = "Que quieres ?*                ? p�cima roja  ?*                ? p�cima verde ?*                ?     NADA     ?"; break;
        case 331 : texte = "Una p�cima roja por 60 rubis ?**              SI ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<60) idsuiv=44; break;
        case 332 : texte = "Una p�cima roja por 60 rubis ?**              si              NO ?"; break;
        case 333 : texte = "Una p�cima verde por 40 rubis ?**              SI ?            no  ";
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<40) idsuiv=44; break;
        case 334 : texte = "Una p�cima verde por 40 rubis ?**              si              NO ?"; break;
        case 335 : texte = "Has encontrado una p�cima roja !!!**B�bela para restaurar toda tu energ�a !!!"; break;
        case 336 : texte = "Has encontrado una p�cima verde !!!**B�bela para restaurar toda tu magia!!!"; break;
        case 337 : texte = "Has encontrado una p�cima azul !!!**B�bela para restaurar tu energ�a y tu magia!!!"; break;
        case 338 : texte = "ME ACOJO ENSAGRADO !!!!!!!!"; break;
        case 339 : texte = "Ah tu tambi�n... las gallinas ? Hic!*Terribles estos bichos verdad ?... Hic!"; break;
        case 340 : 
            if (gpJeu->getJoueur()->getAsile()==2) {id=339; chercheText(); break;}
            if (gpJeu->getJoueur()->hasCristal(3)) {id=341; chercheText(); break;}
            texte = "Era pescador hace tiempo... Hic!*Pero desde que LO vi... Hic!*Este terrible monstruo... Hic!*En el lago... Hic!"; break;
        case 341 : texte = "Has vencido el monstruo del lago ???*... ... ...*De todos modos temo el agua... Hic!*(prefiero el vino) Hic!"; break;
        case 342 : texte = "Ja! Ja! Ja!"; break;
        case 343 : 
            if (gpJeu->getJoueur()->getAvancement()==11) {id=344; chercheText(); break;}
            if (gpJeu->getJoueur()->getAsile()==3) {id=347; chercheText(); break;}
            if (gpJeu->getJoueur()->getRaplaplat()) {id=348; chercheText(); break;}
            texte = "Hola! Yo s� todo sobre lo que se dice en la ciudad, ven a verme si necesitas informaciones."; break;
        case 344 : 
            if (gpJeu->getJoueur()->getAvancement()!=11) {id=343; chercheText(); break;}
            texte = "Quieres saber porque el alcalde es tan silencioso ?*Vale, pero no te he dicho nada, ok ?"; idsuiv=345; break;
        case 345 : texte = "Este ciudad tiene un horrible secreto...*Cada noche, chicas son raptadas, y nunca les vemos de nuevo. Ni siquiera me atrevo a ir a pasear..."; idsuiv=346; break;
        case 346 : texte = "La noche pasada, seg�n los rumores, ser�a la hija del alcalde quien habr�a desaparecido..."; break;
        case 347 : 
            if (gpJeu->getJoueur()->getRaplaplat()) idsuiv=348;
            texte = "Hola, Se�or-que-teme-las-gallinas!*Ji! Ji! Ji!"; break;
        case 348 : texte = "Se dice que habr�as escalado el monte Planito ? Felicitaciones! Ji! Ji! Ji!"; break;
        case 349 : 
            if (gpJeu->getJoueur()->getAvancement()==13) {id=50; chercheText(); break;}
            texte = "Es... estas al corriente por mi hija ?*Es horrible... Mi querida hija..."; idsuiv=350;break;
        case 350 : texte = "Seg�n la investigaci�n que llevo desde el principio de estos acontecimientos, las chicas raptadas son llevadas en la casa antigua al Norte de la ciudad..."; idsuiv=351; break;
        case 351 : texte = "Ya he mandado la guardia ah�, pero nadie volvi�..."; idsuiv=352; break;
        case 352 : texte = "Entonces esta ma�ana, cuando descubr� que mi hija ya no estaba aqu�, supliqu� mi secuaz de ir a buscarla... Es un combatiente excepcional, pero es anormalmente lento..."; idsuiv=353; break;
        case 353 : texte = "Pareces un combatiente tambi�n, puedes ir a ver lo qu� ocurre ah� ?*Ser�s muy bien recompensado si salvas a mi hija."; idsuiv=354; break;
        case 354 : texte = "Vete al guardia al Noroeste de la ciudad, te dejar� pasar."; break;
        case 355 : 
            if (gpJeu->getJoueur()->hasMelodie(1)) {id=358; chercheText(); break;}
            texte = "Mi hija me ha contado todo, te debo much�simo!!!"; idsuiv=356; break;
        case 356 : texte = "Esc�chame atentamente, voy a aprenderte un canto que se transmite en mi familia de generaci�n en generaci�n :*La Eleg�a al Vac�o"; break;
        case 357 : texte = "Has aprendido la Eleg�a al Vac�o!!!**Utiliza el Ocarina para tocarla !"; break;
        case 358 : texte = "La Eleg�a al Vac�o tiene misteriosos poderes...*...Creo."; break;
        case 359 : texte = "Buenos d�as se�or-mi-salvador!"; break;
        case 360 : 
            if (gpJeu->getJoueur()->hasBouteille(0)!=1 
            && gpJeu->getJoueur()->hasBouteille(1)!=1
            && gpJeu->getJoueur()->hasBouteille(2)!=1) {id=326; chercheText(); break;}
            texte = "Una p�cima azul por 160 rupias ?*No te decepcionar�...*              SI ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<160) idsuiv=44; break;
        case 361 : texte = "Una p�cima azul por 160 rupias ?*No te decepcionar�...*              si              NO ?"; break;
        case 362 : 
            if (gpJeu->getJoueur()->hasObjet(O_GRAPPIN)) {id=364; chercheText(); break;}
            texte = "Hola, no solemos ver a un monstruo tan poderoso en el pueblo, es un gran honor..."; idsuiv=363; break;
        case 363 : texte = "Deber�as ir a divertirte en el coliseo al suroeste del pueblo, hay un precio interesante que ganar..."; break;
        case 364 : texte = "Has ganado el precio del Coliseo ? *Impresionante..."; break;
        case 365 : texte = "Si crees que eres el monstruo el m�s aterrador de Termina, es que tomas tus sue�os por la realidad pobre amigo m�o..."; idsuiv=366; break;
        case 366 : texte = "Palabra de honor, el monstruo del lago es con diferencia el m�s terror�fico de los monstruos, sobre todo te aconsejo que no procures enfrentarte a el."; break;
        case 367 : texte = "El coliseo al sur de aqu� es el principal divertimiento del pueblo.*El objetivo es de ir lo m�s lejos que puedes antes de ser matado."; idsuiv=368; break;
        case 368 : texte = "Pero es siempre muy dif�cil de encontrar a voluntarios, entonces el jefe fue obligado de poner dentro un objeto de gran valor."; break;
        case 369 : 
            texte = "Quieres escuchar mi historia por 10 rupias ?**              SI ?            no  "; 
            if (gpJeu->getJoueur()->getRubis() + gpJeu->getJoueur()->getBoostRubis()<10) idsuiv=44; break;
        case 370 : texte = "Quieres escuchar mi historia por 10 rupias ?**              si              NO ?"; break;
        case 371 : texte = "Seg�n el jefe, al Norte de aqu� est� el templo de Xanto, tambi�n conocido bajo el nombre del templo de los muertos..."; idsuiv=372; break;
        case 372 : texte = "Este templo seria un paso del mundo de los vivos hasta el mundo de los muertos... Pero para ir al mundo de los muertos, hay que atravesar un laberinto infranqueable..."; idsuiv=373; break;
        case 373 : texte = "P�game otra vez si quieres que repita."; break;
        case 374 : 
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==1) {id=376; chercheText(); break;}
            if (gpJeu->getJoueur()->hasObjet(O_MASQUE)==2) {id=380; chercheText(); break;}
            texte = "Estas buscando la M�scara del Esp�ritu ?*... F�jate..."; idsuiv=375; break;
        case 375 : texte = "No, no s� donde est�, pero s� como utilizarla.*Vuelve a verme si lo encuentras y podr� ayudarte."; break;
        case 376 : 
            if (gpJeu->getJoueur()->hasMelodie(2)) {id=379; chercheText(); break;}
            texte = "Has encontrado la M�scara del Esp�ritu ??? *...*Entonces esc�chame bien, voy a aprenderte como utilizarla."; idsuiv=377; break;
        case 377 : texte = "En presencia de un esp�ritu debilitado, tendr�s que tocar la Canci�n del Esp�ritu con tu ocarina.*Escucha la Canci�n del Esp�ritu!"; break;
        case 378 : texte = "Has aprendido la Canci�n del Esp�ritu!!! **Utiliza el Ocarina para tocarla!"; break;
        case 379 : texte = "La M�scara del Esp�ritu solo puede servir una vez, utilizala adecuadamente..."; break;
        case 380 : texte = "Has encerrado un esp�ritu terriblemente poderoso...*Cuidado que no caiga en malas manos..."; break;
        case 381 : texte = "Nuestro pueblo alberga pocas veces visitantes...*A lo mejor es porque bloqueamos la entrada..."; break;
        case 382 : 
            if (gpJeu->getJoueur()->hasObjet(O_BFEU)) {id=386; chercheText(); break;}
            if (gpJeu->getJoueur()->getAvancement()==66) {id=385; chercheText(); break;}
            texte = "Eres el �nico visitante que he tenido desde que vivo aqu�...*Soy un ex aventurero, era muy listo como buscador de tesoro..."; idsuiv=383;break;
        case 383 : texte = "Un d�a o� la historia del tesoro de la pir�mide, un objeto m�gico...*Pero este desierto caus� mi ruina, nunca pude atravesarlo, es demasiado peligroso..."; idsuiv=384; break;
        case 384 : texte = "Pareces tan decidido como yo en mi juventud... Te propongo un trato..."; idsuiv=385; break;
        case 385 : texte = "Tr�eme el tesoro de la pir�mide, y te ofrecer� mi tesoro el m�s precioso."; break;
        case 386 : 
            if (gpJeu->getJoueur()->hasMelodie(0)) {id=389; chercheText(); break;}
            texte = "Has encontrado el tesoro ???*Una varilla de fuego ?*...*..."; idsuiv=387; break;
        case 387 : texte = "Vale... Esta varilla te ser� mucho m�s �til que a mi...*Puedes conservarla...*"; idsuiv=388; break;
        case 388 : texte = "Acepta esta recompensa por haber ense�ado a un hombre viejo el tesoro que busc� toda su vida...*La Canci�n de Vuelo!!!"; break;
        case 389 : texte = "Tocada con un instrumento m�gico, esta canci�n te teletransporta. Esperaba que me permitir�a atravesar el desierto, pero nunca encontr� el instrumento adecuado..."; break;
        case 390 : texte = "Has aprendido la Canci�n de Vuelo!!!**Utiliza el Ocarina para tocarla!"; break;
        case 391 : texte = "Link! Soy Pit!!!*Que estas haciendo ???*Date prisa de ir a la finca oeste !!!"; break;
        case 392 : texte = "Link, soy Zelda, felicitaciones!!!*Rauru est� en seguridad, por un rato...*Va a la Torre del Destino  en la cumbre de la monta�a y para a Ganon!"; break;
        case 393 : texte = "Tutorial : cuando el indicador de nivel de ira est� lleno, te transformas en Oni-Link.*Tu alcance y tu fuerza aumentan mientras que tu defensa disminuye."; idsuiv=394; break;
        case 394 : texte = "En Oni-Link, no puedes utilizar los objetos equipables, pero puedes teletransportarte en la entrada cuando estas en un calabozo pulsando L y R."; idsuiv=395; break;
        case 395 : texte = "Por cada enemigo vencido por Oni-Link, tu indicador de nivel disminuye. Cuando est� vac�o, Link recupera su forma inicial."; break;
        case 396 : texte = "Jefe de proyecto, dise�ador y programador :                                                                  Vincent Jouillat"; break;
        case 397 : texte = "Guionista y traductora :                                                                                         Lobaluz"; break;
        case 398 : texte = "Ayuda con los Grafismos :                                                                                      Harvestland"; break;
        case 399 : texte = "Ayuda con los Grafismos :                                                                                    Sol�ne Jouillat"; break;
        case 400 : texte = "Ilustrador :                                                                                                      Raiden"; break;
        case 401 : texte = "Has encontrado el mapa de Termina !!!**Pulsa START cuando estas fuera para mirarlo."; break;
        case 402 : texte = "La leyenda olvida que despu�s de estos acontecimientos su h�roe fue presa de una terrible maldici�n..."; idsuiv=403; break;
        case 403 : texte = "D�a a d�a, Link se transformaba en un monstruo con un poder destructor incontrolable nombrado Oni-Link..."; idsuiv=404; break;
        case 404 : texte = "Exiliado de Hyrule, Link pidi� consejo a la Princesa Zelda."; idsuiv=405; break;
        case 405 : texte = "Ella le indic� su ultima esperanza : un portal hasta un mondo secreto..."; break;
        case 406 : texte = "Juego gravado."; break;
        case 407 : texte = "No necesitas beber esta p�cima ahora."; break;
        case 408 : texte = "AYUDA : Pulsa L y Y para consultar la ayuda."; break;
        case 409 : texte = "Grrrr... Como has podido escaparte del mundo de los muertos y llegar aqu� ???"; idsuiv=410; break;
        case 410 : texte = "Porque te empe�as en venir a enfrentarme ? *Aunque me venzas siempre resucitar�."; idsuiv=411; break;
        case 411 : texte = "Tu b�squeda es vana, abandona toda esperanza! **Let's rock, baby!"; break;
    }
	break; //Spanish

default:	
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
        case 7 : texte = "You find Pegasus Boots!!! *Hold R to run."; break;
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
        case 103 : texte = "Tip : Hold L to look around with the keyboard arrows."; break;
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
        case 131 : texte = "You find a sword!!!**Press B to attack or hold B to charg a spin attack."; break;
        case 132 : texte = "You find the Map!!!*Press START to see the map of the Dungeon."; break;
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
        case 146 : texte = "You find the Bomb Bag!!!*And it's full!!!*Press Y to put one down."; break;
        case 147 : texte = "You find the Gloves!!!**Now you can lift light stones by pressing X."; break;
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
        
        case 197 : texte = "Tutorial : Press A to talk, read, open a chest, or to pass the texts on the screen on."; break;
        case 198 : texte = "Press X to lift a light object."; break;
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
        case 240 : texte = "You find the Golden Gloves!!!**Now you can lift heavy stones pressing X."; break;
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
        case 273 : texte = "There is no time to loose!*Go immediately to the West Field to intercept Ganon's army!"; break;
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
        case 289 : texte = "You just have to beat a new enemy to add him in the encyclopedia.*You can see it by pressing L + B!"; break;
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
        case 368 : texte = "But it's always very difficult to find volunteers, so the chief was obligated to put a very high valued object inside."; break;
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
        case 394 : texte = "As Oni-Link, you cannot use objects, but you can teleport yourself to the entry when you are in a dungeon by pressing L + R."; idsuiv=395; break;
        case 395 : texte = "Each time Oni-Link defeats an enemy, your gauge decreases. When it's empty, Link regain his normal form."; break;
        case 396 : texte = "Team leader, creator and programmer :                                                                         Vincent Jouillat"; break;
        case 397 : texte = "Scriptwriter and translator:                                                                                      Lobaluz"; break;
        case 398 : texte = "Help to the Graphics :                                                                                          Harvestland"; break;
        case 399 : texte = "Help to the Graphics :                                                                                        Sol�ne Jouillat"; break;
        case 400 : texte = "Illustrator :                                                                                                      Raiden"; break;
        case 401 : texte = "You find the Termina map!!!**Press START when you are outside to see it."; break;
        case 402 : texte = "The legend forgets that after these events, the hero was brought down by a terrible curse..."; idsuiv=403; break;
        case 403 : texte = "Day by day, Link was transforming into an incontrollable and destructive powered monster named Oni-Link..."; idsuiv=404; break;
        case 404 : texte = "Banished from Hyrule, Link asked for advice from Princess Zelda."; idsuiv=405; break;
        case 405 : texte = "She indicated to him his last hope : a portal to a secret world..."; break;
        case 406 : texte = "Game saved."; break;
        case 407 : texte = "You don't need to drink this potion now."; break;
        case 408 : texte = "HELP : Press L + Y to see the help."; break;
        case 409 : texte = "Grrrr... But how could you escape from the world of the deads and arrive here???"; idsuiv=410; break;
        case 410 : texte = "Why do you persist to challenge me? *Even if you strike me down I will always return to life."; idsuiv=411; break;
        case 411 : texte = "Your quest is vain, abandon all hope! **Let's rock, baby!"; break;
    }
	break; // default language : English
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

	std::string comptexte;
	
switch(getLanguage()) {

case 2: // French
	comptexte = "Tu as trouv� un quart de coeur !!!";
break;

/*
case 3: // German
	comptexte = "Du hast ein Herzfragment gefunden!!!";
break;

case 4: // Italian
	comptexte = "Hai trovato una parte di cuore !!!";
break;
*/
case 5: // Spanish
	comptexte = "Has encontrado un cuarto de coraz�n !!!";
break;

default:
	comptexte = "You found a piece of heart!!!";
break;	
}    
//    if (id==3 && texte == "You find a piece of heart!!!") {
    if (id==3 && texte == comptexte) {
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
    //compte le nombre de caract�res possibles et largeur et en hauteur
    int nbcol = (w-16)/6 -1;
    int nblig = (h-16)/16;
    int tailleMax = nbcol * nblig;
    int taille;
    
    //parcours du texte � afficher; � chaque d�but de mot, 
    //v�rifie que le mot peut tenir sur la ligne
    for (int i = 0; i < (int)texte.length(); i++) {
        
        //supprime les espaces isol�s en d�but de ligne
        if (texte.at(i)==' ' && texte.at(i+1)!=' ' && i%nbcol == 0) texte.erase(i,1);
        //recherche du d�but du prochain mot
        while(texte.at(i)==' ' && i < (int)texte.length()-1) i++;
        
        //saute une ligne si trouve une �toile
        if (texte.at(i)=='*') {
            texte.erase(i,1);//replace(i, 1, " ");
            int nb = (nbcol)-(i%(nbcol));
            for (int j = 0; j < nb; j++) texte.insert(i," ");
            continue;
        }
        
        //si le mot d�passe
        taille = tailleMot(i);
        if ((i%nbcol)+taille>nbcol) {
            if  (i < tailleMax) {
                //si le mot ne tient pas sur une ligne, on le coupe avec des tirets
                if (taille>nbcol) {
                    texte.insert(((i/nbcol)+1)*nbcol-1,"--");
                    i = 1+((i/nbcol)+1)*nbcol;
                }
                //sinon, on ajoute des espaces pour faire commencer le mot � la ligne
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
    // �
    if(val=='�') {src.x=164;src.y=68;}
    // �
    if(val=='�') {src.x=164;src.y=103;}
    // �
    if(val=='�') {src.x=164;src.y=52;}
    // �
    if(val=='�') {src.x=164;src.y=84;}
    // �
    if(val=='�') {src.x=164;src.y=151;}
    
	// de
    // �
    if(val=='�') {src.x=6+16*3; src.y=167;}
    
    // �
    if(val=='�') {src.x=6; src.y=167;}
    
    // �
    if(val=='�') {src.x=6+16; src.y=167;}
    
    // �
    if(val=='�') {src.x=6+16*2; src.y=167;}
    

    // it
    // �
    if(val=='�') {src.x=164;src.y=36;}
    // �
    if(val=='�') {src.x=164;src.y=119;}
 

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
    // �
    if(val=='�') {src.x=148;src.y=34;}
    // �
    if(val=='�') {src.x=100;src.y=84;}
    // �
    if(val=='�') {src.x=116;src.y=84;}
    // �
    if(val=='�') {src.x=132;src.y=84;}
    // �
    if(val=='�') {src.x=132;src.y=151;}
    // �
    if(val=='�') {src.x=148;src.y=84;}
    // �
    if(val=='�') {src.x=148;src.y=103;}
    // �
    if(val=='�') {src.x=148;src.y=135;}
    // �
    if(val=='�') {src.x=84;src.y=119;}
    // �
    if(val=='�') {src.x=116;src.y=151;}
    // �
    if(val=='�') {src.x=84;src.y=103;}
    // u
    if(val==-'u') {src.x=148;src.y=151;}
    // �
    if(val=='�') {src.x=116;src.y=135;}
    // �
    if(val=='�') {src.x=132;src.y=135;}
    // �
    if(val=='�') {src.x=148;src.y=119;}
            
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
