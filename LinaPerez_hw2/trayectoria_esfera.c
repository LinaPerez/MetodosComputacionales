#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define USAGE "./a.out tetha_1 phi_1 tetha_2 phi_2"

int main(int argc, char **argv){
  int i;
  double tetha_1;
  double tetha_2;
  double phi_1;
  double phi_2;
  double Radio = 6357;  
 
  double x1;
  double y1;
  double z1;
  double x2;
  double y2;
  double z2; 

  /*revisa el numero de argumentos que entra en al consola */ 
  if(argc!=5){
    printf("USAGE: %s\n", USAGE);
    exit(1);
  }

  tetha_1 = atof(argv[1]); 
  phi_1 = atof(argv[2]);
  tetha_2 = atof(argv[3]);
  phi_2 = atof(argv[4]); 
  
  /* revisar condiciones de los angulos*/
  
  if(tetha_1<0 || tetha_2<0 || tetha_1>180 || tetha_2>180 || phi_1<0 || phi_2<0 || phi_1>360 || phi_2>360){
    printf("las coordenadas no sonvalidas para hacer el recorrido");
    exit(1);
  }
  double pi = 3.14159265358;
  double tetha_rad1;
  double tetha_rad2;
  double phi_rad1;
  double phi_rad2; 

  /* convertir de grados a radianes */ 
  tetha_rad1 = (tetha_1 * pi)/180;
  tetha_rad2 = (tetha_2 * pi)/180;
  phi_rad1 = (phi_1 * pi)/180;
  phi_rad2 = (phi_2 * pi)/180;

  
  /* cambiar a coordenadas cartesianas */ 
  x1 = Radio*sin(tetha_rad1)*cos(phi_rad1);
  y1 = Radio*sin(tetha_rad1)*sin(phi_rad1);
  z1 = Radio*cos(tetha_rad1); 

  x2 = Radio*sin(tetha_rad2)*cos(phi_rad2);
  y2 = Radio*sin(tetha_rad2)*sin(phi_rad2);
  z2 = Radio*cos(tetha_rad2); 

  /* hacer le producto cruz entre los dos puntos dado para poder hayar un vectorpara normalizarlo y hacerlo ortogonal */ 

  double x3;
  double y3;
  double z3;

  x3 = (y1*z2) - (z1*y2);
  y3 = (z1*x2) - (x1*z2); 
  z3 = (x1*y2) - (y1*x2); 

  /*normas de todos los vectores*/

  double norma_x1;
  double norma_x2;
  double norma_x3;

  norma_x1 = sqrt(pow(x1, 2)+pow(y1, 2) + pow(z1, 2));
  norma_x2 = sqrt(pow(x2, 2) + pow(y2, 2) + pow(z2, 2));
  norma_x3 = sqrt(pow(x3, 2) + pow(y3, 2) + pow(z3, 2)); 

  
  /*normalizar las nuevas coordenadas para hacerlo ortogonal*/

  double x4;
  double y4;
  double z4;

  x4 = x3/norma_x3;
  y4 = y3/norma_x3;
  z4 = z3/norma_x3;
   

  /*producto cruz entre una coordenada fija de los queentra por consola y el nuevo vector para hayar un vector perpendicular y poder parametrizar */

  double x5;
  double y5;
  double z5;

  x5 = (y2*z4) - (z2*y4);
  y5 = (z2*x4) - (x2*z4);
  z5 = (x2*y4) - (y2*x4);

  /*sacar la norma del vector 5*/
  double norma_x5;

  norma_x5 = sqrt(pow(x5, 2) + pow(y5, 2) + pow(z5, 2)); 

  /*hayar el angulo entre los vectores de las dos coordenadas dadas*/ 
  double alpha;

  alpha = acos((x1*x2 + y1*y2 + z1*z2)/(norma_x1*norma_x2)); 

  double alpha_100 = alpha/100;


  /*sacar las coordenadas x y z de un punto arbitrario sobre la curva mas corta*/ 

  double X[101];
  double Y[101];
  double Z[101];
  double x6;
  double y6;
  double z6;

  /* normalizar x5 y x2 para que me de un vector normalizado dentro de la esfera*/ 

  double x7;
  double y7;
  double z7;
  double x8;
  double y8;
  double z8;

  x7 = x5/norma_x5;
  y7 = y5/norma_x5;
  z7 = z5/norma_x5; 

  x8 = x2/norma_x2;
  y8 = y2/norma_x2;
  z8 = z2/norma_x2; 
  FILE *file;

  double x9;
  double y9;
  double z9;


  file=fopen("numeritos.txt", "w");

  /*para x y z*/
  for (i=0; i<101; i++){
    x6 = x7*sin((i)*alpha_100)+x8*cos((i)*alpha_100);
    x9 = Radio*x6;    
    X[i] = x9; 
    y6 = y7*sin((i)*alpha_100)+y8*cos((i)*alpha_100);
    y9 = Radio*y6;
    Y[i] = y9; 
    z6 = z7*sin((i)*alpha_100)+z8*cos((i)*alpha_100);
    z9 = Radio*z6;   
    Z[i] = z9; 
    fprintf(file, "%f %f %f \n", X[i], Y[i], Z[i]);
  }
  fclose(file);

  
  /*pasar las coordenadas cartesianas a esfericas */   

  double Tetha[101];
  double Phi[101];

  double Norma[101];

  for (i=0; i<101; i++){
    Norma[i] = sqrt(pow(X[i], 2) + pow(Y[i], 2) + pow(Z[i], 2)); 
   
  }

   for(i=0; i<101; i++){

     Tetha[i] = acos(Z[i]/Norma[i])*(180/pi);
     Phi[i] = atan(Y[i]/X[i])*(180/pi);
      if(phi_1>=90 || phi_1<180 || phi_2>=90 || phi_2<180){
     
      double f = Phi[i] + 180.0;
      Phi[i] = f; 
      
      }
      if(phi_1>=180 || phi_1<270 || phi_2>=180 || phi_2<270){
     
      double f = Phi[i] + 270 + 90;
      Phi[i] = f; 
      
      }
      if(phi_1>=0 || phi_1<90 || phi_2>=0 || phi_2<90){
     
      double f = Phi[i] - 360*2;
      Phi[i] = f; 
      
      }
      if(phi_1>=270 || phi_1<360 || phi_2>=270 || phi_2<360){
     
      double f = Phi[i] +180;
      Phi[i] = f; 
      
      }
     printf("%f %f \n", Tetha[i], Phi[i]);  
 }

  return 0; 
}
