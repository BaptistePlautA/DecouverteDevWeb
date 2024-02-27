#include "fonctions.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#define N 2200000
#define MAX_STATIONS 62 //Il y a 62 stations différentes dans le tableau.

//////////Traces de notre travail sur les arbres et les listes qui n'a pas pu être abouti//////////

/*
// Fonction pour créer un nouveau noeud
Arbre nouveauNoeud(int id, float longit, float lat, float alt) {
	
  Arbre noeudA = malloc(1000*sizeof(Arbre));
  noeudA->donnee->id = id;
  noeudA->donnee->longit = longit;
  noeudA->donnee->lat = lat;
  noeudA->gauche = NULL;
  noeudA->droit = NULL;
  return noeudA;
}

//Fonction permettant de créer un maillon
Liste creerMaillon(char* date, float press, int hum, float temp) {
	
	maillon* m;
	
	m = malloc(sizeof(maillon)*100);
	m->date = date;
	m->press = press;
	m->hum = hum;
	m->temp = temp;
	m->suivant = NULL;
	
	return m;
	
}

// Fonction pour insérer un nouveau noeud dans l'abr
Arbre inserer(Arbre noeudA, int id, float longit, float lat, float alt) {
	
	// 1. insertion abr classique
	if (noeudA == NULL){
		return nouveauNoeud(id, longit, lat, alt);
	}
	else if (id < (noeudA->donnee->id)){
		noeudA->gauche = inserer(noeudA->gauche, id, longit, lat, alt);
	}
	else if (id > (noeudA->donnee->id)){
		noeudA->droit = inserer(noeudA->droit, id, longit, lat, alt);
	}
	// 2. Retourner le noeud racine
	return noeudA;
}

// Procédure récursive pour afficher l'arbre ABR en infixe
void afficherArbre(Arbre noeudA) {
  if (noeudA == NULL) {
    return;
  }
  afficherArbre(noeudA->gauche);
  printf("%d ", noeudA->donnee->id);
  afficherArbre(noeudA->droit);
}

// Procédure pour afficher l'arbre ABR dans le terminal
void afficherArbreTerminal(Arbre noeudA, int niveau) {
  if (noeudA == NULL) {
    return;
  }
  afficherArbreTerminal(noeudA->droit, niveau + 1);
  for (int i = 0; i < niveau; i++) {
    printf("    ");
  }
  printf(" %d \n", noeudA->donnee->id);
  afficherArbreTerminal(noeudA->gauche, niveau + 1);
}

// Procédure pour vider l'arbre ABR
void libererArbre(Arbre a) {
	
	if (a==NULL) { 
    return;
  }
	
  free(a);
	libererArbre(a->gauche);
	libererArbre(a->droit);

}

// Fonction qui vérifie si un identifiant est déja présent dans l'ABR
int existenceID(int id, Arbre a, int estID) {

  if(a!=NULL) {

    if(id==(a->donnee->id)) {
      estID=1;
    }
    return existenceID(id, a->gauche, estID);
    return existenceID(id, a->droit, estID);
  }
  return estID;
}

// Fonction permettant de lire un fichier d'entrée
Arbre lireFichier(FILE* fichierEntree, Arbre a) {
	
	char ligne[N];
	int ligne1=1;
	int t;
	char* ligneCopie=NULL;
	char* lignePartie = NULL; //Pour séparer la ligne en plusieurs parties.
	int id;
  int estID=0; //Pour vérifier si la station existe déja dans le tableau crée.
	float longit;
	float lat;
	float alt;
		  
	while (fgets(ligne, N, fichierEntree)) { 
				
		if(ligne1==0) { //Si on est pas à la 1ère ligne pour ne pas analyser la première ligne.
					
			t=0;
			ligneCopie = strdup(ligne); //On copie la ligne en question.
					
			while((lignePartie = strsep(&ligneCopie, ";")) != NULL) {
						
				if(t==0) {
							
					id = atoi(lignePartie);
							
				}else if(t==9) {
				
					sscanf(lignePartie, "%f,%f", &lat, &longit);
					
				}else if(t==13) {
				
					alt = atof(lignePartie);
					
				}
				
        estID = existenceID(id, a, estID); //Pour ne pas ajouter plusieurs fois la même id.

        if(estID==0) {

          a = inserer(a, id, longit, lat, alt);

        }
						
				t++; //Colonne suivante.
			}
					
			free(ligneCopie);	
		}
				 
		ligne1 = 0; //On est plus à la ligne 1. Pour pouvoir analyser à partier de la ligne 2 du tableau.
	}

  return a;
}

*/

//////////Fonctions et procédures utilisés dans notre programme//////////

// Procédure permettant, lors de son appel, d'afficher l'aide sur toutes les options utilisables du programme.
void afficheAide() {

    printf("\n---------- Manuel sur les commandes utilisables ----------\n\n");
    printf("La syntaxe est la suivante : ./<executable> <option> (possibilité de mettre plusieurs options de suite pour certaines options)\n\n");
    printf("OPTIONS :\n\n");
    printf("--help : affiche une aide sur toutes les options utilisables.\n");
    printf("-i <nom_fichier> : Permet de specifier le chemin du fichier CSV d'entrée. Cette option est obligatoire et nécessite l'utilisation d'une autre option afin de traiter le fichier.\n");
    printf("-o <nom_fichier> : Permet de donner un nom au fichier de sortie contenant les données. Si les options utilisées nécessitent plusieurs fichiers, cet argument peut servir à definir le préfixe des fichiers de sortie.\n");
    printf("\nLes options suivantes sont exclusives. \nPlus précisement, si l'une d'elle est présente, les autres ne doivent pas l'être. En même temps, il faut que l'une d'entre elles soit absolument utilisée :\n");
    printf("    -w : Produit en sortie l'orientation moyenne et la vitesse moyenne des vents pour chaque station. Les données seront triées par identifiant croissant de la station.\n");
    printf("    -h : Produit en sortie la hauteur pour chaque station. Les hauteurs seront triées par ordre décroissant.\n");
   	printf("    -m : Produit en sortie l'humidité maximale pour chaque station. Les valeurs d'humidités seront triées par ordre décroissant.\n");
    printf("    -t <mode> : Températures.\n");
    printf("    -p <mode> : Pressions atmosphériques.\n");
    printf("    Pour ces 2 options, il faut indiquer la valeur de <mode> :\n");
    printf("        1 : Produit en sortie les températures (ou pressions) minimales, maximales et moyennes par station par ordre croissant du numero de station.\n");
    printf("        2 : Produit en sortie les températures (ou pressions) moyennes par date/heure par ordre chronologique. La moyenne se fait sur toutes les stations.\n");
    printf("        3 : Produit en sortie les températures (ou pressions) par date/heure par station. Elles seront triées d'abord par ordre chronologique, puis par identifiant croissant de la station.\n");
}

// Fonction permettant, lors de son appel, de comparer 2 identifiants dans le but de trier le tableau avec la fonction qsort().
int compareID(const void *ID1, const void *ID2) { //Format des paramètres adapté pour la fonction qsort.
                                                  //Les pointeurs sont génériques et peuvent pointer vers n'importe quel type de données mais les données auxquelles ils pointent ne doivent pas être modifiées.
    //On convertit les pointeurs génériques en pointeur de structure station pour pouvoir comparer les identifiants.
    station* sID1 = (station*)ID1;
    station* sID2 = (station*)ID2; 

    return (sID1->id - sID2->id);  //Par ordre croissant d'identifiant.
}

// Fonction permettant, lors de son appel, de comparer 2 valeurs d'humidité dans le but de trier le tableau avec la fonction qsort().
int compareHum(const void *Hum1, const void *Hum2) { //Format des paramètres adapté pour la fonction qsort.
                                                  //Les pointeurs sont génériques et peuvent pointer vers n'importe quel type de données mais les données auxquelles ils pointent ne doivent pas être modifiées.
    //On convertit les pointeurs génériques en pointeur de structure station pour pouvoir comparer les humidités.
    station* sHum1 = (station*)Hum1;
    station* sHum2 = (station*)Hum2; 

    return (sHum2->humMax - sHum1->humMax); //Par ordre décroissant d'humidité.
}

// Fonction permettant, lors de son appel, de comparer 2 valeurs d'altitude dans le but de trier le tableau avec la fonction qsort().
int compareAlt(const void *Alt1, const void *Alt2) { //Format des paramètres adapté pour la fonction qsort.
                                                  //Les pointeurs sont génériques et peuvent pointer vers n'importe quel type de données mais les données auxquelles ils pointent ne doivent pas être modifiées.
    //On convertit les pointeurs génériques en pointeur de structure station pour pouvoir comparer les altitudes.
    station* sAlt1 = (station*)Alt1;
    station* sAlt2 = (station*)Alt2; 

    return (sAlt2->alt - sAlt1->alt);  //Par ordre décroissant d'altitude.
}

// Fonction permettant, lors de son appel, de produire la hauteur de chaque station et de les écrire dans un fichier de sortie par ordre décroissant.
void alt(FILE* fichierEntree) {

    FILE* fichierSortie = NULL; //On initialise le fichier de sortie.

    station tabStations[MAX_STATIONS]; //Tableau qui contiendra les 62 stations différentes.
    int nbStation = 0; //Servira à stocker le nombre de station.

    char ligne[N]; //Stocke les lignes du tableau csv.
    float alt; //L'altitude de la station.
    float longit, lat; //Pour stocker les coordonnées de la station.
    int annee, mois, jour; //Pour la date de la station.
    int id; //L'id de la station.
    int t; //Compteur qui définit le numéro de la colonne de la ligne stockée par ligne[N].
    int ligne1=1; //On suppose qu'on commence le tableau par la 1ère ligne. Cependant, elle ne nous intéresse pas.
  	char* ligneCopie=NULL; //Pour copier la ligne que l'on souhaite traiter.
	  char* lignePartie = NULL; //Pour séparer la ligne que l'on souhaite traiter en plusieurs parties.

    while (fgets(ligne, N, fichierEntree) != NULL) { //Traite chaque ligne du tableau csv.

      if(ligne1==0) { //Si on est pas à la 1ère ligne pour ne pas analyser la première ligne.

          int longID, longM, longJ; //Stocke le nombre de chiffre de l'identifiant, du mois et du jour de la station.
          char ids[5]; //Stocke les identifiants d'une station.  
          char m[2]; //Stocke les mois d'une station.
          char j[2]; //Stocke les jours d'une station.        
          t=0; //On commence à la première colonne de la ligne que l'on souhaite traiter.
          ligneCopie = strdup(ligne); //On copie la ligne en question.
                
          while((lignePartie = strsep(&ligneCopie, ";")) != NULL) { //On traite la ligne en question colonne par colonne. Les colonnes sont séparées par ";".
                  
            if(t==0) { //Si on est à la 1ère colonne.
                    
              id = atoi(lignePartie); //On prend l'id de la station.

              sprintf(ids, "%d", id); //On ajoute l'id de la station dans le tableau de station.
              longID = strlen(ids); //On utilise strlen pour avoir le nombre de chiffre de l'id de la station.
                    
            }else if(t==1) { //Si on est à la 2ème colonne.
					
					    sscanf(lignePartie, "%d-%d-%dT", &annee, &mois, &jour); //On prend la date de la station.

              sprintf(m, "%d", mois); //On ajoute le mois de la station dans le tableau de mois.
              longM = strlen(m); //On utilise strlen pour avoir le nombre de chiffre du mois de la station.

              sprintf(j, "%d", jour); //On ajoute le jour de la station dans le tableau de jour.
              longJ = strlen(j); //On utilise strlen pour avoir le nombre de chiffre du jour de la station.

				    }else if(t==9) { //Si on est à la 10ème colonne.
					
					    sscanf(lignePartie, "%f,%f", &longit, &lat); //On prend la longitude et la latitude.
					
				    }else if(t==13) { //Si on est à la 14ème colonne.
              
              alt = atof(lignePartie); //On prend l'altitude de la station.
  
            }
                       
            t++; //Colonne suivante.
          }	

          int station_index = -1; //On va chercher si la station existe déjà dans le tableau de station crée.

          for (int i = 0; i < nbStation; i++) { //On parcourt le tableau.
              if (tabStations[i].id == id) { //Si l'id de la station est déjà présente dans le tableau.
                  station_index = i; //alors on prend sa position dans le tableau.
                  break; //Comme on a trouvé que la station existait déjà, plus besoin de continuer et on sort de la boucle.
              }
          }

          if (station_index == -1) { //Si la station n'existe pas encore, on l'ajoute dans le tableau de station crée.
              station_index = nbStation; //Pour ajouter à la suite du tableau la nouvelle station.
              tabStations[station_index].id = id; //On ajoute l'id de la station.
              tabStations[station_index].alt = alt; //On ajoute l'altitude de la station.
              tabStations[station_index].longit = longit; //On ajoute la longitude de la station.
              tabStations[station_index].lat = lat; //On ajoute la latitude de la station.
              tabStations[station_index].annee = annee; //On ajoute l'année de la station.
              tabStations[station_index].mois = mois; //On ajoute le mois de la station.
              tabStations[station_index].jour = jour; //On ajoute le jour de la station.
              tabStations[station_index].longID = longID; //On ajoute la longueur de l'id de la station.
              tabStations[station_index].longM = longM; //On ajoute la longueur du mois de la station.
              tabStations[station_index].longJ = longJ; //On ajoute la longueur du jour de la station.
              nbStation++; //On a donc une station supplémentaire dans le tableau.
          }

      }//Fin ligne==0
        
      ligne1 = 0; //Comme on va passer à la ligne 2 du tableau, on pourra commencer à analyser le tableau. Pour cela, on met ligne1=0.  
  
    }//Fin du parcours des lignes du fichier csv.

    /*qsort(à trier, nb éléments, **, ***);
     **taille en octet de l'élément (d'où le sizeof pour avoir la taille de la structure station).
     ***pointeur vers une fonction de comparaison qui est utilisée pour déterminer l'ordre des éléments dans le tableau. */
    qsort(tabStations,nbStation, sizeof(station), compareAlt); //On trie les stations par altitude décroissante.

    fichierSortie = fopen("mesures.csv", "w"); //Pour écrire l'altitude de chaque station dans le fichier de sortie.

    //On écrit dans le fichier de sortie l'altitude de chaque station.
    for (int i = 0; i < nbStation; i++) { //On parcourt le tableau pour pouvoir écrire les différentes stations qui s'y trouvent dans le fichier de sortie.
        station current_station = tabStations[i]; //On initialise la station que l'on va écrire dans le fichier de sortie comme étant la station qui se trouve dans le tableau.

        //Pour chacune des conditions ci-dessous, si l'id de la station comporte 4 chiffres, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                                //si le mois de la station comporte 1 chiffre, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                                //si le jour de la station comporte 1 chiffre, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                                //sinon, on écrit l'id, le mois ou le jour sans le 0.

        if(current_station.longID==4 && current_station.longM==1 && current_station.longJ==1) { //Si l'id de la station comporte 4 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "0%d;%d-0%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.alt);
        }else if(current_station.longID==4 && current_station.longM==1 && current_station.longJ==2) { //Sinon si l'id de la station comporte 4 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 2 chiffres.
          fprintf(fichierSortie, "0%d;%d-0%d-%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.alt);
        }else if(current_station.longID==4 && current_station.longM==2 && current_station.longJ==1) { //Sinon si l'id de la station comporte 4 chiffres, le mois de la station comporte 2 chiffres et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "0%d;%d-%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.alt);
        }else if(current_station.longID==5 && current_station.longM==1 && current_station.longJ==1) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "%d;%d-0%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.alt);
        }else if(current_station.longID==5 && current_station.longM==1 && current_station.longJ==2) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 2 chiffres.
          fprintf(fichierSortie, "%d;%d-0%d-%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.alt);
        }else if(current_station.longID==5 && current_station.longM==2 && current_station.longJ==1) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 2 chiffres et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "%d;%d-%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.alt);
        }else { //Sinon c'est que l'id de la station comporte 5 chiffres, le mois de la station comporte 2 chiffres et que le jour de la station comporte 2 chiffres.
          fprintf(fichierSortie, "%d;%d-%d-%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.alt);
        }
    }

    fclose(fichierSortie); //On ferme le fichier de sortie.

}

// Fonction permettant, lors de son appel, de produire l'humidité maximale de chaque station et de les écrire dans un fichier de sortie par ordre décroissant.
void hum(FILE* fichierEntree){
	
  FILE* fichierSortie = NULL; //On initialise le fichier de sortie.

  station tabStations[MAX_STATIONS]; //Tableau qui contiendra les 62 stations différentes.
  int nbStation = 0; //Servira à stocker le nombre de station.

  char ligne[N]; //Stocke les lignes du tableau csv.
  int hum; //Une pression de la station.
  float longit, lat; //Pour stocker les coordonnées de la station.
  int annee, mois, jour; //Pour la date de la station.
  int id; //L'id de la station.
  int t; //Compteur qui définit le numéro de la colonne de la ligne stockée par ligne[N].
  int ligne1=1; //On suppose qu'on commence le tableau par la 1ère ligne. Cependant, elle ne nous intéresse pas.
	char* ligneCopie=NULL; //Pour copier la ligne que l'on souhaite traiter.
	char* lignePartie = NULL; //Pour séparer la ligne que l'on souhaite traiter en plusieurs parties.
  
	while (fgets(ligne, N, fichierEntree)) { 

		if(ligne1==0) { //Si on est pas à la 1ère ligne pour ne pas analyser la première ligne.
			
			t=0;
			ligneCopie = strdup(ligne); //On copie la ligne en question.
      int longID, longM, longJ; //Stocke le nombre de chiffre de l'identifiant, du mois et du jour de la station.
      char ids[5]; //Stocke les identifiants d'une station.  
      char m[2]; //Stocke les mois d'une station.
      char j[2]; //Stocke les jours d'une station.  

			while((lignePartie = strsep(&ligneCopie, ";")) != NULL) {
				
				if(t==0) { //Si on est à la 1ère colonne
					
					id = atoi(lignePartie); //On prend l'élément de la colonne et ça sera l'identifiant station à la 1ère colonne.

          sprintf(ids, "%d", id); //On ajoute l'id de la station dans le tableau de station.
          longID = strlen(ids);	//On utilise strlen pour avoir le nombre de chiffre de l'id de la station.

				}else if(t==1) { //Si on est à la 2e colonne.
                    
          sscanf(lignePartie, "%d-%d-%dT", &annee, &mois, &jour); //On prend la date de la station.

            sprintf(m, "%d", mois); //On ajoute le mois de la station dans le tableau de mois.
            longM = strlen(m); //On utilise strlen pour avoir le nombre de chiffre du mois de la station.
              
            sprintf(j, "%d", jour); //On ajoute le jour de la station dans le tableau de jour.
            longJ = strlen(j); //On utilise strlen pour avoir le nombre de chiffre du jour de la station.
    
        }else if(t==5) { //Si on est à la 6e colonne.
					
					hum = atoi(lignePartie); //On prend l'élément de la colonne et ça sera l'humidité à la colonne 6.
					
				}else if(t==9) { //Si on est à la 10e colonne.
					
					sscanf(lignePartie, "%f,%f", &longit, &lat); //On prend les coordonnées de la station.
					
				}
				
				t++; //Colonne suivante.
			}
			
			int station_index = -1; //On va chercher si la station existe déjà dans le tableau de station crée.

      for (int i = 0; i < nbStation; i++) { //On parcourt le tableau.
          if (tabStations[i].id == id) { //Si l'id de la station est déjà présente dans le tableau.
              station_index = i; //alors on prend sa position dans le tableau.
              break; //Comme on a trouvé que la station existait déjà, plus besoin de continuer et on sort de la boucle.
          }
      }

      if (station_index == -1) { //Si la station n'existe pas encore, on l'ajoute dans le tableau de station crée.
          station_index = nbStation; //Pour ajouter à la suite du tableau la nouvelle station.
          tabStations[station_index].id = id; //On ajoute l'id de la station.
          tabStations[station_index].humMax = hum; //On ajoute l'humidité de la station.
          tabStations[station_index].longit = longit; //On ajoute la longitude de la station.
          tabStations[station_index].lat = lat; //On ajoute la latitude de la station.
          tabStations[station_index].annee = annee; //On ajoute l'année de la station.
          tabStations[station_index].mois = mois; //On ajoute le mois de la station.
          tabStations[station_index].jour = jour; //On ajoute le jour de la station.
          tabStations[station_index].longID = longID; //On ajoute la longueur de l'id de la station.
          tabStations[station_index].longM = longM; //On ajoute la longueur du mois de la station.
          tabStations[station_index].longJ = longJ; //On ajoute la longueur du jour de la station.
          nbStation++; //On a donc une station supplémentaire dans le tableau.
      }

      if(hum>tabStations[station_index].humMax) {
        tabStations[station_index].humMax=hum;
      }	
	  } 
	  ligne1 = 0; //On est plus à la ligne 1. Pour pouvoir analyser à partier de la ligne 2 du tableau.
	
  }//Fin du parcours des lignes du fichier csv.

  /*qsort(à trier, nb éléments, **, ***);
   **taille en octet de l'élément (d'où le sizeof pour avoir la taille de la structure station).
   ***pointeur vers une fonction de comparaison qui est utilisée pour déterminer l'ordre des éléments dans le tableau. */
  qsort(tabStations,nbStation, sizeof(station), compareHum); //On trie les stations par humidité décroissante.

  fichierSortie = fopen("mesures.csv", "w"); //Pour écrire l'humidité des différentes stations dans le fichier de sortie.

  //On écrit l'humidité de chaque station dans le fichier de sortie.
  for (int i = 0; i < nbStation; i++) { //On parcourt le tableau pour pouvoir écrire les différentes stations qui s'y trouvent dans le fichier de sortie.
      station current_station = tabStations[i]; //On initialise la station que l'on va écrire dans le fichier de sortie comme étant la station qui se trouve dans le tableau.

      //Pour chacune des conditions ci-dessous, si l'id de la station comporte 4 chiffres, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                              //si le mois de la station comporte 1 chiffre, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                              //si le jour de la station comporte 1 chiffre, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                              //sinon, on écrit l'id, le mois ou le jour sans le 0.

      if(current_station.longID==4 && current_station.longM==1 && current_station.longJ==1) { //Si l'id de la station comporte 4 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 1 chiffre.
        fprintf(fichierSortie, "0%d;%d-0%d-0%d;%f;%f;%d\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.humMax);
      }else if(current_station.longID==4 && current_station.longM==1 && current_station.longJ==2) { //Sinon si l'id de la station comporte 4 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 2 chiffres.
        fprintf(fichierSortie, "0%d;%d-0%d-%d;%f;%f;%d\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.humMax);
      }else if(current_station.longID==4 && current_station.longM==2 && current_station.longJ==1) { //Sinon si l'id de la station comporte 4 chiffres, le mois de la station comporte 2 chiffres et le jour de la station comporte 1 chiffre.
        fprintf(fichierSortie, "0%d;%d-%d-0%d;%f;%f;%d\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.humMax);
      }else if(current_station.longID==5 && current_station.longM==1 && current_station.longJ==1) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 1 chiffre.
        fprintf(fichierSortie, "%d;%d-0%d-0%d;%f;%f;%d\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.humMax);
      }else if(current_station.longID==5 && current_station.longM==1 && current_station.longJ==2) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 2 chiffres.
        fprintf(fichierSortie, "%d;%d-0%d-%d;%f;%f;%d\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.humMax);
      }else if(current_station.longID==5 && current_station.longM==2 && current_station.longJ==1) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 2 chiffres et le jour de la station comporte 1 chiffre.
        fprintf(fichierSortie, "%d;%d-%d-0%d;%f;%f;%d\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.humMax);
      }else { //Sinon c'est que l'id de la station comporte 5 chiffres, le mois de la station comporte 2 chiffres et que le jour de la station comporte 2 chiffres.
        fprintf(fichierSortie, "%d;%d-%d-%d;%f;%f;%d\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.longit, current_station.lat, current_station.humMax);
      }
  }

  fclose(fichierSortie); //On ferme le fichier de sortie.
}

// Fonction permettant, lors de son appel, de produire les températures minimales, maximales et moyennes de chaque station et de les écrire dans un fichier de sortie par ordre croissant d'identifiant de station.
void tempMode1(FILE* fichierEntree) {

    FILE* fichierSortie = NULL; //On initialise le fichier de sortie.

    station tabStations[MAX_STATIONS]; //Tableau qui contiendra les 62 stations différentes.
    int nbStation = 0; //Servira à stocker le nombre de station.

    char ligne[N]; //Stocke les lignes du tableau csv.
    float temp; //Une température de la station.
    float tempMax; //La plus grande température d'une station.
    float tempMin; //La plus petite température d'une station.
    int annee, mois, jour; //Pour la date de la station.
    int id; //L'id de la station.
    int t; //Compteur qui définit le numéro de la colonne de la ligne stockée par ligne[N].
    int ligne1=1; //On suppose qu'on commence le tableau par la 1ère ligne. Cependant, elle ne nous intéresse pas.
  	char* ligneCopie=NULL; //Pour copier la ligne que l'on souhaite traiter.
	  char* lignePartie = NULL; //Pour séparer la ligne que l'on souhaite traiter en plusieurs parties.

    while (fgets(ligne, N, fichierEntree) != NULL) { //Traite chaque ligne du tableau csv.

      if(ligne1==0) { //Si on est pas à la 1ère ligne pour ne pas analyser la première ligne.
            
          t=0; //On commence à la première colonne de la ligne que l'on souhaite traiter.
          ligneCopie = strdup(ligne); //On copie la ligne en question.
          int longID, longM, longJ; //Stocke le nombre de chiffre de l'identifiant, du mois et du jour de la station.
          char ids[5]; //Stocke les identifiants d'une station.  
          char m[2]; //Stocke les mois d'une station.
          char j[2]; //Stocke les jours d'une station.
                
          while((lignePartie = strsep(&ligneCopie, ";")) != NULL) { //On traite la ligne en question colonne par colonne. Les colonnes sont séparées par ";".
                  
            if(t==0) { //Si on est à la 1ère colonne.
                    
              id = atoi(lignePartie); //On prend l'id de la station.

              sprintf(ids, "%d", id); //On ajoute l'id de la station dans le tableau de station.
              longID = strlen(ids); //On utilise strlen pour avoir le nombre de chiffre de l'id de la station.
                    
            }else if(t==1) { //Si on est à la 2e colonne.
                    
              sscanf(lignePartie, "%d-%d-%dT", &annee, &mois, &jour); //On prend la date de la station.

              sprintf(m, "%d", mois); //On ajoute le mois de la station dans le tableau de mois.
              longM = strlen(m); //On utilise strlen pour avoir le nombre de chiffre du mois de la station.
                
              sprintf(j, "%d", jour); //On ajoute le jour de la station dans le tableau de jour.
              longJ = strlen(j); //On utilise strlen pour avoir le nombre de chiffre du jour de la station.

            }else if(t==10) { //Si on est à la 11ème colonne.
              
              temp = atof(lignePartie); //On prend la température de la station.
                
            }
                       
            t++; //Colonne suivante.
          }	

          int station_index = -1; //On va chercher si la station existe déjà dans le tableau de station crée.

          for (int i = 0; i < nbStation; i++) { //On parcourt le tableau.
              if (tabStations[i].id == id) { //Si l'id de la station est déjà présente dans le tableau.
                  station_index = i; //alors on prend sa position dans le tableau.
                  break; //Comme on a trouvé que la station existait déjà, plus besoin de continuer et on sort de la boucle.
              }
          }

          if (station_index == -1) { //Si la station n'existe pas encore, on l'ajoute dans le tableau de station crée.
              station_index = nbStation; //Pour ajouter à la suite du tableau la nouvelle station.
              tabStations[station_index].id = id; //On ajoute l'id de la station.
              tabStations[station_index].tempMin = temp; //On ajoute la température minimale de la station.
              tabStations[station_index].tempMax = temp; //On ajoute la température maximale de la station.
              tabStations[station_index].annee = annee; //On ajoute l'année de la station.
              tabStations[station_index].mois = mois; //On ajoute le mois de la station.
              tabStations[station_index].jour = jour; //On ajoute le jour de la station.
              tabStations[station_index].longID = longID; //On ajoute la longueur de l'id de la station.
              tabStations[station_index].longM = longM; //On ajoute la longueur du mois de la station.
              tabStations[station_index].longJ = longJ; //On ajoute la longueur du jour de la station.
              nbStation++; //On a donc une station supplémentaire dans le tableau.
          }

          tabStations[station_index].temp += temp; //On ajoute la température à la station dans le tableau de station crée.
          tabStations[station_index].nbTemp++; //Il y a donc une température en + pour une station.

          if(temp<tabStations[station_index].tempMin) { //Si la température de la station du fichier d'entrée est inférieure à la température minimale de la station du tableau crée.
            tabStations[station_index].tempMin=temp; //On remplace la valeur de la température minimale de la station du tableau crée par la température de la station du fichier d'entrée.
          }
          
          if(temp>tabStations[station_index].tempMax) { //Si la température de la station du fichier d'entrée est supérieure à la température maximale de la station du tableau crée.
            tabStations[station_index].tempMax=temp; //On remplace la valeur de la température maximale de la station du tableau crée par la température de la station du fichier d'entrée.
          }

      }//Fin ligne==0

          
      ligne1 = 0; //Comme on va passer à la ligne 2 du tableau, on pourra commencer à analyser le tableau. Pour cela, on met ligne1=0.  
  
    }//Fin du parcours des lignes du fichier csv.

    /*qsort(à trier, nb éléments, **, ***);
     **taille en octet de l'élément (d'où le sizeof pour avoir la taille de la structure station).
     ***pointeur vers une fonction de comparaison qui est utilisée pour déterminer l'ordre des éléments dans le tableau. */
    qsort(tabStations,nbStation, sizeof(station), compareID); //On trie les températures par identifiant de station croissant.

    fichierSortie = fopen("mesures.csv", "w"); //Pour écrire les températures des différentes stations dans le fichier de sortie.

    //On calcule la température moyenne pour chaque station, puis on écrit les températures moyennes, max et min de chaque station dans le fichier de sortie.
    for (int i = 0; i < nbStation; i++) { //On parcourt le tableau pour pouvoir écrire les différentes stations qui s'y trouvent dans le fichier de sortie.
        station current_station = tabStations[i]; //On initialise la station que l'on va écrire dans le fichier de sortie comme étant la station qui se trouve dans le tableau.
        current_station.tempMoy = current_station.temp / current_station.nbTemp; //On calcule la température moyenne de la station.

        //Pour chacune des conditions ci-dessous, si l'id de la station comporte 4 chiffres, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                                //si le mois de la station comporte 1 chiffre, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                                //si le jour de la station comporte 1 chiffre, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                                //sinon, on écrit l'id, le mois ou le jour sans le 0.

        if(current_station.longID==4 && current_station.longM==1 && current_station.longJ==1) { //Si l'id de la station comporte 4 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "0%d;%d-0%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.tempMin, current_station.tempMax, current_station.tempMoy);
        }else if(current_station.longID==4 && current_station.longM==1 && current_station.longJ==2) { //Sinon si l'id de la station comporte 4 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 2 chiffres.
          fprintf(fichierSortie, "0%d;%d-0%d-%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.tempMin, current_station.tempMax, current_station.tempMoy);
        }else if(current_station.longID==4 && current_station.longM==2 && current_station.longJ==1) { //Sinon si l'id de la station comporte 4 chiffres, le mois de la station comporte 2 chiffres et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "0%d;%d-%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.tempMin, current_station.tempMax, current_station.tempMoy);
        }else if(current_station.longID==5 && current_station.longM==1 && current_station.longJ==1) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "%d;%d-0%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.tempMin, current_station.tempMax, current_station.tempMoy);
        }else if(current_station.longID==5 && current_station.longM==1 && current_station.longJ==2) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 2 chiffres.
          fprintf(fichierSortie, "%d;%d-0%d-%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.tempMin, current_station.tempMax, current_station.tempMoy);
        }else if(current_station.longID==5 && current_station.longM==2 && current_station.longJ==1) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 2 chiffres et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "%d;%d-%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.tempMin, current_station.tempMax, current_station.tempMoy);
        }else { //Sinon c'est que l'id de la station comporte 5 chiffres, le mois de la station comporte 2 chiffres et que le jour de la station comporte 2 chiffres.
          fprintf(fichierSortie, "%d;%d-%d-%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.tempMin, current_station.tempMax, current_station.tempMoy);
        }
    }

    fclose(fichierSortie); //On ferme le fichier de sortie.
}

// Fonction permettant, lors de son appel, de produire les pressions minimales, maximales et moyennes de chaque station et de les écrire dans un fichier de sortie par ordre croissant d'identifiant de station.
void pressMode1(FILE* fichierEntree) {

    FILE* fichierSortie = NULL; //On initialise le fichier de sortie.

    station tabStations[MAX_STATIONS]; //Tableau qui contiendra les 62 stations différentes.
    int nbStation = 0; //Servira à stocker le nombre de station.

    char ligne[N]; //Stocke les lignes du tableau csv.
    float press; //Une pression de la station.
    float pressMax; //La plus grande pression d'une station.
    float pressMin; //La plus petite pression d'une station.
    int annee, mois, jour; //Pour la date de la station.
    int id; //L'id de la station.
    int t; //Compteur qui définit le numéro de la colonne de la ligne stockée par ligne[N].
    int ligne1=1; //On suppose qu'on commence le tableau par la 1ère ligne. Cependant, elle ne nous intéresse pas.
  	char* ligneCopie=NULL; //Pour copier la ligne que l'on souhaite traiter.
	  char* lignePartie = NULL; //Pour séparer la ligne que l'on souhaite traiter en plusieurs parties.

    while (fgets(ligne, N, fichierEntree) != NULL) { //Traite chaque ligne du tableau csv.

      if(ligne1==0) { //Si on est pas à la 1ère ligne pour ne pas analyser la première ligne.
              
          t=0; //On commence à la première colonne de la ligne que l'on souhaite traiter.
          ligneCopie = strdup(ligne); //On copie la ligne en question.
          int longID, longM, longJ; //Stocke le nombre de chiffre de l'identifiant, du mois et du jour de la station.
          char ids[5]; //Stocke les identifiants d'une station.  
          char m[2]; //Stocke les mois d'une station.
          char j[2]; //Stocke les jours d'une station.
                
          while((lignePartie = strsep(&ligneCopie, ";")) != NULL) { //On traite la ligne en question colonne par colonne. Les colonnes sont séparées par ";".
                  
            if(t==0) { //Si on est à la 1ère colonne.
                    
              id = atoi(lignePartie); //On prend l'id de la station.

              sprintf(ids, "%d", id); //On ajoute l'id de la station dans le tableau de station.
              longID = strlen(ids); //On utilise strlen pour avoir le nombre de chiffre de l'id de la station.

            }else if(t==1) { //Si on est à la 2e colonne.
                    
              sscanf(lignePartie, "%d-%d-%dT", &annee, &mois, &jour); //On prend la date de la station.

              sprintf(m, "%d", mois); //On ajoute le mois de la station dans le tableau de mois.
              longM = strlen(m); //On utilise strlen pour avoir le nombre de chiffre du mois de la station.
                
              sprintf(j, "%d", jour); //On ajoute le jour de la station dans le tableau de jour.
              longJ = strlen(j); //On utilise strlen pour avoir le nombre de chiffre du jour de la station.

            }else if(t==6) { //Si on est à la 7ème colonne.
              
              press = atof(lignePartie); //On prend la pression de la station.
                
            }
                       
            t++; //Colonne suivante.
          }	

          int station_index = -1; //On va chercher si la station existe déjà dans le tableau de station crée.

          for (int i = 0; i < nbStation; i++) { //On parcourt le tableau.
              if (tabStations[i].id == id) { //Si l'id de la station est déjà présente dans le tableau.
                  station_index = i; //alors on prend sa position dans le tableau.
                  break; //Comme on a trouvé que la station existait déjà, plus besoin de continuer et on sort de la boucle.
              }
          }

          if (station_index == -1) { //Si la station n'existe pas encore, on l'ajoute dans le tableau de station crée.
              station_index = nbStation; //Pour ajouter à la suite du tableau la nouvelle station.
              tabStations[station_index].id = id; //On ajoute l'id de la station.
              tabStations[station_index].pressMin = press; //On ajoute la pression minimale de la station.
              tabStations[station_index].pressMax = press; //On ajoute la pression maximale de la station.
              tabStations[station_index].annee = annee; //On ajoute l'année de la station.
              tabStations[station_index].mois = mois; //On ajoute le mois de la station.
              tabStations[station_index].jour = jour; //On ajoute le jour de la station.
              tabStations[station_index].longID = longID; //On ajoute la longueur de l'id de la station.
              tabStations[station_index].longM = longM; //On ajoute la longueur du mois de la station.
              tabStations[station_index].longJ = longJ; //On ajoute la longueur du jour de la station.
              nbStation++; //On a donc une station supplémentaire dans le tableau.
          }

          tabStations[station_index].press += press; //On ajoute la pression à la station dans le tableau de station crée.
          tabStations[station_index].nbPress++; //Il y a donc une pression en + pour une station.

          if(press<tabStations[station_index].pressMin) { //Si la presion de la station du fichier d'entrée est inférieure à la pression minimale de la station du tableau crée.
            tabStations[station_index].pressMin=press; //On remplace la valeur de la pression minimale de la station du tableau crée par la pression de la station du fichier d'entrée.
          }
          
          if(press>tabStations[station_index].pressMax) { //Si la presion de la station du fichier d'entrée est supérieure à la pression maximale de la station du tableau crée.
            tabStations[station_index].pressMax=press; //On remplace la valeur de la pression maximale de la station du tableau crée par la pression de la station du fichier d'entrée.
          }

      }//Fin ligne==0

          
      ligne1 = 0; //Comme on va passer à la ligne 2 du tableau, on pourra commencer à analyser le tableau. Pour cela, on met ligne1=0.  
  
    }//Fin du parcours des lignes du fichier csv.

    /*qsort(à trier, nb éléments, **, ***);
     **taille en octet de l'élément (d'où le sizeof pour avoir la taille de la structure station).
     ***pointeur vers une fonction de comparaison qui est utilisée pour déterminer l'ordre des éléments dans le tableau. */
    qsort(tabStations,nbStation, sizeof(station), compareID); //On trie les pressions par identifiant de station croissant.

    fichierSortie = fopen("mesures.csv", "w"); //Pour écrire les pressions des différentes stations dans le fichier de sortie.

    //On calcule la pression moyenne pour chaque station, puis on écrit les pressions moyennes, max et min de chaque station dans le fichier de sortie.
    for (int i = 0; i < nbStation; i++) { //On parcourt le tableau pour pouvoir écrire les différentes stations qui s'y trouvent dans le fichier de sortie.
        station current_station = tabStations[i]; //On initialise la station que l'on va écrire dans le fichier de sortie comme étant la station qui se trouve dans le tableau.
        current_station.pressMoy = current_station.press / current_station.nbPress; //On calcule la pression moyenne de la station.

        //Pour chacune des conditions ci-dessous, si l'id de la station comporte 4 chiffres, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                                //si le mois de la station comporte 1 chiffre, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                                //si le jour de la station comporte 1 chiffre, on lui rajoute un 0 (car avec la convertion atoi(), le 0 initial a disparu);
                                                //sinon, on écrit l'id, le mois ou le jour sans le 0.

        if(current_station.longID==4 && current_station.longM==1 && current_station.longJ==1) { //Si l'id de la station comporte 4 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "0%d;%d-0%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.pressMin, current_station.pressMax, current_station.pressMoy);
        }else if(current_station.longID==4 && current_station.longM==1 && current_station.longJ==2) { //Sinon si l'id de la station comporte 4 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 2 chiffres.
          fprintf(fichierSortie, "0%d;%d-0%d-%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.pressMin, current_station.pressMax, current_station.pressMoy);
        }else if(current_station.longID==4 && current_station.longM==2 && current_station.longJ==1) { //Sinon si l'id de la station comporte 4 chiffres, le mois de la station comporte 2 chiffres et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "0%d;%d-%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.pressMin, current_station.pressMax, current_station.pressMoy);
        }else if(current_station.longID==5 && current_station.longM==1 && current_station.longJ==1) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "%d;%d-0%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.pressMin, current_station.pressMax, current_station.pressMoy);
        }else if(current_station.longID==5 && current_station.longM==1 && current_station.longJ==2) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 1 chiffre et le jour de la station comporte 2 chiffres.
          fprintf(fichierSortie, "%d;%d-0%d-%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.pressMin, current_station.pressMax, current_station.pressMoy);
        }else if(current_station.longID==5 && current_station.longM==2 && current_station.longJ==1) { //Sinon si l'id de la station comporte 5 chiffres, le mois de la station comporte 2 chiffres et le jour de la station comporte 1 chiffre.
          fprintf(fichierSortie, "%d;%d-%d-0%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.pressMin, current_station.pressMax, current_station.pressMoy);
        }else { //Sinon c'est que l'id de la station comporte 5 chiffres, le mois de la station comporte 2 chiffres et que le jour de la station comporte 2 chiffres.
          fprintf(fichierSortie, "%d;%d-%d-%d;%f;%f;%f\n", current_station.id, current_station.annee, current_station.mois, current_station.jour, current_station.pressMin, current_station.pressMax, current_station.pressMoy);
        }
    }

    fclose(fichierSortie); //On ferme le fichier de sortie.
}
