#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_const_mksa.h> //Epsilon
#ifndef fonctionsBE_h
#define fonctionsBE_h

/*Auteurs :Plaut-Aubry Baptiste, Team TAB
Date : Mai 2023
Résumé : BUREAU D'ETUDE PARTIE RESOLUTION NUMERIQUE
Entré(s) : aucune.
Sortie(s) : Graphs d'études de LDC et Elec Field
*/


/**********************************************************************************/
/*Constantes Physiques utilisées dans le programme :                              */
/*                                                                                */ 
/*EO 8.85418782e-12 --> GSL_CONST_MKSA_VACUUM_PERMITTIVITY //Permittivité du vide */
/*PI = M_PI                                                                       */ 
/*c 8.9875517849e+9 // Constante de Coulomb                                       */ 
/*q 1.602176634e-19 // Charge de l'électron                                       */ 
/*d 1e-10 //Distance d                                                            */ 
/*                                                                                */ 
/**********************************************************************************/

#define C_CONVERT 14.398/// C_CONVERT = C * Q / D 
//C_CONVERT Adaptée pour éviter les problèmes avec les très grand puissances   


/********PROECEDURES ET FONCTIONS DU PROGRAMMES ********/

///Calcul elec field 1 charge
void calc_electric_field(double q, double d, double r, double teta, double *Er, double *Eteta);

///Calcul potentiel field 1 charge
double calcul_potential(double q, double d, double r, double teta);

///Calcul potentiel multi-charges
double potentiel_multipoints(double x1, double x2, double y1, double y2,double qA);

///Calcul elec field multi-charges
void elec_field_multipoints(double x1, double x_origine, double y1, double y_origine,double qA,double *Ex, double *Ey);

///Réalise toutes les étapes du programmes :
//1.Ouvre les fichiers de données
//2.Calcule et écrit dans chaque .dat pour chaque loop avec les var fixées dans fonctionsBE.c
//3.Appelle chaque .gpi avec les données calculées
void generate_data(double q,double d,double grid,double precision);


#endif
