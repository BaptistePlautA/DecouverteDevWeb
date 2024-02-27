
 

# ---------------TRAITEMENT D'IMAGE PPM---------------

#  Auteur : Baptiste PLAUT-AUBRY, El Kili Ayman, De Morais Théo
  Date : 20 mai 2022 - 05/06 2022
  Resume :Programme permettant d'appliquer différents effet sur une image d'entrée de type ppm(p3), qui renvoie une image modifiée avec les fonctions appliquées

## ----- Language de programmation : C -----

## ----- Fichiers présents dans le git : -----
    makefile
    RecupDonnees.c (équivalent fonction.c)
    main.c
    projet.h (équivalent fonction.h)
    readme
---------------------------------------------

## -----Execution du programme : -----
  Rentrer dans le terminal
  make 
  exécuter ./img pour voir les aides sur le projet
  EXEMPLE d'éxecution : ./img -i bender.ppm -e -d -f -m -o image_sortie.ppm
---------------------------------------------

 Ci-dessous la liste des options utilisables :


## ----- Manuel sur les commandes utilisables -----
  La syntaxe est la suivante : ./<executable> <option> (possibilite de mettre plusieurs options de suite)
  OPTIONS :
  -h <option>: affiche une aide sur le programme, quitte le programme avec un code de retour egal a 0 et doit suivre l'executable 
  -b <seuil>: binarise une image 
  -c : realise un renforcement de contraste
  -d : realise une dilatation 
  -e : realise une erosion
  -f : realise un flou
  -i <fichier> : definit le fichier d'entree, OBLIGATOIRE (sauf si -h utilisee) 
  -l : realise une detection de contours/lignes 
  -g : convertit l'image en niveau de gris
  -o <fichier> : definit le fichier de sortie 
  -r : realise un recadrage dynamique 
  -x <largeur> <hauteur> <epaisseur> : realise une croix (Ne MARCHE bien QUE POUR LARGEUR == HAUTEUR ) : bug qui sera corrigé dans une version future v1.02 du programme
  -m : realise le miroir d une image 
  -n : realise le negatif d une image 
  -p : pivote une image de 90 degres dans le sens horaire (Ne MARCHE bien QUE POUR LARGEUR == HAUTEUR ) : bug qui sera corrigé dans une version future v1.02 du programme

## -----Nous Contacter-----
  Baptiste Plaut-Aubry 
  plautaubry@cy-tech.fr

  Ayman El Kili
  elkiliayma@cy-tech.fr

  Theo De Morais
  demoraisth@cy-tech.fr
-------------------------
