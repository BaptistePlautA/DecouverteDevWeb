#!/bin/bash

echo "Entrée BE.sh"
#On rm aussi projet pour éviter les problèmes en cas de modif du C
echo "Suppression des traces potentielles..."
for fichier in fonctionsBE.o BE; do
    if [ -f $fichier ]; then
        rm $fichier
    fi
done

#Création du répertoire "Graphs" s'il n'existe pas
if [ ! -d "Graphs" ]; then
mkdir Graphs
echo "Création du repertoire accueillant les graphs..."
fi


if [ ! -f "BE" ]; then   
  # Compilation du programme C si l'exécutable n'existe pas
  echo "L'exécutable n'est pas présent, compilation"
  make
  # Vérification du code retour de la compilation
  if [ $? -ne 0 ]; then
    # Arrêt de l'exécution du script en cas d'erreur de compilation
    echo "Erreur dans la compilation du programme C, fin du script"
    exit 1
  fi
else
  # Message indiquant que le fichier est présent
  echo "L'exécutable est présent, pas besoin de le recompiler"
fi

# Demande à l'utilisateur quelles options du programme C il souhaite exécuter (si nécessaire à un moment : note après avoir terminé -> C'était pas nécessaire)
#echo "Ecrivez l'option(s) du programme C que vous souhaitez exécuter : --help pour afficher l'aide détaillée du programme C"
#read option

# Appel du programme C en injectant l'option choisie par l'utilisateur
./BE #$option
if [ $? -ne 0 ]; then
  # Arrêt de l'exécution du script en cas d'erreur dans le programme C
  echo "Erreur dans l'exécution du programme C"
  exit 1
fi
echo "Sortie BE.sh"

