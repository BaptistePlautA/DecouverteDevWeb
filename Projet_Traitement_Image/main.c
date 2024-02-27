/* Auteurs : Théo De Morais, Baptiste Plaut-Aubry, Ayman El kili
 * Date : 20.05.22 */

#include "PROJET.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>				//necessaire au getopt.
#include <string.h>
#include <getopt.h>             //necessaire au getopt.
#define N 100

	// Procédure qui permet * d'afficher l'aide de toutes les commandes utilisables par le programme;
	//                      * d'afficher l'aide d'une option précise grâce à l'option -h.

void afficheAide(char* arg) {

    if(!strcmp(arg,"-h")){                      //Si l'argument est -h alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -h <-argument>\n\n");
        printf("OPTION :\n\n");
        printf("-h <-argument> (-argument facultatif): affiche une aide sur les options utilisables ou sur une option precise utilisable, quitte le programme avec un code de retour egal a 0. Cette option doit suivre l'executable ;\n\n");
        printf("L'option '-h', utilisee seule, affiche l'aide de toutes les options possibles.\n");
        printf("A contrario, si un argument suit le '-h', cela va afficher precisement l'aide de l'argument en question.\n");
        printf("Il convient donc que cette argument doit etre une option prise en charge par le programme.\n");
        printf("Attention : plus d'un argument apres le '-h' n'est pas possible.\n\n");

    }
    else if(!strcmp(arg,"-b")){                      //Si l'argument est -b alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -b <seuil>\n\n");
        printf("OPTION :\n\n");
        printf("-b : binarise une image ;\n\n");

    }
    else if(!strcmp(arg,"-c")){                      //Si l'argument est -c alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -c\n\n");
        printf("OPTION :\n\n");
        printf("-c : realise un renforcement de contraste ;\n\n");

    }
    else if(!strcmp(arg,"-d")){                      //Si l'argument est -d alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -d\n\n");
        printf("OPTION :\n\n");
        printf("-d : realise une dilatation ;\n\n");

    }
    else if(!strcmp(arg,"-e")){                      //Si l'argument est -e alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -e\n\n");
        printf("OPTION :\n\n");
        printf("-e : realise une erosion ;\n\n");

    }
    else if(!strcmp(arg,"-f")){                      //Si l'argument est -f alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -f\n\n");
        printf("OPTION :\n\n");
        printf("-f : realise un flou ;\n\n");

    }
    else if(!strcmp(arg,"-i")){                      //Si l'argument est -i alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -i <fichier>\n\n");
        printf("OPTION :\n\n");
        printf("-i : definit le fichier d'entree, OBLIGATOIRE (sauf si -h utilisee) ;\n\n");

    }
    else if(!strcmp(arg,"-l")){                      //Si l'argument est -l alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -l\n\n");
        printf("OPTION :\n\n");
        printf("-l : realise une detection de contours/lignes ;\n\n");

    }
    else if(!strcmp(arg,"-g")){                      //Si l'argument est -g alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -g\n\n");
        printf("OPTION :\n\n");
        printf("-g : convertit l'image en niveau de gris ;\n\n");

    }
    else if(!strcmp(arg,"-o")){                      //Si l'argument est -o alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -o <fichier>\n\n");
        printf("OPTION :\n\n");
        printf("-o : definit le fichier de sortie ;\n\n");

    }
    else if(!strcmp(arg,"-r")){                      //Si l'argument est -r alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -r\n\n");
        printf("OPTION :\n\n");
        printf("-r : realise un recadrage dynamique ;\n\n");

    }
    else if(!strcmp(arg,"-x")){                      //Si l'argument est -x alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -x <largeur> <hauteur> <epaisseur>\n\n");
        printf("OPTION :\n\n");
        printf("-x : realise une croix aux dimensions specifiees ;\n\n");
        printf("Cette option ne necessite pas l'utilisation de l'option '-i'.\n");

    }
    else if(!strcmp(arg,"-m")){                      //Si l'argument est -m alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -m -i <fichier> -o <fichier>\n\n");
        printf("OPTION :\n\n");
        printf("-m : realise le miroir d une image ;\n\n");

    }
    else if(!strcmp(arg,"-p")){                      //Si l'argument est -p alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -p -i <fichier> -o <fichier>\n\n");
        printf("OPTION :\n\n");
        printf("-p : pivote une image de 90 degres dans le sens horaire ;\n\n");

    }
    else if(!strcmp(arg,"-n")){                      //Si l'argument est -n alors on affiche l'aide pour son utilisation.

        printf("\n\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> -n -i <fichier> -o <fichier>\n\n");
        printf("OPTION :\n\n");
        printf("-n : realise le negatif d une image ;\n\n");

    }
    else if(!strcmp(arg,"1")){					//Cas dans lequel le seul argument est l'exécutable lui-même. On affiche alors l'aide.

        printf("\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> <option> (possibilite de mettre plusieurs options de suite)\n\n");
        printf("OPTIONS :\n\n");
        printf("-h <-argument> (-argument facultatif): affiche une aide sur les options utilisables ou sur une option precise utilisable, quitte le programme avec un code de retour egal a 0 et doit suivre l'executable ;\n");
        printf("L'option '-h', utilisee seule, affiche l'aide de toutes les options possibles.");
        printf("A contrario, si un argument suit le '-h', cela va afficher precisement l'aide de l'argument en question.");
        printf("Il convient donc que cette argument doit etre une option prise en charge par le programme. Plus d'un argument apres le '-h' n'est pas possible.");
        printf("-b <seuil>: binarise une image ;\n");
        printf("-c : realise un renforcement de contraste ;\n");
        printf("-d : realise une dilatation ;\n");
        printf("-e : realise une erosion ;\n");
        printf("-f : realise un flou ;\n");
        printf("-i <fichier> : definit le fichier d'entree, OBLIGATOIRE (sauf si -h utilisee) ;\n");
        printf("-l : realise une detection de contours/lignes ;\n");
        printf("-g : convertit l'image en niveau de gris ;\n");
        printf("-o <fichier> : definit le fichier de sortie ;\n");
        printf("-r : realise un recadrage dynamique ;\n");
        printf("-x <largeur> <hauteur> <epaisseur> : realise une croix aux dimensions specifiees ;\n");
        printf("-m : realise le miroir d une image ;\n");
        printf("-n : realise le negatif d une image ;\n");
        printf("-p : pivote une image de 90 degres dans le sens horaire ;\n");
        printf("\nToutes les options ci-dessus necessite l'utilisation de l'option '-i', exceptee les options '-x' et '-h'.\n");
        printf("\n\n");

    }
    else {

        printf("\n----- Manuel sur les commandes utilisables -----\n\n");
        printf("La syntaxe est la suivante : ./<executable> <option> (possibilite de mettre plusieurs options de suite)\n\n");
        printf("OPTIONS :\n\n");
        printf("-h <-argument> (-argument facultatif): affiche une aide sur les options utilisables ou sur une option precise utilisable, quitte le programme avec un code de retour egal a 0 et doit suivre l'executable ;\n");
        printf("L'option '-h', utilisee seule, affiche l'aide de toutes les options possibles.");
        printf("A contrario, si un argument suit le '-h', cela va afficher precisement l'aide de l'argument en question.");
        printf("Il convient donc que cette argument doit etre une option prise en charge par le programme. Plus d'un argument apres le '-h' n'est pas possible.");
        printf("-b <seuil>: binarise une image ;\n");
        printf("-c : realise un renforcement de contraste ;\n");
        printf("-d : realise une dilatation ;\n");
        printf("-e : realise une erosion ;\n");
        printf("-f : realise un flou ;\n");
        printf("-i <fichier> : definit le fichier d'entree, OBLIGATOIRE (sauf si -h utilisee) ;\n");
        printf("-l : realise une detection de contours/lignes ;\n");
        printf("-g : convertit l'image en niveau de gris ;\n");
        printf("-o <fichier> : definit le fichier de sortie ;\n");
        printf("-r : realise un recadrage dynamique ;\n");
        printf("-x <largeur> <hauteur> <epaisseur> : realise une croix aux dimensions specifiees ;\n");
        printf("-m : realise le miroir d une image ;\n");
        printf("-n : realise le negatif d une image ;\n");
        printf("-p : pivote une image de 90 degres dans le sens horaire ;\n");
        printf("\nToutes les options ci-dessus necessite l'utilisation de l'option '-i', exceptee les options '-x' et '-h'.\n");
        printf("\n\n");

    }
}

// Fonction principale du programme.

int main(int argc, char* argv[]) {
	
	printf("Debut\n");
	
    /// II MANIPULATIONS BASIQUES
    
    int* histogramme;
    //Variables qui permettent de savoir si une option est utilisée.
    int tmph = 0;
    int tmphVrai = 0;
    int tmpi = 0;
    int tmpb = 0;
    int tmpc = 0; 
    int tmpd = 0;
    int tmpe = 0;
    int tmpf = 0;
    int tmpl = 0;
    int tmpg = 0;
    int tmpgHisto = 0;
    int tmpo = 0;
    int tmpoVrai = 0;
    int tmpr = 0;
    int tmpx = 0;
    int tmpxVrai = 0;
    int tmpm = 0;
    int tmpn = 0;
    int tmpp = 0;
	int seuil;              //Seuil qu'on indique en argument pour la binarisation. 

    //Variables pour la réalisation de la croix.
    int Xlarge = 0;
    int Yhaut = 0;
    int epaisseur = 0;
    int xpos = 0;
    
    ///Creation et Allocation de monImage
    IMAGE* monImage;
    monImage = malloc(sizeof(IMAGE)*N);
    monImage->signature = malloc(sizeof(char)*3);
    
    FILE* img_entree = NULL;
	
	/// III FILTRAGE
	
	int opt;				//Option
    char* arg;              //Servira pour afficher l'aide sur une option précise.
    char* nomImageSortie;

    CROIX* maCroix;
    ///Allocation du tab 2D
    maCroix = malloc(sizeof(int)*N);
    maCroix->TabCroix = malloc(5 * sizeof(int));
        for (int i=0;i<5;i++){
          maCroix->TabCroix[i] = malloc(5 * sizeof (int));
        }
	
	if(argc == 1){                                                                                      //Si le seul argument est l'exécutable lui-même,
        
        arg = "1";                                                                                       //Juste pour assigner une valeur à arg et pouvoir le passer en parametre de la procédure afficheAide().
        printf("\nVous n'avez mis aucun argument. Ci-dessous la liste des options utilisables :\n");    //alors on affiche une erreur
		afficheAide(arg);                                                                               //et on affiche l'aide sur les options.

	}
	
	while((opt = getopt(argc, argv, "hb:cdefi:lgo:rx:::mnp")) != -1) //getopt analyse les options de ligne de commande et la liste des paramètres. 
                                                                        //argc est la liste d'arguments à analyser,
                                                                        //argv est la chaîne de lettre d'options que le script doit reconnaître,
                                                                        //"hb:cdefi:lgo:rx:mnp" est la liste des chaînes avec les noms des options qui doivent être prises en charge.
    { 
        switch(opt)                                                     //En fonction de/des option(s) renseignee(s)
        {
			case 'i': 
				
                tmpi = 1;
                //C'est l'argument après le -i (donc le nom du fichier d'entrée).
		        img_entree = fopen(optarg ,"r");
		        ////Sauvegarde de l'image d'entree en utilisant monImage comme sauvegarde
		        monImage = ChargementPPM(img_entree,monImage);
				break;
					
            case 'h':
                
                tmphVrai = 1;
                tmph += 1;
				break;
				
            case 'b':

                tmpb += 1;
                seuil = atoi(optarg);
				break;
				
            case 'c': 
            
                tmpc += 1;
                break; 
                
            case 'd': 
				
                tmpd += 1; 
                break; 
                
            case 'e': 

                tmpe += 1;
                break; 
                
            case 'f': 
            
                tmpf += 1;
                break;
                
            case 'l': 

                tmpl += 1;
                break; 
                
            case 'g': 

                tmpg += 1;
                break; 
                
            case 'r': 

                tmpr += 1;
                break;
                
            case 'x': 

                tmpx += 1;
                tmpxVrai = 1;
                Xlarge = atoi(argv[xpos+1]);
                Yhaut = atoi(argv[xpos+2]);
                epaisseur = atoi(argv[xpos+3]);
                break;

            case 'm': 

                tmpm += 1;
                break;

            case 'n': 

                tmpn += 1;
                break;

            case 'p': 

                tmpp += 1;
                break;
                
            case 'o':

                nomImageSortie = optarg;
                tmpo +=1;
                break;
                
            default :

                arg = "1";																									//Juste pour assigner une valeur à arg et pouvoir le passer en parametre de la procédure afficheAide().
				afficheAide(arg);                           //On affiche l'aide car il y a soit une/des option(s) qui n'est/ne sont pas prise en compte ou soit un/des argument(s) manquant(s) pour une/des option(s).
				break;
                
        } 

        xpos +=1;       //Variable pour connaitre la position de l'option x et ainsi pour pouvoir gérer les 3 arguments de x. 
    }

    for(int q=0; q<argc; q++) {

        if(tmph>=1){

            arg = "1";                                          //Juste pour asssigner une valeur à la variable pour afficher l'aide des options.

                if(argc == 3){                                      //Si on a 3 arguments alors

                    if(!strcmp(argv[1],"-h")){                      //Si -h suit l'exécutable alors

                        char* optAide = argv[2];                    //on prend l'option renseignée juste après -h
                        afficheAide(optAide);                       //et on affiche l'aide de l'option en question.
                        exit(0);

                    }
                    else{                                                                 //Sinon si -h ne suit pas l'exécutable alors

                        afficheAide(arg);                                                 //et on affiche l'aide.
                        exit(0);

                    }
                }
                else if(argc == 2){                                                                                     //Si on a 2 arguments alors

                    afficheAide(arg);                                                                                   //on affiche l'aide.
                    exit(0);

                }
                else if(argc > 3) {                                                       //Si on a au moins 4 arguments alors

                    if(!strcmp(argv[1],"-h")){                                            //si -h suit l'exécutable alors  

                        afficheAide(arg);                                                 //et on affiche l'aide.
                        exit(0);

                    }
                    else {                                                                                  //Sinon si -h ne suit pas l'exécutable alors

                        afficheAide(arg);                                                                  //on affiche l'aide.
                        exit(0);

                    }

                }
                tmph -=1;
				return 0;

        }
        if(!tmpi && !tmpx && !tmpxVrai && !tmph && !tmphVrai){            //Si les options -i, -h et -x ne sont pas utilisées, alors on affiche l'aide. ()

            arg = "1";          //Juste pour assigner une valeur à la variable arg afin d'afficher l'aide;
            afficheAide(arg);
            exit(0);

        }
        if(tmpx>=1 && tmpxVrai){

            if(Xlarge || Yhaut || epaisseur){               //Si les dimensions de la croix ne sont pas vide, c'est-àdire si elles ont été spécifiées alors on peut rentrer dans fonction Croix.

                monImage = Croix(monImage, Xlarge, Yhaut, epaisseur);            //Une image en entree est necessaire. Sur ce point, nous avons manqué de temps afin de rendre cette fonction indépendante d'une image d'entree.
                tmpx -=1;

            }
            else {                              //Sinon si les dimensions de la croix ne sont pas spécifiées on affiche l'aide.

                arg = "1";
                afficheAide(arg);
                exit(0);
            }
        }
        if(tmpb>=1){
			
			if(seuil){
				
				monImage = Binarisation(monImage,seuil);
				
			}
			else {
					
				arg = "-b";
				afficheAide(arg);
                exit(0);
					
			}
            tmpb -=1;

        }
        if(tmpc>=1){

            monImage = MatriceContraste(monImage);
            tmpc -=1;

        }
        if(tmpd>=1){

            monImage = Dilatation(monImage,maCroix);
            tmpd -=1;

        }
        if(tmpe>=1){

            monImage = Erosion(monImage, maCroix);
            tmpe -=1;
        }
        if(tmpf>=1){

            monImage = MatriceFlou(monImage);
            tmpf -=1;

        }
        if(tmpl>=1){

            monImage = MatriceContour(monImage);
            tmpl -=1;

        }
        if(tmpg>=1){

            tmpgHisto = 1;
            monImage = NiveauDeGris(monImage);
            histogramme = CreationHistogramme(monImage);
            tmpg -=1;

        }
        if(tmpr>=1){

            if(tmpgHisto){
				
                monImage = RecadrageDynamique(monImage, histogramme);
                tmpr -=1;

            }
            else{
				
				arg = "-r";
				afficheAide(arg);
				exit(0);
				
				}
        }
        if(tmpm>=1){

            monImage = Miroir(monImage);
            tmpm -=1;

        }
        if(tmpn>=1){

            monImage = Negatif(monImage);
            tmpn -=1;

        }
        if(tmpp>=1){
            
            monImage = Rotation(monImage);
            tmpp -=1;

        }
}

for(int u=0; u<argc; u++) {

    if(tmpo>=1){

        tmpoVrai = 1;
            ///Creation d'une nouvelle image de sortie en utilisant monImage
		    SauvegardePPM(img_entree,monImage, nomImageSortie, tmpo);
            tmpo -=1;    
    }
    else if(!tmpo && !tmpoVrai){                    //Si -o n'est pas utilisé, alors à travers sauvegardePPM on va afficher dans le terminal l'image.

        ///Creation d'une nouvelle image de sortie en utilisant monImage
	    SauvegardePPM(img_entree,monImage, nomImageSortie, tmpo);
    }
}

    FreeImage(monImage); 
    printf("Fin\n");
	return 0;
	
}

/*  /// II MANIPULATIONS BASIQUES 
    ///Fonctionnalitées
    ///monImage = NiveauDeGris(monImage);            ///1

    ///monImage = Binarisation(monImage,seuil);   ///2

    ///monImage = Miroir(monImage);    ///3

    ///monImage = Rotation(monImage);  ///4

    ///monImage = Negatif(monImage);   ///5

    histogramme = CreationHistogramme(monImage);                               ///6    ///NIVEAU DE GRIS NECESSAIRE
    ///Affichage du nombre d'occurence => Verif de la bonne récupération des valeurs
    ///for(int Num = 0; Num < 256; Num++){
     /// printf("Le pixel de couleur %d est apparu %d fois\n",Num,histogramme[Num]);
   /// }

    monImage = RecadrageDynamique(monImage,histogramme);              ///7 		////NIVEAU DE GRIS NECESSAIRE

    /// III FILTRAGE
    ///monImage = MatriceIdentite(monImage);  ///1
    ///monImage = MatriceContraste(monImage); ///2
    ///monImage = MatriceFlou(monImage);      ///3
    ///monImage = MatriceContour(monImage);   ///4
*/
