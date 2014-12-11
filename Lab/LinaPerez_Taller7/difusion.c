#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main (){
  
  int n_x=80;
  int n_t = 100;
  int i;
  float c = 1.0;
  float nu = 0.3;
  float sigma = 0.2;
  int k; 
  float* x;
  float* u_present;
  float* u_past;
  float dx = 1.0/(n_x-1);
  int j;
  float dt =(sigma*pow(dx,2))/nu;
 
  float alpha = dt/pow(dx, 2);
  FILE *in;

  x = malloc(n_x*sizeof(float));
  u_present = malloc(n_x*sizeof(float));
  u_past = malloc(n_x*sizeof(float));
  
  in = fopen("datos_difusion.txt", "w");

  for(i=0;i<n_x;i++) {
    x[i]=i*dx;
  }
  
  for(i=0;i<n_x;i++) {
    u_present[i]=0.0;
    if(x[i]<0.66 && x[i]>0.33){
      u_present[i]=1.0;
      
    }
  }
  
  for(i=0; i<n_t; i++){
    for(k=0; k<n_x; k++){
      u_past[k] = u_present[k];
    }
    for(j=1; j<(n_x-1); j++){
      u_present[j] = (nu * alpha * u_past[j+1]) +( (1.0 - 2.0*nu*alpha)*u_past[j]) +(nu*alpha*u_past[j-1]); 
    }
    
  }
  
  for(i=0;i<n_x;i++){
    fprintf(in, "%f %f\n", x[i], u_present[i]);
  }
  
  return 0;
}
