#include "fonctions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>		//necessaire au getopt.
#include <getopt.h>     //necessaire au getopt.
#define N 2200000

//Fonction principale du programme.

int main(int argc, char* argv[]) { //argc est le nombre d'argument de la ligne de commande du terminal ; argv[] est le tableau d'arguments de la ligne de commande du terminal.

////////////////////VARIABLES////////////////////

    clock_t debut = clock();   //Démarrer le compteur du temps d'execution.

////////////////////GESTION DES OPTIONS////////////////////

    //opt renvoie -1 lorsqu'il n'y aura plus d'options à traiter avec la méthode getopt().
    //Si cette variable prend une valeur, alors cette valeur sera pointée par optarg.
    char* optC_exlu;
    int opt;
    int mode = 0; //Dédié pour les options -t et -p.
    int exclusif=0; //Dédié pour les options -h , -m, -p, -t et -w.
    int iLongueurOpt, oLongueurOpt; //iLongueurOpt(respectivement oLongueurOpt) stocke la longueur de l'argument de l'option -i(respectivement -o).
    int t=0;
    int estp=0;
    int esth=0;
    int estm=0;
    int esto=0;
    int esti=0;
    int autreOptQuei=0; //Permet de verifier qu'une option, autre que -i, soit utilisée. L'option -i nécessite l'utilisation d'une autre option afin d'effectuer une action.

////////////////////GESTION FICHIER////////////////////

    FILE* fichierEntree=NULL; //Variable de type FILE* qui joue le rôle du fichier d'entrée.
    //FILE* fichierSortie=NULL; //Variable de type FILE* qui joue le rôle du fichier de sortie.
    char* nomEntree;    //Nom du fichier d'entrée que l'on utilisera pour récupérer les données.
    char* nomSortie;    //Nom du fichier de sortie qui prend soit le nom que l'utilisateur aura choisi ou soit un nom par défaut (meteo1234.dat).

////////////////////DEBUT////////////////////

    if(argc==1){   //Si le seul argument est l'exécutable lui-même.
   	 
    	printf("\nErreur : vous n'avez émis aucun argument.\n\n");  //On affiche une erreur.
        return 1; //On retourne 1 car c'est une erreur.
    }
    else if(argc==2 && !strcmp(argv[1],"--help")) { //Sinon si il y a 2 arguments et que le 2e argument est "--help".

        afficheAide();   //On affiche l'aide comme demandé avec l'option "--help".
        return 0;   //On retourne 0 car tout s'est bien déroulé.
    }

    /*
        * getopt analyse les options de ligne de commande et la liste des paramètres, 
        * argc est la liste d'arguments à analyser,
        * argv est la chaîne de lettre d'options que le script doit reconnaître,
        * "t:p:whmi:o:g:" est la liste des chaînes avec les noms des options qui doivent être prises en charge.
    */

    while((opt = getopt(argc, argv, "t:p:whmi:o:g::")) != -1) {

        switch(opt) {  //En fonction de/des option(s) renseignée(s).

			case 'i': //Obligatoire.

                iLongueurOpt=strlen(optarg); //strlen(optarg) permet de connaître la longueur de optarg, l'argument de l'option -i.
                nomEntree=optarg; //nomEntree récupère le nom du fichier d'entrée que l'utilisateur a renseigné en argument de l'option -i.
                esti = 1; //esti=1 car l'option -i est utilisée.
				break; //On sort du cas opt=i.

            case 't': //-t est une option exclusive mais doit être en argument si les options -p, -w, -h et -m n'y sont pas.
                
                autreOptQuei=1; //L'option -i, obligatoire, est accompagnée d'une autre option.
                exclusif+=1; //On ajoute +1 à la variable à chaque fois qu'une des options suivantes est utilisée : -t, -p, -w, -h, -m.
                t=1; //t=1 car l'option -t est utilisée.
                mode=atoi(optarg); //La variable mode récupère l'argument de l'option -t; atoi(optarg) convertit en valeur numérique optarg qui est l'argument de l'option -t.
                optC_exlu = "t";
				break; //On sort du cas opt=t.
				
            case 'p': //-p est une option exclusive mais doit être en argument si les options -t, -w, -h et -m n'y sont pas.

                autreOptQuei=1; //L'option -i, obligatoire, est accompagnée d'une autre option.
                exclusif+=1; //On ajoute +1 à la variable à chaque fois qu'une des options suivantes est utilisée : -t, -p, -w, -h, -m.
                estp=1; //estp=1 car l'option -p est utilisée.
                mode=atoi(optarg); //La variable mode récupère l'argument de l'option -p; atoi(optarg) convertit en valeur numérique optarg qui est l'argument de l'option -p.
                optC_exlu = "p";
                break; //On sort du cas opt=p.
                
            case 'w': //-w est une option exclusive mais doit être en argument si les options -t, -p, -h et -m n'y sont pas.
				
                autreOptQuei=1; //L'option -i, obligatoire, est accompagnée d'une autre option.
                exclusif+=1; //On ajoute +1 à la variable à chaque fois qu'une des options suivantes est utilisée : -t, -p, -w, -h, -m.
                optC_exlu = "w";
                break; //On sort du cas opt=w.
            
            case 'h': //-h est une option exclusive mais doit être en argument si les options -t, -p, -w et -m n'y sont pas.
				
                autreOptQuei=1; //L'option -i, obligatoire, est accompagnée d'une autre option.
                exclusif+=1; //On ajoute +1 à la variable à chaque fois qu'une des options suivantes est utilisée : -t, -p, -w, -h, -m.
                esth=1; //esth=1 car l'option -h est utilisée.
                optC_exlu = "h";
                break; //On sort du cas opt=h.
            
            case 'm': //-m est une option exclusive mais doit être en argument si les options -t, -p, -w et -h n'y sont pas.
				
                autreOptQuei=1; //L'option -i, obligatoire, est accompagnée d'une autre option.
                exclusif+=1; //On ajoute +1 à la variable à chaque fois qu'une des options suivantes est utilisée : -t, -p, -w, -h, -m.
                estm=1; //estm=1 car l'option -m est utilisée.
                optC_exlu = "m";
                break; //On sort du cas opt=m.

            case 'o': //L'option -o n'est pas obligatoire.	

                autreOptQuei=1; //L'option -i, obligatoire, est accompagnée d'une autre option.
                oLongueurOpt=strlen(optarg); //strlen(optarg) permet de connaître la longueur de optarg, l'argument de l'option -i.
                nomSortie=optarg; //nomSortie récupère le nom du fichier de sortie que l'utilisateur a renseigné en argument de l'option -o.
                esto=1; //esto>=1 car l'option -o est utilisée au moins une fois.
                break; //On sort du cas opt=o.

            default : //Si nous ne sommes dans aucun des cas ci-dessus.

                //On affiche une erreur.
                printf("\nErreur : il y a minimum une option qui n'est pas prise en compte ou au moins un argument manquant pour une ou plusieurs options.\n\n");
   			    return 1; //On retourne 1 car c'est une erreur.
    	}
	}

//////////ON TRAITE D'ABORD LES ERREURS POSSIBLES DANS L'INDICATION DES OPTIONS DANS LE TERMINAL PAR L'UTILISATEUR//////////

    if(esti==0) { //Si l'option -i n'est pas utilisée. Si on ne rentre pas dans cette condition, alors l'option -i est forcément utilisée.

        printf("\nErreur : il faut obligatoirement utiliser l'option -i et renseigner le fichier d'entrée.\n\n"); //On affiche une erreur.
        return 1; //On retourne 1 car c'est une erreur.

    }

    if(esto==0) { //Si l'option -o n'est pas utilisée. Si on ne rentre pas dans cette condition, alors l'option -o est forcément utilisée.

        nomSortie = "meteo1234.dat"; //On prend un nom de fichier de sortie par défaut qui est "meteo1234.dat".

    }

    if(exclusif==0){   //Sinon s'il n'y a aucune option exclusive d'utilisée.

        //On affiche une erreur.
        printf("\nErreur : option exclusive manquante parmis -t, -p, -w, -h et -m. Il faut absolument utiliser une seule de ces options.\n\n");
        return 1; //On retourne 1 car c'est une erreur.

    } else if(exclusif>1){   //Sinon s'il y a au moins 2 options exclusives utilisées en même temps.

        printf("\nErreur : il y a au moins 2 options exclusives utilisées en même temps.\n\n"); //On affiche une erreur.
        return 1; //On retourne 1 car c'est une erreur.

    }

//////////ENSUITE ON PEUT TRAITER LES OPTIONS CAS PAR CAS//////////

    if(autreOptQuei==1) { //Si une autre option que l'option -i est utilisée.

        if(iLongueurOpt>2) { //Si la longueur de caractère de l'argument de l'option -i est supérieure à 2.

            fichierEntree = fopen(nomEntree, "r"); //On ouvre en mode lecture le fichier en question.
                
            if (fichierEntree == NULL) {
                printf("Impossible d'ouvrir le fichier '%s'\n", nomEntree);
                return 1;
            }
        }else { //Sinon si la longueur de caractère de l'argument de l'option -i est inférieure ou égale à 2.

            printf("\nErreur : l'argument de l'option -i n'est pas valide.\n\n"); //On affiche une erreur.
            return 1; //On retourne 1 car c'est une erreur.

        }
    }else { //Sinon s'il n'y a aucune autre option que l'option -i d'utilisée dans le terminal.

        printf("\nErreur : option manquante après l'option -i.\n\n");//On affiche une erreur car l'exécutable avec l'utilisation, seule, de l'option -i doit retourner une erreur.
        return 1; //On retourne 1 car c'est une erreur.

    }
    
    if(esto==1) { //Si l'option -o est utilisée.

        if(oLongueurOpt<2) { //Si la longueur de caractère de l'argument de l'option -o est supérieure à 2.

            printf("\nErreur : l'argument de l'option -o n'est pas valide.\n\n"); //On affiche une erreur.
            return 1; //On retourne 1 car une erreur.
        
        }
    }

    if(exclusif==1) { //Si une seule option exclusive est utilisée.

        if(t==1) { //Si l'option utilisée est -t.

            if(mode<1 || mode>3) { //Si le mode saisi n'est ni 1, ni 2, ni 3.

                printf("\nErreur : le mode saisi pour la température n'est pas valide.\n\n"); //On affiche une erreur.
                return 1; //On retourne 1 car c'est une erreur.

            }else { //Sinon si le mode de l'option -t est compris entre 1 et 3.

                if(mode==1) { //Si le mode de la température est 1.

                    fichierEntree = fopen(nomEntree, "r"); //On ouvre le fichier d'entrée à analyser.
                    tempMode1(fichierEntree);
                    fclose(fichierEntree); //On ferme le fichier d'entrée.

                }
            }

        }else if(estp==1) { //Sinon si l'option utilisée est -p.

            if(mode<1 || mode>3) { //Si le mode saisi n'est ni 1, ni 2, ni 3.

                printf("\nErreur : le mode saisi pour la pression atmosphérique n'est pas valide.\n\n"); //On affiche une erreur.
                return 1; //On retourne 1 car c'est une erreur.

            }else { //Sinon si le mode est compris entre 1 et 3.

                if(mode==1) { //Si le mode de la pression atmosphérique est 1.

                    fichierEntree = fopen(nomEntree, "r"); //On ouvre le fichier d'entrée à analyser.
                    pressMode1(fichierEntree);
                    fclose(fichierEntree); //On ferme le fichier d'entrée.

                }
            }
            
        }else if(esth==1) { //Sinon si l'option utilisée est -h.
			
            fichierEntree = fopen(nomEntree, "r"); //On ouvre le fichier d'entrée à analyser.
            alt(fichierEntree);
            fclose(fichierEntree); //On ferme le fichier d'entrée.

        }else if(estm==1) { //Sinon si l'option utilisée est -m.

			fichierEntree = fopen(nomEntree, "r"); //On ouvre le fichier d'entrée à analyser.
			hum(fichierEntree);
			fclose(fichierEntree); //On ferme le fichier d'entrée.
		}
	}

//////////APPEL DU SCRIPT//////////

    // Déclaration de la variable option qui stockera les options saisies par l'utilisateur
    // Déclaration de la variable commande qui stockera la commande shell complète
    char option[2000];
    char commande[5000];
    printf("sh AffichageExclu.sh nom d'entrée : %s nom de sortie : %s %s %d",nomEntree,nomSortie,optC_exlu,mode);
    printf("Entrez les options pour l'exécution du script: \n");
    fgets(option, sizeof(option), stdin); // FGETS et pas SCANF sinon ça pose soucis si y'a des espaces
    printf("%s", option);

    // Construction de la commande shell complète en utilisant sprintf
    // inclut le nom du script et les options saisies par l'utilisateur
    sprintf(commande, "sh AffichageExclu.sh -%s %s %s %d %s",optC_exlu,nomEntree,nomSortie,mode,option);

    // Exécution de la commande shell avec la fonction system
    int res = system(commande);
    // Si la fonction system renvoie -1, cela signifie qu'une erreur s'est produite, on affiche un message d'erreur avec perror
    if (res == -1) {
        perror("erreur lors de l'execution du script shell \n");
        return 1;
    }

    // Afficher le temps d'exécution.
    clock_t fin = clock();
    double tempsEcoule = (double)(fin - debut) / CLOCKS_PER_SEC;
    printf("\n Temps d'exécution du programme C : %f secondes\n", tempsEcoule);

    return 0; //Si on arrive jusqu'ici, c'est que tout s'est bien déroulé. On retourne donc 0.
}
