#include <stdio.h>
#include <stdlib.h>
#ifndef fonctions_h
#define fonctions_h

//Signatures et prototypes des procédures et des fonctions du programme.

/*Auteur : De Morais Théo
Date : 12/01/23
Résumé : structure d'une station.
Entré(s) : aucune.
Sortie(s) : aucune. */
typedef struct station {
  
  int id; //identifiant de la station.
  float longit; //longitude de la station.
  float lat; //latitude de la station.
  float alt; //altitude de la station.
  float temp; //température de la station.
  int nbTemp; //nombre de températures de la station.
  float tempMoy; //température moyenne de la station.
  float tempMax; //température max de la station.
  float tempMin; //température min de la station.
  float press; //pression de la station.
  int nbPress; //nombre de pressions de la station.
  float pressMoy; //pression moyenne de la station.
  float pressMax; //pression max de la station.
  float pressMin; //pression min de la station.
  int hum; //humidité de la station.
  int humMax; //humidité max de la station.
  int heure; //heure de la station.
  int annee; //annee de la station.
  int mois; //mois de la station.
  int jour; //jour de la station.
  int fuseauH; //fuseau horaire de la station.
  int longID; //nombre de chiffre de l'identifiant de la station.
  int longJ; //nombre de chiffre du jour de la station.
  int longM; //nombre de chiffre du mois de la station.
  int dirVent; //direction du vent de la station.
  float vitVent; //vitesse du vent de la station.
  //Liste donneesL;
  
}station;

/*Auteur : De Morais Théo
Date : 18/12/22
Résumé : Procédure permettant, lors de son appel, d'afficher l'aide sur toutes les options utilisables du programme.
Entré(s) : aucune.
Sortie(s) : aucune. */
void afficheAide();

/*Auteur : De Morais Théo
Date : 13/01/23
Résumé : Fonction permettant, lors de son appel, de comparer 2 identifiants dans le but de trier le tableau avec la fonction qsort().
Entré(s) : Les 2 identifiants à comparer sous forme de pointeurs génériques pouvant pointer vers n'importe quel type de données et ces données ne doivent pas être modifiées.
Sortie(s) : retourne 1 si le résultat de la différence entre les 2 identifiants est positif, retourne -1 sinon ou retourne 0 si le résultat est nul. */
int compareID(const void *ID1, const void *ID2);

/*Auteur : De Morais Théo
Date : 13/01/23
Résumé : Fonction permettant, lors de son appel, de comparer 2 valeurs d'humidité dans le but de trier le tableau avec la fonction qsort().
Entré(s) : Les 2 valeurs d'humidité à comparer sous forme de pointeurs génériques pouvant pointer vers n'importe quel type de données et ces données ne doivent pas être modifiées.
Sortie(s) : retourne 1 si le résultat de la différence entre les 2 valeurs d'humidités est positif, retourne -1 sinon ou retourne 0 si le résultat est nul. */
int compareHum(const void *Hum1, const void *Hum2);

/*Auteur : De Morais Théo
Date : 13/01/23
Résumé : Fonction permettant, lors de son appel, de comparer 2 valeurs d'altitude dans le but de trier le tableau avec la fonction qsort().
Entré(s) : Les 2 valeurs d'altitude à comparer sous forme de pointeurs génériques pouvant pointer vers n'importe quel type de données et ces données ne doivent pas être modifiées.
Sortie(s) : retourne 1 si le résultat de la différence entre les 2 valeurs d'altitude est positif, retourne -1 sinon ou retourne 0 si le résultat est nul. */
int compareAlt(const void *Alt1, const void *Alt2);

/*Auteur : De Morais Théo
Date : 13/01/23
Résumé : Fonction permettant, lors de son appel, de produire l'humidité maximale de chaque station et de les écrire dans un fichier de sortie par ordre décroissant.
Entré(s) : le fichier d'entrée à analyser de type FILE*, le nom du fichier de sortie de type char*.
Sortie(s) : aucune. */
void hum(FILE* fichierEntree);

/*Auteur : De Morais Théo
Date : 13/01/23
Résumé : Fonction permettant, lors de son appel, de produire la hauteur de chaque station et de les écrire dans un fichier de sortie par ordre décroissant.
Entré(s) : le fichier d'entrée à analyser de type FILE*, le nom du fichier de sortie de type char*.
Sortie(s) : aucune. */
void alt(FILE* fichierEntree);

/*Auteur : De Morais Théo
Date : 14/01/23
Résumé : Fonction permettant, lors de son appel, de produire les températures minimales, maximales et moyennes de chaque station et de les écrire dans un fichier de sortie par ordre croissant d'identifiant de station.
Entré(s) : le fichier d'entrée à analyser de type FILE*, le nom du fichier de sortie de type char*.
Sortie(s) : aucune. */
void tempMode1(FILE* fichierEntree);

/*Auteur : De Morais Théo
Date : 14/01/23
Résumé : Fonction permettant, lors de son appel, de produire les pressions minimales, maximales et moyennes de chaque station et de les écrire dans un fichier de sortie par ordre croissant d'identifiant de station.
Entré(s) : le fichier d'entrée à analyser de type FILE*, le nom du fichier de sortie de type char*.
Sortie(s) : aucune. */
void pressMode1(FILE* fichierEntree);

#endif
