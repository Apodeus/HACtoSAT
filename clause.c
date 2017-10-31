#include <stdio.h>
#include <stdlib.h>
#include "clause.h"

Clause create_clause(int n, int cond){
  Clause clause = (Clause)malloc(sizeof(Clause));
  clause->length = n;
  clause->cond = cond;
  clause->vars = (int*)malloc(sizeof(int) * n);

  for(int i = 0; i < 0; i ++){
    clause->vars[i] = 0;
  }

  return clause;
}

void destroyClause(Clause c){
  free(c->vars);
  free(c);
}

void showClause(Clause c){
  for(int i = 0; i < c->length; i++){
    printf("%d ", c->vars[i]);
  }
  printf("\n");
}
