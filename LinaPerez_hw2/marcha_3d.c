#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#define USAGE "./a.out M"

/**
 * devuelve un puntero normalizado de cualqueir marcha
 */
double *vector_random(){
  double x = 2.0*(drand48()-0.5);
  double y = 2.0*(drand48()-0.5);
  double z = 2.0*(drand48()-0.5);
  /*este array lo  declaramos static para poder adquirir despues la informacion de este metodo y con tres para x , y , z*/  
 static double r[3];
  double norma;
  norma  = sqrt(pow(x,2) + pow(y, 2) + pow(z, 2));
  r[0] = x/norma;
  r[1] = y/norma;
  r[2] = z/norma;
  return r;
};

/* devuelve la distancia desde el origen hasta N pasos
 */
double distancia(int n){
  /* usamos la libreria de tiempo para poder hacer lo mas random posible a la semilla */ 
  srand48(time(NULL));
  double i;
  double x;
  double y;
  double z;
  double d;
  double *v;
  /*empieza en el origen */   
  x=0.0;
  y=0.0;
  z=0.0;
  for (i=1; i<=n; i++){
    v = vector_random();
    x += *(v + 0);
    y += *(v + 1);
    z += *(v + 2);
  }
  d = sqrt(pow(x, 2) + pow(y,2) + pow(z,2));
  return d;
}

int main(int argc, char **argv)
{
  int i;
  int  j;
  int M;
 
  char filename[25];
  FILE *file;
  double promedio;

 /*revisa el numero de argumentos que entra en al consola */ 
  if(argc!=2){
    printf("USAGE: %s\n", USAGE);
    exit(1);
  }
  /*convertir el numero de marchas*/ 
  M = atoi(argv[1]); 

 

  sprintf(filename, "final_stats_3D_%d.dat", M);
  file = fopen(filename, "w");

  for (j=10; j<=500; j+=10){
    promedio = 0.0;
   
    for (i=0; i<M; i++){
      promedio += distancia(j);
    }
    promedio = promedio/M; 
    fprintf(file, "%d %f\n", j, promedio);
  }

  fclose(file);
  return 0;
}

/* no se encontro ninguna preferencia en los pomedios, unicamente que se ve una tendencia a crecer segun el radio, pero sin emargo algunas veces se devuelve */
   



