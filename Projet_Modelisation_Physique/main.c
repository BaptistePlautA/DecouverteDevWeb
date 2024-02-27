#include "fonctionsBE.h"

//Fonction principale du programme.
int main() {
    // Initialisation des variables
    double q = 1; ///Q converti
    double d = 10;///D converti
    double grid = 20;///taille de base, modifiée par l'utilisateur au départ : taille optimale après tests
    double precision = 1;///Précision du data_generator : de base à 1 : 
    /**Pour une plus grande précision => Plus de points baisser à 0,5/0,25... */
    /**Remarque : Baisser la précision peut faire apparaître plus de données extrêmes et inadaptées*/
    printf("Quelle taille pour la longueur de votre grille: ");
    scanf("%lf", &grid);

    generate_data(q, d, grid,precision);
    return 0;
}
