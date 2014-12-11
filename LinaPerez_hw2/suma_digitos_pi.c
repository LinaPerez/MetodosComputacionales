#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#define USAGE "./a.out n_r"



int main(int argc, char **argv){
  int n_r;
  FILE *in;
  int i;
  int suma = 0; 
  int *num; 
  
  int c = 0;  
  
  /*convierte el argumento*/
   n_r = atoi(argv[1]);
  
   num = malloc(n_r * sizeof(int));
  
  
  /* revisa el numero de argumentos que entra*/ 
  if(argc!=2){
    printf("USAGE %s\n", USAGE);
    exit(1);
    }
  
  /* verifica las condicionales de los numeros que entra por parametro para que funciones, es decir que sea mayor a cero y menor a 2500000 */
  
  if (n_r<0 || n_r>2500000){
    printf("el numero no es permitido para hacer la cuenta");
    exit(1);
  }
  
  
  in = fopen("Pi_2500000.txt", "r");
  
  /*abre el archivo de los decimales de pi*/
  if(!(in=fopen("Pi_2500000.txt", "r"))){
    printf("problem opening the file\n");
    exit(1);
  }
  
  /* coge los datos del fle y los pasa de char a un puntero int */    
    
  for (i=0; i<=n_r+2; i++){
    char ti = fgetc(in);
    ti = ti-'0'; 
    num[i] = ti; 
   
    /*hace el conteo de los numeros */ 
  }
    
  for (i=2; i<(n_r+2); i++){
    suma += num[i];
   
    }
    
  /* imprime el resultado*/ 
     printf("%d\n", suma);

 
  
  return 0; 
}

