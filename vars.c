#include <stdio.h>
#include <stdlib.h>
#include "vars.h"


int** createVars(int nbSommet, int k){
  int** vars = (int**)malloc(sizeof(int*) * nbSommet);
  int n = 1;
  for(int i = 0; i < nbSommet; i++){
    vars[i] = malloc(sizeof(int) * k);
    for(int j = 0; j < k; j++){
      vars[i][j] = n;
      n++;
    }
  }
  return vars;
}

void showVars(int** vars, int w, int h){
  for(int i = 0; i < w; i++){
    for(int j = 0; j < h; j++){
      printf("%02d ", vars[i][j]);
    }
    printf("\n");
  }
}

void destroyVars(int** vars, int nbSommet){
  for(int i = 0; i < nbSommet; i++){
    free(vars[i]);
  }
  free(vars);
}
