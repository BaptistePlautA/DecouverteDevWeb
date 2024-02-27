#include "fonctionsBE.h"


/// Fonction pour calculer le champ électrique
void calc_electric_field(double q, double d,double r, double teta, double *Er, double *Eteta) {
    double Epsilon =1/(4*M_PI*C_CONVERT);
    *Er = (q *d * cos(teta)) / (2 * M_PI * Epsilon * pow(r, 3));
    *Eteta = (q *d  * sin(teta)) / (4 * M_PI * Epsilon * pow(r, 3));
}

// Fonction pour calculer le potentiel électrique
double calcul_potential(double q, double d, double r, double teta){
    double Epsilon =1/(4*M_PI*C_CONVERT);
    double V = (q * d * cos(teta)) / (4 * M_PI * Epsilon *pow(r,2)); // V :potentiel
    return V;
}

// Fonction pour calculer le potentiel électrique pour plusieurs points
double potentiel_multipoints(double x1, double x_origine, double y1, double y_origine,double qA){
  double x = x_origine-x1;
  double y = y_origine-y1;
  double norme = hypot(x,y);
  return (C_CONVERT*qA)/norme; ///FORMULE DU PROF ECRITE AU TABLEAU : V=(C*qA)/(||AM||)
}


// Fonction pour calculer le champ électrique pour plusieurs points
void elec_field_multipoints(double x1, double x_origine, double y1, double y_origine,double qA,double *Ex, double *Ey){
  double x = x_origine-x1;
  double y = y_origine-y1;
  double norme = hypot(x,y);
  *Ex = (C_CONVERT*qA*x)/pow(norme,3); ///FORMULE DU PROF ECRITE AU TABLEAU E=(C*qA*AM)/(||AM||^3)
  *Ey = (C_CONVERT*qA*y)/pow(norme,3); ///FORMULE DU PROF ECRITE AU TABLEAU E=(C*qA*AM)/(||AM||^3)
}



// Fonction pour générer les données pour le potentiel et le champ électrique
void generate_data(double q,double d,double grid,double precision) {
    //1 CHARGE
    FILE *file_potential = fopen("data_potential.dat", "w");
    FILE *file_field = fopen("data_field.dat", "w");

    //2 CHARGES
    FILE *file_potential_duo = fopen("data_potential_duo.dat", "w");
    FILE *file_field_duo = fopen("data_field_duo.dat", "w");

    //4 CHARGES
    FILE *file_potential_quatuor = fopen("data_potential_quatuor.dat", "w");
    FILE *file_field_quatuor = fopen("data_field_quatuor.dat", "w");

  // On génère les données pour le potentiel et le champ elec dans une énorme boucle
    for (double i = (-grid); i < grid+1; i+=precision) {
        for (double j = (-grid); j < grid+1; j+=precision) {

            //Variables calculées à chaque boucles
            double x = i;
            double y = j;

            /***ICI SETUP DES VARIABLES POUR 1 CHARGE : (PAS BESOIN DE MODIF) ***/
            double r = sqrt(x*x + y*y);
            double teta = atan(y/x);
            //printf("r : %lf \n",r); ////DEBUG
            //printf("teta : %lf \n",teta);
            /*******************FIN SETUP 1 CHARGE ******************************/


            /******************ELEC_FIELD 1 CHARGE*******************************/
            double Er, Eteta;
            calc_electric_field(q, d ,r, teta, &Er, &Eteta);
            double Ex = Er*cos(teta);
            double Ey = Eteta*sin(teta);
            if(abs(Ex > 1) || abs(Ey > 1)){  /////Restreindre pour éviter des valeurs extrêmes
                Ex = 0;
                Ey = 0;
            }
            //printf("Ex %lf \n",Ex); //// DEBUG
            //printf("Ey %lf \n",Ey);
            /******************FIN ELEC_FIELD 1 CHARGE**************************/


            /******************POTENTIEL 1 CHARGE*******************************/
            double V = calcul_potential(q, d, r, teta);
            if((x == 0) && (y==0)){
                V = 0;
            }
            //printf("V : %lf \n",V);//// DEBUG
            /******************FIN POTENTIEL 1 CHARGE***************************/




            /*****ICI SETUP DES VARIABLES POUR 2 CHARGES : POTENTIEL+ELEC_FIELD****/
            /**/double x1 = -4;
            /**/double y1 = 12;
            /**/double x2 = 18;
            /**/double y2 = -2;
            /**/
            /**/double q1 = 1;
            /**/double q2 = 1;
            /*******************FIN SETUP 2 CHARGES******************************/


            /******************ELEC_FIELD 2 CHARGES*******************************/
            double Ex_2 = 0.0;
            double Ey_2 = 0.0;

            // Calcul pour le premier point
            elec_field_multipoints(x1, x, y1, y, q1, &Ex_2, &Ey_2);

            // Calcul pour le deuxième point en ajoutant le champ électrique précédent
            double Ex_2_prev = Ex_2;
            double Ey_2_prev = Ey_2;
            elec_field_multipoints(x2, x, y2, y, q2, &Ex_2, &Ey_2);
            Ex_2 += Ex_2_prev;
            Ey_2 += Ey_2_prev;

            if(abs(Ex_2 > 1) || abs(Ey_2 > 1)){ 
                Ex_2 = 0;
                Ey_2 = 0;
            }
            /******************FIN ELEC_FIELD 2 CHARGES**************************/


            /******************POTENTIEL 2 CHARGES*******************************/

            ///x : ordonnée à l'origine   et x1, x2 coeff directeurs
            double V_2 = potentiel_multipoints(x1,x,y1,y,q1) + potentiel_multipoints(x2,x,y2,y,q2);
            if((x == 0) && (y==0)){
                V_2 = 0;
            }
            /******************FIN POTENTIEL 2 CHARGES***************************/




            /*********ICI SETUP DES VARIABLES POUR 4 CHARGES : POTENTIEL+ELEC_FIELD*/
            /**/double x3 = 10;                                                
            /**/double y3 = 12;
            /**/double x4 = 2;
            /**/double y4 = 7;
            /**/
            /**/double x5 = 12;
            /**/double y5 = -12;
            /**/double x6 = 25;
            /**/double y6 = 1;
            /**/
            /**/double q3 = 1;
            /**/double q4 = -3;
            /**/double q5 = 5;
            /**/double q6 = 2;
            /*******************FIN SETUP 4 CHARGES******************************/

            /******************ELEC_FIELD 4 CHARGES*******************************/
            double Ex_4 = 0.0;
            double Ey_4 = 0.0;

            // Calcul pour chaque point (ça aurait clairement été plus pratique avec des classes je pense)
            elec_field_multipoints(x1, x, y1, y, q1, &Ex_4, &Ey_4);
            double Ex_4_prev = Ex_4;
            double Ey_4_prev = Ey_4;
            elec_field_multipoints(x2, x, y2, y, q2, &Ex_4, &Ey_4);
            Ex_4 += Ex_4_prev;
            Ey_4 += Ey_4_prev;

            Ex_4_prev = Ex_4;
            Ey_4_prev = Ey_4;
            elec_field_multipoints(x3, x, y3, y, q3, &Ex_4, &Ey_4);
            Ex_4 += Ex_4_prev;
            Ey_4 += Ey_4_prev;

            Ex_4_prev = Ex_4;
            Ey_4_prev = Ey_4;
            elec_field_multipoints(x4, x, y4, y, q4, &Ex_4, &Ey_4);
            Ex_4 += Ex_4_prev;
            Ey_4 += Ey_4_prev;

            if(abs(Ex_4 > 1) || abs(Ey_4 > 1)){  /////Restreindre pour éviter les extrêmes
                Ex_4 = 0;
                Ey_4 = 0;
            }
            /******************FIN ELEC_FIELD 4 CHARGES**************************/

            /******************POTENTIEL 4 CHARGES*******************************/

            ///x : ordonnée à l'origine   et x3 x4, x5 x6 coeff directeurs
            double V_4 = potentiel_multipoints(x3,x,y3,y,q3) + potentiel_multipoints(x4,x,y4,y,q4) + potentiel_multipoints(x5,x,y5,y,q5) + potentiel_multipoints(x6,x,y6,y,q6);
            if((x == 0) && (y==0)){ 
                V_4 = 0;
            }
            /******************FIN POTENTIEL 4 CHARGES***************************/



            /******************ECRITURE DANS UN FICHIER***************************/
            //1 CHARGES
            fprintf(file_field, "%lf %lf %lf %lf\n", x, y, Ex, Ey);
            fprintf(file_potential, "%lf %lf %lf\n", x, y, V);

            //2 CHARGES
            fprintf(file_field_duo, "%lf %lf %lf %lf\n", x, y, Ex_2, Ey_2);
            fprintf(file_potential_duo, "%lf %lf %lf\n", x, y, V_2);

            //4 CHARGES
            fprintf(file_field_quatuor, "%lf %lf %lf %lf\n", x, y, Ex_4, Ey_4);
            fprintf(file_potential_quatuor, "%lf %lf %lf\n", x, y, V_4);
            /*************FIN ECRITURE DANS UN FICHIER***************************/
        }
    }
    /******************EXECUTION DES DIFFERENTS SCRIPT GNUPLOT***************************/
      fclose(file_field);
      char command1[256];
      sprintf(command1, "gnuplot -persist %s", "data_field.gpi");
      system(command1);


      fclose(file_potential);
      char command2[256];
      sprintf(command2, "gnuplot -persist %s", "data_potential.gpi");
      system(command2);

      fclose(file_field_duo);
      char command4[256];
      sprintf(command4, "gnuplot -persist %s", "data_field_duo.gpi");
      system(command4);

      fclose(file_potential_duo);
      char command5[256];
      sprintf(command5, "gnuplot -persist %s", "data_potential_duo.gpi");
      system(command5);

      fclose(file_field_quatuor);
      char command6[256];
      sprintf(command6, "gnuplot -persist %s", "data_field_quatuor.gpi");
      system(command6);

      fclose(file_potential_quatuor);
      char command7[256];
      sprintf(command7, "gnuplot -persist %s", "data_potential_quatuor.gpi");
      system(command7);

      char command3[256];
      sprintf(command3, "gnuplot -persist %s", "LDC+EQUI.gpi");
      system(command3);
    /******************FIN D'EXECUTION DES DIFFERENTS SCRIPT GNUPLOT**********************/


    printf("Fin de generate_data\n");
}
