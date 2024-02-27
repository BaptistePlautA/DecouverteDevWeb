/* Auteurs : Théo De Morais, Baptiste Plaut-Aubry, Ayman El kili
 * Date : 20.05.22 */

#include "PROJET.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

void AllocTab(IMAGE* monImage){
        ////Allocation du tab2DDynamique
        monImage->tabpixel2D = malloc(monImage->largeur * sizeof(PIXEL));
        for (int i=0;i<monImage->largeur;i++){
          monImage->tabpixel2D[i] =  malloc(monImage->hauteur * sizeof (PIXEL));
          }
}

IMAGE* CreerTMP(IMAGE* TMP,IMAGE* monImage){
    TMP->signature = malloc(sizeof(char)*3);
    TMP->largeur = monImage->largeur;
    TMP->hauteur = monImage->hauteur;
    AllocTab(TMP);
    /// On clone juste l'image de base pour l'utiliser dans certains fonctions (miroir, rotation)
    for (int ligne = 0 ; ligne < TMP->largeur ; ligne ++ )
        {
            for (int colonne = 0 ; colonne < TMP->hauteur; colonne ++ )
            {
               TMP->tabpixel2D[ligne][colonne].r =monImage->tabpixel2D[ligne][colonne].r;
               TMP->tabpixel2D[ligne][colonne].g =monImage->tabpixel2D[ligne][colonne].g;
               TMP->tabpixel2D[ligne][colonne].b =monImage->tabpixel2D[ligne][colonne].b;
            }
        }

  return TMP;
}

void FreeImage(IMAGE* image){///Libère l'image (tampon + image)
    free(image->tabpixel2D);
    free(image->signature);
    free(image);
}

IMAGE* ChargementPPM(FILE* img_entree,IMAGE* image){    ////////////////////////////////////////////////  I.1./
	
    printf("Entree fonction ChargementPPM\n");
    
    ///Verif de l'image
        if (img_entree == NULL){
      printf("Pas d'image detectee dans ChargementPPM\n");
      exit(0);
    }
        //////////////////////////
        ///Lecture de la signature
        fscanf (img_entree, "%s", image->signature);
        ///printf ( "%s\n", monImage->signature);       ///Test signature
        ///Lecture de la largeur
        fscanf ( img_entree, "%d", &image->largeur);
        ///printf ( "%d largeur\n", monImage->largeur); ///Test largeur
        ///Lecture de la hauteur
        fscanf ( img_entree, "%d", &image->hauteur);
        ///printf ( "%d hauteur\n", monImage->hauteur); ///Test hauteur
        ///Lecture de la couleur max des Pixels
        fscanf ( img_entree, "%d", &image->maxPixel);
        ///printf ( "%d couleurMax\n",monImage->maxPixel);  ///Test couleurmax
        ///printf ( "largeur=%d, hauteur=%d couleurMax=%d\n", monImage->largeur, monImage->hauteur, monImage->maxPixel);  ///Test tout
        //////Lecture de la "Tête"
        //////////////////////////
        AllocTab(image);

        ///////////////////////////////
        for (int ligne = 0 ; ligne < image->largeur ; ligne ++ )
        {
            for (int colonne = 0 ; colonne < image->hauteur; colonne ++ )
            {
               fscanf(img_entree, "%d", &image->tabpixel2D[ligne][colonne].r);
               ///printf ( "valeur PixelRouge: %d\n",monImage->tabpixel2D[ligne][colonne].r);       ///Test red
               fscanf(img_entree, "%d", &image->tabpixel2D[ligne][colonne].g);
               ///printf ( "valeur PixelVert : %d\n",monImage->tabpixel2D[ligne][colonne].g);       ///Test green
               fscanf(img_entree, "%d", &image->tabpixel2D[ligne][colonne].b);
               ////printf ( "valeur PixelBleu : %d\n",monImage->tabpixel2D[ligne][colonne].b);      ///Test blue
            }///Fin for colonne
        }///Fin for ligne
         //////Lecture du Corps de l'image
        /////////////////////////////////
        
      printf("Sortie fonction ChargementPPM\n");
      
      fclose ( img_entree ) ;
    return image;
}

void SauvegardePPM(FILE* img_entree,IMAGE* monImage, char* nomImageSortie, int tmpo){  ////////////////////////////////////////////////  I.2./
	
    printf("Entree fonction SauvegardePPM\n");

    if(tmpo>=1) {

        FILE* img_sortie = fopen(nomImageSortie, "w");

        if(img_sortie){///Réécrit tout ce qui se trouve dans monImage dans une image de sortie
            fprintf(img_sortie, "%s\n",monImage->signature);
            fprintf (img_sortie, "%d %d\n", monImage->largeur,monImage->hauteur);
            fprintf (img_sortie, "%d\n", monImage->maxPixel);
            for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
            {
                for (int colonne = 0 ; colonne < monImage->hauteur ; colonne ++ )
                {
                fprintf(img_sortie, "%d %d %d\n", monImage->tabpixel2D[ligne][colonne].r,
                monImage->tabpixel2D[ligne][colonne].g,
                monImage->tabpixel2D[ligne][colonne].b);
                }///Fin for colonne
            }///Fin for ligne
        }
        else{
            printf("Erreur dans SauvegardePPM\n");
            exit(0);
        }
    }
    else if(!tmpo) {/// Si il n'y pas de -o, on écrit monImage dans le terminal comme demandé

            printf("%s\n",monImage->signature);
            printf ("%d %d\n", monImage->largeur,monImage->hauteur);
            printf ("%d\n", monImage->maxPixel);
            for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
            {
                for (int colonne = 0 ; colonne < monImage->hauteur ; colonne ++ )
                {
                printf("%d %d %d\n", monImage->tabpixel2D[ligne][colonne].r,
                monImage->tabpixel2D[ligne][colonne].g,
                monImage->tabpixel2D[ligne][colonne].b);
                }///Fin for colonne
            }///Fin for ligne
        }
  printf("Sortie fonction SauvegardePPM\n");
}

IMAGE* Croix(IMAGE* monImage, int Xlarge, int Yhaut, int epaisseur){ ////////////////////////////////////////////////  I.3./
  printf("Entree fonction Croix\n");
  if (Xlarge != Yhaut){
    printf(" Malheureusement nous n'avons pas pu réaliser une croix avec une hauteur et une largeur différente, même si le code nous semble algorithmiquement correct. \n");
    return monImage;
  }
  monImage->largeur = Xlarge;
  monImage->hauteur = Yhaut;
  epaisseur = epaisseur/2; ////La division par 2 est nécessaire pour la condition des boucles for 
  free(monImage->tabpixel2D);
  AllocTab(monImage); ///On ne compte pas réutiliser l'image d'entrée donc on peut juste allouer à 0

  ///Fond blanc
  for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
    {
        for (int colonne = 0 ; colonne < monImage->hauteur ; colonne ++ )
        {
           monImage->tabpixel2D[ligne][colonne].r = 255;
           monImage->tabpixel2D[ligne][colonne].g = 255;
           monImage->tabpixel2D[ligne][colonne].b = 255;
        }///Fin for colonne
    }///Fin for ligne

         ///Barre Noire Verticale (on écrit en noir au centre de l'image/2 - l'épaisseur jusqu'à + l'épaisseur = épaisseur initiale)
  for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
    {
        for (int colonne = (monImage->hauteur/2)-epaisseur; colonne < (monImage->hauteur/2)+epaisseur ; colonne ++ )
        {
           monImage->tabpixel2D[ligne][colonne].r = 0;
           monImage->tabpixel2D[ligne][colonne].g = 0;
           monImage->tabpixel2D[ligne][colonne].b = 0;
        }///Fin for colonne
    }///Fin for ligne


       ///Barre Noire Horizontale (on écrit en noir au centre de l'image/2 - l'épaisseur jusqu'à + l'épaisseur = épaisseur initiale)
  for (int ligne = (monImage->largeur/2)-epaisseur ; ligne < (monImage->largeur/2)+epaisseur ; ligne ++ )
    {
        for (int colonne = 0; colonne < monImage->hauteur ; colonne ++ )
        {
           monImage->tabpixel2D[ligne][colonne].r = 0;
           monImage->tabpixel2D[ligne][colonne].g = 0;
           monImage->tabpixel2D[ligne][colonne].b = 0;
        }///Fin for colonne
    }///Fin for ligne
    printf("Sortie Croix\n");
    return monImage;  
}

IMAGE* NiveauDeGris(IMAGE* monImage){ ////////////////////////////////////////////////  II.1./
	
  printf("Entree fonction NiveauDeGris\n");
  
  for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
    {
        for (int colonne = 0 ; colonne < monImage->hauteur ; colonne ++ )
        {  int LuminanceGris  = ((monImage->tabpixel2D[ligne][colonne].r* 0.2126)+(monImage->tabpixel2D[ligne][colonne].g* 0.7152)+(monImage->tabpixel2D[ligne][colonne].b*  0.0722)); ///Def luminance
           monImage->tabpixel2D[ligne][colonne].r = LuminanceGris;
           monImage->tabpixel2D[ligne][colonne].g = LuminanceGris;
           monImage->tabpixel2D[ligne][colonne].b = LuminanceGris;
        }///Fin for colonne
    }///Fin for ligne
    
    printf("Sortie fonction NiveauDeGris\n");
    
    return monImage;  
}

IMAGE* Binarisation(IMAGE* monImage, int seuil){ ////////////////////////////////////////////////  II.2./
	
	printf("Entree binarisation\n");
	
	for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
    {
        for (int colonne = 0 ; colonne < monImage->hauteur ; colonne ++ )
        {
			if((monImage->tabpixel2D[ligne][colonne].r + monImage->tabpixel2D[ligne][colonne].g + monImage->tabpixel2D[ligne][colonne].b)/3  < seuil){ //// [(r+g+b)/3] < seuil
				
				monImage->tabpixel2D[ligne][colonne].r = 0;
				monImage->tabpixel2D[ligne][colonne].g = 0; /// Si le pixel est d'une valeur inférieur au seuil, il devient noir
				monImage->tabpixel2D[ligne][colonne].b = 0;
				
           }else{
			   
			   monImage->tabpixel2D[ligne][colonne].r = 255;
			   monImage->tabpixel2D[ligne][colonne].g = 255; /// Sinon, il devient blanc
			   monImage->tabpixel2D[ligne][colonne].b = 255;
           }

        }///Fin for colonne
    }///Fin for ligne
    
    printf("Sortie binarisation\n");
    return monImage;  
}

IMAGE* Miroir(IMAGE* monImage){ ////////////////////////////////////////////////  II.3./
	
    IMAGE* TMPMiroir;//// On doit créer une image tampon pour ne pas réécrire par dessus l'image de départ
    TMPMiroir = malloc(sizeof(IMAGE)*N);
    TMPMiroir = CreerTMP(TMPMiroir,monImage);
    
    printf("Entree Miroir\n");
    
    for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
    {
		for (int colonne = 0 ; colonne < monImage->hauteur ; colonne ++ )
        {
			monImage->tabpixel2D[ligne][colonne].r =  TMPMiroir->tabpixel2D[ligne][monImage->hauteur-colonne].r; ////Les pixels  à gauche se transposent à droite progressivement
            monImage->tabpixel2D[ligne][colonne].g =  TMPMiroir->tabpixel2D[ligne][monImage->hauteur-colonne].g; 
            monImage->tabpixel2D[ligne][colonne].b =  TMPMiroir->tabpixel2D[ligne][monImage->hauteur-colonne].b;
        }///Fin for colonne
    }///Fin for ligne
    
    FreeImage(TMPMiroir);
    
    printf("Sortie Miroir\n");
	return monImage;  
}

IMAGE* Rotation(IMAGE* monImage){ ////////////////////////////////////////////////  II.4./
	if(monImage->largeur != monImage->hauteur){
    printf("Malheureusement nous nous sommes rendus compte trop tard que cette fonction ne supporte pas une image de dimension largeur!= hauteur \n");
    return monImage;
  }
	IMAGE* TMP90;//// On doit créer une image tampon pour ne pas réécrire par dessus l'image de départ
    TMP90 = malloc(sizeof(IMAGE)*N);
    TMP90 = CreerTMP(TMP90,monImage);
    
    printf("Entree Rotation 90\n");
    
    for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
    {
		for (int colonne = 0 ; colonne < monImage->hauteur ; colonne ++ )
		{
			monImage->tabpixel2D[ligne][colonne].r =  TMP90->tabpixel2D[monImage->hauteur-colonne-1][ligne].r;  ////On inverse les lignes et colonne pour obtenir une rotation 90
            monImage->tabpixel2D[ligne][colonne].g =  TMP90->tabpixel2D[monImage->hauteur-colonne-1][ligne].g;
            monImage->tabpixel2D[ligne][colonne].b =  TMP90->tabpixel2D[monImage->hauteur-colonne-1][ligne].b;
        }///Fin for colonne
    }///Fin for ligne
    
    FreeImage(TMP90);
    
    printf("Sortie Rotation 90\n");
	return monImage;  
}

IMAGE* Negatif(IMAGE* monImage){ ////////////////////////////////////////////////  II.5./
	
	printf("Entree negatif\n");
	for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
	{
		for (int colonne = 0 ; colonne < monImage->hauteur ; colonne ++ )
		{  
			monImage->tabpixel2D[ligne][colonne].r = 255 - monImage->tabpixel2D[ligne][colonne].r;
            monImage->tabpixel2D[ligne][colonne].g = 255 - monImage->tabpixel2D[ligne][colonne].g;////Effet négatif
            monImage->tabpixel2D[ligne][colonne].b = 255 - monImage->tabpixel2D[ligne][colonne].b;
        }///Fin for colonne
    }///Fin for ligne
    
    printf("Sortie negatif\n");
    return monImage;  
}

int* CreationHistogramme(IMAGE* ImageGrise){ ////////////////////////////////////////////////  II.6./ (3.1 Bonus essai)
	
  printf("Entree fonction CreationHistogramme\n");

  ///Initialisation de toutes les cases à 0
  int* histo = malloc (sizeof (int*) * 256);
  for(int i = 0; i<ImageGrise->maxPixel; i++){
    histo[i]=0;
  }

  for (int ligne = 0 ; ligne < ImageGrise->largeur ; ligne ++ )
    {
        for (int colonne = 0 ; colonne < ImageGrise->hauteur ; colonne ++ )
        {  
          histo[ImageGrise->tabpixel2D[ligne][colonne].r]++;  ////r, g , b sont censés avoir la même valeur donc on peut choisir un des 3
        }///Fin for colonne
    }///Fin for ligne

  ///Essais GNUPLOT (non fructueux pas réussi à faire fonctionner sous windows)
  /* 
  FILE *histog = popen("histogramme.png"", "w");
    	if (!histog) {
        	perror("popen");
        	exit(0);
    	}
    	fprintf(histog, “set title' Histogramme de luminance'\n”);
      fprintf(histog, “set xlabel ' Nb occurences'\n”);
      fprintf(histog,  “set ylabel 'Valeur de luminance'\n”);
      fprintf(histog,  "plot '-' u 1:2 t hist.dat\n");
      fprintf(histog, “set style data histogram\n”); <- marchait pas

    	for (int i = 0; i < 256; ++i) {
        	fprintf(histog,"%d %d\n", i,histo[i]);
    	}
    	fprintf(histog, "\n");
    	fflush(histog);
    	pclose(histog);
    	exit(1);
*/

  printf("Sortie fonction CreationHistogramme\n");
  return histo;
}

IMAGE* RecadrageDynamique(IMAGE* monImage,int* histogramme){ ////////////////////////////////////////////////  II.7./
	
  printf("Entree fonction RecadrageDynamique\n");
  
  float Max =0;
  float Min =histogramme[0];
  float MaxLum =0;
  float MinLum =0;
  ///int Luminance; 

  /// On récupère les valeurs qui apparaissent le plus et le moins de fois
  for (int i=0; i<monImage->maxPixel; i++){
    if (histogramme[i]>Max){
      Max = histogramme[i];
      MaxLum = i;
    }
    else if(histogramme[i]<Min) {
      Min = histogramme[i];
      MinLum =i;
    }
  }

  float Delta = 255/(MaxLum-MinLum);
  ////Cas où la Valeur de MinLum > MaxLum
  if (Delta < 0){
    Delta = -Delta; /// Si MinLum > MaxLum
  }
  printf("MaxLum = %f\n",MaxLum);
  printf("MinLum = %f\n",MinLum);
  printf("Delta = %f\n",Delta);


  for (int ligne = 0 ; ligne < monImage->largeur ; ligne ++ )
    {
        for (int colonne = 0 ; colonne < monImage->hauteur ; colonne ++ )
        {  int LuminanceXY = (((monImage->tabpixel2D[ligne][colonne].r* 0.2126)+(monImage->tabpixel2D[ligne][colonne].g* 0.7152)+(monImage->tabpixel2D[ligne][colonne].b*  0.0722))-MinLum)*Delta; ///Def lumXY
           monImage->tabpixel2D[ligne][colonne].r = LuminanceXY;
           monImage->tabpixel2D[ligne][colonne].g = LuminanceXY;
           monImage->tabpixel2D[ligne][colonne].b = LuminanceXY;
        }///Fin for colonne
    }///Fin for ligne
    
    printf("Sortie fonction RecadrageDynamique\n");
return monImage;  
}

IMAGE* PrdtConvolution(IMAGE* monImage,float** Filtre){ ////////////////////////////////////////////////  III
	
  printf("Debut PrdtConvolution\n");
  
   for (int x = 2 ; x < monImage->largeur-2 ; x ++ )
    {
        for (int y = 2 ; y < monImage->hauteur-2 ; y ++ )
        {  
          monImage->tabpixel2D[x-1][y-1].r =  abs(monImage->tabpixel2D[x+1][y+1].r*Filtre[0][0]+   monImage->tabpixel2D[x][y+1].r*Filtre[0][1]+  monImage->tabpixel2D[x-1][y+1].r*Filtre[0][2]+ ///Produit de convolution par le filtre 3x3
                                                    monImage->tabpixel2D[x+1][y].r*Filtre[1][0]+     monImage->tabpixel2D[x][y].r*Filtre[1][1]+    monImage->tabpixel2D[x-1][y].r*Filtre[1][2]+
                                                  monImage->tabpixel2D[x+1][y-1].r*Filtre[2][0]+   monImage->tabpixel2D[x][y-1].r*Filtre[2][1]+  monImage->tabpixel2D[x-1][y-1].r*Filtre[2][2]);

          monImage->tabpixel2D[x-1][y-1].g =  abs(monImage->tabpixel2D[x+1][y+1].g*Filtre[0][0]+   monImage->tabpixel2D[x][y+1].g*Filtre[0][1]+  monImage->tabpixel2D[x-1][y+1].g*Filtre[0][2]+ 
                                                    monImage->tabpixel2D[x+1][y].g*Filtre[1][0]+     monImage->tabpixel2D[x][y].g*Filtre[1][1]+    monImage->tabpixel2D[x-1][y].g*Filtre[1][2]+
                                                  monImage->tabpixel2D[x+1][y-1].g*Filtre[2][0]+   monImage->tabpixel2D[x][y-1].g*Filtre[2][1]+  monImage->tabpixel2D[x-1][y-1].g*Filtre[2][2]);

          monImage->tabpixel2D[x-1][y-1].b = abs(monImage->tabpixel2D[x+1][y+1].b*Filtre[0][0]+   monImage->tabpixel2D[x][y+1].b*Filtre[0][1]+  monImage->tabpixel2D[x-1][y+1].b*Filtre[0][2]+ 
                                                   monImage->tabpixel2D[x+1][y].b*Filtre[1][0]+     monImage->tabpixel2D[x][y].b*Filtre[1][1]+    monImage->tabpixel2D[x-1][y].b*Filtre[1][2]+
                                                 monImage->tabpixel2D[x+1][y-1].b*Filtre[2][0]+   monImage->tabpixel2D[x][y-1].b*Filtre[2][1]+  monImage->tabpixel2D[x-1][y-1].b*Filtre[2][2]);

        }///Fin for colonne
    }///Fin for ligne
    
    printf("Fin PrdtConvolution\n");
  return monImage;
}

IMAGE* MatriceIdentite(IMAGE* monImage){   ////////////////////////////////////////////////  III.1/
	
  printf("Debut MatriceIdentite\n");
  
  float** FiltreIdentite = malloc(3 * sizeof(int));///Float nécessaire pour le flou et on devrait créer des produits différents si on utilisait un float que pour le flou
  for (int i=0;i<3;i++){
        FiltreIdentite[i] =  malloc(3 * sizeof (int));
  };
  FiltreIdentite[0][0] = 0;///Filtre Identité
  FiltreIdentite[0][1] = 0;
  FiltreIdentite[0][2] = 0;
  FiltreIdentite[1][0] = 0;
  FiltreIdentite[1][1] = 1;
  FiltreIdentite[1][2] = 0;
  FiltreIdentite[2][0] = 0;
  FiltreIdentite[2][1] = 0;
  FiltreIdentite[2][2] = 0;
  PrdtConvolution(monImage,FiltreIdentite);
  
  printf("Fin MatriceIdentite\n");
  return monImage;
}

IMAGE* MatriceContraste(IMAGE* monImage){   ////////////////////////////////////////////////  III.2/ 
	
  printf("Debut MatriceContraste\n");
  
  float** FiltreContraste = malloc(3 * sizeof(int));
  for (int i=0;i<3;i++){
        FiltreContraste[i] =  malloc(3 * sizeof (int));
  };
  FiltreContraste[0][0] = 0;
  FiltreContraste[0][1] =-1;///Filtre Contraste
  FiltreContraste[0][2] = 0;
  FiltreContraste[1][0] =-1;
  FiltreContraste[1][1] = 5;
  FiltreContraste[1][2] =-1;
  FiltreContraste[2][0] = 0;
  FiltreContraste[2][1] =-1;
  FiltreContraste[2][2] = 0;
  PrdtConvolution(monImage,FiltreContraste);
  
  printf("Fin MatriceContraste\n");
  return monImage;
}

IMAGE* MatriceFlou(IMAGE* monImage){   ////////////////////////////////////////////////  III.3/
	
  printf("Debut MatriceFlou\n");
  
  float** FiltreFlou = malloc(3 * sizeof(int));
  for (int i=0;i<3;i++){
        FiltreFlou[i] =  malloc(3 * sizeof (int));
  };
  FiltreFlou[0][0] = 0.0625;
  FiltreFlou[0][1] = 0.125;
  FiltreFlou[0][2] = 0.0625;///Filtre flou
  FiltreFlou[1][0] = 0.125;
  FiltreFlou[1][1] = 0.25;
  FiltreFlou[1][2] = 0.125;
  FiltreFlou[2][0] = 0.0625;
  FiltreFlou[2][1] = 0.125;
  FiltreFlou[2][2] = 0.0625;

  PrdtConvolution(monImage,FiltreFlou);
  
  printf("Fin MatriceFlou\n");
  return monImage;
}

IMAGE* MatriceContour(IMAGE* monImage){   ////////////////////////////////////////////////  III.4/
	
  printf("Debut MatriceContour\n");
  
  float** FiltreContour = malloc(3 * sizeof(int));
  for (int i=0;i<3;i++){
        FiltreContour[i] =  malloc(3 * sizeof (int));
  };
  FiltreContour[0][0] = -1;
  FiltreContour[0][1] = -1;///Filtre contour
  FiltreContour[0][2] = -1;
  FiltreContour[1][0] = -1;
  FiltreContour[1][1] =  8;
  FiltreContour[1][2] = -1;
  FiltreContour[2][0] = -1;
  FiltreContour[2][1] = -1;
  FiltreContour[2][2] = -1;
  PrdtConvolution(monImage,FiltreContour);
  
  printf("Fin MatriceContour\n");
  return monImage;
}



IMAGE* Erosion(IMAGE* monImage, CROIX* maCroix){
  printf("Debut Erosion\n");
  int min = 255;
  monImage = NiveauDeGris(monImage);
  /*maCroix->TabCroix ={0,0,1,0,0
                        0,0,1,0,0
                        1,1,1,1,1
                        0,0,1,0,0
                        0,0,1,0,0} Représentation de la croix
  maCroix->TabCroix[0][0] = 0, maCroix->TabCroix[0][1] = 0, maCroix->TabCroix[0][2] = 1, maCroix->TabCroix[0][3] = 0,maCroix->TabCroix[0][4] = 0;
  maCroix->TabCroix[1][0] = 0, maCroix->TabCroix[1][1] = 0, maCroix->TabCroix[1][2] = 1, maCroix->TabCroix[1][3] = 0,maCroix->TabCroix[1][4] = 0;
  maCroix->TabCroix[2][0] = 1, maCroix->TabCroix[2][1] = 1, maCroix->TabCroix[2][2] = 1, maCroix->TabCroix[2][3] = 1,maCroix->TabCroix[2][4] = 1;
  maCroix->TabCroix[3][0] = 0, maCroix->TabCroix[3][1] = 0, maCroix->TabCroix[3][2] = 1, maCroix->TabCroix[3][3] = 0,maCroix->TabCroix[3][4] = 0;
  maCroix->TabCroix[4][0] = 0, maCroix->TabCroix[4][1] = 0, maCroix->TabCroix[4][2] = 1, maCroix->TabCroix[4][3] = 0,maCroix->TabCroix[4][4] = 0;*/

  for (int x = 2 ; x < monImage->largeur-2 ; x ++ )
    { 
        for (int y = 2 ; y < monImage->hauteur-2 ; y ++ )
        { min = 255;

              if(monImage->tabpixel2D[x][y-2].r < min){//maCroix->TabCroix[2][0] = 1
                min = monImage->tabpixel2D[x][y-2].r;
              }
              if(monImage->tabpixel2D[x][y-1].r < min){//maCroix->TabCroix[2][1] = 1
                min = monImage->tabpixel2D[x][y-1].r;
              }
              if(monImage->tabpixel2D[x-2][y].r < min){//maCroix->TabCroix[0][2] = 1
                min = monImage->tabpixel2D[x-2][y].r;
              }
              if(monImage->tabpixel2D[x-1][y].r < min){//maCroix->TabCroix[1][2] = 1
                min = monImage->tabpixel2D[x-1][y].r;
              }
              if(monImage->tabpixel2D[x][y].r < min){//maCroix->TabCroix[2][2] = 1
                min = monImage->tabpixel2D[x][y].r;
              }
              if(monImage->tabpixel2D[x+1][y].r < min){//maCroix->TabCroix[3][2] = 1
                min = monImage->tabpixel2D[x+1][y].r;
              }
              if(monImage->tabpixel2D[x+2][y].r < min){//maCroix->TabCroix[4][2] = 1
                min = monImage->tabpixel2D[x+2][y].r;
              }
              if(monImage->tabpixel2D[x][y+1].r < min){//maCroix->TabCroix[2][3] = 1
                min = monImage->tabpixel2D[x][y+1].r;
              }
              if(monImage->tabpixel2D[x][y+2].r < min){//maCroix->TabCroix[2][4] = 1
                min = monImage->tabpixel2D[x][y+2].r;
              }
            

          monImage->tabpixel2D[x-2][y-2].r = min;
          monImage->tabpixel2D[x-2][y-2].g = min;/// Le pixel du milieu prend la plus petite valeur dans une croix de 2 autour de lui même
          monImage->tabpixel2D[x-2][y-2].b = min;
        }///Fin for ligne
      } ///Fin for colonne


  printf("Fin Erosion\n");
  return monImage;
}

IMAGE* Dilatation(IMAGE* monImage, CROIX* maCroix){
  printf("Debut Dilatation\n");
  int max = 0;
  monImage = NiveauDeGris(monImage);
  /*maCroix->TabCroix ={0,0,1,0,0
                        0,0,1,0,0
                        1,1,1,1,1
                        0,0,1,0,0
                        0,0,1,0,0} Représentation de la croix
  maCroix->TabCroix[0][0] = 0, maCroix->TabCroix[0][1] = 0, maCroix->TabCroix[0][2] = 1, maCroix->TabCroix[0][3] = 0,maCroix->TabCroix[0][4] = 0;
  maCroix->TabCroix[1][0] = 0, maCroix->TabCroix[1][1] = 0, maCroix->TabCroix[1][2] = 1, maCroix->TabCroix[1][3] = 0,maCroix->TabCroix[1][4] = 0;
  maCroix->TabCroix[2][0] = 1, maCroix->TabCroix[2][1] = 1, maCroix->TabCroix[2][2] = 1, maCroix->TabCroix[2][3] = 1,maCroix->TabCroix[2][4] = 1;
  maCroix->TabCroix[3][0] = 0, maCroix->TabCroix[3][1] = 0, maCroix->TabCroix[3][2] = 1, maCroix->TabCroix[3][3] = 0,maCroix->TabCroix[3][4] = 0;
  maCroix->TabCroix[4][0] = 0, maCroix->TabCroix[4][1] = 0, maCroix->TabCroix[4][2] = 1, maCroix->TabCroix[4][3] = 0,maCroix->TabCroix[4][4] = 0;*/

  for (int x = 2 ; x < monImage->largeur-2 ; x ++ )
    { 
        for (int y = 2 ; y < monImage->hauteur-2 ; y ++ )
        { max = 0;

              if(monImage->tabpixel2D[x][y-2].r > max){//maCroix->TabCroix[2][0] = 1
                max = monImage->tabpixel2D[x][y-2].r;
              }
              if(monImage->tabpixel2D[x][y-1].r > max){//maCroix->TabCroix[2][1] = 1
                max = monImage->tabpixel2D[x][y-1].r;
              }
              if(monImage->tabpixel2D[x-2][y].r > max){//maCroix->TabCroix[0][2] = 1
                max = monImage->tabpixel2D[x-2][y].r;
              }
              if(monImage->tabpixel2D[x-1][y].r > max){//maCroix->TabCroix[1][2] = 1
                max = monImage->tabpixel2D[x-1][y].r;
              }
              if(monImage->tabpixel2D[x][y].r > max){//maCroix->TabCroix[2][2] = 1
                max = monImage->tabpixel2D[x][y].r;
              }
              if(monImage->tabpixel2D[x+1][y].r > max){//maCroix->TabCroix[3][2] = 1
                max = monImage->tabpixel2D[x+1][y].r;
              }
              if(monImage->tabpixel2D[x+2][y].r > max){//maCroix->TabCroix[4][2] = 1
                max = monImage->tabpixel2D[x+2][y].r;
              }
              if(monImage->tabpixel2D[x][y+1].r > max){//maCroix->TabCroix[2][3] = 1
                max = monImage->tabpixel2D[x][y+1].r;
              }
              if(monImage->tabpixel2D[x][y+2].r > max){//maCroix->TabCroix[2][4] = 1
                max = monImage->tabpixel2D[x][y+2].r;
              }
            

          monImage->tabpixel2D[x-2][y-2].r = max;
          monImage->tabpixel2D[x-2][y-2].g = max;/// Le pixel du milieu prend la plus grande valeur dans une croix de 2 autour de lui même
          monImage->tabpixel2D[x-2][y-2].b = max;
        }///Fin for ligne
      } ///Fin for colonne


  printf("Fin Dilatation\n");
  return monImage;
}

