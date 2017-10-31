#include "SAT.h"
#include "test.h"


void showVars(int** vars, int w, int h){
  for(int i = 0; i < w; i++){
    for(int j = 0; j < h; j++){
      printf("%02d ", vars[i][j]);
    }
    printf("\n");
  }
}



void number2(SAT_Formula f, int** vars, int k){
  int nbSommet = orderG();
  Clause c1 = create_clause(nbSommet, DISJONCTIVE);
  for(int i = 0; i < nbSommet; i++){
    c1->vars[i] = vars[i][0];
  }
  add(f, c1);
  //
  //n² +n / 2
  int nb = ((nbSommet * nbSommet) + nbSommet) / 2;
  printf("\n NB CLAUSES NUMBER 2 : %d\n\n", nb);
  for(int i = 0; i < nbSommet - 1; i++){
    for(int j = i + 1; j < nbSommet; j++){
      Clause c = create_clause(2, DISJONCTIVE);
      c->vars[0] = -vars[i][0];
      c->vars[1] = -vars[j][0];
      add(f, c);
    }
  }
}

void number3(SAT_Formula f, int** vars, int k){
  Clause c = create_clause(orderG(), DISJONCTIVE);
  for(int i = 0; i < orderG(); i++){
    c->vars[i] = vars[i][k-1];
  }
  add(f, c);
  //return c;
}

int main(int argc, char* argv[]){
  //Init vars

  int nbSommet = orderG();
  int k = 1;
  if(argc > 1)
    k = atoi(argv[1]);

  int** vars = (int**) malloc(sizeof(int*) * nbSommet);// All vars we need Xu,i, with u€V and i€[0;k]
  SAT_Formula formula = create_formula();

  int n = 1;
  for(int i = 0; i < nbSommet; i++){
    vars[i] = malloc(sizeof(int) * k);
    for(int j = 0; j < k; j++){
      vars[i][j] = n;
      n++;
    }
  }
  showVars(vars, nbSommet, k);
  printf("\n\n");

  number2(formula, vars, k);
  number3(formula, vars, k);
  /*
  1-
  */
  showFormula(formula);
  destroyFormula(formula);
  return 0;
}
