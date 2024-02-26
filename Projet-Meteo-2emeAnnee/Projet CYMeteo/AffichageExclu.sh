#!/bin/bash

#Auteur : Ayman El Kili et Plaut-Aubry Baptiste
#Résumé : Le shell s'occupe de gérer les options et faire les graphs gnuplot
#Entré(s) : $entree_csv $sortie_csv et toutes les options utilisées
#Sortie(s) : le diagramme gnuplot et le csv

#Fichier qui va être executé par le C qui est lui même exécuté par le premier script.sh CYMeteo.sh

#Lancement du chrono pour le temps d'execution du script shell 
debut=$(date +%s)
echo "Entrée AffichageExclu.sh"


#Test arguments
for arg in "$@"
do
    # Affiche chaque argument
    echo $arg
done

#################GERER LES VARIABLES DU SHELL
#Récupère l'option du programme C pour savoir quel graph réaliser
# Récupération des options passées en argument
while getopts "whmtp" opt; do
    case $opt in
        w)  plot_vent=1;;
        h)  plot_hauteur=1;;
        m)  plot_humidite=1;;
        t)  plot_temperature=1;;
        p)  plot_pression=1;;
    esac
done


# Récupération des noms des fichiers csv d'entrée et de sortie passés en argument
entree_csv=$2
sortie_csv=$3
mode=$4 #1,2,3 ou 0 si aucun mode n'a été choisi
echo "entree_csv $entree_csv, sortie_csv $sortie_csv, mode $mode " 

shift
shift
shift
shift

# Initialisation de la variable qui indiquera si une option exclusive a été activée
option_active=0
#Pour éviter les problèmes quand le nombre d'option est 0
nombre_option=0
# Initialisation des variables min et max qui seront utilisées par l'option -d
min=""
max=""

#################


################# Traitement de l'option --help
if [ "$1" = "--help" ]; then
  echo "Description des options :"
  echo "-F : limitation des mesures à celles présentes en France métropolitaine + Corse"
  echo "-G : limitation des mesures à celles présentes en Guyane"
  echo "-S : limitation des mesures à celles présentes à Saint-Pierre-et-Miquelon (Est-Canada)"
  echo "-A : limitation des mesures à celles présentes aux Antilles (Martinique et Guadeloupe)"
  echo "-O : limitation des mesures à celles présentes dans l’Océan Indien (Mayotte et La Réunion)"
  echo "-Q activée : limitation des mesures à celles présentes en Antarctique (TAAF)"
  echo "-d <min> <max> : filtre les dates entre les valeurs min et max"
  echo "-a <min> <max> : filtre les latitudes entre les valeurs min et max"
  echo "-g <min> <max> : filtre les longitudes entre les valeurs min et max"
  echo "Sortie du programme"
  exit 0
fi

################# Traitement des arguments exclusifs
while getopts ":FGSOAQdag:" opt; do
  case $opt in
   F) # Option -F
        echo "Option -F activée :  limitation des mesures à celles présentes en France métropolitaine + Corse"
        grep ^07.*$ $entree_csv > mesures1.csv #ID FR
        option_active=$((option_active+1))
        nombre_option=$((nombre_option+1))
        shift # On shift pour éviter les erreurs avec les mins et max du -d
        ;;
    G) # Option -G
        echo "Option -G activée : limitation des mesures à celles présentes en Guyane"
        grep ^814.*$ $entree_csv > mesures1.csv #ID Guyane
        option_active=$((option_active+1))
        nombre_option=$((nombre_option+1))
        shift
        ;;
    S) # Option -S
        echo "Option -S activée : limitation des mesures à celles présentes à Saint-Pierre-et-Miquelon (Est-Canada)"
        grep ^718.*$ $entree_csv > mesures1.csv #ID Saint Pierre et Miquelon
        option_active=$((option_active+1))
        nombre_option=$((nombre_option+1))
        shift
        ;;
    A) # Option -A
        echo "Option -A activée : limitation des mesures à celles présentes aux Antilles"
        grep ^78.*$ $entree_csv > mesures1.csv #ID Antilles
        option_active=$((option_active+1))
        nombre_option=$((nombre_option+1))
        shift
        ;;
    O) # Option -O
        echo "Option -O activée : limitation des mesures à celles présentes dans l’Océan Indien"
        grep ^67.*$ $entree_csv > mesures1.csv #ID Mayotte
        grep ^61980.*$ $entree_csv >> mesures1.csv #ID La Réunion
        option_active=$((option_active+1))
        nombre_option=$((nombre_option+1))
        shift
        ;;
    Q) # Option -Q
        echo "Option -Q activée : limitation des mesures à celles présentes en Antarctique"
        grep ^619.*$ $entree_csv | grep -v 61980 > mesures1.csv #ID TAAF sauf Réunion
        option_active=$((option_active+1))
        nombre_option=$((nombre_option+1))
        shift
        ;;
    d) # Option -d <min> <max>
        # Vérif du nombre d'arguments après l'option -d
        echo "Option -d activée"
        if [ $# -ne 3 ] && [ "$4" != "-a" ] && [ "$4" != "-g" ]; then
          echo "Erreur : nombre d'arguments après l'option -d incorrect"
          exit 1
        fi
        # Si une option a été activée, il faut utiliser le fichier déjà modifié
        if [ $option_active -eq 1 ]; then
          echo "Aucune option géographique activée et -d activé :"
          sort -t';' -k2 mesures1.csv > mesuresTmp.csv #Tri croissant des dates
          rm mesures1.csv
          min=$2
          max=$3
          awk -F ';' '$2 >= "'$min'" && $2 <= "'$max'" {print $0}' mesuresTmp.csv > mesures1.csv #On garde ce qui est >min <max
          rm mesuresTmp.csv
          echo "min $min" #DEBUG
          echo "max $max" #DEBUG
          nombre_option=$((nombre_option+1))
          shift
          shift 
          shift
        fi
        #Sinon on fait avec le fichier d'entrée
        if [ $option_active -eq 0 ]; then
          echo "Aucune option géographique activée, -d activé :"
          sort -t';' -k2 $entree_csv > mesuresTmp.csv  #Tri croissant des dates
          min=$2
          max=$3
          awk -F ';' '$2 >= "'$min'" && $2 <= "'$max'" {print $0}' mesuresTmp.csv > mesures1.csv #On garde ce qui est >min <max
          rm mesuresTmp.csv
          echo "min $min" #DEBUG
          echo "max $max" #DEBUG
          nombre_option=$((nombre_option+1))
          shift
          shift
          shift
        fi    
        ;;
         a)
      echo "Latitude"
        if [ $# -ne 3 ] && [ "$4" != "-d" ] && [ "$4" != "-g" ]; then
          echo"$4"
          echo "Erreur : nombre d'arguments après l'option -a incorrect"
          exit 1
        fi
      min_lat="$2"
      max_lat="$3"
      echo "min $min_lat"#DEBUG
      echo "max $max_lat"#DEBUG
      if [ -n "$min_lat" -a -n "$max_lat" ]; then
        if [ $option_active -eq 0 ]; then
          awk -F ';' '$10 >= "'$min_lat'" && $10 <= "'$max_lat'" {print $0}' $entree_csv > mesures1.csv
        else
          awk -F ';' '$10 >= "'$min_lat'" && $10 <= "'$max_lat'" {print $0}' mesures1.csv > mesuresTmp.csv
          mv mesuresTmp.csv mesures1.csv
        fi
      fi
      shift
      shift
      shift
      ;;
    g)
      echo "Longitude"
        if [ $# -ne 3 ] && [ "$4" != "-d" ] && [ "$4" != "-a" ]; then
          echo "Erreur : nombre d'arguments après l'option -g incorrect"
          exit 1
        fi
      min_long="$2"
      max_long="$3"
      echo "min long $min_long" #DEBUG
      echo "max long $max_long" #DEBUG
      if [ -n "$min_long" -a -n "$max_long" ]; then
       if [ $option_active -eq 0 ]; then
          awk -F ',' '$2 >= "'$min_long'" && $2 <= "'$max_long'" {print $0}' $entree_csv > mesures1.csv
        else
          awk -F ',' '$2 >= "'$min_long'" && $2 <= "'$max_long'" {print $0}' mesures1.csv > mesuresTmp.csv
          mv mesuresTmp.csv mesures1.csv
        fi
      fi
      shift
      shift
      shift
      ;;
    ?) # Option invalide
        echo "les options données par l'utilisateur sont $1 $2 $3"
        echo "Option invalide : -$OPTARG. Les options valides sont -F, -G, -S, -A, -O, -Q ou -d <min> <max>." 
        exit 1
        ;;
  esac
done

#################

#################VERIF DES OPTIONS

#Si rien n'est activé
if [ $nombre_option -eq 0 ]; then
  echo "Aucune option activée : pas de limite sur la position des relevés et sur la date" 
fi

  # Si aucune option n'a été activée, il n'y a pas de limite sur la position des relevés
if [ $option_active -eq 0 ]; then
  echo "Aucune option geographique activée : pas de limite sur la position des relevés"
fi

#Vérification qu'une seule option a été activée
if [ $option_active -gt 1 ]; then
  echo "Erreur : plusieurs options ont été activées" 
  exit 1
fi

#################

##################GNUPLOT

# Si l'option "-v" est présente, génération d'un diagramme de type vecteurs
if [ "$plot_vent" = "1" ]; then #J'ai eu des problèmes avec le -eq pour eux donc j'ai changé j'imagine qu'il prend ça comme des chaines de caractères
  echo "Plot Vecteurs" #Simple nom de code pour voir si c'est bien rentré
# Extraire les colonnes nécessaires et séparer la latitude et la longitude
  if [ $nombre_option -eq 0 ]; then 
    awk -F';' '{if ($1!="" && $4!="" && $5!="" && $10!="") print $1";"$4";"$5";"$10}' $entree_csv | sed 's/,/;/g' > temp0.csv
  fi
  if [ $nombre_option -ge 1 ]; then 
    awk -F';' '{if ($1!="" && $4!="" && $5!="" && $10!="") print $1";"$4";"$5";"$10}' mesures1.csv | sed 's/,/;/g' > temp0.csv
    rm mesures1.csv
  fi

#Sinon ça bug des fois
touch temp1.csv
# Boucle pour traiter les données pour chaque station
while IFS=';' read -r id alpha vitesse lat lon; do
  # Ecrire les résultats dans le fichier temporaire
  echo "$id;$alpha;$vitesse;$lat;$lon" >> temp1.csv
done < temp0.csv

# Trier les données par identifiant croissant de la station
sort -t ';' -k 1 -n temp1.csv > temp2.csv
rm temp1.csv
rm temp0.csv
# Calculer la moyenne des vents et de l'angle pour chaque station
awk -F';' '{sum_angle[$1]+=$2; sum_vitesse[$1]+=$3; count[$1]++; lat[$1]=$4; lon[$1]=$5;} END {for (i in sum_angle)
 printf("%s;%.2f;%.2f;%s;%s\n",i,sum_angle[i]/count[i],sum_vitesse[i]/count[i],lat[i],lon[i])}' temp2.csv > temp3.csv
rm temp2.csv
# Calculer xdelta et ydelta pour chaque station
while IFS=';' read -r id alpha vitesse lat lon; do
  xdelta=$(awk "BEGIN {print cos($alpha)*$vitesse}")
  ydelta=$(awk "BEGIN {print sin($alpha)*$vitesse}")
  echo "$id;$lat;$lon;$xdelta;$ydelta" >> temp4.csv
done < temp3.csv

# On garde seulement les ids uniques
awk -F';' '!seen[$1]++' temp4.csv > $sortie_csv

rm temp3.csv
rm temp4.csv
#Verif perso
#hea d$sortie_csv

#longitude/latitude/finX/finY
gnuplot -e "
    set terminal pngcairo size 600,600;
    set title 'Graphe vecteurs';
    set datafile separator ';';
    set output 'GrapheVECTEURS.png';
    set xlabel 'Longitude (Ouest-Est)';
    set ylabel 'Latitude (Nord-Sud)';
    set dgrid3d 100,100,10;
    set grid linetype 1 linecolor rgb 'gray';
    plot '$sortie_csv' using 3:2:5:4 with vectors head size screen 0.02,10,5 filled back lc rgb 'black'"
fi 



# Si l'option "-h" est présente, génération d'un diagramme de type carte interpolée et colorée
if [ "$plot_hauteur" = "1" ]; then
  echo "Plot Hauteur"
  if [ $nombre_option -eq 0 ]; then # J'ai pas trouvé de meilleure solution quand y'a pas d'option entrée
    awk -F';' '{print $1";"$10";" $14}' $entree_csv > a1.csv 
  fi
  if [ $nombre_option -ge 1 ]; then # J'ai pas trouvé de meilleure solution quand y'a pas d'option entrée
    awk -F';' '{print $1";"$10";" $14}' mesures1.csv > a1.csv
    rm mesures1.csv
  fi
  sort -u a1.csv > a2.csv #Sort des IDs uniques
  rm a1.csv
  sort -t';' -k3nr a2.csv > a3.csv #Tri hauteur décroissant
  rm a2.csv
  sed 's/,/;/g' a3.csv > $sortie_csv
  rm a3.csv
  # Générer le graphique avec Gnuplot
  gnuplot -e "
    set terminal png size 600,600;
    set title 'Graph hauteur';
    set datafile separator ';';
    set output 'GrapheHAUTEUR.png';
    set xlabel 'Longitude (Ouest-Est)';
    set ylabel 'Latitude (Nord-Sud)';
    set palette rgb 10,12,14;
    set dgrid3d 100,100,10;
    splot '$sortie_csv' using 3:2:4 with pm3d"

fi

# Si l'option "-m" est présente, génération d'un diagramme de type carte interpolée et colorée
if [ "$plot_humidite" = "1" ]; then
  echo "Plot Humidite" 
  if [ $nombre_option -eq 0 ]; then 
    awk -F';' '{print $1";"$10";" $6}' $entree_csv > a1.csv
  fi
  if [ $nombre_option -ge 1 ]; then 
    awk -F';' '{print $1";"$10";" $6}' mesures1.csv > a1.csv
    rm mesures1.csv
  fi
awk -F';' '{a[$1]=$3>a[$1]?$3";"$2:a[$1]} END {for (i in a) print i";"a[i]}' a1.csv | sort -t';' -k2nr > a2.csv
rm a1.csv
sed 's/,/;/g' a2.csv > $sortie_csv
rm a2.csv

gnuplot -e "
    set terminal png size 600,600;
    set title 'Graph Humidite';
    set datafile separator ';';
    set output 'GrapheHUMIDITE.png';
    set xlabel 'Longitude (Ouest-Est)';
    set ylabel 'Latitude (Nord-Sud)';
    set palette rgb 10,12,14;
    set dgrid3d 100,100,10;
    set pm3d interpolate 0,0;
    splot '$sortie_csv' using 4:3:2 with pm3d"
fi

################## -t
# Si l'option "-t" est présente, et que mode = 1
if [ "$plot_temperature" = "1" ] && [ "$mode" = "1" ]; then 
  echo "Plot Temperature Mode 1" 
  if [ $nombre_option -eq 0 ]; then 
    awk -F';' '{print $1";"$11}' $entree_csv > temp0.csv
  fi
  if [ $nombre_option -ge 1 ]; then
    awk -F';' '{print $1";"$11}' mesures1.csv > temp0.csv
    rm mesures1.csv
  fi
  # Extraire les colonnes de station et de température
  cut -f1,2 -d\; temp0.csv > temp1.csv
  rm temp0.csv
  # Tri du fichier par numéro de station
  sort -n -t\; -k1 temp1.csv > temp2.csv
  rm temp1.csv

  # Grouper les lignes par station et calculer les températures minimales, maximales et moyennes
  awk -F\; '{
    if (a[$1]) {
      a[$1] = a[$1]" "$2
    } else {
      a[$1] = $2
    }
  }
  END {
    for (i in a) {
      split(a[i], b, " ")
      min=b[1]
      max=b[1]
      sum=0
      for (j in b) {
        if (b[j] < min) {min = b[j]}
        if (b[j] > max) {max = b[j]}
        sum += b[j]
      }
      print i ";" min ";" max ";" sum/length(b)
    }
  }' temp2.csv > temp3.csv

  sort -t';' -k1n temp3.csv > $sortie_csv
rm temp2.csv
rm temp3.csv
gnuplot -e "
  set terminal png size 600,600;
  set title 'Graph temperature';
  set datafile separator ';';
  set output 'GrapheTMODE1.png';
  set xlabel 'ID de la station';
  set ylabel 'min/max/moy';
  set key font ',8';
  plot '$sortie_csv' using 1:2 linetype rgb 'blue' with yerrorbar, '$sortie_csv' using 1:3 linetype rgb 'green' with yerrorbar, '$sortie_csv' using 1:4 linetype rgb 'red' with yerrorbar"
fi  



if [ "$plot_temperature" = "1" ] && [ "$mode" = "2" ]; then 
  echo "Plot Temperature Mode 2"
  if [ $nombre_option -eq 0 ]; then
    # Extraction des colonnes de date/heure et de température : on ne prend pas les lignes vides
    awk -F';' '$7!=""{print $2";"$11}' $entree_csv > temp0.csv
  fi
  if [ $nombre_option -ge 1 ]; then
    # Extraction des colonnes de date/heure et de température : on ne prend pas les lignes vides
    awk -F';' '$7!=""{print $2";"$11}' mesures1.csv > temp0.csv
    rm mesures1.csv
  fi

# Trier le fichier temporaire par date/heure
sort -k1 temp0.csv > temp1.csv
rm temp0.csv
# Calculer la moyenne de température pour chaque date/heure
awk '{a[$1]+=$2;b[$1]++;}END{for (i in a) {print i ";" a[i]/b[i]}}' temp1.csv | awk -F";" '{print $1 ";" $2}' > temp2.csv
rm temp1.csv
# Tri final du fichier par date/heure
sort -t';' -k1 temp2.csv > $sortie_csv
rm temp2.csv
# Utilisation de gnuplot pour afficher le graphique
gnuplot -e "
    set terminal png size 600,600;
    set output 'GrapheTMODE2.png';
    set datafile separator ';';
    set title 'Graphe Mesures';
    set xlabel 'Temps';
    set ylabel 'Mesures Moyennes Temperature';
    set xdata time;
    set timefmt '%Y-%m-%d';
    plot '$sortie_csv' using 1:2 with lines linetype 1 lc rgb 'red'"
fi



if [ "$plot_temperature" = "1" ] && [ "$mode" = "3" ]; then 
  echo "Plot Temperature Mode 3"
  if [ $nombre_option -eq 0 ]; then
    awk -F';' '{print $1";"$2";" $11}' $entree_csv > a1.csv
  fi
  if [ $nombre_option -ge 1 ]; then
    awk -F';' '{print $1";"$2";" $11}' mesures1.csv > a1.csv
    rm mesures1.csv
  fi
  sort -t ';' -k1,1n -k2,2 a1.csv > $sortie_csv
  rm a1.csv
  # Extraire les heures uniques
  cut -d ';' -f2 $sortie_csv | cut -d 'T' -f2 | cut -d ':' -f1 | sort -u > heures_uniques.txt

  # Générer un fichier de données pour chaque heure unique (on va effacer après)
  while read heure; do
      grep "T$heure:" $sortie_csv > $heure.txt
  done < heures_uniques.txt

  # Spécifier les options de tracé et les commandes gnuplot = GROS BAZARD
  gnuplot -e "
  set terminal png;
  set output 'GrapheTMODE3.png';
  set datafile separator ';';
  set title 'Diagramme multilignes des Temperatures';
  set xdata time;
  set format x '%Y-%m';
  set xlabel 'Dates de relevé';
  set timefmt '%Y-%m';
  set ylabel 'Mesures °C';
  set key font ',5';
  plot '01.txt' using 2:3 with lines linetype 1 lc rgb 'red', '02.txt' using 2:3 with lines linetype 2 lc rgb 'blue',
  '04.txt' using 2:3 with lines linetype 3 lc rgb 'green', '05.txt' using 2:3 with lines linetype 4 lc rgb 'purple',
  '07.txt' using 2:3 with lines linetype 5 lc rgb 'orange', '08.txt' using 2:3 with lines linetype 6 lc rgb 'black',
  '10.txt' using 2:3 with lines linetype 7 lc rgb 'pink', '11.txt' using 2:3 with lines linetype 8 lc rgb 'brown',
  '13.txt' using 2:3 with lines linetype 9 lc rgb 'cyan', '14.txt' using 2:3 with lines linetype 10 lc rgb 'gray',
  '16.txt' using 2:3 with lines linetype 11 lc rgb 'violet', '17.txt' using 2:3 with lines linetype 12 lc rgb 'magenta',
  '19.txt' using 2:3 with lines linetype 13 lc rgb 'yellow', '20.txt' using 2:3 with lines linetype 14 lc rgb 'white',
  '22.txt' using 2:3 with lines linetype 15 lc rgb 'light-red', '23.txt' using 2:3 with lines linetype 16 lc rgb 'light-blue'"

  # On supprime les fichiers d'heures
      while read heure; do
          rm $heure.txt
      done < heures_uniques.txt
    rm heures_uniques.txt
fi   

##################




################## -p
# Si l'option "-p" est présente, on fait attention au mode
if [ "$plot_pression" = "1" ] && [ "$mode" = "1" ]; then 
  echo "Plot Pression Mode 1" 
  if [ $nombre_option -eq 0 ]; then
    awk -F';' '{print $1";"$7}' $entree_csv > temp0.csv
  fi
  if [ $nombre_option -ge 1 ]; then
    awk -F';' '{print $1";"$7}' mesures1.csv > temp0.csv
    rm mesures1.csv
  fi

  # Extraire les colonnes de station et de pression
  cut -f1,2 -d\; temp0.csv > temp1.csv
  rm temp0.csv

  # Tri du fichier par numéro de station
  sort -n -t\; -k1 temp1.csv > temp2.csv
  rm temp1.csv

  # Grouper les lignes par station et calculer les pression minimales, maximales et moyennes
  awk -F\; '{
    if (a[$1]) {
      a[$1] = a[$1]" "$2
    } else {
      a[$1] = $2
    }
  }
  END {
    for (i in a) {
      split(a[i], b, " ")
      min=b[1]
      max=b[1]
      sum=0
      for (j in b) {
        if (b[j] < min) {min = b[j]}
        if (b[j] > max) {max = b[j]}
        sum += b[j]
      }
      print i ";" min ";" max ";" sum/length(b)
    }
  }' temp2.csv > temp3.csv

  sort -t';' -k1n temp3.csv > $sortie_csv
  rm temp2.csv
  rm temp3.csv

gnuplot -e "
  set terminal png size 600,600;
  set title 'Graph Pression';
  set datafile separator ';';
  set output 'GraphePMODE1.png';
  set xlabel 'ID de la station';
  set ylabel 'min/max/moy';
  set key font ',8';
  plot '$sortie_csv' using 1:2 linetype rgb 'blue' with yerrorbar, '$sortie_csv' using 1:3 linetype rgb 'green' with yerrorbar, '$sortie_csv' using 1:4 linetype rgb 'red' with yerrorbar"
fi     



if [ "$plot_pression" = "1" ] && [ "$mode" = "2" ]; then 
  echo "Plot Pression Mode 2"
  if [ $nombre_option -eq 0 ]; then
    # Extraction des colonnes de date/heure et de température : on ne prend pas les lignes vides
    awk -F';' '$7!=""{print $2";"$7}' $entree_csv > temp0.csv
  fi
  if [ $nombre_option -ge 1 ]; then
    # Extraction des colonnes de date/heure et de température : on ne prend pas les lignes vides
    awk -F';' '$7!=""{print $2";"$7}' mesures1.csv > temp0.csv
    rm mesures1.csv
  fi

# Trier le fichier temporaire par date/heure
sort -k1 temp0.csv > temp1.csv
rm temp0.csv

# Calculer la moyenne de température pour chaque date/heure
awk '{a[$1]+=$2;b[$1]++;}END{for (i in a) {print i ";" a[i]/b[i]}}' temp1.csv | awk -F";" '{print $1 ";" $2}' > temp2.csv
rm temp1.csv
# Tri final du fichier par date/heure
sort -t';' -k1 temp2.csv > $sortie_csv
rm temp2.csv
  gnuplot -e "
    set terminal png size 600,600;
    set output 'GraphePMODE2.png';
    set datafile separator ';';
    set title 'graphe';
    set xlabel 'Temps';
    set xdata time;
    set timefmt '%Y-%m-%d';
    set ylabel 'Mesures Moyenne Pression';
    plot '$sortie_csv' using 2:1  with lines "
fi   



if [ "$plot_pression" = "1" ] && [ "$mode" = "3" ]; then 
  echo "Plot Pression Mode 3"
  if [ $nombre_option -eq 0 ]; then
    awk -F';' '{print $1";"$2";" $7}' $entree_csv > a1.csv
  fi
  if [ $nombre_option -ge 1 ]; then
    awk -F';' '{print $1";"$2";" $7}' mesures1.csv > a1.csv
    rm mesures1.csv
  fi
  sort -t ';' -k1,1n -k2,2 a1.csv > $sortie_csv
  rm a1.csv
  # Extraire les heures uniques
  cut -d ';' -f2 $sortie_csv | cut -d 'T' -f2 | cut -d ':' -f1 | sort -u > heures_uniques.txt

  # Générer un fichier de données pour chaque heure unique
  while read heure; do
      grep "T$heure:" $sortie_csv > $heure.txt
  done < heures_uniques.txt
  

  # Spécifier les options de tracé et les commandes gnuplot
  gnuplot -e "
  set terminal png;
  set output 'GraphePMODE3.png';
  set datafile separator ';';
  set title 'Diagramme multilignes des Pressions';
  set xdata time;
  set format x '%Y-%m';
  set xlabel 'Dates de relevé';
  set timefmt '%Y-%m';
  set ylabel 'Mesures Pression';
  set key font ',5';
  plot '01.txt' using 2:3 with lines linetype 1 lc rgb 'red', '02.txt' using 2:3 with lines linetype 2 lc rgb 'blue',
  '04.txt' using 2:3 with lines linetype 3 lc rgb 'green', '05.txt' using 2:3 with lines linetype 4 lc rgb 'purple',
  '07.txt' using 2:3 with lines linetype 5 lc rgb 'orange', '08.txt' using 2:3 with lines linetype 6 lc rgb 'black',
  '10.txt' using 2:3 with lines linetype 7 lc rgb 'pink', '11.txt' using 2:3 with lines linetype 8 lc rgb 'brown',
  '13.txt' using 2:3 with lines linetype 9 lc rgb 'cyan', '14.txt' using 2:3 with lines linetype 10 lc rgb 'gray',
  '16.txt' using 2:3 with lines linetype 11 lc rgb 'violet', '17.txt' using 2:3 with lines linetype 12 lc rgb 'magenta',
  '19.txt' using 2:3 with lines linetype 13 lc rgb 'yellow', '20.txt' using 2:3 with lines linetype 14 lc rgb 'white',
  '22.txt' using 2:3 with lines linetype 15 lc rgb 'light-red', '23.txt' using 2:3 with lines linetype 16 lc rgb 'light-blue'"

  # Supprimer les fichiers d'heures
      while read heure; do
          rm $heure.txt
      done < heures_uniques.txt
    rm heures_uniques.txt
fi   

####################################


#################################### Fonction de fin du script
#Supression des traces potentielles
#On rm aussi projet pour éviter les problèmes en cas de modif du C
echo "Suppression des traces potentielles..."
for fichier in mesures1.csv mesuresTmp.csv a1.csv a2.csv temp.csv temp0.csv temp1.csv temp2.csv temp3.csv temp4.csv projet; do
    if [ -f $fichier ]; then
        rm $fichier
    fi
done

fin=$(date +%s)
# Calcul de la durée de l'exécution 
ecart=$((fin-debut))
# Affichage de la durée de l'exécution
echo "Temps d'exécution du script : $ecart secondes"
echo "Sortie AffichageExclu.sh"

exit 0
# Fin du script
