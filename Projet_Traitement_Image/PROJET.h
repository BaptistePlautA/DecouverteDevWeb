#ifndef __PROJET_h_
#define __PROJET_h_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

////Notes persos pour le groupe : Structures en MAJ, Variables en min

/////STRUCTURE
/* Auteur : Baptiste PLAUT-AUBRY, El Kili Ayman, De Morais Théo
 * Date : 20 mai 2022
 * Resume :structure contenant les différentes composantes d'un PIXEL (rouge,vert et bleu)
 * Entree :-----
 * Sortie :-----
 */

typedef struct{
  int r; ///rouge
  int g; ///vert
  int b; ///bleu
} PIXEL;
////STRUCTURE
/* Auteur : Baptiste PLAUT-AUBRY, El Kili Ayman, De Morais Théo
 * Date : 20 mai 2022
 * Resume :structure contenant les différentes composantes d'une image en PIXEl présentée dans un tableau 2D ( hauteur,largeur,maxPixel,signature et le tableau 2D "tabpixel2D)
 * Entree :-----
 * Sortie :-----
 */

typedef struct{
    int hauteur;
    int largeur;
    int maxPixel;
    char* signature;
    PIXEL** tabpixel2D;
} IMAGE;


////STRUCTURE
/* Auteur : Baptiste PLAUT-AUBRY, El Kili Ayman, De Morais Théo
 * Date : 20 mai 2022
 * Resume :structure de croix, demandée pour l'érosion et la dillatation composée d'un tableau 2D
 * Entree :-----
 * Sortie :-----
 */
typedef struct{
  int** TabCroix;
} CROIX;

/////////////////////////////////////////////////////////////////////////////////////////////////////MAIN : 


/////////////////////////////////////////////////////////////////////////////////////////////////////FONCTIONS : 

/* Auteur : Baptiste PLAUT-AUBRY
 * Date : 25  mai 2022
 * Resume :Procédure permettant d'Allouer un tableau dynamique "2 Dimensions"
 * Entree :image avec une largeur et une hauteur
 * Sortie :tableau dynamique 2D alloué
 */
void AllocTab(IMAGE* monImage);



/* Auteur : Baptiste PLAUT-AUBRY
 * Date : 25  mai 2022
 * Resume :fonction permettant de copier les informations d'une image et les coller dans une autre image ,qu'il faut retourner à la fin
 * Entree :image avec une hauteur et largeur
 * Sortie :image 
 */
IMAGE* CreerTMP(IMAGE* TMP,IMAGE* monImage);



/* Auteur : Baptiste PLAUT-AUBRY
 * Date : 25  mai 2022
 * Resume :procédure permettant de libérer un tableau 2 dimension qu'une image conient
 * Entree :une image
 * Sortie :tableau 2D de l'image libéré
 */
void FreeImage(IMAGE* image);



/* Auteur : Baptiste PLAUT-AUBRY
 * Date : 21,22,23  mai 2022
 * Resume :fonction permettant de charger une image depuis un fichier; qui prend en paramètre le fichier et qui retourne une structure d’image initialisés aux valeurs correctes d'après le fichier image
 * Entree :fichier 
 * Sortie :image 
 */
IMAGE* ChargementPPM(FILE* img_entree,IMAGE* image); ////////////////////////////////////////////////  I.1./



/* Auteur : Baptiste PLAUT-AUBRY
 * Date : 24  mai 2022
 * Resume : une fonction permettant de sauvegarder une image dans un fichier.ppm, qui prend en paramètre: (img : une structure d’image), (nom : le nom du fichier de sauvegarde) et qui retourne 0 si la sauvegarde a échouée, 1 sinon 
 * Entree :image à sauvegarder et nom du fichier
 * Sortie :image sauvegardée
 */
void SauvegardePPM(FILE* img_entree,IMAGE* monImage, char* nomImageSortie, int tmpo); ////////////////////////////////////////////////  I.2./

/* Auteur : Baptiste PLAUT-AUBRY
 * Date : 24  mai 2022
 * Resume : Ecrire une fonction qui crée une image représentant une croix
 * Entree :image, largeur, epaisseur, epaisseur
 * Sortie :image sauvegardée
 */
IMAGE* Croix(IMAGE* monImage, int Xlarge, int Yhaut, int epaisseur);

/* Auteur : Baptiste PLAUT-AUBRY
 * Date : 25  mai 2022
 * Resume :une procédure qui transforme une image couleur en une image en niveau de gris qui prend en paramètre une structure contenant l’image en couleur
 * Entree :image en couleur 
 * Sortie :image en niveau gris
 */
IMAGE* NiveauDeGris(IMAGE* monImage); ////////////////////////////////////////////////  II.1./



/* Auteur : Baptiste PLAUT-AUBRY
 * Date : 25  mai 2022
 * Resume : une procédure qui réalise la binarisation d’une image qui prend en paramètre :(img : une structure contenant l’image en couleur), (seuil : le seuil utilisé pour la binarisation)
 * Entree :image en couleur et le seuil utilisé pour la binarisation
 * Sortie :image binarisée
 */
IMAGE* Binarisation(IMAGE* monImage, int seuil); ////////////////////////////////////////////////  II.2./



/* Auteur : Baptiste PLAUT-AUBRY, Theo De Morais
 * Date : 25  mai 2022
 * Resume :procédure permettant de réaliser le miroir d’une image.
 * Entree :image
 * Sortie :image en miroir
 */
IMAGE* Miroir(IMAGE* monImage); ////////////////////////////////////////////////  II.3./


/* Auteur : Baptiste PLAUT-AUBRY
 * Date : 25  mai 2022
 * Resume :une procédure qui pivote l’image de 90° dans le sens horaire.
 * Entree :image à  pivoter
 * Sortie :image pivotée
 */
IMAGE* Rotation(IMAGE* monImage); ////////////////////////////////////////////////  II.4./



/* Auteur : Baptiste PLAUT-AUBRY, 
 * Date : 25  mai 2022
 * Resume :une procédure permettant de réaliser le négatif d’une image (par rapport à sa valeur de luminance maximum)
 * Entree :image en couleur
 * Sortie :image en négative
 */
IMAGE* Negatif(IMAGE* monImage); ////////////////////////////////////////////////  II.5./



/* Auteur : Baptiste PLAUT-AUBRY, Ayman EL KILI 
 * Date : 26  mai 2022
 * Resume :une fonction qui prend en paramètre l’image à traiter en niveaux de gris et qui retourne l’histogramme de l’image
 * Entree :image en niveaux de gris
 * Sortie :histogrme de l'image
 */
int* CreationHistogramme(IMAGE* ImageGrise); ////////////////////////////////////////////////  II.6./ 3.1 Bonus 



/* Auteur : Baptiste PLAUT-AUBRY, Ayman EL KILI 
 * Date : 26  mai 2022
 * Resume :une procédure permettant de recadrer dynamiquement l’image passée en paramètre
 * Entree :image
 * Sortie :image recadrée dynamiquement
 */
IMAGE* RecadrageDynamique(IMAGE* monImage,int* histogramme); ////////////////////////////////////////////////  II.7./


/* Auteur : Baptiste PLAUT-AUBRY, 
 * Date : 26  mai 2022
 * Resume :une procédure qui réalise le produit de convolution
 * Entree : (img : L’image initiale) + (filtre : une matrice de convolution)
 * Sortie :-----
 */
IMAGE* PrdtConvolution(IMAGE* monImage,float** Filtre); ////////////////////////////////////////////////  III



/* Auteur : Baptiste PLAUT-AUBRY, 
 * Date : 26  mai 2022
 * Resume :fonction permettant de créer une matrice indentité
 * Entree :image
 * Sortie :image avec la matrice identité
 */
IMAGE* MatriceIdentite(IMAGE* monImage);   ////////////////////////////////////////////////  III.1/



/* Auteur : Baptiste PLAUT-AUBRY, 
 * Date : 26  mai 2022
 * Resume :une procédure permettant de renforcer le contraste d’une image
 * Entree :image initiale
 * Sortie :image avec renforcement de contraste
 */
IMAGE* MatriceContraste(IMAGE* monImage);   ////////////////////////////////////////////////  III.2/ 



/* Auteur : Baptiste PLAUT-AUBRY, 
 * Date : 26  mai 2022
 * Resume : une procédure qui floute une image
 * Entree :image initiale
 * Sortie :image avec du floutage
 */
IMAGE* MatriceFlou(IMAGE* monImage);   ////////////////////////////////////////////////  III.3/



/* Auteur : Baptiste PLAUT-AUBRY, 
 * Date : 26  mai 2022
 * Resume :procédure permettant de mettre en évidence les contours des éléments présents dans une image
 * Entree :image initiale
 * Sortie :image contourée
 */
IMAGE* MatriceContour(IMAGE* monImage);   ////////////////////////////////////////////////  III.4/


/* Auteur : Baptiste PLAUT-AUBRY, 
 * Date : 04  juin 2022
 * Resume : fonction qui applique une érosion sur une image qui prend en paramètre l’image initiale ainsi que la structure de croix de taille 5.
 * Entree :image initiale
 * Sortie :image erodée & croix
 */
IMAGE* Erosion(IMAGE* monImage, CROIX* maCroix);

/* Auteur : Baptiste PLAUT-AUBRY, 
 * Date : 04  juin 2022
 * Resume : fonction  qui applique une dilatation sur une image qui prend en paramètre l’image initiale ainsi que la structure de croix de taille 5.
 * Entree :image initiale
 * Sortie :image dilatée & croix
 */
IMAGE* Dilatation(IMAGE* monImage, CROIX* maCroix);
#endif
