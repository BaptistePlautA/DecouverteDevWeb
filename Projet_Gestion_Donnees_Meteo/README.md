# Projet CYMeteo
Le but de ce projet est de réaliser une application qui va traiter un fichier de données météorologiques, dans le but d’afficher des graphiques.\
Le programme va demander à plusieurs reprises à l'utilisateur de saisir les options qu'il veut utiliser pour réaliser le graphique.

###  Auteurs : Baptiste PLAUT-AUBRY, El Kili Ayman, De Morais Théo

### Ce qui a été utilisé:

**Outils nécessaires au fonctionnement :** C, Shell, gnuplot, git

##  Fichiers présents dans le git : 
    AffichageExclu.sh
    CYMeteo.sh
    fonctions.c
    fonctions.h
    main.c
    makefile
    readme
    le rapport de projet au format pdf
    tableau.csv (Votre fichier d'entrée qui sera utilisé)
---------------------------------------------

## Execution du programme : 
    Rentrer dans le terminal
    1.Script Shell: sh CYMeteo.sh
    2.Programme C : --help / -i <montableau.csv> <option> <mode>(ssi -t,-p) 
    3.Script Shell : --help / <optionGeographique> -d <min> <max> -<a> <min> <max> -g <min> <max>
    4.Création du graphique associé dans le répertoire courant
-----------------------------------


## Exemple d'execution :
    sh CYMeteo.sh
    -i meteo_filtered_data_v1.csv -o mesMesures.csv -t 1
    -F -d 2010-05-15 2012-07-18 -a 0 44 -g 0 7

Dans cet exemple, le programme utilise le fichier d'entrée "meteo_filtered_data_v1.csv", et nomme "mesMesures.csv" le fichier de sortie.\
Le programme C traite les témpératures avec le mode 1 envoyant comme instruction de créer un diagramme barres d'erreur.\
Ensuite le script trie les données du csv pour qu'elles correspondent à celles de la France et qu'elles correspondent aux réglages liés à la date à la latitude et à la longitude

### Ci-dessous la liste des options utilisables dans le programme C (2.) :

    --help : affiche une aide sur toutes les options utilisables.
    -i <nom_fichier> : Obligatoire.Permet de specifier le chemin du fichier CSV d'entrée. Cette option est obligatoire et nécessite l'utilisation d'une autre option afin de traiter le fichier.
    -o <nom_fichier> :Optionnel.Permet de donner un nom au fichier de sortie contenant les données.
    Si les options utilisées nécessitent plusieurs fichiers, cet argument peut servir à definir le préfixe des fichiers de sortie.Si l'option -o n'est pas utilisée, le fichier de sortie s'appellera meteo1234.dat
    __________________________________________________________________________________________
    Les options suivantes sont exclusives. Plus précisement, si l'une d'elle est présente, les autres ne doivent pas l'être. En même temps, il faut que l'une d'entre elles soit absolument utilisée :
    -w : Produit en sortie l'orientation moyenne et la vitesse moyenne des vents pour chaque station. Les données seront triées par identifiant croissant de la station.
    -h : Produit en sortie la hauteur pour chaque station. Les hauteurs seront triées par ordre décroissant.
    -m : Produit en sortie l'humidité maximale pour chaque station. Les valeurs d'humidités seront triées par ordre décroissant.
    
    -t <mode> : Températures.
    -p <mode> : Pressions atmosphériques.
    Pour ces 2 options, il faut indiquer la valeur de <mode> :
    1 : Produit en sortie les températures (ou pressions) minimales, maximales et moyennes par station par ordre croissant du numero de station.
    2 : Produit en sortie les températures (ou pressions) moyennes par date/heure par ordre chronologique. La moyenne se fait sur toutes les stations.
    3 : Produit en sortie les températures (ou pressions) par date/heure par station. Elles seront triées d'abord par ordre chronologique, puis par identifiant croissant de la station.

-----------------------------

### Ci-dessous la liste des options utilisables dans le programme Shell (3.) :
    Les options suivantes sont exclusives. Plus précisement, si l'une d'elle est présente, les autres ne doivent pas l'être.
    Il est toutefois  possible de ne pas mettre d'option exclusive pour ne pas limite la zone géographique des mesures.

    -F : limitation des mesures à celles présentes en France métropolitaine + Corse
    -G : limitation des mesures à celles présentes en Guyane
    -S : limitation des mesures à celles présentes à Saint-Pierre-et-Miquelon (Est-Canada)
    -A : limitation des mesures à celles présentes aux Antilles (Martinique et Guadeloupe)
    -O : limitation des mesures à celles présentes dans l’Océan Indien (Mayotte et La Réunion)
    -Q activée : limitation des mesures à celles présentes en Antarctique (TAAF)
    
    __________________________________________________________________________________________
    Les options suivantes sont optionnelles :   
    Elles ne servent qu'à restreindre le nombre de données qui seront utilisées dans le calcul.
    Si l'une de ces options n'est pas renseignée, alors le critère associé ne sera pas filtré et toutes les données seront traités :
    -g <min> <max> : Permet de filtrer les données de sortie en ne gardant que les données qui sont dans l'intervalle de longitudes [<min>..<max>] incluses. Le format des   longitudes est un nombre réel.
    -a <min> <max> : Permet de filtrer les données de sortie en ne gardant que les relevés qui sont dans l'intervalle de latitudes [<min>..<max>] incluses. Le format des latitudes est un nombre réel.
    -d <min> <max> : filtre les dates entre les valeurs min et max
    les dates doivent être données impérativement sous la forme "YYYY-MM-DD" 
    exemple : -d 2010-05-15 2012-07-18

## -----Nous Contacter-----
    Baptiste Plaut-Aubry 
    Ayman El Kili
    Theo De Morais
    plautaubry@cy-tech.fr
    elkiliayma@cy-tech.fr
    demoraisth@cy-tech.fr
-------------------------
