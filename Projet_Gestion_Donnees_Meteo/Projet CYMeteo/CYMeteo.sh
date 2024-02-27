#!/bin/bash

echo "Entrée CYMeteo.sh"
if [ ! -f "projet" ]; then        #####################################"MODIF QUAND ON AURA UN VRAI NOM DE FICHIER C BIEN EVI-DEMMENT"
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

# Demande à l'utilisateur quelles options du programme C il souhaite exécuter
echo "Ecrivez l'option(s) du programme C que vous souhaitez exécuter : --help pour afficher l'aide détaillée du programme C"
read option

# Appel du programme C en injectant l'option choisie par l'utilisateur
./projet $option
if [ $? -ne 0 ]; then
  # Arrêt de l'exécution du script en cas d'erreur dans le programme C
  echo "Erreur dans l'exécution du programme C"
  exit 1
fi
echo "Sortie CYMeteo.sh"