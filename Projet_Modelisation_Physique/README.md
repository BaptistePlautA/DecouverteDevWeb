# BE Rapport de Resolution : README

###  Auteurs : Baptiste PLAUT-AUBRY, Team TAB

### Ce qui a été utilisé:

**Outils utilisés :** C, gnuplot, gitlab, Shell, GSL 


##  Fichiers présents dans le gitlab :
    #### Compilation et Compréhension
    · BE.sh
    · makefile
    · README.md	

    #### Fonction principales
    · fonctionsBE.c	
    · fonctionsBE.h	
    · main.c	

    #### Scripts Gnuplot
    · LDC+EQUI.gpi 	
    · data_field.gpi	
    · data_field_duo.gpi	
    · data_field_quatuor.gpi
    · data_potential.gpi	
    · data_potential_duo.gpi
    · data_potential_quatuor.gpi
---------------------------------------------

## Execution du programme : 
    Rentrer dans le terminal
    1.Script Shell: sh BE.sh
    2.Programme C : Entrer la taille de grille voulue (= longueur de l'axe positif + négatif)
    3.Observer les graphs dans le répertoire "Graphs"

    Note : IL N'Y A PAS DE PRISE D'ARGUMENTS X,Y,Q pour éviter de demander 20 variables à chaque execution 
    => Modification des variables : 
    Modifier la précision/résolution : (Directement dans le main.c)
    Fonction 1 charge : (Directement dans le main.c)
    Fonction 2 & 4 charges : Directement dans fonctionsBE.c aux emplacements associés
    Fonction LDC+EQUI : Variables fixes, à modifier dans LDC+EQUI.gpi si besoin
    (C'est plus ou moins un choix de programmation : On ne prend pas de fichiers avec des variables car cela aurait impacté la lisibilité du code vu le nombre de variables)
-----------------------------------

## -----Nous Contacter-----
    Baptiste Plaut-Aubry 
    Ayman El Kili
    Theo De Morais
    plautaubry@cy-tech.fr
    elkiliayma@cy-tech.fr
    demoraisth@cy-tech.fr
-------------------------

